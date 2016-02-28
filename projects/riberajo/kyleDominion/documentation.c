/*
Kyle Johnson
johnsky3
CS 362
1/13/16

Documentation for smithy and adventurer cards and discardCard() and updateCoins() methods.

***************************************************************************************************

smithy:

The smithy card is an action card that causes the player to draw 3 new cards to be added to their hand,
after which the smithy card is discarded.

code:
*/
case smithy:
      //+3 Cards
      for (i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);
	}
			
      //discard card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
/*
If the smithy card is selected, first the drawCard() method is called three times within the 
for loop so that 3 new cards are added to the player's hand. After 3 cards have been drawn, 
the discardCard() method is called on the smithy card, and it is removed from the player's hand 
and added to played card pile.

***************************************************************************************************

adventurer:

The adventurer card is an action card that reveals cards in the player's hand until 2 Treasure
cards have been found. The 2 Treasure cards are added to the player's hand and the other revealed
cards are placed in the discard pile.

code:
*/
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
/*
The variable drawntreasure is initialized to 0 at the start if the cardEffect method().  While drawntreasure
is < 2 the following actions take place:
First, if the deck is empty then the shuffle() method is called to add the discard pile back to the deck.
Then the drawCard() method is called and the result is assigned to the cardDrawn variable.
If cardDrawn is a Treasure card, then it is kept in the hand and the drawntreasure count is incremented
If cardDrawn is not a Treasure card, it is added to the temphand variable and removed from the player's hand count

Once 2 Treasure cards have been drawn, the cards in the temphand are added to the discard pile.

***************************************************************************************************

discardCard():

The discardCard() method removes a card from the player's hand and adds it to the played card pile, so long as it is
not flagged to be added to the trash pile instead.  When the card is removed from the player's hand, if the last card in 
the player's hand has been played, or if there is only one card in hand, then the number of cards in hand is reduced by one. 
Otherwise, the discarded card is replaced with the last card in the hand before reducing the number of cards in hand.

***************************************************************************************************

updateCoins():

The state->coins variable is first initialized to 0. To update the coin count during a turn, a for loop runs for i = number of cards in hand.  
Within the loop, if a card == copper then the coins count is increased by 1. If a card == silver or gold, the coin count is incremented 
by 2 or 3, respectively. Outside of the loop, any bonus coins from action cards are added to the coins count.



