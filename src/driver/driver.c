//=====================================
// System Component Driver Functions
//=====================================

#include "driver.h"


// Calculating elapsed time in milliseconds
float timeElapsedMilliSec(ccounter_t timer)
{
	float duration;

	duration = (float)(timer.elapsed) / (SYSTEM_CLOCK / 1000);		// calculating duration in milliseconds

	return duration;
}
// Calculating elapsed time in microseconds
float timeElapsedMicroSec(ccounter_t timer)
{
	float duration;

	duration = (float)(timer.elapsed) / (SYSTEM_CLOCK / 1000000);		// calculating duration in microseconds

	return duration;
}
// Cycle to msec converter
float cycleToTimeMilliSec(alt_u32 cycle)
{
	float duration;

	duration = (float)(cycle) / (SYSTEM_CLOCK / 1000);					// calculating duration in milliseconds

	return duration;
}
// Cycle to usec converter
float cycleToTimeMicroSec(alt_u32 cycle)
{
	float duration;

	duration = (float)(cycle) / (SYSTEM_CLOCK / 1000000);				// calculating duration in microseconds

	return duration;
}
