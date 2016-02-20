/*
Filename:	unittest1.c
Author:		Chris Loomis
Created:	1/27/2016
Last Mod:	1/27/2016

This is a unit test of shuffle() from dominion.c, lines 201-229.
shuffle() takes int player and struct gameState *state as arguments.
It shuffles the player's deck, forming a new deck.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
	int i;
	int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int numIdenticalCards = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, feast, tribute, smithy, council_room};
	
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing shuffle() ----------------\n\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	shuffle(0, &testG);
	
	for(i=0; i<G.deckCount[thisPlayer]-1; i++){
		if(G.deck[0][i]==testG.deck[0][i])
			printf("Card at %d are the same.\n", i);
			 numIdenticalCards++;
	}
	
	if(G.deckCount[thisPlayer] == numIdenticalCards)
		printf("\n !!! DECK IS EXACTLY THE SAME !!!\n");
	else
		printf("\ndecks are NOT identical\n");
	
	printf("\n >>>>> Test complete <<<<<\n\n");
	
	return 0;
}