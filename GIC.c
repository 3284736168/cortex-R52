//----------------------------------------------------------------
// Copyright (c) 2016-2022 Arm Limited (or its affiliates). All rights reserved.
// Use, modification and redistribution of this file is subject to your possession of a
// valid End User License Agreement for the Arm Product of which these examples are part of
// and your compliance with all applicable terms and conditions of such license agreement.
//----------------------------------------------------------------

#include "v8rgicv3cpuif.h"
#include <stdint.h>
#include "GICv3.h"

void GIC_configure(void);
void GIC_enableVirtualTimerInterrupt(void);
void GIC_enableDualTimer0Interrupt(void);

void GIC_configure(void)
{
	GICD.CTLR = 0x13;                          // Enable Group 0, Group 1 distribution and affinity routing
	while ((GICD.CTLR & 0x80000000) != 0x0);   // Poll until bit RWP is cleared
	GICR_RD.WAKER &= 0xFFFFFFFD;               // Clear ProcessorSleep
	// In Cortex-R52 SR interface is enabled by default (RAO, WI)
	//setICC_SRE(0x1);                         // Enable system register interface
	enableGroup0Ints();                        // Enable group 0 interrupts
	enableGroup1Ints();                        // Enable group 1 interrupts
	setPriorityMask(0xFF);                     // Set priority to 0xFF (lowest)
	setBinaryPoint(0x0);                       // Set Group0 binary point (preemption) to gggggggg
	setAliasedBinaryPoint(0x0);                // Set Group1 binary point (preemption) to gggggggg
}

void GIC_enableVirtualTimerInterrupt(void)
{
	GICR_SGI.IPRIORITYR[1] = 0x3F;             // Set priority SGI1
	GICR_SGI.IPRIORITYR[27] = 0x7F;            // Set priority vTimer
	GICR_SGI.IGROUPR0 = 0xFFFFFFFF;            // All SGI/PPI belong to group 1
	//GICR_SGI.IGROUPR0 = 0x0;                 // All SGI/PPI belong to group 0
	GICR_SGI.ICFGR[1] = 0x0;                   // PPI level sensitive
	//GICR_SGI.ICFGR[1] = 0xAAAAAAAA;          // PPI edge sensitive
	GICR_SGI.ISENABLER0 = 0x08000002;          // Enable vTimer (27) and SGI1
	
}

void GIC_enableDualTimer0Interrupt(void)
{
	GICD.IPRIORITYR[34] = 0x1F;                // Dual timer priority
	GICD.IGROUPR[1] = 0x4;                     // Dual timer group 1
	//GICD.ICFGR[1] = 0x0;                     // Level sensitive
	GICD.ISENABLER[1] = 0x4;                   // Dual timer interrupt enabled
	GICD.IROUTER[34] = 0x0;                    // Route IRQ to CPU0
}
