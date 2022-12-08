/**
 * @file system_clock.c
 * @author D. Funke
 * @brief Module to initialize the system clock on the KL25Z
 * @date 2022-11-19
 * 
 */

#include "system_clock.h"

#include <MKL25Z4.h>

void system_clock_init(void)
{
    // Select PLL/FLL as clock source and select internal reference clock as source
    MCG->C1 |= (MCG_C1_CLKS(0) | MCG_C1_IREFS(1));
	
    // Select "Mid range" for DCO range and set DCO frequency of 48MHz
    MCG->C4 |= (MCG_C4_DRST_DRS(1) | MCG->C4 | MCG_C4_DMX32(1));
}
