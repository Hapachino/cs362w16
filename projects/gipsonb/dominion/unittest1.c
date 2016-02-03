/*-------------------------------------------------------
 * Unit test for draw card. Heavily based on information
 * found in lesson 11 on random testing.
 *-------------------------------------------------------
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>


int testDrawCard(int p, struct gameState *post);

int main () {

  int n, i, p;
 
  struct gameState game;
  
  SelectStream(2);
  PutSeed(3);
  
  for (n = 0; n < 2000; n++) { //runs 2000 tests
	  //The below code manually initializes a game
	  printf ("--------------------------\n");
      printf ("Running test series %d ...\n", n+1);
	  for (i = 0; i < sizeof(struct gameState); i++) { 
	  ((char*)&game)[i] = floor(Random() * 256);
	  }
	  p = floor(Random() * 2);
	  game.deckCount[p] = floor(Random() * MAX_DECK);
	  game.discardCount[p] = floor(Random() * MAX_DECK);
	  game.handCount[p] = floor(Random() * MAX_HAND);
	  testDrawCard(p, &game);
	  printf ("--------------------------\n\n");
  }

  return 0;
}

int testDrawCard(int p, struct gameState *post) {
 struct gameState pre;
 memcpy (&pre, post, sizeof(struct gameState));
 int r;
    
  r = drawCard(p, post);

  //If the deck has cards in it then this will draw from it
  //basically does what draw card should do
  if (pre.deckCount[p] > 0) {
	  pre.handCount[p]++;
	  pre.hand[p][pre.handCount[p]-1] = pre.deck[p][pre.deckCount[p]-1];
	  pre.deckCount[p]--;
  }
  
  //If deck is empty this fills the deck with the discard pile
  //before drawing a card from the deck
  else if (pre.discardCount[p] > 0) {
	  memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
	  memcpy(pre.discard[p], post->discard[p], sizeof(int) * pre.discardCount[p]);
	  pre.hand[p][post->handCount[p]-1] = post->hand[p][post->handCount[p]-1];
	  pre.handCount[p]++;
	  pre.deckCount[p] = pre.discardCount[p]-1;
	  pre.discardCount[p] = 0;
  }
  assert (r == 0);
  
  assert(memcmp(&pre, post, sizeof(struct gameState)) == 0); //makes sure both game states are the same
  printf ("Test passed\n");
  
  return 0;
}