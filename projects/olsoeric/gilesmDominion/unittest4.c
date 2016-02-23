/******************
 * Eric Olson
 * CS362_Assignment3
 * discardCard Function Test
 ******************/

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int validate(struct gameState *pre, struct gameState *post, int errors, int cards, int tally, int played, int trashflag);
void basic_setup(struct gameState *pre, struct gameState *post);

int main(){
  struct gameState *pre = malloc(sizeof(struct gameState)), *post = malloc(sizeof(struct gameState));
  int i, j, cards, tally, played, trashflag, errors = 0;
  srand(time(NULL));
  
  printf("\n|------------------------------------------|\n");
  printf("  Running tests on discardCard():\n");
  printf("|------------------------------------------|\n");
  
  /***** 1 CARD Scenario *****/
  printf("Running Scenario 1...\n");
  //Setup Scenario:
  basic_setup(pre, post);
  //Stage Hand with 1 card.  
  post->hand[0][0] = (rand() % 27);  //Assign a random card.
  tally = post->hand[0][0];     
  post->handCount[0] = 1;
  //Ensure pre & post are equal
  memcpy(pre, post, sizeof(struct gameState));
  //Test discardCard().
  played = 0;
  trashflag = rand() % 2;
  discardCard(played, 0, post, trashflag);
  //Check final state.
  errors = validate(pre, post, errors, 1, tally, played, trashflag);
  
  /***** LAST CARD SCENARIO *****/
  printf("Running Scenario 2...\n");
  //Setup Scenario:
  basic_setup(pre, post);
  //Stage Hand with between 1-MAX_DECK random cards.  
  cards = ((rand() % MAX_HAND) + 1);
  tally = 0;
  for (j = 0; j < cards; j++){
     post->hand[0][j] = (rand() % 27);  //Assign a random card.
     //And add to hand tally for later comparison.
     tally = tally + post->hand[0][j];     
  }
  post->handCount[0] = cards;
  //Ensure pre & post are equal
  memcpy(pre, post, sizeof(struct gameState));
  //Test discardCard().
  played = cards - 1; //ensure play last card.
  trashflag = rand() % 2;
  discardCard(played, 0, post, trashflag);
  //Check final state.
  errors = validate(pre, post, errors, cards, tally, played, trashflag);
  
  /***** RANDOM SCENARIO *****/
  printf("Running 50,000 Random Scenarios...\n");
  for (i = 0; i < 50000; i++){
    //Setup Scenario:
    basic_setup(pre, post);
    //Stage Hand with between 1-MAX_DECK random cards.  
    cards = ((rand() % MAX_HAND) + 1);
    tally = 0;
    for (j = 0; j < cards; j++){
       post->hand[0][j] = (rand() % 27);  //Assign a random card.
       //And add to hand tally for later comparison.
       tally = tally + post->hand[0][j];     
    }
    post->handCount[0] = cards;
    //Ensure pre & post are equal
    memcpy(pre, post, sizeof(struct gameState));
    //Test discardCard().
    played = rand() % cards;
    trashflag = rand() % 2;
    discardCard(played, 0, post, trashflag);
    //Check final state.
    errors = validate(pre, post, errors, cards, tally, played, trashflag);
  }
 
  
  //Report Findings
  if (errors) { printf("Tests Complete: discardCard() failed %d tests.\n\n", errors); }
  else { printf("Tests Complete: No errors found.\n\n"); }

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
  
int validate(struct gameState *pre, struct gameState *post, int errors, int cards, int tally, int played, int trashflag){
  int i, check_tally = 0, not_trashed = 0;

  //Used to determine played value at end of round.
  if (!trashflag) { 
    not_trashed++;  //Used to determine played value at end of round.
    //Check if actual played card was put in played pile.
    if (post->playedCards[0] != pre->hand[0][played]){
       printf("state.playedCards[0] failed. (expected=%d, actual=%d)\n", pre->hand[0][played], post->playedCards[0]);
       errors++;
    }
  }
    
  //Check that the same cards remained in hand (minus played card). . .
  for (i = 0; i < post->handCount[0]; i++){
     check_tally = check_tally + post->hand[0][i];
  }
  tally = tally - pre->hand[0][played];  //Remove the played card from tally.
  if (tally != check_tally){
     printf("state.hand[0] card tally failed. (expected=%d, actual=%d)\n", tally, check_tally);
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
  //Confirm played card is removed from hand.
  if (post->handCount[0] != (pre->handCount[0] - 1)){ 
     printf("state.handCount failed. (expected=%d, actual=%d)\n", (pre->handCount[0] - 1), post->handCount[0]);
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
  //Confirm if card was not trashed that it is in the played pile.
  if (post->playedCardCount != (pre->playedCardCount + not_trashed)){ 
     printf("state.playedCardCount failed. (expected=%d, actual=%d)\n", (pre->playedCardCount + not_trashed), post->playedCardCount);
    errors++;
  }

  return errors;
}
