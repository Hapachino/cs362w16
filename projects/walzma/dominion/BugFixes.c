/*
Matt Walz
CS 362
Assignment 5 - BugFixes.c

The following are a list of the revisions made to my dominion.c source code based on results from my teammates testing as well as from conducting my own testing. The bugs and the corresponding code changes are documented below, beginning with bugs found by my teammates.



Bugs found by Teammate 1 (Rishi Bhandarkar):
	Bug 1: Smithy card not added to played card pile and playedCardCount not incremented (also found by teammate 2 and my testing via cardtest1.c).
	Fix: Added line "discardCard(handPos, currentPlayer, state, 0);" to SmithyEffect() method.
	
	Bug 2: Adventurer card not added to played card pile and playedCardCount not incremented (also found by teammate 2 and my testing via cardtest3.c and randomtestadventurer.c).
	Fix: Added line "discardCard(handPos, currentPlayer, state, 0);" to AdventurerEffect() method. This requires adding int handPos as a parameter to be passed to AdventurerEffect() method.
	
	Bug 3: Council Room card does not draw the correct number of cards (introduced by me in earlier assignment and also found by teammate 2).
	Fix: Re-added "(if i != currentPlayer)" check for section when all other players draw cards
	
	Bug 4: scoreFor() method calculates scores incorrectly
	Fix: In "//score from deck" section of code, changed the for loop to "for (i = 0; i < state->deckCount[player]; i++)."



Bugs found by Teammate 2 (Tom Dale):
	Bug 1: Smithy card not added to played card pile and playedCardCount not incremented (also found by teammate1 and my testing with cardtest1.c).
	Fix: Added line "discardCard(handPos, currentPlayer, state, 0);" to SmithyEffect() method.
	
	Bug 2: Adventurer card not added to played card pile and playedCardCount not incremented (also found by teammate 1 and my own testing via cardtest3.c and randomtestadventurer.c).
	Fix: Added line "discardCard(handPos, currentPlayer, state, 0);" to AdventurerEffect() method. This requires adding int handPos as a parameter to be passed to AdventurerEffect() method.
	
	Bug 3: Council Room card does not draw the correct number of cards (introduced by me in earlier assignment and also found by teammate 1).
	Fix: Re-added "(if i != currentPlayer)" check for section when all other players draw cards



Bugs found by my testing (omitting duplicate bugs):	
	Bug 1: When playing Remodel, card to be trashed is instead moved to played cards pile (found by cardtest4.c).
	Fix: Revised loop commented "//move trashed card to played pile" so that it removes the trashed card from the game rather than discards it. This is done by switching the card to be trashed with the last card in the player's hand. Then setting the last card to -1 and decrementing the player's handcount.
	
	Bug 2: When playing Remodel, a card which is too expensive gets incorrectly added to player's discard pile (found by cardtest4.c).
	Fix: Revised "if ( (getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2) )" by changing > to <.
	
	Bug 3: When playing Remodel, a chosen card of appropriate cost is not added to the player's discard pile (found by cardtest4.c).
	Fix: The fix for bug 4 also solved this issue.
	
	Bug 4: When playing Mine, a card which is too expensive gets incorrectly added to player's hand (found by randomtestcard.c).
	Fix: Revised "if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )" by changing > to <.
	
	Bug 5: When playing Mine, a chosen card of appropriate cost is not added to the player's hand (found by randomtestcard.c).
	Fix: The fix for bug 6 also solved this issue.
	
	Bug 6: When playing Mine, a chosen card which was not a coin was incorrectly added to the player's hand (found by randomtestcard.c).
	Fix: Revised "if (choice2 > treasure_map || choice2 < curse) {
			return -1;
		}" to check if choice2 is a coin:
		if (choice2 > gold || choice2 < copper) {
			return -1;
		}
	
	Bug 7: When playing Mine, card to be trashed is instead moved to played cards pile (found by randomtestcard.c).
	Fix: Revised loop commented "//discard trashed card" so that it removes the trashed card from the game rather than discards it. This is done by switching the card to be trashed with the last card in the player's hand. Then setting the last card to -1 and decrementing the player's handcount.
	
	Bug 8: In Baron card, while loop is exited too early (this is a bug I introduced in previous assignment).
	Fix: Changed 'card_not_discarded == 0;" check back to 'card_not_discarded = 0;' assignment
	
	Bug 9: In Minion card, all players (including current player) discarded hands if their hand size was greater than 4 (this was a bug I introduced in an earlier assignment).
	Fix: Re-introduced "if (i != currentPlayer)" check into 'other players discard hand' section.
	
	Bug 10: In Minion card, the incorrect player discards (this is a bug I introduced in an earlier assignment).
	Fix: Replaced 'currentPlayer' parameter in discardCard() method back to 'i' as was originally in code.
*/