CS362 Assignment 2 - refactor.c - Spencer Winlaw

The code for the following 5 cards was refactored in dominion.c. Each card effect 
is now implemented in its own function rather than as part of the switch statement
in cardEffect() and function declarations have been added to the dominion.h header 
file. See the description found below each heading for implementation details along 
with descriptions of any bugs introduced per the instructions for Assignment 2.

----------------------------------------------------------------------------
Adventurer Card 
----------------------------------------------------------------------------
**Bug Introduced**: Omit check for silver when checking if cardDrawn is a treasure
				    card. drawnTreasure will not increment if silver is drawn and
				    treasure card will be discarded with temp hand instead of kept.

int playAdventurer(struct gameState *state)
{ 
  int currentPlayer = whoseTurn(state);
  int temphand[MAX_HAND];// moved above the if statement
  int drawntreasure=0;
  int cardDrawn;
  int z = 0;
  
  while(drawntreasure<2)
  {
    if (state->deckCount[currentPlayer] <1)//if the deck is empty we need to shuffle discard and add to deck
    {
    shuffle(currentPlayer, state);
    }
    drawCard(currentPlayer, state);
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    //if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) *ORIGINAL CODE*
    if (cardDrawn == copper || cardDrawn == gold) //*BUG INTRODUCED* - Omit check for silver
      drawntreasure++;
    else
    {
      temphand[z]=cardDrawn;
      state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
      z++;
    }
  }
  
  while(z-1>=0)
  {
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }
  return 0;
}

----------------------------------------------------------------------------
Smithy Card 
----------------------------------------------------------------------------
**Bug Introduced**: Use of incorrect logical operator (<= instead of <)
					introduces an off-by-one error causing a 4th card to be 
					drawn when only 3 should be

int playSmithy(struct gameState *state, int handPos)
{
  int i;
  int currentPlayer = whoseTurn(state);
  
  //+3 Cards
  //for (i = 0; i < 3; i++) *ORIGINAL CODE*
  for (i = 0; i <= 3; i++) //*BUG INTRODUCED* - wrong logical operator  -> Off-By-One error  
  {
    drawCard(currentPlayer, state);
  }
      
  //discard card from hand
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}


----------------------------------------------------------------------------
Village Card 
----------------------------------------------------------------------------
int playVillage(struct gameState *state, int handPos)
{
  int currentPlayer = whoseTurn(state);
 
  //+1 Card
  drawCard(currentPlayer, state);
      
  //+2 Actions
  state->numActions = state->numActions + 2;
      
  //discard played card from hand
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}


----------------------------------------------------------------------------
Great Hall Card 
----------------------------------------------------------------------------
**Bug Introduced**: Increment numBuys instead of numActions. Introduces  
					incorrect behavior for this card (+1 Card and +1 Buy
					rather than +1 Card and +1 Action)

int playGreat_Hall(struct gameState *state, int handPos)
{
  int currentPlayer = whoseTurn(state);

  //+1 Card
  drawCard(currentPlayer, state);

  //+1 Actions
  //state->numActions++; *ORIGINAL CODE*
  state->numBuys++; //*BUG INTRODUCED* - increment wrong variable
      
  //discard card from hand
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}



----------------------------------------------------------------------------
Council Room Card 
----------------------------------------------------------------------------
**Bug Introduced**: Use of incorrect logical operator (== instead of !=)
					incorrect behavior for this card (currentPlayer gets an 
					additional card instead of eath other player)

int playCouncil_Room(struct gameState *state, int handPos)
{
  int i;
  int currentPlayer = whoseTurn(state);

  //+4 Cards
  for (i = 0; i < 4; i++)
  {
    drawCard(currentPlayer, state);
  }
      
  //+1 Buy
  state->numBuys++;
      
  //Each other player draws a card
  for (i = 0; i < state->numPlayers; i++)
  {
    //if ( i != currentPlayer ) *ORIGINAL CODE*
    if ( i == currentPlayer ) //*BUG INTRODUCED* - Wrong logical operator
    {
      drawCard(i, state);
    }
  }
      
  //put played card in played card pile
  discardCard(handPos, currentPlayer, state, 0);
      
  return 0;
}