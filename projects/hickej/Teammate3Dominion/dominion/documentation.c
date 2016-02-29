/*
Smithy Card:
	Returns a cost of 4 (found in the getCost() function)
	When played:
		Runs a loop three times that causes the drawCard() function to be called, causing the player to draw three cards
		Discards the smithy card from the player's hand

Adventurer Card:
	Returns a cost of 6 (found in the getCost() function)
	When played:
		While the player still needs to draw two cards:
			If the draw deck is empty, reshuffle the discard pile and add it to the draw deck
			Draw the top card in the draw deck
			If the card is a treasure card, add one the the drawn treasure variable
			If the card is not a treasure card, add it to the player's hand
		Discard all cards in the player's hand

discardCard():
	If a card does not contain the trash flag, add it to the discard pile
	Set played card to -1 <- this should be better figured out
	If that was the last card in the player's hand or second to last, subtract the size of the player's hand by one
	If not, place it in the back of the player's hand and reduce the size of the hand by 1

updateCoins():
	Reset the coin count
	For each treasure card in the player's hand:
		If it's a copper, add one to their coin amount
		If it's a silver, add two to their coin amount
		If it's a gold, add three to their coin amount
	If the player gets a bonus, add that too
*/