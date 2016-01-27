// Unit test for the updateCoins() method.

// Business requirements:
// This method updates the players coin count according to what
// treasure cards he/she has in hand. updateCoins() has a very simple set of
// business requirements because it just reads some values from game state and does
// not make any changes. The only requirements are:
// Sets the coins correctly, according to what cards the player has in their possession.
// Should NOT modify the player's cards.

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

void updateCoinsTest(int player, int totalGold, int totalSilver, int totalCopper, int bonus);

int main(int argc, char *argv[]){
    // Preconditions: Player must be 4 or less, bonus can be any int
    int maxPlayers = MAX_PLAYERS;

    // First test the case when there are no treasures at all and no bonus,
    // then try with combos of one (first arg doesn't count)
    updateCoinsTest(1, 0, 0, 0, 0);
    updateCoinsTest(1, 0, 0, 0, 1);
    updateCoinsTest(1, 0, 0, 1, 0);
    updateCoinsTest(1, 0, 1, 0, 0);
    updateCoinsTest(1, 1, 0, 0, 0);
    updateCoinsTest(1, 0, 0, 1, 1);
    updateCoinsTest(1, 0, 1, 0, 1);
    updateCoinsTest(1, 1, 0, 0, 1);
    updateCoinsTest(1, 1, 1, 1, 1);

    // Test using various other variables.
    // In a game, the bonus will never be negative, but
    // lets test just to verify it won't throw an unhandled error
    updateCoinsTest(2, 12, 14, 31, 11);
    updateCoinsTest(2, 12, 14, 31, -11);
    updateCoinsTest(1, 56, 999, 35, -16);
    updateCoinsTest(0, 0, 44, 8, 999);

    printf("\tunittest1: PASS\r\n");
    return 0;
}

void updateCoinsTest(int player, int totalGold, int totalSilver, int totalCopper, int bonus)
{
    struct gameState state;
    state.handCount[player] = totalGold + totalSilver + totalCopper;

    // updateCoins looks at all the cards in the players hand
    // looking for treasure cards. So we need to add some (or not) ahead of time.
    // Set the player number and bonus to random numbers.
    int k;
    for (k = 0; k < totalGold; k++)
        state.hand[player][k] = gold;
    for (; k < totalSilver + totalGold; k++)
        state.hand[player][k] = silver;
    for (; k < totalCopper + totalSilver + totalGold; k++)
        state.hand[player][k] = copper;

    int total = (3 * totalGold) + (2 * totalSilver) + totalCopper + bonus;
    updateCoins(player, &state, bonus);

    // Sets the coins correctly, according to what cards the player has in their possession.
    assert(state.coins == total);

    // Should NOT modify the player's cards.
    for (k = 0; k < totalGold; k++)
        assert(state.hand[player][k] == gold);
    for (; k < totalSilver + totalGold; k++)
        assert(state.hand[player][k] == silver);
    for (; k < totalCopper + totalSilver + totalGold; k++)
        assert(state.hand[player][k] == copper);
}
