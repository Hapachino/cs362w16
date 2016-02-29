/*
Filename:	cardtest4.c
Author:		Chris Loomis
Created:	1/30/2016
Last Mod:	1/31/2016

This is a unit test of card Council Room from dominion.c, lines 1327-1347.
When Village is played, that player draws four cards, gains a buy, and all other players draw one card.
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
    int numPlayers = 3;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, feast, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing Council Room ----------------\n\n");
	
	G.hand[0][0] = council_room;
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	cardEffect(handCard(0, &testG), -1, -1, -1, &testG, 0, 0);
	
	//CHECK ACTIVE PLAYER HAND, DECK, AND DISCARD
	if(G.handCount[0] + 3 != testG.handCount[0]){
		printf(" !!! Active player should have three more cards as when he started, FAILED !!!\n");
		printf(" !!! Hand should have %d cards, but has %d cards !!!\n", G.handCount[0] + 3, testG.handCount[0]);
	}
	else
		printf("Active player's hand has correct number of cards\n");
	
	if(G.deckCount[0] - 4 != testG.deckCount[0]){
		printf(" !!! Active player has wrong number of cards in deck, FAILED !!!\n");
		printf(" !!! Deck should have %d cards, but has %d cards !!!\n", G.deckCount[0] - 4, testG.deckCount[0]);
	}
	else
		printf("Active player's deck has correct number of cards\n");
	
	if(G.discardCount[0] + 1 != testG.discardCount[0]){
		printf(" !!! Active player discard did not increment 1 card, FAILED !!!\n");
		printf(" !!! Discard should have %d cards, but has %d cards !!!\n", G.discardCount[0] + 1, testG.discardCount[0]);
	}
	else
		printf("Active player's hand has correct number of cards\n");
	
	if(G.numBuys + 1 != testG.numBuys){
		printf(" !!! Should have gained 1 more buy, FAILED !!!\n");
		printf(" !!! Should have %d buys, but has %d buys !!!\n", G.numBuys + 1, testG.numBuys);
	}
	else
		printf("Active player has correct number of buys\n");
	
	//CHECK INACTIVE PLAYERS HAND, DECK, AND DISCARD (should remain same)
	if(G.handCount[1] + 1 != testG.handCount[1]){
		printf(" !!! Inactive player 1 has wrong number of cards in hand, FAILED !!!\n");
		printf(" !!! Hand should have %d cards, but has %d cards !!!\n", G.handCount[1], testG.handCount[1]);
	}
	else
		printf("Inactive player 1 hand has correct number of cards\n");
	
	if(G.deckCount[1] - 1 != testG.deckCount[1]){
		printf(" !!! Inactive player 1 has wrong number of cards in deck, FAILED !!!\n");
		printf(" !!! Deck should have %d cards, but has %d cards !!!\n", G.deckCount[1] - 1, testG.deckCount[1]);
	}
	else
		printf("Inactive player 1 deck has correct number of cards\n");
	
	if(G.discardCount[1] != testG.discardCount[1]){
		printf(" !!! Inactive player 1 discard did not increment 1 card, FAILED !!!\n");
		printf(" !!! Discard should have %d cards, but has %d cards !!!\n", G.discardCount[1], testG.discardCount[1]);
	}
	else
		printf("Active player 1 hand has correct number of cards\n");
	
	if(G.handCount[2] + 1 != testG.handCount[2]){
		printf(" !!! Inactive player 2 has wrong number of cards in hand, FAILED !!!\n");
		printf(" !!! Hand should have %d cards, but has %d cards !!!\n", G.handCount[2], testG.handCount[2]);
	}
	else
		printf("Inactive player 2 hand has correct number of cards\n");
	
	if(G.deckCount[2] - 1 != testG.deckCount[2]){
		printf(" !!! Inactive player 2 has wrong number of cards in deck, FAILED !!!\n");
		printf(" !!! Deck should have %d cards, but has %d cards !!!\n", G.deckCount[2] - 1, testG.deckCount[2]);
	}
	else
		printf("Inactive player 2 deck has correct number of cards\n");
	
	if(G.discardCount[2] != testG.discardCount[2]){
		printf(" !!! Inactive player 2 discard did not increment 1 card, FAILED !!!\n");
		printf(" !!! Discard should have %d cards, but has %d cards !!!\n", G.discardCount[2], testG.discardCount[2]);
	}
	else
		printf("Inactive player 2 hand has correct number of cards\n");

	
	printf("\n >>>>> Test complete <<<<<\n\n");
	
	return 0;
}