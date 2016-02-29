/******************************************************************************************************
 * CS362 - Assignment 3 - Spencer Winlaw
 * cardtest1.c - unit test for Adventurer Card. 
 *
 * Basic Requirements of Adventurer
 *  - Remove cards from player's deck until 2 treasure cards have been drawn
 *	- Add those two treasure cards to current players hand
 *	- Place all other cards drawn into current player's discard deck
 *	- Place card played (Adventurer) into current player's discard deck
 *	- Make no other changes to game state
 *	- Place card played (Adventurer) into current player's discard deck
 *  - Place card played (Adventurer) into current player's playedCards
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

 #define TESTCARD "ADVENTURER"
 #define TESTCARD_VALUE adventurer

void cardtest1_helper(struct gameState* test, struct gameState* control, int currentPlayer, bool shuffledCards, int nonTreasureCardsDrawn);

int main()
{
    int i;
    int j;
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

	// ----------- TEST 1: +2 treasure cards (gold and silver) --------------
	printf("TEST 1: +2 treasure cards (gold and silver)\n");
	
	//set currentPlayer's hand and deck
	control.hand[currentPlayer][0] = TESTCARD_VALUE;
	control.handCount[currentPlayer] = 1;

	control.deck[currentPlayer][0] = copper;
	control.deck[currentPlayer][1] = silver;
	control.deck[currentPlayer][2] = gold;
	for(i = 0; i < treasure_map + 1; i++)
	{
		j = 3;
		if(i < 4 && i > 6)
		{
			control.deck[currentPlayer][j] = i;
			j++; 
		}
	}
	control.deckCount[currentPlayer] = j;

	// copy the game state to a test case
	memcpy(&test, &control, sizeof(struct gameState));

	// call cardEffect to test TESTCARD functionality	
	cardEffect(TESTCARD_VALUE, choice1, choice2, choice3, &test, handpos, &bonus);

	// compare results of test with expected results
	cardtest1_helper(&test, &control, currentPlayer, false, 24);

	// ----------- TEST 2: +2 treasure cards (copper and silver) --------------
	printf("TEST 2: +2 treasure cards (copper and silver)\n");
	control.deck[currentPlayer][0] = gold;
	control.deck[currentPlayer][1] = silver;
	control.deck[currentPlayer][2] = copper;
	
	// copy the game state to a test case
	memcpy(&test, &control, sizeof(struct gameState));
	
	// call cardEffect to test TESTCARD functionality
	cardEffect(TESTCARD_VALUE, choice1, choice2, choice3, &test, handpos, &bonus);

	// compare results of test with expected results
	cardtest1_helper(&test, &control, currentPlayer, false, 24);

	// ----------- TEST 3: +2 treasure cards (copper and gold) --------------
	printf("TEST 3: +2 treasure cards (copper and gold)\n");
	control.deck[currentPlayer][0] = silver;
	control.deck[currentPlayer][1] = gold;
	control.deck[currentPlayer][2] = copper;
	
	// copy the game state to a test case
	memcpy(&test, &control, sizeof(struct gameState));
	
	// call cardEffect to test TESTCARD functionality
	cardEffect(TESTCARD_VALUE, choice1, choice2, choice3, &test, handpos, &bonus);

	// compare results of test with expected results
	cardtest1_helper(&test, &control, currentPlayer, false, 24);

	// ----------- TEST 4: +2 treasure cards (copper and gold) --------------
	printf("TEST 4: +2 treasure cards (copper and gold) from empty deck\n");
	control.deckCount[currentPlayer] = 0;

	control.discard[currentPlayer][0] = gold;
	control.discard[currentPlayer][1] = copper;
	control.discardCount[currentPlayer] = 2;
	
	// copy the game state to a test case
	memcpy(&test, &control, sizeof(struct gameState));
	
	// call cardEffect to test TESTCARD functionality
	cardEffect(TESTCARD_VALUE, choice1, choice2, choice3, &test, handpos, &bonus);

	// compare results of test with expected results
	cardtest1_helper(&test, &control, currentPlayer, true, 0);


	printf("\n >>>>> %s Testing Complete <<<<<\n\n", TESTCARD);

	return 0;
}

void cardtest1_helper(struct gameState* test, struct gameState* control, int currentPlayer, bool shuffledCards, int nonTreasureCardsDrawn)
{
	int plusCards = 2;
    int discardedCards = 1;
    int i, j;

    //Compare values of each attribute of the test gameState with an expected value
    //Almost All values should remain the same as before running test (same as control)
    //Exceptions: hand, handCount, deck, deckCount, discard, discardCount, playedCards, playedCardCount
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
  
  	if(test->numActions != control->numActions)
  		printf("\tFAILED: numActions = %d, expected = %d\n", test->numActions, control->numActions);
  
  	if(test->coins != control->coins)
  		printf("\tFAILED: coins = %d, expected = %d\n", test->coins, control->coins);	
  
  	if(test->numBuys != control->numBuys)
  		printf("\tFAILED: numBuys = %d, expected = %d\n", test->numBuys, control->numBuys);	
  
  	for(i = 0; i < MAX_PLAYERS; i++)
  	{
  		if(i == currentPlayer)
  		{
  			if(test->handCount[currentPlayer] != (control->handCount[currentPlayer] + plusCards - discardedCards))
  				printf("\tFAILED: handCount[%d] = %d, expected = %d\n", i, test->handCount[currentPlayer], (control->handCount[currentPlayer] + plusCards - discardedCards));
  		
  			for(j = 0; j < test->handCount[currentPlayer]; j++)
	  		{
	  			if(j == 0 || j > test->handCount[currentPlayer] - plusCards)
	  			{
	  				if(test->hand[currentPlayer][j] != copper && test->hand[i][j] != silver && test->hand[currentPlayer][j] != gold)
	  					printf("\tFAILED: hand[%d][%d] = %d, expected = treasure card (copper, silver, gold)\n", currentPlayer, j, test->hand[i][j]);
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
	  			if(test->deckCount[currentPlayer] != 1)
	  				printf("\tFAILED: deckCount[%d] = %d, expected = %d\n", currentPlayer, test->deckCount[currentPlayer], 1);
	  		
		  		for(j = 0; j < test->deckCount[currentPlayer]; j++)
		  		{
		  			if(test->deck[currentPlayer][j] != control->deck[currentPlayer][j])
		  				printf("\tFAILED: deck[%d][%d] = %d, expected = %d\n", currentPlayer, j, test->deck[currentPlayer][j], control->deck[currentPlayer][j]);
		  		}

		  		if(test->discardCount[currentPlayer] != control->discardCount[currentPlayer] + nonTreasureCardsDrawn + discardedCards)
		  			printf("\tFAILED: discardCount[%d] = %d, expected = %d\n", currentPlayer, test->discardCount[currentPlayer], control->discardCount[currentPlayer] + discardedCards);
		  		
		  		for(j = 0; j < test->discardCount[currentPlayer] - 1; j++)
		  		{
		  			if(j < control->discardCount[currentPlayer])
		  			{
		  				if(test->discard[currentPlayer][j] != control->discard[currentPlayer][j])
		  					printf("\tFAILED: discard[%d][%d] = %d, expected = %d\n", currentPlayer, j, test->discard[currentPlayer][j], control->discard[currentPlayer][j]);
		  			}
		  			else
		  			{
		  				if(test->discard[currentPlayer][j] == copper || test->discard[currentPlayer][j] == silver || test->discard[currentPlayer][j] == gold)
		  					printf("\tFAILED: discard[%d][%d] (discarded during cardEffect) = %d, expected = no treasure should be discarded\n", currentPlayer, j, test->discard[currentPlayer][j]);
		  			}
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
  		printf("\tFAILED: playedCardCount = %d, expected = %d\n", test->playedCardCount, control->playedCardCount + discardedCards);
  		
  	for(i = 0; i < test->playedCardCount - 1; i++)
  	{
  		if(test->playedCards[i] != control->playedCards[i])
  			printf("\tFAILED: playedCards[%d] = %d, expected = %d\n", i, test->playedCards[i], control->playedCards[i]);
  	}

  	if(test->playedCards[i] != TESTCARD_VALUE)
  			printf("\tFAILED: playedCards[%d] = %d, expected = %d\n", i, test->playedCards[i], TESTCARD_VALUE);
}