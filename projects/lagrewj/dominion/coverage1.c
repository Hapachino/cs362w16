/*
Jonathan Lagrew
CS 362
Winter 2016
Assignment 3: coverage1.c

Summary of coverage for all tests:
File 'dominion.c'
Lines executed:35.51% of 583
Branches executed:37.89% of 417
Taken at least once:33.09% of 417
Calls executed:22.00% of 100

unittest1:

	100% statement coverage of updateCoins().
	branch coverage: function updateCoins called 52 returned 100% blocks executed 100%.
	
unittest2:

	100% statement coverage of fullDeckCount().
	branch coverage: function fullDeckCount called 20 returned 100% blocks executed 100%.
	
unittest3:

	100% statement coverage of isGameOver()
	branch coverage: function isGameOver called 9 returned 100% blocks executed 100%

unittest4:
	
	100% statement coverage of scoreFor(). 
	Branch coverage for function scoreFor() called 2 returned 100% blocks executed 73%.
	Not all blocks were executed because this unit test did not check the player's hands
	or player's decks. This should be something I can improve in future assignments in 
	order to get 100 of the blocks executed. 
	
cardtest1:

	function playSmithy called 500 returned 100% blocks executed 100%.
	
cardtest2:

	function playAdventurer called 500 returned 100% blocks executed 100%.
	
cardtest3:
	
	function playVillage called 500 returned 100% blocks executed 100%.

cardtest4:

	function playCouncil_Room called 5400 returned 100% blocks executed 100%.
	
*/
