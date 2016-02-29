Jonathon Hicke
Smithy documentation - draw three cards
Smithy card is played under the cardEffect method in the dominion.c file. It calls the drawCard function three times through a for loop. Buying the smithy card and tracking the smithy card is down in the playdom.c file.
     for (i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);


Adventurer documentation- reveal cards in player deck till 2 treasure cards are found and place in hand. The rest of the cards are discarded. Buying the adventurer card and tracking the adventurer card is down in the playdom.c file.
This is played under the card effect method in dominion.c. It is done through a while loop  that repeats til the index hits 2. First it checks to see if the deck needs to be shuffled. Next it draws a card and adds to the hand, if the card is a treasure the index increases , else it is added to a temphand. After the while loop finishes the temphand is discarded.  

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


discardCard()
int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)

HandPos -  index for which card in hand is discarded
Currentplayer- which player the hand belongs to
gameState- current game state
trashFlag-  if less than 1 then goes to played pile else card is dropped from game

If trashflag is <1 than card is added to the PlayedCards. Set played card to -1, removed card from hand, reduce card count


updateCoins()
int updateCoins(int player, struct gameState *state, int bonus)
player- which player
gamestate - the current games
bonus - coins added. 

For loop that checks each card in the player's hand and coins to state->coins 1for copper 2 for silver 3 for gold. After loop adds amount from the bonus parameter.
