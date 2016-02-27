/*  Paul Zotz
    CS 362 Winter 2016
    Assignment 4 - randomtestadventurer
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
#define NUM_TESTS 500

int cardsForPlayer(int, struct gameState *);
void checkAdventurer(int, struct gameState *, int);

int main() {
    int i, n;
    int thisPlayer;
    int handPos;
    int p1treasure, p2treasure, treasureBefore;
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
        p1treasure = cardsForPlayer(0, &G);
        p2treasure = cardsForPlayer(1, &G);
        // randomly pick a player
        thisPlayer = floor(Random() * 2);
        if (thisPlayer == 0)
            treasureBefore = p1treasure;
        else
            treasureBefore = p2treasure;

        // make sure player hand has adventurer to play
        //handPos = floor(Random() * G.handCount[thisPlayer]);
        //G.hand[thisPlayer][handPos] = adventurer;
        checkAdventurer(thisPlayer, &G, treasureBefore);
    }

	printf("\n >>>>> SUCCESS: Random testing complete: %s <<<<<\n\n", TESTCARD);
	return 0;
}

int cardsForPlayer(int thisPlayer, struct gameState *G)
{

	int j, numTreasure, thisCard;
	numTreasure = 0;
    int deckCards = floor(Random() * MAX_DECK);
    G->discardCount[thisPlayer] = 0;
    int handCards = floor(Random() * MAX_HAND);

    G->deckCount[thisPlayer] = deckCards;
    G->handCount[thisPlayer] = handCards;

    for(j = 0; j < deckCards; j++)
    {
        thisCard = floor(Random() * (treasure_map + 1));
        if ((thisCard == gold || thisCard == silver) || thisCard == copper)
            numTreasure++;

        G->deck[thisPlayer][j] = thisCard;

        // start again if we end up without at least 2 treasures
        if (j == deckCards - 1 && numTreasure < 2)
        {
            j = 0;
            numTreasure = 0;
        }

    }

    numTreasure = 0; //reset numTreasure to count treasures in hand
    for(j = 0; j < handCards; j++)
    {
        thisCard = floor(Random() * (treasure_map + 1));
        G->hand[thisPlayer][j] = thisCard;
        if ((thisCard == gold || thisCard == silver) || thisCard == copper)
            numTreasure++;
    }

	return numTreasure;

}

void checkAdventurer(int thisPlayer, struct gameState *G, int treasureBefore)
{
    int treasureAfter = 0;
    int deckBefore;
    int numTreasure = 0;
    struct gameState testG;
    int i, z = 0;
    int temphand[MAX_HAND];
    int otherPlayer;
    int result;
    int discardCount = 0;
    memcpy (&testG, G, sizeof(struct gameState));

    deckBefore = testG.deckCount[thisPlayer];


    if (thisPlayer == 1)
        otherPlayer = 0;
    else
        otherPlayer = 1;

    // call adventurerCard on testG
    result = playAdventurer(thisPlayer, &testG);

    // count treasures on testG after call
    for (i = 0; i < testG.handCount[thisPlayer]; i++)
    {
        if (testG.hand[thisPlayer][i] <= gold && testG.hand[thisPlayer][i] >= copper)
            treasureAfter++;
    }

    // do what we think adventurer should do to G
    while(numTreasure < 2)
	{
		if(G->deckCount[thisPlayer] < 1)
		{
			shuffle(thisPlayer, G);
		}

		drawCard(thisPlayer, G);
		int thisCard = G->hand[thisPlayer][G->handCount[thisPlayer]-1];
		if (thisCard >= copper && thisCard <= gold)
			numTreasure++;
		else
		{
		    discardCount++; // manually track expected discards
			temphand[z] = thisCard;
			G->handCount[thisPlayer]--;
			z++;
		}
	}

	while(z-1>=0){
        G->discard[thisPlayer][G->discardCount[thisPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
        z--;
    }

    // -- TESTS --//
    printf("Adventurer returned successfully - return value %d, expected %d\n", result, 0);
    assert (result == 0); // adventurer returned correctly
    int treasureReceived = treasureAfter - treasureBefore;
    printf("Current player received 2 treasures - received %d, expected %d\n", treasureReceived, numTreasure);
    // assert (treasureAfter - treasureBefore == numTreasure);
    if (treasureReceived != numTreasure) // replace assert since it always catches bug
        printf("Failure: incorrect number of treasures received\n");

    printf("Cards added to discard - discard pile %d, expected %d\n",
           testG.discardCount[thisPlayer], G->discardCount[thisPlayer]);
    //assert(testG.discardCount[thisPlayer] == discardCount);
    if (testG.discardCount[thisPlayer] != discardCount)
        printf("Failure: discard not incremented properly\n");
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
        printf("Failure: game states are not identical\n");
    //assert(memcmp(&G, testG, sizeof(struct gameState)) == 0);
}
