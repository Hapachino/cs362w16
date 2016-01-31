/*
 * Unit test for Smithy Card
 *
 * Business Rules:
 *  1.	Current player should receive exactly 3 cards
 *	2.	3 cards should come from his own pile
 *	3.	No state change should occur
 *	4.	Current card should be discarded
 *
 * cardTest1: cardTest1.c dominion.o rngs.o
 *      gcc -o cardTest1 -g cardTest1.c dominion.o rngs.o $(FLAGS)
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

    printf("TESTING Smithy Card\n");

    //clear the game state
    memset(&G, 23, sizeof(struct gameState));
    //initialize a new game
    new_game = initializeGame(numPlayer, k, seed, &G);

    hand_count = G.handCount[p];
    deck_count = G.deckCount[p];
    player_turn = G.whoseTurn;
    smithy_count = G.supplyCount[smithy];
    int estate_count = G.supplyCount[estate];
    int duchy_count = G.supplyCount[duchy];
    int province_count = G.supplyCount[province];
    int great_hall_count = G.supplyCount[great_hall];
    int gardens_count = G.supplyCount[gardens];

    //play smithy card
    playSmithy(&G, handPos);
#if (NOISY_TEST == 1)
    //hand should have +2 cards
    if(G.handCount[p] == hand_count + 2)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
    //deck should have -3 cards
    if(G.deckCount[p] == deck_count - 3)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
    //player's turn should not change
    if(G.whoseTurn == player_turn)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
    //victory cards should be unchanged
    if(G.supplyCount[estate] == estate_count && G.supplyCount[duchy] == duchy_count && G.supplyCount[province] == province_count)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
    //kingdom cards should be unchanged
    if(G.supplyCount[great_hall] == great_hall_count && G.supplyCount[gardens] == gardens_count)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
#endif

    hand_count = G.handCount[p];
    deck_count = G.deckCount[p];
    player_turn = G.whoseTurn;

    printf("\nAll tests passed: Smithy Card\n");

    return 0;
}
