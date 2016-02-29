/******************
 * Eric Olson
 * CS362_Assignment5
 * Adventurer Card Function Random Test (Draw first 2 treasure from deck, discard rest)
 ******************/

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


int validate(struct gameState *pre, struct gameState *post, int errors);
void basic_setup(struct gameState *pre, struct gameState *post);
int scenario_stage(struct gameState *pre, struct gameState *post, int treasure1, int treasure2);

int main(){
  struct gameState *pre = malloc(sizeof(struct gameState)), *post = malloc(sizeof(struct gameState));
  struct infosStruct infos;
  int i, errors = 0, adventurer_pos;
  srand(time(NULL));
  
  printf("\n|------------------------------------------|\n");
  printf("  Running test on adventurer_play():\n");
  printf("|------------------------------------------|\n");
  
  /***** SCENARIO 1 *****/
  printf("Running Test Scenario...\n");
  //Setup Scenario:
  adventurer_pos = scenario_stage(pre, post, 0, 0);      
  infos.drawntreasure = 0;
  infos.currentPlayer = 0;
  infos.z = 0;
  //Have player 0 play adventurer card.  Would pass adventurer_pos if adventurer_play used handPos(bug).
  effectAdventure(post, &infos);
  //Check results.
  errors = validate(pre, post, errors);
  
  //Report Findings
  if (errors) { printf("Tests Complete: adventurer_play() failed %d tests.\n\n", errors); }
  else { printf("Tests Complete: No errors found.\n\n"); }

  return 0;  
}
  
int scenario_stage(struct gameState *pre, struct gameState *post, int treasure1, int treasure2){
  int decksize, discardsize, handsize, treasure_count = 0, adventurer_pos = -1, i;

  basic_setup(pre, post);
  //Clear out hand/deck/discard for random assignment.
  memset(post->deck[0], 0, MAX_DECK * sizeof(int));
  memset(post->hand[0], 0, 5 * sizeof(int));
  memset(post->discard[0], 0, MAX_DECK * sizeof(int));
  
  decksize = 10;
  post->deckCount[0] = decksize;
  for (i = 0; i < decksize; i++){
     post->deck[0][i] = 10;
  }
  
  //Randomize discard (with at minimum 10 deck/discard cards)
  discardsize = 10;
  post->discardCount[0] = discardsize;
  for (i = 0; i < discardsize; i++){
     post->discard[0][i] = 10;
  }
  
  //Randomize hand
  handsize = 5;  //To allow room for 2 treasure cards and 1 adventurer card to be added.
  post->handCount[0] = handsize;
  for (i = 0; i < handsize; i++){
     post->hand[0][i] = adventurer;
  }
  
  //Make sure pre == post.
  memcpy(pre, post, sizeof(struct gameState));

  return 5;  //So we know which card to play.
}
  
  
void basic_setup(struct gameState *pre, struct gameState *post){
  int i, j, try, k[10] = { 0 };
  //Clear any previous data.
  memset(pre, 0, sizeof(struct gameState));
  memset(post, 0, sizeof(struct gameState));
  
  //randomize kingdom cards & initalize a game.
  k[0] = adventurer;
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
  if (initializeGame(2, k, ((rand() % 500) + 1), post) != 0) { printf( "Initalization of game failed.\n"); }
  
  //Ensure player 0 has adventurer card in hand.
  post->hand[0][5] = adventurer;
  post->handCount[0]++;
  
  //And create identical copies of gamestate before test.
  memcpy(pre, post, sizeof(struct gameState));
}
  
int validate(struct gameState *pre, struct gameState *post, int errors){
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
  //Actually check if player drew 2 treasure cards (and played 1):
  if (post->handCount[0] != pre->handCount[0] + 1 || 
      post->hand[0][post->handCount[0] - 2] < 4 || post->hand[0][post->handCount[0] - 2] > 6 ||
      post->hand[0][post->handCount[0] - 1] < 4 || post->hand[0][post->handCount[0] - 1] > 6){ 
        printf("state.handCount failed. (expected=%d, actual=%d)", pre->handCount[0] + 1, post->handCount[0]);
        if (post->handCount[0] >= 2){
          printf(" last 2 in hand = %d,%d\n", post->hand[0][post->handCount[0] - 2], 
	          post->hand[0][post->handCount[0] - 1]);
        }
	else { printf("\n"); }
    errors++;  
  }
  if (pre->handCount[1] != post->handCount[1]){ 
    printf("state.handCount[1] failed. (expected=%d, actual=%d)\n", pre->handCount[1], post->handCount[1]);
    errors++;
  }
  //Ensure 2 cards removed from deck/discard.
  if (pre->deckCount[0] + pre->discardCount[0] != post->deckCount[0] + post->discardCount[0] + 2){ 
    printf("Deck+Discard count failed. (expected=%d, actual=%d)\n",
	   (pre->deckCount[0] + pre->discardCount[0]) - 2, (post->deckCount[0] + post->discardCount[0]));
    errors++;
  }
  if (pre->deckCount[1] != post->deckCount[1]){ 
    printf("state.deckCount[1] failed. (expected=%d, actual=%d)\n", pre->deckCount[1], post->deckCount[1]);
    errors++;
  }
  if (pre->discardCount[1] != post->discardCount[1]){ 
    printf("state.discardCount[1] failed. (expected=%d, actual=%d)\n", 
	   pre->discardCount[1], post->discardCount[1]);
    errors++;
  }
  //Ensure advenurer card moved to played after use.
  if (post->playedCardCount != pre->playedCardCount + 1){ 
    printf("state.playedCardCount failed. (expected=%d, actual=%d)\n", pre->playedCardCount + 1, post->playedCardCount);
    errors++;
  }

  return errors;
}
