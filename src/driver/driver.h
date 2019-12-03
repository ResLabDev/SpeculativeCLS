//=====================================================
// System Component Driver Header file
//	@ wraps the system related low-level driver calls
//=====================================================

#ifndef DRIVER_H_
#define DRIVER_H_

#include "ccounter.h"


//-----------------
// Cycle Counter
//-----------------
// Basic definitions
#define SYSTEM_CLOCK						50000000U		// 50 MHz system clock

// Function prototypes
float timeElapsedMilliSec(ccounter_t timer);				// Calculating elapsed time in milliseconds
float timeElapsedMicroSec(ccounter_t timer);				// Calculating elapsed time in milliseconds
float cycleToTimeMilliSec(alt_u32 cycle);					// Cycle to msec converter
float cycleToTimeMicroSec(alt_u32 cycle);					// Cycle to msec converter

#endif /* DRIVER_H_ */
