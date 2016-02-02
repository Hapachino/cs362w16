/* -----------------------------------------------------------------------
  updateCoins() Unit Testing file
  Author: James Linnenburger - Oregon State CS362 Spring 2016

  testUnit3: unittest3.c dominion.o rngs.o
 	gcc -0 unittest3 dominion.o rngs.o unittest3.c $(CFLAGS)

 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "compare_gamestates.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "rngs.h"


int statesAreEqual(struct gameState *g1, struct gameState *g2)
{
    int i, j;

    if(g1->numPlayers != g2->numPlayers) return 0;
    for(i = 0; i < treasure_map+1; i++)
        if(g1->supplyCount[i] != g2->supplyCount[i]) return 0;
    for(i = 0; i < treasure_map+1; i++)
        if(g1->embargoTokens[i] != g2->embargoTokens[i]) return 0;
    if(g1->outpostPlayed != g2->outpostPlayed) return 0;
    if(g1->outpostTurn != g2->outpostTurn) return 0;
    if(g1->whoseTurn != g2->whoseTurn) return 0;
    if(g1->phase != g2->phase) return 0;
    if(g1->numActions != g2->numActions) return 01;
    if(g1->coins != g2->coins) return 0;
    if(g1->numBuys != g2->numBuys) return 0;
    for(i = 0; i < MAX_PLAYERS; i++)
    {
        if(g1->handCount[i] != g2->handCount[i]) return 0;
        if(g1->deckCount[i] != g2->deckCount[i]) return 0;
        if(g1->discardCount[i] != g2->discardCount[i]) return 0;

        for(j = 0; j < MAX_HAND; j++)
            if(g1->hand[i][j] != g2->hand[i][j]) return 0;

        for(j = 0; j < MAX_DECK; j++)
            if(g1->deck[i][j] != g2->deck[i][j]) return 0;
    }

    for(i = 0; i < MAX_DECK; i++)
        if(g1->playedCards[i] != g2->playedCards[i]) return 0;

    if(g1->playedCardCount != g2->playedCardCount) return 0;

    return 1;
}
