Documentation

smithy 
 case smithy:
      //+3 Cards
      for (i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);
	}
			
      //discard card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;

The smithy card uses a for loop to have the current player draw three cards. It than calls discard 
to discard the the smithy card from the current player's hand.

adventurer
   case adventurer:
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
	  
The adventurer card runs a while loop until two treasure are drawn. 
In the while lopp the deck count is checked to make sure there is at least on card in the deck.
If there is less than one card in the deck (no cards in the deck) then the deck is shuffled.
The draw card function is called. 
If the drawn card is a treasure (copper, silver, or gold) then dranwtreasure is incremented by 1. 
If the drawn card is not a treasure the card drawn is put in an array, temphand at location z. 
Then the card is removed from the players hand by decrimenting state->handCount[currentPlayer] by 1.
Then z is incremented by 1.
After the while loop to draw cards finishes running, a second while loop begins that discards the
cards that have been drawn.


discardCard() 

int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
{
	
  //if card is not trashed, added to Played pile 
  if (trashFlag < 1)
    {
      //add card to played pile
      state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos]; 
      state->playedCardCount++;
    }
	
  //set played card to -1
  state->hand[currentPlayer][handPos] = -1;
	
  //remove card from player's hand
  if ( handPos == (state->handCount[currentPlayer] - 1) ) 	//last card in hand array is played
    {
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
    }
  else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
    {
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
    }
  else 	
    {
      //replace discarded card with last card in hand
      state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
      //set last card to -1
      state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
    }
	
  return 0;
}

The discardCard function takes as parameters the handPos, currentPlayer, state, and trashFlag.
First it checks if the trash flag is set. If the trash flag is not set it is added to the played pile.
The played card, state->hand[currentPlayer][handPos] , is set to -1.
The card is then removed from the players hand. If eirther the last card in hand is played, or there
is only on card in the hand, the number of cards in the hand is decremented by 1. Otherwise the 
discraded card is replaced with the last card in the hand, the last card is set to -1. And the number
of cards in the hand is decremented. 

updateCoins()

int updateCoins(int player, struct gameState *state, int bonus)
{
  int i;
	
  //reset coin count
  state->coins = 0;

  //add coins for each Treasure card in player's hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == copper)
	{
	  state->coins += 1;
	}
      else if (state->hand[player][i] == silver)
	{
	  state->coins += 2;
	}
      else if (state->hand[player][i] == gold)
	{
	  state->coins += 3;
	}	
    }	

  //add bonus
  state->coins += bonus;

  return 0;
}

The updateCoins() function takes player, state, and bonus as parameters.
First it resets the coin count, state->coins , to zero. Then it uses a for loop to iterate through
the cards in the players hand to check if the cards in the hand are treasures.
If the card is a copper the coin count is incremented by 1.
If the card is a silver the coint count is incremented by 2.
If the card is a gold the coint count is incremented by 3.
The for loop ends when all the cards in the player's hand have been iterated through. 
After the for loop any bonus coins are added to the coin count.