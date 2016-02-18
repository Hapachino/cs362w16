/*
 * cardtest3.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;
	//int cardTotal = 7;
    int m, s, t;
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

	
		printf("\n---------- Test 1 - Pre state for each player, victory cards, and treasure cards: ----------\n");

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
			
			//check treasure cards
			printf("Treasure cards count: Copper = %d, Silver = %d, Gold = %d ... expected values are 46,40,30\n", testG.supplyCount[copper], testG.supplyCount[silver], testG.supplyCount[gold]);
			
			//error treasure cards
			if(testG.supplyCount[copper] != 46 || testG.supplyCount[silver] != 40 || testG.supplyCount[gold] != 30){
				printf("TEST FAILED: Treasure Card totals are incorrect. \n");
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
			
			//player 1 discard count
			printf("player 1 discard count before = %d\n", testG.discardCount[thisPlayer]);
			
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
			printf("\n\n----------Test 2 - play adventurer - add 2 treasure cards to player 1: -------------\n");
			cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

			printf("\nending cards for player 1: ");

			// tests that the two treasure cards are added to players hand
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);				
			}
			//assert(testG.handCount[thisPlayer] == cardTotal);
			
			newCards = 2;
			//test total cards
			if(testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards){
				printf("TEST FAILED: Player 1 cards gained is incorrect. \n");
			}
			
			
			printf("\n");
			
			printf("\n---------- Test 3 - Post state for each player, victory cards, and treasure cards: ----------\n");
			
			//check treasure cards
			printf("Treasure cards count: Copper = %d, Silver = %d, Gold = %d ... expected values to total 116\n", testG.supplyCount[copper], testG.supplyCount[silver], testG.supplyCount[gold]);
			
			//error treasure cards
			if((testG.supplyCount[copper] + testG.supplyCount[silver] + testG.supplyCount[gold]) != 116){
				printf("TEST FAILED: Treasure Cards totals is incorrect. \n");
			}
			
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
			
			printf("player 1 deck count after = %d\n", testG.deckCount[thisPlayer]);
			printf("player 1 discard count after = %d\n", testG.discardCount[thisPlayer]);
			
			t = 0;
			//cycle through discarded pile to confirm no treasure cards were tossed out.
			for( s = 0; s < testG.discardCount[thisPlayer]; s++){
				if(testG.discard[thisPlayer][s] == 4 || testG.discard[thisPlayer][s] == 5 || testG.discard[thisPlayer][s] == 6){
					t++;
				}
			}
			
			//error check player 1 discard pile for treasure cards
			if(t > 0){
				printf("TEST FAILED: Player 1 discard pile contains treasure %d cards. \n", t);
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