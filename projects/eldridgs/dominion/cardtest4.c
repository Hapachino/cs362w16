#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define Random rand

int checkGreatHall (struct gameState *post, int p, int handP) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

    int r = pGreatHall(post, p, handP);

    //draw card is draw one card and add one action
    drawCard(p, &pre);
    pre.numActions++;
    //discard great hall
    discardCard(handP, p, &pre, 0);

    assert (r == 0);

    assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
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
            if (G.hand[p][i] == great_hall){
                handP = i;
                checkGreatHall (&G, p, handP);
            }
        }
    }
    return 0;
}
