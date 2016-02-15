******************************************************************************

****  CS 362 - Assignment 3 - Unit Testing For Dominion - Spencer Winlaw  ****

******  coverage1.c - coverage of dominion.c for Assignment 3 testing  *******

******************************************************************************

gcov Results Summary
------------------------------------------------------------------------------
	File 'dominion.c'
	Lines executed:33.91% of 581
	Branches executed:29.64% of 415
	Taken at least once:22.89% of 415
	Calls executed:28.00% of 100
	dominion.c:creating 'dominion.c.gcov'

gcov Results by Tested Functions
------------------------------------------------------------------------------
	function endTurn called 1 returned 100% blocks executed 92%
	function isGameOver called 3 returned 100% blocks executed 100%
	function discardCard called 10 returned 100% blocks executed 88%
	function updateCoins called 11 returned 100% blocks executed 100%

	function playAdventurer called 4 returned 100% blocks executed 100%
	function playSmithy called 2 returned 100% blocks executed 100%
	function playVillage called 2 returned 100% blocks executed 100%
	function playGreat_Hall called 2 returned 100% blocks executed 100%

On reviewing the coverage result of my testing I find that my statement coverage
(relative to the specific functions tested) was high. My branch coverage was somewhat
less. In order to improve these results in future testing suites, I find that I need
to further consider corner cases and really put boundaries to the test in a stress
testing fashion in order to reach some of the mor exceptional code lines.

