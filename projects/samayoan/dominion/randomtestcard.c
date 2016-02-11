// Random test for the Cutpurse card
// This card gives the player 2 coins and then
// makes the others player discards a Copper card if they have one.

// Business requirements:
// After the Cutpurse card is played:
// The player that drew the card should have 2 more coins in the coin count
// The other players should have one less copper card in their hand
// The other players should have one less in their coin count

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

static const PLAYER1 = 0;
static const PLAYER2 = 1;

void cardEffectCutpurse(int handPos, struct gameState *state){
    int makesNoDif = -999;
    cardEffect(cutpurse, makesNoDif, makesNoDif, makesNoDif, state, handPos, &makesNoDif);
}

void processResults(struct gameState *testState, struct gameState *oldState){
    // The player that drew the card should have 2 more coins in the coin count
    updateCoins(PLAYER1, oldState, 0);
    assert(testState->coins == oldState->coins + 2);
    // The other players should have one less copper card in their hand
    printf("\tCopper cards in player 2's hand. Expected = %d Actual = %d\n", numOfCardInHand(copper, oldState->hand[PLAYER2]) - 1, numOfCardInHand(copper, testState->hand[PLAYER2]));

    // The other players should have one less in their coin count
    updateCoins(PLAYER2, oldState, 0);
    updateCoins(PLAYER2, testState, 0);
    printf("\tCoin count for player 2. Expected = %d Actual = %d\n", oldState->coins - 1, testState->coins);
}

int numOfCardInHand(int card, struct gameState *state, int player){
    int count = 0, i = 0;

    for (; i < state->handCount[player]; i++){
        if (state->hand[player][i] == card){
            count++;
        }
    }

    return count;
}

// This is needed because the hand giving to each player with initializeGame
// is not very varied in card type
void prepareRandomizedHand(struct gameState *state, int player, int addTreasure){
    int totalCards = 27, prevCard = 0, i = 0;
    state->handCount[player] = 5;

    // Put a few treasure cards in the other player's hand
    // Put the Cutpurse card in the hand since it will be played
    state->hand[player][0] = cutpurse;
    state->hand[player][1] = estate;
    state->hand[player][2] = mine;
    state->hand[player][3] = smithy;
    state->hand[player][4] = province;

    if (addTreasure > 0) {
        // Randomly select a treasure and where it goes in the hand
        int indxForTreasure = 3 + (random() % 2);
        int treasureSelection = 0 + (random() % 3);

        if (treasureSelection == 0)
            state->hand[player][indxForTreasure] = copper;
        else if (treasureSelection == 1)
            state->hand[player][indxForTreasure] = silver;
        else if (treasureSelection == 2)
            state->hand[player][indxForTreasure] = gold;
    }

    updateCoins(player, state, 0);
}

int main(int argc, char *argv[]){
    printf("\n----------------- Testing Card: Cutpurse ----------------\n\n");

    struct gameState oldState, testState;
    int seed = random() % 1000;
    int handPos = 0, numPlayers = 2, testRuns = 500, i = 0;
    int k[10] = {smithy, embargo, village, minion, mine, cutpurse, sea_hag, tribute, steward, council_room};

    for (i = 1; i <= testRuns; i++) {
        printf("\nTest run %d\n", i);
        initializeGame(numPlayers, k, seed, &oldState);
        // Randomize the last param, which is a flag to add or not add treasure cards.
        // That should give more variety to the code run.
        prepareRandomizedHand(&oldState, PLAYER1, (random() % 2));
        // Only the second player discards a copper
        prepareRandomizedHand(&oldState, PLAYER2, (random() % 2));
        // copy the game state to a test case
        memcpy(&testState, &oldState, sizeof(struct gameState));
        cardEffectCutpurse(handPos, &testState);
        processResults(&testState, &oldState);
    }

    printf("\n\nNOTE: The Discard & Coin counts are BOTH failing due to a bug documented in bug.c \n");
    return 0;
}
