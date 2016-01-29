/*
 * unittest1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define FUNCTION "update_coins"

int main() {
    int newCards = 0;
    int shuffledCards = 0;
	int buyCount = 0;
	int maxBonus = 10;
    int handCount;
    int bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	int i;
	int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
	
	printf("\n----------------- Testing Function: %s ----------------\n", FUNCTION);
	printf("\n");
	
	int p;
	for (thisPlayer = 0; thisPlayer < numPlayers; thisPlayer++){
        for (handCount = 0; handCount <= maxHandCount; handCount++){
            for (bonus = 0; bonus <= maxBonus; bonus++){
			
			//check treasure cards
			printf("\n\n***Iteration %d - Player %d - Treasure cards count: %d and bonus: %d***\n", p, thisPlayer, handCount, bonus);
			p++;
			// initialize a game state and player cards
			initializeGame(numPlayers, k, seed, &G);
	
			printf("\n---------- Test 1 - Pre state for each player, victory cards, treasure cards, and buys: ----------\n");
			
			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));
			
			// set the number of cards on hand
			testG.handCount[thisPlayer] = handCount;                 
			// set all the cards to copper
            memcpy(testG.hand[thisPlayer], coppers, sizeof(int) * handCount); 
					
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
			printf("\n\n----------Test 2 - Call Update Coins: -------------\n");
			
				updateCoins(thisPlayer, &testG, bonus);

                printf("coin total = %d, expected = %d\n", testG.coins, handCount * 1 + bonus);

				// check if the number of coins is correct
                if(testG.coins != handCount * 1 + bonus){
					printf("\nTEST FAILED: Player %d copper coin count is incorrect. \n", thisPlayer);
				}

				// set all the cards to silver
                memcpy(testG.hand[thisPlayer], silvers, sizeof(int) * handCount); 
                updateCoins(thisPlayer, &testG, bonus);

                printf("coin total = %d, expected = %d\n", testG.coins, handCount * 2 + bonus);

                // check if the number of coins is correct
                if(testG.coins != handCount * 2 + bonus){
					printf("\nTEST FAILED: Player %d silver coin count is incorrect. \n", thisPlayer);
				}

                memcpy(testG.hand[thisPlayer], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(thisPlayer, &testG, bonus);

                printf("coin total = %d, expected = %d\n", testG.coins, handCount * 3 + bonus);

                // check if the number of coins is correct
                if(testG.coins != handCount * 3 + bonus){
					printf("TEST FAILED: Player %d gold coin count is incorrect. \n", thisPlayer);
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
        }
    }
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", FUNCTION);

	return 0;
}