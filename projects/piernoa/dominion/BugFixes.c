My Bugs:
  /* * * * * * * * * * * * * *  Incorrect bug reported for scoreFor, shown here to report change history * * * * * * * * * * * * * * * *  * * */

  The scoreFor function had a bug which miscounts victory points in the player's deck.
  code before:
  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->deck[player][i] == curse) { score = score - 1; };
      if (state->deck[player][i] == estate) { score = score + 1; };
      if (state->deck[player][i] == duchy) { score = score + 3; };
      if (state->deck[player][i] == province) { score = score + 6; };
      if (state->deck[player][i] == great_hall) { score = score + 1; };
      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  code with fix:
  //score from deck
  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == curse) { score = score - 1; };
      if (state->deck[player][i] == estate) { score = score + 1; };
      if (state->deck[player][i] == duchy) { score = score + 3; };
      if (state->deck[player][i] == province) { score = score + 6; };
      if (state->deck[player][i] == great_hall) { score = score + 1; };
      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

  The score was being calculated based on the discount card size instaed of the
  deck count size. This was casing the error in reportin the users score. Since gdb
  is no longer installed on a mac, I used lldb, which essentially does the same
  thing as gdb.

  Adventurer hangs indefinitely due to an infinite loop, which results from the number of treasures drawn not being counted correctly.

  The above bug was actually reported in error, the correct code is:
  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->deck[player][i] == curse) { score = score - 1; };
      if (state->deck[player][i] == estate) { score = score + 1; };
      if (state->deck[player][i] == duchy) { score = score + 3; };
      if (state->deck[player][i] == province) { score = score + 6; };
      if (state->deck[player][i] == great_hall) { score = score + 1; };
      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }



  /* * * * * * * * * * * * * *  Smithy: * * * * * * * * * * * * * * * * * * */

  code before:
  //+3 Cards
  for (i = 0; i < 3; i++)
  {
    drawCard(currentPlayer - 1, state);
  }

  //discard card from hand
  discardCard(handPos, currentPlayer, state, 1)
  return 0;


  code after:
  //+3 Cards
  for (i = 0; i < 3; i++)
  {
    drawCard(currentPlayer, state);
  }

  //discard card from hand
  discardCard(handPos, currentPlayer, state, 0);
  return 0;

/* * * * * * * * * * * * * *  Adventurer: * * * * * * * * * * * * * * * * * * */

  code before
  while(drawntreasure<2){
    if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
      shuffle(currentPlayer - 1, state);
    }
    drawCard(currentPlayer, state);
    cardDrawn = state->hand[currentPlayer - 1 ][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    if (cardDrawn == copper && cardDrawn == silver || cardDrawn == gold)
    drawntreasure++;
    else{
      temphand[z]=cardDrawn;
      state->handCount[currentPlayer]; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  while(z-1<=0){
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }
  return 0;

  code after:
  while(drawntreasure<2){
    if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
      shuffle(currentPlayer, state);
    }
    drawCard(currentPlayer, state);
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
    drawntreasure++;
    else{
      temphand[z]=cardDrawn;
      state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  while(z-1>=0){
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }
  return 0;
