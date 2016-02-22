/*
Rishi Bhandarkar
CS 362

Smithy Card Random Tester
Gamestate
	- The game is initiated for 2-4 players
	- A random player draws and plays the Smithy card
	
Requirements to test
	- After the player plays the Smithy card
		- Player should have 2 additional cards in their hand (Gain 3, discard Smithy)
		- Player should have 3 less cards in their deck
		- Player discard pile / Other Player piles should be unchanged
		- No change for Kingdom/Victory piles
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

int main () {
	int deckCount, remCards, handCount, state, numPlayers, curPlayer, numTests, seed, flag = 0;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	struct gameState G, prevG;

	SelectStream(2);
	PutSeed(3);

	numTests = 1000;
	for(int x = 0; x < numTests; x++){
		numPlayers = floor(Random() * (MAX_PLAYERS - 2)) + 2; //random number of players 2 to MAX_PLAYERS
		seed = floor(Random() * 2000);
		initializeGame(numPlayers, k, seed, &G);	//initialize the game
		curPlayer = floor(Random() * numPlayers);	//select current player at random
		G.whoseTurn = curPlayer;	//set current player
		
		//fill all player hands
		for(int i = 0; i < numPlayers; i++){
			handCount = floor(Random() * MAX_HAND); //random hand size 0 to MAX_HAND
			G.handCount[i] = handCount;	//set hand count value		
			for(int j = 0; j < handCount; j++){ //for each card in hand, select random card
				G.hand[i][j] = floor(Random() * (treasure_map + 1));
			}
		}
		
		//fill all player decks
		for(int i = 0; i < G.numPlayers; i++){
			remCards = MAX_DECK - G.handCount[i]; //maximum possible cards left for deck
			deckCount = floor(Random() * remCards);	//random number of cards in deck 0 to remCards
			G.deckCount[i] = deckCount; //set deck size for player i
			for(int j = 0; j < deckCount; j++) //for each card in deck, select random card
			{
				G.deck[i][j] = floor(Random() * (treasure_map + 1));
			}
		}
		
		//add smithy card to player
		gainCard(smithy, &G, 2, curPlayer);

		//preserve game state
		memcpy(&prevG, &G, sizeof(struct gameState));

		//play smithy card
		state = playCard((G.handCount[curPlayer] - 1), 0, 0, 0, &G);
		if(state != 0){
			printf("Card Play Failed\n");
		}
		
		printf("Smithy Card: Test %d\n", x+1);
	
		//Current player should have 2 more cards in their hand, 3 new cards and 1 discard
		if(prevG.handCount[curPlayer]+2 != G.handCount[curPlayer]){
			printf("TEST FAILED: Hand count error. Expected %d Actual %d\n", prevG.handCount[curPlayer]+2, G.handCount[curPlayer]);
			flag = 1;
		}
		
		//Player should have 3 fewer cards in their deck
		if(prevG.deckCount[curPlayer]-3 != G.deckCount[curPlayer]){
			printf("TEST FAILED: Deck count error. Expected %d Actual %d\n", prevG.deckCount[curPlayer]-3, G.deckCount[curPlayer]);
			flag = 1;
		}
		
		//Player's discard pile should remain unchanged
		if(prevG.discardCount[curPlayer] != G.discardCount[curPlayer]){
			printf("TEST FAILED: Smithy altered discard pile\n");
			flag = 1;
		}
		
		//Hand, deck, and discard of other players should be unchanged
		for(int i = 0; i < G.numPlayers; i++){
			if(i != curPlayer){ //for every player except current player
				//hand count unchanged
				if(prevG.handCount[i] != G.handCount[i]){
					printf("TEST FAILED: Smithy altered Player %d's hand\n", i);
					flag = 1;
				}
				//deck count unchanged
				if(prevG.deckCount[i] != G.deckCount[i]){
					printf("TEST FAILED: Smithy altered Player %d's deck\n", i);
					flag = 1;
				}
				//discard count unchanged
				if(prevG.discardCount[i] != G.discardCount[i]){
					printf("TEST FAILED: Smithy altered Player %d's discard pile\n", i);
					flag = 1;
				}
			}
		}

		//Kingdom/Victory piles unchanged
		int arraySize = sizeof(G.supplyCount) / sizeof(int);
		for(int i = 0; i < arraySize; i++){
			if(G.supplyCount[i] != prevG.supplyCount[i]){
				printf("TEST FAILED: Kingdom/Victory supplied have been altered\n");
				flag = 1;
			}
		}
	}
	
	if(flag == 0){
		printf("ALL TESTS SUCCEEDED\n");
	}

	return 0;
}
