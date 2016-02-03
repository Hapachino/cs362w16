#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define Random rand

int checkSmithy(struct gameState *post, int p, int j, int handP){
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

    int r = pSmithy(post, p, j, handP);

    //smithy adds 3 cards to hand
    for (j=0; j<3; j++){
        drawCard(pre.whoseTurn, &pre);
        pre.handCount[p]++;
    }
    //discard smithy card
    discardCard(handP, p, &pre, 0);

    assert (r == 0);

    assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int pSmithy(struct gameState *state, int currentPlayer, int i, int handPos)
{
    //+3 Cards
            for (i = 0; i < 3; i++)
            {
                drawCard(currentPlayer, state);
                state->numBuys = 5;
            }

            //discard card from hand
            discardCard(handPos, currentPlayer, state, 0);
            return 0;
}

int main () {
    int x;
    int i;
    int p = floor(Random() * 2);
    struct gameState G;
    int handP = -1;
    //test 1000 times
    for (x=0; x < 1000; x++){
        for (i=0; i<G.handCount; i++){
            if (G.hand[p][i] == smithy){
                handP == i;
            }
        }
        //only check smithy if there is a smithy
        if(handP != -1){
            checkSmithy(&G, p, 3, handP);
        }
    }
    return 0;
}
