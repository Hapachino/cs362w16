/* ---------------------------------------------------------------------------
 * David Vogel
 * CS362 Assignment 3
 * Due Feb 3, 2016
 * Filename: cardtest2.c
 *   testing village card
 *
 * Include the following lines in your makefile:
 *   cardtest2: cardtest2.c dominion.o rngs.o
 *     gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
 *  
 * Requirements for village:
 *   - Current player should receive exactly 1 cards.
 *   - The 1 cards should come from his own pile.
 *   - Current player should discard exactly 1 cards.
 *   - Current player should gain exactly 2 actions.
 *   - No state change should occur for other players.
 *   - No state change should occur to the Victory card piles and Kingdom card piles.
 * ---------------------------------------------------------------------------*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

int main() {
  int shuffledCards = 0;          //cards gained if deck becomes empty
  int i = 0;                      //index counter
  int expectedHandCount = 0;      //desired value for hand count
  int actualHandCount = 0;        //actual value for expected hand count
  int expectedDeckCount = 0;      //desired value for deck count
  int actualDeckCount = 0;        //actual value for expected hand count
  int successfulTests = 0;        //number of successful tests
  int failedTests = 0;            //number of failed tests
  int totalNumberOfTests = 0;     //total number of tests run
  int randSeed = 1000;            //random seed for game init
  int numPlayers = 2;             //num players for game init
  int testPlayer = 0;             //test player is always 0
  int otherPlayer = 1;            //this is the computer
  int cardsGained = 1;            //should gain 1 card
  int cardsDiscarded = 1;         //should have discarded 1 card after playing
  int actualActionsGained = 0;    //how many actions village actually gained
  int expectedActionsGained = 2;  //village was supposed to gain 2 actions
  
  //passed to cardEffect
  int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, handPos = 0;

  //actual game state & tested game state
  struct gameState actualGameState, testGameState;
  
  //kingdom cards for game
  int kingdom_Cards[10] = {adventurer, council_room, remodel, village, baron, embargo, steward, tribute, ambassador, smithy};

  //victory cards for game
  int victory_Cards[3] = {estate, duchy, province};

  //initialize game & copy state for reference
  initializeGame(numPlayers, kingdom_Cards, randSeed, &actualGameState);
  memcpy(&testGameState, &actualGameState, sizeof(struct gameState));

  //call the village card
  cardEffect(village, choice1, choice2, choice3, &testGameState, handPos, &bonus);

  //begin tests
  printf("**************************** TESTING VILLAGE CARD ****************************\n");

  /* ---------------------- TEST 1 --------------------- */
  //test player should receive 1 card and discard 1, ending with 5 in hand
  printf("---------------- TEST 1: TESTING CARDS RECEIVED AND DISCARDED ----------------\n");
  printf("Current player should receive 1 card, discard 1...\n");

  //print test of calling handCount()
  actualHandCount = testGameState.handCount[testPlayer];
  expectedHandCount = actualGameState.handCount[testPlayer] + cardsGained - cardsDiscarded;
  printf("Actual hand count: %d\n", actualHandCount);
  printf("Expected hand count: %d\n", expectedHandCount);
  if (actualHandCount == expectedHandCount) {
    printf("***SUCCESS: HAND COUNT GAME STATE FOR CURRENT PLAYER IS THE SAME!\n\n");
    ++successfulTests;
  }
  else {
    printf("***FAIL: HAND COUNT GAME STATE FOR CURRENT PLAYER IS DIFFERENT!\n\n");
    ++failedTests;
  }
  ++totalNumberOfTests;

  /* ---------------------- TEST 2 --------------------- */
  //The 1 card should come from the test player's pile
  printf("------------------------- TEST 2: TESTING DECK COUNT -------------------------\n");
  printf("Card should come from current player's deck count...\n");
  actualDeckCount = testGameState.deckCount[testPlayer];
  expectedDeckCount = actualGameState.deckCount[testPlayer] - cardsGained + shuffledCards;
  printf("Actual deck count: %d\n", actualDeckCount);
  printf("Expected deck count: %d\n", expectedDeckCount);

  //test game state of deckCount for test player
  if (expectedDeckCount == actualDeckCount) {
    printf("***SUCCESS: DECK COUNT GAME STATE FOR CURRENT PLAYER IS THE SAME!\n\n");
    ++successfulTests;
  }
  else {
    printf("***FAIL: DECK COUNT GAME STATE FOR CURRENT PLAYER IS DIFFERENT!\n\n");
    ++failedTests;
  }
  ++totalNumberOfTests;

  /* ---------------------- TEST 3 --------------------- */
  //current player should gain exactly 2 actions.
  printf("-------------- TEST 3: TESTING THAT PLAYER RECEIVES 2 ACTIONS --------------\n");
  //player will have lost 1 action and gained 2, so subtract 1
  actualActionsGained = testGameState.numActions - 1;
  //player starts with 1 action, so adding 1 should give 2
  expectedActionsGained = actualGameState.numActions + 1;
  printf("Actual actions gained: %d\n", actualActionsGained);
  printf("Expected actions gained: %d\n", expectedActionsGained);
  if (actualActionsGained == expectedActionsGained) {
    printf("***SUCCESS: ACTIONS GAME STATE FOR CURRENT PLAYER IS THE SAME!\n\n");
    ++successfulTests;
  }
  else {
    printf("***FAIL: ACTIONS GAME STATE FOR CURRENT PLAYER IS DIFFERENT!\n\n");
    ++failedTests;
  }
  ++totalNumberOfTests;

  /* ---------------------- TEST 4 --------------------- */
  //test that game state for victory cards & kingdom cards did not change
  printf("-------- TEST 4: TESTING THAT NUMBER OF VICTORY CARDS HAS NOT CHANGED --------\n");
  for (i = 0; i < 3; i++) {
    if(testGameState.supplyCount[victory_Cards[i]] == actualGameState.supplyCount[victory_Cards[i]]) {
      printf("***SUCCESS: VICTORY CARD %d SUCCEEDED!\n", i);
      ++successfulTests;
    }
    else {
      printf("***FAIL: VICTORY CARD %d FAILED!\n", i);
      ++failedTests;
    }
    ++totalNumberOfTests;
  }
  printf("\n");

  /* ---------------------- TEST 5 --------------------- */
  printf("-------- TEST 5: TESTING THAT NUMBER OF KINGDOM CARDS HAS NOT CHANGED --------\n");
  for (i = 0; i < 10; i++) {
    if (testGameState.supplyCount[kingdom_Cards[i]] == actualGameState.supplyCount[kingdom_Cards[i]]) {
      printf("***SUCCESS: KINGDOM CARD %d SUCCEEDED!\n", i);
      ++successfulTests;
    }
    else {
      printf("***FAIL: KINGDOM CARD %d FAILED!\n", i);
      ++failedTests;
    }
    ++totalNumberOfTests;
  }
  printf("\n");

  /* ---------------------- TEST 6 --------------------- */
  printf("------ TEST 6: TESTING THAT GAME STATE FOR OTHER PLAYER HASN'T CHANGED ------\n");
  //test that game state hasn't changed for other player
  printf("Testing game state for other player...\n");
  if (testGameState.handCount[otherPlayer] == actualGameState.handCount[otherPlayer]
      && testGameState.deckCount[otherPlayer] == actualGameState.deckCount[otherPlayer]
      && testGameState.discardCount[otherPlayer] == actualGameState.discardCount[otherPlayer]) {
    printf("***SUCCESS: GAME STATE FOR OTHER PLAYER IS THE SAME!\n\n");
    ++successfulTests;
  }
  else {
    printf("***FAIL: GAME STATE FOR OTHER PLAYER IS DIFFERENT!\n\n");
    ++failedTests;
  }
  ++totalNumberOfTests;

  /* ---------------------- TEST RESULTS --------------------- */
  if (totalNumberOfTests == successfulTests) {
    printf("************ SUCCESS: ALL TESTS PASSED FOR VILLAGE CARD ************\n");
  }
  else {
    printf("************ FAIL: NOT ALL TESTS PASSED FOR VILLAGE CARD ************\n");
  }
  printf("The number of tests run was: %d\n", totalNumberOfTests);
  printf("The number of tests passed was: %d\n", successfulTests);
  printf("The number of tests failed was: %d\n", failedTests);
  
  return 0;
}