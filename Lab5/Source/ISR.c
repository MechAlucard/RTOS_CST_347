#include <LPC23xx.H>
#include <stdio.h>
#include "rtos.h"
#include "Flag/flag.h"
void irq_interrupt_service_routine(void)
{
	//flag_set();
	if( T0IR & 0x01 ) //if Timer0
	{	
		T0IR = 1;//reset Int
		timerTick();
	}

	VICVectAddr = 0; /*Ack the interrupt*/
    return;
}
