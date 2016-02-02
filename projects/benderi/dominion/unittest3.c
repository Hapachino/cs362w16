/* Author:      Ian Bender
 * Course:      CS362
 * Due Date:    2/3/2016
 * Description: Unit test for getCost() function.
 * Business Requirements
 *      - Correct value of card is returned
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() 
{
    int i, j;
    int outcome;
    int seed = 1000;
    struct gameState G, testG;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                    remodel, smithy, village, baron, great_hall};

    int cards[27] = {curse, estate, duchy, province,
                     copper, silver, gold, adventurer, council_room,
                     feast, gardens, mine, remodel, smithy, village,
                     baron, great_hall, minion, steward, tribute,
                     ambassador, cutpurse, embargo, outpost, 
                     salvager, sea_hag, treasure_map};
    int values[27] = {0, 2, 5, 8,
                      0, 3, 6, 6, 5,
                      4, 4, 5, 4, 4, 3,
                      4, 3, 5, 3, 5, 
                      3, 4, 2, 5,
                      4, 4, 4};

    //initialize game state
    outcome = initializeGame(MAX_PLAYERS, k, seed, &G);
    if (outcome == -1)
        printf("ERROR - Game initialization failed.\n");
    memcpy(&testG, &G, sizeof(struct gameState));


    printf("TESTING - GET CARD COSTS\n");
    //test each card against its expected value
    for (i = 0; i < 27; i++)
    {
        if (getCost(cards[i]) != values[i])
            printf("ERROR - Returned cost: %d, Expected cost: %d\n",
                    getCost(cards[i]), values[i]);
        else
            printf("SUCCESS - Returned cost: %d, Expected cost: %d\n",
                    getCost(cards[i]), values[i]);
    }

    if (getCost(treasure_map + 1) != -1)
        printf("ERROR - Returned cost: %d, Expected cost: -1\n",
                getCost(treasure_map + 1));
    else
        printf("SUCCESS - Returned cost: %d, Expected cost: -1\n",
                getCost(treasure_map + 1));

    printf("TEST COMPLETE\n");

    return 0;
}
