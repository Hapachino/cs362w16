/*
Filename:	cardtest2.c
Author:		Chris Loomis
Created:	1/30/2016
Last Mod:	1/31/2016

This is a unit test of card Adventurer from dominion.c, lines 1226-1251.
When Adventurer is played, that player reveals cards until two treasure are revealed.  The two treasure go into their hand while the rest of the cards
revealed are discarded.
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
	int oldTreasure = 0;
	int newTreasure = 0;
	int seed = 50;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, feast, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing Adventurer ----------------\n\n");
	
	G.hand[0][0] = adventurer;
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	cardEffect(handCard(0, &testG), -1, -1, -1, &testG, 0, 0);
	
	//CHECK ACTIVE PLAYER HAND, DECK, AND DISCARD
	if(G.handCount[0] + 1 != testG.handCount[0]){
		printf(" !!! Active player should have 1 more card than when he started, FAILED !!!\n");
		printf(" !!! Hand should have %d cards, but has %d cards !!!\n", G.handCount[0] + 1, testG.handCount[0]);
	}
	else
		printf("Active player's hand has correct number of cards\n");
	
	if(G.discardCount[0] + 1 != testG.discardCount[0]){
		printf(" !!! Active player discard did not increment 1 card, FAILED !!!\n");
		printf(" !!! Discard should have %d cards, but has %d cards !!!\n", G.discardCount[0] + 1, testG.discardCount[0]);
	}
	else
		printf("Active player's hand has correct number of cards\n");
	
	for(i=0; i<testG.handCount[0]; i++){
		if(testG.hand[0][i] == copper || testG.hand[0][i] == silver || testG.hand[0][i] == gold)
			newTreasure++;
	}
	
	for(i=0; i<G.handCount[0]; i++){
		if(G.hand[0][i] == copper || G.hand[0][i] == silver || G.hand[0][i] == gold)
			oldTreasure++;
	}
	
	if(oldTreasure + 2 != newTreasure){
		printf(" !!! Active player does not have exactly 2 more treasure, FAILED !!!\n");
		printf(" !!! Active player should have %d treasure, but has %d treasure !!!\n", oldTreasure + 2, newTreasure);
	}
	else
		printf("Active player's hand has correct number of treasure cards\n");
	
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