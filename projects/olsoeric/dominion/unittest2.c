/******************
 * Eric Olson
 * CS362_Assignment3
 * gainCard Function Test
 ******************/

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int validate(struct gameState *pre, struct gameState *post, int errors, int card, int toFlag, int failed);
void basic_setup(struct gameState *pre, struct gameState *post);

int main(){
  struct gameState *pre = malloc(sizeof(struct gameState)), *post = malloc(sizeof(struct gameState));
  int i, j, card, toFlag, failed, errors = 0;
  srand(time(NULL));
  
  printf("\n|------------------------------------------|\n");
  printf("  Running tests on gainCard():\n");
  printf("|------------------------------------------|\n");
  
  /***** RANDOM SCENARIO *****/
  printf("Running 50,000 Random Scenarios...\n");
  for (i = 0; i < 50000; i++){
    //Setup Scenario:
    basic_setup(pre, post);
    //Stage # of available cards between 0-10 randomly.
    for (j = 0; j <= treasure_map; j++){
       if (post->supplyCount[j] != -1) { post->supplyCount[j] = (rand() % 11); }
    }
    //Ensure pre & post are equal
    memcpy(pre, post, sizeof(struct gameState));
    //Test gainCard().
    card = rand() % 27;
    toFlag = rand() % 3;
    failed = gainCard(card, post, toFlag, 0);
    //Validate Correct Results
    errors = validate(pre, post, errors, card, toFlag, failed);
  }
 
  
  //Report Findings
  if (errors) { printf("Tests Complete: gainCard() failed %d tests.\n", errors); }
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
  
int validate(struct gameState *pre, struct gameState *post, int errors, int card, int toFlag, int failure){
  int i, hnd = 0, dck = 0, dsc = 0;

  //Used to determine if hand, deck or discount counts should increase.
  if (!failure){
    if (toFlag == 0) { dsc++; }
    if (toFlag == 1) { dck++; }
    if (toFlag == 2) { hnd++; }
  }
  
  //Check pre vs post gameState's to ensure intended changes occured, and no unintended changes occured.
  //Check if card was in fact drawn that it is in correct location.
  if (!failure){
    if (toFlag == 0){
      if (post->discard[0][post->discardCount[0] - 1] != card){
         printf("state.discard[0][last card] failed. (expected=%d, actual=%d)\n", card, post->discard[0][post->discardCount[0] - 1]);
         errors++;
      }
    }
    else if (toFlag == 1){
      if (post->deck[0][post->deckCount[0] - 1] != card){
         printf("state.deck[0][last card] failed. (expected=%d, actual=%d)\n", card, post->deck[0][post->deckCount[0] - 1]);
         errors++;
      }
    }
    else if (toFlag == 2){
      if (post->hand[0][post->handCount[0] - 1] != card){
        printf("state.hand[0][last card] failed. (expected=%d, actual=%d)\n", card, post->hand[0][post->handCount[0] - 1]);
        errors++;
      }
    }
  }
  if (pre->numPlayers != post->numPlayers){ 
    printf("state.numPlayers failed. (expected=%d, actual=%d)\n", pre->numPlayers, post->numPlayers);
    errors++;   
  }
  for (i = 0; i < treasure_map + 1; i++) {
    //Check that card was not drawn from supply.
    if (failure || i != card){    
      if (pre->supplyCount[i] != post->supplyCount[i]){ 
        printf("state.supplyCount[%d] failed. (expected=%d, actual=%d)\n", 
	       i, pre->supplyCount[i], post->supplyCount[i]);
        errors++;  
      }
    }
    //Check that card WAS drawn from supply (only tested if gainCard was a success and on cardtype drawn).
    else{
      if (pre->supplyCount[i] != (post->supplyCount[i] + 1)){
        printf("state.supplyCount[%d] failed. (expected=%d, actual=%d)\n",
          i, (pre->supplyCount[i] - 1), post->supplyCount[i]);
          errors++;
      }
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
    printf("state.coins failed. (expected=%d, actual=%d)\n", pre->coins , post->coins);
    errors++;  
  }
  if (pre->numBuys != post->numBuys){ 
     printf("state.numBuys failed. (expected=%d, actual=%d)\n", pre->numBuys, post->numBuys);
    errors++;  
  }
  //If successful and drawn to hand check for +1, same otherwise.
  if (pre->handCount[0] != (post->handCount[0] - hnd)){
     printf("state.handCount failed. (expected=%d, actual=%d)\n", (pre->handCount[0] + hnd), post->handCount[0]);
    errors++;  
  }
  if (pre->handCount[1] != post->handCount[1]){ 
    printf("state.handCount[1] failed. (expected=%d, actual=%d)\n", pre->handCount[1], post->handCount[1]);
    errors++;
  }
  //If successful and drawn to deck check for +1, same otherwise.
  if (pre->deckCount[0] != (post->deckCount[0] - dck)){ 
     printf("state.deckCount[0] failed. (expected=%d, actual=%d)\n", (pre->deckCount[0] + dck), post->deckCount[0]);
    errors++;
  }
  //If successful and drawn to discard check for +1, same otherwise.
  if (pre->discardCount[0] != (post->discardCount[0] - dsc)){
     printf("state.discardCount[0] failed. (expected=%d, actual=%d)\n", (pre->discardCount[0] + dsc), post->discardCount[0]);
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
