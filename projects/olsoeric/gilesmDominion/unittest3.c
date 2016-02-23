/******************
 * Eric Olson
 * CS362_Assignment3
 * Shuffle Function Test
 ******************/

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int validate(struct gameState *pre, struct gameState *post, int errors, int cards, int tally);
void basic_setup(struct gameState *pre, struct gameState *post);

int main(){
  struct gameState *pre = malloc(sizeof(struct gameState)), *post = malloc(sizeof(struct gameState));
  int i, j, cards, tally, failure, errors = 0;
  srand(time(NULL));
  
  printf("\n|------------------------------------------|\n");
  printf("  Running tests on shuffle():\n");
  printf("|------------------------------------------|\n");
  
  /***** RANDOM SCENARIO *****/
  printf("Running 50,000 Random Scenarios...\n");
  for (i = 0; i < 50000; i++){
    //Setup Scenario:
    basic_setup(pre, post);
    //Stage Deck with between 0-MAX_DECK random cards.  (These are moved by drawCard to deck normally)
    cards = (rand() % MAX_DECK);
    tally = 0;
    for (j = 0; j < cards; j++){
       post->deck[0][j] = (rand() % 27);  //Assign a random card.
       //And add card value to tally for later comparison.
       tally = tally + post->deck[0][j];     
    }
    post->deckCount[0] = cards;
    post->discardCount[0] = 0;
    //Ensure pre & post are equal
    memcpy(pre, post, sizeof(struct gameState));
    //Test shuffle().
    failure = shuffle(0, post);
    //Confirm failure only if no cards in deck.
    if (failure && post->deckCount[0] != 0){
      printf("shuffle() returned -1 in error. (expected=0, actual=%d)\n", failure);
      errors++;
    }
    //Check final state.
    errors = validate(pre, post, errors, cards, tally);
  }
 
  
  //Report Findings
  if (errors) { printf("Tests Complete: shuffle() failed %d tests.\n", errors); }
  else { printf("Tests Complete: No errors found.\n"); }

  return 0;  
}
  
void basic_setup(struct gameState *pre, struct gameState *post){
  int i, j, try, k[10] = { 0 };
  //Clear any previous data.
  memset(pre, 0, sizeof(struct gameState));
  memset(post, 0, sizeof(struct gameState));
  
  //randomize kingdom cards & initalize a game.
  for (i = 0; i < 10; i++) {
    do{
      //Pick random kingdom card.
      try = ((rand() % 20) + 7);
      for (j = 0; j <= i; j++) {
        if (k[j] == try) { break; }  //If already used, break and try another random kingdom card.
        if (j == i) { k[i] = try; }  //If no duplicates found, assigned random kingdom card to array.
      }
    } while (k[i] == 0);      
  }
  if (initializeGame(2, k, ((rand() % 500) + 1), post) != 0) { printf( "Initalization of game failed.\n"); }

  //And create identical copies of gamestate before test.
  memcpy(pre, post, sizeof(struct gameState));
}
  
int validate(struct gameState *pre, struct gameState *post, int errors, int cards, int tally){
  int i, check_tally = 0;

  //Check that the same cards made it back into the deck. . .
  for (i = 0; i < cards; i++){
     check_tally = check_tally + post->deck[0][i];
  }
  if (tally != check_tally){
     printf("state.deck[0] card tally failed. (expected=%d, actual=%d)\n", tally, check_tally);
     errors++;
  }
  //For large enough sample sizes make sure first couple cards not in same order
  if (cards > 50 && pre->deck[0][0] == post->deck[0][0] && pre->deck[0][1] == post->deck[0][1] 
      && pre->deck[0][2] == post->deck[0][2] && pre->deck[0][3] == post->deck[0][3] && pre->deck[0][4] == post->deck[0][4]
      && pre->deck[0][5] == post->deck[0][5] && pre->deck[0][6] == post->deck[0][6] && pre->deck[0][7] == post->deck[0][7]
      && pre->deck[0][8] == post->deck[0][8] && pre->deck[0][9] == post->deck[0][9] && pre->deck[0][10] == post->deck[0][10]){
        printf("state.deck[0]... not sufficiently changed as expected.");
        errors++;
  }
  
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
  if (post->handCount[0] != pre->handCount[0]){ 
     printf("state.handCount failed. (expected=%d, actual=%d)\n", pre->handCount[0], post->handCount[0]);
    errors++;  
  }
  if (pre->handCount[1] != post->handCount[1]){ 
    printf("state.handCount[1] failed. (expected=%d, actual=%d)\n", pre->handCount[1], post->handCount[1]);
    errors++;
  }
  if (pre->deckCount[0] != post->deckCount[0]){ 
     printf("state.deckCount[0] failed. (expected=%d, actual=%d)\n", pre->deckCount[0], post->deckCount[0]);
    errors++;
  }
  if (pre->discardCount[0] != post->discardCount[0]){
     printf("state.discardCount[0] failed. (expected=%d, actual=%d)\n", pre->discardCount[0], post->discardCount[0]);
     errors++;
  }
  if (pre->deckCount[1] != post->deckCount[1]){
     printf("state.deckCount[1] failed. (expected=%d, actual=%d)\n", pre->deckCount[1], post->deckCount[1]);
     errors++;
  }
  if (pre->discardCount[1] != post->discardCount[1]){
     printf("state.discardCount[1] failed. (expected=%d, actual=%d)\n", pre->discardCount[1], post->discardCount[1]);
     errors++;
  }
  if (post->playedCardCount != pre->playedCardCount){ 
     printf("state.playedCardCount failed. (expected=%d, actual=%d)\n", pre->playedCardCount, post->playedCardCount);
    errors++;
  }

  return errors;
}
