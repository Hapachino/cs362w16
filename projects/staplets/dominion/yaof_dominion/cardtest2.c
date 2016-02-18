/*
 * cardtest2.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;
	//int cardTotal = 7;
    int m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("\n----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("\n");

	// ----------- TEST 1: draw 3 cards and see how it affects the state of each player and player 1's hand  --------------

		printf("\n---------- Test 1 - Pre state for each player and victory cards: ----------\n");

			G.hand[thisPlayer][0] = smithy;
			G.hand[thisPlayer][1] = copper;
			G.hand[thisPlayer][2] = adventurer;
			G.hand[thisPlayer][3] = estate;
			G.hand[thisPlayer][4] = feast;

			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));
			
			//check victory cards
			printf("Victory cards count: Estate = %d, Duchy = %d, Province = %d ... expected values are 8,8,8\n", testG.supplyCount[estate], testG.supplyCount[duchy], testG.supplyCount[province]);
			
			//error victory cards
			if(testG.supplyCount[estate] != 8 || testG.supplyCount[duchy] != 8 || testG.supplyCount[province] != 8){
				printf("TEST FAILED: Victory Card totals are incorrect. \n");
			}
			
			//Test player 1 hand and deck count before smithy is played
			newCards = 0;
			discarded = 0;
			
			printf("player 1 hand count before = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
			
			//error check player 1 hand count
			if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded){
				printf("TEST FAILED: Player 1 hand count is incorrect. \n");
			}
			
			printf("player 1 deck count before = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
			
			//error check player 1 deck count
			if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - newCards + shuffledCards){
				printf("TEST FAILED: Player 1 deck count is incorrect. \n");
			}
			
			//test player 2 deck state
			printf("player 2 deck count before = %d, expected = %d\n", testG.deckCount[thisPlayer + 1], G.deckCount[thisPlayer + 1] - newCards + shuffledCards);
			
			//error check player 2 deck count
			if(testG.deckCount[thisPlayer + 1] != G.deckCount[thisPlayer + 1] - newCards + shuffledCards){
				printf("TEST FAILED: Player 2 deck count is incorrect. \n");
			}
			
			printf("\nstarting cards for player 1: ");
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);
			}

			printf("; ");
			
			//Play card and see results
			printf("\n\n----------Test 2 - add 3 cards to player 1: -------------\n");
			cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

			printf("\nending cards for player 1: ");

			// tests that the three cards are added to players hand
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);				
			}
			//assert(testG.handCount[thisPlayer] == cardTotal);
			
			//test total cards
			if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + 2){
				printf("TEST FAILED: Player 1 cards gained is incorrect. \n");
			}
			
			
			printf("\n");
			
			printf("\n---------- Test 3 - Post state for each player and victory cards: ----------\n");
			
			//check victory cards
			printf("Victory cards count: Estate = %d, Duchy = %d, Province = %d ... expected values are 8,8,8\n", testG.supplyCount[estate], testG.supplyCount[duchy], testG.supplyCount[province]);
			
			//error victory cards
			if(testG.supplyCount[estate] != 8 || testG.supplyCount[duchy] != 8 || testG.supplyCount[province] != 8){
				printf("TEST FAILED: Victory Card totals are incorrect. \n");
			}
			
			// tests for the appropriate number of remaining cards
			newCards = 3;
			discarded = 1;
			
			printf("player 1 hand count after = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
										
			//error check player 1 hand count
			if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded){
				printf("TEST FAILED: Player 1 hand count is incorrect. \n");
			}
			
			printf("player 1 deck count after = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards + shuffledCards);
			
			//error check player 1 deck count
			if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - newCards + shuffledCards){
				printf("TEST FAILED: Player 1 deck count is incorrect. \n");
			}
			
			newCards = 0;
			discarded = 0;
			//test player 2 deck state
			printf("player 2 deck count after = %d, expected = %d\n", testG.deckCount[thisPlayer + 1], G.deckCount[thisPlayer + 1] - newCards + shuffledCards);
			
			//error check player 2 deck count
			if(testG.deckCount[thisPlayer + 1] != G.deckCount[thisPlayer + 1] - newCards + shuffledCards){
				printf("TEST FAILED: Player 2 deck count is incorrect. \n");
			}
			//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
			//assert(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards + shuffledCards);

		
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}