/*
** Copyright (c) 2016-2023 Arm Limited (or its affiliates). All rights reserved.
** Use, modification and redistribution of this file is subject to your possession of a
** valid End User License Agreement for the Arm Product of which these examples are part of 
** and your compliance with all applicable terms and conditions of such license agreement.
*/

/* This file contains the main() program that displays a welcome message, enables the caches,
   performs a float calculation to demonstrate floating point, then runs the main application (sorts) */

#include <stdio.h>
#include <arm_acle.h>
#include <stdint.h>
#include "generictimer.h"
#include "v8rgicv3cpuif.h"

#define MILLISECOND 0x186A0		//100000 assuming 100MHz
#define DUALTIMER0BASE 0x9C110000
#define SYSLEDBASE 0x9C010000
#define CNTCONTROLBASE 0xAA430000

extern void enable_caches(void);
extern void GIC_configure(void);
extern void GIC_enableVirtualTimerInterrupt(void);
extern void GIC_enableDualTimer0Interrupt(void);
extern void compare_sorts(void);
float calculate( float a, float b );
void enableSystemCounter(void);
void enableDualTimer0(unsigned int);


int main(void)
{
    /* Display a welcome message via semihosting */
    printf("Cortex-R52 bare-metal startup example with GIC\n");

    /* Enable the caches */
    enable_caches();

    /* Perform a float calculation to demonstrate floating point (using the FPU, if compiled appropriately) */
#ifdef __ARM_FP
    printf("Floating point calculation using the FPU...\n");
#else
    printf("Floating point calculation using the software floating point library (no FPU)...\n");
#endif
    printf("Float result is        %f\n", calculate(1.5f, 2.5f));
    printf("Float result should be 0.937500\n");

    /* Run the main application (sorts) */
    compare_sorts();

    /* Configure GIC */
	GIC_configure();

	/* Enable Virtual Timer */
	enableSystemCounter();
	setCNTV_TVAL(MILLISECOND);
	enableVirtualTimer();

	/* Configure Virtual Timer Interrupt */
	GIC_enableVirtualTimerInterrupt();
	
	/* Configure and enable Dual Timer 0 Interrupt */
	enableDualTimer0(0x29aa);
	GIC_enableDualTimer0Interrupt();

	/* Switch on first LED */
	*((volatile uint32_t*)SYSLEDBASE+2) = 0x1;
	
	/* Enable IRQ and FIQ in SVC mode */
	__asm volatile ("CPSIE if");

	while (1)
	{
		__asm volatile ("WFI");
	}
	
    return 0;
}

/* Float calculation to demonstrate the FPU, not inlined for clarity */
__attribute__((noinline)) float calculate( float a, float b )
{
    float temp1, temp2;

    temp1 = a + b;
    temp2 = a * b;
    return temp2 / temp1;
}

void enableSystemCounter(void)
{
    volatile uint32_t* CNTCR = (volatile uint32_t*) CNTCONTROLBASE; // Counter Control register
    *CNTCR |= 0x3;                                  // Enable counter and freeze in debug
}

void virtualTimerIRQhandler(void)
{
	setCNTV_TVAL(MILLISECOND);
	sendGroup1SGI(0x1000000 /* ID 1 */, 0x0 /* IRM 0 */, 0x1 /* Target CPU0 */);
}

void SGI1IRQhandler(void)
{
	static unsigned char Seconds;
	static unsigned char Minutes;
	static unsigned char Hours;
	static uint32_t ms = 1;

	if (ms==1000)
	{
		ms = 1;

		// update timer
		if (59 == Seconds)
		{
			Seconds = 0;
			if (59 == Minutes)
			{
				Minutes = 0;
				if (23 == Hours)
				{
					Hours = 0;
				}
				else
				{
					Hours++;
				}
			}
			else
			{
				Minutes++;
			}
		}
		else
		{
			Seconds++;
		}
		if (Hours >= 10)
		{
			printf("%d",Hours);
		}
		else
		{
			printf("0%d",Hours);
		}
		printf(":");
		if (Minutes >= 10)
		{
			printf("%d",Minutes);
		}
		else
		{
			printf("0%d",Minutes);
		}
		printf(":");
		if (Seconds >= 10)
		{
			printf("%d\n",Seconds);
		}
		else
		{
			printf("0%d\n",Seconds);
		}
	}
	else
		ms++;
}


// ARM Dual-Timer Module (SP804)
// See https://developer.arm.com/documentation/ddi0271/d/programmer-s-model/summary-of-registers
void enableDualTimer0(unsigned int period)
{
	volatile uint32_t* DualTimer0 = (uint32_t*)DUALTIMER0BASE;
	*(DualTimer0+0x2) = 0x0;	// Disable timer
	*(DualTimer0+0x0) = period;
	*(DualTimer0+0x2) = 0xe2;	// Enable timer, periodic mode, enable interrupts, 32-bit counter
}

void DualTimer0IRQhandler(void)
{
	volatile uint32_t* DualTimer0 = (uint32_t*)DUALTIMER0BASE;
	volatile uint32_t* SysLed = (uint32_t*)SYSLEDBASE;
	*(DualTimer0+0x3) = 0x0;	// Clear timer interrupt

    // Advance the LEDs
	if (*(SysLed+0x2)!= 0x80)
		*(SysLed+0x2) = *(SysLed+0x2)<<1;
	else
		*(SysLed+0x2) = 0x1;
}
