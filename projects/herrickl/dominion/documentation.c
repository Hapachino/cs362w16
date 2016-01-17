/******************************************************************
Assignment 2 - Documentation of Smithy, the aventurer cards (Pt 2)
Author: Lynn Herrick
Date: 1/16/2016

Smithy:  This card, when played, gets 3 more cards drawn to the 
player.  It is an action card and costs 4.


Adventurer:  This card, when played, has the player draw cards 
from their deck.  If the card is not a treasure card, the drawn 
card is discarded.  If a treasure card is drawn, that card is put
into the player's hand.  This action repeats until two treasure 
cards are drawn.  It is an action card and costs 6.


discardCard():  In game, this puts the selected card(s) in the
discard (played card) pile.  This function is called during the 
player's turn when a player chooses to discard card(s) and/or when
the player plays a card (which is discarded after play).  It is 
also called in response to an opponent's played card which causes a 
discard.  In code, if the card enters this function as played, it is
put in the played pile.  If it has been played or if it enters this
function as discard, it is removed from the player's hand.  As a 
response to card, this function is also called within:
	-cardEffect() - if card is council_room (played), mine (played), 
	smithy (played), village (played), great_hall (played), 
	minion (played), steward (played and discard 2 other cards if 
	player chooses this option), ambassador (played and discard/s if 
	copies of card), cutpurse (played), embargo (disgard), 
	outpost (played), salvager (played and discard if player chooses
	this option), treasure_map (discard two treasure map cards)


updateCoins(): In game, this updates the amount of coins a player 
has.  In code, this looks at a players hand and adds coins for all
of the "treasure" cards and then adds any bonus coins.  Bonus coins
can be collected from the following game functions: 
	-initializeGame() - no bonus coins

	-playcard() - bonus if coins gained from actions

	-endTurn() - no bonus coins

	-cardEffect() - bonus coins gained from card effects.  Cards 
	include "feast" for 5 and "cutpurse" for 2.

******************************************************************/