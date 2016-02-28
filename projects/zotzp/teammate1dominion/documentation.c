/*
Jeannine Amm
CS362w16
Assignment2: documentation.c
Due Date: Jan 17, 2014

Instructions:
Documentation should contain your understanding of smithy and adventurer cards
(code).  It should also contain documentation of your understanding of
discardCard() and updateCoins() method.

My Understandings:
smithy:
	Action: Smithy adds 3 cards from the player's deck to the player's hand
	Smithy card index is 13 and is assigned in dominion.h
	Smith value is assigned a cost of 4 coins in getCost().

	Steps performed when card is played:
	3 cards are drawn from the Deck and added to the players hand.
	Smithy Card added to the discard pile.

adventurer:
	Action: Adventurer flips through the cards in the deck until it finds 2 treasures.
	If only one treasure can be found in the deck it keeps flipping through the
	deck until the full deck is seen.

	Adventurer Card index is 7 and is assigned in dominion.h.
	Adventurer is assigned a cost of 6 coins in getCost().

	Steps performed when card is played:
	If the deck is empty discard cards are shuffled and added to the deck
	Single Cards are drawn from the player's deck and added to hand.
	If the card is not a treasure the card is added to temphand and removed from
	players hand.
	Once two cards have been added to the hand all cards drawn
	that were not added to the hand are added to the discard Pile.

discardCard():
	Receives handPos, current player number, G as gameState and trashFlag to identify if the card is trashed or added to played pile
	Purpose:  discards a card from the hand
	If the card is to be played add the card to the played pile (state->playedCards[]).
	If the card is trashed it is not added to the played pile.

	Steps performed:
	The played card count is increased. (state->playedCardCount)
	The card index in the hand is set to -1 and removed from the hand.

	if there is more than one card left in the hand when the card is played or
	trashed move the last card into the discarded position the last card is moved
	into the discarded card position in the hand.

updateCoins():
	Receives player number, G as gameState and bonus coin value
	Purpose: Updates coins available for buy phase

	steps performed:
	set state->coins to 0
	Add 1 coin to state->coins for every copper in hand.
	Add 2 coins to state->coins for every silver in hand.
	Add 3 coins to state->coins for every gold in hand.
	Add bonus coins to state->coins if any.
	state->coins holds the total of coins that can be spent in buy phase.
*/
