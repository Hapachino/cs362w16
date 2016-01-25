/*
Testing Function: draw_card

Steps:
1. Check if deck is empty
	1.1 If deck is empty, shuffle discard pile to deck
		1.1.1 Check that deck count is greater than 0
	1.2 Set the discard pile count to 0
2. Add card to hand
3. Increment hand count
4. Decrement deck count

Things to check to ensure pass:
- Hand count + 1
- Deck count - 1
- Draw a card with empty draw deck
- Draw a card with all cards in hand
*/

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int totalDeckCount(int player, struct gameState *state);
int playTreasures(int player, struct gameState *state);
int discardAll(int player, struct gameState *state);
int discardHand(int player, struct gameState *state);
int numDiscards(int player, struct gameState *state);
int checkHand(int orig_hand_count, int offset, int player, struct gameState *state);
int numDeck(int player, struct gameState *state);
int initTestGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state);
int initTurn(int player, struct gameState *state);
int checkDeck(int player, struct gameState *previousState, struct gameState *state);

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

}

/***************************************************
* resets all the card effect stuff from previous cards
* and draws 5 cards
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
* plays all treasures in hand
****************************************************/
int playTreasures(int player, struct gameState *state){
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

/*
Param: orig_hand_count - original count in hand
Param: offset - the number it should have increased or decreased (added)
*/
int checkHand(int orig_hand_count, int offset, int player, struct gameState *state){
  if ((orig_hand_count + offset) != numHandCards(state)){
    printf("ERROR: HAND COUNT\n");
    return 1;
  }

  return 0;
}

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
    printf("ERROR: DECK COUNT\n");
    return 1;
  }
  return 0;
}

int main (int argc, char** argv) {
  struct gameState G;
  struct gameState previousG;
  int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

  int seed = 2;
  

  int i=0;
  int j = 0;
  int limit = 0;
  int total_deck_count = 0;
  int money = 0;
  int hand_count = 0;
  int total_other_deck_count = 0;
  int discard_count = 0;
  int other_discard_count = 0;
  int deck_count_err = 0;
  int hand_count_err = 0;
  int offset = 0;

  for (i = 0; i < 1; i++){
    initTestGame(2, k, seed, &G);
    limit = 0;
    total_deck_count = 0;
    money = 0;
    hand_count = 0;

    if (whoseTurn(&G) == 0) {

      total_deck_count = totalDeckCount(0,&G);
      
      //draw card with empty hand
      //if this doesnt work, the rest definitely won't
      previousG = G;
      drawCard(0,&G); 
      offset = 1; //should be 1 card more
      if (checkDeck(0,&previousG,&G)){
        continue;
      }
      if (checkHand(hand_count,offset,0,&G)){
        continue;
      }

      //tests drawing all the rest of cards in deck
      //set limit for drawing all card in deck to hand
      if (MAX_HAND > total_deck_count){
        limit = total_deck_count - numHandCards(&G);
      }
      else {
        limit = MAX_HAND - numHandCards(&G);
      }

      hand_count = numHandCards(&G);
      for (j = 0; j < limit; j++) { //draw all rest of cards in deck
        drawCard(0,&G);  
      }
      checkHand(hand_count,limit, 0, &G); //should be offset by limit

      //check that another card is not drawn when deck and discard are empty
      hand_count = numHandCards(&G);
      drawCard(0,&G);
      offset = 0; //hand count should not change, so no offset
      checkHand(hand_count,offset,0,&G);

      //check when all cards are in discard pile
      drawCard(0,&G);
      discardAll(0,&G);
      offset = 1;
      hand_count = numHandCards(&G);
      previousG = G;
      drawCard(0,&G);
      checkDeck(0,&previousG,&G);
      checkHand(hand_count,offset,0,&G);
      
    }
    
  } // end of for
  return 0;
}
