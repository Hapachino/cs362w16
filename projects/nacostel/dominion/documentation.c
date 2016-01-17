Smithy:
-Allows player to draw 3 additional cards

Adventurer:
-Allows player to draw cards until two treasure cards are drawn
	-after two treasure cards are drawn, all other cards are discarded

discardCard():
-Receives hand position, current player, game state, and trash flag
-Returns 0
-Removes played card from player's hand
	-if trash flag not set, add card to played pile 
	-remove card from player's hand


updateCoins():
-Receives player, game state, and bonus
-Returns 0
- Iterates through every card in player's hand and updates player's coins accordingly
	-adds one coin, for each copper card
	-adds two coins, for each silver card
	-adds three coins, for each gold card
	-adds bonus as needed