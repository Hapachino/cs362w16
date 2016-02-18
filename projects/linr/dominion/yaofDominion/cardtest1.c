/* -----------------------------------------------------------------------
 * Faye Yao
 * CS 362
 * Adventurer Card Unit Test
 * 
 * This is a unit test for the adventurer card in Dominion.
 *
 * We test for:
 * 1) Does the adventurer keep drawing from the deck until the player
 * that played it has two treasure cards?
 * 2) Does it successfully change the deck/discard state for only the player
 * that played the card?
 * 3) Is the rest of game state intact? No other states should change except
 * the player that played the adventurer.
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
    int i, j;
    int seed = floor(Random() * 1000);
    int numPlayer = 4; // we can reasonably expect the max players to be 4
    int p, r;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, copyG;

    printf ("TESTING playAdventurer:\n");
    printf("---------------------------------\n");
    printf("Test if each player 1 through 4 can play Adventurer correctly.\n");
    for (p = 0; p < numPlayer; p++)
    {
        printf("Testing if Player %i can playAdventurer properly.\n", p + 1);
        printf("---------------------------------\n");
        memset(&G, 23, sizeof(struct gameState));   // clear the game state
        r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
        G.whoseTurn = p;
        G.deckCount[p] = 0; 
        memset(G.deck[p], 0, sizeof(int) * MAX_DECK);
        G.discardCount[p] = MAX_DECK;
        memset(G.discard[p], 0, sizeof(int) * MAX_DECK);
        memset(G.hand[p], 0, sizeof(int) * MAX_HAND);
        G.deck[p][MAX_DECK - 1] = copper;
        G.deck[p][MAX_DECK - 2] = gold;
        G.discard[p][MAX_DECK - 1] = copper;
        G.discard[p][MAX_DECK - 2] = gold;
        // set the player's hand to be "empty", with all -1 values
        for (j = 0; j < MAX_HAND; j++)
        {
            G.hand[p][j] = -1;
        }
        G.handCount[p] = 1;
        G.hand[p][0] = adventurer;
        memcpy(&copyG, &G, sizeof(struct gameState));
        printf("Test without any cards in the deck, but a full discard deck to see if shuffle will work.\n");
        cardEffect(adventurer, 0, 0, 0, &G, 0, &i);
        playAdventurer(&G);
        printf("Checking if player drew two treasure cards successfully ...\n");
        if (G.handCount[p] != 2)
        {
            printf("Player did not draw two treasure cards successfully. Expected handCount: 2, Actual handCount: %i\n", G.handCount[p]);
        }
        // if the first three cards in their hand are still -1, then they didn't draw a card for
        // one of those slots
        // we check the last two cards to see if it's either the copper or gold that we should've drawn from the
        // deck
        printf("Checking player hand contents ...\n");
        for (j = 0; j < G.handCount[p]; j++)
        {
            if (!(G.hand[p][j] == copper || G.hand[p][j] == gold))
                printf("Player did not draw a copper or gold card that we put into the deck. Drew a card that wasn't a treasure card at position %i! Card Value: %i\n", j, G.hand[p][j]);
            if (G.hand[p][j] == -1)
            {
                printf("Player did not draw a treasure card successfully in their hand at position %i.\n", j);
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
        printf("This will test to see if our copied game state before we performed playAdventurer is equal to the modified game state.\n");
        
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
    printf("\nAll tests done for playAdventurer!\n");
    return 0;
}