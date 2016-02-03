/* Paul Zotz
 * CS 362 Winter 2016
 * Assignment 3 - card test 1 - smithy
 * Test 1 fails due to introduced bug - assertion commented out
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"

int main() {
    int currentPlayer = 0;
    int passed = 1;
    int i, j;
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: current player receives 3 cards --------------
	printf("TEST 1: current player receives 3 cards\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    smithyCard(&testG, currentPlayer, 0); // play smithy card on current player
    // check for 2 more cards (3 cards - smithy)
    //assert(testG.handCount[currentPlayer] == G.handCount[currentPlayer] + 2);
    if (testG.handCount[currentPlayer] != G.handCount[currentPlayer] + 2)
    {
        printf("TEST 1 failed\n");
        passed = 0;
    }


	// ----------- TEST 2: cards come from own pile --------------
	printf("TEST 2: cards come from own pile\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    smithyCard(&testG, currentPlayer, 0); // play smithy card on current player
    int deckDifference = G.deckCount[currentPlayer] - testG.deckCount[currentPlayer];
    int handDifference = testG.handCount[currentPlayer] - G.handCount[currentPlayer];
    // deck difference is -1 to account for smithy being removed from hand
    assert(handDifference == deckDifference - 1);

	// ----------- TEST 3: choice1 = 3 = no state change for other players --------------

	printf("TEST 3: no state change for other players\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	smithyCard(&testG, currentPlayer, 0); // play smithy card on current player
	for (i = 0; i < numPlayers; i++)
    {
        // check all players except current player for state change
        if (i != currentPlayer)
        {
            for (j = 0; j < MAX_HAND; j++)
            {
                // check for changes to this player's hand
                assert(testG.hand[i][j] == G.hand[i][j]);
            }

            for (j = 0; j < MAX_DECK; j++)
            {
                // check for changes to this playe'rs deck
                assert(testG.deck[i][j] == G.deck[i][j]);
            }

            for (j = 0; j < MAX_DECK; j++)
            {
                // check for changes to this player's discard
                assert(testG.discard[i][j] == G.discard[i][j]);
            }
        }
    }

	// ----------- TEST 4: no change to kingdom or victory card piles --------------

	printf("TEST 4: no change to kingdom or victory card piles\n");
	smithyCard(&testG, currentPlayer, 0); // play smithy card on current player

	for (i = 0; i < treasure_map + 1; i++)
    {
        if ((i != copper && i != silver) && i != gold)
            assert(testG.supplyCount[i] == G.supplyCount[i]);
    }

    if (passed)
        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
    else
        printf("\n >>>>> FAILURE: Testing complete %s <<<<<\n\n", TESTCARD);

	return 0;
}


