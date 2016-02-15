#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"




int main(){
	int i, r, testcase;
	struct gameState G, testG;
	int kcards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	int player;
	int cardPos;
	int coins[3] = {gold, silver, copper};
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	srand(time(NULL));

	int seed;
	int numPlayers = 2;
	int testNum = 0;
	int coinPos;
	for(testcase = 0; testcase <1000; testcase++){
		seed = rand();
		memset(&testG, 23, sizeof(struct gameState));
		r = initializeGame(numPlayers, kcards, seed, &testG);
		testNum++;
		printf("------Test#%d Smithy Card--------\n", testNum);

		player = rand() % 2;
		
		int deckCount = floor(Random() * MAX_DECK);
		testG.deckCount[player] = deckCount;
	    int discardCount = floor(Random() * MAX_DECK);
	    testG.discardCount[player] = discardCount;
	    int handCount = floor(Random() * MAX_HAND);
	    testG.handCount[player] = handCount;
	    
	    int coinPos;
	    int j;

	   	for(j = 0; j < deckCount; j++){
	        testG.deck[player][j] = floor(Random() * 26);
	        }

	    for(j = 0; j < discardCount; j++){
	        testG.discard[player][j] = floor(Random() * 26);
	        }

	    for(j = 0; j < handCount; j++){
	        testG.hand[player][j] = floor(Random() * 26);
	        }

	    printf("Before playing card: Current Player = %d; Deck Count = %d; Discard Count = %d; Hand Count = %d\n", player+1, testG.deckCount[player], testG.discardCount[player], testG.handCount[player]);

		printf("After Playing card Results\n");

		memcpy(&G, &testG, sizeof(struct gameState));


		cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

		int newCards = 3;
		int xtraCoins = 0;
		printf("Player 1 hand count = %d, expected = %d\n", testG.handCount[player], G.handCount[player] + newCards - 1);
		printf("Player 1 deck count = %d, expected = %d\n", testG.deckCount[player], G.deckCount[player] - newCards);
		printf("Player 1 discard count = %d, expected = %d\n", testG.discardCount[player], G.discardCount[player] + 1);
		printf("Player 1 coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
		//for player 2
		
		if(testG.handCount[player] == G.handCount[player] + newCards - 1){
			printf("\n >>>>>> Success: Handcount of current player is correct!!!");
		}
		else{
			printf("\n >>>>>> Fail: Handcount of current player is incorrect!!!");
		}
		
		if(testG.deckCount[player] == G.deckCount[player] - newCards){
			printf("\n >>>>>> Success: Deck count of current player is correct!!!");
		}
		else{
			printf("\n >>>>>> Fail: Deck count of current player is incorrect!!!");
		}
		
		if(testG.discardCount[player] == G.discardCount[player] + 1){
			printf("\n >>>>>> Success: Discard count of player is correct!!!");
		}
		else{
			printf("\n >>>>>> Fail: discardCount of player is incorrect!!!");
		}
		

		printf("\n >>>>> SUCCESS: Testing complete for smithy <<<<<\n\n");
	}

	return 0;
}