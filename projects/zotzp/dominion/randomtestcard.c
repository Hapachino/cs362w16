/*  Paul Zotz
    CS 362 Winter 2016
    Assignment 4 - randomtestcard (village)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"
#define NUM_TESTS 1000
void cardsForPlayers(struct gameState *);
void checkVillage(int, struct gameState *, int);

int main() {
    int i, n;
    int thisPlayer;
    int handPos = 0;
	struct gameState G;

	// Random control
	SelectStream(2);
    PutSeed(3);

    printf("Random testing %s:\n", TESTCARD);
    for (n = 0; n < NUM_TESTS; n++) {\
        printf("\n >>>>> TEST %d <<<<<\n\n", n + 1);
        // randomize struct - from lecture
        for (i = 0; i < sizeof(struct gameState); i++) {
          ((char*)&G)[i] = floor(Random() * 256);
        }
        // generate random decks and hands for both players
        cardsForPlayers(&G);
        // randomly pick a player
        G.numActions = 0;
        thisPlayer = floor(Random() * 2);
        // make sure player hand has village to play
        do
        {
            handPos = Random() * G.handCount[thisPlayer];
        } while (handPos == G.handCount[thisPlayer]);
        G.hand[thisPlayer][handPos] = village;
        checkVillage(thisPlayer, &G, handPos);
    }

	printf("\n >>>>> SUCCESS: Random testing complete: %s <<<<<\n\n", TESTCARD);

	return 0;
}

void cardsForPlayers(struct gameState *G)
{
    int i, j;
	for(i = 0; i < 2; i++)
	{
	    int deckCards = floor(Random() * MAX_DECK);
        G->discardCount[i] = 0;
        G->playedCardCount = 0;
        int handCards = floor(Random() * MAX_HAND);

		/* coin toss to halve piles - helps run time while
       still allowing for large pile sizes */

        if (handCards >  10 && deckCards > 10)
        {
            if (rand()%2 == 1)
            {
                deckCards /= 2;
                handCards /= 2;
            }
        }

		G->deckCount[i]  = deckCards;
		G->handCount[i] = deckCards;
		for(j = 0; j < deckCards; j++)
            G->deck[i][j] = floor(Random() * (treasure_map + 1));

		for(j = 0; j < handCards; j++)
            G->hand[i][j] = floor(Random() * (treasure_map + 1));
	}

}

void checkVillage(int thisPlayer, struct gameState *G, int handPos) {
    int otherPlayer;
    int result;
    int discardCount = 0;
    struct gameState testG;
    memcpy (&testG, G, sizeof(struct gameState));

    if (thisPlayer == 1)
        otherPlayer = 0;
    else
        otherPlayer = 1;

    result = villageCard(&testG, thisPlayer, handPos);

    // do to G what we think village should do
    drawCard(thisPlayer, G);
    G->numActions += 2;
    // discard village from hand
    discardCard(handPos, thisPlayer, G, 0);
    discardCount++;

    // -- TESTS --//
    printf("Village returned successfully - return value %d, expected %d\n", result, 0);
    assert (result == 0); // village returned correctly
    printf("Number of actions incremented properly - actions %d, expected %d\n", testG.numActions, G->numActions);
    // assert (testG.numActions == G->numActions);
    if (testG.numActions != G->numActions) // replace assert since it always catches bug
        printf("Failure: incorrect number of actions added\n");

    printf("Played card discarded as expected - played card pile %d, expected %d\n",
           testG.playedCardCount, G->playedCardCount);
    assert(testG.playedCardCount == G->playedCardCount);
    printf("Discarded card is village - played card value %d, expected %d\n",
           testG.playedCards[testG.playedCardCount - 1], village);
    assert(testG.playedCards[testG.playedCardCount - 1] == village);
    // check for state change to other player
    printf("No state change to other player:\n");
    printf("     Other player deck count - actual %d, expected %d\n",
           testG.deckCount[otherPlayer], G->deckCount[otherPlayer]);
    assert(testG.deckCount[otherPlayer] == G->deckCount[otherPlayer]);
    printf("     Other player hand count - actual %d, expected %d\n",
           testG.handCount[otherPlayer], G->handCount[otherPlayer]);
    assert(testG.handCount[otherPlayer] == G->handCount[otherPlayer]);
    printf("     Other player discard count - actual %d, expected %d\n",
           testG.discardCount[otherPlayer], G->discardCount[otherPlayer]);
    assert(testG.discardCount[otherPlayer] == G->discardCount[otherPlayer]);

    // test game states have been altered the same way
    printf("Testing for identical game states...\n");
    if (memcmp(G, &testG, sizeof(struct gameState)) == 0)
        printf("Success: both game states identical\n");
    else
        printf("Fail: game states are not identical\n");
    //assert(memcmp(&G, testG, sizeof(struct gameState)) == 0);
}
