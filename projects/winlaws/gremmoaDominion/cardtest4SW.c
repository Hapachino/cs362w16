/******************************************************************************************************
 * CS362 - Assignment 3 - Spencer Winlaw
 * cardtest4.c - unit test for Great Hall Card. 
 *
 * Basic Requirements of Great Hall
 *	- Add one card to the current player's hand
 *	- Add one action to the game state
 *	- Place card played (Great Hall) into current player's discard deck
 *  - Place card played (Great Hall) into current player's playedCards
 *	- Make no other changes to game state
 *
 *****************************************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

 #define TESTCARD "GREAT HALL"
 #define TESTCARD_VALUE great_hall

void cardtest4_helper(struct gameState* test, struct gameState* control, int currentPlayer, bool shuffledCards);

int main()
{
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
	struct gameState control, test;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state 
	initializeGame(numPlayers, k, seed, &control);
	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	
	int currentPlayer = whoseTurn(&control);

	// ----------- TEST 1: +1 action and +1 card from full player deck --------------
	printf("TEST 1: +1 action and +1 card from full player deck\n");
	
	//set currentPlayer's hand and deck
	control.hand[currentPlayer][0] = TESTCARD_VALUE;
	control.hand[currentPlayer][1] = copper;
	control.hand[currentPlayer][2] = duchy;
	control.hand[currentPlayer][3] = estate;
	control.hand[currentPlayer][4] = smithy;
	control.handCount[currentPlayer] = 5;

	control.deck[currentPlayer][0] = silver; 
	control.deck[currentPlayer][1] = gold;
	control.deck[currentPlayer][2] = mine;
	control.deckCount[currentPlayer] = 3;

	// copy the game state to a test case
	memcpy(&test, &control, sizeof(struct gameState));

	// call cardEffect to test TESTCARD functionality	
	cardEffect(TESTCARD_VALUE, choice1, choice2, choice3, &test, handpos, &bonus);

	// compare results of test with expected results
	cardtest4_helper(&test, &control, currentPlayer, false);

	// ----------- TEST 2: +1 action and +1 card from full player deck --------------
	printf("TEST 2: +1 action and +1 card from full player deck\n");
	//set currentPlayer's hand and deck
	control.hand[currentPlayer][0] = TESTCARD_VALUE;
	control.hand[currentPlayer][1] = copper;
	control.hand[currentPlayer][2] = duchy;
	control.hand[currentPlayer][3] = estate;
	control.hand[currentPlayer][4] = smithy;
	control.handCount[currentPlayer] = 5;

	control.deckCount[currentPlayer] = 0;

	control.discard[currentPlayer][0] = silver; 
	control.discard[currentPlayer][1] = gold;
	control.discard[currentPlayer][2] = mine;
	control.discardCount[currentPlayer] = 3;
	
	// copy the game state to a test case
	memcpy(&test, &control, sizeof(struct gameState));
	
	// call cardEffect to test TESTCARD functionality
	cardEffect(TESTCARD_VALUE, choice1, choice2, choice3, &test, handpos, &bonus);

	// compare results of test with expected results
	cardtest4_helper(&test, &control, currentPlayer, true);


	printf("\n >>>>> %s Testing Complete <<<<<\n\n", TESTCARD);

	return 0;
}

void cardtest4_helper(struct gameState* test, struct gameState* control, int currentPlayer, bool shuffledCards)
{
	int plusCards = 1;
    int discardedCards = 1;
    int plusActions = 1;
    int i, j;

    //Compare values of each attribute of the test gameState with an expected value
    //Almost All values should remain the same as before running test (same as control)
    //Exceptions: hand, handCount, deck, deckCount, discard, discardCount, playedCards, playedCardCount, numActions
	if(test->numPlayers != control->numPlayers)
  		printf("\tFAILED: numPlayers = %d, expected = %d\n", test->numPlayers, control->numPlayers);

  	for(i = 0; i < (treasure_map + 1); i++)
  	{
  		if(test->supplyCount[i] != control->supplyCount[i])
  			printf("\tFAILED: supplyCount[%d] = %d, expected = %d\n", i, test->supplyCount[i], control->supplyCount[i]);
  	}
  	
  	for(i = 0; i < (treasure_map + 1); i++)
  	{
  		if(test->embargoTokens[i] != control->embargoTokens[i])
  			printf("\tFAILED: embargoTokens[%d] = %d, expected = %d\n", i, test->embargoTokens[i], control->embargoTokens[i]);
  	}
  
  	if(test->outpostPlayed != control->outpostPlayed)
  		printf("\tFAILED: outpostPlayed = %d, expected = %d\n", test->outpostPlayed, control->outpostPlayed);
 
  	if(test->outpostTurn != control->outpostTurn)
  		printf("\tFAILED: outpostTurn = %d, expected = %d\n", test->outpostTurn, control->outpostTurn);
 
  	if(test->whoseTurn != control->whoseTurn)
  		printf("\tFAILED: whoseTurn = %d, expected = %d\n", test->whoseTurn, control->whoseTurn);

  	if(test->phase != control->phase)
  		printf("\tFAILED: phase = %d, expected = %d\n", test->phase, control->phase);
  
  	if(test->numActions != control->numActions + plusActions)
  		printf("\tFAILED: numActions = %d, expected = %d\n", test->numActions, control->numActions + plusActions);
  
  	if(test->coins != control->coins)
  		printf("\tFAILED: coins = %d, expected = %d\n", test->coins, control->coins);	
  
  	if(test->numBuys != control->numBuys)
  		printf("\tFAILED: numBuys = %d, expected = %d\n", test->numBuys, control->numBuys);	
  
  	for(i = 0; i < MAX_PLAYERS; i++)
  	{
  		if(i == currentPlayer)
  		{
  			if(test->handCount[currentPlayer] != control->handCount[currentPlayer] + plusCards - discardedCards)
  				printf("\tFAILED: handCount[%d] = %d, expected = %d\n", i, test->handCount[currentPlayer], control->handCount[i]);
  		
  			for(j = 0; j < test->handCount[currentPlayer]; j++)
	  		{
	  			if(j == 0 || j > test->handCount[currentPlayer] - plusCards)
	  			{
	  				if(test->hand[currentPlayer][j] != silver && test->hand[i][j] != gold && test->hand[currentPlayer][j] != mine)
	  					printf("\tFAILED: hand[%d][%d] = %d, expected = card drawn from deck (silver, gold, or mine)\n", currentPlayer, j, test->hand[i][j]);
	  			}
	  			else
	  			{
	  				if(test->hand[currentPlayer][j] != control->hand[i][j])
	  					printf("\tFAILED: hand[%d][%d] = %d, expected = %d\n", currentPlayer, j, test->hand[currentPlayer][j], control->hand[currentPlayer][j]);
	  			}
	  		}

	  		if(shuffledCards)
	  		{
	  			if(test->deckCount[currentPlayer] != (control->discardCount[currentPlayer] - (plusCards - control->deckCount[currentPlayer])))
	  				printf("\tFAILED: deckCount[%d] = %d, expected = %d\n", currentPlayer, test->deckCount[currentPlayer], (control->discardCount[currentPlayer] - (plusCards - control->deckCount[currentPlayer])));
	  			if(test->discardCount[currentPlayer] != discardedCards)
		  			printf("\tFAILED: discardCount[%d] = %d, expected = %d\n", currentPlayer, test->discardCount[currentPlayer], discardedCards);
	  		}
	  		else
	  		{
	  			if(test->deckCount[currentPlayer] != control->deckCount[currentPlayer] - plusCards)
	  				printf("\tFAILED: deckCount[%d] = %d, expected = %d\n", currentPlayer, test->deckCount[currentPlayer], control->deckCount[currentPlayer] - plusCards);
	  		
		  		for(j = 0; j < test->deckCount[currentPlayer]; j++)
		  		{
		  			if(test->deck[currentPlayer][j] != control->deck[currentPlayer][j])
		  				printf("\tFAILED: deck[%d][%d] = %d, expected = %d\n", currentPlayer, j, test->deck[currentPlayer][j], control->deck[currentPlayer][j]);
		  		}

		  		if(test->discardCount[currentPlayer] != control->discardCount[currentPlayer] + discardedCards)
		  			printf("\tFAILED: discardCount[%d] = %d, expected = %d\n", currentPlayer, test->discardCount[currentPlayer], control->discardCount[currentPlayer] + discardedCards);
		  		
		  		for(j = 0; j < test->discardCount[currentPlayer] - 1; j++)
		  		{
		  			if(test->discard[currentPlayer][j] != control->discard[currentPlayer][j])
		  				printf("\tFAILED: discard[%d][%d] (last discarded) = %d, expected = %d\n", currentPlayer, j, test->discard[currentPlayer][j], control->discard[currentPlayer][j]);
		  		}
		  	}
		  	if(test->discard[currentPlayer][test->discardCount[currentPlayer] - 1] != TESTCARD_VALUE)
		  		printf("\tFAILED: discard[%d][%d] (last discarded) = %d, expected = %d\n", currentPlayer, test->discardCount[currentPlayer] - 1, test->discard[currentPlayer][test->discardCount[currentPlayer] - 1], TESTCARD_VALUE);
  		}
  		else
  		{
	  		if(test->handCount[i] != control->handCount[i])
	  			printf("\tFAILED: handCount[%d] = %d, expected = %d\n", i, test->handCount[i], control->handCount[i]);
	  		
	  		for(j = 0; j < test->handCount[i]; j++)
	  		{
	  			if(test->hand[i][j] != control->hand[i][j])
	  				printf("\tFAILED: hand[%d][%d] = %d, expected = %d\n", i, j, test->hand[i][j], control->hand[i][j]);
	  		}

	  		if(test->deckCount[i] != control->deckCount[i])
	  			printf("\tFAILED: deckCount[%d] = %d, expected = %d\n", i, test->deckCount[i], control->deckCount[i]);
	  		
	  		for(j = 0; j < test->deckCount[i]; j++)
	  		{
	  			if(test->deck[i][j] != control->deck[i][j])
	  				printf("\tFAILED: deck[%d][%d] = %d, expected = %d\n", i, j, test->deck[i][j], control->deck[i][j]);
	  		}

	  		if(test->discardCount[i] != control->discardCount[i])
	  			printf("\tFAILED: discardCount[%d] = %d, expected = %d\n", i, test->discardCount[i], control->discardCount[i]);
	  		
	  		for(j = 0; j < test->discardCount[i]; j++)
	  		{
	  			if(test->discard[i][j] != control->discard[i][j])
	  				printf("\tFAILED: discard[%d][%d] = %d, expected = %d\n", i, j, test->discard[i][j], control->discard[i][j]);
	  		}

	  	}
  	}

  	if(test->playedCardCount != control->playedCardCount + discardedCards)
  		printf("\tFAILED: playedCardCount = %d, expected = %d\n", test->playedCardCount, control->playedCardCount);
  		
  	for(i = 0; i < test->playedCardCount - 1; i++)
  	{
  		if(test->playedCards[i] != control->playedCards[i])
  			printf("\tFAILED: playedCards[%d] = %d, expected = %d\n", i, test->playedCards[i], control->playedCards[i]);
  	}

  	if(test->playedCards[i] != TESTCARD_VALUE)
  			printf("\tFAILED: playedCards[%d] = %d, expected = %d\n", i, test->playedCards[i], TESTCARD_VALUE);
}