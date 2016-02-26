// Unit test for the discardCard() method.

// Business requirements:
// discardCard() gets called whenever there is a need to remove a card to the player's hand.
// The card should be sent to the trash pile if (and only if) that is specified.
// Only the hand should be affected.
// Discarding from the front, middle, and end of the hand should work.
// No other player's hand should be affected.
// The players discard and deck piles should not be affected.

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

void discardCardTest(int totalHandCount, int handPos, int player, int trashFlag){
    struct gameState state;

    // Initialize the played card count if not trashing
    if (trashFlag < 1)
        state.playedCardCount = 0;

    state.handCount[player] = totalHandCount;
    state.deckCount[player] = 0;
    state.discardCount[player] = 0;
    state.handCount[player + 1] = 0;

    // Set all hards in hand to smithy to initialize them
    int c = 0;
    for (; c < totalHandCount; c++){
        // Set to following ard so we can later check that it was pushed back
        state.hand[player][c] = smithy;
    }

    // Set the card in question to sea_hag so we can later check and ensure it
    // was discarded (set to -1) or set to smithy if it wasn't the last card in the hand.
    state.hand[player][handPos] = sea_hag;

    discardCard(handPos, player, &state, trashFlag);

    // The card should be sent to the trash pile if (and only if) that is specified.
    if (trashFlag < 1)
        assert(state.playedCardCount == 1);

    assert(state.hand[player][handPos] != sea_hag);

    // If we are discarding the one and only hard in the hand, it should be reset to 99.
    // If we are discarding the last card, it should also be reset to 99.
    // Otherwise it should be the smithy card
    if (totalHandCount == 1 || handPos == totalHandCount - 1){
        // Only the hand should be affected.
        assert(state.hand[player][handPos] == 99);
    }
    else {
        // Only the hand should be affected.
        assert(state.hand[player][handPos] == smithy);
    }

    // The players discard and deck piles should not be affected.
    assert(state.deckCount[player] == 0);
    assert(state.discardCount[player] == 0);

    // No other player's hand should be affected.
    assert(state.handCount[player + 1] == 0);
}

int main(int argc, char *argv[]){
    // Discarding from the front, middle, and end of the hand should work.
    // Start with the case where there is only one card in the hand.
    discardCardTest(1, 0, 0, 0);
    discardCardTest(1, 1, 0, 0);
    discardCardTest(1, 0, 1, 0);
    discardCardTest(1, 0, 0, 1);

    // Now do cases where there are 3 cards in the hand and we want to remove the first
    discardCardTest(3, 0, 0, 0);
    discardCardTest(3, 0, 1, 0);
    discardCardTest(3, 0, 0, 1);

    // Now do cases where there are 3 cards in the hand and we want to remove the middle
    discardCardTest(3, 1, 0, 0);
    discardCardTest(3, 1, 0, 1);
    discardCardTest(3, 1, 1, 0);
    discardCardTest(3, 1, 0, 1);

    // Now do cases where there are 3 cards in the hand and we want to remove the last
    discardCardTest(3, 2, 0, 0);
    discardCardTest(3, 2, 0, 1);
    discardCardTest(3, 2, 1, 0);
    discardCardTest(3, 2, 0, 1);

    printf("\tunittest3: PASS\r\n");
    return 0;
}

