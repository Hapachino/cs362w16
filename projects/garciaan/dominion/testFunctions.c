#include "dominion.h"
#include "dominion_helpers.h"
#include "testFunctions.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

/****************************************************
* everything in the default init except does not draw 
* cards or set a players turn. Use initTurn
****************************************************/
int initTestGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state){
  int i;
  int j;   
  //set up random number generator
  SelectStream(1);
  PutSeed((long)randomSeed);
  
  //check number of players
  if (numPlayers > MAX_PLAYERS || numPlayers < 2) {
    return -1;
  }

  //set number of players
  state->numPlayers = numPlayers;

  //check selected kingdom cards are different
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      if (j != i && kingdomCards[j] == kingdomCards[i]) {
        return -1;
      }
    }
  }


  //initialize supply
  ///////////////////////////////

  //set number of Curse cards
  if (numPlayers == 2) {
    state->supplyCount[curse] = 10;
  }
  else if (numPlayers == 3) {
    state->supplyCount[curse] = 20;
  }
  else {
    state->supplyCount[curse] = 30;
  }

  //set number of Victory cards
  if (numPlayers == 2) {
    state->supplyCount[estate] = 8;
    state->supplyCount[duchy] = 8;
    state->supplyCount[province] = 8;
  }
  else {
    state->supplyCount[estate] = 12;
    state->supplyCount[duchy] = 12;
    state->supplyCount[province] = 12;
  }

  //set number of Treasure cards
  state->supplyCount[copper] = 60 - (7 * numPlayers);
  state->supplyCount[silver] = 40;
  state->supplyCount[gold] = 30;

  //set number of Kingdom cards
  for (i = adventurer; i <= treasure_map; i++){        //loop all cards
    for (j = 0; j < 10; j++){              //loop chosen cards
      if (kingdomCards[j] == i){
        //check if card is a 'Victory' Kingdom card
        if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens){
          if (numPlayers == 2){ 
            state->supplyCount[i] = 8; 
          }
          else { 
            state->supplyCount[i] = 12; 
          }
        }
        else {
          state->supplyCount[i] = 10;
        }
        break;
      }
      else {   //card is not in the set choosen for the game
        state->supplyCount[i] = -1;
      }
    }
  }

  ////////////////////////
  //supply intilization complete

  //set player decks
  for (i = 0; i < numPlayers; i++){
    state->deckCount[i] = 0;
    for (j = 0; j < 3; j++){
      state->deck[i][j] = estate;
      state->deckCount[i]++;
    }
    for (j = 3; j < 10; j++){
     state->deck[i][j] = copper;
     state->deckCount[i]++;   
    }
  }

  //shuffle player decks
  for (i = 0; i < numPlayers; i++){
    if ( shuffle(i, state) < 0 ){
      return -1;
    }
  }

  //set counts to 0
  for (i = 0; i < numPlayers; i++)
    {  
      //initialize hand size to zero
      state->handCount[i] = 0;
      state->discardCount[i] = 0;
    }
  
  //set embargo tokens to 0 for all supply piles
  for (i = 0; i <= treasure_map; i++){
    state->embargoTokens[i] = 0;
  }
  return 0;
}

/***************************************************
* resets all the card effect stuff from previous cards
* and draws 5 cards
* NOTE: THIS DOES NOT FOLLOW GAME RULES. TESTING ONLY
* This function assumed to be used at the beginning of a player's turn
***************************************************/
int initTurn(int player, struct gameState *state){
  int i = 0;

  //initialize player's turn
  state->outpostPlayed = 0;
  state->phase = 0;
  state->numActions = 1;
  state->numBuys = 1;
  state->playedCardCount = 0;
  state->whoseTurn = 0;
  state->handCount[player] = 0;
  updateCoins(player, state, 0);

  //Moved draw cards to here, only drawing at the start of a turn
  for (i = 0; i < 5; i++){
    drawCard(player, state);
  }
  return 0;
}

/****************************************************
* Creates an array of 18 spots all set to default_num (0,1). 
* Change spot to 1 using game_state_vars to 
* test specific spots in the gameState struct
****************************************************/
void createCompareStateArray(int *array,int default_num){
  int i;
  for (i = 0; i < last_tester; i++){
    array[i] = default_num;
  }
}

