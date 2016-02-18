/*
 * unittest2.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define FUNCTION "fullDeckCount()"

int main() {
    int newCards = 0;
    int shuffledCards = 0;
	int buyCount = 0;
	int expectedGold, expectedSilver;
	int goldCount = 0, silverCount = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	printf("\n----------------- Testing Function: %s ----------------\n", FUNCTION);
	
	int p;
	for (thisPlayer = 0; thisPlayer < numPlayers; thisPlayer++){
                  			
			//check treasure cards
			printf("\n\n***Iteration %d - Player %d***\n", p, thisPlayer);
			p++;
			// initialize a game state and player cards
			initializeGame(numPlayers, k, seed, &G);
	
			printf("\n---------- Test 1 - Pre state for each player, victory cards, treasure cards, and buys: ----------\n");
			
			if(thisPlayer == 0){
				G.hand[thisPlayer][0] = smithy;
				G.hand[thisPlayer][1] = copper;
				G.hand[thisPlayer][2] = gold;
				G.hand[thisPlayer][3] = gold;
				G.hand[thisPlayer][4] = feast;
				G.deck[thisPlayer][0] = gold;
				G.discard[thisPlayer][0] = gold;
				G.discardCount[thisPlayer]++;
			}
			else{
				G.hand[thisPlayer][0] = adventurer;
				G.hand[thisPlayer][1] = feast;
				G.hand[thisPlayer][2] = remodel;
				G.hand[thisPlayer][3] = duchy;
				G.hand[thisPlayer][4] = silver;
				G.deck[thisPlayer][0] = silver;
				G.deck[thisPlayer][1] = silver;
				G.discard[thisPlayer][0] = silver;
				G.discardCount[thisPlayer]++;
			}
			
			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));
			
			//check victory cards
			printf("Victory cards count: Estate = %d, Duchy = %d, Province = %d ... expected values are 8,8,8\n", testG.supplyCount[estate], testG.supplyCount[duchy], testG.supplyCount[province]);
			
			//error victory cards
			if(testG.supplyCount[estate] != 8 || testG.supplyCount[duchy] != 8 || testG.supplyCount[province] != 8){
				printf("TEST FAILED: Victory Card totals are incorrect. \n");
			}
										
			buyCount = 1;
			//Output buys available
			printf("player %d number of buys count before = %d, expected = 1\n", thisPlayer, testG.numBuys);
			
			//error check buys
			if(testG.numBuys != buyCount){
				printf("TEST FAILED: Buys count is incorrect. \n");
			}
			
			printf("player %d deck count before = %d, expected = %d\n", thisPlayer, testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
			
			//error check player 1 deck count
			if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer]){
				printf("TEST FAILED: Player %d deck count is incorrect. \n", thisPlayer);
			}
			
			//player discard count
			printf("player %d discard count before = %d\n", thisPlayer, testG.discardCount[thisPlayer]);
			
			if(thisPlayer == 0){
				//test other player deck state
				printf("player %d deck count before = %d, expected = %d\n", thisPlayer + 1, testG.deckCount[thisPlayer + 1], G.deckCount[thisPlayer + 1]);
				
				//error check other player deck count
				if(testG.deckCount[thisPlayer + 1] != G.deckCount[thisPlayer + 1]){
					printf("TEST FAILED: Player %d deck count is incorrect. \n", thisPlayer + 1);
				}
			}
			else{
				//test other player deck state
				printf("player %d deck count before = %d, expected = %d\n", thisPlayer - 1, testG.deckCount[thisPlayer - 1], G.deckCount[thisPlayer - 1]);
				
				//error check other player deck count
				if(testG.deckCount[thisPlayer - 1] != G.deckCount[thisPlayer - 1]){
					printf("TEST FAILED: Player %d deck count is incorrect. \n", thisPlayer - 1);
				}
			}
	
			// ----------- TEST 2: Test updateCoins function  --------------
			//call updateCoins and see results
			printf("\n\n----------Test 2 - Call fullDeckCount(): -------------\n");
			
			
				goldCount = fullDeckCount(thisPlayer, gold, &testG);
				silverCount = fullDeckCount(thisPlayer, silver, &testG);
				
				if(thisPlayer == 0){
					expectedGold = 4;
					expectedSilver = 0;
					printf("gold card total = %d, expected = %d\n", goldCount, expectedGold);
					printf("silver card total = %d, expected = %d\n", silverCount, expectedSilver);
					
					// check if the number of cards is correct
					if(goldCount != expectedGold){
					printf("\nTEST FAILED: Player %d gold returned count is incorrect. \n", thisPlayer);
					}
					
					// check if the number of cards is correct
					if(silverCount != expectedSilver){
					printf("\nTEST FAILED: Player %d silver returned count is incorrect. \n", thisPlayer);
					}
				}
				else{
					expectedGold = 0;
					expectedSilver = 3;
					printf("gold card total = %d, expected = %d\n", goldCount, expectedGold);
					printf("silver card total = %d, expected = %d\n", silverCount, expectedSilver);
					
					// check if the number of cards is correct
					if(goldCount != expectedGold){
					printf("\nTEST FAILED: Player %d gold returned count is incorrect. \n", thisPlayer);
					}
					
					// check if the number of cards is correct
					if(silverCount != expectedSilver){
					printf("\nTEST FAILED: Player %d silver returned count is incorrect. \n", thisPlayer);
					}
				}
   								
							
			printf("\n---------- Test 3 - Post state for other player, treasure cards, victory cards, and buys: ----------\n");
			
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
			
			//Output buys available
			printf("player %d number of buys count after = %d, expected = 1\n", thisPlayer, testG.numBuys);
			
			buyCount = 1;
			//error check buys
			if(testG.numBuys != buyCount){
				printf("TEST FAILED: Buys count is incorrect. There should be one. \n");
			}
			
			printf("player %d deck count after = %d, expected = %d\n", thisPlayer, testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
			
			//error check player 1 deck count
			if(testG.deckCount[thisPlayer] != G.deckCount[thisPlayer]){
				printf("TEST FAILED: Player %d deck count is incorrect. \n", thisPlayer);
			}
			
			//player discard count
			printf("player %d discard count after = %d\n", thisPlayer, testG.discardCount[thisPlayer]);
			
			// tests for the appropriate number of remaining cards
			if(thisPlayer == 0){
				//test other player deck state
				printf("player %d deck count after = %d, expected = %d\n", thisPlayer + 1, testG.deckCount[thisPlayer + 1], G.deckCount[thisPlayer + 1] - newCards + shuffledCards);
				
				//error check other player deck count
				if(testG.deckCount[thisPlayer + 1] != G.deckCount[thisPlayer + 1] - newCards + shuffledCards){
					printf("TEST FAILED: Player %d deck count is incorrect. \n", thisPlayer + 1);
				}
			}
			else{
				//test other player deck state
				printf("player %d deck count after = %d, expected = %d\n", thisPlayer - 1, testG.deckCount[thisPlayer - 1], G.deckCount[thisPlayer - 1] - newCards + shuffledCards);
				
				//error check other player deck count
				if(testG.deckCount[thisPlayer - 1] != G.deckCount[thisPlayer - 1] - newCards + shuffledCards){
					printf("TEST FAILED: Player %d deck count is incorrect. \n", thisPlayer - 1);
				}
			}
		       
    }
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", FUNCTION);

	return 0;
}