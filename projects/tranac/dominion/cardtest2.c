/* -----------------------------------------------------------------------
 * Testing adventurer
 * Pre conditions
 *  1) passed in currentPlayer, gamestate 
 * Post conditions
 *  1) players hand is increased by 2
 *  2) players deck is decreased by by number of cards drawn
 *  3) players turn doesn't change
 *  4) players discard pile is increased by extra drawn cards -2
 *
 *  adventurer: cardtest2.c dominion.o rngs.o
 *      gcc -o card2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 *
 * -----------------------------------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//set NOISY to 0 to remove prinftf's from output
#define NOISY 1

int main() {
  
	int numPlayers = 2;
	int seed = 1004;
	struct gameState G, storeG;
	int r;
	int ret;
	int thisPlayer = 0;
	int kcards[10] = {adventurer, minion, cutpurse, steward, smithy,
			   council_room, village, mine, tribute, ambassador};
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayers, kcards, seed, &G);;

	printf ("TESTING adventurer:\n");

	memcpy(&storeG, &G, sizeof(struct gameState));  //copy gameState before smithy.

	//play adventurer card
	ret = adventurerCard(thisPlayer, &G);
	
	#if (NOISY == 1)
	//deck should decrement by number of cards drawn returned by adventurer
	if (G.deckCount[thisPlayer] == (storeG.deckCount[thisPlayer]- ret))
	{
		printf("deckCount PASSED\n");
	}
	else {
		printf("deckCount Failed\n");
	}
	
	//player's turn should not change
	if (G.whoseTurn == storeG.whoseTurn)
	{
		printf("player turn PASSED\n");
	}
	else{
		printf("player turn FAILED\n");
	}

	//hand should have +2 cards
	if (G.handCount[thisPlayer] == (storeG.handCount[thisPlayer] + 2))
	{
		printf("handCount PASSED\n");
	}
	else {
		printf("handCount FAILED\n");
	}
	
	//discard pile should increase by unused cards 
	if (G.discardCount[thisPlayer] == (storeG.discardCount[thisPlayer] + ret - 2))
	{
		printf("discardCount PASSED\n");
	}
	else {
		printf("discardCount FAILED\n");
	}
   
	#endif
	
	printf("\nAll tests completed. \n");
	

    return 0;
}