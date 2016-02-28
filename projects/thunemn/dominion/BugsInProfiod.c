/*
File:		BugsInProfiod.c
Author:		Nathan Thunem
Date:		02/20/2016

Bug Report 1
	Council Room decrements numBuys

	dominion.c

	Serious Bug
	
	Can be reproduced everytime

	Launch Dominion
	Play Council Room Card
	Active Player decreases number of buys
	
	Active Player should have increased number of buys, due to Smithy card being played
	
	This bug does not result in a crash, but is noted as a serious bug as it's function is wrong.
	It is marked serious as this product cannot ship with this bug, due to the card not acting properly.

Bug Report 2
	Council Room draws a card for everyone, even the active player
	
	dominion.c
	
	Serious Bug
	
	Can be reproduced everytime
	
	Launch Dominion
	Play Council Room Card
	Every other player including active player draws a card
	
	Active Player should not have been included in the card draw
	
	This bug does not result in a crash, but is noted as a serious bug as it's function is wrong.
	It is marked serious as this product cannot ship with this bug, due to the card not acting properly.

*/