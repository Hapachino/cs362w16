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
    int player = 0;
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
    
    state->whoseTurn = player;
    return 0;
}

int testAdventurer(struct gameState* state)
{
    int player = 0;
    int rand = 0;
    int i;
    struct gameState state;
    if (setUp(&state) == -1) return 0;

    // Randomize player deck
    state->deckCount[player] = 0;
    state->deckCount[player + 1] = 0;
    rand = rand() % MAX_DECK;
    
    for (i = 0; i < rand; i++)
    {
    }

    return 0;
}

int main()
{
    srand(time(NULL));

