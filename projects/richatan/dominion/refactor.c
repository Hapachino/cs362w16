Tanna Richardson
CS362 - Winter 2016
Assignment 2 part 3

---cardEffects Refactor---

Changes made to dominion_helpers.h:
	1. Added function prototypes for each refactored card:
		Adventurer -> runAdventurer()
		Council Room -> runCouncilRoom()
		Mine -> runMine()
		Remodel -> runRemodel()
		Smithy -> runSmithy()

Changes made to dominion.c:
	1. Replaced existing code in cardEffect for each of the following case statements:
		adventure
		council_room
		mine
		remodel
		smithy
	New code simply calls appropriate card method and then returns 0.
	
	2. Added new methods for each refactored card at end of file:
		Adventurer -> runAdventurer()
		Council Room -> runCouncilRoom()
		Mine -> runMine()
		Remodel -> runRemodel()
		Smithy -> runSmithy()
	New methods include a copy/paste of code previously located in the case
	statement for the corresponding card and a copy/paste of related
	variable declarations from the cardEffect method.

	
---General Refactor---

Changes made to dominion.c:
	1. Added comment headers to delineate sections of code (definitions, game setup,
	     game play, game completion, helper functions, card actions)
	2. Fixed white space issues so nested blocks of code lined up properly
	3. Updated all curly braces for consistency. Opening curly braces on same line
	     as loop/conditional statement, closing braces on own line.


---Introduce Bugs---

All changes made in dominion.c.

Changes made to runAdventurer():
	1. Changed first while loop expression from (drawntreasure<2) to <=
	2. In second while loop (discard temp hand), z=z-1 in last line
	     replaced with z++
	
Changes made to runSmithy():
	1. Changed for loop expression from i<3 to i<=3
	2. Changed trashFlag parameter in discardCard method from 0 to 1

Changes made to runCouncilRoom():
	1. Changed state-->numBuys from ++ to =1 (under comment +1 Buy)
	2. Changed in for loop to draw card for each other player,
	     changed !=currentPlayer to ==currentPlayer

Changes made to runMine():
	1. Switched all choice1 to choice2, and all choice2 to choice1