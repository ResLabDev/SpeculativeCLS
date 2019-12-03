//=====================================================
// Speculative Algorithm to Clipping Line Segments
//	Function Collection
//=====================================================

#include "speccls.h"

void clipped(float x1, float y1, float x2, float y2)
{
	// TBD...
}

ccounter_t clip(float x1, float y1, float x2, float y2, float xL, float yB, float xR, float yT)
{
	ccounter_t ccounter;
    float x;

    // Calibrating the cycle counter
	ccounter = ccounterCalibration();

	// Start the measurement
    CCOUNTER_reset;													// Reset the cycle counter
    ccounter.timeStamp0 = CCOUNTER_getValueCI;                       	// Get cycle counter's value via custom instruction macro
    // The speculative algorithm
    if (x1 < xL)
    {
    	if (x2 < xL)
    	{
    		// Stop and evaluate the measurement
    		ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
    		cycleElapsed(&ccounter);								// Calculating the elapsed time
    		return ccounter; 										// Return with the measured data
    	}
    }
	else if (y1 < yB)
	{
		/* p1 in bottom-left corner */
		if (y2 < yB)
		{
			// Stop and evaluate the measurement
            ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
            cycleElapsed(&ccounter);								// Calculating the elapsed time
            return ccounter; 										// Return with the measured dat
		}
        x = x1 + (x2 - x1)*(yB - y1)/(y2 - y1);
        if (x > xR)
        {
        	// Stop and evaluate the measurement
            ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
            cycleElapsed(&ccounter);								// Calculating the elapsed time
            return ccounter; 										// Return with the measured data
        }
        if (x < xL)
        {
        	y1 += (y2 - y1)*(xL - x1)/(x2 - x1);
            if (y1 > yT)
            {
            	// Stop and evaluate the measurement
                ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
                cycleElapsed(&ccounter);								// Calculating the elapsed time
                return ccounter; 										// Return with the measured data
            }
            x1 = xL;
        }
        else
        {
        	x1 = x; y1 = yB;
        }
        if (y2 > yT)
        {
        	CLIP(x1, y1, x2, y2, yT)
        }
        if (x2 > xR)
        {
        	CLIP(y1, x1, y2, x2, xR)
        }
	}
	else if (y1 > yT)
	{   /* p1 in top-left corner */
		if (y2 > yT)
		{
        	// Stop and evaluate the measurement
            ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
            cycleElapsed(&ccounter);								// Calculating the elapsed time
            return ccounter; 										// Return with the measured data
		}
        x = x1 + (x2 - x1)*(yT - y1)/(y2 - y1);
        if (x > xR)
        {
        	// Stop and evaluate the measurement
            ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
            cycleElapsed(&ccounter);								// Calculating the elapsed time
            return ccounter; 										// Return with the measured data
        }
        if (x < xL)
        {
        	y1 += (y2 - y1)*(xL - x1)/(x2 - x1);
            if (y1 < yB)
            {
            	// Stop and evaluate the measurement
                ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
                cycleElapsed(&ccounter);								// Calculating the elapsed time
                return ccounter; 										// Return with the measured data
            }
            x1 = xL;
        }
        else
        {
        	x1 = x; y1 = yT;
        }
        if (y2 < yB)
        {
        	CLIP(x1, y1, x2, y2, yB)
        }
        if (x2 > xR)
        {
        	CLIP(y1, x1, y2, x2, xR)
        }
	}
    // ??? --> the code stops here ELSE after ELSE IF
//	else
//	{
//		/* p1 in left edge region */
//		y1 += (y2 - y1)*(xL - x1)/(x2 - x1);
//        if (y1 > yT || y1 < yB)
//        {
//        	// Stop and evaluate the measurement
//            ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
//            cycleElapsed(&ccounter);								// Calculating the elapsed time
//            return ccounter; 										// Return with the measured data
//        }
//        x1 = xL;
//        RANGE(x1, y1, x2, y2, yB, yT);
//        if (x2 > xR) CLIP(y1, x1, y2, x2, xR);
//    }
    else if (x1 > xR)
    {
    	if (x2 > xR)
        {
        	// Stop and evaluate the measurement
            ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
            cycleElapsed(&ccounter);								// Calculating the elapsed time
            return ccounter; 										// Return with the measured data
        }
    }
    else if (y1 < yB)
    {
    	/* p1 in bottom-right corner */
    	if (y2 < yB)
    	{
        	// Stop and evaluate the measurement
            ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
            cycleElapsed(&ccounter);								// Calculating the elapsed time
            return ccounter; 										// Return with the measured data
    	}
    	x = x1 + (x2 - x1)*(yB - y1)/(y2 - y1);
    	if (x < xL)
    	{
        	// Stop and evaluate the measurement
            ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
            cycleElapsed(&ccounter);								// Calculating the elapsed time
            return ccounter; 										// Return with the measured data
    	}
    	if (x > xR)
    	{
    		y1 += (y2 - y1)*(xR - x1)/(x2 - x1);
    		if (y1 > yT)
    		{
            	// Stop and evaluate the measurement
                ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
                cycleElapsed(&ccounter);								// Calculating the elapsed time
                return ccounter; 										// Return with the measured data
    		}
            x1 = xR;
    	}
    	else
    	{
    		x1 = x;
    		y1 = yB;
    	}
    	if (y2 > yT)
    	{
    		CLIP(x1, y1, x2, y2, yT)
    	}
		if (x2 < xL)
		{
			CLIP(y1, x1, y2, x2, xL)
		}
    }
    else if (y1 > yT) {   /* p1 in top-right corner */
    	if (y2 > yT)
    	{
        	// Stop and evaluate the measurement
            ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
            cycleElapsed(&ccounter);								// Calculating the elapsed time
            return ccounter; 										// Return with the measured data
    	}
    	x = x1 + (x2 - x1)*(yT - y1)/(y2 - y1);
    	if (x < xL)
    	{
        	// Stop and evaluate the measurement
            ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
            cycleElapsed(&ccounter);								// Calculating the elapsed time
            return ccounter; 										// Return with the measured data
    	}
    	if (x > xR)
    	{
    		y1 += (y2 - y1)*(xR - x1)/(x2 - x1);
    		if (y1 < yB)
    		{
            	// Stop and evaluate the measurement
                ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
                cycleElapsed(&ccounter);								// Calculating the elapsed time
                return ccounter; 										// Return with the measured data
    		}
    		x1 = xR;
    	}
    	else
    	{
    		x1 = x; y1 = yT;
    	}
    	if (y2 < yB)
    	{
    		CLIP(x1, y1, x2, y2, yB)
    	}
    	if (x2 < xL)
    	{
    		CLIP(y1, x1, y2, x2, xL)
    	}
    }
    // ??? --> the code stops here ELSE after ELSE IF
//  else
// 	{
//    	/* p1 in right edge region */
//        y1 += (y2 - y1)*(xR - x1)/(x2 - x1);
//        if (y1 > yT || y1 < yB)
//        {
//        	// Stop and evaluate the measurement
//            ccounter.timeStamp1 = CCOUNTER_getValueCI;               // Get cycle counter's value via custom instruction macro
//            cycleElapsed(&ccounter);								// Calculating the elapsed time
//            return ccounter; 										// Return with the measured data
//        }
//        x1 = xR;
//        RANGE(x1, y1, x2, y2, yB, yT);
//        if (x2 < xL)
//        {
//        	CLIP(y1, x1, y2, x2, xL);
//        }
//    }
    else if (y1 < yB)
    {
    	if (y2 < yB)
    	{
        	// Stop and evaluate the measurement
            ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
            cycleElapsed(&ccounter);								// Calculating the elapsed time
            return ccounter; 										// Return with the measured data
    	}
        else
        {
        	/* p1 in bottom edge region */
            x1 += (x2 - x1)*(yB - y1)/(y2 - y1);
            if (x1 > xR || x1 < xL)
            {
            	// Stop and evaluate the measurement
                ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
                cycleElapsed(&ccounter);								// Calculating the elapsed time
                return ccounter; 										// Return with the measured data
            }
            y1 = yB;
            RANGE(y1, x1, y2, x2, xL, xR);
            if (y2 > yT)
            {
            	CLIP(x1, y1, x2, y2, yT);
            }
        }
    }
    else if (y1 > yT)
    {
    	if (y2 > yT)
    	{
        	// Stop and evaluate the measurement
            ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
            cycleElapsed(&ccounter);									// Calculating the elapsed time
            return ccounter; 										// Return with the measured data
    	}
        else
        {
        	/* p1 in top edge region */
            x1 += (x2 - x1)*(yT - y1)/(y2 - y1);
            if (x1 > xR || x1 < xL)
            {
            	// Stop and evaluate the measurement
                ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
                cycleElapsed(&ccounter);								// Calculating the elapsed time
                return ccounter; 										// Return with the measured data
            }
            y1 = yT;
            RANGE(y1, x1, y2, x2, xL, xR);
            if (y2 < yB)
            {
            	CLIP(x1, y1, x2, y2, yB);
            }
        }
    }
    else
    {
    	/* p1 is inside the window */
    	RANGE(x1, y1, x2, y2, yB, yT);
        RANGE(y1, x1, y2, x2, xL, xR);
    }
	// Stop and evaluate the measurement
    ccounter.timeStamp1 = CCOUNTER_getValueCI;                // Get cycle counter's value via custom instruction macro
    cycleElapsed(&ccounter);								// Calculating the elapsed times

    clipped(x1, y1, x2, y2);

    return ccounter; 										// Return with the measured data
}
