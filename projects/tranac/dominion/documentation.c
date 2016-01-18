/* 	File: documentation.c
	Author: Chris Trana
	CS 362

Smithy
When a player plays this card, that player will draw three cards from that players deck. Then the player discards the Smithy card.

Adventurer
When a player plays this card, that player will draw cards from that players deck until they have drawn three treasure (copper, silver, or gold) cards. If the deck becomes empty the players discard pile will be reshuffled into the players deck. When a treasure is drawn, it is added to the player's hand. Any card drawn 
that is not a treasure is then discarded.

discardCard()
This function takes four parameters: the position of the card in the player's hand, the current player, a pointer to the game state, and a boolean which determines whether the card is trashed and removed from the game or added to the discard pile.

If the card is discared it is added to the discard pile and the number of played cards is incremented by 1. Otherwise, it simply ceases to exist when it is 
removed from the player's. Next, the card's position is determined. If it is the last or only card, it is removed. Otherwise, the last card in the hand replaces the discarded card, and the discarded card is removed from the hand.

updateCoins()
This function takes three parameters: the player, a pointer to the game state, and the coin bonus the player received this turn. The game state's coin total is reset to 0. Then, the player's treasure cards are added together and stored in the game state.  Then the bonus is added and the total remains in the game state.

*/
