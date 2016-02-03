// Test the smithy card
// This card gives the player 3 more cards to their hand, then
// the player discards the smithy card after use.

// Business requirements
// After the smithy card is played, the user should have:
// 2 more cards in the hand (3 new cards added but 1 smithy is discarded)
// 3 less cards in the deck
// One more card in their discard
// No change to other players piles/hands


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

static const PLAYER = 0;

void cardEffectSmithy(struct gameState *state, int handpos)
{
    int makesNoDif = -999;
    cardEffect(smithy, makesNoDif, makesNoDif, makesNoDif, state, handpos, &makesNoDif);
}

void printResults(struct gameState *testState, int expectedHandCount, int expectedDeckCount, int expectedDiscardCount, int handpos)
{
	printf("\tHand count = %d, expected = %d\n", testState->handCount[PLAYER], expectedHandCount);
    printf("\tDeck count = %d, expected = %d\n", testState->deckCount[PLAYER], expectedDeckCount);
    printf("\tDiscard count = %d, expected = %d\n", testState->discardCount[PLAYER], expectedDiscardCount);
    printf("\tCard at handpos %d should NOT be %d. Actual: %d\n", handpos, smithy, testState->hand[PLAYER][handpos]);
}

int main(int argc, char *argv[]){
	printf("\n----------------- Testing Card: Smithy ----------------\n\n");
    
	// These variables never change
    int handpos = 0, shuffledCards = 0, testruns = 10;
    int numPlayers = 2, newCards = 3, discarded = 1;
	struct gameState state, testState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, steward, council_room};

    // The smithy card is fairly simple, so we'll loop to make the test valuable
    int i =0;
    for (; i < testruns; i++) {
        // Randomize the seed to make it interesting
        int seed = random() % 1000;

        // initialize a game state and player cards
        initializeGame(numPlayers, k, seed, &state);
        // copy the game state to a test case
        memcpy(&testState, &state, sizeof(struct gameState));

        printf("\nTEST %d: Expect +%d cards in hand using seed %d in intializeGame.\n", i, newCards, seed);
        cardEffectSmithy(&testState, handpos);

        // 2 more cards in the hand (3 new cards added but 1 smithy is discarded)
        // 3 less cards in the deck
        // One more card in their discard
        printResults(&testState, state.handCount[PLAYER] + newCards - discarded, state.deckCount[PLAYER] - newCards, state.discardCount[PLAYER] + 1, handpos);

        // No change to other players piles/hands
        assert(testState.handCount[1] == state.handCount[1]);
        assert(testState.deckCount[1] == state.deckCount[1]);
        assert(testState.discardCount[1] == state.discardCount[1]);
    }

    printf("\n\nNOTE: These tests technically are 'Failing' due to a known bug that is documented in bug.c\n");
    return 0;
}
