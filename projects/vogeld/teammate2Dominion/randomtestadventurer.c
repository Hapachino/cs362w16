/* ---------------------------------------------------------------------------
 * David Vogel
 * CS362 Assignment 4
 * Due Feb 14, 2016
 * Filename: randomtestadventurer.c
 *   random test adventurer card
 *
 * Include the following lines in your makefile:
 *   randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *     gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
 *  
 * Requirements for adventurer:
 *   - Action should draw 2 treasure cards, giving total of 6, after action is discarded
 *   - Player should have same amount of cards in discard pile as were drawn and discarded
 *   - Player should have 2 extra treasure cards 
 *        (these will be coppers since that is what is started with)
 *   - No state change should occur for other players.
 *   - No state change should occur to the Victory card piles and Kingdom card piles.
 * ---------------------------------------------------------------------------*/
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <math.h>
#include <sys/time.h>

enum MY_CARDS {
  CURSE = 0, ESTATE = 1, DUCHY = 2, PROVINCE = 3, COPPER = 4, SILVER = 5, GOLD = 6, ADVENTURER = 7, COUNCIL_ROOM = 8, FEAST = 9, GARDENS = 10,
  MINE = 11, REMODEL = 12, SMITHY = 13, VILLAGE = 14, BARON = 15, GREAT_HALL = 16, MINION = 17, STEWARD = 18, TRIBUTE = 19, AMBASSADOR = 20,
  CUTPURSE = 21, EMBARGO = 22, OUTPOST = 23, SALVAGER = 24, SEA_HAG = 25, TREASURE_MAP = 26
};

#define MAX_HAND_SIZE 5         //max starting hand size
#define MIN_HAND_SIZE 1         //min hand size
#define NUM_PLAYERS 2           //num players for game init
#define TEST_PLAYER 0           //test player is always 0
#define OTHER_PLAYER 1          //this is the computer
#define TEST_CARD ADVENTURER

/* 
This is a shuffle routine for randomizing
http://stackoverflow.com/questions/6127503/shuffle-array-in-c
Arrange the N elements of ARRAY in random order.
Only effective if N is much smaller than RAND_MAX;
if this may not be the case, use a better random
number generator. */
void myShuffle2(int *rooms, int n) {
  struct timeval t1;
  gettimeofday(&t1, NULL);
  srand(t1.tv_usec * t1.tv_sec);
  if (n > 1) {
    int i;
    for (i = 0; i < n - 1; i++) {
      int j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = rooms[j];
      rooms[j] = rooms[i];
      rooms[i] = t;
    }
  }
}

