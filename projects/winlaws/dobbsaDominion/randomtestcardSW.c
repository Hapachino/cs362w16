/******************************************************************************************************
 * CS362 - Assignment 4 - Spencer Winlaw
 * randomtestcard.c - random test for Smithy Card. 
 *
 * Basic Requirements of Smithy
 *  - Add three cards from current player's deck (or discard if necessary)
 *    to current player's hand
 *	- Remove card played (Smithy) from current player's hand
 *	- Place card played (Smithy) into current player's discard deck
 *  - Place card played (Smithy) into current player's playedCards
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
#include "getRandomGameState.h"

 #define TESTCARD "SMITHY"
 #define TESTCARD_VALUE smithy

void randomtestcard_helper(struct gameState* test, struct gameState* control, int currentPlayer, bool shuffledCards, int handpos);

int main()
{
    int i;
    int NUM_TESTS = 10000;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 100;
    int currentPlayer;
    bool shuffled;
    struct gameState* control;
    struct gameState* test;
    
    //set up random number generator
  	SelectStream(1);
  	PutSeed((long)seed);
  	
	printf("----------------- Testing %s Card ----------------\n", TESTCARD);
	
	for(i = 0; i < NUM_TESTS; i++)
	{
		// initialize a random game state 
		control = getRandomGameState();

		// ----------- TESTING +3 cards from player deck --------------
		printf("TEST %i: \n", i + 1);
		
		currentPlayer = whoseTurn(control);

		//set a card in currentPlayer's hand to smithy
		if(control->handCount[currentPlayer] > 0)
			handpos = rand() % control->handCount[currentPlayer];
		else 
			handpos = 0;
		control->hand[currentPlayer][handpos] = TESTCARD_VALUE;
		
		// copy the game state to a test case
		test = malloc(sizeof(struct gameState));
		memcpy(test, control, sizeof(struct gameState));

		// call cardEffect to test TESTCARD functionality	
		cardEffect(TESTCARD_VALUE, choice1, choice2, choice3, test, handpos, &bonus);

		shuffled = false;
		if(control->deckCount[currentPlayer] < 3)
		{
			shuffled = true;
		}

		// compare results of test with expected results
		randomtestcard_helper(test, control, currentPlayer, shuffled, handpos);

		free(control);
		free(test);
	}

	printf("\n >>>>> %s Testing Complete <<<<<\n\n", TESTCARD);

	return 0;
}

void randomtestcard_helper(struct gameState* test, struct gameState* control, int currentPlayer, bool shuffledCards, int handpos)
{
	int plusCards = 3;
    int discardedCards = 1;
    int i, j;
    bool failed = false;

    //Compare values of each attribute of the test gameState with an expected value
    //Almost All values should remain the same as before running test (same as control)
    //Exceptions: hand, handCount, deck, deckCount, discard, discardCount, playedCards, playedCardCount
	if(test->numPlayers != control->numPlayers)
  	{
  		printf("\tFAILED: numPlayers = %d, expected = %d\n", test->numPlayers, control->numPlayers);
  		failed = true;
  	}	

  	for(i = 0; i < (treasure_map + 1); i++)
  	{
  		if(test->supplyCount[i] != control->supplyCount[i])
  		{
  			printf("\tFAILED: supplyCount[%d] = %d, expected = %d\n", i, test->supplyCount[i], control->supplyCount[i]);
  			failed = true;
  		}
  	}
  	
  	for(i = 0; i < (treasure_map + 1); i++)
  	{
  		if(test->embargoTokens[i] != control->embargoTokens[i])
  		{
  			printf("\tFAILED: embargoTokens[%d] = %d, expected = %d\n", i, test->embargoTokens[i], control->embargoTokens[i]);
  			failed = true;
  		}
  	}
  
  	if(test->outpostPlayed != control->outpostPlayed)
  	{
  		printf("\tFAILED: outpostPlayed = %d, expected = %d\n", test->outpostPlayed, control->outpostPlayed);
 		failed = true;
 	}

  	if(test->outpostTurn != control->outpostTurn)
  	{
		printf("\tFAILED: outpostTurn = %d, expected = %d\n", test->outpostTurn, control->outpostTurn);
 		failed = true;
 	}

  	if(test->whoseTurn != control->whoseTurn)
  	{
  		printf("\tFAILED: whoseTurn = %d, expected = %d\n", test->whoseTurn, control->whoseTurn);
  		failed = true;
  	}

  	if(test->phase != control->phase)
  	{
		printf("\tFAILED: phase = %d, expected = %d\n", test->phase, control->phase);
  		failed = true;
  	}
  	
  	if(test->numActions != control->numActions)
  	{
  		printf("\tFAILED: numActions = %d, expected = %d\n", test->numActions, control->numActions);
  		failed = true;
  	}

  	if(test->coins != control->coins)
  	{
  		printf("\tFAILED: coins = %d, expected = %d\n", test->coins, control->coins);	
  		failed = true;
  	}

  	if(test->numBuys != control->numBuys)
  	{
  		printf("\tFAILED: numBuys = %d, expected = %d\n", test->numBuys, control->numBuys);	
  		failed = true;
  	}

  	for(i = 0; i < MAX_PLAYERS; i++)
  	{
  		if(i == currentPlayer)
  		{
  			if(test->handCount[currentPlayer] != (control->handCount[currentPlayer] + plusCards - discardedCards))	
  			{
  				printf("\tFAILED: handCount[%d] = %d, expected = %d\n", i, test->handCount[currentPlayer], (control->handCount[currentPlayer] + plusCards - discardedCards));
  				failed = true;
  			}

  			for(j = 0; j < test->handCount[currentPlayer]; j++)
	  		{
	  			if(j != handpos && j < test->handCount[currentPlayer] - plusCards)
	  			{
	  				if(test->hand[currentPlayer][j] != control->hand[i][j])
	  				{
	  					printf("\tFAILED: hand[%d][%d] = %d, expected = %d\n", currentPlayer, j, test->hand[currentPlayer][j], control->hand[currentPlayer][j]);
	  					failed = true;
	  				}
	  			}
	  		}

	  		if(shuffledCards)
	  		{
	  			if(test->deckCount[currentPlayer] != (control->discardCount[currentPlayer] - (plusCards - control->deckCount[currentPlayer])))
	  			{
	  				printf("\tFAILED: deckCount[%d] = %d, expected = %d\n", currentPlayer, test->deckCount[currentPlayer], (control->discardCount[currentPlayer] - (plusCards - control->deckCount[currentPlayer])));
	  				failed = true;
	  			}
	  			if(test->discardCount[currentPlayer] != discardedCards)
		  		{	
		  			printf("\tFAILED: discardCount[%d] = %d, expected = %d\n", currentPlayer, test->discardCount[currentPlayer], discardedCards);
	  				failed = true;
	  			}
	  		}
	  		else
	  		{
	  			if(test->deckCount[currentPlayer] != control->deckCount[currentPlayer] - plusCards)
	  			{
					printf("\tFAILED: deckCount[%d] = %d, expected = %d\n", currentPlayer, test->deckCount[currentPlayer], control->deckCount[currentPlayer] - plusCards);
	  				failed = true;
	  			}
		  		for(j = 0; j < test->deckCount[currentPlayer]; j++)
		  		{
		  			if(test->deck[currentPlayer][j] != control->deck[currentPlayer][j])
		  			{
		  				printf("\tFAILED: deck[%d][%d] = %d, expected = %d\n", currentPlayer, j, test->deck[currentPlayer][j], control->deck[currentPlayer][j]);
		  				failed = true;
		  			}
		  		}

		  		if(test->discardCount[currentPlayer] != control->discardCount[currentPlayer] + discardedCards)
		  		{
		  			printf("\tFAILED: discardCount[%d] = %d, expected = %d\n", currentPlayer, test->discardCount[currentPlayer], control->discardCount[currentPlayer] + discardedCards);
		  			failed = true;
		  		}
		  		for(j = 0; j < test->discardCount[currentPlayer] - 1; j++)
		  		{
		  			if(test->discard[currentPlayer][j] != control->discard[currentPlayer][j])
		  			{
		  				printf("\tFAILED: discard[%d][%d] (last discarded) = %d, expected = %d\n", currentPlayer, j, test->discard[currentPlayer][j], control->discard[currentPlayer][j]);
		  				failed = true;
		  			}
		  		}
		  	}
		  	if(test->discard[currentPlayer][test->discardCount[currentPlayer] - 1] != TESTCARD_VALUE)
		  	{
		  		printf("\tFAILED: discard[%d][%d] (last discarded) = %d, expected = %d\n", currentPlayer, test->discardCount[currentPlayer] - 1, test->discard[currentPlayer][test->discardCount[currentPlayer] - 1], TESTCARD_VALUE);
  				failed = true;
  			}
  		}
  		else
  		{
	  		if(test->handCount[i] != control->handCount[i])
	  		{
	  			printf("\tFAILED: handCount[%d] = %d, expected = %d\n", i, test->handCount[i], control->handCount[i]);
	  			failed = true;
	  		}
	  		
	  		for(j = 0; j < test->handCount[i]; j++)
	  		{
	  			if(test->hand[i][j] != control->hand[i][j])
	  			{
	  				printf("\tFAILED: hand[%d][%d] = %d, expected = %d\n", i, j, test->hand[i][j], control->hand[i][j]);
	  				failed = true;
	  			}
	  		}

	  		if(test->deckCount[i] != control->deckCount[i])
	  		{
				printf("\tFAILED: deckCount[%d] = %d, expected = %d\n", i, test->deckCount[i], control->deckCount[i]);
	  			failed = true;
	  		}
	  		
	  		for(j = 0; j < test->deckCount[i]; j++)
	  		{
	  			if(test->deck[i][j] != control->deck[i][j])
	  			{
	  				printf("\tFAILED: deck[%d][%d] = %d, expected = %d\n", i, j, test->deck[i][j], control->deck[i][j]);
	  				failed = true;
	  			}
	  		}

	  		if(test->discardCount[i] != control->discardCount[i])
	  		{
	  			printf("\tFAILED: discardCount[%d] = %d, expected = %d\n", i, test->discardCount[i], control->discardCount[i]);
	  			failed = true;
	  		}
	  		
	  		for(j = 0; j < test->discardCount[i]; j++)
	  		{
	  			if(test->discard[i][j] != control->discard[i][j])
	  			{
	  				printf("\tFAILED: discard[%d][%d] = %d, expected = %d\n", i, j, test->discard[i][j], control->discard[i][j]);
	  				failed = true;
	  			}
	  		}

	  	}
  	}

  	if(test->playedCardCount != control->playedCardCount + discardedCards)
  	{
  		printf("\tFAILED: playedCardCount = %d, expected = %d\n", test->playedCardCount, control->playedCardCount);
  		failed = true;
  	}	

  	for(i = 0; i < test->playedCardCount - 1; i++)
  	{
  		if(test->playedCards[i] != control->playedCards[i])
  		{
  			printf("\tFAILED: playedCards[%d] = %d, expected = %d\n", i, test->playedCards[i], control->playedCards[i]);
  			failed = true;
  		}
  	}

  	if(test->playedCards[i] != TESTCARD_VALUE)
  	{
  		printf("\tFAILED: playedCards[%d] = %d, expected = %d\n", i, test->playedCards[i], TESTCARD_VALUE);
  		failed = true;
  	}

  	if(!failed)
  		printf("\t SUCCESS\n");
}
