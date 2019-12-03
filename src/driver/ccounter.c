//=====================================================
// Cycle Counter's Function Collection
//=====================================================

#include "ccounter.h"

// Cycle counter calibration
ccounter_t ccounterCalibration(void)
{
	ccounter_t timer;

	CCOUNTER_reset;											// Reset the counter
	timer.timeStamp0 = CCOUNTER_getValueCI;
	timer.timeStamp1 = CCOUNTER_getValueCI;
	timer.offset = timer.timeStamp1 - timer.timeStamp0;			// Calculating offset

	return timer;
}
// Calculating the elapsed cycles
void cycleElapsed(ccounter_t *timer)
{
	timer->elapsed = timer->timeStamp1 - timer->timeStamp0 - timer->offset;
}
