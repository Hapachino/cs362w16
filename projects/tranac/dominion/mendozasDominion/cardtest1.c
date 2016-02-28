/* -----------------------------------------------------------------------
 * Testing smithy
 * Pre conditions
 *  1) passes in hand pos, currentPlayer, gamestate 
 * Post conditions
 *  1) players hand is increased by 3
 *  2) players deck is decreased by 3
 *  3) smithy is discarded
 *  4) players turn doesn't change
 *
 *  smithy: cardtest1.c dominion.o rngs.o
 *      gcc -o card1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
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
  
	int pos =0;
	int numPlayers = 2;
	int seed = 1004;
	struct gameState G, storeG;
	int r;
	int thisPlayer = 0;
	int kcards[10] = {adventurer, minion, cutpurse, steward, smithy,
			   council_room, village, mine, tribute, ambassador};
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayers, kcards, seed, &G);;

	printf ("TESTING smithy:\n");

	memcpy(&storeG, &G, sizeof(struct gameState));  //copy gameState before smithy.

	thisPlayer=whoseTurn(&G);//added to identify player turn
	//play smithy card
	playSmithy(&G, pos);//corrected to pass in correct values and call correct function name
	
	
	#if (NOISY == 1)
	//deck should have -3 cards
	if (G.deckCount[thisPlayer] == (storeG.deckCount[thisPlayer]- 3))
	{
		printf("deckCount PASSED\n");
	}
	else {
		printf("deckCount Failed\n");
	}
	
	//smithy should be removed from hand
	if (G.hand[thisPlayer][pos] != storeG.hand[thisPlayer][pos])
	{
		printf("smithy removed from hand PASSED\n");
	}
	else {
		printf("smithy removed from hand FAILED\n");
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
   
	#endif
	
	printf("\nAll tests completed. \n");

    return 0;
}