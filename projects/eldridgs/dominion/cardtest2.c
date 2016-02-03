#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define Random rand

int checkAdventurer (struct gameState *post, int p, int drawntreasure, int temphand[MAX_HAND], int cardDrawn, int z) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

    int r = pAdventurer (post, p, drawntreasure, temphand[MAX_HAND], cardDrawn, z);
    int i;
    int c;

    //continue adventure card until two treasure cards are found
    while (drawntreasure < 2){
       //shuffle discard pile if deck is 0
        if(pre.deckCount == 0){
            shuffle(p, &pre);
        }
        drawCard(p, &pre);
        c = pre.handCount;
        //check if treasure card
        if (pre.hand[p][c] == copper || pre.hand[p][c] == silver || pre.hand[p][c] == gold){
            drawntreasure++;
        }
        //if not treasure add to temp hand to be discarded
        else {
        //add to temphand
        temphand[z] = pre.hand[p][c];
        //take card out of player's actual hand
        pre.hand[p][c]--;
        z++;
        }
    }
    //discard temp hand
    for (i=0; i<z; i++){
        discardCard(i, p, &pre, 0);
    }
    assert (r == 0);

    assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int main () {
    int x;
    struct gameState G;
    int drawntreasure = 0;
    int z = 0;
    int cardDrawn = 0;
    //test 1000 times
    for (x=0; x < 1000; x++){
        //0 to 15 bonus coins
        int bon = floor(Random() * 16);
        int cardinhand = floor(Random() * 4);

        int p = floor(Random() * 2);

        int temphand[MAX_HAND] = {0};
        int i;

        //if adventurer in hand check
        for(i=0; i<G.handCount; i++){
            if (G.hand[p][i] == adventurer){
                checkAdventurer(&G, p, drawntreasure, temphand[MAX_HAND], cardDrawn, z);
            }
        }
    }
    return 0;
}
