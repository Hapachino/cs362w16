/*
File:		BugsInLoomisc.c
Author:		Nathan Thunem
Date:		02/20/2016

Bug Report 1
	Smithy draws 4 cards instead of 3

	dominion.c

	Serious Bug
	
	Can be reproduced everytime

	Launch Dominion
	Play Smithy card
	Active Player draws 4 cards 
	
	Active Player should have received 3 cards, due to Smithy card being played
	
	This bug does not result in a crash, but is noted as a serious bug as it's function is wrong.
	It is marked serious as this product cannot ship with this bug, due to the card not acting properly.

Bug Report 2
	Village adds one action
	
	dominion.c
	
	Serious Bug
	
	Can be reproduced everytime
	
	Launch Dominion
	Play Village card
	Active Player receives 1 more action
	
	Active Player should have received 2 more actions
	
	This bug does not result in a crash, but is noted as a serious bug as it's function is wrong.
	It is marked serious as this product cannot ship with this bug, due to the card not acting properly.

*/