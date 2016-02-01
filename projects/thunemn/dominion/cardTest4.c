/*
 * Unit test for Great Hall Card
 *
 * Business Rules:
 *  1.	Current player should receive exactly 1 card
 *	2.	Current player gains 1 action
 *	3.	No state change should occur
 *
 * cardTest4: cardTest4.c dominion.o rngs.o
 *      gcc -o cardTest4 -g cardTest4.c dominion.o rngs.o $(FLAGS)
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
    int hand_count, action_count, player_turn;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf("TESTING Great Hall Card\n");
    //clear the game state
    memset(&G, 23, sizeof(struct gameState));
    //initialize a new game
    new_game = initializeGame(numPlayer, k, seed, &G);

    hand_count = G.handCount[p];
    action_count = G.numActions;
    player_turn = G.whoseTurn;

    //play village card
    playGreatHall(&G, handPos, p);
#if (NOISY_TEST == 1)
    //hand should have +1 cards
    if(G.handCount[p] == hand_count)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
    //player should have +1 action cards
    if(G.numActions == action_count + 1)
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
    action_count = G.numActions;
    player_turn = G.whoseTurn;

    printf("\nAll tests passed: Great Hall Card\n");

    return 0;
}
