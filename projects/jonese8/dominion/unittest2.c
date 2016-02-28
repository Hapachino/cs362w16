/* -----------------------------------------------------------------------
 * CS362 - Assignment 3 - Emmalee Jones
 * Description of scoreFor() unit test. 
 * Include the following lines in the makefile:
 * $ (CFLAGS = -WALL -fpic -coverage -lm )
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 *      unittest2 >> unittestresult.out
 *      gcov unittest2 >> unittestresult.out
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int runScoreFor (int player, struct gameState *state) {

  int i;
  int score = 0;
  //score from hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == curse) { score = score - 1; };
      if (state->hand[player][i] == estate) { score = score + 1; };
      if (state->hand[player][i] == duchy) { score = score + 3; };
      if (state->hand[player][i] == province) { score = score + 6; };
      if (state->hand[player][i] == great_hall) { score = score + 1; };
      if (state->hand[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  //score from discard
  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == curse) { score = score - 1; };
      if (state->discard[player][i] == estate) { score = score + 1; };
      if (state->discard[player][i] == duchy) { score = score + 3; };
      if (state->discard[player][i] == province) { score = score + 6; };
      if (state->discard[player][i] == great_hall) { score = score + 1; };
      if (state->discard[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  //score from deck
  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == curse) { score = score - 1; };
      if (state->deck[player][i] == estate) { score = score + 1; };
      if (state->deck[player][i] == duchy) { score = score + 3; };
      if (state->deck[player][i] == province) { score = score + 6; };
      if (state->deck[player][i] == great_hall) { score = score + 1; };
      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  return score;
}


int main() {
    int newCards = 0;
    int discarded = 0;
    int shuffledCards = 0;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int nextPlayer = 1;
    int nextCards = 0;
    int r;
    int testR;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
            sea_hag, tribute, smithy, council_room};

    printf ("TESTING unittest2 scoreFor()\n");

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    // ----------- TEST 1: Test score from beginning of game --------------
    printf("TEST 1: Test score from beginning of game\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    r = scoreFor(0, &G); // Run scoreFor() for player 0
    testR = runScoreFor(0, &testG); //Run runScoreFor() for player 0

    printf("Return from scoreFor = %d\n", r);
    printf("Test Return from scoreFor = %d\n", testR);

    if (r == testR)
        printf("scoreFor(): PASS on scores match\n");    
    else    
        printf("scoreFor: FAIL on scores match\n");

    printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer], \
        G.handCount[currentPlayer] + newCards - discarded);
    if (testG.handCount[currentPlayer] == G.handCount[currentPlayer] + newCards - discarded) 
        printf("scoreFor(): PASS on handcount does not change on current player\n");    
    else    
        printf("scoreFor: FAIL on handcount does not change on current player\n");

    printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer], \
     G.deckCount[currentPlayer] - newCards + shuffledCards);
        if (testG.deckCount[currentPlayer] == G.deckCount[currentPlayer] - newCards + shuffledCards)  
        printf("scoreFor: PASS on deckcount does not change\n");
    else 
        printf("scoreFor: FAIL on deckcount does not change\n");

    printf("hand count = %d, expected = %d\n", testG.handCount[nextPlayer], \
        G.handCount[nextPlayer] + nextCards);
    if (testG.handCount[nextPlayer] == G.handCount[nextPlayer] + nextCards)
        printf("scoreFor(): PASS on handcount does not change on next player\n");    
    else    
        printf("scoreFor: FAIL on handcount does not change on next player\n");

    printf("deck count = %d, expected = %d\n", testG.deckCount[nextPlayer], \
        G.deckCount[nextPlayer] - nextCards);   
    if (testG.deckCount[nextPlayer] == G.deckCount[nextPlayer] - nextCards)  
        printf("scoreFor: PASS on deckcount does not change on next player\n");
    else 
        printf("scoreFor: FAIL on deckcount does not change on next player\n");

    printf("estate = %d, expected = %d, duchy = %d, expected = %d, province = %d, expected = %d\n", \
         testG.supplyCount[estate], G.supplyCount[estate], testG.supplyCount[duchy], \
         G.supplyCount[duchy], testG.supplyCount[province], G.supplyCount[province]);
    if (testG.supplyCount[estate] == G.supplyCount[estate])  
        printf("scoreFor: PASS on estate count does not change\n");
    else 
        printf("scoreFor: FAIL on estate count does not change\n");

    if (testG.supplyCount[duchy] == G.supplyCount[duchy])  
        printf("scoreFor: PASS on duchy count does not change\n");
    else 
        printf("scoreFor: FAIL on duchy count does not change\n");  

    if (testG.supplyCount[province] == G.supplyCount[province])  
        printf("scoreFor: PASS on province count does not change\n");
    else 
        printf("scoreFor: FAIL on province count does not change\n");

    printf("adventurer = %d, expected = %d\n", testG.supplyCount[adventurer], \
        G.supplyCount[adventurer]);
    if (testG.supplyCount[adventurer] == G.supplyCount[adventurer])  
        printf("scoreFor: PASS on adventurer count does not change\n");
    else 
        printf("scoreFor: FAIL on adventurer count does not change\n");

    // ----------- TEST 2: Test score with full score --------------
    printf("TEST 2: Test score with full score\n");
    initializeGame(numPlayers, k, seed, &G);

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

    printf("Print out fullDeckCount = %d\n", fullDeckCount(nextPlayer, 0, &G));

        // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));
    
    r = scoreFor(nextPlayer, &G); // Run scoreFor() for player 0
    testR = runScoreFor(nextPlayer, &testG); //Run runScoreFor() for player 0

    printf("Return from scoreFor = %d\n", r);
    printf("Test Return from scoreFor = %d\n", testR);

    if (r == testR)
        printf("scoreFor(): PASS on scores match\n");    
    else    
        printf("scoreFor: FAIL on scores match\n");

    // ----------- TEST 3: Test score with partial hand --------------
    printf("TEST 3: Test score with partial hand\n");
    initializeGame(numPlayers, k, seed, &G);

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

    printf("Print out fullDeckCount = %d\n", fullDeckCount(nextPlayer, 0, &G));

        // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    //Change number of deck count  
    testG.deckCount[nextPlayer] = 2; 
    G.deckCount[nextPlayer] = 2; 
    
    r = scoreFor(nextPlayer, &G); // Run scoreFor() for player 0
    testR = runScoreFor(nextPlayer, &testG); //Run runScoreFor() for player 0

    printf("Return from scoreFor = %d\n", r);
    printf("Test Return from scoreFor = %d\n", testR);

    if (r == testR)
        printf("scoreFor(): PASS on scores match\n");    
    else    
        printf("scoreFor: FAIL on scores match\n");
    printf("All tests completed!\n");

    return 0;
}
