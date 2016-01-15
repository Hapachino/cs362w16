Smithy
When a player plays a Smithy card, that player will draw three cards. Then the player will discard the Smithy card.

Adventurer
When a player plays an Adventurer card, that player will draw cards until they have drawn two treasure cards. If the 
deck becomes empty it will be reshuffled. When a treasure is drawn, it is added to the player's hand. Any card drawn 
that is not a treasure is simply discarded.

discardCard()
The function discardCard() takes four parameters: the position of the card in the player's hand, the current player, 
a pointer to the game state (which contains data about the players and their hands), and a boolean which determines 
whether the card is trashed and removed from the game or simply added to the discard pile.

If the card is not to be trashed, it is added to the discard pile. Otherwise, it simply ceases to exist when it is 
removed from the player's hand in a few lines. Next, the card's position is determined. If it is the last or only
card, it is simply removed. Otherwise, the last card in the hand replaces the discarded card, and the discarded card 
is removed.

updateCoins()
The function updateCoins() takes three parameters: the player, a pointer to the game state, and the coin bonus the 
player receives this round. First, the game state's coin integer is reset to 0. Then, the player's treasure cards 
are added together and stored in the game state. Finally, the bonus is added and the total remains in the game state.