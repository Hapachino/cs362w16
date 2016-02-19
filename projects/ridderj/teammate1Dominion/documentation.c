1) Playing a Smithy card
The Smithy card is an action card that allows the player to draw 3 more cards.
Choosing the card calls cardEffect(). cardEffect() has a switch statement that identifies the Smithy card, which then calls drawCard() 3 times.
The card is then discarded from the player's hand with discardCard().

2) Playing an Adventurer card
The Adventurer card is an action card that essentially keeps drawing cards from the player's deck until two treasure cards are drawn.
Just like Smithy, choosing the card calls cardEffect(). Then, while there are less than 2 drawn treasure cards, it draws another card. cardEffect() has measures in place to check 
for things like an empty deck (it shuffles the discarded pile ands it to the deck), if it drew a treasure card. It also clears cards from the hand that aren't treasure cards.

3) the discardCard() function
	First, the function checks whether this card is trashed or will continue to be in play and be added to the discarded pile using the trashFlag variable. Then,
it goes about setting the card to the beginning of the player's hand array and reducing their hand count.

4) updateCoins() function
	This function starts by setting the count of coins to 0. Then, it goes through each card in the player's hand and adds copper, silver, and gold coin values to the running total. Finally it sets the
game state total coin count to the running total plus any bonuses from action cards.