/****************************************************
* compares equality of states. Checks the variables in 
* the spots in the array corresponding to the order of
* declaration in the struct
* 0 means not equal, 1 means either equal or not tested
****************************************************/
void compareStates(struct gameState *state1, struct gameState *state2, int* test, int *results, int verbose){
  int state_index[last_tester]; //18 variables/arrays in struct gameState + 1 for checking other player affected
  int i;
  int j;
  for (i = 0; i < last_tester; i++){
    state_index[i] = 1;
  }
  if (verbose)
    printf("UNINTENTIONALLY AFFECTED: \n");
  if (test[num_players]){
    if (state1->numPlayers != state2->numPlayers){
      state_index[num_players] = 0;
      if (verbose)
        printf("- Num Players\n");
    }
  }
  if (test[supply_count]){
    for (i = 0; i < last_card + 1; i++){
      if (state1->supplyCount[i] != state2->supplyCount[i]){
        state_index[supply_count] = 0;
        if (verbose)
          printf("- Supply Count\n");
        break;
      }
    }
  }
  if (test[embargo_tokens]){
    for (i = 0; i < last_card + 1; i++){
      if (state1->embargoTokens[i] != state2->embargoTokens[i]){
        state_index[embargo_tokens] = 0;
        if (verbose)
          printf("- Embargo Tokens\n");
        break;
      }
    }
  }
  if (test[outpost_played]){
    if (state1->outpostPlayed != state2->outpostPlayed){
      state_index[outpost_played] = 0;
      if (verbose)
        printf("- Outpost Played\n");
    }
  }
  if (test[outpost_turn]){
    if (state1->outpostTurn != state2->outpostTurn){
      state_index[outpost_turn] = 0;
      if (verbose) 
        printf("- Outpost Turn\n");
    }
  }
  if (test[whose_turn]){
    if (state1->whoseTurn != state2->whoseTurn){
      state_index[whose_turn] = 0;
      if (verbose)
        printf("- Whose Turn\n");
    }
  }
  if (test[num_phase]){
    if (state1->phase != state2->phase){
      state_index[num_phase] = 0;
      if (verbose)
        printf("- Num Phase\n");
    }
  }
  if (test[num_actions]){
    if (state1->numActions != state2->numActions){
      state_index[num_actions] = 0;
      if (verbose)
        printf("- Num Actions\n");
    }
  }
  if (test[num_coins]){
    if (state1->coins != state2->coins){
      state_index[num_coins] = 0;
      if (verbose)
        printf("- Num Coins\n");
    }
  }
  if (test[num_buys]){
    if (state1->numBuys != state2->numBuys){
      state_index[num_buys] = 0;
      if (verbose)
        printf("- Num Buys\n");
    }
  }
  if (test[player_hand]){
    for (i = 0; i < MAX_PLAYERS; i++){
      for (j = 0; j < MAX_HAND; j++){
        if (state1->hand[i][j] != state2->hand[i][j]) {
          state_index[player_hand] = 0;
          if (verbose)
            printf("- Player Hand\n");
          break;
        }
      }
      if (state_index[player_hand] == 0)
        break;
    }
  }
  if (test[player_hand_count]){
    for (i = 0; i < MAX_PLAYERS; i++){
      if (state1->handCount[i] != state2->handCount[i]){
        state_index[player_hand_count] = 0;
        if (verbose)
          printf("- Player Hand Count\n");
        break;
      }
    }
  }
  if (test[player_deck]){
    for (i = 0; i < MAX_PLAYERS; i++){
      for (j = 0; j < MAX_DECK; j++){
        if (state1->deck[i][j] != state2->deck[i][j]){
          state_index[player_deck] = 0;
          if (verbose)
            printf("- Player Deck\n");
          break;
        }
      }
      if (state_index[player_deck] == 0) 
        break;
    }
  }
  if (test[player_deck_count]){
    for (i = 0; i < MAX_PLAYERS; i++){
      if (state1->deckCount[i] != state2->deckCount[i]){
        state_index[player_deck_count] = 0;
        if (verbose)
          printf("- Player Deck Count\n");
        break;
      }
    }
  }
  if (test[player_discard]){
    for (i = 0; i < MAX_PLAYERS; i++){
      for (j = 0; j < MAX_DECK; j++){
        if (state1->discard[i][j] != state2->discard[i][j]){
          state_index[player_discard] = 0;
          if (verbose)
            printf("- Player Discard Pile\n");
          break;
        }
      }
      if (state_index[player_discard] == 0) 
        break;
    }
  }
  if (test[player_discard_count]){
    for (i = 0; i < MAX_PLAYERS; i++){
      if (state1->discardCount[i] != state2->discardCount[i]){
        state_index[player_discard_count] = 0;
        if (verbose)
          printf("- Player Discard Pile Count\n");
        break;
      }
    }
  }
  if (test[played_cards]){
    for (i = 0; i < MAX_DECK; i++){
      if (state1->playedCards[i] != state2->playedCards[i]){
        state_index[played_cards] = 0;
        if (verbose)
          printf("- Played Cards\n");
        break;
      }
    }
  }
  if (test[played_card_count]){
    if (state1->playedCardCount != state2->playedCardCount){
      state_index[played_card_count] = 0;
      if (verbose)
        printf("- Played Card Count\n");
    }
  }

  if (whoseTurn(state1) == whoseTurn(state2)){
    for (i = 0; i < MAX_PLAYERS; i++){
      if (i == whoseTurn(state1)){
        continue;
      }
      if (checkOtherPlayer(state1,state2,i,verbose) == 0){
        state_index[other_player] = 0;
        if (verbose){
          printf("- Other Player\n");
        }
        break;
      }

    }
  }

  for (i = 0; i < played_card_count; i++){
    results[i] = state_index[i];
  }
}
/****************************************************
* Very similar to compareStates, but checks if another player changed anything
* Return 0 if other player changed, 1 if stayed the same
****************************************************/
int checkOtherPlayer(struct gameState *state1, struct gameState *state2, int player, int verbose){
  int j;
  int change = 0;
  if (verbose)
    printf("PLAYER %d WAS UNINTENTIONALLY AFFECTED IN: \n", player);
  for (j = 0; j < MAX_HAND; j++){
    if (state1->hand[player][j] != state2->hand[player][j]) {
      change = 1;
      if (verbose)
        printf("- Player %d Hand\n",player);
      break;
    }
  }
  if (state1->handCount[player] != state2->handCount[player]){
    change = 1;
    if (verbose)
      printf("- Player %d Hand Count\n", player);
  }
  for (j = 0; j < MAX_DECK; j++){
    if (state1->deck[player][j] != state2->deck[player][j]){
      change = 1;
      if (verbose)
        printf("- Player %d Deck\n", player);
      break;
    }
  }
  if (state1->deckCount[player] != state2->deckCount[player]){
    change = 1;
    if (verbose)
      printf("- Player %d Deck Count\n", player);
  }
  for (j = 0; j < MAX_DECK; j++){
    if (state1->discard[player][j] != state2->discard[player][j]){
      change = 1;
      if (verbose)
        printf("- Player %d Discard Pile\n", player);
      break;
    }
  }
  if (state1->discardCount[player] != state2->discardCount[player]){
    change = 1;
    if (verbose)
      printf("- Player %d Discard Pile Count\n", player);
  }
  if (change == 0){
    return 1;
  }
  else {
    return 0;
  }
}
/****************************************************
* returns 0 if not all 1s (equal), exluding excludes (marked
* as zeros), the ones that should be different
* PARAM: excludes
*   - If you want to test everything except what you know
*     is going to change, pass a createCompareStateArray 
*     with all 1s except for the spots you know are going
*     to change which are marked as 0s
****************************************************/
int checkStates(struct gameState *state1, struct gameState *state2, int *excludes, int verbose){
  int *results = malloc(played_card_count * sizeof(int));
  int i;
  createCompareStateArray(results,0);
  compareStates(state1,state2,excludes,results,verbose);
  for (i = 0; i < played_card_count; i++){
    if (results[i] == 0){
      return 0;
    }
  }
  return 1;
}

