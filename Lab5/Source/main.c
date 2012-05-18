#include <stdio.h>
#include <stdlib.h>
#include "rtos.h"
#include "LCD/LCD.h"
#include "Serial/Serial.h"
#include "LED/led.h"
#include "Flag/flag.h"
#define MAX_COUNT 0xFF
extern int THREAD_TIME;
threadObject_t WriteThread1, WriteThread2, ReadThread1, ReadThread2;
void	Read1(void);
void	Read2(void);
void	Write1(void);
void	Write2(void);
int32 Rstack1[1000], Rstack2[1000];
int32 Wstack1[1000], Wstack2[1000];
int32 global_integer_array[2] = {0,0};
readerWriterLockObject_t lock;
#define READER_THREADS 2
#define	WRITER_THREADS 2
int main(void)
{
	global_integer_array[0] = 0;
	global_integer_array[1] = 0;
    rtosInit();
    init_serial();
		lcd_init();
		LED_Init();
		flag_init();
		rwLockObjectInit(&lock);
		if(READER_THREADS > 0)
			threadObjectCreate(&ReadThread1,
                        (void *)Read1,
                        0,
                        0,
                        0,
                        0,
                        &Rstack1[1000],
                        1,
                        INITIAL_CPSR_ARM_FUNCTION,
                        "ReaderThread1");
		if(READER_THREADS > 1)
			threadObjectCreate(&ReadThread2,
                        (void *)Read2,
                        0,
                        0,
                        0,
                        0,
                        &Rstack1[1000],
                        1,
                        INITIAL_CPSR_ARM_FUNCTION,
                        "ReaderThread2");
    if(WRITER_THREADS > 0)                    
			threadObjectCreate(&WriteThread1,
                        (void *)Write1,
                        0,
                        0,
                        0,
                        0,
                        &Wstack1[1000],
                        1,
                        INITIAL_CPSR_ARM_FUNCTION,
                        "WriterThread1");
		if(WRITER_THREADS > 1)                    
			threadObjectCreate(&WriteThread2,
                        (void *)Write2,
                        0,
                        0,
                        0,
                        0,
                        &Wstack2[1000],
                        1,
                        INITIAL_CPSR_ARM_FUNCTION,
                        "WriterThread2");
                        
                        
    lcd_print("Works Yo!");
    scheduler();            //This function will never return.
}                       
                        
                        
void Read1(void)
{
	for(;;)
	{
		rwLockObjectLockReader(&lock);
		printf("ReaderThread1: %d\n",global_integer_array[0]);
		rwLockObjectRelease(&lock);
	}
}
                    
void Read2(void)
{
	for(;;)
	{
		rwLockObjectLockReader(&lock);
		printf("ReaderThread2: %d\n",global_integer_array[1]);
		rwLockObjectRelease(&lock);
	}
}
void Write1(void)
{
	for(;;)
	{
		rwLockObjectLockWriter(&lock);
		global_integer_array[0]++;
		printf("WriterThread1: %d\n",global_integer_array[0]);
		rwLockObjectRelease(&lock);
	}
}
void Write2(void)
{
	for(;;)
	{
		rwLockObjectLockWriter(&lock);
		global_integer_array[1]++;
		printf("WriterThread2: %d\n",global_integer_array[1]);
		rwLockObjectRelease(&lock);
	}
}
