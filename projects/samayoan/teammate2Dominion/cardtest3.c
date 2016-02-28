// Test the Salvager card
// This card gives the player one more buy and makes
// the player trash one card from their hand and in return
// gets coins equal to the value of the trashed card.
// If the player has no cards, they only get the extra buy.

// Business requirements:
// The number of buys of the player should increase by 1
// The coins received should equal the cost of the trash cardEffect
// If no card is trashed, no coins are received
// If no card is trashed, an extra buy is received
// If a card is not trashed, the discard count should increase by one
// The deck count should remain
// If a card is trashed, the hand count should decrease by two
// If a card is not trashed, the hand count should remain the same

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

static const PLAYER = 0;

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

// This is needed becuase the hand giving to each player with initializeGame
// is not very varied in card type
void randomizeHand(struct gameState *state, int player){
    int totalCards = 27, prevCard = 0, i = 0;

    for (; i < state->handCount[player]; i++){
        prevCard = getRandomInt(0, totalCards - 1, prevCard);
        state->hand[player][i] = prevCard;
    }
}

void processResults(struct gameState *testState, struct gameState *oldState, int cardChoice){
    int expectedBuys = 0;
    int expectedCoins = 0;
    int expectedDiscard = 0;
    int expctedHandcout = 0;

    if (cardChoice > -2)
    {
        // The number of buys of the player should increase by 1
        expectedBuys = oldState->numBuys + 1;

        // The coins received should equal the cost of the trash cardEffect
        int cardValue = getCost(cardChoice);
        expectedCoins = oldState->coins + cardValue;

        // If a card is trashed, the discard count should increase by two
        expectedDiscard = oldState->discardCount[PLAYER] + 2;

        // If a card is trashed, the hand count should decrease by two
        expctedHandcout = oldState->handCount[PLAYER] - 2;
    }
    else
    {
        // If no card is trashed, an extra buy is received
        expectedBuys = oldState->numBuys + 1;

        // If no card is trashed, no coins are received
        expectedCoins = oldState->coins;

        // If a card is not trashed, the discard count should increase by one
        expectedDiscard = oldState->discardCount[PLAYER] + 1;

        // If a card is not trashed, the hand count should remain the same
        expctedHandcout = oldState->handCount[PLAYER];
    }

    printf("\tBuys count = %d, expected = %d\n", testState->numBuys, expectedBuys);
    printf("\tCoins count = %d, expected = %d\n", testState->coins, expectedCoins);
    printf("\tDiscard count = %d, expected = %d\n", testState->discardCount[PLAYER], expectedDiscard);
    printf("\tHandcount = %d, expected = %d\n", testState->handCount[PLAYER], expctedHandcout);
    // The deck count should remain
    printf("\tDeck count = %d, expected = %d\n", testState->deckCount[PLAYER], oldState->deckCount[PLAYER]);
}

int main(int argc, char *argv[]){
    printf("\n----------------- Testing Card: Salvager ----------------\n\n");

    struct gameState oldState, testState, testState2;
    int numPlayers = 2, choice1 = 0, handPos = 0;
    int makesNoDif = -999;
    int k[10] = {smithy, embargo, village, minion, mine, cutpurse, sea_hag, tribute, steward, council_room};
    int i = 1;
    int seed = 1000, testRuns = 3;

    for (; i <= testRuns; i++){
        initializeGame(numPlayers, k, seed, &oldState);
        randomizeHand(&oldState, PLAYER);
        // Randomize which card we choose to discard. Make sure it's different every time
        handPos = getRandomInt(0, oldState.handCount[PLAYER], handPos);
        choice1 = oldState.hand[PLAYER][handPos];
        // copy the game state to a test case
        memcpy(&testState, &oldState, sizeof(struct gameState));
        cardEffect(salvager, choice1, makesNoDif, makesNoDif, &testState, handPos, &makesNoDif);
        printf("\n\n Test run %d - Card to discard = %d with a value of $%d\n", i, choice1, getCost(choice1));
        processResults(&testState, &oldState, choice1);
    }

    return 0;
}

