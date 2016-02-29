/*
 * unittest.h
 *
 *  Created on: Jan 21, 2016
 *      Author: jamm8888
 */

#ifndef UNITTEST_H_
#define UNITTEST_H_

struct results
{
	int lowBound;
	int highBound;
	int mixedBound;
	int testsPassed;
	int testsFailed;
	int testNum;
	int counter;
};

int random_number(int min, int max);
void printResults(int testsPassed, int testsFailed);
void printTestName(char *testName);
void initResults(struct results* result);
struct results* declResults();

#endif /* UNITTEST_H_ */