/****************************************************
* returns the total number of cards the player has
***************************************************/
int totalDeckCount(int player, struct gameState *state){
  int i;
  int deck_count = 0;
  for (i = 0; i < last_card; i++){
    deck_count += fullDeckCount(player,i,state);
  }
  return deck_count;
}

/****************************************************
* returns the number of cards in the drawable deck (total-discard-hand)
*****************************************************/
int numDeck(int player, struct gameState *state){
  return state->deckCount[player];
}

/****************************************************
* Returns sum of all treasures in hand
****************************************************/
int countTreasures(int player, struct gameState *state){
  int i;
  int money = 0;
  while(i < numHandCards(state)){
    if (handCard(i, state) == copper){
      playCard(i, -1, -1, -1, state);
      money++;
    }
    else if (handCard(i, state) == silver){
      playCard(i, -1, -1, -1, state);
      money += 2;
    }
    else if (handCard(i, state) == gold){
      playCard(i, -1, -1, -1, state);
      money += 3;
    }
    i++;
  }
  return money;
}

/****************************************************
* returns number of discarded cards
****************************************************/
int numDiscards(int player, struct gameState *state){
  return state->discardCount[player];
}
/****************************************************
* move everything (deck + hand) to discard pile by drawing 
* all and then discarding hand
****************************************************/
int discardAll(int player, struct gameState *state){
  int i = 0;
  for (i = 0; i < numDeck(player,state); i++){
    drawCard(player,state);
  }
  discardHand(player,state);

  return 0;
}

