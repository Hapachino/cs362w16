#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
#define TESTFUNCTION "discardCard"

int main() {
    int seed = 1000;
    int numPlayers = 4;
    int handNum, handPos, player, trashFlag, result;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;
    initializeGame(numPlayers, k, seed, &G);
    int hands[3][15] = {{copper, gold, village, estate, smithy}, {gold}, {silver, province, copper, copper, feast, baron, remodel, copper, smithy, province, duchy, estate, copper, mine, gardens}};
    int handCounts[3] = {5, 1, 8};

    printf("\n----------------- Testing Function: %s ----------------\n", TESTFUNCTION);
    memcpy(&testG, &G, sizeof(struct gameState));

    for (player = 0; player < numPlayers; player++) //for each of the players
    {
        G.whoseTurn = player;        
        for (handNum = 0; handNum < 3; handNum++) //for each of the 3 predefined hands
        {
            memcpy(&G.hand[player], &hands[handNum], sizeof(hands[handNum])); //load new hand
            G.handCount[player] = handCounts[handNum]; //load new handCount
            for (handPos = 0; handPos < handCounts[handNum]; handPos++) //for every card in the hand
            {
                for (trashFlag = 0; trashFlag < 2; trashFlag ++)
                {
                    memcpy(&testG, &G, sizeof(struct gameState)); //restore game state
                    discardCard(handPos, player, &testG, trashFlag);
#if (NOISY_TEST == 1)                    
                    printf("handCount = %d, expected = %d\n", testG.handCount[player], G.handCount[player] - 1);
#endif
                    assert(testG.handCount[player] == handCounts[handNum] - 1);
#if (NOISY_TEST == 1)
                    printf("playedCardCount = %d, expected = %d\n", testG.playedCardCount, G.playedCardCount + 1 - trashFlag);
#endif                    
                    assert(testG.playedCardCount == G.playedCardCount + 1 - trashFlag);

                    if (trashFlag == 0) //if it wasn't trashed, it should be in the played cards pile
                    {
#if (NOISY_TEST == 1)                        
                        printf("playedCard = %d, expected = %d\n", testG.playedCards[0], hands[handNum][handPos]);
#endif                        
                        assert(testG.playedCards[0] == hands[handNum][handPos]);
                    }

                    //restore values and check that the rest of the game was left intact
                    testG.handCount[player] = G.handCount[player];
                    testG.playedCardCount = G.playedCardCount;
                    memcpy(&testG.hand[player], &G.hand[player], sizeof(G.hand[player]));
                    if (trashFlag == 0)
                    {
                        memcpy(&testG.playedCards, &G.playedCards, sizeof(G.playedCards));
                    }
                    result = memcmp(&testG, &G, sizeof(struct gameState));
#if (NOISY_TEST == 1)                    
                    printf("memcmp result = %d, expected = %d\n", result, 0);
#endif                          
                    assert(result == 0);



                }
            }
        }
    }
 
    printf("All tests passed!\n");

    return 0;
}
