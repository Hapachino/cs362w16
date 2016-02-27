/*Chris Loomis
CS362 W16
Assignment 5
BugsInTeammates.c
02/27/2016

This is a composite of BugsInThunemn.c and BugsInProfiod.c which are the two bug files for my teammates.
I created this as the instructions indicate I need a file BugsInTeammates.

Bugs found for Nathan Thunem
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
		
		
Bugs found for David Profio
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