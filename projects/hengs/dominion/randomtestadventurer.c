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
		printf("------Test#%d Adventurer Card--------\n", testNum);

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



	 /* 
	int theCoins;
	int secPos;
	if(coinCheck<2){
		coinPos = rand() % deckCount;
		theCoins = rand() % 3;
		testG.deck[player][coinPos] = coins[theCoins];
		secPos = rand() % deckCount;
		while(secPos == coinPos){
			secPos = rand() % deckCount;
		}
		theCoins = rand() % 3;
		testG.deck[player][secPos] = coins[theCoins];
	}
	*/
		printf("Before playing card: Current Player = %d; Deck Count = %d; Discard Count = %d; Hand Count = %d\n", player+1, testG.deckCount[player], testG.discardCount[player], testG.handCount[player]);

		printf("After Playing card Results\n");

		memcpy(&G, &testG, sizeof(struct gameState));


		cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);


		printf("Player %d hand count = %d, expected = %d\n", player+1, testG.handCount[player] - 1, G.handCount[player] + 2 - 1);


		printf("Player %d deck count = %d, expected = %d\n", player+1, testG.deckCount[player], G.deckCount[player] - (testG.discardCount[player] - G.discardCount[player] + 2));
		
		printf("Player %d discard count = %d, expected = %d\n", player+1, testG.discardCount[player], G.discardCount[player] + (G.deckCount[player] - testG.deckCount[player]) - 2);
		int coinCardsTest = 0;
		for(i=0; i < testG.handCount[player]; i++){
			if(testG.hand[player][i] == gold || testG.hand[player][i] == silver || testG.hand[player][i] == copper){
				coinCardsTest++;
			}
		}
		int coinCardsG = 0;
		for(i=0; i < G.handCount[player]; i++){
			if(G.hand[player][i] == gold || G.hand[player][i] == silver || G.hand[player][i] == copper){
				coinCardsG++;
			}
		}

		printf("Player %d hand Treasure count = %d, expected = %d\n", player+1, coinCardsTest, coinCardsG + 2);


		//HandCount
		if(testG.handCount[player] == G.handCount[player] + 2){
			printf("\n >>>>>> Success: Handcount of current player is correct!!!");
		}
		else{
			printf("\n >>>>>> Fail: Handcount of current player is incorrect!!!");
		}
		//Deck Count, might be plus 2
		if(testG.deckCount[player] == G.deckCount[player] - (testG.discardCount[player] - G.discardCount[player] + 2)){
			printf("\n >>>>>> Success: Deck count of current player is correct!!!");
		}
		else{
			printf("\n >>>>>> Fail: Deck count of current player is incorrect!!!");
		}

		//Discard count
		if(testG.discardCount[player] >= G.discardCount[player] + (G.deckCount[player] - testG.deckCount[player]) - 2){
			printf("\n >>>>>> Success: Discard count of current player is correct!!!");
		}
		else{
			printf("\n >>>>>> Fail: Discard count of current player is incorrect!!!");
		}
		//Coin Count
		
		if(coinCardsTest == coinCardsG + 2){
			printf("\n >>>>>> Success: Treasure Handcount of player is correct!!!");
		}
		else{
			printf("\n >>>>>> Fail: Treasure Handcount of player is incorrect!!!");
		}
		int totalCoins=0;
		int totalCoinsG=0;
		for(i=0; i < testG.handCount[player]; i++){
			if(testG.hand[player][i] == gold){
				totalCoins+=3;
			}
			if(testG.hand[player][i] == silver){
				totalCoins+=2;
			}
			if(testG.hand[player][i] == copper){
				totalCoins+=1;
			}
		}
		for(i=0; i < G.handCount[player]; i++){
			if(G.hand[player][i] == gold){
				totalCoinsG+=3;
			}
			if(G.hand[player][i] == silver){
				totalCoinsG+=2;
			}
			if(G.hand[player][i] == copper){
				totalCoinsG+=1;
			}
		}

		printf("\nTotal coins for After:%d, Before:%d", totalCoins, totalCoinsG);
		printf("\n >>>>> SUCCESS: Testing complete for adventurer() <<<<<\n\n");

}
	return 0;
}


