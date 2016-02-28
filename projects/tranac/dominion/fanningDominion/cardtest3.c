/* -----------------------------------------------------------------------
 * Testing village
 * Pre conditions
 *  1) passed in handPos, currentPlayer, gamestate 
 * Post conditions
 *  1) players hand is not changed
 *  2) players deck is decreased by by 1
 *  3) players turn doesn't change
 *  4) players discard pile is increased by 1
 *  5) players action is increased by 2
 *
 *  village: cardtest3.c dominion.o rngs.o
 *      gcc -o card3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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
	int pos = 1;
	int thisPlayer = 0;
	int kcards[10] = {adventurer, minion, cutpurse, steward, smithy,
			   council_room, village, mine, tribute, ambassador};
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayers, kcards, seed, &G);;

	printf ("TESTING village:\n");

	memcpy(&storeG, &G, sizeof(struct gameState));  //copy gameState before smithy.

	//play adventurer card
	villageCard(thisPlayer, &G, pos);
	
		#if (NOISY == 1)
	//deck should decrement by 1
	if (G.deckCount[thisPlayer] == (storeG.deckCount[thisPlayer]- 1))
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

	//hand should should not change
	if (G.handCount[thisPlayer] == storeG.handCount[thisPlayer])
	{
		printf("handCount PASSED\n");
	}
	else {
		printf("handCount FAILED\n");
	}
	
	//discard pile should increase by 1
	if (G.discardCount[thisPlayer] == (storeG.discardCount[thisPlayer] + 1))
	{
		printf("discardCount PASSED\n");
	}
	else {
		printf("discardCount FAILED\n");
	}
   
	//players action should increase by 2
	if (G.numActions == (storeG.numActions + 2))
	{
		printf("numActions PASSED\n");
	}
	else {
		printf("numActions FAILED\n");
	}
   
	#endif
	
	printf("\nAll tests completed. \n");


    return 0;
}