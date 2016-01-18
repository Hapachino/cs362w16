/* THIS IS NOT A C FILE
 *
 *
 *

Refactoring v1.0
By: Thomas "Adam" Pippert

Refactoring of cards was performed for the following 5 Dominion cards:


1) Smithy
Smithy became the smithyCard function.

int smithyCard(int handPos, int currentPlayer, struct gameState *state)

The bug introduced in the smithyCard function is the for loop containing <=3, which introduces
a 4th card instead of the intended 3 cards to be added to the hand.


2) Adventurer
Adventurer became the adventurerCard function.

int adventurerCard(int currentPlayer, struct gameState *state)

The bug introduced in the adventurerCard function is in the while loop for discarding the
cards in play that have been drawn.  By setting the terminating condition to 1 instead of
0, this always leaves behind a card when clearing cards from the hand that have been drawn.


3) Mine
Mine became the mineCard function

int mineCard(int choice1, int choice2, int handPos, int currentPlayer, struct gameState *state)

The bug introduced in the mineCard function is that the gainCard function, which is supposed to add a card
to the current player's hand, actually adds the card to the deck instead.  The flag value should be set to "2",
but is set to "1" in the function.


4) Salvager
Salvager became the salvagerCard function

int salvagerCard(int choice1, int handPos, int currentPlayer, struct gameState *state)

The bug introduced to salvagerCard is that the numBuys function is moved to the choice1 loop instead of the
beginning.  This means that if the Salvager card is played and there is a valid card to trade for coins, then
the card operates like normal.  If the choice1 card is not there, the numBuys++ never gets called, and so it
is not incremented like it should be.


5) Treasure Map
Treasure Map became the treasureMapCard function

int treasureMapCard(int handPos, int currentPlayer, struct gameState *state)

The bug introduced in the treasureMapCard function is that the statement detecting whether or not there is a second
treasure map should include i != handPos (which indicates that the map is in a different place than the current card),
but in fact always is true due to being i == handPos, so the player gains 4 gold even if there is only one treasure
map card.
