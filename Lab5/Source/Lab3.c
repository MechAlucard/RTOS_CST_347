#include <stdio.h>
#include <stdlib.h>
#include "rtos.h"
#include "LCD/LCD.h"
#include "Serial/Serial.h"

threadObject_t thread1, thread2, thread3;
void Count(void);
void Count_out(void);
int32 stack1[1000], stack2[1000];

int main(void)
{
	int count = 0;
    rtosInit();
    init_serial();
    threadObjectCreate(&thread1,
                        (void *)Count,
                        0,
                        0,
                        0,
                        0,
                        &stack1[1000],
                        1,
                        INITIAL_CPSR_ARM_FUNCTION,
                        "thread1");
                        
    threadObjectCreate(&thread2,
                        (void *)Count_out,
                        0,
                        0,
                        0,
                        0,
                        &stack2[1000],
                        1,
                        INITIAL_CPSR_ARM_FUNCTION,
                        "thread2");
                        
		lcd_init();
    lcd_print("Works Yo!");
                        
    scheduler();            //This function will never return.
}                       
                        
                        
void Count(void)
{
	for(;;)
	{
		LED_Out(count);
		count++;
		if(count > 0xFF)
			count = 0;
	}
}
                    
void Count_out(void)
{
  for(;;)
	{
		printf("%d\n",count);
	}
}
 
