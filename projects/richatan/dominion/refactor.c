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


