// Unit test for the gainCard() method.

// Business requirements:
// gainCard() gets called whenever there is a need to add a card to the player's deck.
// Card should only be added to specified pile/hand
// The card should be of the type specified.
// The card should come from the supply.
// No state change should occur for other players.
// Card should only be added to specified pile/hand.
// No state change should occur to pile/hand not specified.
// If the card is not in the game, no changes should occur

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

void gainCardTest(int card, int toFlag, int player, struct gameState *state);

int main(int argc, char *argv[]){
    struct gameState state;
    int kingdoms[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    initializeGame(MAX_PLAYERS, kingdoms, 3, &state);

    // Preconditions: toFlag and player variables must both be 0, 1, or 2
    int i = 0;
    int k = 0;
    int totalCardTypes = 28;

    // Test for each card type
    for (; k < totalCardTypes; k++){
        for (; i <= 2; i++){
            gainCardTest(k, i, i, &state);
        }
    }

    printf("\tunittest2: PASS\r\n");
    return 0;
}

void gainCardTest(int card, int toFlag, int player, struct gameState *state){

    // toFlag = 0 : add to discard
    // toFlag = 1 : add to deck
    // toFlag = 2 : add to hand

    int isInSupply = 0;
    int origSupplyCount = state->supplyCount[card];
    int originalPlayerCount = 0;
    int originalPlayerCount2 = 0;
    int originalPlayerCount3 = 0;
    int originalOtherPlayerCount = 0;

    if (toFlag == 0){
        originalPlayerCount = state->discardCount[player];
        originalPlayerCount2 = state->deckCount[player];
        originalPlayerCount3 = state->handCount[player];
        originalOtherPlayerCount = state->discardCount[player + 1];
    } else if (toFlag == 1){
        originalPlayerCount = state->deckCount[player];
        originalPlayerCount2 = state->discardCount[player];
        originalPlayerCount3 = state->handCount[player];
        originalOtherPlayerCount = state->deckCount[player + 1];
    } else if (toFlag == 2){
        originalPlayerCount = state->handCount[player];
        originalPlayerCount2 = state->deckCount[player];
        originalPlayerCount3 = state->discardCount[player];
        originalOtherPlayerCount = state->handCount[player + 1];
    }

    // If the card is not in the game, no changes should occur
    if (supplyCount(card, state) == 0)
        isInSupply = 1;

    gainCard(card, state, toFlag, player);

    // If the card is not in the game, no changes should occur
    if (isInSupply != 0){
        assert(state->discardCount[player] == originalPlayerCount);
        assert(state->discard[player][originalPlayerCount] == card);
        assert(originalOtherPlayerCount == state->discardCount[player + 1]);
        assert(originalPlayerCount2 == state->deckCount[player]);
        assert(originalPlayerCount3 == state->handCount[player]);
        return;
    }

    // The new card should have been added to the top of the
    // discard, deck, or hand stacks (depending on the toFlag passed in)
    if (toFlag == 0){
        // Card should only be added to specified pile/hand
        assert(state->discardCount[player] == originalPlayerCount + 1);
        // The card should be of the type specified.
        assert(state->discard[player][originalPlayerCount] == card);
        // No state change should occur for other players.
        assert(originalOtherPlayerCount == state->discardCount[player + 1]);
        // No state change should occur to pile/hand not specified
        assert(originalPlayerCount2 == state->deckCount[player]);
        assert(originalPlayerCount3 == state->handCount[player]);
    } else if (toFlag == 1){
        assert(state->deckCount[player] == originalPlayerCount + 1);
        assert(state->deck[player][originalPlayerCount] == card);
        assert(originalOtherPlayerCount == state->deckCount[player + 1]);
        assert(originalPlayerCount2 == state->discardCount[player]);
        assert(originalPlayerCount3 == state->handCount[player]);
    } else if (toFlag == 2){
        assert(state->handCount[player] == originalPlayerCount + 1);
        assert(state->hand[player][originalPlayerCount] == card);
        assert(originalOtherPlayerCount == state->handCount[player + 1]);
        assert(originalPlayerCount2 == state->deckCount[player]);
        assert(originalPlayerCount3 == state->discardCount[player]);
    }

    // The card should come from the supply.
    assert(state->supplyCount[card] == origSupplyCount - 1);
}
