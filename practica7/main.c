/*
 * P7_PavloHunverto.c
 *
 * Created: 4/27/2021 11:32:46 PM
 * Author : L03068681
 */ 

#include "stdint.h"
#include "sam.h"
#include "myprintf.h"
#include "spi.h"

void UARTInit(void);
void initCycles(void);
uint32_t spiXchg(const uint8_t * send_buff, uint32_t bc, uint8_t * receive_buff );
void rcvr_datablock(const uint8_t * send_buff, uint32_t lba, uint8_t * receive_buff, uint32_t bs );

#define RXBUFSIZE 0x400
#define LENGTH_R1 0x03
#define LENGTH_R7 0x07

#define SIZE_SD_CMD 0x06
#define kCMD00 0x40
#define kCMD08 0x48
#define kCMD55 0x77
#define kCMD41 0x69

uint8_t CMD00[SIZE_SD_CMD]  = {0x40, 0x00, 0x00, 0x00, 0x00, 0x95};
uint8_t CMD08[SIZE_SD_CMD]  = {0x48, 0x00, 0x00, 0x01, 0xAA, 0x87};
uint8_t CMD17[SIZE_SD_CMD]  = {0x51, 0x00, 0x00, 0x00, 0x00, 0x01};
uint8_t CMD172[SIZE_SD_CMD]  = {0x51, 0x00, 0x00, 0x08, 0x00, 0x01};
uint8_t CMD18[SIZE_SD_CMD]  = {0x52, 0x00, 0x00, 0x00, 0x00, 0x01};
uint8_t CMD55[SIZE_SD_CMD]  = {0x77, 0x00, 0x00, 0x00, 0x00, 0x65};
uint8_t CMD41[SIZE_SD_CMD] = {0x69, 0x40, 0x00, 0x00, 0x00, 0x77};

uint8_t RxBuffer[RXBUFSIZE];

int main(void)
{
	uint32_t temp = 0xFF;
	/* Initialize the SAM system */
	SystemInit();

	UARTInit();
	spiInit();

	initCycles();
	//myprintf("\n");
	
	
	
	/* reset instruction */
	int cm00flag = 0;
	while(!cm00flag){
		spiXchg(CMD00, SIZE_SD_CMD, RxBuffer);
		if(RxBuffer[1] == 1){
			cm00flag = 1;
		}
	}
	/* read conditions from sd card */
	spiXchg(CMD08, SIZE_SD_CMD, RxBuffer);
	if (RxBuffer[1] != 1 && RxBuffer[4] != 1 && RxBuffer[5] != 170) {
		myprintf("invalid response from sd card");
		return;
	}
		
	/* check if sd card is ready for data */
	int flag2 = 0;
	while(!flag2){
		spiXchg(CMD55, SIZE_SD_CMD, RxBuffer);
		spiXchg(CMD41, SIZE_SD_CMD, RxBuffer);
		if(RxBuffer[1] == 0){
			flag2 = 1;
		}
	}
		
	myprintf("\nSd card initialization complete\n");

	//Write your code here
	rcvr_datablock(CMD17, 0x00, RxBuffer, 0x200);
	
	myprintf("\nDone");
}

void initCycles(void){
	uint32_t i;
	REG_PORT_OUTSET0 = PORT_PA18;
	for(i=0;i<76;i++)
	spiSend(0xFF);
}

//ADD spiXchg FUNCTION TO THE “spi.c” FILE

void rcvr_datablock(const uint8_t * send_buff, uint32_t lba, uint8_t * receive_buff, uint32_t bs ) {
	uint8_t temp = 0xFF;
	uint32_t i;
	
	REG_PORT_OUTCLR0 = PORT_PA18;
	myprintf("\n\n");

	temp = send_buff[0];
	temp = spiSend(temp);
	myprintf(" %x", temp);
	
	temp = (lba >> 24);
	temp = spiSend(temp);
	myprintf(" %x", temp);
	
	temp = ((lba >> 16 ) & 0xFF);
	temp = spiSend(temp);
	myprintf(" %x", temp);

	temp = ((lba >> 8 ) & 0xFF);
	temp = spiSend(temp);
	myprintf(" %x", temp);
	
	temp = (lba & 0xFF);
	temp = spiSend(temp);
	myprintf(" %x", temp);

	temp = send_buff[5];
	temp = spiSend(temp);
	myprintf(" %x", temp);

	// Reading to find the beginning of the sector

	temp = spiSend(0xFF);
	while(temp != 0xFE){
		temp = spiSend(0xFF);
		myprintf(" %x", temp);
	}
	
	// Receiving the memory sector/block
	
	myprintf("\n\n");
	for(i=0; i< bs; i++) {
		while(SERCOM1->SPI.INTFLAG.bit.DRE == 0);
		SERCOM1->SPI.DATA.reg = 0xFF;
		while(SERCOM1->SPI.INTFLAG.bit.TXC == 0);
		while(SERCOM1->SPI.INTFLAG.bit.RXC == 0);
		temp = SERCOM1->SPI.DATA.reg;
		*(receive_buff++) = temp;
		myprintf(" %x", temp);
	}
	REG_PORT_OUTSET0 = PORT_PA18;
	myprintf("\n\n");
}

