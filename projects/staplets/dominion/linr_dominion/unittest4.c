/*
 * unittest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define FUNCTION "getCost()"

int main() {
    int newCards = 0;
    int shuffledCards = 0;
	int buyCount = 0;
	int total, value, i;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	const char* cardNames[] = {"curse", "estate", "duchy", "province", "copper", "silver", "gold", "adventurer",
	"council_room", "feast", "gardens", "mine", "remodel", "smithy", "village", "baron", "great_hall", "minion",
	"steward", "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
	
	int costs[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};
	printf("\n----------------- Testing Function: %s ----------------\n", FUNCTION);
	                  			
			// initialize a game state and player cards
			initializeGame(numPlayers, k, seed, &G);
	
			printf("\n---------- Test 1 - Pre state for each player, victory cards, treasure cards, and buys: ----------\n");
			
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
			
			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));
			
	
			// ----------- TEST 2: Test isGameOver function  --------------
			//call isGameOver and see results
			printf("\n\n----------Test 2 - Call getCost() tests: -------------\n");
			total = 27;
			
			for(i = 0; i < total; i++){
				value = getCost(i);
				
				printf("Card %s: getCost() returned = %d, expected = %d\n", cardNames[i], value, costs[i]);
				
				// check for correctness
				if(value != costs[i]){
				printf("\nTEST FAILED: getCost() returned incorrect value: %d \n", value);
				}
				
			}
			int market = 28;
			value = getCost(market);
				
				printf("\nTest Error code return - Card 'market': getCost() returned = %d, expected = -1\n", value);
				
				// check for correctness
				if(value != -1){
				printf("\nTEST FAILED: getCost() returned incorrect value: %d \n", value);
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
		       
    
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", FUNCTION);

	return 0;
}