#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTFUNCTION updateCoins

int checkUpdateCoins (int p, struct gameState *post, int bon) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

    int r = updateCoins (p, *post, bon);

    //update coin count to indicate bonus coins
    post->coins = bon;

    for ( i = 0; i < 5; i++)) {
        if ( playersHand[p][i] == "copper"){
            post->coins += 1;
        }
        else if ( playersHand[p][i] == "silver"){
            post->coins += 2;
        }
        else if ( playersHand[p][i] == "gold") {
            post->coins += 3;
        }
    }

    assert (r == 0);

    assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int updateCoins(int player, struct gameState *state, int bonus)
{
    int i;

    //reset coin count
    state->coins = 0;

    //add coins for each Treasure card in player's hand
    for (i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == copper)
        {
            state->coins += 1;
        }
        else if (state->hand[player][i] == silver)
        {
            state->coins += 2;
        }
        else if (state->hand[player][i] == gold)
        {
            state->coins += 3;
        }
    }

    //add bonus
    state->coins += bonus;

    return 0;
}

int main () {
    int bon;
    //no coin cards
    int playersHand0[5] = {none, none, none, none, none};
    //some coins, some not
    int playersHand1[5] = {none, none, copper, silver, silver};
    int playersHand2[5] = {none, copper, none, gold, silver};
    int playersHand3[5] = {gold, none, gold, silver, silver};
    //all coins
    int playersHand4[5] = {copper, copper, silver, silver, silver};
    int playersHand5[5] = {copper, coopper, silver, gold, silver};
    int playersHand6[5] = {silver, gold, copper, silver, gold};
    // all copper
    int playersHand7[5] = {copper, copper, copper, copper, copper};
    //all silver
    int playersHand8[5] = {silver, silver, silver, silver, silver};
    //all gold
    int playersHand9[5] = {gold, gold, gold, gold, gold};

    struct gameState G;

    int p = 2;

    for (i = 0; i < 9; i++) {
        if ( i == 0 ) {
            G.hand[p][5] = playersHand0;
        }
        else if ( i == 1 ) {
            G.hand[p][5] = playersHand1;
        }
        else if ( i == 2 ) {
            G.hand[p][5] = playersHand2;
        }
        else if ( i == 3 ) {
            G.hand[2][5] = playersHand0;
        }
        else if ( i == 4 ) {
            G.hand[2][5] = playersHand0;
        }
        else if ( i == 5 ) {
            G.hand[2][5] = playersHand0;
        }
        else if ( i == 6 ) {
            G.hand[2][5] = playersHand0;
        }
        else if ( i == 7 ) {
            G.hand[2][5] = playersHand0;
        }
        else if ( i == 8 ) {
            G.hand[2][5] = playersHand0;
        }
        else if ( i == 0) ( i == 0 ) {
            G.hand[2][5] = playersHand9;
        }
    }
    //bonus is 0 to 15
    for ( i = 0; i <= 15; i++ ){
        bon = i;
        checkUpdateCoins(p, &G, bon);
    }

}