/****************************************************
* discards entire hand
****************************************************/
int discardHand(int player, struct gameState *state){
  int i = 0;
  for (i = 0; i < state->handCount[player]; i++){
    state->discard[player][state->discardCount[player]++] = state->hand[player][i];//Discard
    state->hand[player][i] = -1;//Set card to -1
  }
  state->handCount[player] = 0;//Reset hand count
  
  return 0;
}

/****************************************************
* Checks old hand  + offset vs current hand
* Return: 0 on pass, -1 otherwise
* Param: orig_hand_count - original count in hand
* Param: offset - the number it should have increased or decreased (added)
****************************************************/
int checkHand(int orig_hand_count, int offset, int player, struct gameState *state){
  if ((orig_hand_count + offset) != numHandCards(state)){
    return -1;
  }

  return 0;
}

/****************************************************
* Checks for card removal from game, deck decrementing,
* and accidental discarding. 
****************************************************/
int checkDeck(int player, struct gameState *previousState, struct gameState *state){
  int deck_count_err = 0;
  int previous_deck_count = 0;
  //Checks if card is removed from game / trashed
  if (totalDeckCount(player,previousState) != totalDeckCount(player,state)){
    deck_count_err = 1;
  }      
  //Checks if drawable deck is decremented accounting for reshuffle
  if (numDiscards(player,previousState) == (totalDeckCount(player,previousState) - numHandCards(previousState)) && numDiscards(player,previousState) > 0){
    previous_deck_count = numDiscards(player,previousState); //discards become new deck
  }
  else {
    previous_deck_count = numDeck(player,previousState);
  }
  if ((previous_deck_count - 1) != numDeck(player,state)){
    deck_count_err = 1;
  } 
  //Check to see if deck was shuffled when all card in discards
  if (numDiscards(player,previousState) == (totalDeckCount(player,previousState) - numHandCards(previousState)) && numDiscards(player,previousState) > 0){
    //if the discard pile is still 0 after drawing
    if (numDiscards(player,state) != 0 || numDeck(player,state) == 0){
      deck_count_err = 1;
    }
  }

  if (deck_count_err){
    return -1;
  }
  return 0;
}

/****************************************************
* Raises the error flag if passed a false (0).
* Error if flag is set to 1 
****************************************************/
void checkError(int pass){
  if (pass == 0){
    ERROR = 1;
  }
}

/****************************************************
* Resets the error flag (back to 0)
****************************************************/
void resetError(){
  ERROR = 0;
}

/****************************************************
* Checks for card removal from game, deck decrementing,
* and accidental discarding. 
****************************************************/
void printResults(){
  if (ERROR != 0){
    printf("\t- RESULT: FAIL\n\n");
  }
  else {
    printf("\t- RESULT: PASS\n\n");
  }
}

/****************************************************
* SIGNAL HANDLERS
****************************************************/
void timeout(int signum){
  printf("\t- RESULT: FAIL - TIMEOUT - EXITING...\n\n");
    printf(">>>>>>>>>>> FAILURE: Testing incomplete <<<<<<<<<<<\n\n");

  exit(0);
}

void handle_segfault(int signum){
  printf("\t- RESULT: FAIL - SEGFAULT - EXITING...\n\n");
  printf(">>>>>>>>>>> FAILURE: Testing incomplete <<<<<<<<<<<\n\n");

  exit(0);
}
