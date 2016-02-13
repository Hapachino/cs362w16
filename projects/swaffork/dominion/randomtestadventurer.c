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

    // Randomly change bytes in game state
    for (i = 0; i <= 1000; i++)
    {
        for (j = 0; j < sizeof(struct gameState); j++)
        {
            ((char*)state)[j] = floor(Random() * 256);
        }
    }

    // Randomly assign players and their decks, hands, and discard piles
    
    state->whoseTurn = player;
    return 0;
}

int testAdventurer(struct gameState* state)
{
    int i;
    int j;
    printf("Beginning random tests for adventurer:\n");

    SelectStream(2);
    PutSeed(3);

            
}

int main()
{
    srand(time(NULL));

