

//***--- End Turn ---***//
int endTurn(struct gameState *state) {
  int k;
  int i;
  int currentPlayer = whoseTurn(state);
  
  //Discard hand
  for (i = 0; i < state->handCount[currentPlayer]; i++){
    state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
    state->hand[currentPlayer][i] = -1;//Set card to -1
  }
  state->handCount[currentPlayer] = 0;//Reset hand count
    
  printf("Still no crash after discard\n");

  //Code for determining the player
  if (currentPlayer < (state->numPlayers - 1)){ 
    state->whoseTurn = currentPlayer + 1;//Still safe to increment
  }
  else{
    state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
  }
  printf("Still no crash after determining player\n");

  state->outpostPlayed = 0;
  state->phase = 0;
  state->numActions = 1;
  state->coins = 0;
  state->numBuys = 1;
  state->playedCardCount = 0;
  state->handCount[state->whoseTurn] = 0;

  printf("Still no crash after stateset\n");

  //int k; move to top
  //Next player draws hand
  for (k = 0; k < 5; k++){
    drawCard(state->whoseTurn, state);//Draw a card
  }
  printf("Still no crash after drawcard\n");

  //Update money
  updateCoins(state->whoseTurn, state , 0);

  return 0;
}

int main () {
endTurn(game)
}
