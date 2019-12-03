//=====================================================
// Cycle Counter's Header File
//=====================================================

#ifndef CCOUNTER_H_
#define CCOUNTER_H_

#include "system.h"
#include "io.h"
#include "alt_types.h"

// Cycle counter data type
typedef struct ccounter
{
	alt_u32 timeStamp0;
	alt_u32 timeStamp1;
	alt_u32 offset;
	alt_u32 elapsed;
} ccounter_t;

// Constant definitions
#define CCOUNTER_ADR_OFS							0
#define CCOUNTER_BASE								CYCLE_COUNTER_BASE									// ***Change it based on "system.h"***
// Macros
#define CCOUNTER_setValue(data)						(IOWR(CCOUNTER_BASE, CCOUNTER_ADR_OFS, data))		// Set the cycle counter's value
#define CCOUNTER_getValue							(IORD(CCOUNTER_BASE, CCOUNTER_ADR_OFS))				// Get the cycle counter's value
#define CCOUNTER_getValueCI							(ALT_CI_CICC)										// Get the cycle counter's value via custom instruction
#define CCOUNTER_reset								(CCOUNTER_setValue(0))								// Reset the counter

// Function prototypes
ccounter_t ccounterCalibration(void);							// Cycle counter calibration
void cycleElapsed(ccounter_t *timer);							// Calculating elapsed cycles

#endif /* CCOUNTER_H_ */
