Adventurer card:
Rule: Draw cards until you have drawn two treasure cards. Put those treasure cards in your hand and discard the rest of the drawn cards.

cardEffect()
switch()
case: adventurer
Draw cards until 2 treasures found:
	While (drawntreasures < 2):
		If (deck empty): shuffle discard and add to deck
		drawCard()
		set variable cardDrawn to most recently drawn card
		If (card drawn is copper or silver or gold): add 1 to drawntreasures
		Else: add card to temphand, remove top card of hand, add 1 to z
Discard extra cards:
	While (z-1 >= 0):
		discard temphand[z-1]
		subtract 1 from z
	

Smithy card:
Rule: Draw 3 cards

cardEffect()
switch()
case: smithy
draw 3 cards:
	For i in range (0,3)
		drawCard()
put played card in discard:
	discardCard()
	


int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag) method:

Check trash flag. If card is not being trashed, then add it to the playedCards and increment playedCardCount. 
Regardless of whether the card is being trashed, it now needs to be removed from the hand. 
Set the played card to -1 in the current player's hand.
Check if the card is the last card in the hand, or if it is the only card in the hand. 
If it is, then simply decrement the handCount to trim it from the hand.
Otherwise, swap the last card position and played card position and then decrement handCount to trim it from the hand.

Note: I don't understand the necessity of differentiating between a hand of only one card.
When the handCount is 1, then played card must be the last card and would be caught by the first if condition.
This code works, but seems extraneous to me.



int updateCoins(int player, struct gameState *state, int bonus) method:

Set coin count to 0. Loop over current player's hand and check if each card is a treasure.
If copper, add 1 to coins. If silver, add 2 to coins. If gold, add 3 to coins.
Add in bonus coins as provided in input.
return coins





















