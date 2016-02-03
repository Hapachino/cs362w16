#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int getCardScore(int card, struct gameState *state, int currentPlayer)
{
    if (card == curse) 
        return -1;
    if (card == estate) 
        return 1;
    if (card == duchy) 
        return 3;
    if (card == province) 
        return 6;
    if (card == great_hall) 
        return 1;
    if (card == gardens) { 
        int fullDeck;
        fullDeck = state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer];
        return ( fullDeck / 10 ); 
    }
    return 0;
}

int main() {
    srand(time(NULL));
    int p, i;
    int score;
    int handRandom, deckRandom, discardRandom;
    int numPlayer = 2;
    int seed = rand() % 9999;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    
    struct gameState G;
    
    printf ("TESTING scoreFor():\n");
    memset(&G, 23, sizeof(struct gameState));
    assert(initializeGame(numPlayer, k, seed, &G) == 0);
    
    for (p = 0; p < numPlayer; p++) {
        score = 0;
        handRandom = rand() % MAX_HAND;
        G.handCount[p] = handRandom;
        for (i = 0; i < handRandom; i++) {
            G.hand[p][i] = rand() % 27;
        }
        
        deckRandom = rand() % MAX_DECK;
        G.deckCount[p] = deckRandom;
        for (i = 0; i < deckRandom; i++) {
            G.deck[p][i] = rand() % 27;
        }
 
        discardRandom = rand () % MAX_DECK;
        G.discardCount[p] = discardRandom;
        for (i = 0; i < discardRandom; i++) {
            G.discard[p][i] = rand() % 27;
        }
        //sum up the score of all cards
        for (i = 0; i < handRandom; i++) {
            score += getCardScore(G.hand[p][i], &G, p);
        }

        for (i = 0; i < deckRandom; i++) {
            score += getCardScore(G.deck[p][i], &G, p);
        }

        for (i = 0; i < discardRandom; i++) {
            score += getCardScore(G.discard[p][i], &G, p);
        }
        if (scoreFor(p, &G) == score){
            printf("Testing scoreFor() passed! for user: %d\n", p);
        } 
        else {
            printf("Testing scoreFor() failed for user: %d \n", p);
        }
    }
 
    return 0;
}