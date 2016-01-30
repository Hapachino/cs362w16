Michael Byrne
Assignment 2 Part 3 
CS 362 

Refactored:
	smithy
	adventurer
	village
	great_hall
	steward


smithy:
	Removed smithy logic from cardEffect switch statement
	New function smithy() added
	Required parameters provided by cardEffect parameters and local
	BUG: function does not check for bad return values from drawCard()
		Always returns 1

adventurer: 
	Removed adventurer logic from cardEffect switch statement
	New function adventurer() added
	Required parameters provided by cardEffect parameters and local
	BUG: function does not check for empty card pile
		Does not shuffle


village:
	Removed village logic from cardEffect switch statement
	New function village() added
	Required parameters provided by cardEffect parameters and local
	BUG: no BUG

great_hall:
	Removed great_hall logic from cardEffect switch statement
	New function great_hall() added
	Required parameters provided by cardEffect parameters and local
	BUG: reduces actions by one instead of increasing by one

steward:
	Removed steward logic from cardEffect switch statement
	New function steward() added
	Required parameters provided by cardEffect parameters and local
	BUG: discards the same card two times




