/*
File:		BugsInThunemn.c
Author:		Chris Loomis
Date:		02/20/2016

Bug Report 1
	Smithy does not discard

	dominion.c

	Serious Bug
	
	Can be reproduced everytime

	Launch Dominion
	Play Smithy card
	Active Player discard pile does not increment
	
	Active Player discard pile should increment by one, due to Smithy card being played
	
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