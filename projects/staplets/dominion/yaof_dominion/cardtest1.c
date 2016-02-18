/*
 * cardtest1.c
 *
 
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
#include <stdlib.h>

#define TESTCARD "remodel"

int main() {
    int newCards = 0;
    int discarded = 1;
    int shuffledCards = 0;
	
    int i, m, n;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	printf("\n");

		// cycle through each eligible card that's not remodel and confirm model is not removed.
		//Additionally check to make sure the gainCard is no more than 2 cost of the trashed card.
		for (i = 1; i<G.handCount[thisPlayer]; i++) {
			
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
			

			printf("\nstarting cards: ");
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);
			}
			printf("; ");

			// ----------- TEST21: choice1 tested against all cards that can be trashed  --------------
			printf("\n\n---------- Test 2 - choice1 = test against each card per iteration: ----------\n");
			printf("\nUser chooses Estate Card. \n");
			
			choice1 = i;
			choice2 = 1; //Each time we will go through and select an Estate. This keeps the gained card from being
			//more than the trashed card for the sake of testing. It will lead to a seg fault if not.
			remove1 = testG.hand[thisPlayer][i];
			cardEffect(remodel, choice1, choice2, choice3, &testG, handpos, &bonus);

			printf("\nremoved: (%d); ", remove1);
			printf("\nending cards: ");
		
			n = 0;
			// tests that the removed cards are no longer in the player's hand
			for (m=0; m<testG.handCount[thisPlayer]; m++) {
				printf("(%d)", testG.hand[thisPlayer][m]);
				//assert(testG.hand[thisPlayer][m] != remove1);
				if(testG.hand[thisPlayer][m] == remove1){
					n++;
				}
			}
			//if we have an error output it
			if( n > 0){
				printf("TEST FAILED: There was a failure calling remodel.\n");
			}
			printf("\nexpected: ");
			for (m=1; m<G.handCount[thisPlayer]; m++) {
				if (G.hand[thisPlayer][m] != G.hand[thisPlayer][i]) {
					printf("(%d)", G.hand[thisPlayer][m]);
				}
			}
			printf("\n");
			
			//TEST 3: Check to make sure the card gained is no more than 2 cost of the discarded card.
			printf("\n\n---------- Test 3 - choice2 = 1 Make sure gained card is no more than 2 the cost of the trashed: ----------\n");
			printf("Cost of card gained: (%d) \n", getCost(testG.discard[thisPlayer][0]));
			printf("Cost of card trashed: (%d) \n", getCost(G.hand[thisPlayer][i]));
			
			if ( (getCost(G.hand[thisPlayer][i]) + 2) < getCost(testG.discard[thisPlayer][0]) )
			{
				printf("TEST FAILED: The card failed to gain a card costing 2 or less.\n");
			}
			
			//post state cards counts
			printf("\n\n---------- Test 4 - Post state for each player and victory cards: ----------\n");
			
			//check victory cards
			printf("Victory cards count: Estate = %d, Duchy = %d, Province = %d ... expected values are 8,8,8\n", testG.supplyCount[estate], testG.supplyCount[duchy], testG.supplyCount[province]);
			
			//error victory cards
			if(testG.supplyCount[estate] != 7 || testG.supplyCount[duchy] != 8 || testG.supplyCount[province] != 8){
				printf("TEST FAILED: Victory Card totals are incorrect. \n");
			}
			
			// tests for the appropriate number of remaining cards
			newCards = 0;
			discarded = 2;
			
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
		}

		
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}