/*
Filename:	randomtestcard.c
Author:		Chris Loomis
Created:	2/11/2016
Last Mod:	2/13/2016

This is a random unit test of card Smithy from dominion.c, lines 1253-1265.
When Smithy is played, that player draws 3 cards.
This will test Smithy in a random, legal iteration of the game.
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
//#include "randDom.c"

int randDom(struct gameState *G);
int findNextCard(struct gameState *G, int c);

int main(int argc, char** argv) {
	/*int n,s;
	if(argc == 1){
		printf("You may enter number of times to run test as #A and RNG seed as #B in the commandline example->./randomtestcard #A #B\n");
		printf("Running once with seed 1000\n");
		n = 1;
		s = 1000;
	}
	else if(argc == 2){
		printf("You may enter RNG seed in the commandline as #B example->./randomtestcard #A #B\n");
		printf("Using seed 1000\n");
		n = argv[1];
		s = 1000;
	}
	else if(argc == 3){
		n = argv[1];
		s = argv[2];
	}
	else{
		printf("ERROR - too many command line arguments\n");
		printf("You may enter no more than number of times to run test as #A and RNG seed as #B in the commandline example->./randomtestcard #A #B\n");
		printf("Exitting\n");
		return 1;
	}
	*/
	printf("starting randomtestcard\n");
	int i,j;
	int n = 1000;
	int s = 1000;
	struct gameState G, testG;
	srand(s);
	
	for(j = 1; j <= n; j++){
		randDom(&G);
		printf("\n----------------- Testing Smithy %d ----------------\n\n",j);

		G.hand[0][0] = smithy;

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));

		cardEffect(handCard(0, &testG), -1, -1, -1, &testG, 0, 0);

		//CHECK ACTIVE PLAYER HAND, DECK, AND DISCARD
		if(G.handCount[0] + 2 != testG.handCount[0]){
			printf(" !!! Active player did not draw 3 cards, FAILED !!!\n");
			printf(" !!! Hand should have %d cards, but has %d cards !!!\n", G.handCount[0] + 2, testG.handCount[0]);
		}
		else
			printf("Active player's hand has correct number of cards\n");

		if(G.deckCount[0] - 3 != testG.deckCount[0]){
			printf(" !!! Active player should have same deck count, FAILED !!!\n");
			printf(" !!! Deck should have %d cards, but has %d cards !!!\n", G.deckCount[0] - 3, testG.deckCount[0]);
		}
		else
			printf("Active player's deck has correct number of cards\n");

		if(G.discardCount[0] + 1 != testG.discardCount[0]){
			printf(" !!! Active player discard did not increment 1 card, FAILED !!!\n");
			printf(" !!! Discard should have %d cards, but has %d cards !!!\n", G.discardCount[0] + 1, testG.discardCount[0]);
		}
		else
			printf("Active player's hand has correct number of cards\n");

		//CHECK INACTIVE PLAYER HAND, DECK, AND DISCARD (should remain same)
		for(i = 1; i < testG.numPlayers; i++){
			if(G.handCount[i] != testG.handCount[i]){
				printf(" !!! Inactive player %d has wrong number of cards in hand, FAILED !!!\n",i);
				printf(" !!! Hand should have %d cards, but has %d cards !!!\n", G.handCount[i], testG.handCount[i]);
			}
			else
				printf("Inactive player %d's hand has correct number of cards\n",i);

			if(G.deckCount[i] != testG.deckCount[i]){
				printf(" !!! Inactive player %d has wrong number of cards in deck, FAILED !!!\n",i);
				printf(" !!! Deck should have %d cards, but has %d cards !!!\n", G.deckCount[i], testG.deckCount[i]);
			}
			else
				printf("Inactive player %d's deck has correct number of cards\n",i);

			if(G.discardCount[i] != testG.discardCount[i]){
				printf(" !!! Inactive player %d discard did not increment 1 card, FAILED !!!\n",i);
				printf(" !!! Discard should have %d cards, but has %d cards !!!\n", G.discardCount[i], testG.discardCount[i]);
			}
			else
				printf("Inactive player %d's hand has correct number of cards\n",i);
		}


		printf("\n >>>>> Test %d complete <<<<<\n\n",j);
	}
	
	return 0;
}

int randDom(struct gameState *G){
	int i, j, r;
	
	G->numPlayers = rand() % 3 + 2;	//2, 3, or 4 players
	
	if (G->numPlayers == 2)
		G->supplyCount[curse] = 10;
	else if (G->numPlayers == 3)
		G->supplyCount[curse] = 20;
	else
		G->supplyCount[curse] = 30;
	
	if (G->numPlayers == 2){
		G->supplyCount[estate] = 8;
		G->supplyCount[duchy] = 8;
		G->supplyCount[province] = 8;
	}
	else{
		G->supplyCount[estate] = 12;
		G->supplyCount[duchy] = 12;
		G->supplyCount[province] = 12;
	}

	//set number of Treasure cards
	G->supplyCount[copper] = 60;
	G->supplyCount[silver] = 40;
	G->supplyCount[gold] = 30;
	
	  //set number of Kingdom cards
	for (i = adventurer; i <= treasure_map; i++){       	//loop all cards
				G->supplyCount[i] = -1;
	}
	
	G->supplyCount[adventurer] = 10;
	G->supplyCount[embargo] = 10;
	G->supplyCount[village] = 10;
	G->supplyCount[minion] = 10;
	G->supplyCount[mine] = 10;
	G->supplyCount[cutpurse] = 10;
	G->supplyCount[feast] = 10;
	G->supplyCount[tribute] = 10;
	G->supplyCount[smithy] = 10;
	G->supplyCount[council_room] = 10;
	
	//this randomizes deck and hand
	for (i = 0; i < G->numPlayers; i++){
		if(G->numPlayers == 2)
			r = (rand() % (244/2)) + 10;	//254 cards in a 2 player game and I want at least 10 cards in a deck
		else
			r = (rand() % (256/G->numPlayers)) + 10;	//266 cards in a 3 or 4 player game
		G->deckCount[i] = r;
		//printf("deckcount of %d is %d\n",i,G->deckCount[i]);
		for (j = 0; j < G->deckCount[i]; j++){
			r = rand() % (treasure_map + 1);
			if(G->supplyCount[r] < 2)
				findNextCard(G,r);
			G->deck[i][j] = r;
			G->supplyCount[r]--;
		}
				
		r = (rand() % (G->deckCount[i]/2)) + 1;		//draw hand at least 1 card, but no more than half that player's deck
		G->handCount[i] = r;
		//printf("handcount of %d is %d\n",i,G->handCount[i]);
		for(j = 0; j < G->handCount[i]; j++){
			//printf("%d draws hand\n",i);
			G->hand[i][j] = G->deck[i][G->deckCount[i]];
			G->deckCount[i]--;
			
		G->discardCount[i] = 0;
		}
		
	}
	
	
	for(i = 0; i <= treasure_map; i++)
		G->embargoTokens[i] = 0;
	
	G->outpostPlayed = 0;
	G->phase = 0;
	G->numActions = 1;
	G->numBuys = 1;
	G->playedCardCount = 0;
	G->whoseTurn = 0;
	
	updateCoins(G->whoseTurn, G, 0);

	return 0;

}

int findNextCard(struct gameState *G, int c){
	while(G->supplyCount[c] < 2){
		//printf("yep\n");
		c++;
		if(c > treasure_map)
			c = 0;
	}
	return c;
}