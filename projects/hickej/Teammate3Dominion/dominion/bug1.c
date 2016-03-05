/*
Unit test 1: updateCoins()
	No bugs that I could find.

Unit test 2: discardCard()
	No bugs that I could find.

Unit test 3: whoseTurn()
	Found it a bit strange that I had to initialize whose turn it was before calling the code

Unit test 4: endTurn()
	So many problems trying to get this code to work!
	In short, it appears that initialize game isn't doing its job by setting a number of the gamestate values

Card test 1: adventurer
	Fails all the time
	To be expected since the implementation of the code is wrong

Card test 2: smithy
	Works whenever there is something in the player's hand
	find this strange since the code was written incorrectly

Card test 3: village
	Works correctly
	Glad to see it since is was supposed to be implemented correctly in assignment 2

Card test 4: Salvager
	Doesn't work correctly
	Coins are never correct
	not a surprise since the code was written incorrectly

*/