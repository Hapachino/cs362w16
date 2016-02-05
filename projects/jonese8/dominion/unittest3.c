/* -----------------------------------------------------------------------
 * CS362 - Assignment 3 - Emmalee Jones
 * Description of getWinner() unit test. 
 * Include the following lines in the makefile:
 * $ (CFLAGS = -WALL -fpic -coverage -lm )
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 *      unittest3 >> unittestresult.out
 *      gcov unittest3 >> unittestresult.out
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
    int players[MAX_PLAYERS];
	int newCards = 0;
    int discarded = 0;
    int shuffledCards = 0;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int nextPlayer = 1;
    int notPlayer = 2;
    int nextCards = 0;
    int r;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};

    printf ("TESTING unittest3 getWinner():\n");

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    // ----------- TEST 1: Checking Winner as Player 1 --------------
    printf("TEST 1: Checking Winner as Player 1\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    //Score adjustment to hand pile
    G.handCount[nextPlayer] = 5;
    G.hand[nextPlayer][0] = curse;
    G.hand[nextPlayer][1] = estate;
    G.hand[nextPlayer][2] = duchy;
    G.hand[nextPlayer][3] = province; 
    G.hand[nextPlayer][4] = great_hall; 
    G.hand[nextPlayer][5] = gardens; 

    //Score adjustment to discard pile
    G.discardCount[nextPlayer] = 5;
    G.discard[nextPlayer][0] = curse;
    G.discard[nextPlayer][1] = estate;
    G.discard[nextPlayer][2] = duchy;
    G.discard[nextPlayer][3] = province; 
    G.discard[nextPlayer][4] = great_hall; 
    G.discard[nextPlayer][5] = gardens; 

    //Score adjustment to deck pile
    G.deckCount[nextPlayer] = 5;
    G.deck[nextPlayer][0] = curse;
    G.deck[nextPlayer][1] = estate;
    G.deck[nextPlayer][2] = duchy;
    G.deck[nextPlayer][3] = province; 
    G.deck[nextPlayer][4] = great_hall; 
    G.deck[nextPlayer][5] = gardens; 
   
    r = getWinners(players, &G); // Run getWinners()

    printf("Return = %d\n", r);
    if (r == 0) 
        printf("getWinner(): PASS on return code getWinner\n");    
    else    
        printf("getWinner: FAIL on return code getWinner\n");

    printf("highest_score test player 0 =  %d\n", players[0]);
    printf("highest_score test player 1 =  %d\n", players[1]); 
    printf("highest_score test player 2 =  %d\n", players[2]);
    printf("highest_score test player 3 =  %d\n", players[3]);  

    printf("number of active players = %d\n", G.numPlayers);

    printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer], \
        G.handCount[currentPlayer] + newCards - discarded);
    if (testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded) 
        printf("getWinner(): PASS on handcount does not change on current player\n");    
    else    
        printf("getWinner: FAIL on handcount does not change on current player\n");

    printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer], \
     G.deckCount[currentPlayer] - newCards + shuffledCards);
        if (testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards + shuffledCards)  
        printf("getWinner: PASS on deckcount does not change\n");
    else 
        printf("getWinner: FAIL on deckcount does not change\n");

    printf("hand count = %d, expected = %d\n", testG.handCount[nextPlayer], \
        G.handCount[nextPlayer] + nextCards);
    if (testG.handCount[nextPlayer] == G.handCount[nextPlayer] + nextCards)
        printf("getWinner(): PASS on handcount does not change on next player\n");    
    else    
        printf("getWinner: FAIL on handcount does not change on next player\n");

    printf("deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], \
        G.deckCount[nextPlayer] - nextCards);   
    if (testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] - nextCards)  
        printf("getWinner: PASS on deckcount does not change on next player\n");
    else 
        printf("getWinner: FAIL on deckcount does not change on next player\n");

    printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n", \
         testG.supplyCount[estate], G.supplyCount[estate], testG.supplyCount[duchy], \
         G.supplyCount[duchy], testG.supplyCount[province], G.supplyCount[province]);
    if (testG.supplyCount[estate] == G.supplyCount[estate])  
        printf("getWinner: PASS on estate count does not change\n");
    else 
        printf("getWinner: FAIL on estate count does not change\n");

    if (testG.supplyCount[duchy] == G.supplyCount[duchy])  
        printf("getWinner: PASS on duchy count does not change\n");
    else 
        printf("getWinner: FAIL on duchy count does not change\n");  

    if (testG.supplyCount[province] == G.supplyCount[province])  
        printf("getWinner: PASS on province count does not change\n");
    else 
        printf("getWinner: FAIL on province count does not change\n");

    printf("adventurer = %d, expected = %d\n", testG.supplyCount[adventurer], \
        G.supplyCount[adventurer]);
    if (testG.supplyCount[adventurer] == G.supplyCount[adventurer])  
        printf("getWinner: PASS on adventurer count does not change\n");
    else 
        printf("getWinner: FAIL on adventurer count does not change\n");

     // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    // ----------- TEST 2: Checking Winner as Player 3 (not active Player) ---- 
    printf("TEST 2: Checking Winner as Player 3 (not active Player)\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    //Score adjustment to hand pile
    G.handCount[notPlayer] = 5;
    G.hand[notPlayer][0] = curse;
    G.hand[notPlayer][1] = estate;
    G.hand[notPlayer][2] = duchy;
    G.hand[notPlayer][3] = province; 
    G.hand[notPlayer][4] = great_hall; 
    G.hand[notPlayer][5] = gardens; 

    //Score adjustment to discard pile
    G.discardCount[notPlayer] = 5;
    G.discard[notPlayer][0] = curse;
    G.discard[notPlayer][1] = estate;
    G.discard[notPlayer][2] = duchy;
    G.discard[notPlayer][3] = province; 
    G.discard[notPlayer][4] = great_hall; 
    G.discard[notPlayer][5] = gardens; 

    //Score adjustment to deck pile
    G.deckCount[notPlayer] = 5;
    G.deck[notPlayer][0] = curse;
    G.deck[notPlayer][1] = estate;
    G.deck[notPlayer][2] = duchy;
    G.deck[notPlayer][3] = province; 
    G.deck[notPlayer][4] = great_hall; 
    G.deck[notPlayer][5] = gardens; 
    
    r = getWinners(players, &G); // Run getWinners()

    printf("Return = %d\n", r);
    if (r == 0) 
        printf("getWinner(): PASS on return code getWinner\n");    
    else    
        printf("getWinner: FAIL on return code getWinner\n");

    printf("highest_score test player 0 =  %d\n", players[0]);
    printf("highest_score test player 1 =  %d\n", players[1]); 
    printf("highest_score test player 2 =  %d\n", players[2]);
    printf("highest_score test player 3 =  %d\n", players[3]); 

    printf("number of active players = %d\n", G.numPlayers);
  
       return 0;

 printf("All tests completed!\n");

}
