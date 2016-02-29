#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define TESTFUNCTION "gainCard"

int main() {
    int seed = 1000;
    int numPlayers = 4;
    int player, toFlag, supplyPos, result;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    initializeGame(numPlayers, k, seed, &G);


    printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);

    for (player = 0; player < numPlayers; player++) //for each of the players
    {
        G.whoseTurn = player;        
        for (supplyPos = 0; supplyPos < 27; supplyPos++) //for each of the 27 cards
        {
            for (toFlag = 0; toFlag < 3; toFlag++) //for each of the 3 possible destinations
            {
                memcpy(&testG, &G, sizeof(struct gameState)); //restore game state
                result = gainCard(supplyPos, &testG, toFlag, player);
                if (supplyPos > 16) //if invalid supplyPos, function should return -1
                {
                    assert(result == -1);
                    continue;
                }
                else
                {
                    assert(result == 0);
                }
                //ensure correct count is incremented and card is added to correct position of correct pile.
                if(toFlag == 2)
                {
#if (NOISY_TEST == 1)                    
                    printf("handCount = %d, expected = %d\n", testG.handCount[player], G.handCount[player] + 1);
                    printf("last card of hand = %d, expected = %d\n", testG.hand[player][testG.handCount[player] - 1], supplyPos);
#endif
                    assert(testG.handCount[player] == G.handCount[player] + 1);
                    assert(testG.hand[player][testG.handCount[player] - 1] == supplyPos);   

                }    
                else if(toFlag == 1)
                {
#if (NOISY_TEST == 1)                    
                    printf("deckCount = %d, expected = %d\n", testG.deckCount[player], G.deckCount[player] + 1);
                    printf("last card of deck = %d, expected = %d\n", testG.deck[player][testG.deckCount[player] - 1], supplyPos);                    
#endif
                    assert(testG.deckCount[player] == G.deckCount[player] + 1);
                    assert(testG.deck[player][testG.deckCount[player] - 1] == supplyPos);
                }
                else if(toFlag == 0)
                {
#if (NOISY_TEST == 1)                    
                    printf("discardCount = %d, expected = %d\n", testG.discardCount[player], G.discardCount[player] + 1);
                    printf("last card of discard = %d, expected = %d\n", testG.discard[player][testG.discardCount[player] - 1], supplyPos);
#endif
                    assert(testG.discardCount[player] == G.discardCount[player] + 1);
                    assert(testG.discard[player][testG.discardCount[player] - 1] == supplyPos);
                }
#if (NOISY_TEST == 1)                    
                //make sure supply was decremented correctly
                printf("supplyCount = %d, expected = %d\n", testG.supplyCount[supplyPos], G.supplyCount[supplyPos] - 1);
                assert(testG.supplyCount[supplyPos] == G.supplyCount[supplyPos] - 1);
#endif                
                //restore values and check that the rest of the game was left intact
                if (toFlag == 2)
                {
                    testG.handCount[player] = G.handCount[player];
                    memcpy(&testG.hand[player], &G.hand[player], sizeof(G.hand[player]));
                }
                else if (toFlag == 1)
                {
                    testG.deckCount[player] = G.deckCount[player];
                    memcpy(&testG.deck[player], &G.deck[player], sizeof(G.deck[player]));                
                }
                else if (toFlag == 0)
                {
                    testG.discardCount[player] = G.discardCount[player];
                    memcpy(&testG.discard[player], &G.discard[player], sizeof(G.discard[player]));
                }
                testG.supplyCount[supplyPos] = G.supplyCount[supplyPos];
                result = memcmp(&testG, &G, sizeof(struct gameState));
#if (NOISY_TEST == 1)                    
                printf("memcmp result = %d, expected = %d\n", result, 0);
#endif                
                assert(result == 0);                    

            }
        }
       
    }
    for (player = 0; player < numPlayers; player++) //for each of the 4 players
    {
        for (supplyPos = 0; supplyPos < 27; supplyPos++) //for each of the 27 cards
        {
            G.supplyCount[supplyPos] = 0; //set supply to 0
            for (toFlag = 0; toFlag < 3; toFlag++) //for each of the 3 possible destinations
            {
                memcpy(&testG, &G, sizeof(struct gameState)); //restore game state
                result = gainCard(supplyPos, &testG, toFlag, player);
                assert(result == -1); //gainCard should fail and return -1 because supply is empty
            }
        }
    }

                                



 
    printf("All tests passed!\n");

    return 0;
}
