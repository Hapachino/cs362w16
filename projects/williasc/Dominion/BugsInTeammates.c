/*
Scott Williams
Assignment 5 -- Bugs in Teammates code


Teammate1 - Matthew Boal:
NOTE: 	This was hard to test as there were a number of changing commits. Sometimes there were seperate card functions
		in dominion.c sometimes there weren't. The latest update to dominion.c didn't have separate card for things like
		playAdventurere(), I had to modify tests a bit more than normal.

LOCATION:
	council_room card

BUG1:
	In this bug it's very sutble and it took some time to find it. In essence ONLY the current player will get to discard
	a card. This messes up the rest of the players if it is played.

CODE:
	if ( i == currentPlayer )

LOCATION:
	great_hall card

BUG2:
	This was a simple mistake, but you can get a card now if the cost is less. So it is inflating your hand. The cost
	is supposed to be +2 but it was +3 in the code.

CODE:
	if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )

Teammate2 - Gerald Gale

BUG 1:
    Play adventurer card
    kept card count = 3, expected = 2

NOTE:
    The number of cards in the hand is 1 higher than it should be.  This indicates that
    either the adventurer is not being discarded, or too many cards are being drawn.  After looking at the code, it's
    clear that the line to discard the adventurer card is missing.


BUG 2:
    Play village card
    drawn card count = 0, expected = 1

NOTE:
    It looks like the village card did not draw a card.  It should have drawn two cards.
    The line to draw a card is missing from this function.


*/
