/*
Rishi Bhandarkar
CS 362
BugFixes.c
*/

- Adventurer Card
	My teammates discovered that the adventurer card was adding too many cards to my hand. To fix this, I needed to fix the while
	loop that tracked how many treasures were drawn. Instead of drawing while treasures <= 2, I changed it to while treasures < 2.
	In addition, the adventurer card function did not add the adventurer card to the played pile. To fix this, I edited the parameter
	list for the adventure function to include the handPos variable that tracked where the adventurer card was. I then altered
	state->playedCards and state->playedCardCount to track the played adventurer card.
	
- Smithy Card
	Player was incorrectly drawing 4 cards instead of 3. To fix this, I changed the for loop to < 3 instead of <= 3.

- Village Card
	My teammates discovered that the card was incorrectly adding 3 actions to the current player instead of 2. To fix this, I edited
	the state->numActions variable to be incremented by 2 instead of the incorrect 3.

- Council Room Card
	Council room was incorrectly decrementing then number of buys available instead of incrementing. To fix this, state->numBuys was incremented
	in the playCouncil_Room function.

- Feast Card
	When backing up the player's hand before feast card is executed, the for loop to iterate through the player's hand to back it up was bugged.
	To fix this, I changed the conditional to be <= instead of <, so it became i <= state->handCount[currentPlayer]
	
- Remodel Card
	My teammate discovered that instead of trashing a card to gain a new card, the Remodel card was adding the card to the played pile which
	would reintroduce the remodel card into the player's deck. To fix this, the trashFlag parameter needed to be set to 0 when calling the
	discardCard function. Previously, it was set to 0 in the Remodel card code.
	
- Mine Card
	There were a number of errors discovered in the Mine Card code, including: 
		1. Failed to add chosen card to player's hand when it cost less than allowed,
		2. Incorrectly added the chosen card to player's hand when it cost more than allowed, 
		3. Incorrectly allowed a non-coin card to be chosen and added to a player's hand, and
		4. Trashed card is added to the discard pile rather than being removed from game.
	To fix these errors, I edited the code as follows:
		1./2. The conditional was incorrect. We need to check that the selected card costs at most 3 more than the discarded card, so the 
		conditional becomes if( (getCost(state->hand[currentPlayer][choice1]) + 3) < getCost(choice2) ). Before, the conditional was a 
		greater than, so it was finding errors with valid cards, but allowing overly costly cards.
		3. The code was checking that the card to be added was any card in the deck, but it needed to check that the card was a treasure card.
		So instead of a conditional that checks if curse <= choice2 <= treasure_map, the conditional now checks that choice2 is between copper
		or gold.
		4. When calling the discardCard to trash the selected card, I set the trashFlag parameter to 1 to indicate we are trashing the card
		instead of discarding it (which would reintroduce the card into the player deck)