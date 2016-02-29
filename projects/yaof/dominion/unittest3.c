/* -----------------------------------------------------------------------
 * Faye Yao
 * CS 362
 * scoreFor Unit Test
 * 
 * This unit test for scoreForTest guages how accurately it 
 * counts scores for each player, given if they have a deck/hand count
 * full of the different kind of cards that can add to your victory
 * point value.
 *
 * We test for:
 * 1) Are all of the estate card values counted properly?
 * 2) Are each of the estate cards accounted for? (especially cards like gardens)
 * 3) Is the gameState appropriately changed for just the player? eg. when we add
 * cards to a player's deck/hand, is it just for that player, or are there side effects?
 *
 * We test this by iterating through all possible estate cards worth a score, 
 * filling the player's deck, discard, and hand full of one type of estate card.
 * We test one player at a time and then test if any other players are 
 * affected by running scoreFor.
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

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
    int i, j; // loop counter vars
    int seed = 1000;
    int score, expectedVal;
    int numPlayer = 4; // we can reasonably expect the max players to be 4
    int p, r, handCount, discardCount, deckCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, copyG;
    int maxHandCount = MAX_HAND;
    int maxDiscardCount = MAX_DECK;
    int maxDeckCount = MAX_DECK;
    int estate[6] = {curse, estate, duchy, province, great_hall, gardens};
    char * estateString[6] = {"Curse", "Estate", "Duchy", "Province", "Great Hall", "Gardens"};
    int estateVal[5] = {-1, 1, 3, 6, 1};

    printf ("TESTING scoreForTest:\n");
    printf("---------------------------------\n");
    // test all estate cards and making the player's discard piles, deck piles, and hand piles a card
    // that contributes to the victory point total
    for (i = 0; i < 6; i++)
    {
        printf("TESTING IF ALL CARDS WERE %s\n", estateString[i]);
        printf("---------------------------------\n");
        for (p = 0; p < numPlayer; p++) 
        {
            expectedVal = 0;
            score = 0;
            memset(&G, 23, sizeof(struct gameState));   // clear the game state
            r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
            G.handCount[p] = maxHandCount;
            G.deckCount[p] = maxDeckCount;
            G.discardCount[p] = maxDiscardCount;
            for (handCount = 0; handCount < maxHandCount; handCount++)
            {
                G.hand[p][handCount] = estate[i];
            }
            G.discardCount[p] = maxDiscardCount;
            for (discardCount = 0; discardCount < maxDiscardCount; discardCount++)
            {
                G.discard[p][discardCount] = estate[i];
            }
            for (deckCount = 0; deckCount < maxDeckCount; deckCount++)
            {
                G.deck[p][deckCount] = estate[i];
            }
            memcpy(&copyG, &G, sizeof(struct gameState)); // hold the previous state of our game state before we count scores
            score = scoreFor(p, &G);
            if (i == 5)
            {
                expectedVal = ((maxDeckCount + maxHandCount + maxDiscardCount) / 10) * (maxDiscardCount + maxHandCount + maxDiscardCount);
            }
            else
            {
                expectedVal = ((maxHandCount + maxDeckCount + maxDiscardCount) * estateVal[i]);
            }
            printf("Player %i - Score = %d, expected = %d\n", p + 1, score, expectedVal);
            if (score != expectedVal)
            {
                printf("Error! Score was not equal to expected score.\n");
            }
            printf("Now testing gameState for all other players and the kingdom/victory card piles.\n");
            for (j = 0; j < numPlayer; j++)
            {
                if (j == p)
                    continue;
                printf("Testing if Player %i deck values have changed at all ... (they shouldn't)\n", j + 1);
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
            printf("This will test to see if our copied game state before we performed scoreFor is equal to the modified game state.\n");
            
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
    }
    printf("\nAll scoreFor tests done!\n");

    return 0;
}