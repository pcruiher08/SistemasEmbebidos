#include <bcm2835.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

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


int main(int argc, char **argv){
	uint8_t addr = 0x68;
	char data = readReg(addr,0x01);
	printf("%x \n" ,data);
	return 0;
}