int main() {
  int shuffledCards = 0;        //cards gained if deck becomes empty
  int i = 0, j = 0, m = 0;                    //index counters
  int expectedHandCount = 0;    //desired value for hand count
  int actualHandCount = 0;      //actual value for expected hand count
  int expectedDeckCount = 0;    //desired value for deck count
  int actualDeckCount = 0;      //actual value for expected hand count
  int successfulTests = 0;      //number of successful tests
  int failedTests = 0;          //number of failed tests
  int totalNumberOfTests = 0;   //total number of tests run
  int handSize;                 //from 1 to 5 cards in hand
  int cardsGained = 2;            //should gain 2 cards
  int cardsDiscarded = 1;         //should have discarded 1 card after playing
  int expectedExtraCoins = 2;     //should have 2 new coppers
  int actualExtraCoins = 0;      //actual coins received
  //passed to cardEffect:
  int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0, handPos = 0;

  srand(time(NULL)); //random seed

  //actual game state & tested game state
  struct gameState actualGameState, testGameState;

  //kingdom cards for game
  int kingdom_Cards[10]; //to be shuffled from all_k_cards
  int all_k_cards[] =
      {ADVENTURER, COUNCIL_ROOM, FEAST, GARDENS, MINE, REMODEL, SMITHY, VILLAGE, BARON, GREAT_HALL, MINION, STEWARD, TRIBUTE, AMBASSADOR, CUTPURSE,
       EMBARGO, OUTPOST, SALVAGER, SEA_HAG, TREASURE_MAP};

  //victory cards for game (to be shuffled)
  int victory_Cards[] = {ESTATE, DUCHY, PROVINCE};
  // int all_tres_cards[] = {COPPER, SILVER, GOLD};

  //random test loop
  for (m = 0; m < 1000; m++) {
    myShuffle2(all_k_cards, 19); //shuffle kingdom cards
    for (j = 0; j < 10; j++) { //copy first 10 cards for use
      kingdom_Cards[j] = all_k_cards[j];
    }
    myShuffle2(victory_Cards, 3); //shuffle victory cards
    //initialize game & copy state for reference
    initializeGame(NUM_PLAYERS, kingdom_Cards, 2, &actualGameState);
    memcpy(&testGameState, &actualGameState, sizeof(struct gameState));
    handSize = rand() % MAX_HAND_SIZE + 1; //rand handSize between 1 & 5
    handPos = rand() % handSize; //rand handPos between 0 & handSize

    //call the adventurer card
    // cardEffect(adventurer, choice1, choice2, choice3, &testGameState, handPos, &bonus);
    playAdventurer(TEST_PLAYER, &testGameState); //test ian's adventurer refactor
    //begin tests
    printf("**************************** TESTING ADVENTURER CARD ****************************\n");
    /* ---------------------- TEST 1 --------------------- */
    //test player should receive 2 cards
    printf("---------------- TEST 1: TESTING CARDS RECEIVED ----------------\n");
    printf("Player should receive 2 cards...\n");
    // cardEffect(adventurer, choice1, choice2, choice3, &testGameState, handPos, &bonus);
    actualHandCount = testGameState.handCount[TEST_PLAYER];
    expectedHandCount = actualGameState.handCount[TEST_PLAYER] + cardsGained - cardsDiscarded;
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
    //The 2 cards should come from the test player's pile
    printf("------------------------- TEST 2: TESTING DECK COUNT -------------------------\n");
    printf("2 Cards should come from current player's deck count...\n");
    actualDeckCount = testGameState.deckCount[TEST_PLAYER];
    expectedDeckCount = actualGameState.deckCount[TEST_PLAYER] - cardsGained + shuffledCards;
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
    //Player should have 2 extra coins
    printf("------------------------- TEST 3: TESTING EXTRA COINS -------------------------\n");
    printf("Player should have 2 extra coins...\n");
    updateCoins(TEST_PLAYER, &testGameState, bonus);
    actualExtraCoins = testGameState.coins - actualGameState.coins;
    printf("Actual extra coins: %d\n", actualExtraCoins);
    printf("Expected extra coins: %d\n", expectedExtraCoins);

    //test game state of coins for test player
    if (expectedExtraCoins == actualExtraCoins) {
      printf("***SUCCESS: GAME STATE COINS FOR CURRENT PLAYER IS THE SAME!\n\n");
      ++successfulTests;
    }
    else {
      printf("***FAIL: GAME STATE COINS FOR CURRENT PLAYER IS DIFFERENT!\n\n");
      ++failedTests;
    }
    ++totalNumberOfTests;

    /* ---------------------- TEST 4 --------------------- */
    //test that game state for victory cards & kingdom cards did not change
    printf("-------- TEST 4: TESTING THAT NUMBER OF VICTORY CARDS HAS NOT CHANGED --------\n");
    for (i = 0; i < 3; i++) {
      if (testGameState.supplyCount[victory_Cards[i]] == actualGameState.supplyCount[victory_Cards[i]]) {
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
    if (testGameState.handCount[OTHER_PLAYER] == actualGameState.handCount[OTHER_PLAYER]
        && testGameState.deckCount[OTHER_PLAYER] == actualGameState.deckCount[OTHER_PLAYER]
        && testGameState.discardCount[OTHER_PLAYER] == actualGameState.discardCount[OTHER_PLAYER]) {
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
      printf("************ SUCCESS: ALL TESTS PASSED FOR ADVENTURER CARD ************\n");
    }
    else {
      printf("************ FAIL: NOT ALL TESTS PASSED FOR ADVENTURER CARD ************\n");
    }
    printf("The number of tests run was: %d\n", totalNumberOfTests);
    printf("The number of tests passed was: %d\n", successfulTests);
    printf("The number of tests failed was: %d\n", failedTests);
  }
  return 0;
}