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
  int tested = 0;
  struct gameState G, testG;
  int numPlayers = 2;
  int num_cards = 13;
  int k[13] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room, copper, silver, gold};
	int seed = 1000;
  
  initializeGame(numPlayers, k, seed, &G);
  printf("Copper is %d, Silver is %d, Gold is %d\n", copper, silver, gold);
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
    int temphand[100];
    int z;
   
    memcpy(&testG, &G, sizeof(struct gameState));
    //printf("Test #%d...\n", n);
    cAdventurer(0, &testG, testG.whoseTurn, 0, temphand, z);
    	int thisPlayer = testG.whoseTurn;
    	
    	if (tested < 20){
    	  printf("Last hand card: %d, second-last: %d\n", testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1],
    	                                                  testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2]);
    	  printf("testG.discardCount = %d, G.discardCount = %d\n", testG.discardCount[testG.whoseTurn], G.discardCount[G.whoseTurn]);
    	}
    	/*
    	assert(testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == copper
	        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == silver
	        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == gold);
	assert(testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == copper // THIS ASSERT FAILS!
	        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == silver
	        || testG.hand[thisPlayer][testG.handCount[thisPlayer] - 2] == gold);
	      */
    // assert(testG.discardCount[testG.whoseTurn] > G.discardCount[G.whoseTurn]); // This assert fails!
    
  }
  printf("A lot of the second-last cards will probably not be a treasure number,\n and the discard counts will be the same even though they should be different.\n");
  printf("Tests finished.\n");
  return 0;
}