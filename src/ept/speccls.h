//=====================================================
// Speculative Algorithm to Clipping Line Segments
//	Header File
//=====================================================

#ifndef SPECCLS_H_
#define SPECCLS_H_

// Standard C libraries
#include <stdio.h>
#include <string.h>

// Cycle counter device driver
#include "../driver/driver.h"

// Constant definitions
#define TEST_RUN					10		// The number of test to be run in a single vector point
#define SEGMENT_CHAR_LENGTH			50		// The maximum length of the string to be stored in a segment

// Speculative CLS data type
typedef struct specClsData
{
    float x1;
    float y1;
    float x2;
    float y2;
    float xL;
    float yB;
    float xR;
    float yT;
    char segment[SEGMENT_CHAR_LENGTH];
} specClsData_t;

// Speculative CLS measurement result data type
typedef struct specClsResult
{
	char segment[SEGMENT_CHAR_LENGTH];		// Name of the segment
	unsigned int iteration;
	unsigned int cycleAVG;					// Average cycle
	unsigned int cycleMin;					// Minimum cycle
	unsigned int cycleMax;					// Maximum cycle
	unsigned int tolerance;					// Max-Min cycle
	float timeAVG;
} specClsResult_t;

// Macros
#define CLIP(X1, Y1, X2, Y2, YT) {               \
    X2 = X1 + (X2 - X1)*((YT - Y1)/(Y2 - Y1));   \
    Y2 = YT;                                     \
}
#define RANGE(X1, Y1, X2, Y2, YB, YT) {          \
    if (Y2 > YT) CLIP(X1, Y1, X2, Y2, YT)        \
    else if (Y2 < YB) CLIP(X1, Y1, X2, Y2, YB)   \
}

#define MIN(a, b) 				((a) > (b) ? (b) : (a))
#define MAX(a, b) 				((a) < (b) ? (b) : (a))

// Function prototypes
unsigned int getTestVectorSize(void);																// Get Test Vector length
void clipped(float x1, float y1, float x2, float y2);
ccounter_t clip(float x1, float y1, float x2, float y2, float xL, float yB, float xR, float yT);	// The Speculative CLS algorithm
void runTestBench (specClsData_t clsData, ccounter_t *ccounter_data);								// Run the testbench multiple times in single vector operating point
void runVectorMeasurement(specClsResult_t *result);													// Run the measurement based on Test Vector
void generateReport(specClsResult_t *result);														// Report generator

#endif /* SPECCLS_H_ */
