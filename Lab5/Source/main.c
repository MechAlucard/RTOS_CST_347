#include <stdio.h>
#include <LPC23xx.H>
#include <stdlib.h>
#include "rtos.h"
#include "LCD/LCD.h"
#include "Serial/Serial.h"
#include "LED/led.h"
#include "Flag/flag.h"
#define MAX_COUNT 0xFF
#define READER_THREADS 1
#define	WRITER_THREADS 2
extern int THREAD_TIME;
threadObject_t WriteThread[WRITER_THREADS],ReadThread[READER_THREADS];
void	Read(int32 * count, int32 threadNumber,readerWriterLockObject_t * const lock );
void	Write(int32 * count, int32 threadNumber,readerWriterLockObject_t * const lock );
int32 Rstack[READER_THREADS][1000];
int32 Wstack[WRITER_THREADS][1000];
int32 global_integer_array[2] = {0,0};
readerWriterLockObject_t lock;

int main(void)
{
	int i;
	global_integer_array[0] = 0;
	global_integer_array[1] = 0;
    rtosInit();
    init_serial();
		lcd_init();
		LED_Init();
		flag_init();
		rwLockObjectInit(&lock);
	
		for(i = 0;READER_THREADS > i;i++)
			threadObjectCreate(&ReadThread[i],
                        (void *)Read,
                        (int32)&global_integer_array[i],
                        i,
                        (int32)&lock,
                        0,
                        &Rstack[i][1000],
                        1,
                        INITIAL_CPSR_ARM_FUNCTION,
                        "ReaderThread");
		
    for(i = 0;WRITER_THREADS > i;i++)                    
			threadObjectCreate(&WriteThread[i],
                        (void *)Write,
                        (int32)&global_integer_array[i],
                        i,
                        (int32)&lock,
                        0,
                        &Wstack[i][1000],
                        1,
                        INITIAL_CPSR_ARM_FUNCTION,
                        "WriterThread");
    lcd_print("Works Yo!");
    scheduler();            //This function will never return.
}                       
                        
                        
void Read(int32 * count, int32 threadNumber,readerWriterLockObject_t * const lock )
{
	for(;;)
	{
		rwLockObjectLockReader(lock);
		printf("RT%d: %d\n",threadNumber,*count);
		rwLockObjectRelease(lock);
	}
}
                    
void Write(int32 * count, int32 threadNumber,readerWriterLockObject_t * const lock )
{
	for(;;)
	{
		rwLockObjectLockWriter(lock);
		(*count)++;
		printf("WT%d: %d\n",threadNumber,*count);
		rwLockObjectRelease(lock);
	}
}

