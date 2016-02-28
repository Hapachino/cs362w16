/*
Robert Jackson
CS362
Documentation Asignment 2

Smithy:
	Has a cost of 4 coins.When invoked this "card" allows the current player to draw an additional 3 cards from their deck, to be placed in hand.
	The code runs a for loop  from 0 to < 3 (3 times) calling the drawCard() function using the current player and current state.


Adventurer:
Has a cost of 6 coin, It's purpose is to allow you to draw from the deck until you gain two treasure cards.

	It tracks the treasure that you have obtained by incrementing drawntreasure. 
	In a while loop so long as drawntreasure is < 2 
	If the number of cards in the deck should be < 1 then it switches players
	then it draws a card using drawCard()
	The drawn card is set equal to the card on the top of the person's deck. 
	if the card is equal to any of the 3 treasure types, drawntreasure is incremented.
	Otherwise the card is added to a temporary array of cards , and then the handCount is decremented to remove the card that was drawn
	the array is then incremented for the temporary array

	A second while where z >=0 loop is used to clean up the temp hand by setting the discard of the current player equal to the temparrays last card, and then
	decrementing z each time 


discardCard():
	Is responsible to taking a card out of the plays current hand, and putting it back into the player's deck
	first if the card is going to be trashed, it wont get put back into the played pile
	Then its taken out of the players hand by reducing the count by decrementing the current players handcount
	Only when the handPos of the last card in the array are both equal to -1
	Unless  there is only one card in the players hand at the time of being called- it does the same thing just decrement by one
	Otherwise it moves the last card in your hand to the position of the discard card and decrements the card count in hand
	(i.e. in the first two cases there was no need to move anything around. the last one is if you take something from the middle of your 
	deck for example)


updateCoins():
	Sets the number of coins being used on a players turn to 0
	for each trasure card played depending on the value of the card, it increments the amount by 1 two or three,
	Then it looks to see if there is a bonus set and adds this to the overall state of coins


 
