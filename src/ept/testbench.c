//=====================================================
// Speculative Algorithm to Clipping Line Segments
//	Testbench
//=====================================================

#include "speccls.h"

// Specify vectors for testbench
//	@ modify the test based on data requirement
const specClsData_t testVector[] =
{
//     x1   y1   x2   y2   xL   yB   xR   yT  Segment
	{  50, 250,  60, 260, 100, 100, 200, 200, "Top-left corner"						},
    {  50, 150,  60, 160, 100, 100, 200, 200, "Left-edge region" 					},
    {  50,  50,  60,  60, 100, 100, 200, 200, "Bottom-left corner"					},
    { 150, 250, 160, 260, 100, 100, 200, 200, "Top-edge region"						},
    { 150, 150, 160, 160, 100, 100, 200, 200, "Window region"						},
    { 150,  50, 160,  60, 100, 100, 200, 200, "Bottom-edge region"					},
    { 250, 250, 260, 260, 100, 100, 200, 200, "Top-right corner"					},
    { 250, 150, 260, 160, 100, 100, 200, 200, "Right-edge region"					},
    { 250,  50, 260,  60, 100, 100, 200, 200, "Bottom-right corner"					},
    {  50, 150, 110, 160, 100, 100, 200, 200, "Left-edge region, k=1, C&T wins" 	},
    {  90, 190, 110, 240, 100, 100, 200, 200, "Left-edge region, k=2, C&T loses"	}
};

// Run the testbench multiple times in single vector operating point
//	@ this validates the measurement environment as well
void runTestBench (specClsData_t clsData, ccounter_t *ccounter_data)
{
	int i;

	// Calling the clip, storing the measurement results in an array
	for (i=0; i<TEST_RUN; i++)
	{
		ccounter_data[i] = clip(clsData.x1, clsData.y1, clsData.x2, clsData.y2, clsData.xL, clsData.yB, clsData.xR, clsData.yT);
	}
}
// Get Test Vector length
unsigned int getTestVectorSize(void)
{
	return (sizeof(testVector)/sizeof(specClsData_t));
}
// Run the measurement based on Test Vector
void runVectorMeasurement(specClsResult_t *result)
{
	unsigned int i, j, cycleSum, min, max;
	unsigned int vectorLength = getTestVectorSize();			// Calculating the size of the Test Vector array
	float timeSum;
	ccounter_t ccounterData[TEST_RUN];

	for (i=0; i<vectorLength; i++)
	{
		runTestBench(testVector[i], ccounterData);											// Calculate the measured cycle in a single vector point
		// Obtain some statistics
		min = ccounterData[0].elapsed;
		max = ccounterData[0].elapsed;
		for (j=0, cycleSum=0, timeSum=0; j<TEST_RUN; j++)
		{
			cycleSum += ccounterData[j].elapsed;												// SUM
			min = MIN(ccounterData[j].elapsed, min); 											// MIN
			max = MAX(ccounterData[j].elapsed, max); 											// MAX
			timeSum += timeElapsedMicroSec(ccounterData[j]);
		}
		// Store the results
		strcpy(result[i].segment, testVector[i].segment);				// Copy the name of the segment
		result[i].iteration = TEST_RUN;
		result[i].cycleAVG = cycleSum / TEST_RUN;
		result[i].cycleMin = min;
		result[i].cycleMax = max;
		result[i].tolerance = max - min;
		result[i].timeAVG = timeSum / TEST_RUN;
	}
}
// Validation & Report generation
void generateReport(specClsResult_t *result)
{
	int i, vectorSize = getTestVectorSize();
	unsigned int totalExecution = 0;
	unsigned int cycleSumAVG = 0;
	float cycleSumPercentAVG = 0, timeSumAVG = 0;

	// Calculating report-related values
	for (i=0; i<vectorSize; i++)
	{
		totalExecution += result[i].cycleAVG;
		cycleSumAVG += result[i].cycleAVG;
		timeSumAVG += result[i].timeAVG;
	}

	printf("--- Measurement Report ----\n\n");
	printf("Vector | CycleAVG[1] | CycleAVG[%%] | TimeAVG[us] | ACC[%%] | Segment\n");
	for (i=0; i<vectorSize; i++)
	{
		cycleSumPercentAVG += ((float)result[i].cycleAVG/(float)totalExecution)*100;
		printf("   %2d.       %6u        %2.3f         %2.3f     %2.1f    %s\n", i+1, result[i].cycleAVG,
				((float)result[i].cycleAVG/(float)totalExecution)*100, result[i].timeAVG,
				((float)(result[i].cycleAVG-result[i].tolerance)/(float)result[i].cycleAVG)*100, result[i].segment);
	}
	printf("----------\n");
	printf("   Total:    %6u      %2.3f         %2.3f\n", cycleSumAVG, cycleSumPercentAVG, timeSumAVG);
	printf("   Average:  %6u                      %2.3f\n", cycleSumAVG/vectorSize, timeSumAVG/vectorSize);
	printf("   Repeated test in each single vector point: %d\n", TEST_RUN);
	printf("   System clock: %u MHz\n", SYSTEM_CLOCK/1000000);
}





