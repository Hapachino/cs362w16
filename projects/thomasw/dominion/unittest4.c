/*******************************************
* Test for discardCard()
* Add this to your dominion makefile
* unittest4: unittest4.c dominion.o rngs.o
     gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
*******************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNCTION "discardCard()"

int main(int argc, char const *argv[])
{
	int i;
	int seed = 1000;
	int thisPlayer = 0;
	int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, great_hall, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	//Set up initial hand
	G.hand[thisPlayer][0] = copper;
    G.hand[thisPlayer][1] = silver;
    G.hand[thisPlayer][2] = gold;
    G.hand[thisPlayer][3] = village;
    G.hand[thisPlayer][4] = minion;    

	printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

	memcpy(&testG, &G, sizeof(struct gameState));

	//Test 1: last card in hand is played, trash flag not set
	printf("\nTest 1: Last card in hand is played");
    printf("\nStarting hand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

    discardCard(testG.handCount[thisPlayer]-1, thisPlayer, &testG, 0);

    printf("\nUpdated hand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

    printf("\nDiscarded contents:\n");
    for (i = 0; i < testG.playedCardCount; ++i)
    {
    	printf("%d, ", testG.playedCards[i]);
    }

    //Proves card wasn't trashed
    if (testG.playedCards[0] != G.hand[thisPlayer][G.handCount[thisPlayer]-1])
    {
    	printf("\n----------------- TEST FAILED -----------------\n");
    }
    //Hand was decremented by 1
    else if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] - 1)
    {
    	printf("\n----------------- TEST FAILED -----------------\n");
    }
	else
		printf("\n----------------- TEST PASSED -----------------\n");

	//Test 2: discarding last card in hand
	printf("\nTest 2: Discarding last card in hand\n");
	
	//Reset game state
	memcpy(&testG, &G, sizeof(struct gameState));
	int count = testG.handCount[thisPlayer];

	//Set hand to 1 card
	for (i = 1; i < count; ++i)
	{
		testG.hand[thisPlayer][i] = -1;
		testG.handCount[thisPlayer] --;
	}

    printf("\nStarting hand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

    discardCard(testG.handCount[thisPlayer]-1, thisPlayer, &testG, 0);

    printf("\nUpdated hand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

    printf("\nDiscarded contents:\n");
    for (i = 0; i < testG.playedCardCount; ++i)
    {
    	printf("%d, ", testG.playedCards[i]);
    }

    if (testG.playedCards[0] != G.hand[thisPlayer][G.handCount[thisPlayer]-4])
    {
    	printf("\n----------------- TEST FAILED -----------------\n");
    }
    //Hand was decremented by 1
    else if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] - 5)
    {
    	printf("\n----------------- TEST FAILED -----------------\n");
    }
	else
		printf("\n----------------- TEST PASSED -----------------\n");

	//Test 3: Discard card from middle of hand

	printf("\nTest 3: Discarding card from middle of hand. Discarded card is replaced by last card in hand.\n");
	
	//Reset game state
	memcpy(&testG, &G, sizeof(struct gameState));
    
    printf("\nStarting hand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

    discardCard(testG.handCount[thisPlayer]-3, thisPlayer, &testG, 0);

    printf("\nUpdated hand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

    printf("\nDiscarded contents:\n");
    for (i = 0; i < testG.playedCardCount; ++i)
    {
    	printf("%d, ", testG.playedCards[i]);
    }

    if (testG.playedCards[0] != G.hand[thisPlayer][G.handCount[thisPlayer]-3])
    {
    	printf("\n----------------- TEST FAILED -----------------\n");
    }
    //Hand was decremented by 1
    else if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] - 1)
    {
    	printf("\n----------------- TEST FAILED -----------------\n");
    }
    //Discarded card replaced by last card in hand
    else if (testG.hand[thisPlayer][testG.handCount[thisPlayer]-2] != G.hand[thisPlayer][G.handCount[thisPlayer]-1])
    {
    	printf("\n----------------- TEST FAILED -----------------\n");
    }
	else
		printf("\n----------------- TEST PASSED -----------------\n");

	//Test 4: discard card with trash flag set
	printf("\nTest 4: Discard with trash flag set to true");

	//Reset game state
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("\nStarting hand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

    discardCard(testG.handCount[thisPlayer]-1, thisPlayer, &testG, 1);

	printf("\nUpdated hand contents:\n");
    for (i = 0; i < testG.handCount[thisPlayer]; i++) {
        printf("%d, ", testG.hand[thisPlayer][i]);
    }

    printf("\nDiscarded contents:\n");
    for (i = 0; i < testG.playedCardCount; ++i)
    {
    	printf("%d, ", testG.playedCards[i]);
    }

    printf("Expected: \n");

    if(testG.playedCardCount == 0)
    {
		printf("\n----------------- TEST PASSED -----------------\n");
    }
    else
		printf("\n----------------- TEST FAILED -----------------\n");

    //Test state unchanged for both players
	for (i = 0; i < 2; ++i)
    {
	    printf("\nTesting unchanged state for player%d:\n", i+1);
		printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
		printf("deck count = %d, expected = %d\n", testG.deckCount[i], G.deckCount[i]);
		printf("discard count = %d, expected = %d\n", testG.discardCount[i], G.discardCount[i]);
		if ((testG.handCount[i]) != (G.handCount[i]) || (testG.deckCount[i]) != (G.deckCount[i]) || (testG.discardCount[i]) != (G.discardCount[i]))
		{
			printf("----------------- TEST FAILED -----------------\n");
		}
		else
			printf("----------------- TEST PASSED -----------------\n");
    }

	return 0;
}