#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define Random rand

int checkBuyCard (int supplyP, struct gameState *post) {
    struct gameState pre;
    memcpy (&pre, post, sizeof(struct gameState));

    int r = buyCard (supplyP, post);

    //must have a buy to do a buy
    if ( pre.numBuys > 0){
        //if card is available for purchase
        if (supplyP > 0){
            //if you have enough coins to buy
            if (pre.coins >= getCost(supplyP)){
                // flag is 0 because a newly purchased card goes straight to discard
                gainCard(supplyP, &pre, 0, pre.whoseTurn);
                pre.coins = pre.coins - getCost(supplyP);
            }
        }
    }

    assert (r == 0);

    assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);
}

int buyCard(int supplyPos, struct gameState *state) {
    int who;
    if (DEBUG){
        printf("Entering buyCard...\n");
    }

    // I don't know what to do about the phase thing.

    who = state->whoseTurn;

    if (state->numBuys < 1){
        if (DEBUG)
            printf("You do not have any buys left\n");
        return -1;
    } else if (supplyCount(supplyPos, state) <1){
        if (DEBUG)
            printf("There are not any of that type of card left\n");
        return -1;
    } else if (state->coins < getCost(supplyPos)){
        if (DEBUG)
            printf("You do not have enough money to buy that. You have %d coins.\n", state->coins);
        return -1;
    } else {
        state->phase=1;
        //state->supplyCount[supplyPos]--;
        gainCard(supplyPos, state, 0, who); //card goes in discard, this might be wrong.. (2 means goes into hand, 0 goes into discard)

        state->coins = (state->coins) - (getCost(supplyPos));
        state->numBuys--;
        if (DEBUG)
            printf("You bought card number %d for %d coins. You now have %d buys and %d coins.\n", supplyPos, getCost(supplyPos), state->numBuys, state->coins);
    }

    //state->discard[who][state->discardCount[who]] = supplyPos;
    //state->discardCount[who]++;

    return 0;
}

int main () {
    int x;
    struct gameState G;
    //test 1000 times
    for (x=0; x < 1000; x++){

        int p = floor(Random() * 2);
        int cardNum;
        int cardCostCard = floor(Random() * 27);
            if (cardCostCard == 0){
                cardNum = curse;
            }
            else if (cardCostCard == 1){
                cardNum = estate;
            }
            else if (cardCostCard == 2){
                cardNum = duchy;
            }
            else if (cardCostCard == 3){
                cardNum = province;
            }
            else if (cardCostCard == 4){
                cardNum = copper;
            }
            else if (cardCostCard == 5){
                cardNum = silver;
            }
            else if (cardCostCard == 6){
                cardNum = gold;
            }
            else if (cardCostCard == 7){
                cardNum = adventurer;
            }
            else if (cardCostCard == 8){
                cardNum = council_room;
            }
            else if (cardCostCard == 9){
                cardNum = feast;
            }
            else if (cardCostCard == 10){
                cardNum = gardens;
            }
            else if (cardCostCard == 11){
                cardNum = mine;
            }
            else if (cardCostCard == 12){
                cardNum = remodel;
            }
            else if (cardCostCard == 13){
                cardNum = smithy;
            }
            else if (cardCostCard == 14){
                cardNum = village;
            }
            else if (cardCostCard == 15){
                cardNum = baron;
            }
            else if (cardCostCard == 16){
                cardNum = great_hall;
            }
            else if (cardCostCard == 17){
                cardNum = minion;
            }
            else if (cardCostCard == 18){
                cardNum = steward;
            }
            else if (cardCostCard == 19){
                cardNum = tribute;
            }
            else if (cardCostCard == 20){
                cardNum = ambassador;
            }
            else if (cardCostCard == 21){
                cardNum = cutpurse;
            }
            else if (cardCostCard == 22){
                cardNum = embargo;
            }
            else if (cardCostCard == 23){
                cardNum = outpost;
            }
            else if (cardCostCard == 24){
                cardNum = salvager;
            }
            else if (cardCostCard == 25){
                cardNum = sea_hag;
            }
            else if (cardCostCard == 26){
                cardNum = treasure_map;
            }

        //0 to 8 buys
        G.numBuys = floor(Random() * 9);
        //number of coins available is 0 to 20
        G.coins = floor(Random() * 21);

        checkBuyCard (cardNum, &G);
    }
    return 0;
}
