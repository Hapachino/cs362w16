/*
 * unittest.c
 *
 *  Created on: Jan 21, 2016
 *      Author: jamm8888
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct results
{
	int lowBound;
	int highBound;
	int mixedBound;
	int testsPassed;
	int testsFailed;
	int testNum;
	int counter;
	int goldCount;

};

void initResults(struct results* result)
{
  result->lowBound = 0;
  result->highBound = 0;
  result->mixedBound = 0;
  result->testsPassed = 0;
  result->testsFailed = 0;
  result->testNum = 0;
  result->counter = 0;
}

struct results* declResults() {
  struct results* result = malloc(sizeof(struct results));
  initResults(result);
  return result;
}

/**
 * generates a random number within a range to be returned
 * Preconditions: min and max are integers and min is less than max
 * PostConditions:  random number returned or -1 on error
 */
int random_number(int min, int max)
{

	/**
	 * Require min to be greater than max
	 */
	if(min < max)
	{

			double randNum, randSeed, rangeVal;

			// get the range for the random number
			rangeVal = max - min + 1;
			randSeed = rand();
			randSeed = randSeed / RAND_MAX;
			randNum = floor(randSeed * rangeVal) + min;

			return (int) randNum;
	}

	return 0;
}

/**
 * Function: printResults
 * inputs:  testsPassed, testsFailed
 * Prints out test metrics for pass / fail criteria
 */
void printResults(int testsPassed, int testsFailed){

	int totalTests = testsPassed + testsFailed;
	float testPercent = 100 * testsPassed/totalTests;
	printf("Number of tests Passed: %d\n", testsPassed);
	printf("Number of tests Failed: %d\n", testsFailed);
	printf("Percentage of tests Passed: %.2f %% \n", testPercent);

}

/**
 * Function: printTest
 * inputs:  testName
 * Prints out test metrics for pass / fail criteria
 */
void printTestName(char *testName){

	printf("Starting Test for: %s\n", testName);

}




