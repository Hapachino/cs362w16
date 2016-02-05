/* -----------------------------------------------------------------------
 * Faye Yao
 * CS 362
 * Feast Card Unit Test
 * 
 * This is a unit test for the feast card in Dominion.
 *
 * We test for:
 * 1) Does the card discard properly? (the card should go to the discard pile)
 * 2) Do we gain a card that is worth up to 5 value? Does it go to the discard pile?
 * 3) Does it inappropriately change any other game states for any other players?
 * 4) Does it properly change the state for the kingdom/supply piles?
 *
 * We check if feast card works for the following cards: gold, village, and 
 * council room. Gold should not be able to be bought, while the other two should.
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

int main() {
    PutSeed(-1);
    int i, j, zero;
    int seed = floor(Random() * 1000);
    int numPlayer = 4; // we can reasonably expect the max players to be 4
    int p, r, prevSupplyCount;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    int testCards[3] = {gold, village, council_room};
    char * testStr[3] = {"gold", "village", "council room"};
    struct gameState G, copyG;

    printf ("TESTING playFeast():\n");
    printf("---------------------------------\n");
    for (i = 0; i < 3; i++)
    {
        for (p = 0; p < numPlayer; p++) 
        {
            printf("Testing if player %i can buy card '%s' using Feast.\n", p + 1, testStr[i]);
            printf("---------------------------------\n");
            memset(&G, 23, sizeof(struct gameState));   // clear the game state
            r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
            G.whoseTurn = p;
            G.deckCount[p] = MAX_DECK; 
            memset(G.deck[p], 0, sizeof(int) * MAX_DECK);
            G.discardCount[p] = MAX_DECK - 1;
            memset(G.discard[p], 0, sizeof(int) * MAX_DECK);
            memset(G.hand[p], 0, sizeof(int) * MAX_HAND);
            // set the player's hand to be "empty", with all -1 values
            for (j = 0; j < MAX_HAND; j++)
            {
                G.hand[p][j] = -1;
            }
            G.handCount[p] = 1;
            G.hand[p][0] = feast;
            memcpy(&copyG, &G, sizeof(struct gameState));
            prevSupplyCount = G.supplyCount[testCards[i]];
            r = cardEffect(feast, testCards[i], testCards[i], testCards[i], &G, 0, &zero);
            printf("Checking supplyCount and discard pile if card was able to be bought ...\n");
            if ( (prevSupplyCount != G.supplyCount[testCards[i]] + 1) && r != -1)
                printf("Did not properly subtract supplyCount for the bought card, if card is able to be bought. Expected: %i, Actual: %i\n", prevSupplyCount - 1, G.supplyCount[testCards[i]]);
            if ( (G.discard[p][G.discardCount[p]-1] != testCards[i]) && r != -1)
                printf("Did not gain the card in the discard pile. Card value at expected position: %i, Actual: %i\n", testCards[i], G.discard[p][G.discardCount[p] -1]);
            printf("Checking the gameState for all other players to make sure it wasn't modified... \n");
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
        }
        printf("Testing general game state variables if they've been changed ...\n");
        printf("This will test to see if our copied game state before we performed playFeast is equal to the modified game state.\n");
        
        if (cmpPlayedCards(&G, &copyG) == 0)
            printf("playedCards hasn't changed between copied and modified game state!\n");
        if (cmpPlayedCardCount(&G, &copyG) == 0)
            printf("playedCardCount hasn't changed between copied and modified game state!\n");
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
        if (cmpSupplyCount(&G, &copyG) == 0)
            printf("SupplyCount hasn't changed between copied and modified game state! (This should only happen if we couldn't buy the card.)\n");
        printf("Done checking game states.\n");
    }
    printf("\nAll tests done for playFeast!\n");
    return 0;
}