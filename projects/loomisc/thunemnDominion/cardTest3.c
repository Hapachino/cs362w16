/*
Filename:	cardtest3.c
Author:		Chris Loomis
Created:	1/30/2016
Last Mod:	1/30/2016

This is a unit test of card Village from dominion.c, lines 1267-1278.
When Village is played, that player draws one card and receives two more actions.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
	int seed = 50;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, feast, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing Village ----------------\n\n");
	
	G.hand[0][0] = village;
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	cardEffect(handCard(0, &testG), -1, -1, -1, &testG, 0, 0);
	
	//CHECK ACTIVE PLAYER HAND, DECK, AND DISCARD
	if(G.handCount[0] != testG.handCount[0]){
		printf(" !!! Active player should have same number of cards as when he started, FAILED !!!\n");
		printf(" !!! Hand should have %d cards, but has %d cards !!!\n", G.handCount[0], testG.handCount[0]);
	}
	else
		printf("Active player's hand has correct number of cards\n");
	
	if(G.deckCount[0] - 1 != testG.deckCount[0]){
		printf(" !!! Active player has wrong number of cards in deck, FAILED !!!\n");
		printf(" !!! Deck should have %d cards, but has %d cards !!!\n", G.deckCount[0], testG.deckCount[0]);
	}
	else
		printf("Active player's deck has correct number of cards\n");
	
	if(G.discardCount[0] + 1 != testG.discardCount[0]){
		printf(" !!! Active player discard did not increment 1 card, FAILED !!!\n");
		printf(" !!! Discard should have %d cards, but has %d cards !!!\n", G.discardCount[0] + 1, testG.discardCount[0]);
	}
	else
		printf("Active player's hand has correct number of cards\n");
	
	if(G.numActions + 2 != testG.numActions){
		printf(" !!! Should have gained 2 more actions, FAILED !!!\n");
		printf(" !!! Should have %d actions, but has %d actions !!!\n", G.numActions + 2, testG.numActions);
	}
	else
		printf("Active player has correct number of actions\n");
	
	//CHECK INACTIVE PLAYER HAND, DECK, AND DISCARD (should remain same)
	if(G.handCount[1] != testG.handCount[1]){
		printf(" !!! Inactive player has wrong number of cards in hand, FAILED !!!\n");
		printf(" !!! Hand should have %d cards, but has %d cards !!!\n", G.handCount[1], testG.handCount[1]);
	}
	else
		printf("Inactive player's hand has correct number of cards\n");
	
	if(G.deckCount[1] != testG.deckCount[1]){
		printf(" !!! Inactive player has wrong number of cards in deck, FAILED !!!\n");
		printf(" !!! Deck should have %d cards, but has %d cards !!!\n", G.deckCount[1], testG.deckCount[1]);
	}
	else
		printf("Inactive player's deck has correct number of cards\n");
	
	if(G.discardCount[1] != testG.discardCount[1]){
		printf(" !!! Inactive player discard did not increment 1 card, FAILED !!!\n");
		printf(" !!! Discard should have %d cards, but has %d cards !!!\n", G.discardCount[1], testG.discardCount[1]);
	}
	else
		printf("Inactive player's hand has correct number of cards\n");

	
	printf("\n >>>>> Test complete <<<<<\n\n");
	
	return 0;
}