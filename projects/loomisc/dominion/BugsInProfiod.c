/*
File:		BugsInProfiod.c
Author:		Chris Loomis
Date:		02/20/2016

Bug Report 1
	Smithy draws 2 cards

	dominion.c

	Serious Bug
	
	Can be reproduced everytime

	Launch Dominion
	Play Smithy card
	Active Player only draws 2 cards
	
	Active Player should have drawn 3 cards
	
	This bug does not result in a crash, but is noted as a serious bug as it's function is wrong.
	It is marked serious as this product cannot ship with this bug, due to the card not acting properly.

Bug Report 2
	Adventurer draws too much treasure
	
	dominion.c
	
	Serious Bug
	
	Can be reproduced everytime
	
	Launch Dominion
	Play Adventurer card
	Active Player receives more than 2 treasure cards
	
	Active Player should have drawn until they had exactly 2 more treasure cards
	
	This bug does not result in a crash, but is noted as a serious bug as it's function is wrong.
	It is marked serious as this product cannot ship with this bug, due to the card not acting properly.

*/