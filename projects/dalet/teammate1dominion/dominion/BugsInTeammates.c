/*
Matt Walz
CS 362
Assignment 5 - BugsInTeammates.c

I tested both of my teammates' dominion code with the cardtest1.c, cardtest2.c, cardtest3.c, cardtest4.c, randomtestadventurer.c, and randomtestcard.c tests which I developed. This means that the following card effects were tested for each of my teammates: adventurer, mine, remodel, smithy, and village (testcard3.c and randomtestadventurer.c both tested the adventurer card). Breaking down the testing by teammate and card, the following were the results of my testing.




Teammate 1 (Rishi Bhandarkar):
Adventurer bugs:
	1. An incorrect number of cards are added to the player's hand.
	2. The adventurer card is not being added to the played card pile (and the playedCardCount variable is not being incremented).

Mine bugs:
	1. Failed to add chosen card to player's hand when it cost less than allowed.
	2. Incorrectly added the chosen card to player's hand when it cost more than allowed.
	3. Incorrectly allowed a non-coin card to be chosen and added to a player's hand.
	4. Trashed card is added to the discard pile rather than being removed from game.

Remodel bugs:
	1. Trashed card is added to the playedCard pile rather than being removed from game.

Smithy bugs:
	1. An incorrect number of cards are added to the player's hand.

Village bugs:
	1. An incorrect number of actions were added for the player.


	
	
Teammate 2 (Tom Dale):
Adventurer bugs:
	1. Treats silvers as non-coin cards.
	2. The adventurer card is not being added to the played card pile (and the playedCardCount variable is not being incremented).

Mine bugs:
	1. Failed to add chosen card to player's hand when it cost less than allowed.
	2. Incorrectly added the chosen card to player's hand when it cost more than allowed.
	3. Incorrectly allowed a non-coin card to be chosen and added to a player's hand.
	4. Trashed card is added to the discard pile rather than being removed from game.

Remodel bugs:
	1. The trashed card is removed from player's hand even when chosen card is too expensive (and, thus, not added to player's hand)
	2. Trashed card is added to the playedCard pile rather than being removed from game.

Smithy bugs:
	1. An incorrect number of cards are added to the player's hand.

Village bugs:
	No bugs found
*/