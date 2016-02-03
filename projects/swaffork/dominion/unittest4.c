/* -----------------------------------------------------------------------
 * isGameOver()
 *
 * The isGameOver() function works as follows:
 *  -returns 1 on any end-game condition (0 province cards OR three supply piles at 0)
 *
 * Things to check:
 *  -0 province cards returns 1
 *  -3 supply piles at 0 returns 1
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testhelper.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main()
{
    int seed = 1000;
    int numPlayers = 2;
    int cards[10] = {adventurer, council_room, feast, gardens, mine,
                     remodel, smithy, village, baron, great_hall};
    struct gameState state;

    // Initialize gameState
    if (initializeState(numPlayers, cards, seed, &state) != 0)
    {
        printf("Error: Could not initialize state.\n");
        return -1;
    }

    printf("Testing isGameOver():\n");

    // Stack of province cards is empty
    state.supplyCount[province] = 0;
    if (isGameOver(&state) != 1)
    {
        printf("\tERROR: No province cards left; game should be over.\n");
        return -1;
    }
    // restore supply count for next test
    state.supplyCount[province] = 8;
    
    // 3 supply stacks are empty
    state.supplyCount[adventurer] = 0;
    state.supplyCount[council_room] = 0;
    state.supplyCount[feast] = 0;
    if (isGameOver(&state) != 1)
    {
        printf("\tERROR: 3 supply stacks are empty; game should be over.\n");
        return -1;
    }

    printf ("All tests passed.\n");
    return 0;
}
