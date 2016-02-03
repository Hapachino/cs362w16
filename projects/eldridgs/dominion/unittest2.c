#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define Random rand

int checkDiscardCard(int handp, int p, struct gameState *post, int trashF)
{
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));
    int r = discardCard(handp, p, post, trashF);

    //make my own version of discard card
    //must have cards in hand to discard
    if (pre.handCount[p] > 0){
        //card is trashed
        if (trashF == 1){
        //card is not added to cards played, but handcount does go down
        pre.hand[p][handp] = pre.handCount[p];
        pre.handCount[p]--;
        }
        //card not trashed
        else if (trashF == 0){
            //card at hand position added to played cards
            pre.playedCards[pre.playedCardCount] = pre.hand[p][handp];
            pre.playedCardCount++;
            //move last card in hand to replace played card
            pre.hand[p][handp] = pre.handCount[p];
            //handcount goes down
            pre.handCount[p]--;
        }
    }
    assert (r == 0);

    assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int main () {
    int x;
    struct gameState G;
    //run test 1000 times
    for (x=0; x < 1000; x++) {
        int p = floor(Random() * 2);
        //trash flag can be 0 or 1
        int trashF = floor(Random() * 2);

        G.deckCount[p] = floor(Random() * MAX_DECK);
        int handp = floor(Random() * MAX_HAND);
        checkDiscardCard(handp, p, &G, trashF);
    }
    return 0;
}
