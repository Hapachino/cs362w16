/* -----------------------------------------------------------------------
 * Faye Yao
 * CS 362
 * drawCard Unit Test
 * 
 * This drawCardTest tests for the following:
 *
 * 1) Does drawCard successfully draw a Card and change the deck/discard/hand
 * state for ONLY the player that draws a card?
 * 2) Does drawCard change any other player's game state as a result? It shouldn't.
 * 3) Does drawCard successfully shuffle if the current deck is empty?
 * 4) Does drawCard exit successfully if we have no cards in the discard deck AND
 * the deck?
 * 5) Does drawCard update the current player's game state correctly?
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
    int i, j, curHandPos; // loop counter vars
    int seed = floor(Random() * 1000);
    int numPlayer = 4; // we can reasonably expect the max players to be 4
    int p, g, r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, copyG;

    srand(time(NULL));

    printf ("TESTING drawCard():\n");
    printf("---------------------------------\n");
    for (p = 0; p < numPlayer; p++)
    {
        printf("Testing drawCard for player %i.\n", p+1);
        printf("---------------------------------\n");
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        memset(&copyG, 23, sizeof(struct gameState));
        g = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        // make sure that we test conditions for where we can't draw a card
        G.deckCount[p] = 0;
        G.discardCount[p] = 0;
        G.handCount[p] = 0;
        memcpy(&copyG, &G, sizeof(struct gameState)); // hold the previous state of our game state before we draw
        r = drawCard (p, &G);
        printf("Testing drawCard with deckCount, discardCount, and handCount at 0 for player %i. Should return -1.\n", p);
        if (r != -1)
        {
            printf("Error! drawCard should've returned -1, but it was %i.\n", r);
        }
        if (G.handCount[p] > 0)
            printf("Error! We shouldn't have any cards in our hand at this point.\n");
        G.deckCount[p] = MAX_DECK-5; 
        memset(G.deck[p], 0, sizeof(int) * MAX_DECK);
        G.discardCount[p] = MAX_DECK;
        memset(G.discard[p], 0, sizeof(int) * MAX_DECK);
        G.handCount[p] = 0;
        memset(G.hand[p], 0, sizeof(int) * MAX_HAND);
        // let's now try and draw as many cards as we can
        printf("Now testing to draw all of the cards we possibly can from the deck.\n");
        printf("Since there aren't enough cards in the deck, we will also test shuffle for the last four card draws ...\n");
        curHandPos = 0;
        for (i = 0; i < MAX_HAND; i++)
        {
            G.hand[p][i] = -1;
        }
        for (i = 0; i < MAX_HAND; i++)
        {
            r = drawCard(p, &G);
            curHandPos++;
            if (r == -1)
                printf("Error! We were unable to draw a card from the deck for card #%i.\n", i);
            if (G.handCount[p] < curHandPos)
                printf("Hand position is behind what it should be. Expected: %i, Actual: %i\n", curHandPos, G.handCount[p]);
            if (G.hand[p][curHandPos-1] < 0)
                printf("Error! Nothing was drawn at the current hand position. Did not actually draw a card.\n");
        }
        printf("Now testing gameState for all players that did not draw cards and the kingdom/victory card piles.\n");
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
        printf("This will test to see if our copied game state before we performed drawCardTest is equal to the modified game state.\n");
        
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
    printf("\nDone testing drawCard!\n");
    return 0;
}