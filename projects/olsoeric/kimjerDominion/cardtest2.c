/******************
 * Eric Olson
 * CS362_Assignment3
 * Adventurer Card Function Test
 ******************/

#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int validate(struct gameState *pre, struct gameState *post, int errors, int hand, int played);
void basic_setup(struct gameState *pre, struct gameState *post);
void scenario_stage(struct gameState *pre, struct gameState *post, int treasure1, int treasure2);

int main(){
  struct gameState *pre = malloc(sizeof(struct gameState)), *post = malloc(sizeof(struct gameState));
  int i, errors = 0;
  srand(time(NULL));
  
  printf("\n|------------------------------------------|\n");
  printf("  Running tests on adventurer_play():\n");
  printf("|------------------------------------------|\n");
  
  /***** SCENARIO 1 - New game, hand=6, deck=10(only 2 coppers), discard=0  *****/
  printf("Running Scenario 1...\n");
  //Setup Scenario:
  scenario_stage(pre, post, copper, copper);
  //Have player 0 play adventurer card.
  adventurer_play(0, post);
  //Check hand went from 6 to 7, deck+discard went down by 2, played went from 0 - 1.
  errors = validate(pre, post, errors, 7, 1);
  printf("Errors so far %d\n", errors);

  /***** SCENARIO 2 - New game, hand=6, deck=10(only 2 silvers), discard=0  *****/
  printf("Running Scenario 2...\n");
  //Setup Scenario:
  scenario_stage(pre, post, silver, silver);
  //Have player 0 play adventurer card.
  adventurer_play(0, post);
  //Check hand went from 6 to 7, deck+discard went down by 2, played went from 0 - 1.
  errors = validate(pre, post, errors, 7, 1);
  printf("Errors so far %d\n", errors);
  
  /***** SCENARIO 3 - New game, hand=6, deck=10(only 2 gold), discard=0  *****/
  printf("Running Scenario 3...\n");
  //Setup Scenario:
  scenario_stage(pre, post, gold, gold);
  //Have player 0 play adventurer card.
  adventurer_play(0, post);
  //Check hand went from 6 to 7, deck+discard went down by 2, played went from 0 - 1.
  errors = validate(pre, post, errors, 7, 1);
  printf("Errors so far %d\n", errors);
  
  
  /***** SCENARIO 4(Randoms) - New game, hand=6, deck=10(2 random treasure types), discard=0  *****/
  printf("Running 5 Random Scenarios...\n");
  for (i = 0; i < 5; i++){
    //Setup Scenario:
    scenario_stage(pre, post, ((rand() % 3) + 4), ((rand() % 3) + 4));
    //Have player 0 play adventurer card.
    adventurer_play(0, post);
    //Check hand went from 6 to 7, deck+discard went down by 2, played went from 0 - 1.
    errors = validate(pre, post, errors, 7, 1);
    printf("Errors so far %d\n", errors);
  }

  
  //Report Findings
  if (errors) { printf("Tests Complete: adventurer_play() failed %d tests.\n", errors); }
  else { printf("Tests Complete: No errors found.\n"); }

  return 0;  
}
  
void scenario_stage(struct gameState *pre, struct gameState *post, int treasure1, int treasure2){
  int i;

  basic_setup(pre, post);
  //Ensure exactly 2 treasure cards only.
  memset(pre->deck[0], 0, MAX_DECK * sizeof(int));
  memset(pre->hand[0], 0, 5 * sizeof(int));
  memset(post->deck[0], 0, MAX_DECK * sizeof(int));
  memset(post->hand[0], 0, 5 * sizeof(int));
  pre->deckCount[0] = post->deckCount[0] = 10;
  i = rand() % 10;
  pre->deck[0][i] = post->deck[0][i] = treasure1;  //Assign 1st treasure.
  i = rand() % 10;
  //Assign 2nd treasure randomly, or 4 away from current treasure if chosen at random again.
  if (pre->deck[0][i] != treasure1){ pre->deck[0][(i + 4) % 10] = post->deck[0][(i + 4) % 10] = treasure2; }
  else { pre->deck[0][i] = post->deck[0][i] = treasure2; } 
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
  
int validate(struct gameState *pre, struct gameState *post, int errors, int hand, int played){
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
  //Actually check if player drew 2 treasure cards (intended functionality):
  if (post->handCount[0] < 2 || post->handCount[0] != hand || 
      post->hand[0][post->handCount[0] - 2] < 4 || post->hand[0][post->handCount[0] - 2] > 6 ||
      post->hand[0][post->handCount[0] - 1] < 4 || post->hand[0][post->handCount[0] - 1] > 6){ 
        printf("state.handCount failed. (expected=%d, actual=%d)", hand, post->handCount[0]);
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
    printf("Deck+Discard count failed. (expected=%d, actual=%d)\n",(pre->deckCount[0] + pre->discardCount[0]),
	   (post->deckCount[0] + post->discardCount[0] + 2));
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
  if (post->playedCardCount != played){ 
    printf("state.playedCardCount failed. (expected=%d, actual=%d)\n", played, post->playedCardCount);
    errors++;
  }

  return errors;
}
