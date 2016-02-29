/*
Rishi Bhandarkar
CS 362

Adventurer Card Random Tester
Gamestate
	- The game is initiated for 2-4 players
	- A random player draws and plays the Adventurer card

Requirements to test
	- After the player plays the Adventurer card	
		- Player should have gained 2 treasure cards and discarded the Adventurer card
		- Player's discard pile will have increased or stayed the same
		- Player's deck will go down by 2 or more
		- Other players will be unaffected
		- Kingdom/Victory cards will be unaffected
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

int main () {
	int deckCount, remCards, handCount, state, numPlayers, curPlayer, numTests, seed, flag = 0;
	struct gameState G, prevG;
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy}; 

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
		
		//add adventurer card to player
		gainCard(adventurer, &G, 2, curPlayer);

		//preserve game state
		memcpy(&prevG, &G, sizeof(struct gameState));

		//play adventurer card
		state = playCard((G.handCount[curPlayer] - 1), 0, 0, 0, &G);
		if(state != 0){
			printf("Card Play Failed\n");
		}
		
		printf("Adventurer Card: Test %d..\n", x+1);
		
		//curPlayer should have added 2 treasure cards and discarded Adventurer card
		if(prevG.handCount[curPlayer]+1 != G.handCount[curPlayer]){
			printf("TEST FAILED: Hand count error. Expected %d, Actual %d\n", prevG.handCount[curPlayer]+1, G.handCount[curPlayer]);
			flag = 1;
		}
		
		//First card added should by a copper, silver, or gold
		if(G.hand[curPlayer][G.handCount[curPlayer]-2] != copper && G.hand[curPlayer][G.handCount[curPlayer]-2] != silver && G.hand[curPlayer][G.handCount[curPlayer]-2] != gold){
			printf("TEST FAILED: Card type error. Added a non-treasure card\n");
			flag = 1;
		}
		
		//Second card added should be a copper, silver, or gold
		if(G.hand[curPlayer][G.handCount[curPlayer]-1] != copper && G.hand[curPlayer][G.handCount[curPlayer]-1] != silver && G.hand[curPlayer][G.handCount[curPlayer]-1] != gold){
			printf("TEST FAILED: Card type error. Added a non-treasure card\n");
			flag = 1;
		}
		
		//Deck should have at least 2 fewer cards after adventuerer is played
		if(prevG.deckCount[curPlayer]-2 < G.deckCount[curPlayer]){
			printf("TEST FAILED: Deck count error. Didn't draw enough cards from the deck\n");
			flag = 1;
		}
		
		//Hand count, deck count, and discard pile for other players should remain the same
		for(int i = 0; i < G.numPlayers; i++){
			if(i != curPlayer){ //For every player i that didn't play the adventurer card
				if(prevG.handCount[i] != G.handCount[i]){
					printf("TEST FAILED: Adventurer altered Player %d's hand\n", i+1);
					flag = 1;
				}
				if(prevG.deckCount[i] != G.deckCount[i]){
					printf("TEST FAILED: Adventurer altered Player %d's deck\n", i+1);
					flag = 1;
				}
				if(prevG.discardCount[i] != G.discardCount[i]){
					printf("TEST FAILED: Adventurer altered Player %d's discard pile\n", i+1);
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
