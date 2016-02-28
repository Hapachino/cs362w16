/* -----------------------------------------------------------------------
 * Testing drawCard()
 * Pre conditions
 *  1) Passes in player number and gameState 
 * Post conditions
 *  1) players hand is increased by 1
 *  2) players deck is decreased by 1
 *  3) players discard pile is unchanged
 *  4) card from top of deck is moved to hand
 *  5) returns 0 
 *  
 * drawCard: unittest4.c dominion.o rngs.o
 *      gcc -o unit4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 *
 * -----------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


int main() {
    int seed = 1004; // random seed
    int numPlayer = 2; 
    int r;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState G, storeG;
	int thisPlayer = 1;
    int i,j;
	
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    
	int deckSize = G.deckCount[thisPlayer];
	 
            
    //Test runs until player has drawn all cards in original deck
    //Also tests that when deck size is 0 discard pile is shuffled in and a card is drawn
    for (i = 0; i <= deckSize; i++)
    {
		
		memcpy(&storeG, &G, sizeof(struct gameState));  //copy gameState before drawCard
					
		printf("Player has %d cards remaining in deck.\n", G.deckCount[thisPlayer]);
					
		j = (drawCard(thisPlayer, &G));  //call drawCard
		
		//test that drawCard executed correctly
		if (j == 0)
		{
			printf("draw card returned 0, pass\n");
		}
		else {
			printf("draw card returned 0, fail\n");
		}
		
		//test hand increased by 1
		if(G.handCount[thisPlayer] == (storeG.handCount[thisPlayer] + 1))
		{
			printf("handCount passed\n");
		}
		else {
			printf("handCount failed with %d cards remaining in the deck \n", G.deckCount[thisPlayer]);
		}
		
		//test that deck decreased by 1
		if (G.deckCount[thisPlayer] == (storeG.deckCount[thisPlayer] - 1))
		{
			printf("deckCount passed\n");
		}
		else {
			printf("deckCount failed\n");
		}
		
		
		//test that top card from deck before draw is now in hand
		if (G.hand[thisPlayer][G.handCount[thisPlayer] - 1] == storeG.deck[thisPlayer][storeG.deckCount[thisPlayer] - 1])
		{
			printf("top card from the deck now in hand passed\n");
		}
		else {
			printf("top card from the deck now in hand failed\n");
		}
		
		//test that discard pile is the same size
		if (G.discardCount[thisPlayer] == storeG.discardCount[thisPlayer])
		{
			printf("discard pile same size passed\n");
		}
		else {
			printf("discard pile same size failed\n");
		}
		
		discardCard(1, thisPlayer, &G, 0); //discard 1 card to the discarde pile
		
		printf("drawCard() PASSED all tests for this draw.\n");
		
    } 
        
    
    return 0;
}

