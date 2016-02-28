/*
Filename:	unittest4.c
Author:		Chris Loomis
Created:	1/30/2016
Last Mod:	1/31/2016

This is a unit test of drawCard() from dominion.c, lines 525-581.
drawCard() takes int player and struct gameState *state as an argument.
It firsts checks if the discard pile needs to be shuffled to create a new deck.
A card is drawn from the deck, and placed into that player's hand
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

int main() {
	int i;
	time_t t;
	int seed = 50;
    int numPlayers = 2;
    int thisPlayer = 0;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, feast, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);
	
	printf("----------------- Testing drawCard() ----------------\n\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	drawCard(0, &testG);
	
	//CHECK PLAYER 0
	if(G.handCount[0] + 1 != testG.handCount[0]){
		printf(" !!! Active player did not draw a cards, FAILED !!!\n");
		printf(" !!! Hand should have %d cards, but has %d cards !!!\n", G.handCount[0] + 3, testG.handCount[0]);
	}
	else
		printf("Active player's hand has correct number of cards after draw\n");
	
	if(G.deckCount[0] - 1 != testG.deckCount[0]){
		printf(" !!! Active player should have same deck count, FAILED !!!\n");
		printf(" !!! Deck should have %d cards, but has %d cards !!!\n", G.deckCount[0], testG.deckCount[0]);
	}
	else
		printf("Active player's deck has correct number of cards\n");
	
	if(G.discardCount[0] != testG.discardCount[0]){
		printf(" !!! Active player discard pile not the same, FAILED !!!\n");
		printf(" !!! Discard should have %d cards, but has %d cards !!!\n", G.discardCount[0] + 1, testG.discardCount[0]);
	}
	else
		printf("Active player's hand has correct number of cards\n");
	
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

//now check that it works when deckCount is 0 and shuffle required	
	memcpy(&testG, &G, sizeof(struct gameState));
	testG.deckCount[0] = 0;
	drawCard(0, &testG);
	
	//CHECK PLAYER 0
	if(G.handCount[0] + 1 != testG.handCount[0]){
		printf(" !!! Active player did not draw a card, FAILED !!!\n");
		printf(" !!! Hand should have %d cards, but has %d cards !!!\n", G.handCount[0] + 1, testG.handCount[0]);
	}
	else
		printf("Active player's hand has correct number of cards after draw\n");
	
	if(G.deckCount[0] + 1 != testG.deckCount[0]){
		printf(" !!! Active player should have same deck count, FAILED !!!\n");
		printf(" !!! Deck should have %d cards, but has %d cards !!!\n", G.deckCount[0] + 1, testG.deckCount[0]);
	}
	else
		printf("Active player's deck has correct number of cards\n");
	
	if(G.discardCount[0] != testG.discardCount[0]){
		printf(" !!! Active player discard pile not the same, FAILED !!!\n");
		printf(" !!! Discard should have %d cards, but has %d cards !!!\n", G.discardCount[0] + 1, testG.discardCount[0]);
	}
	else
		printf("Active player's hand has correct number of cards\n");
	
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