/******************************************************************************
 ** Author: Tim Robinson
 ** 1/17/2016
 ****

	The 5 cards for which the code has been refactored are as follows:

	- Smithy
	- Adventurer
	- Great Hall
	- Embargo
	- Steward

	These functions have been refactored in the dominion.c file by calling 
	respective functions when the case statement for that card has been 
	triggered.


	The function signatures are as follows:

	SMITHY
	int playSmithy(int currentPlayer, struct gameState * state, int handPos)

	ADVENTURER
	int playAdventurer(int currentPlayer, struct gameState * state, 
										 int drawntreasure, int temphand[], int cardDrawn)

	GREAT HALL
	int playGreatHall(int currentPlayer, struct gameState * state, int handPos)

	EMBARGO
	int playEmbargo(int currentPlayer, struct gameState * state, int choice1, 
									int handPos)

	STEWARD
	int playSteward(int currentPlayer, struct gameState * state, int choice1, 
									int choice2, int choice3, int handPos)
	


	The bugs introduced are as follows:

	SMITHY
	If the current player is not player 0, then that player draws 4 cards
	instead of 3.

	ADVENTURER
	The initialization of the z vartiable is off by 1, initialized to -1 instead
	of 0. This causes the temphand to be incorrectly discarded.

	GREAT HALL
	The current player that discards a card is the opposite player of a 2 person
	game, though the currentPlayer still selects the hand position that is
	discarded.

	EMBARGO
	If the position from which embargo was played is even, then embargo adds 4
	additional coins to their available coin pool instead of 2.

	STEWARD
	No bug introduced.

 *****************************************************************************/