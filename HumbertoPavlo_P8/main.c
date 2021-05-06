/* Kernel includes. */
#include "sam.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "uart.h"
#include "myprintf.h"

/* Priorities at which the tasks are created. */
#define myTASK_TASK_PRIORITY         	( tskIDLE_PRIORITY + 1 )
xQueueHandle Global_Queue_Handle = 0;



void my_task(void *p) {
    	while(1) {
            	static uint32_t i = 0;
            	myprintf("\nHello World task 1 %d", i++);
            	vTaskDelay(1000);
    	}
}

void receiver_task(void *p) {
	while(1) {
		static uint32_t j = 0;
		if(xQueueReceive(Global_Queue_Handle, &j, 1000)){
			myprintf("Received %d\n", j);
		}else{
			myprintf("Failed to receive data from queue\n");
		}
	}
}


void sender_task(void *p) {
	while(1) {
		static uint32_t i = 0;
		myprintf("Send %d to receiver task\n", i);
		if (! xQueueSend(Global_Queue_Handle, &i, 1000)){
			myprintf("Failed to receive data from queue\n");
		}
		i++;
		vTaskDelay(2000);
	}
}

void GPIO_thread(void *p){
  while(1){
    static uint32_t i = 4;
    if((PORT->Group[0].IN.reg & PORT_IN_IN(PORT_PA14) ) == _U_(0x00000000)){
      i = 0;
	  if (!xQueueSend(Global_Queue_Handle, &i, 1000)){
          myprintf("Failed to receive data from queue\n");
        }
    } else if((PORT->Group[0].IN.reg & PORT_IN_IN(PORT_PA09) ) == _U_(0x00000000)){
      i = 1;
	  if (!xQueueSend(Global_Queue_Handle, &i, 1000)){
          myprintf("Failed to receive data from queue\n");
        }
    } else if((PORT->Group[0].IN.reg & PORT_IN_IN(PORT_PA08) ) == _U_(0x00000000)){
      i = 2;
	  if (!xQueueSend(Global_Queue_Handle, &i, 1000)){
          myprintf("Failed to receive data from queue\n");
        }
    } else if((PORT->Group[0].IN.reg & PORT_IN_IN(PORT_PA15) ) == _U_(0x00000000)){
      i = 3;
	  if (!xQueueSend(Global_Queue_Handle, &i, 1000)){
          myprintf("Failed to receive data from queue\n");
        }
    }
	
	
    if(!xQueueReceive(Global_Queue_Handle, &i, 1000)){
			myprintf("Failed to receive data from queue\n");
		}
  }
}

void output_thread(void* p){
  while(1){
    uint32_t j = 0;
    if(xQueueReceive(Global_Queue_Handle, &j, 1000)){
      if(j == 0){
        myprintf("UP\n");
      } else if(j == 1){
        myprintf("DOWN\n");
      } else if(j == 2){
        myprintf("LEFT\n");
      } else if(j == 3){
        myprintf("RIGHT\n");
      }
	  int Ack = 5;
      xQueueSend(Global_Queue_Handle, &Ack, 1000);
    } else{
      myprintf("Failed to receive data from queue\n");
    }
  }
}


int main()
{
  SystemInit();
  /* Switch to 8MHz clock (disable prescaler) */
  SYSCTRL->OSC8M.bit.PRESC = 0;	
  initUART();

  PORT->Group[0].PINCFG[PIN_PA14].reg = 0x02; 
  PORT->Group[0].PINCFG[PIN_PA09].reg = 0x02; 
	PORT->Group[0].PINCFG[PIN_PA08].reg = 0x02; 
	PORT->Group[0].PINCFG[PIN_PA15].reg = 0x02; 

	PORT->Group[0].DIRCLR.reg = PORT_PA14; 
	PORT->Group[0].DIRCLR.reg = PORT_PA09; 
	PORT->Group[0].DIRCLR.reg = PORT_PA08; 
	PORT->Group[0].DIRCLR.reg = PORT_PA15; 
	Global_Queue_Handle = xQueueCreate(3, sizeof(int));

  xTaskCreate(GPIO_thread, "GPIO_thread", 512, NULL, myTASK_TASK_PRIORITY, NULL);
	xTaskCreate(output_thread, "output_thread", 512, NULL, myTASK_TASK_PRIORITY, NULL);

  /*
  xTaskCreate( my_task,        	    
            	"my_task",              
            	512,            	    
            	NULL,           	    
            	myTASK_TASK_PRIORITY,   
            	NULL );     
  */
  /*
  xTaskCreate(sender_task,"sender",512,NULL,myTASK_TASK_PRIORITY,NULL );         	    
  
  xTaskCreate(receiver_task,"receiver",512,NULL,myTASK_TASK_PRIORITY,NULL );         	      	    
    */
  vTaskStartScheduler();

  for( ;; );
  return(0);
}