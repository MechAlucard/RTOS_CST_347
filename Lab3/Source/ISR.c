#include <LPC23xx.H>
#include <stdio.h>
#include "rtos.h"
void irq_interrupt_service_routine(void)
{
	if( T0IR & 0x01 ) //if Timer0
	{	
		T0IR = 1;//reset Int
		timerTick();
	}

	VICVectAddr = 0; /*Ack the interrupt*/
    return;
}