uint32_t spiXchg(const uint8_t * send_buff, uint32_t bc, uint8_t * receive_buff ) {
	uint8_t temp = 0xFF;
	uint32_t i;
	uint8_t temp_cmd = send_buff[0];
	
	REG_PORT_OUTCLR0 = PORT_PA18;
	for(i=0; i< bc; i++) {
		temp = spiSend(*(send_buff++));
		//myprintf(" %x", temp);
	}
	switch(temp_cmd) {
		case kCMD00 :
		for(i=0; i<LENGTH_R1; i++) {
			temp = spiSend(0xFF);
			receive_buff[i] = temp;
			//myprintf(" %x", temp);
		}
		break;
		case kCMD08 :
		for(i=0; i<LENGTH_R7; i++) {
			temp = spiSend(0xFF);
			receive_buff[i] = temp;
			//myprintf(" %x", temp);
		}
		break;
		case kCMD41 :
		for(i=0; i<LENGTH_R1-1; i++) {
			temp = spiSend(0xFF);
			receive_buff[i] = temp;
			//myprintf(" %x", temp);
		}
		spiSend(0xFF);
		break;
		case kCMD55 :
		for(i=0; i<LENGTH_R1; i++) {
			temp = spiSend(0xFF);
			receive_buff[i] = temp;
			//myprintf(" %x", temp);
		}
		break;
		default :
		myprintf("\n Error in CMD");
	}
	REG_PORT_OUTSET0 = PORT_PA18;
	return(temp);
}

void UARTInit(void) {
	/* Initialize the SAM system */
	SystemInit();
	/* Switch to 8MHz clock (disable prescaler) */
	SYSCTRL->OSC8M.bit.PRESC = 0;
	
	/* port mux configuration*/
	PORT->Group[0].DIR.reg |= (1 << 10);                  /* Pin 10 configured as output */
	PORT->Group[0].PINCFG[PIN_PA11].bit.PMUXEN = 1;       /* Enabling peripheral functions */
	PORT->Group[0].PINCFG[PIN_PA10].bit.PMUXEN = 1;       /* Enabling peripheral functions */
	
	/*PMUX: even = n/2, odd: (n-1)/2 */
	PORT->Group[0].PMUX[5].reg |= 0x02;                   /* Selecting peripheral function C */
	PORT->Group[0].PMUX[5].reg |= 0x20;                   /* Selecting peripheral function C */
	
	/* APBCMASK */
	//PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0;			  /* SERCOM 0 enable*/
	PM->APBCMASK.reg |= PM_APBCMASK_SERCOM0;

	/*GCLK configuration for sercom0 module: using generic clock generator 0, ID for sercom0, enable GCLK*/

	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(SERCOM0_GCLK_ID_CORE) |
	GCLK_CLKCTRL_CLKEN | GCLK_CLKCTRL_GEN(0);

	
	/* configure SERCOM0 module for UART as Standard Frame, 8 Bit size, No parity, BAUDRATE:9600*/

	SERCOM0->USART.CTRLA.reg =
	SERCOM_USART_CTRLA_DORD | SERCOM_USART_CTRLA_MODE_USART_INT_CLK |
	SERCOM_USART_CTRLA_RXPO(3/*PAD3*/) | SERCOM_USART_CTRLA_TXPO(1/*PAD2*/);
	
	uint64_t br = (uint64_t)65536 * (8000000 - 16 * 9600) / 8000000;
	
	SERCOM0->USART.CTRLB.reg = SERCOM_USART_CTRLB_RXEN | SERCOM_USART_CTRLB_TXEN | SERCOM_USART_CTRLB_CHSIZE(0/*8 bits*/);

	SERCOM0->USART.BAUD.reg = (uint16_t)br;

	SERCOM0->USART.CTRLA.reg |= SERCOM_USART_CTRLA_ENABLE;
}