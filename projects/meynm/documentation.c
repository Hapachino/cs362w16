/*
Week 2 Documentation
by Matthew Meyn
2016/1/12



adventurer card:

	Playing this card should cause the player to draw cards until 2 treasure
	cards have been drawn. The 2 treasure cards will remain in the player's
	hand, while the other cards drawn will return to the player's discard pile.
	If the player's deck becomes empty while drawing cards, the discard pile
	will be reshuffled and become the player's new deck.
	
	Implementation:
		
		while treasure cards drawn < 2:
			Check current player's deck count in the state variable.
			If it's less than 1: reshuffle.
			Draw a card.
			If drawn card is copper or silver or gold: 
				Add one to treasure cards drawn
			Otherwise:
				Push the card onto a temporary hand and increment its length.
		
		Insert each card in the temporary hand into the discard pile.
		
		Return 0



smithy card:

	This card should result in the player drawing 3 cards. In the code, no 
	provision is made for what happens if the deck is empty. When the cards are
	drawn, this card is put in the player's discard pile.
	
	Implementation:
		
		For i in range 3:
			draw a card
			
		Call discardCard to put away this card.
		
		Return 0



int discardCard( int handPos, int currentPlayer, 
				struct gameState *state, int trashFlag ):

	This function presumably should transfer a card in the player's hand either
	into the player's discard pile (transFlag < 0) or into the trash pile. I
	don't see where the transfer to discard happens; the function appears to 
	simply remove the card from the player's hand and either put it in the
	trash pile or not.
	
	Implementation:
		
		if trashFlag < 1:
			Push the card at handPos in the player's hand onto the end of 
			playedCards and increment length of playedCards.
		Set the card at player's handPos to -1.
		Perform dynamic-array-style manipulation to remove card from the set.



int updateCoins( int player, struct gameState *state, int bonus ):

	Finds the total value of treasure cards in the player's hand, adding any
	bonus value passed into the function. The total value is assigned to 
	state->coins
	
	Implementation:
	
		Initialize state->coins to 0
		
		For each card in the player's hand:
			If the card is
				copper, add 1
				silver, add 2
				gold, add 3
			to state->coins
			
		Add any bonus to state->coins.
		
		Return 0
*/
