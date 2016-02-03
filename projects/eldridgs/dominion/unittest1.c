#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define Random rand

int checkUpdateCoins (int p, struct gameState *post, int bon) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

    int r = updateCoins (p, post, bon);

    //update coin count to indicate bonus coins
    pre.coins = bon;
    int i;
    for ( i = 0; i < 5; i++ ) {
        if ( pre.hand[p][i] == copper ){
            pre.coins += 1;
        }
        else if ( pre.hand[p][i] == silver ){
            pre.coins += 2;
        }
        else if ( pre.hand[p][i] == gold ) {
            pre.coins += 3;
        }
    }

    assert (r == 0);

    assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int main () {
    int x;
    struct gameState G;
    //test 1000 times
    for (x=0; x < 1000; x++){
        //0 to 15 bonus coins
        int bon = floor(Random() * 16);
        int cardinhand = floor(Random() * 4);

        int p = floor(Random() * 2);
        int i;
        for (i = 0; i < 5; i++) {
            //not a treasure card
            if (cardinhand == 0){
                    G.hand[p][i] = 0;
            }
            else if (cardinhand == 1){
                G.hand[p][i] = copper;
            }
            else if (cardinhand == 2){
                G.hand[p][i] = silver;
            }
            else if (cardinhand == 3){
                G.hand[p][i] = gold;
            }
        }
        checkUpdateCoins(p, &G, bon);
    }
    return 0;
}
