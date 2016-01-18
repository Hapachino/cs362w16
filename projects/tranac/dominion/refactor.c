/* 	File: documentation.c
	Author: Chris Trana
	CS 362
	
Added functions for 5 cards and called the functions in the correct place in cardEffect.

card functions:  smithyCard, adventurerCard, council_roomCard, villageCard, and sea_hagCard.

Bugs were introduced into 4 of the new card functions as described below:
	
The smith card will draw 4 cards instead of 3.

The while loop in the adventurer card is incorrect and will draw an extra card (drawntreasure <= 2 instead of correct way of drawntreasure < 2).

The council room card will decrement the number of buys instead of increment.

The village card will increase the number of actions by 1 instead of 2.

*/
