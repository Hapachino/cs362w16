#ifndef _FORDSAMTEST_H
#define _FORDSAMTEST_H

#include "dominion.h"

/* This struct is a modification of gameState which basically adds additional
   members for keeping track of overall changes for two-dimensional arrays
   (e.g. handChanged[] for hand[][]). The values in gameStateComparison
   indicate change status (0 for unchanged or 1 for changed). */
struct gameStateComparison {
  int numPlayers;
  int supplyCount[treasure_map+1];
  int embargoTokens[treasure_map+1];
  int outpostPlayed;
  int outpostTurn;
  int whoseTurn;
  int phase;
  int numActions;
  int coins;
  int numBuys;
  int hand[MAX_PLAYERS][MAX_HAND];
  int handCount[MAX_PLAYERS];
  int handChanged[MAX_PLAYERS];
  int deck[MAX_PLAYERS][MAX_DECK];
  int deckCount[MAX_PLAYERS];
  int deckChanged[MAX_PLAYERS];
  int discard[MAX_PLAYERS][MAX_DECK];
  int discardCount[MAX_PLAYERS];
  int discardChanged[MAX_PLAYERS];
  int playedCards[MAX_DECK];
  int playedCardCount;
};

int fakeAssert(char condition[], int result);
void printTestResults(int passCount, int testCount);
int containsCard(int card, int *array, int arrayCount);
int compareState(
  struct gameState *state1,
  struct gameState *state2,
  struct gameStateComparison *results
);
int printIntArray(int *array, int arrayCount);

#endif
