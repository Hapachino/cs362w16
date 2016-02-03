#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define Random rand

int checkVillage (struct gameState *post, int p, int handP) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

    int r = pvillage(post, p, handP);

    //village is draw one card and get 2 more actions
    drawCard(p, &pre);
    pre.numActions = pre.numActions + 2;
    //discard village card
    discardCard(handP, p, &pre, 0);

    assert (r == 0);

    assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int pVillage(struct gameState *state, int currentPlayer, int handPos){
//+1 Card
            drawCard(currentPlayer, state);

            //+2 Actions
            state->numActions = state->numActions + 2;

            //discard played card from hand
            discardCard(handPos + 1, currentPlayer, state, 0);
            return 0;
}

int main () {
    int x;
    int i;
    struct gameState G;
    int handP;
    //test 1000 times
    for (x=0; x < 1000; x++){
        int p = floor(Random() * 2);\
        //start with 0 to 10 actions
        G.numActions = floor(Random() * 11);
        //if village is in hand
        for(i=0; i<G.handCount; i++){
            if (G.hand[p][i] == village){
                handP = i;
                checkVillage(&G, p, handP);
            }
        }
    }
    return 0;
}
