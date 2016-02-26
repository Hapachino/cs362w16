Ava Petley
Assignment 4

randomtestcard:
	The card I choose to test is the smithy card. If working correctly three cards should 
	be added and one should be discarded to the current players hand and no other hands should
	be affected. My test randomly sets the state of the game, distributino randomcards to either
	the deck or the discard where the number in the deck and discard are also randomly selected.
	The function is called and values before are compared to values after.
	Bugs: the players hand is not being properly altered. It should increase by two cards since
	three are added and one is discarded but the function is adding 4 cards instead.
	
	to run: make randomcardtest.out
	
	coverage: 20.89% the coverage is higher than with the unit test because inputting random values increase
	the chance to find bugs.
	
randomtestadventurer:
	The adventurer card added two treasure cards to the users deck. Again I randomly selected cards
	to be added to the deck or discard piles of random amounts. The function is then called. The discard
	pile is checked for discarded treasure cards. The hand count, discard count and deck count are compared
	before and after. 
	
	Bugs: on occasion a treasure card is discarded - it is always a copper.
	on occasion the wrong number of cards are in the players hand. 
	If there are no treasure cards in the players deck there is an error
		
	to run: make randomtestadventurer.out
	
	coverage: 21.23% the coverage is higher because with random input the chance to error
	increases. 
