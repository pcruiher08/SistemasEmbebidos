#include "stdio.h"
#include "myprintf.h"
#include "sam.h"
#include "stdbool.h"
#include "RTCControl.h"

#define SLAVE_ADDR 0x68
#define BUF_SIZE 8

uint8_t tx_buf[BUF_SIZE] = {0x00, 0x00, 0x10, 0x04, 0x04, 0x16, 0x04, 0x21};
uint8_t rx_buf[BUF_SIZE];


void UARTInit(void);

int main(void)
{
	I2CInit();
	
	sendI2CDataArray(SLAVE_ADDR, 0,tx_buf, BUF_SIZE);
	receiveI2CDataArray(SLAVE_ADDR, 0,rx_buf, BUF_SIZE);
	
	UARTInit();
	time_type time;
	
	while(true){
		
		I2CInit();
		receiveI2CDataArray(SLAVE_ADDR, 0,rx_buf, BUF_SIZE);

		time.seconds.reg = rx_buf[SECONDS_ADDR];
		time.minutes.reg = rx_buf[MINUTES_ADDR];
		time.hours.reg	= rx_buf[HOURS_ADDR];
		time.day.reg = rx_buf[DAY_ADDR];
		time.date.reg = rx_buf[DATE_ADDR];
		time.month.reg = rx_buf[MONTH_ADDR];
		time.year.reg = rx_buf[YEAR_ADDR];
		
		myprintf("%d%d/", time.date.field.dec_date, time.date.field.un_date);
		myprintf("%d%d/", time.month.field.dec_mont, time.month.field.un_month);
		myprintf("%d%d ", time.year.field.dec_year, time.year.field.un_year);
		myprintf("%d%d:", time.hours.field.dec_hours, time.hours.field.un_hours);
		myprintf("%d%d:", time.minutes.field.dec_minutes, time.minutes.field.un_minutes);
		myprintf("%d%d ", time.seconds.field.dec_seconds, time.seconds.field.un_seconds);
		myprintf("\n");
	}
	
	
	return 0;
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