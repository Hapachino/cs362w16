/************
 * Eric Olson
 * Assignment #2 
 * CS362_400 - Winter 2016 - Christi
 ************/

 Dominion Card/Function Documentation:


 /** Smithy Card **/
 switch( card )
 	case smithy:
 		//When this card is played 3 additional cards are drawn from the deck and added to
 		//the players hand.  One action is used (although this is executed outside the case statement).
 		//This is an action card that costs 4 coins to purchase.

 		//In code this is accomplished by iterating 3 times through a loop that calls drawCard().
 		//This adds three cards from the deck to the players hand (executing any required shuffles).
 		//Finally discardCard() is called which moves the smithy card from the players hand to the played
 		//pile.


/** Adventure Card **/
switch( card )
	case adventurer:
		//When this card is played cards from the deck are drawn one at a time, as each card is draw if
	    //it is not a treasure card, the card is discarded.  This continues until 2 treasure cards have
	    //been drawn at which point the two treasure cards are added to the player's hand.  One action is
	    //used (although this is executed outside the case statement).  This is an action card that costs
		//6 coins to purchase.

	    //In code this is accomplished by calling drawCard() repeatedly.  After each draw the top hand
	    //card is evaluated, and if card is not a treasure it is moved to a temporary hand.  If the card
	    //is a treasure it is left in the players hand and a treasure counter is iterated.  This continues
	    //until the treasure counter reaches 2.  At this time the temporary hand is iterated through
	    //moving each card to discard in order.


/** discardCard() **/
int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag);
		//This function moves a card from a players hand to either the trash, or to the played pile.
		//It requires as parameters the position of the card in hand to discard, the player, the state
        //object and a boolean flag indicating if the card is to be trashed or played.

        //In code this is accomplished by evaluating the trashFlag parameter.  If card is is not being
        //trashed then card is added to the playedCards pile, otherwise card will simply be destroyed.
		//Following trashing the card is removed from the hand.  This is done in 3 steps, if card is
		//final card in hand, then the handCount variable is decremented (removing the card from hand).
		//If the card is the only card in the players hand the handCount variable is decremented.
		//Lastly if card is neither last or single, then the played card is replaced by the last card
        //in hand and handCount variable is decremented.


/** updateCoins() **/
int updateCoins(int player, struct gameState *state, int bonus);
		//This function is called at the start of each players buy phase (or with special cards), and
		//calculates the number of coins based on the treasure cards in the players hand and bonus
		//coins earned.  It requires parameters including the player, the state object, and any bonus
		//coins earned.

		//In code this is accomplished by setting the state->coins value to zero.  Then each card in the
		//players hand is evaluated.  If the card is a copper, 1 is added to coins, if silver 2 and if
		//gold 3.  Finally any bonus coins passed as a paramenter are added to state->coins.