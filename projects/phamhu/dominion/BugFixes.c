//Program: BugFixes.c
//Author: Huy Pham
//Created date: 02/27/2016
//Description: Describe the process of identifying and fixing the bugs in dominion.c program

The following bugs that were introduced with earlier version of the program through code refactoring were fixed:
in smithyCard():
	correct card increase from 4 to 3
in villageCard():
	set trashcard switch back to false (0) (discardCard(handPos, currentPlayer, state, 0));
in councilRoomCard():
	set trashcard switch back to false (0) (discardCard(handPos, currentPlayer, state, 0));
in adventurerCard():
	set drawntreasure back to 2 instead of 1


