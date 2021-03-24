#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void writeReg(uint8_t slave_address, char reg_addr, char data) {
    const uint16_t clk_div = BCM2835_I2C_CLOCK_DIVIDER_2500;
    if (!bcm2835_init()) {
        printf("bcm2835_init failed. Are you running as root??\n");
        return;
    }
    bcm2835_i2c_setSlaveAddress(slave_address);
    bcm2835_i2c_setClockDivider(clk_div);
    
    char buffer[]={reg_addr, data};
    bcm2835_i2c_write(buffer,2);
	
    bcm2835_close(); 
}

char readReg(uint8_t slave_address, char reg_addr) {
    const uint16_t clk_div = BCM2835_I2C_CLOCK_DIVIDER_2500;

    if (!bcm2835_init()) {
        printf("bcm2835_init failed. Are you running as root??\n");
        return 'n';
    }

    bcm2835_i2c_setSlaveAddress(slave_address);
    bcm2835_i2c_setClockDivider(clk_div);

    char buffer[]={reg_addr};
    bcm2835_i2c_write(buffer,1);
    bcm2835_i2c_read(buffer,1);
    
    bcm2835_close();
    
    return (char)buffer[0];
}

char logs[4][100];

int main(int argc, char **argv){
	uint8_t addr = 0x68;
	uint8_t addr2 = 0x4D;
	char days[7][4] = {"Mon","Tue","Wed","Thr","Fri","Sat","Sun"};
	char amorpm[3] = "AM";
	//Data inti
	char i = 0;
	for(i = 0; i < 7;i++){
		if(i < 2){
			writeReg(addr,i,0x00);
		}
		else if(i == 2){
			writeReg(addr,i,0x52);
		} else{
			writeReg(addr,i,0x01);
		}
	}
	int recNum = 1;
	while(1){
		int write_flag = 0;
		char sec = readReg(addr,0x00);
		char min;
		char hour;
		char weekd;
		char day;
		char month;
		char year;
		char temp = readReg(addr2,0x00);
		//Check if 10 seconds have passed or temperature is above threshold
		if(sec % 16 == 0 || temp >= 30){
			min = readReg(addr,0x01);
			hour = readReg(addr,0x02);
			weekd = readReg(addr,0x03);
			day = readReg(addr,0x04);
			month = readReg(addr,0x05);
			year = readReg(addr,0x06);
			write_flag = 1;
		}
		if(write_flag){
			//Format date numbers, BCD to decimal and check for AM or PM
			sec = ((sec & 0xF0) >> 4) * 10 + (sec & 0x0F);
			min = ((min & 0xF0) >> 4) * 10 + (min & 0x0F);
			if(hour & 0x20 == 0){
				strcpy(amorpm,"PM");
			}
			hour = ((hour & 0x10) >> 4) * 10 + (hour & 0x0F);
			day = ((day & 0x30) >> 4) * 10 + (day & 0x0F);
			month = ((month & 0x10) >> 4) * 10 + (month & 0x0F);
			year = ((year & 0x0F) >> 4 )*10 + (year & 0x0F);
			
			//Print the temperature and the date
			printf("RECEIVER> Temperature: %d °C\n",temp);
			printf("RECEIVER> Record %d: %d/%d/%d %s %d:%d:%d %s \n",recNum,day,month,year,days[weekd - 1],hour,min,sec,amorpm);
			
			//Save temperature and date into strings
			char logOut[100];
			char tempOut[100];
			sprintf(logOut,"RECEIVER> Record %d: %d/%d/%d %s %d:%d:%d %s \n",recNum,day,month,year,days[weekd - 1],hour,min,sec,amorpm);
			sprintf(tempOut,"RECEIVER> Temperature: %d °C\n",temp);
			
			//Save into logs matrix to keep track of 3 logs
			strcpy(logs[0],tempOut);
			strcpy(logs[(recNum - 1) % 3 + 1],logOut);
			FILE* fp = fopen("/home/pi/Desktop/log.txt","w"); 
			
			//Dump logs matrix into .txt file
			if(recNum < 3){
				for(int i = 0; i < recNum + 1;i++){
					if(i == 0){
						fprintf(fp,"%s",tempOut);
					} else{
						fprintf(fp,"%s",logs[i]);
					}
				}
			} else{
				for(int i = 0; i < 4;i++){
					if(i == 0){
						fprintf(fp,"%s",tempOut);
					} else{
						fprintf(fp,"%s",logs[i]);
					}
				}
			}
			fclose(fp);
			
			recNum++;
			write_flag = 0;
			delay(1000);
			
		}
	}
	return 0;
}
