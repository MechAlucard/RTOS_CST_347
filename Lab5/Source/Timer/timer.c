#include "timer.h"
#include <LPC23xx.h>

void irq_interrupt_handler(void);

//setup and start timer
void timer_init(void)
{
  T0MR0         = 11999;                       //1ms timmer
  T0MCR         = 3;                           //mode inturupt and reset on timmer
  T0TCR         = 1;                           //enable timer
  VICVectAddr4  = (unsigned long)irq_interrupt_handler;//assign vector
  VICVectPriority4  = 15;
  VICIntEnable  = (1  << 4);                   //enable timer interupt
}
