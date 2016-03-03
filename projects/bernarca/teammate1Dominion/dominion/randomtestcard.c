#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>


/*
fill gamestate with random bytes
correct any bytes that have to be a certain way
pass it to the card a bunch of times and verify output
*/

int main(){
  int shown_p1_assert = 0;
  int shown_p2_assert = 0;
  struct gameState G, testG;
  int numPlayers = 2;
  int num_cards = 13;
  int k[13] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room, copper, silver, gold};
	int seed = 1000;
  initializeGame(numPlayers, k, seed, &G);
  int i,n;
  for (n = 0; n < 2000; n++){
    for (i = 0; i < sizeof(struct gameState); i++){
      ((char*)&G)[i] = floor(Random() * 256);
    }
    G.numPlayers = 2;
    G.whoseTurn = 0;
    while (G.whoseTurn < G.numPlayers){
      G.handCount[G.whoseTurn] = floor(Random() * 100) + 5;
      for (i = 0; i < G.handCount[G.whoseTurn]; i++){
        G.hand[G.whoseTurn][i] = k[(int) floor(Random() * num_cards)];
      }
      G.deckCount[G.whoseTurn] = floor(Random() * 100) + 5;
      for (i = 0; i < G.deckCount[G.whoseTurn]; i++){
        G.deck[G.whoseTurn][i] = k[(int) floor(Random() * num_cards)];
      }
      for (i = 0; i < 2; i++){
        G.deck[G.whoseTurn][i] = copper; // Add two coppers to one end of the deck
      }
      G.deck[G.whoseTurn][G.deckCount[G.whoseTurn] - 1] = copper; // and one to the other, to guarantee there's enough treasure
      G.discardCount[G.whoseTurn] = floor(Random() * 200) + 5;
      for (i = 0; i < G.discardCount[G.whoseTurn]; i++){
        G.discard[G.whoseTurn][i] = k[(int) floor(Random() * num_cards)];
      }
      G.whoseTurn++;
    }
    G.whoseTurn = floor(Random() * G.numPlayers);
    for (i = 0; i < (treasure_map + 1); i++){
      G.supplyCount[i] = floor(Random() * 40);
    }
    if (G.numActions < 0){
      G.numActions *= -1;
    }
    G.playedCardCount = floor(Random() * 100) + 5;
    for (i = 0; i < G.playedCardCount; i++){
      G.playedCards[i] = k[(int) floor(Random() * num_cards)];
    }
    
    G.hand[G.whoseTurn][3] = village;
   
    memcpy(&testG, &G, sizeof(struct gameState));
    
    cVillage(testG.whoseTurn, &testG, 3);
    
    if (testG.whoseTurn == 0){
      if (!shown_p1_assert){
        printf("Player = 1. TestG.numActions = %d, G.numActions = %d\n", testG.numActions, G.numActions);
        shown_p1_assert = 1;
      }
      //assert(testG.numActions == G.numActions + 1); // tests # of actions given to p1
    } else {
      if (!shown_p2_assert){
        printf("Player = 2. TestG.numActions = %d, G.numActions = %d\n", testG.numActions, G.numActions);
        shown_p2_assert = 1;
      }
      //assert(testG.numActions == G.numActions + 1); // tests same for p2, this one fails!
    }
    
  }
  printf("testG should be 1 more than G both times, but it's 2 more for player 2.\n");
  printf("Tests finished.\n");
  return 0;
}