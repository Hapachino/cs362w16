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
int calcCoins(int *hand, int handCount);
int calcCoinCards(int *hand, int handCount);
int updatePile(int player, int count, int pile, struct gameState *state);
int getDeckFrequencies(int *card, int cardCount, int *cardFrequencies, int cardFreqCount);
char* getCardType(int card);
int cardCount(int card, int *pile, int pileCount);

#endif /* UNITTEST_H_ */
