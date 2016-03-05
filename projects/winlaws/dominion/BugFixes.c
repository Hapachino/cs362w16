*********************************************************************************
***  CS 362 - Assignment 5 - Testing and Debugging Dominion - Spencer Winlaw  ***
***         BugsFixes.c - documentation of bugs fixed in dominion code        ***
*********************************************************************************

The following changes were made in dominion.c as documented in order to fix the 
bugs reported by my teammates in Assignment 5. 

----------------------------------------------------------------------------
Adventurer Card 
----------------------------------------------------------------------------
**Bug Description**: In call to adventurer, there is one card too many in the players hand 
                    after playing adventurer.
**Bug Fix**: adventurer card was not being discarded when it was played. Fixed by adding
            a statement which discards the card (this required handPos, so handPos was
            added as a parameter for the call to the cards function).

**Bug Description**: In call to adventurer, silver cards are discarded rather thatn
                    being added to the players hand.
**Bug Fix**: Check for silver was omitted when checking if cardDrawn is a treasure
            card. Therefore drawnTreasure was not being incremented if silver was drawn and
            treasure card would be discarded with temp hand instead of kept. Fixed by adding
            a check for silver.

int playAdventurer(struct gameState *state, int handPos)//*Bug Fix*
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
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) // *Bug Fix*
    //if (cardDrawn == copper || cardDrawn == gold) //*BUG INTRODUCED* - Omit check for silver
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

  //discard card from hand
  discardCard(handPos, currentPlayer, state, 0);//*Bug Fix*
  
  return 0;
}

----------------------------------------------------------------------------
Smithy Card 
----------------------------------------------------------------------------
**Bug Description**: In call to smithy, there is one card too many in the
                    players hand after playing smithy.
**Bug Fix**: Use of incorrect logical operator (<= instead of <)
					introduced an off-by-one error causing a 4th card to be drawn when 
          only 3 should be. Fixed by correcting the logical operator.

int playSmithy(struct gameState *state, int handPos)
{
  int i;
  int currentPlayer = whoseTurn(state);
  
  //+3 Cards
  for (i = 0; i < 3; i++) //*Bug Fix*  
  //for (i = 0; i <= 3; i++) //*BUG INTRODUCED* - wrong logical operator -> Off-By-One error 
  {
    drawCard(currentPlayer, state);
  }
      
  //discard card from hand
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}


----------------------------------------------------------------------------
Great Hall Card 
----------------------------------------------------------------------------
**Bug Description**: In call to great_hall, the current player has 1 less
                    remaining turn than they should after play.
**Bug Fix**: numBuys was being incremented instead of numActions. This
          introduced the incorrect behavior for this card (+1 Card and +1 Buy
					rather than +1 Card and +1 Action). Fixed by correcting the attribute
          being incremented.

int playGreat_Hall(struct gameState *state, int handPos)
{
  int currentPlayer = whoseTurn(state);

  //+1 Card
  drawCard(currentPlayer, state);

  //+1 Actions
  state->numActions++; // *Bug Fix*
  //state->numBuys++; //*BUG INTRODUCED* - increment wrong variable
      
  //discard card from hand
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}



----------------------------------------------------------------------------
Council Room Card 
----------------------------------------------------------------------------
**Bug Description**: In call to council_room, the current player has 1 more
                    card than they are supposed to and the other player has 
                    1 less card than they are supposed to.
**Bug Fix**: Use of incorrect logical operator (== instead of !=) introduced
					incorrect behavior for this card (currentPlayer was getting an 
					additional card instead of eath other player). Fixed by correcting 
          the logical operator.

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
    if ( i != currentPlayer ) //*Bug Fix*
    //if ( i == currentPlayer ) //*BUG INTRODUCED* - Wrong logical operator
    {
      drawCard(i, state);
    }
  }
      
  //put played card in played card pile
  discardCard(handPos, currentPlayer, state, 0);
      
  return 0;
}