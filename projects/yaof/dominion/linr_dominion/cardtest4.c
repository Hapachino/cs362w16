/* -----------------------------------------------------------------------
 * Faye Yao
 * CS 362
 * Village Card Unit Test
 * 
 * This is a unit test for the village card in Dominion.
 *
 * We test for:
 * 1) Does the Village card properly change the deck/hand/discard state for
 * drawing a card to the player's hand?
 * 2) Does it give the proper number of actions to the player who played it?
 * 3) Does the player get one card to their hand after playing it?
 * 4) Does it change any other player's gameState inappropriately? It also
 * shouldn't change any of the victory card or kingdom card piles.
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
    int j, p, r, prevActions, zero;
    int seed = floor(Random() * 1000);
    int numPlayer = 4; // we can reasonably expect the max players to be 4
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, copyG;

    printf ("TESTING playVillage:\n");
    printf("---------------------------------\n");
    printf("Test if each player 1 through 4 can play Village correctly.\n");
    for (p = 0; p < numPlayer; p++)
    {
        printf("Testing player %i playing Village.\n", p + 1);
        printf("---------------------------------\n");
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.whoseTurn = p;
        G.deckCount[p] = MAX_DECK; 
        memset(G.deck[p], 0, sizeof(int) * MAX_DECK);
        G.discardCount[p] = MAX_DECK;
        memset(G.discard[p], 0, sizeof(int) * MAX_DECK);
        memset(G.hand[p], 0, sizeof(int) * MAX_HAND);
        // set the player's hand to be "empty", with all -1 values
        for (j = 0; j < MAX_HAND; j++)
        {
            G.hand[p][j] = -1;
        }
        G.handCount[p] = 1;
        G.hand[p][0] = village;
        memcpy(&copyG, &G, sizeof(struct gameState));
        prevActions = G.numActions;
        cardEffect(village, 0, 0, 0, &G, 0, &zero);
        printf("Checking if Player drew a card successfully ... \n");
        if (G.handCount[p] != 1)
        {
            printf("Player did not draw one card successfully.\n");
        }
        // if the first three cards in their hand are still -1, then they didn't draw a card for
        // one of those slots
        printf("Checking player hand contents ... \n");
        for (j = 0; j < G.handCount[p]; j++)
        {
            if (G.hand[p][j] != 0)
            {
                printf("Player did not draw a card successfully in their hand at position %i. Value at position: %i\n", j, G.hand[p][j]);
            }
        }
        printf("Checking if Player has +2 to num actions...\n");
        if (G.numActions != prevActions + 1)
        {
            printf("Village Card did not add +2 Actions. Current numActions: %i, Expected numActions: %i\n", G.numActions, prevActions + 1);
        }
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
        printf("Testing general game state variables if they've been changed ...\n");
        printf("This will test to see if our copied game state before we performed villageCardTest is equal to the modified game state.\n");
        
        if (cmpPlayedCards(&G, &copyG) == 0)
            printf("playedCards hasn't changed between copied and modified game state!\n");
        if (cmpPlayedCardCount(&G, &copyG) == 0)
            printf("playedCardCount hasn't changed between copied and modified game state!\n");
        if (cmpPhase(&G, &copyG))
            printf("phase has changed between copied and modified game state!\n");
        if (cmpWhoseTurn(&G, &copyG))
            printf("WhoseTurn has changed between copied and modified game state!\n");
        if (cmpNumActions(&G, &copyG) == 0)
            printf("numActions hasn't changed between copied and modified game state!\n");
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
    printf("\nAll tests done for playVillage!\n");
    return 0;
}