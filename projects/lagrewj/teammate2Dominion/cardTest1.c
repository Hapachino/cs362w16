/*Jonathan Lagrew
 *cardtest1.c
 *test playSmithy()
 *Notes:
 *Smithy should draw 3 cards from player's own discard pile
 *and add them to player's own hand. 
 */
 /*
 * Basic Requirements of Smithy:
 * 1. Current player should receive exact 3 cards.
 * 2. 3 cards should come from his own pile.
 * 3. No state change should occur for other players.
 * 4. No state change should occur to the victory card piles and kingdom card piles.
 * 5. No changes in coins, buys or actions
 * 6. Ensure that it is still the same player's turn before and after card
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

#define DEBUG 0
#define NOISY_TEST 1
#define TESTCARD "smithy"

int testSmithy(struct gameState *after, int handPos) //test smithy function
{
	int p = after->whoseTurn;//initialize whoseTurn stored as p 
	struct gameState before;//before card played 
	memcpy(&before, after, sizeof(struct gameState));
	
	printf("Checking status before player buy...\n");
	before.handCount[p] = before.handCount[p] + 2; //plus 2 additional after smithy goes to discard
	before.playedCardCount++; //inc card count after smithy played
	playSmithy(after, p, handPos);//play smithy with after game state and current hand position
	printf("After status created\n");
	//update for assignment 5: because of found bug, test doesn't execute playSmithy so it doesn't catch that there is an error
	//this test method wasn't created to test a function that doesn't execute so I created another test below. 
	
	
	//check if the discard pile was shuffled into the deck
	//checking no state changes
	if(before.deckCount[p] < 3) //checking if discard pile shuffled 
	{
		before.deckCount[p] = before.deckCount[p] + before.discardCount[p] - 3;//if less than 3, deck plus discard minus 3
	}
	else
	{
		before.deckCount[p] = before.deckCount[p] - 3; //then draws 3 cards
	}
	if(after->handCount[p] != before.handCount[p])
	{
		printf("ERROR 1: handCount is incorrect. Expected: %d Actual: %d\n", before.handCount[p], after->handCount[p]);
	}
	if(after->deckCount[p] != before.deckCount[p])
	{
		printf("ERROR 2: deckCount is incorrect. Expected: %d Actual: %d\n", before.deckCount[p], after->deckCount[p]);
	}
	if(before.playedCardCount != after->playedCardCount)
	{
		printf("ERROR 3: playedCardCount is incorrect. Expected: %d Actual: %d\n", before.playedCardCount, after->playedCardCount);
	}
	int i;
	for(i = 0; i < treasure_map; i++)//checking supply counts before and after buy
	{
		if(before.supplyCount[i] != after->supplyCount[i])
			printf("ERROR 4: Supply counts changed. before: %i, after: %i", before.supplyCount[i], after->supplyCount[i]);
	}
	
	if(before.whoseTurn != after->whoseTurn)//if whoseTurn changed then different player
		printf("ERROR 5: Different player from %i to %i", before.whoseTurn, after->whoseTurn);
	
	//check coins
	if(before.coins != after->coins)
		printf("ERROR 6: Number of coins changed from %i to %i", before.coins, after->coins);
	//check number of buys
	if(before.numBuys != after->numBuys)
		printf("ERROR 7: Number of buys has changed from %i, to %i", before.numBuys, after->numBuys);
	//check number of actions
	if(before.numActions != after->numActions)
		printf("ERROR 8: Number of actions has changed from %i to %i", before.numActions, after->numActions);
	
	return 0;
}

//main function for testing played card 
int main()
{

	int p = 0;
	
	struct gameState G;//generates game state G filled with random bytes
	int handPos;
	int i, j, k, m, n, q;//initializing int 
	
	for (i = 0; i < sizeof(struct gameState); i++) {//random gameState
		((char*)&G)[i] = floor(Random() * 256);
	}
	//starting random tests
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	
	SelectStream(2);
	PutSeed(3);
	
	G.whoseTurn = p;//gameState G's player's turn stored in value p
	
	for(k = 0; k < 250; k++) //250 number of tests
	{
		//from lecture 11 
		G.handCount[p] = floor(Random() * MAX_HAND)+1;//fill random hand with one smithy
		
		G.deckCount[p] = floor(Random() * MAX_DECK);//fill random deck
		
		G.discardCount[p] = floor(Random() * MAX_DECK);//fill random discard pile
		
		G.playedCardCount = floor(Random() * MAX_DECK);//fill random played card pile
		
		 
		for(m = 0; m < G.handCount[p]; m++)
		{
			G.hand[p][m] = floor(Random() * treasure_map) + 1;
		}
		
		for(j = 0; j < G.discardCount[p]; j++)
		{
			G.discard[p][j] = floor(Random() * treasure_map) + 1;
		}

		for(n = 0; n < G.deckCount[p]; n++)
		{
			G.deck[p][n] = floor(Random() * treasure_map) + 1;
		}
		for(q = 0; q < G.playedCardCount; q++)
		{
			G.playedCards[q] = floor(Random() * treasure_map) + 1;
		}
		handPos = floor(Random() * G.handCount[p]);//putting smithy in random hand position
		G.hand[p][handPos] = smithy;//play smithy
		testSmithy(&G, handPos);//running test smithy function 
		
		//********************************************************
		//*********************************************************
		//second test
		
		//initializing variables
		int i;
		int seed = 65535;
		int numPlayer = 2;
		int thisPlayer;
		int index=0;
		int allTestsPassed = 0; 
		int smithyFail = 0;
		int k[10] = {adventurer, smithy, great_hall, council_room, salvager, gardens, mine, remodel, village, ambassador };

		// Checking for victory conditions:
		int victoryPoints;
		int points[13];

		struct gameState state, testState;//creating new game state called testState
		//int count;

		//clearing for new gameState
		memset(&state, 0, sizeof(struct gameState));
		initializeGame(numPlayer, k, seed, &testState);

		memcpy(&state, &testState, sizeof(struct gameState));
		printf("\n\n 2nd testcard1.c test for Smithy\n");
	    printf("Begin Testing Smithy Again!\n");

		//VP tests 
		victoryPoints = testState.supplyCount[estate];
		points[index] = victoryPoints;
		index++;
		assert(victoryPoints == 8);
		victoryPoints = testState.supplyCount[duchy] * 3;
		points[index] = victoryPoints;
		index++;
		assert(victoryPoints == 24);
		victoryPoints = testState.supplyCount[province] * 6;
		points[index] = victoryPoints;
		index++;
		assert(victoryPoints == 48);

		//Test 1 : putting card in hand
		thisPlayer=0;
		printf("Player 1 Test -- Draw Smithy in hand\n");
		testState.hand[thisPlayer][testState.handCount[thisPlayer]] = smithy;
		testState.handCount[thisPlayer]++;
		if(state.handCount[thisPlayer] + 1 == testState.handCount[thisPlayer])
		{
			printf("Test 1 Passed -- card in player's hand.\n");
		}
		else
		{
			printf("Test 1 Failed -- Unable to put Smithy in player's hand. Aborting.\n\n");
			allTestsPassed = 0;//set flag to 0 on fail
			exit(0);
		}

		//Test 2: Checking discard count
		for(i=0; i < testState.deckCount[thisPlayer]; i++)
		{
			printf("Position %d, Card: %d\n", i, testState.deck[thisPlayer][i]);
		}
		printf("DECK COUNTED\n");
		printf("DISCARD COUNT -- SHOULD BE 0\n");
		if(testState.discardCount[thisPlayer] == 0)
		{
			printf("Test 2 Passed -- Discard Successful. Count successful.\n");
		}
		else
		{
			printf("Test 2 failed -- Discard Count Unsuccessful.\n");
			allTestsPassed = 0;//set flag to 0 on fail
		}

		//Test 3: ensure smithy card is in hand
		int handCountExpect[] = { 1, 4, 1, 4, 1, 13 };//enum 13 is smithy
		assert(testState.hand[thisPlayer][5] == smithy);
		for(i=0; i < testState.handCount[thisPlayer]; i++)
		{
			printf("Position %d, card: %d\n", i, testState.hand[thisPlayer][i]);
			if(handCountExpect[i] != testState.hand[thisPlayer][i]);
			{
				allTestsPassed=0;//if fail, set to 0. 
			}
		}
		
		//Recreating adding 3 plus cards to deck 
		testState.deck[thisPlayer][testState.deckCount[thisPlayer] ] = gardens; //enum=10
		testState.deckCount[thisPlayer]++;
		testState.deck[thisPlayer][testState.deckCount[thisPlayer] ] = salvager; //enum=24
		testState.deckCount[thisPlayer]++;
		testState.deck[thisPlayer][testState.deckCount[thisPlayer] ] = ambassador; //enum=20
		testState.deckCount[thisPlayer]++;

		//Test 4: Add the 3 new cards to hand
		printf("Smithy Granted Hand Count: %d\n", testState.handCount[thisPlayer]);
		printf("Before Smithy in Hand, Hand Count: %d\n", state.handCount[thisPlayer]);
		
		playSmithy(&testState, thisPlayer, 0);

		if(testState.handCount[thisPlayer] == state.handCount[thisPlayer] + 4)
		{
			printf("Test 4 passed: Smithy added 3 cards successfully. Test Passed.\n");
		}
		else
		{
			printf("Test 4 Failed: Smithy did not add expected number of cards to hand.\n");
			printf("Expected Hand Count: %d\n", state.handCount[thisPlayer] + 4);
			printf("Actual Result: %d\n", testState.handCount[thisPlayer]);
			allTestsPassed = 0;//set flag to 0 on fail
			smithyFail = 1;
		}

		//Test 5: Testing Discard function
		printf("Testing Card Discard.\n");
		for(i=0; i < testState.discardCount[thisPlayer]; i++)
		{
			printf("Discard Card: %d\n", testState.discard[thisPlayer][i]);
		}

		if(testState.deckCount[thisPlayer] == state.deckCount[thisPlayer]) // Should be even again.
		{
			printf("Test 5 passed -- Discard test and check passed.\n");
		}
		else
		{
			printf("Test 5 failed: Discard test and check failed.\n");
			allTestsPassed=0;//set flag to 0 on fail
		}

		//Test 6: testing seed state
		printf("Checking expected seed state.\n");

		int seedDeckExpect[] = { 4, 4, 4, 4, 4 };
		for(i=0; i < testState.deckCount[thisPlayer]; i++)
		{
			printf("Position %d Deck Card: %d\n", i, testState.deck[thisPlayer][i]);
		   if(seedDeckExpect[i] != testState.deck[thisPlayer][i]) allTestsPassed=0;
		}

		if(allTestsPassed) printf("Test 6 -- Seed Deck Test Passed. State is not corrupted.\n");
		else printf("Test 6 failed. Check code or change seed.\n");

		//Test 7: check hand and seed state
		printf("Checking hand and seed state.\n");

		int seedHandExpect[] = {10, 4, 1, 4, 1, 13, 20, 24};
		int seedNameExpect[] = { gardens, copper, estate, copper, estate, smithy, ambassador, salvager };
		for(i=0; i < testState.handCount[thisPlayer]; i++)
		{
			if(seedHandExpect[i] != testState.hand[thisPlayer][i])
			{
				allTestsPassed = 0;//set flag to 0 on fail
			}
			if(seedHandExpect[i] != seedNameExpect[i])
			{
				allTestsPassed = 0;//set flag to 0 on fail
			}
		}

	    printf("Player 1 Test Completed.\n");
		printf("------------------------\n");

		//starting test for player 1 to make sure in game state that the smithy card played doesn't affect other player's turn.
		thisPlayer = 1;
		printf("\nPlayer 2 Tests ----- \n\n");
		int copperCount = 0;
		int estateCount = 0;
		printf("DECK RECOUNT\n");
		for(i = 0; i < testState.deckCount[thisPlayer]; i++)
		{
			printf("Position %d, Card: %d\n", i, testState.deck[thisPlayer][i]);
			if(testState.deck[thisPlayer][i] == copper)
			{
				copperCount++;
			}
			if(testState.deck[thisPlayer][i] == estate)
			{
				estateCount++;
			}
		}
		if(copperCount != 7)
		{
        printf("Improper copper amount. Should be 7. Result: %d\n", copperCount);
        allTestsPassed = 0;//set flag to 0 on fail
		}
		if(estateCount != 3)
		{
        printf("Improper estate amount. Should be 3. Result: %d\n", estateCount);
        allTestsPassed = 0;//set flag to 0 on fail
		}
		printf("Player has 10 card count Test.\n");

		if(testState.deckCount[thisPlayer] == 10)
		{
        printf("Player has proper number of cards.\n");
		}
		else
		{
        printf("Player has improper number of cards. Should have 10.\nPlayer Has: %d\n", testState.deckCount[thisPlayer]);
        allTestsPassed = 0;//set flag to 0 on fail
		}

		testState.hand[thisPlayer][testState.handCount[thisPlayer]] = smithy;
		testState.handCount[thisPlayer]++;
		if(state.handCount[thisPlayer] + 1 == testState.handCount[thisPlayer])
		{
        printf("Smithy properly granted to player and player card count incremented.\n");
		}
		else
		{
        printf("Smithy was either improperly granted or card count not incremented.\n");
        allTestsPassed=0;
		}
		assert(testState.supplyCount[estate] == 8);
		assert(testState.supplyCount[estate] == 8);
		assert(testState.supplyCount[estate] == 8);
		assert(points[0] == 8);
		assert(points[1] == 24);
		assert(points[2] == 48);

		
		//Test summary
		printf("\n\n------------------------\n");
		printf("Smithy Test Summary\n");
		printf("------------------------\n");
		if(allTestsPassed) printf("No state changes, all tests passed.\n\n");
		else printf("One or more tests failed. playSmithy function has errors.\n");
		if(smithyFail)
		{
        printf("Smithy card did not work properly.\n");
        printf("Smithy gave: %d\n", testState.handCount[0]);
        printf("Expected: %d\n", state.handCount[0] + 4);
		printf("End of Smithy test\n");
		}	
		return 0;
	}
	
	printf("Play Smithy Tests are concluded.\n\n");
	
	return 0;
}