/* Paul Zotz
 * CS 362 Winter 2016
 * Assignment 3 - card test 2 - adventurer
 * Test 1 fails due to introduced bug - assertion commented out
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

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
	printf("TEST 1: current player receives 2 treasure cards\n");

    memcpy(&testG, &G, sizeof(struct gameState));
    for (i = 0; i < testG.handCount[currentPlayer]; i++)
        testG.hand[currentPlayer][i] = curse;

    adventurerCard(&testG, currentPlayer);
    for (i = 1; i <= testG.handCount[currentPlayer]; i++)
    {
        // make sure only last cards are treasure cards
        if (i < 3)
        {
            assert(testG.hand[currentPlayer][testG.handCount[currentPlayer]-i] >= copper &&
                    testG.hand[currentPlayer][testG.handCount[currentPlayer]-i] <= gold);
        }

        else if (testG.hand[currentPlayer][testG.handCount[currentPlayer]-i] != curse && passed == 1)
        {
            printf("TEST 1 failed\n");
            passed = 0 ;
        }
        //else assert(testG.hand[currentPlayer][testG.handCount[currentPlayer]-i] == curse);
    }

	// ----------- TEST 2: discard shuffled and added when deck is empty --------------

	printf("TEST 2: deck is empty - discard must be shuffled and added\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    // stack hand with curses
    for (i = 0; i < testG.handCount[currentPlayer]; i++)
        testG.hand[currentPlayer][i] = curse;
    // stack deck and discard so we know this is possible
    testG.deckCount[currentPlayer] = 0;
    testG.discardCount[currentPlayer] = 5;

    for (i = 0; i < 5; i++)
        testG.discard[currentPlayer][i] = gold;

    adventurerCard(&testG, currentPlayer);

    for (i = 1; i <= 2; i++)
    {
        assert(testG.hand[currentPlayer][testG.handCount[currentPlayer]-i] >= copper &&
                    testG.hand[currentPlayer][testG.handCount[currentPlayer]-i] <= gold);
    }


	// ----------- TEST 3: discard shuffled and added when deck is empty --------------

	printf("TEST 3: non-treasure cards drawn added to discard\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    // stack hand with curses
    for (i = 0; i < testG.handCount[currentPlayer]; i++)
        testG.hand[currentPlayer][i] = curse;

    // stack deck with treasure so we know we have some to draw
    for (i = 0; i < testG.deckCount[currentPlayer]; i++)
        testG.deck[currentPlayer][i] = gold;

    // put two kingdom that aren't used in this game on top of deck so we know where they came from
    testG.deck[currentPlayer][testG.deckCount[currentPlayer] - 1] = salvager;
    testG.deck[currentPlayer][testG.deckCount[currentPlayer] - 2] = salvager;
    testG.discardCount[currentPlayer] = 0; // make sure discard is empty
    adventurerCard(&testG, currentPlayer);
    assert(testG.discardCount[currentPlayer] == 2);

    // check for 2 salvager cards in discard
    for (i = 0; i <= testG.discardCount[currentPlayer] - 1; i++)
    {
        assert(testG.discard[currentPlayer][i] == salvager);
    }


    // ----------- TEST 5: cards came from own deck --------------

	printf("TEST 5: cards came from own deck\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    // stack deck with treasure so we know we have some to draw
    for (i = 0; i < testG.deckCount[currentPlayer]; i++)
        testG.deck[currentPlayer][i] = gold;

    adventurerCard(&testG, currentPlayer);

    int cardsDrawn = testG.handCount[currentPlayer] - G.handCount[currentPlayer];
    assert(testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - cardsDrawn);

	// ----------- TEST 5: no state change for other players --------------
    printf("TEST 5: no state change for other players\n");
	adventurerCard(&testG, currentPlayer); // play adventurer card on current player
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


    // ----------- TEST 6: no change to kingdom or victory card piles --------------

	printf("TEST 6: no change to kingdom or victory card piles\n");
	adventurerCard(&testG, currentPlayer);
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


