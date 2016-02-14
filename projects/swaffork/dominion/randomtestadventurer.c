/*
 * randomtestadventurer.c
 *
 * Random tester for adventurer card in Dominion.
 * Code based on random testing lecture from CS362 - Winter16
 *
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testhelper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

int setUp(struct gameState* state)
{
    int i;
    int r; 
    int index = -1;
    int player;
    int numTests = 1000;
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall};

    // Initialize gameState
    if (initializeGame(numPlayers, cards, seed, state) != 0)
    {
        printf("Error: Default initializeGame() failed.\n");
        return -1;
    }

    // Randomly decide who goes first and randomly set their deck, discard, and hand count
    player = rand() % 2;
    state->whoseTurn = player;
    state->deckCount[player] = floor(Random() * MAX_DECK);
    state->handCount[player] = floor(Random() * MAX_HAND + 1);
    state->discardCount[player] = floor(Random() * MAX_DECK);

    // Since adventurer must draw 2 treasure cards, consider case where there are two treasure cards for interesting test results:
    for (i = 0; i < 2; i++)
    {
        r = floor(Random() * state->deckCount[player];
        if (index == r) continue;
        else index = r;
        state->deck[player][index] = copper;
    }

    return 0;
}

int testAdventurer(struct gameState* state)
{
    printf("Beginning random tests for adventurer:\n");

    SelectStream(2);
    PutSeed(3);
            
}

int main()
{

    return 0;
}
