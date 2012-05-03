#include <stdio.h>
#include <stdlib.h>
#include "rtos.h"
#include "LCD/LCD.h"
#include "Serial/Serial.h"
#include "timer/timer.h"
#include "LED/led.h"
#define MAX_COUNT 0xFF
extern int THREAD_TIME;
threadObject_t thread1, thread2;
void Count_up(int32 * count);
void Count_out(int32 * count);
int32 stack1[1000], stack2[1000];
int main(void)
{
		int count = 0;
    rtosInit();
    init_serial();
		lcd_init();
		LED_Init();
		timer_init();
    threadObjectCreate(&thread1,
                        (void *)Count_up,
                        (int32)&count,
                        0,
                        0,
                        0,
                        &stack1[1000],
                        1,
                        INITIAL_CPSR_ARM_FUNCTION,
                        "thread1");
                        
    threadObjectCreate(&thread2,
                        (void *)Count_out,
                        (int32)&count,
                        0,
                        0,
                        0,
                        &stack2[1000],
                        1,
                        INITIAL_CPSR_ARM_FUNCTION,
                        "thread2");
                        
                        
    lcd_print("Works Yo!");
                        
    scheduler();            //This function will never return.
}                       
                        
                        
void Count_up(int32 * count)
{
   for(;;)
	{
		LED_Out(*count);
		if((*count)++ > MAX_COUNT)
			*count = 0;
	}
}
                    
void Count_out(int32 * count)
{
	for(;;)
	{
		printf("%d\n",*count);
	}
}
