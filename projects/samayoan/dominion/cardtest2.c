// Test the adventurer card
// This card makes the player reveal cards from their deck until
// they reveal 2 Treasure cards. The player must then put those
// Treasure cards in their hand and discard the other revealed cards.

// Business requirements:
// After the adventurer card is played, the player should have:
// 1 more card in their hand (2 new treasures minus 1 discarded adventurer card)
// Two newest cards in their deck will be treasure cards
// Increase of one or more in discard pile (1 for the adventurer card and more possible)
// Increase in that players coin count (executed after cardEffect)
// No change to the other player's piles/hand

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

static const PLAYER = 0;

void cardEffectAdventurer(struct gameState *state)
{
    // The adventurer effect method only needs the state variable
    int makesNoDif = -999;
    cardEffect(adventurer, makesNoDif, makesNoDif, makesNoDif, state, makesNoDif, &makesNoDif);
}

void processResults(struct gameState *testState, struct gameState *oldState)
{
    // Increase in that players coin count (executed after cardEffect)
    updateCoins(testState->whoseTurn, testState, 0);

    // 1 more card in their hand (2 new treasures minus 1 discarded adventurer card)
    printf("\tHand count = %d, expected = %d\n", testState->handCount[PLAYER], oldState->handCount[PLAYER] + 2 - 1);

    // Two newest cards in their deck will be treasure cards
    printf("\tNewest cards in deck should be treasure (%d, %d, or %d) - Actual: %d and %d \n",
            gold, silver, copper, testState->hand[PLAYER][testState->handCount[PLAYER] - 1], testState->hand[PLAYER][testState->handCount[PLAYER] - 2]);

    printf("\tDeck count = %d, expected = %d\n", testState->deckCount[PLAYER], oldState->deckCount[PLAYER]) - 2;

    // Increase of one or more in discard pile
    printf("\tDiscard count = %d, should be >= %d\n", testState->discardCount[PLAYER], 1 + oldState->discardCount[PLAYER]);
    printf("\tCoins = %d. Expected > %d", testState->coins, oldState->coins);

    // No change to the other player's piles/hand
    assert(testState->handCount[1] == oldState->handCount[1]);
    assert(testState->deckCount[1] == oldState->deckCount[1]);
    assert(testState->discardCount[1] == oldState->discardCount[1]);
}

int main(int argc, char *argv[]){
    printf("\n----------------- Testing Card: Adventurer ----------------\n\n");

    struct gameState oldState, testState, testState2;
    int numPlayers = 2;
     // Randomize the seed to make it interesting
    int seed = random() % 1000;
    int k[10] = {smithy, embargo, village, minion, mine, cutpurse, sea_hag, tribute, steward, council_room};
    initializeGame(numPlayers, k, seed, &oldState);
    // copy the game state to a test case
    memcpy(&testState, &oldState, sizeof(struct gameState));
    cardEffectAdventurer(&testState);
    printf("\n\nTest run 1\n");
    processResults(&testState, &oldState);

    memcpy(&testState2, &testState, sizeof(struct gameState));
    cardEffectAdventurer(&testState2);
    printf("\n\nTest run 2\n");
    processResults(&testState2, &testState);

    memcpy(&oldState, &testState2, sizeof(struct gameState));
    cardEffectAdventurer(&oldState);
    printf("\n\nTest run 3\n");
    processResults(&oldState, &testState);

    memcpy(&testState, &oldState, sizeof(struct gameState));
    cardEffectAdventurer(&testState);
    printf("\n\nTest run 4\n");
    processResults(&testState, &oldState);

    printf("\n\nNOTE: These tests are 'failing' due to 2 known bugs that are documented in bug.c\n");
    return 0;
}
