/* -----------------------------------------------------------------------
 * shuffle()
 *
 * The shuffle() function works as follows:
 *  -create a new deck to hold shuffled deck
 *  -sort the player's cards
 *  -pick random cards from the player's deck and place into new deck
 *  -copy new deck into player's deck
 *
 * Things to check:
 *  -Set of cards in deck is the same (check first that deck count is unchanged)
 *  -Order of cards in deck is not the same
 *  -Set and order of other players' decks is the same
 *  -If the player has <= 1 card in his or her deck, everything should be the same
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testhelper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

int compare(const void* a, const void* b);

int main() {
    int i;
    int player;
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall};
    struct gameState state;
    struct gameState originalState;

    // Initialize gameState
    if (initializeState(numPlayers, cards, seed, &state) != 0)
    {
        printf("Error: Could not initialize state.\n");
        return -1;
    }

    // Preserve the original game state to compare result of shuffle()
    memcpy(&originalState, &state, sizeof(struct gameState));

    printf ("Testing shuffle():\n");

    player = 0;
    printf("Shuffling Player %d:\n", player);

    if (shuffle(player, &state) < 0)
    {
        printf("\tERROR: shuffe() failed.\n");
        return -1;
    }

    // Check first that each player's deck count is unchanged)
    int p;
    for (p = 0; p < numPlayers; p++)
    {
        if (state.handCount[p] != originalState.handCount[p])
        {
            printf("\tERROR: handCount not the same\n");
            return -1;
        }
    }

    // Check order of cards for each player 
    for (p = 0; p < numPlayers; p++)
    {
        printf("Checking order of player %d's deck...\n", p);

        i = 0;
        while ( (i < state.deckCount[p]) &&
                (state.deck[p][i] == originalState.deck[p][i]) )
        {
            printf("\tshuffled card %d: %d\n", i, state.deck[p][i]);
            printf("\toriginal card %d: %d\n", i, originalState.deck[p][i]);
            i++;
        }
        printf("\n");
        
        // Check if order of cards in shuffled deck is the same
        if (p == player && i >= state.deckCount[p])
        {
            printf("ERROR: Order of shuffled deck is the same.\n");
            return -1;
        }
        else if (p == player && i < state.deckCount[p])
        {
            printf("Player %d's is different! Great success!\n", player);
        }

        // Check if order of cards in unshuffled deck is the same
        if (p != player && i < state.deckCount[p])
        {
            printf("ERROR: Order of non-shuffled deck is different.\n");
            return -1;
        }
    }
    
    // Check that shuffled deck has same set of cards
    qsort((void*)(state.deck[0]), state.deckCount[player], sizeof(int), compare);
    qsort((void*)(originalState.deck[0]), state.deckCount[player], sizeof(int), compare);

    if (memcmp(&state, &originalState, sizeof(struct gameState)) != 0)
    {
        printf("\tERROR: memcmp failed.\n");
        return -1;
    }

    printf("All tests passed!\n");
    return 0;
}
