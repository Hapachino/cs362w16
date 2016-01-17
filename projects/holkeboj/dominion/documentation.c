/*
Jack Holkeboer
OSU CS362 Assignment 2 part 2
Documentation of Smithy and Adventurer cards in dominion

Smithy:
* The Smithy card allows the player to draw three additional cards. 
  for(i = 0; i <3; i++){
    drawCard(currentPlayer, state);
  } 
* The Smithy card itself is then discarded after playing.
  discardCard(handPos,currentPlayer,state,1);


Adventurer:
* When an Adventurer card is played, the player draws a card from the deck.
* The player then draws again, and this process is repeated until the player 
has drawn two treasure cards.  
    * First check if the deck is empty and reshuffle if necessary
        if (state->deckCount[currentPlayer] <1){//we need to shuffle discard and add to deck
        shuffle(currentPlayer, state);
        }
    * Then draw a card.  If it's treasure, increment drawntreasure
        if (cardDrawn == copper && cardDrawn == silver && cardDrawn == gold){
        drawntreasure++;
        }
    * If it's not treasure, remove it from the hand into a temporary hand, where it will be 
      discarded
        else{
        temphand[z]=cardDrawn;
        state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
        z++;
        }
* Once two treasure cards are drawn,  all drawn cards except the treasue cards 
are discarded.
  while(z-1>=0){
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }
  

discardCard() method:
This method is used to remove a card from the hand and place it in the discard pile.
It takes four arguments:
    * The hand position of the card
    * Identification of the current player
    * a gameState struct pointer
    * a flag that indicates if the card is trashed
If the trash flag is set, the card will be placed in the trash pile.  Otherwise
it will go in the played pile.
The card is removed from the player's hand, and if it's not at the end of the hand, it is 
replaced with the last card in the hand. 

updateCoins() method:
This method updates the coin count based on the number of treasure cards in a player's hand.
First the count is reset to zero.  Then we iterate through each card in the hand and add the 
appropriate number of coins if it's a treasure card.  Any bonus is then added.

*/