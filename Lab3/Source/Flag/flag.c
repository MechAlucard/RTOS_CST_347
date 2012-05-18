#include "flag.h"
#include <LPC23xx.H>    
//initalizes GPOI pin P#[3] to be output
void flag_init(void)
{
	PINSEL6 = 0;
	FIO3DIR = 0x00000008; //set pin 3 as output
	FIO3MASK = 0x00000000;
}
//set GPIO pin P3[3]
void flag_set()
{
	FIO3SET = 0x08;    
}
//clear GPIO pin P3[3]
void flag_clear()
{
	FIO3CLR = 0x08;    
}
