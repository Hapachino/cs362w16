Nancy Chan
CS 362
Winter 2016
Assignment 2: refactor.c

Document your changes in a text file in your dominion source directory, called “refactor.c.” 
Your implementation of at least 4 of these 5 cards should be incorrect in some way, i.e., you should introduce subtle bugs that are hard to catch in
your changes. Introducing bugs in smithy and adventurer is mandatory. Write information of your bugs also in refactor.c

Changes to dominion.c:
	adventurer, smithy, cutpurse, remodel, and sea_hag were refactored to be implemented in their own functions rather than as part of the switch statement
	in the cardEffect function. The new functions are named playAdventurer, playSmithy, playCutpurse, playRemodel, and playSea_Hag.

Bugs introduced:
	adventurer:
	- 

	smithy:

	cutpurse:

	remodel:

	sea_hag: