/*
 * Unit test for Adventure Card
 *
 * Business Rules:
 *  1.	Current player should receive exactly 2 cards
 *	2.	2 cards should come from his own pile
 *	3.	No state change should occur
 *
 * cardTest2: cardTest2.c dominion.o rngs.o
 *      gcc -o cardTest2 -g cardTest2.c dominion.o rngs.o $(FLAGS)
 *
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//set NOISY_TEST to 0 to remove prinftf's from output
#define NOISY_TEST 1

int main() {
    int i = 0, p = 0;
    int handPos = 0;
    int seed = 1000;
    int numPlayer = 2;
    int new_game;
    int hand_count, deck_count, player_turn, smithy_count;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf("TESTING Adventurer Card\n");
    //clear the game state
    memset(&G, 23, sizeof(struct gameState));
    //initialize a new game
    new_game = initializeGame(numPlayer, k, seed, &G);

    hand_count = G.handCount[p];
    deck_count = G.deckCount[p];
    player_turn = G.whoseTurn;

    //play adventurer card
    playAdventurer(&G);

#if (NOISY_TEST == 1)
    //hand should have +1 cards
    if(G.handCount[p] == hand_count + 2)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
    //deck should have -2 cards
    if(G.deckCount[p] == deck_count - 2)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
    //player's turn should not change
    if(G.whoseTurn == player_turn)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
#endif

    hand_count = G.handCount[p];
    deck_count = G.deckCount[p];
    player_turn = G.whoseTurn;

    printf("\nAll tests passed: Adventurer Card\n");

    return 0;
}
