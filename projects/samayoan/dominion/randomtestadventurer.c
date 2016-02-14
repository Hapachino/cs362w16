// Random test for the adventurer card
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

void prepareRandomizedDeck(struct gameState *state, int player){
    int lastDeckInx = state->deckCount[player] - 1;

    // If the deck isn't large enough, forget about trying
    // to randomize this time around
    if (lastDeckInx <= 2)
        return;

    // Randomly select a treasure and where it goes in the hand
    int treasureSelection  = (random() % 3);
    int treasureSelection2 = (random() % 3);

    if (treasureSelection == 0)
        state->deck[player][lastDeckInx] = copper;
    else if (treasureSelection == 1)
        state->deck[player][lastDeckInx] = silver;
    else if (treasureSelection == 2)
        state->deck[player][lastDeckInx] = gold;

    // Make sure there is one non-treasure between the two treasures so we
    // get more coverage of the adventurerEffect method
    state->deck[player][lastDeckInx - 1] = mine;

    if (treasureSelection2 == 0)
        state->deck[player][lastDeckInx - 2] = silver;
    else if (treasureSelection2 == 1)
        state->deck[player][lastDeckInx - 2] = gold;
    else if (treasureSelection2 == 2)
        state->deck[player][lastDeckInx - 2] = copper;

    updateCoins(player, state, 0);
}

void processResults(struct gameState *testState, struct gameState *oldState)
{
    // Increase in that players coin count (executed after cardEffect)
    updateCoins(testState->whoseTurn, testState, 0);

    // 2 more cards in their hand (because discard is skipped)
    int expHandCount = oldState->handCount[PLAYER] + 2;
    int actHandCount = testState->handCount[PLAYER];
    printf("\tHand count Expected = %d, Actual = %d\n", expHandCount, actHandCount);

    int expDeckCount = oldState->deckCount[PLAYER] - 2;
    int actDeckCount = testState->deckCount[PLAYER];
    printf("\tDeck count Expected = %d, Actual = %d\n", expDeckCount, actDeckCount);

    // Increase of one or more in discard pile
    int expDiscardCount = 1 + oldState->discardCount[PLAYER];
    int actDiscardCount = testState->discardCount[PLAYER];
    printf("\tDiscard Expceted = %d, Actual = %d\n", expDiscardCount, actDiscardCount);

    int expectedCoins = oldState->coins;
    int actualCoins = testState->coins;
    printf("\tCoins Expected > %d, Actual = %d\n", expectedCoins, actualCoins);

    // No change to the other player's piles/hand
    assert(testState->handCount[1] == oldState->handCount[1]);
    assert(testState->deckCount[1] == oldState->deckCount[1]);
    assert(testState->discardCount[1] == oldState->discardCount[1]);

    // Two newest cards in their deck will be treasure cards
    int lastC = testState->hand[PLAYER][testState->handCount[PLAYER] - 1];
    int secLC = testState->hand[PLAYER][testState->handCount[PLAYER] - 2];
    assert(lastC == gold || lastC == silver || lastC == copper);
    assert(secLC == gold || secLC == silver || secLC == copper);

    if (actHandCount != expHandCount || actDeckCount != expDeckCount || actDiscardCount != expDiscardCount || actualCoins < expectedCoins) {
        printf("\tRun run status: FAIL\n");
    } else {
        printf("\tRun run status: PASS\n");
    }
}

int main(int argc, char *argv[]){
    printf("\n----------------- Testing Card: Adventurer ----------------\n\n");

    struct gameState oldState, testState, testState2;
    int numPlayers = 2;
     // Randomize the seed to make it interesting
    int seed = random() % 1000, testRuns = 500, i = 0;
    int k[10] = {smithy, embargo, village, minion, mine, cutpurse, sea_hag, tribute, steward, council_room};

    for (i = 1; i <= testRuns; i++) {
        printf("\n\nTest run %d\n", i);
        initializeGame(numPlayers, k, seed, &oldState);
        // Semi-randomize the deck by adding two randomly selected treasures near the end of the deck.
        // That should give more variety to the code run.
        prepareRandomizedDeck(&oldState, 0);
        // copy the game state to a test case
        memcpy(&testState, &oldState, sizeof(struct gameState));
        cardEffectAdventurer(&testState);
        processResults(&testState, &oldState);

        memcpy(&testState2, &testState, sizeof(struct gameState));
        cardEffectAdventurer(&testState2);
        processResults(&testState2, &testState);

        memcpy(&oldState, &testState2, sizeof(struct gameState));
        cardEffectAdventurer(&oldState);
        processResults(&oldState, &testState);

        memcpy(&testState, &oldState, sizeof(struct gameState));
        cardEffectAdventurer(&testState);
        processResults(&testState, &oldState);
    }

    printf("\n\nNOTE: These tests are 'failing' due to 2 known bugs that are documented in bug.c\n");
    return 0;
}
