/*
Assignment 5 - Bug Fixes 
Gerald Gale

BUGS: 
	BUG1:
		callAdventurerCard() did not have the right conditional for the while loop 
	FIX1:
		Needs to be while(drawntreasure<2)

	BUG2:
		callVillageCard() did not call drawCard()
	FIX2:
		Add the drawCard() call 

	BUG3:
		callEmbargoCard() was not correctly adding the embargo token
	FIX3:
		Increment state->embargoTokens[choice1]++;

*/