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
#include <assert.h>
#include "dominion_helpers.h"

#define GOLD_VALUE 3
#define SILVER_VALUE 2
#define COPPER_VALUE 1

#define HAND 0
#define DISCARD 1
#define DECK 2

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

/**
 * Function: calcCoins
 * Inputs: array of cards, array element count
 * Outputs: coin calculation
 * Description:  Calculates coins in a given hand
 */
int calcCoins(int *hand, int handCount){

	int i;
	int coinCount = 0;

	for(i=0; i < handCount; i++)
	{
		if(hand[i] == gold)
		{
			coinCount = coinCount + GOLD_VALUE;
		}
		else if(hand[i] == silver)
		{
			coinCount = coinCount + SILVER_VALUE;
		}
		else if(hand[i] == copper)
		{
			coinCount = coinCount + COPPER_VALUE;
		}
	}

	return coinCount;
}

/**
 * Function: calcCoinsCards
 * Inputs: array of cards, array element count
 * Outputs: treasure Card summation
 * Description:  Calculates treasureCards in a given hand
 */
int calcCoinCards(int *hand, int handCount){

	int i;
	int cardCount = 0;

	for(i=0; i < handCount; i++)
	{
		if(hand[i] == gold || hand[i] == silver || hand[i] == copper)
		{
			cardCount++;
		}

	}

	return cardCount;
}

/**
 * Function: updatePile
 * Inputs: player, count of elements to update, pile type to update, struct gameState
 * Outputs: None
 * Description:  updates a pile of cards to the number of elements requested in count
 */
int updatePile(int player, int count, int pile, struct gameState *state){

	int i;
	int *ptr;
	int oldCount;

	if(pile == HAND)
	{
		oldCount = state->handCount[player];
		state->handCount[player] = count;
		ptr = state->hand[player];
	}
	else if(pile == DECK)
	{
		oldCount = state->deckCount[player];
		state->deckCount[player] = count;
		ptr = state->deck[player];
	}
	else if(pile == DISCARD)
	{
		oldCount = state->discardCount[player];
		state->discardCount[player] = count;
		ptr = state->discard[player];
	}

	for(i = 0; i < count; i++){
		ptr[i] = random_number(0, treasure_map);
	}

	//clear values higher than count
	for(i = count; i < oldCount; i++){
		ptr[i] = 0;
	}

	return 0;
}

/**
 * Function: getDeckFrequencies
 * Inputs: array of cards, count of elements in array, array to hold frequencies,
 * 	count of elements in frequency array
 * Outputs: 0 on completion
 * Description:  counts the frequency of cards in a deck and stores the value in the
 * 	frequency array passed to the function.
 */
int getDeckFrequencies(int *card, int cardCount, int *cardFrequencies, int cardFreqCount){

	int i, j;
	for(i = 0; i < cardFreqCount; i++)
	{
		for(j = 0; j < cardCount; j++)
		{
			if(card[j] == i)
				cardFrequencies[i]++;
		}
	}

	return 0;
}

/**
 * Function: getCardType
 * Inputs: card
 * Outputs: type of card
 * Description:  converts a card to it's type: action, treasure, victory, dead
 */
char* getCardType(int card){
	char *cardType = (char*)malloc(20 * sizeof(char));

	// if cards is a treasure card
	if(card >= 4 && card <= 6)
		cardType = "Treasure";
	else if((card >= 1 && card <=3) || card == gardens)
		cardType = "Victory";
	else if((card >= 7 && card <=9) || (card >= 11))
		cardType = "Action";
	else if(card == great_hall)
		cardType = "Action Victory";
	else
		cardType = "Dead";

	return cardType;

}

/**
 * Function: cardCount
 * Inputs: card, pile
 * Outputs: total of card in hand
 * Description:  Calculates the frequency of a card in a hand
 */
int cardCount(int card, int *pile, int pileCount)
{
	assert(card >= 0);
	assert(pileCount >= 0);

	int i;
	int count = 0;

	for(i = 0; i < pileCount; i++)
	{
		if(pile[i] == card)
			count++;
	}

	return count;
}






