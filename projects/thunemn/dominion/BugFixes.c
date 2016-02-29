/*
File:		BugFixes.c
Author:		Nathan Thunem
Date:		02/27/2016

Bug Report 1:
	Salvager card did not update coins properly

	dominion.c
	function: playSalvager()
	Severity:  Severe

	Unit test shows that the salvager card does lead to the user gaining
	one coin higher than the worth of the card that is discarded.

	The expected action is that post salvager card the user will have the
	amount of coins equal to the value of the card that they choose to
	discard.

	This is a severe bug as while it does not crash the system, it
	reproduces every time and can greatly affect the game.

	BUG FIX:
		the playSalvager function was incorrectly adding 1 to the amount of coins added after
		playing the Salvager card.  I corrected the function to not add 1 to the card value:
			state->coins = state->coins + getCost( handCard(choice1, state) );
		The playSalvager function is now correct.

Bug Report 2:
	Village card did not discard played card properly

	dominion.c
	function: playVillage()
	Severity:  Severe

	Unit test shows that the village card is not returned to the discard
	pile and is instead trashed.

	The expected action is that post village card the discard deck will
	contain the played village card.

	This is a severe bug as while it does not crash the system, it
	reproduces every time and can greatly affect the game.

	BUG FIX:
		The playVillage function was not adding a card to the discard pile, because the trashFlag 
		was incorrectly set to 1.  I corrected the bug by switching the trashFlag to 0 in order to 
		increment the discard pile count.

Bug Report 3:
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

	BUG FIX:
		The playSmithy function was not adding a card to the discard pile, because the trashFlag 
		was incorrectly set to 1.  I corrected the bug by switching the trashFlag to 0 in order to 
		increment the discard pile count.

Bug Report 4:
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

	BUG FIX:
		The playVillage function was only adding one action.  I changed the code to: 
			state->numActions = state->numActions + 2;
		Now the playVillage function correctly adds 2 actions isntead of 1.
*/