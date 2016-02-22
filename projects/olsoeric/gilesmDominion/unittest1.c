/******************
 * Eric Olson
 * CS362_Assignment3
 * Update Coins Function Test
 ******************/

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int validate(struct gameState *pre, struct gameState *post, int errors, int treasures, int bonus);
void basic_setup(struct gameState *pre, struct gameState *post);

int main(){
  struct gameState *pre = malloc(sizeof(struct gameState)), *post = malloc(sizeof(struct gameState));
  int i, j, cards, treasures, bonus, errors = 0;
  srand(time(NULL));
  
  printf("\n|------------------------------------------|\n");
  printf("  Running tests on updateCoins():\n");
  printf("|------------------------------------------|\n");
  
  /***** RANDOM SCENARIO *****/
  printf("Running 50,000 Random Scenarios...\n");
  for (i = 0; i < 50000; i++){
    //Setup Scenario:
    basic_setup(pre, post);
    //Stage Hand with between 5-20 random cards.
    cards = ((rand() % 16) + 5);
    treasures = 0;
    bonus = rand() % 10;
    for (j = 0; j < cards; j++){
       post->hand[0][j] = (rand() % 27);  //Assign a random card.
       //And add to treasures count if needed.
       if (post->hand[0][j] == copper) { treasures++; }
       if (post->hand[0][j] == silver) { treasures = treasures + 2; }
       if (post->hand[0][j] == gold) { treasures = treasures + 3; }
    }
    post->handCount[0] = cards;
    //Ensure pre & post are equal
    memcpy(pre, post, sizeof(struct gameState));
    //Test updateCoins().
    updateCoins(0, post, bonus);
    //Check hand went from 6 to 9, deck went from 5 to 1, buy from 1 - 2, and played went from 0 - 1.
    errors = validate(pre, post, errors, treasures, bonus);
  }
 
  
  //Report Findings
  if (errors) { printf("Tests Complete: updateCoins() failed %d tests.\n", errors); }
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
  
int validate(struct gameState *pre, struct gameState *post, int errors, int treasures, int bonus){
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
  //Testing coins actually incremented correctly based on stating criteria passed in.
  if ((treasures + bonus) != post->coins){ 
    printf("state.coins failed. (expected=%d, actual=%d)\n", (pre->coins + treasures + bonus), post->coins);
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
