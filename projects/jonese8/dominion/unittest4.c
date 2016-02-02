/* -----------------------------------------------------------------------
 * CS362 - Assignment 3 - Emmalee Jones
 * Description of isGameOver() unit test. 
 * Include the following lines in the makefile:
 * $ (CFLAGS = -WALL -fpic -coverage -lm )
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 *      unittest4 >> unittestresult.out
 *      gcov unittest4 >> unittestresult.out
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int newCards = 0;
    int discarded = 0;
    int shuffledCards = 0;
   // int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int nextPlayer = 1;
    int newActions;
    int newBuys;
    int nextCards;
    int i, j, r;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};

    printf ("TESTING unittest4 isGameOver():\n");

// initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    // ----------- TEST 1: Game Not Over --------------
    printf("TEST 1: Game Not Over\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    r = isGameOver(&G); // Run isGameOver()

    newCards = 0;
    nextCards = 0;
    newActions = 0;
    newBuys = 0;

    printf("Return = %d\n", r);
    if (r == 0) 
        printf("council_room(): PASS on return code game not over\n");    
    else    
        printf("council_room: FAIL on return code game over\n");

    printf("supplyCount[province] = %d, expected = %d\n", testG.supplyCount[province], \
        G.supplyCount[province]);
    if (G.supplyCount[province] >= 0) 
        printf("council_room(): PASS on supplyCount[province] game not over\n");    
    else    
        printf("council_room: FAIL on supplyCount[province] game over\n");

  //if three supply pile are at 0, the game ends
     j = 0;
     for (i = 0; i < 25; i++)
        {
        if (G.supplyCount[i] == 0)
        {
            j++;
        }
        }
    if ( j < 3)
        {
            printf("council_room(): PASS on not 3 empty supplyCount piles game not over\n"); 
        }
    else
        {
            printf("council_room(): FAIL on not 3 empty supplyCount piles game over\n"); 
        }
 
    printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer], \
        G.handCount[currentPlayer] + newCards - discarded);
    if (testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded) 
        printf("council_room(): PASS on handcount does not change on current player\n");    
    else    
        printf("council_room: FAIL on handcount does not change on current player\n");

    printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer], \
     G.deckCount[currentPlayer] - newCards + shuffledCards);
        if (testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards + shuffledCards)  
        printf("council_room: PASS on deckcount does not change\n");
    else 
        printf("council_room: FAIL on deckcount does not change\n");

    printf("hand count = %d, expected = %d\n", testG.handCount[nextPlayer], \
        G.handCount[nextPlayer] + nextCards);
    if (testG.handCount[nextPlayer] == G.handCount[nextPlayer] + nextCards)
        printf("council_room(): PASS on handcount does not change on next player\n");    
    else    
        printf("council_room: FAIL on handcount does not change on next player\n");

    printf("deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], \
        G.deckCount[nextPlayer] - nextCards);   
    if (testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] - nextCards)  
        printf("council_room: PASS on deckcount does not change on next player\n");
    else 
        printf("council_room: FAIL on deckcount does not change on next player\n");

    printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n", \
         testG.supplyCount[estate], G.supplyCount[estate], testG.supplyCount[duchy], \
         G.supplyCount[duchy], testG.supplyCount[province], G.supplyCount[province]);
    if (testG.supplyCount[estate] == G.supplyCount[estate])  
        printf("council_room: PASS on estate count does not change\n");
    else 
        printf("council_room: FAIL on estate count does not change\n");

    if (testG.supplyCount[duchy] == G.supplyCount[duchy])  
        printf("council_room: PASS on duchy count does not change\n");
    else 
        printf("council_room: FAIL on duchy count does not change\n");  

    if (testG.supplyCount[province] == G.supplyCount[province])  
        printf("council_room: PASS on province count does not change\n");
    else 
        printf("council_room: FAIL on province count does not change\n");

    printf("adventurer = %d, expected = %d\n", testG.supplyCount[adventurer], \
        G.supplyCount[adventurer]);
    if (testG.supplyCount[adventurer] == G.supplyCount[adventurer])  
        printf("council_room: PASS on adventurer count does not change\n");
    else 
        printf("council_room: FAIL on adventurer count does not change\n");

 // ----------- TEST 2: Game Over With 0 Province Cards --------------
    printf("TEST 2: Game Over With 0 Province Cards\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    G.supplyCount[province] = 0;
    
    r = isGameOver(&G); // Run isGameOver()

    printf("supplyCount[province] = %d\n", G.supplyCount[province]);
    if (G.supplyCount[province] == 0) 
        printf("council_room(): PASS on supplyCount[province] game over\n");    
    else    
        printf("council_room: FAIL on supplyCount[province] game not over\n");
 
 // ----------- TEST 3: Game Over with three supply pile at 0 --------------
    printf("TEST 2: Game Over with three supply pile at 0\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    G.supplyCount[duchy] = 0;
    G.supplyCount[curse] = 0;
    G.supplyCount[silver] = 0;
    
    r = isGameOver(&G); // Run isGameOver()

  //if three supply pile are at 0, the game ends
     j = 0;
     for (i = 0; i < 25; i++)
        {
        if (G.supplyCount[i] == 0)
        {
            j++;
        }
        }
    if ( j >= 3)
        {
            printf("council_room(): PASS on 3 empty supplyCount piles game over\n"); 
        }
    else
        {
            printf("council_room(): FAIL on not 3 empty supplyCount piles game not over\n"); 
        }

    printf("All tests completed!\n");

    return 0;
}
