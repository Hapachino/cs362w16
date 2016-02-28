/******************************************************************************
 ** Author: Tim Robinson
 ** Date: January 25, 2015

	No bugs encountered in discardCard() function, gainCard() function, 
	isGameOver() function, or buyCard() function.


	FUNCTION UNIT TESTS
	-------------------

	In the discardCard function, there is an unreachable piece of code.
	Because we determine whether a discarded card is the LAST card before we
	determine whether that card is the ONLY card, we do not encounter the else-if
	branch dealing specifically with a card being an ONLY card.

	This does not alter the behavior of our program, as both branches have the 
	same outcome. I found this unreachable code by seeing in gcov that the
	latter branch was taken 0% of the time, though I tested single-card hands
	discarding that card.

	This gave me a coverage of 92.31% for the discardCard() function.

	Coverage of 100% for the gainCard() function.

	Coverage of 100% for the isGameOver() function.

	Coverage of 100% for the buyCard() function.

	
	CARD PLAY FUNCTION TESTS
	------------------------

	Smithy 

	The bug that I placed in the smithy function that my tests reveal has to do 
	with a player's draw of cards. If a player is player = 0, then the player 
	only draws 2 cards. Every other player draws 3 cards, i.e. has the expected 
	behavior.

	Adventurer

	The bug that I placed in the adventurer function that my tests reveal is an
	incorrect discard of a non-treasure card drawn as a result of the card
	effect. 

	Previous the error was:

	The function is initialized incorrectly (the 'z' variable should be 
	initialized to 0, but it is initialized to -1).

	Introducing this off-by-one error during initialization caused a seg fault
	on the OSU flip server. I moved the off-by-one error to decrement the "z"
	variable after making an array access of array[z].

	This causes an error where the player does not discard every card drawn 
	from the adventurer's effect.

	Great Hall

	The bug that I placed in the great hall functions that my tests reveal is an
	error that causes an opponent's card to be discarded instead of the current
	player's great hall card. This is tested by counting the current player's
	hand after they play a great hall card.

	Embargo

	I'm not sure if this is a bug or I misunderstand the embargo card. It seems 
	that if a player selects an incorrect supplly choice to place the embargo,
	that player still gains coins for a buy, preserved in the gamestate, while
	they do not discard this embargo card. It seems like the intent is to
	prevent the coins, and perhaps the action, from taking place at all in this
	event.

	The bug that I placed in the embargo function involves the position from 
	which the card is played deciding how many coins the player gets. If the
	position is even-indexed, then the player receives 4 coins instead of the
	expected 2.


	OTHER POTENTIAL BUGS
	--------------------
	For the Smithy card, calling the drawCard function causes 2 cards to be added
	to the hand count (which I intentionally inserted as a bug). Though this is
	the case, 3 cards are still removed from the deckCount for that player.

 *****************************************************************************/
