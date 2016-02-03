/* -----------------------------------------------------------------------
 * Testing council_room
 * Pre conditions
 *  1) currentPlayer, handpos, gamestate 
 * Post conditions
 *  1) players hand is increased by 4
 *  2) players deck is decreased by by 4
 *  3) players turn doesn't change
 *  4) players discard pile is increased by 1
 *  5) players numBuys is increased by 1
 *	6) each other players hand is increased by 1
 *  7) each other players deck is decreased by 1
 *
 *  village: cardtest4.c dominion.o rngs.o
 *      gcc -o card4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
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
  
	int numPlayers = 3;
	int seed = 1004;
	struct gameState G, storeG;
	int r;
	int i;
	int pos = 1;
	int thisPlayer = 0;
	int kcards[10] = {adventurer, minion, cutpurse, steward, smithy,
			   council_room, village, mine, tribute, ambassador};
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayers, kcards, seed, &G);;

	printf ("TESTING council_room:\n");

	memcpy(&storeG, &G, sizeof(struct gameState));  //copy gameState before smithy.

	//play adventurer card
	council_roomCard(thisPlayer, pos, &G);
	
	#if (NOISY == 1)
	//deck should decrement by 4
	if (G.deckCount[thisPlayer] == (storeG.deckCount[thisPlayer]- 4))
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

	//hand should should increase by 3
	if (G.handCount[thisPlayer] == (storeG.handCount[thisPlayer]+3))
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
   
	//players numBuys should increase by 1
	if (G.numBuys == (storeG.numBuys + 1))
	{
		printf("numBuys PASSED\n");
	}
	else {
		printf("numBuys FAILED\n");
	}
	
	//other players hand should increase by 1
	for (i = (thisPlayer + 1); i < numPlayers; i++)
	{
		if (G.handCount[i] == (storeG.handCount[i]+1))
		{
			printf("handCount for player %d PASSED\n", i);
		}
		else {
			printf("handCount for player %d failed\n", i);
		}
	}
	
		//other players deck should decrease by 1
	for (i = (thisPlayer + 1); i < numPlayers; i++)
	{
		if (G.deckCount[i] == (storeG.deckCount[i]-1))
		{
			printf("deckCount for player %d PASSED\n", i);
		}
		else {
			printf("deckCount for player %d failed\n", i);
		}
	}
   
	#endif
	
	printf("\nAll tests completed. \n");
	
    return 0;
}