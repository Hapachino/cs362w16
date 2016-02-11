/******************************************************************************
 ** Author: Tim Robinson
 ** Date: February 2, 2015

	My coverage for the dominion.c file was as follo0ws:

	Lines executed: 36.35% of 586
	Branches executed: 33.25% of 421
	Taken at least once: 28.74% of 421
	Calls executed: 18.95% of 95
	
	Unit Test Function Coverage
	---------------------------
	discardCard: 92.31%
	gainCard: 100%
	isGameOver: 100%
	buyCard: 100%

	Card Test Function Coverage
	---------------------------
	playSmithy: 87.5%
	playAdventurer: 94.12%
	playGreatHall: 100%
	playEmbargo: 100%

	I stated this as a bug in the bug1.c file, but it is relevant for coverage
	here:

	In the discardCard function, there is an unreachable piece of code.
	Because we determine whether a discarded card is the LAST card before we
	determine whether that card is the ONLY card, we do not encounter the else-if
	branch dealing specifically with a card being an ONLY card.

	This does not alter the behavior of our program, as both branches have the 
	same outcome. I found this unreachable code by seeing in gcov that the
	latter branch was taken 0% of the time, though I tested single-card hands
	discarding that card.

	For the Smithy function, I fail to reach the bit of code where a correct 
	amount of cards is set to be drawn. This is due to an inappropriate 
	initialization of the second player, so the gameState is not initialized
	correctly for gameplay past the first stage. In order to remedy this, I 
	would need to implement a full endTurn step to transition from the first to
	the second player. That, or I could manually set the game state for each
	player in order to fully attempt the second player's play of Smithy.

	For the Adventurer function, I never necessitate a shuffling of the deck
	(which occurs if the player draws the remainder of their deck as part of the
	effect of the Adventurer card). This code is not covered by the test, but I
	could vary the deck size of the gameState and play the Adventurer card in 
	order to reach 100% cover.

	The line and branch coverage that I got of 36.35% and 33.25% for the
	dominion.c file overall was anticipated. Given the number of functions that
	I try to intentially fully cover, the ratio of about a third of possible 
	branches covered and about a third of lines covered makes sense.

	The biggest thing that I would change to achieve a better test suite is to
	do a better job of initializing the game state as I move from player to 
	player. Having a more fleshed out game state would have helped me for
	different players, but was sufficiently initialized for the other 
	functionality that I tested.

 *****************************************************************************/
