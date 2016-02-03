/* -----------------------------------------------------------------------
 * Faye Yao
 * CS 362
 * updateCoins Unit Test
 * 
 * This updateCoins test uses random testing in order to test whether 
 * randomly generated coins in the player's hand is counted correctly.
 *
 * We test this with multiple players, and differing hand counts. We also 
 * test each expected value for each player separately, so we also test
 * that one player's value doesn't affect another player's expected value.
 *
 * We test randomly the following:
 *
 * 1) Does updateCoins update coins properly for each player?
 * 2) Does updateCoins influence any other players' correct coin values
 * when we count another player's coins?
 * 3) Does updateCoins reset coin count successfully for each player when
 * we check coin values player by player?
 * 4) Does updateCoins successfully account for cards that are not 
 * coppers, silvers, or golds? 
 * 5) What if the hand doesn't have a single currency card?
 * 6) Is the game state at all changed other than the players' hand 
 * and possibly the coins attribute because of updateCoins?
 * -----------------------------------------------------------------------
 */

#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>
#include "compareStates.h"

 // generate a random coin, either a copper, silver, gold, or some card that has no value
int randomCoin() {
    // generate a random int between 1-100
    int random = rand() % 100 + 1;
    if (random <= 25)
        return copper;
    else if (random <= 50)
        return silver;
    else if (random <= 75)
        return gold;
    else
        return 0;
}

// return the expected value of the coin, if it's not a copper/silver/gold we return 0
int expectedVal(int coin) {
    if (coin == copper)
        return 1;
    else if (coin == silver)
        return 2;
    else if (coin == gold)
        return 3;
    else
        // we got some value we weren't expecting, return 0
        return 0;
}

int main() {
    PutSeed(-1);
    int i, j, k, r; // loop counter vars
    int seed = floor(Random() * 1000);
    int numPlayer = 4; // we can reasonably expect the max players to be 4
    int maxBonus = 10;
    int cards[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    struct gameState copyG;

    srand(time(NULL));

    printf("We perform random tests to see if updateCoins works by giving each player a random amount of coins up to MAX_HAND.\n");
    printf ("TESTING updateCoins:\n");
    for (i = 0; i < 1000; i++)
    {
        printf("\nRANDOM TEST %i STARTING\n", i + 1);
        printf("-------------------------------\n");
        int expected_values[numPlayer];
        memset(&copyG, 23, sizeof(struct gameState)); // clear the copy game state
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, cards, seed, &G); // initialize a new game
        memcpy(&copyG, &G, sizeof(struct gameState)); // copy the state of our game
        for (k = 0; k < numPlayer; k++)
        {
            G.handCount[k] = MAX_HAND; // set the number of cards on hand
            int expected_val = 0;
            // generate random coins for the handcount for the player
            for (j = 0; j < MAX_HAND; j++)
            {
                // it's possible to get NO coins in our hand as well
                int coin;
                coin = randomCoin();
                expected_val += expectedVal(coin);
                G.hand[k][j] = coin;
            }
            expected_values[k] = expected_val;
        }
        for (k = 0; k < numPlayer; k++) 
        {
            int bonus = rand() % maxBonus + 1;
            updateCoins(k, &G, bonus);
            // is the expected value what updateCoins says our coins are?
            printf("Player %d G.coins = %d, expected = %d, bonus=%d\n", k + 1, G.coins, expected_values[k] + bonus, bonus);

            if (G.coins != expected_values[k] + bonus)
            {
                printf("ERROR! Was not equal.\n");

            }
            printf("Testing if Player %d deck values have changed at all ... (they shouldn't)\n", k+1);
            if (cmpDeckCount(&G, &copyG, k))
                printf("Deck Count has changed between copied and modified game state!\n");
            if (cmpDiscard(&G, &copyG, k))
                printf("Discard deck has changed between copied and modified game state!\n");
            if (cmpDiscardCount(&G, &copyG, k))
                printf("Discard count has been changed between copied and modified game state!\n");
            if (cmpDeck(&G, &copyG, k))
                printf("Deck has changed between copied and modified game state!\n");
        }
        printf("Testing general game state variables if they've been changed ...\n");
        printf("This will test to see if our copied game state before we performed updateCoins is equal to the modified game state.\n");
        
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
        if (cmpSupplyCount(&G, &copyG))
            printf("SupplyCount has changed between copied and modified game state!\n");
        printf("Done checking game states.\n");
    }
    printf("\nAll tests done for updateCoins!\n");

    return 0;
}
