/* -----------------------------------------------------------------------
 * Faye Yao
 * CS 362
 * smithy card Unit Test
 * 
 * This is a unit test for smithycardtest for Dominion. We randomize the 
 * cards in the deck, discard, and hand, as well as the count for them.
 * We keep the ranges for discard/deck between 3-MAX_DECK, as we need at
 * least 3 cards to draw from. The randomized handCount should be anywhere 
 * between 1-MAX_HAND - 3.
 *
 * We test for the following:
 * 1) Does smithy draw three cards successfully? Are the three cards in the
 * player's hand?
 * 2) Is the deckCount/discardCount correctly adjusted for just THAT player 
 * that drew three cards?
 * 3) Are they any incorrect state changes for other players or otherwise
 * in the gameState that should not occur?
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
    int j, zero, p, r, randomHandCount, randomDeckCount, randomDiscardCount;
    int seed = floor(Random() * 1000);
    int numPlayer = 4; // we can reasonably expect the max players to be 4
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, copyG;

    srand(time(NULL));

    printf ("TESTING playSmithy:\n");
    printf("---------------------------------\n");
    printf("Test if each player 1 through 4 can play Smithy correctly.\n");
    for (p = 0; p < numPlayer; p++)
    {
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        printf("Setting up gameState so player %i can play Smithy.\n", p+1);
        printf("---------------------------------\n");
        G.whoseTurn = p;
        memset(G.deck[p], 0, sizeof(int) * MAX_DECK);
        memset(G.discard[p], 0, sizeof(int) * MAX_DECK);
        memset(G.hand[p], 0, sizeof(int) * MAX_HAND);
        randomDeckCount = rand() % (MAX_DECK + 1 - 2) + 2;
        randomDiscardCount = rand() % (MAX_DECK + 1 - 2) + 2;
        // roll a random hand count somewhere between 2 - (deckCount + discardCount - 3)
        randomHandCount = rand() % ((randomDeckCount + randomDiscardCount - 3) + 1 - 2) + 2;
        G.deckCount[p] = randomDeckCount;
        G.discardCount[p] = randomDiscardCount;
        G.handCount[p] = randomHandCount;

        for (j = 0; j < MAX_HAND; j++) {
            G.hand[p][j] = -1;
        }

        for (j = 0; j < randomDeckCount; j++)
        {
            int card = rand() % treasure_map;
            G.deck[p][j] = card;
        }
        for (j = 0; j < randomDiscardCount; j++)
        {
            int card = rand() % treasure_map;
            G.discard[p][j] = card;
        }
        for (j = 0; j < randomHandCount; j++)
        {
            int card = rand() % treasure_map;
            G.hand[p][j] = card;
        }
        int smithyPos = rand() % randomHandCount;
        G.hand[p][smithyPos] = smithy;
        memcpy(&copyG, &G, sizeof(struct gameState));
        cardEffect(smithy, 0, 0, 0, &G, smithyPos, &zero);
        printf("Random set-up done!\n");
        printf("Checking if players drew the right amount of cards ... \n");
        if (G.handCount[p] != randomHandCount + 3)
        {
            printf("Player did not draw three cards successfully for handCount. Expected: %i, Actual: %i\n", randomHandCount + 3, G.handCount[p]);
        }
        // if the first three cards in their hand are still -1, then they didn't draw a card for
        // one of those slots
        printf("Checking player's hand contents ... \n");
        for (j = randomHandCount; j < randomHandCount + 3; j++)
        {
            if (G.hand[p][j] == -1)
            {
                printf("Player did not draw a card successfully in their hand at position %i. Value at position: %i\n", j, G.hand[p][j]);
            }
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
        // we don't check for numActions difference here because it's outside of the process of 
        // cardEffect 
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
    printf("\nAll tests done for smithyCard!\n");
    return 0;
}