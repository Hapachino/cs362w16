/*
 * Test for isGameOver function.
 * isGameOver() returns 1 if game is over and 0 if not over.
 * It does this by checking if the three supply piles are empty and checking the number
 * of provinces.
 * Some code has been sourced from lecture videos. 
*/

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int testGameOver()
{
    int empty_supplies = 0;
    int card = 0;
    int result = isGameOver(G);

    // Replicates the isGameOver function. First tests if province cards are empty.
    // Next tests if the three supply piles are empty.
    // Compares result in test to game state G and throws error if inconsistent.
    if(G->supplyCount[province] == 0)
    {
        if(result != 1)
            printf("Error found: supplyCount == 0 and isGameOver exits with 0.");   
    }
    else
    {
        for(card = 0; card < treasure_map; card++)
        {
            if(G->supplyCount[card] == 0)
                empty_supplies++;
        }

        if(empty_supplies > 2 && result != 1)
            printf("Error found: supplyCount[card] == 0 and isGameOver exits with 0."); 
    }
}

void fillCards(struct gameState *G)
{
    int i;
    for(i = 0; i < treasure_map; i++)
    {
        G.supplyCount[i] = 5;
    }
}

int main()
{
    struct gameState G;
    
    SelectStream(2);
    PutSeed(3);

    printf("Test output.");

    int province_count;
    int i;
    for(province_count = 0; province_count < 3; province_count++)
    {
        for(i = 0; i < sizeof(struct gameState); i++)
        {
            ((char*)&G[i] = floor(Random() * 256);
        }
        G.supplyCount[province] = province_count;

        testGameOver(&G);
    }

    
    fillCards(&G);
    G.supplyCount[copper] = 0;
    G.supplyCount[silver] = 0;
    G.supplyCount[gold] = 0;
    testGameOver(&G);

    fillCards(&G);
    G.supplyCount[copper] = 0;
    G.supplyCount[silver] = 0;
    testGameOver(&G);

    printf("isGameOver function - Test Complete\n");    

    return 0;
}
