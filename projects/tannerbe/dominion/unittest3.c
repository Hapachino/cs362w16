#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define TESTFUNCTION "buyCard"

int main() {
    int seed = 1000;
    int numPlayers = 4;
    int numBuys, numCoins, player, supplyPos, result;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    initializeGame(numPlayers, k, seed, &G);
    int buys[5] = {0, 1, 2, 3, 10};
    int coins[5] = {0, 1, 3, 8, 20};


    printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

    for (player = 0; player < numPlayers; player++) //for each of the players
    {
        G.whoseTurn = player;
        for (supplyPos = 0; supplyPos < 27; supplyPos++) //for every possible card
        {
            for (numBuys = 0; numBuys < 5; numBuys++) //for each of the 5 predefined number of buys
            {
                G.numBuys = buys[numBuys];
                for (numCoins = 0; numCoins < 5; numCoins++) //for each of the 5 predefined coin values
                {
                    G.coins = coins[numCoins];
                    memcpy(&testG, &G, sizeof(struct gameState)); //restore game state
                    result = buyCard(supplyPos, &testG);
                    if (coins[numCoins] < getCost(supplyPos) || buys[numBuys] < 1 || supplyPos > 16)
                    {
                        //printf("result: %d\n", result);
                        assert(result == -1);
                        continue;
                    }
#if (NOISY_TEST == 1)
                    //printf("result: %d\n", result);                     
                    printf("supplyCount = %d, expected = %d\n", testG.supplyCount[supplyPos], G.supplyCount[supplyPos] - 1);
                    printf("discardCount = %d, expected = %d\n", testG.discardCount[player], G.discardCount[player] + 1);
                    printf("top of discard pile = %d, expected = %d\n", testG.discard[player][testG.discardCount[player]-1], supplyPos);
                    printf("coins = %d, expected = %d\n", testG.coins, G.coins - getCost(supplyPos));
                    printf("buys = %d, expected = %d\n", testG.numBuys, G.numBuys - 1);
                    printf("phase = %d, expected = %d\n", testG.phase, 1);

#endif                    
                    assert(testG.supplyCount[supplyPos] = G.supplyCount[supplyPos] - 1);
                    assert(testG.discardCount[player] == G.discardCount[player] + 1);
                    assert(testG.discard[player][testG.discardCount[player]-1] == supplyPos);
                    assert(testG.coins == G.coins - getCost(supplyPos));
                    assert(testG.numBuys == G.numBuys - 1);
                    assert(testG.phase == 1);
                    
                    //restore values and check that the rest of the game was left intact
                    testG.supplyCount[supplyPos] = G.supplyCount[supplyPos];
                    testG.discardCount[player] = G.discardCount[player];
                    memcpy(&testG.discard[player], &G.discard[player], sizeof(G.discard[player]));
                    testG.coins = G.coins;
                    testG.numBuys = G.numBuys;
                    testG.phase = G.phase;
                    result = memcmp(&testG, &G, sizeof(struct gameState));
                    printf("memcmp result = %d, expected = %d\n", result, 0);
                    assert(result == 0);                    

                }
            }
        }

    }

    //now check if the function fails when you attempt to buy a card with 0 supply
    for (player = 0; player < numPlayers; player++) //for each of the players
    {
        G.whoseTurn = player;
        for (supplyPos = 0; supplyPos < 27; supplyPos++) //for every possible card
        {
            for (numBuys = 0; numBuys < 5; numBuys++) //for each of the 5 predefined number of buys
            {
                G.numBuys = buys[numBuys];
                for (numCoins = 0; numCoins < 5; numCoins++) //for each of the 5 predefined coin values
                {
                    G.coins = coins[numCoins];
                    memcpy(&testG, &G, sizeof(struct gameState)); //restore game state
                    testG.supplyCount[supplyPos] = 0; //set supply to 0
                    result = buyCard(supplyPos, &testG); //this should fail since supply is empty
                    assert(result == -1);
                }
            }
        }
    }


 
    printf("All tests passed!\n");

    return 0;
}
