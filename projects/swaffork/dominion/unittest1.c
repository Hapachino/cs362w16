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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i;
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState *state = malloc(sizeof(struct gameState));
    struct gameState *originalState = malloc(sizeof(struct gameState));
    // int maxHandCount = 5;

    // Initialize game
    
    if (initializeGame(numPlayers, cards, seed, state) < 0)
    {
        printf("Error initializing game.\n");
        return -1;
    }

    // Preserve the original game state to compare result of shuffle()
    memcpy(originalState, state, sizeof(struct gameState));

    printf ("Testing shuffle():\n");

    int player;
    for (player = 0; player < numPlayers; player++)
    {
        if (shuffle(player, state) < 0)
        {
            printf("shuffe() failed.\n");
            return -1;
        }

        //Set of cards in deck is the same (check first that deck count is unchanged)
        for (i = 0; i < numPlayers; i++)
        {
            if (state->handCount[i] != originalState->handCount[i])
            {
                printf("handCount not the same at player%d\n", i);
                return -1;
            }
        }
      
/*  -Order of cards in deck is not the same
 *  -Set and order of other players' decks is the same
 *  -If the player has <= 1 card in his or her deck, everything should be the same */
    }

    printf("All tests passed!\n");

    return 0;
}
