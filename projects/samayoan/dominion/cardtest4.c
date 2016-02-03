// Test the Cutpurse card
// This card gives the player 2 coins and then
// makes the others player discards a Copper card if they have one.

// Business requirements:
// After the Cutpurse card is played:
// The player that drew the card should have 2 more coins in the coin count
// The other players should have one less copper card in their hand
// The other players should have one less in their coin count
// The discard pile for all players should increase by one
// The hand count for the opposing players should decrease by one

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
    printf("\tCoins count = %d, expected = %d\n", testState->coins, oldState->coins + 2);

    // The other players should have one less copper card in their hand
    printf("\tOther player's Copper card count = %d, expected = %d\n", numOfCardInHand(copper, testState, PLAYER2), numOfCardInHand(copper, oldState, PLAYER2) - 1);

    // The other players should have one less in their coin count
    //testState->whoseTurn = 1;
    updateCoins(PLAYER2, testState, 0);
    updateCoins(PLAYER2, oldState, 0);
      printf("\tNOTE: The following two coin count is failing due to a bug documented in bug.c (bug I introduced in assig 2) \n");
    printf("\tOther player's Coins count = %d, expected = %d\n", testState->coins, oldState->coins - 1);

// The hand count for the opposing players should decrease by one
    printf("\tOther player's hand count = %d, expected = %d\n", testState->handCount[PLAYER2], oldState->handCount[PLAYER2] - 1);

    // The discard pile for all players should increase by one
    printf("\tNOTE: The following two Discard counts are failing due to a bug documented in bug.c \n");
    printf("\tDiscard count = %d, expected = %d\n", testState->discardCount[PLAYER1], oldState->discardCount[PLAYER1] + 1);
    printf("\tOther player's discard count = %d, expected = %d\n", testState->discardCount[PLAYER2], oldState->discardCount[PLAYER2] + 1);
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
void prepareHand(struct gameState *state, int player){
    int totalCards = 27, prevCard = 0, i = 0;
    state->handCount[player] = 5;

    // Put a few treasure cards in the other player's hand
    state->hand[player][0] = copper;
    state->hand[player][1] = copper;
    state->hand[player][2] = silver;
    state->hand[player][3] = gold;

    state->hand[player][4] = getRandomInt(0, totalCards - 1, -2);
}

int getRandomInt(int min, int max, int avoid){
    int tmpInt = avoid;

    if (max == 0)
        return 0;

    while (tmpInt == avoid || tmpInt < min){
        srand((unsigned)time(NULL));
        tmpInt = random() % max;
    }

    return tmpInt;
}

int main(int argc, char *argv[]){
    printf("\n----------------- Testing Card: Cutpurse ----------------\n\n");

    struct gameState oldState, testState;
    int seed = random() % 1000;
    int handPos = 0, numPlayers = 2;
    int k[10] = {smithy, embargo, village, minion, mine, cutpurse, sea_hag, tribute, steward, council_room};
    initializeGame(numPlayers, k, seed, &oldState);

    // Put the Cutpurse card in the hand
    oldState.hand[PLAYER1][handPos] = cutpurse;
    prepareHand(&oldState, PLAYER2);

    // copy the game state to a test case
    memcpy(&testState, &oldState, sizeof(struct gameState));
    cardEffectCutpurse(handPos, &testState);
    processResults(&testState, &oldState);

    return 0;
}
