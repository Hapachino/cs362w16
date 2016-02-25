/******************
 * Eric Olson
 * CS362_Assignment3
 * Smithy Card Function Test
 ******************/

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int validate(struct gameState *pre, struct gameState *post, int errors, int hand, int deck, 
             int discard, int played);
void basic_setup(struct gameState *pre, struct gameState *post);

int main(){
  struct gameState *pre = malloc(sizeof(struct gameState)), *post = malloc(sizeof(struct gameState));
  int i, errors = 0;
  srand(time(NULL));
  
  printf("|------------------------------------------|\n");
  printf("  Running tests on smithy_play():\n");
  printf("|------------------------------------------|\n");
  
  /***** SCENARIO 1 - New game, hand=6, deck=5, discard=0  *****/
  printf("Running Scenario 1...\n");
  //Setup Scenario:
  basic_setup(pre, post);
  //Have player 0 play smithy card.
  smithy_play(0, post, 5);
  //Check hand went from 6 to 8, deck went from 5 to 2, played went from 0 - 1.
  errors = validate(pre, post, errors, 8, 2, 0, 1);
  
  /***** SCENARIO 2 - Shuffle Required, hand=6, deck=0, discard=10  *****/
  printf("Running Scenario 2...\n");
  //Setup Scenario:
  basic_setup(pre, post);
  //Clear out deck and add random cards to discard.
  memset(pre->deck[0], 0, 5 * sizeof(int));
  memset(post->deck[0], 0, 5 * sizeof(int));
  pre->deckCount[0] = post->deckCount[0] = 0;
  for (i = 0; i < 10; i++){ pre->discard[0][i] = post->discard[0][i] = rand() % 26; }
  pre->discardCount[0] = post->discardCount[0] = 10;
  //Have player 0 play smithy card.
  smithy_play(0, post, 5);
  //Check hand went from 6 to 8, deck went from 0 to 7, played went from 0 - 1.
  errors = validate(pre, post, errors, 8, 7, 0, 1);
  
  //Report Findings
  if (errors) { printf("Tests Complete: smithy_play() failed %d tests.\n", errors); }
  else { printf("Tests Complete: No errors found.\n"); }

  return 0;  
}
  
void basic_setup(struct gameState *pre, struct gameState *post){
  int i, j, try, k[10] = { 0 };
  //Clear any previous data.
  memset(pre, 0, sizeof(struct gameState));
  memset(post, 0, sizeof(struct gameState));
  
  //randomize kingdom cards & initalize a game.
  k[0] = smithy;
  for (i = 1; i < 10; i++) {
    do{
      //Pick random kingdom card.
      try = ((rand() % 20) + 7);
      for (j = 0; j <= i; j++) {
        if (k[j] == try) { break; }  //If already used, break and try another random kingdom card.
        if (j == i) { k[i] = try; }  //If no duplicates found, assigned random kingdom card to array.
      }
    } while (k[i] == 0);      
  }
  if (initializeGame(2, k, ((rand() % 500) + 1), post) != 0) { printf("Initalization of game failed.\n"); }
  
  //Ensure player 0 has smithy card in hand.
  post->hand[0][5] = smithy;
  post->handCount[0]++;
  
  //And create identical copies of gamestate before test.
  memcpy(pre, post, sizeof(struct gameState));
}
  
int validate(struct gameState *pre, struct gameState *post, int errors, int hand, int deck, 
             int discard, int played){
  int i;
  
  //Check pre vs post gameState's to ensure intended changes occured, and no unintended changes occured.
  if (pre->numPlayers != post->numPlayers){ 
    printf("state.numPlayers failed. (expected=%d, actual=%d)\n", pre->numPlayers, post->numPlayers);
    errors++;   
  }
  for (i = 0; i < treasure_map + 1; i++) {
    if (pre->supplyCount[i] != post->supplyCount[i]){ 
      printf("state.supplyCount[%d] failed. (expected=%d, actual=%d)\n", 
	     i, pre->supplyCount[i], post->supplyCount[i]);
      errors++;  
    }
    if (pre->embargoTokens[i] != post->embargoTokens[i]){ 
      printf("state.embargoTokens[%d] failed. (expected=%d, actual=%d)\n", 
	     i, pre->embargoTokens[i], post->embargoTokens[i]);
      errors++;  
    }
  }
  if (pre->outpostPlayed != post->outpostPlayed){ 
    printf("state.outpost->layed failed. (expected=%d, actual=%d)\n", pre->outpostPlayed, post->outpostPlayed);
    errors++;  
  }
  if (pre->outpostTurn != post->outpostTurn){ 
    printf("state.outpost->urn failed. (expected=%d, actual=%d)\n", pre->outpostTurn, post->outpostTurn);
    errors++;  
  }
  if (pre->whoseTurn != post->whoseTurn){ 
    printf("state.whoseTurn failed (expected=%d, actual=%d).\n", pre->whoseTurn, post->whoseTurn);
    errors++;  
  }
  if (pre->phase != post->phase){ 
    printf("state.phase failed. (expected=%d, actual=%d)\n", pre->phase, post->phase);
    errors++;  
  }
  if (pre->numActions != post->numActions){ 
    printf("state.numActions failed. (expected=%d, actual=%d)\n", pre->numActions, post->numActions);
    errors++;  
  }
  if (pre->coins != post->coins){ 
    printf("state.coins failed. (expected=%d, actual=%d)\n", pre->coins, post->coins);
    errors++;  
  }
  if (pre->numBuys != post->numBuys){ 
    printf("state.numBuys failed. (expected=%d, actual=%d)\n", pre->numBuys, post->numBuys);
    errors++;  
  }
  //Actually check if player drew 3 cards (intended functionality):
  if (post->handCount[0] != hand){ 
    printf("state.handCount failed. (expected=%d, actual=%d)\n", hand, post->handCount[0]);
    errors++;  
  }
  if (pre->handCount[1] != post->handCount[1]){ 
    printf("state.handCount[1] failed. (expected=%d, actual=%d)\n", pre->handCount[1], post->handCount[1]);
    errors++;
  }
  //Check that cards came from deck.
  if (post->deckCount[0] != deck){ 
    printf("state.deckCount[0] failed. (expected=%d, actual=%d)\n", deck, post->deckCount[0]);
    errors++;
  }
  if (pre->deckCount[1] != post->deckCount[1]){ 
    printf("state.deckCount[1] failed. (expected=%d, actual=%d)\n", pre->deckCount[1], post->deckCount[1]);
    errors++;
  }
  //Confirm cards came from discard on shuffle.
  if (post->discardCount[0] != discard){ 
    printf("state.discardCount[0] failed. (expected=%d, actual=%d)\n", 
	   discard, post->discardCount[0]);
    errors++;
  }
  if (pre->discardCount[1] != post->discardCount[1]){ 
    printf("state.discardCount[1] failed. (expected=%d, actual=%d)\n", 
	   pre->discardCount[1], post->discardCount[1]);
    errors++;
  }
  //Ensure smithy card moved to played after use.
  if (post->playedCardCount != played){ 
    printf("state.playedCardCount failed. (expected=%d, actual=%d)\n", played, post->playedCardCount);
    errors++;
  }

  return errors;
}
