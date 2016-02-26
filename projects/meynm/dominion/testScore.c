// Unit test for the scoreFor() method.

// Business requirements:
// This method calculates a player's current score by looking at each card in his/her deck, discard pile, and hand.
// The score should be correctly calculated (only curse, estates, great hall, and gardens count in calculation).
// Players with no point-adding cards should get a score of zero.
// Gardens should correctly add one point for each set of 10 estate cards.
// Negative scores are possible (if a player has curse cards and no estates) so should be considered.
// The player's hand/piles should not be change in any way

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

void scoreForTest(int expectedScore, int handCards[10], int discardCards[10], int deckCards[10]){
    // The real purpose of this method is to add up scores of various cards.
    // So it doesn't really matter what player it is. We'll just use the first player.

    // Setup: Add cards to player's hand, discard, and deck
    struct gameState state;
    state.handCount[0] = 0;
    state.discardCount[0] = 0;
    state.deckCount[0] = 0;

    int i = 0;
    while (handCards[i] > -2 && i < 10){
        state.handCount[0] = i + 1;
        state.hand[0][i] = handCards[i];
        i++;
    }

    i = 0;
    while (discardCards[i] > -2 && i < 10){
        state.discardCount[0] = i + 1;
        state.discard[0][i] = discardCards[i];
        i++;
    }

    i = 0;
    while (deckCards[i] > -2 && i < 10){
        state.deckCount[0] = i + 1;
        state.deck[0][i] = deckCards[i];
        i++;
    }

    // Perform calculation and assert it is correct
    int calculatedScore = scoreFor(0, &state);
    if(calculatedScore != expectedScore)
    {
        int test = 9;
        printf("FAIL: Player's score was not calculated correctly with %d cards in hand, %d in discard, and %d in deck.", state.handCount[0], state.discardCount[0], state.deckCount[0]);
        printf("\nExpected score = %d, scoreFor result = %d", expectedScore, calculatedScore);
    }

    // The player's hand/piles should not be change in any way
    i = 0;
    while (handCards[i] > -2 && i < 10){
        assert(state.hand[0][i] == handCards[i]);
        i++;
    }

    i = 0;
    while (discardCards[i] > -2 && i < 10){
        assert(state.discard[0][i] == discardCards[i]);
        i++;
    }

    i = 0;
    while (deckCards[i] > -2 && i < 10){
        assert(state.deck[0][i] == deckCards[i]);
        i++;
    }
}

int main(int argc, char *argv[]){
    int empty = -2;

    // The score should be correctly calculated (only curse, estates, great hall, and gardens count in calculation).
    printf("\nTest 1\n");
    int handCards[10] =     { estate, duchy, province, estate, empty, empty, empty, empty, empty, empty };
    int discardCards[10] =  { great_hall, tribute, estate, gardens, empty, empty, empty, empty, empty };
    int deckCards[10] =     { gardens, empty, empty, empty, empty, empty, empty, empty, empty, empty };
    scoreForTest(12, handCards, discardCards, deckCards);

    printf("\nTest 2\n");
    int handCards2[10] =     { province, province, province, province, province, province, province, province, province, province };
    int discardCards2[10] =  { province, province, province, province, province, province, province, province, province, province };
    int deckCards2[10] =     { province, province, province, province, province, province, province, province, province, province };
    scoreForTest(180, handCards2, discardCards2, deckCards2);

    // Players with no point-adding cards should get a score of zero.
    printf("\nTest 3\n");
    int handCards3[10] =     { smithy, adventurer, sea_hag, salvager, outpost, tribute, smithy, adventurer, sea_hag, salvager };
    int discardCards3[10] =  { remodel, village, baron, feast, mine, minion, cutpurse, treasure_map, empty, empty };
    int deckCards3[10] =     { cutpurse, treasure_map, smithy, adventurer, sea_hag, cutpurse, treasure_map, feast, mine, minion };
    scoreForTest(0, handCards3, discardCards3, deckCards3);

    printf("\nTest 4\n");
    // Gardens should correctly add one point for each set of 10 estate cards.
    int handCards4[10] =     { gardens, province, province, province, province, province, province, province, province, province };
    int discardCards4[10] =  { gardens, province, province, province, province, province, province, province, province, province };
    int deckCards4[10] =     { province, province, province, province, province, province, province, province, province, province };
    scoreForTest(170, handCards4, discardCards4, deckCards4);

    printf("\nTest 5\n");

    int handCards5[10] =     { great_hall, tribute, estate, gardens, empty, empty, empty, empty, empty };
    int discardCards5[10] =  { gardens, empty, empty, empty, empty, empty, empty, empty, empty, empty };
    int deckCards5[10] =     { estate, duchy, province, estate, empty, empty, empty, empty, empty, empty };;
    scoreForTest(12, handCards5, discardCards5, deckCards5);

    // Negative scores are possible (if a player has curse cards and no estates) so should be considered.
    printf("\nTest 6\n");

    int handCards6[10] =     { curse, curse, curse, curse, curse, curse, curse, curse, curse, curse };
    int discardCards6[10] =  { curse, curse, curse, curse, curse, curse, curse, curse, curse, curse };
    int deckCards6[10] =     { curse, curse, curse, curse, curse, curse, curse, curse, curse, curse };
    scoreForTest(-30, handCards6, discardCards6, deckCards6);

    return 0;
}

