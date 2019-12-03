//====================================================
// Performance tester for
// "A Speculative Approach to Clipping Line Segments"
//====================================================

#define TEST_FP

// Measurement library
#include "ept/speccls.h"

// Altera specific library
#include "sys/alt_irq.h"

#ifdef TEST_FP
void testOperation(void);
void testSpeculative(void);
#endif

int main()
{
	specClsResult_t resultVector[getTestVectorSize()];
	alt_irq_context context;

	#ifdef TEST_FP
		testOperation();
		testSpeculative();
	#endif

	printf("\n\n================================\n");
	printf("| Execution Performance Tester |\n");
	printf("===============================\n\n");

	//---Measurement Environment---
	context = alt_irq_disable_all();

	// Run the measurement based on the Test Vector constants
	runVectorMeasurement(resultVector);

	alt_irq_enable_all(context);
	//---Measurement Environment---

	// Report and validation
	generateReport(resultVector);

	return 0;
}

#ifdef TEST_FP
// Basic operation test
void testOperation(void)
{
	ccounter_t counterTest;
	float a = 47.81, b = 12.13, c;

	counterTest = ccounterCalibration();
	printf("Calibration: %d cycles\n", (int)counterTest.offset);

	// a+b
	CCOUNTER_reset;
	counterTest.timeStamp0 = CCOUNTER_getValueCI;
	c=a+b;
	counterTest.timeStamp1 = CCOUNTER_getValueCI;
	printf("Result of %4.3f + %4.3f = %4.3f: %d cycles\n", a, b, c, (int)(counterTest.timeStamp1-counterTest.timeStamp0-counterTest.offset));

	//a-b
	CCOUNTER_reset;
	counterTest.timeStamp0 = CCOUNTER_getValueCI;
	c=a-b;
	counterTest.timeStamp1 = CCOUNTER_getValueCI;
	printf("Result of %4.3f - %4.3f = %4.3f: %d cycles\n", a, b, c, (int)(counterTest.timeStamp1-counterTest.timeStamp0-counterTest.offset));

	//a*b
	CCOUNTER_reset;
	counterTest.timeStamp0 = CCOUNTER_getValueCI;
	c=a*b;
	counterTest.timeStamp1 = CCOUNTER_getValueCI;
	printf("Result of %4.3f * %4.3f = %4.3f: %d cycles\n", a, b, c, (int)(counterTest.timeStamp1-counterTest.timeStamp0-counterTest.offset));

	//a/b
	CCOUNTER_reset;
	counterTest.timeStamp0 = CCOUNTER_getValueCI;
	c=a/b;
	counterTest.timeStamp1 = CCOUNTER_getValueCI;
	printf("Result of %4.3f / %4.3f = %4.3f: %d cycles\n", a, b, c, (int)(counterTest.timeStamp1-counterTest.timeStamp0-counterTest.offset));

	//a<b
	CCOUNTER_reset;
	counterTest.timeStamp0 = CCOUNTER_getValueCI;
	c = (a<b) ? 66.6 : 33.3;
	counterTest.timeStamp1 = CCOUNTER_getValueCI;
	printf("Result of (%4.3f < %4.3f) => %4.3f: %d cycles\n", a, b, c, (int)(counterTest.timeStamp1-counterTest.timeStamp0-counterTest.offset));
}

void testSpeculative(void)
{
	float x1=200, y1=50, x2=150, y2=50, xL=250, yB=50, xR=50, yT=50;
	ccounter_t counterTest;

	counterTest = clip(x1, y1, x2, y2, xL, yB, xR, yT);
	printf("Speculative result: %d cycles\n\n", (int)counterTest.elapsed);

}
#endif
