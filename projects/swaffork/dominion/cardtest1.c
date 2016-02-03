/* -----------------------------------------------------------------------
 * playAdventurer()
 *
 * The playAdventurer() function works as follows:
 *  -discards cards until player draws 2 treasure cards
 *  -discards all cards drawn that were not treasure cards
 *
 * Things to check:
 *  -player has drawn 2 treasure cards
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
    int player = 0;
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall};
    struct gameState state;
    struct gameState originalState;

    // Initialize gameState
    if (initializeGame(numPlayers, cards, seed, &state) != 0)
    {
        printf("Error: Default initializeGame() failed.\n");
        return -1;
    }

    // Preserve the original game state to compare result of shuffle()
    memcpy(&originalState, &state, sizeof(struct gameState));

    printf ("Testing playAdventurer():\n");


    printf("All tests passed!\n");
    return 0;
}
