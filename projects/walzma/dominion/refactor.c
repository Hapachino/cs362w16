/*
Matt Walz
CS 362
Assignment 2

Refactoring Changes------------------------------------------------------------

File: dominion_helpers.h:
Changes:
	1. Added function prototypes for refactored card function:
		AdventurerEffect() (Adventurer card)
		CouncilRoomEffect() (Council Room card)
		SmithyEffect() (Smithy card)
		BaronEffect() (Baron card)
		MinionEffect() (Minion card)

		
File: dominion.c:
Changes:
	1. Replaced case statements in cardEffect() method for the five refactored card functions:
		a. Adventurer
		b. Council Room
		c. Smithy
		d. Baron
		e. Minion
	The case statments now simply return methods for the 5 refactored cards (e.g. case adventurer: return AdventurerEffect(currentPlayer, state) ).
	
	2. Added new methods for each refactored card at eof:
		AdventurerEffect()
		CouncilRoomEffect()
		SmithyEffect()
		BaronEffect()
		MinionEffect()
	The method definitions are simply a copy/paste of the original code in the case statement, plus additional local variable definitions where necessary.

	3. Cleaned up existing code by adding comments and aligning, spacing, tabbing code (particularly loops) so that it would be easier to read and understand.


Intentional Bugs-----------------------------------------------------------------

All bugs were introduced into the new methods in dominion.c.

AdventurerEffect() bugs:
	1. Removed the check to see if deck is empty and needs to be re-shuffled

CouncilRoomEffect() bugs:
	1. Removed (if i != currentPlayer) check prior to all other players drawing a card
	
SmithyEffect() bugs:
	1. Changed trashFlag param in discardCard() method to 1

BaronEffect() bugs:
	1. In if statements	embedded in while loop, change card_not_discarded = 0 to == 0, which will make the loop run infinitely
	2. Added p = 0 as the first parameter in in first for loop

MinionEffect() bugs:
	1. In 'other players discard hand and redraw' section:
		a. removed (if (i != currentPlayer) ) check
		b. changed handCount[i] to handCount[currentPlayer] in the while loop parameter
		c. changed discardCard i parameter to currentPlayer

*/
		