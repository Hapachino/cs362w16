/* -----------------------------------------------------------------------
 * Faye Yao
 * CS 362
 * isGameOver Unit Test
 * 
 * This is a unit test for isGameOver for Dominion.
 *
 * We test for:
 * 1) Does isGameOver actually return the right values if the supplyCount is
 * still above 0 for all cards? What about if a few of them are?
 * 2) Does it accurately return the right values if varying combinations of
 * supplyCounts are at 0 (if there's 3 supply counts at 0?)
 * 3) Does it modify any part of the gameState that it shouldn't? It shouldn't
 * modify anything as it is purely counting if 3 supplyCounts are at 0.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include "compareStates.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main() {
    PutSeed(-1);
    int i, r, j, gameVal, zeros; // loop counter vars
    int numPlayer = 4; // we can reasonably expect the max players to be 4
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, copyG;
    int provinceAmount = 12;
    int seed = floor(Random() * 1000);

    srand(time(NULL));
    printf ("TESTING isGameOver():\n");
    // test if isGameOver registers as 1 if we set the supply count for province to 0
    memset(&G, 23, sizeof(struct gameState));   // clear the game state
    r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
    memcpy(&copyG, &G, sizeof(struct gameState)); // save the game state before we start checking isGameOver
    G.supplyCount[province] = 0;
    printf("Force province card amount to be 0 to see if isGameOver triggers.\n");
    if (isGameOver(&G) != 1)
    {
        printf("province card amount is 0, but isGameOver was not 1.\n");
    }
    printf("Running 10000 random tests for our province card count to verify isGameOver is 1 when province amount is 0.\n");
    for (i = 0; i < 10000; i++)
    {
        int provinceCardAmount = rand() % provinceAmount;
        G.supplyCount[province] = provinceCardAmount;
        if (provinceCardAmount == 0)
        {
            if (isGameOver(&G) != 1)
            {
                printf("province card amount is 0, but isGameOver was not 1.\n");
            }
        }
    }
    printf("Done with Province card random testing.\n");
    printf("Running 10000 random tests for randomized supplyCounts to see if we can detect when the game should be over.\n");
    printf("NOTE: We exclude randomizing province card supply counts to test purely if isGameOver can detect a game over from other 0 supplyCounts.\n");
    G.supplyCount[province] = 1; // set it to at least 1 so that isGameOver will never be triggered because of 0 provinces
    // we test whether we can get the game over state by randomly generating supply counts
    // and we also count how many supply counts we get. We then check if isGameOver returns
    // the correct value
    for (i = 0; i < 10000; i++)
    {
        zeros = 0;
        for (j = 0; j < 25; j++)
        {
            // do not touch the province supplyCount, this can throw off our results if
            // we get a 0 for province
            if (j == province)
                continue;
            int randomVal = rand() % 60;
            if (randomVal == 0)
                zeros += 1;
            G.supplyCount[j] = randomVal;
        }
        gameVal = isGameOver(&G);
        if (zeros < 3 && gameVal == 1)
        {
            printf("Iteration %i: Supply count was less than 3 but isGameOver returned 1!\n", i);
        }
        if (zeros > 2 && gameVal == 0)
        {
            printf("Iteration %i: Supply count was at least 3 yet isGameOver did not return 1.\n", i);
        }
    }
    for (j = 0; j < numPlayer; j++)
    {
        if (cmpDeckCount(&G, &copyG, j))
            printf("Deck Count has changed between copied and modified game state!\n");
        if (cmpDiscard(&G, &copyG, j))
            printf("Discard deck has changed between copied and modified game state!\n");
        if (cmpDiscardCount(&G, &copyG, j))
            printf("Discard count has been changed between copied and modified game state!\n");
        if (cmpDeck(&G, &copyG, j))
            printf("Deck has changed between copied and modified game state!\n");
    }
    printf("Testing general game state variables if they've been changed ...\n");
    printf("This will test to see if our copied game state before we performed isGameOver is equal to the modified game state.\n");
    // NOTE: we do exclude testing for supplyCount comparisons, because obviously we have changed that state
    if (cmpPlayedCards(&G, &copyG))
        printf("playedCards has changed between copied and modified game state!\n");
    if (cmpPlayedCardCount(&G, &copyG))
        printf("playedCardCount has changed between copied and modified game state!\n");
    if (cmpPhase(&G, &copyG))
        printf("phase has changed between copied and modified game state!\n");
    if (cmpWhoseTurn(&G, &copyG))
        printf("WhoseTurn has changed between copied and modified game state!\n");
    if (cmpNumActions(&G, &copyG))
        printf("numActions has changed between copied and modified game state!\n");
    if (cmpOutpostPlayed(&G, &copyG))
        printf("OutpostPlayed has changed between copied and modified game state!\n");
    if (cmpNumPlayers(&G, &copyG))
        printf("NumPlayers has changed between copied and modified game state!\n");
    if (cmpNumBuys(&G, &copyG))
        printf("NumBuys has changed between copied and modified game state!\n");
    if (cmpOutpostTurn(&G, &copyG))
        printf("OutpostTurn has changed between copied and modified game state!\n");
    printf("Done checking game states.\n");
    printf("\nAll tests done for isGameOver!\n");
    return 0;
}