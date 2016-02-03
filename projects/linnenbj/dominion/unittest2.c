/* -----------------------------------------------------------------------
 * getCost() Unit Testing file
 * Author: James Linnenburger - Oregon State CS362 Spring 2016
 *
 * This test calls the getCost method for all possible cards in the game
 * and check to make sure it returns the correct values.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"





// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1


int main()
{
    int cardCosts[27] = {0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4, 3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4};
    char *cardNames[27] =  {"curse", "estate", "duchy", "province", "copper",
                            "silver", "gold", "adventurer", "council_room", "feast",
                            "gardens", "mine", "remodel", "smithy", "village", "baron",
                            "great_hall", "minion", "steward", "tribute",
                            "ambassador", "cutpurse", "embargo", "outpost", "salvager",
                            "sea_hag", "treasure_map"};

    int i, pass = 0, fail = 0;

    printf ("\nTESTING getCost():\n");

    //test all possible card costs and an out of range value
    for(i = 0; i < 28; i++)
    {
        if(cardCosts[i] == getCost(i))
        {
            pass++;
            #if (NOISY_TEST == 1)
            printf("\tCard: %s Passed.\n", cardNames[i]);
            #endif
        }
        else if(getCost(i) == -1 && (i < 0 || i > 26)) //was an invalid input sent? should return -1
        {
            pass++;
            #if (NOISY_TEST == 1)
            printf("\tNot a Card: Passed.\n");
            #endif
        }
        else
        {
            #if (NOISY_TEST == 1)
            fail++;
            printf("\tCard: %s failed.\n", cardNames[i]);
            #endif
        }
    }

    printf("Test results: [%d fails]  [%d/28 passes]\n          >>>>> Testing getCost() Complete <<<<<\n\n", fail, pass);
    return 0;
}
