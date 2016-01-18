#Documentation.c
#Rishi Bhandarkar
#CS 362

#Documentation.c

Smithy Card
- The Smithy card is an Action card that allows the player to draw 3 additional cards from their deck. 
- It costs 4 treasures to purchase the Smithy card from the Supply pile.
- The Smithy card action is processed in the cardEffect function
Pseudocode:
- For loop (3 iterations)
	- Draw a card
- Discard the Smithy card from your hand

Adventurer Card
- The Adventurer Card is an Action card that allows the player to continaully draw cards until 2 Treasure cards are revealed.
- The non-Treasure cards drawn from this Action will be discarded.
- The costs 6 treasures to purchase the Adventurer card from the Supply pile.
- The Adventurer card action is processed in the cardEffect function
Pseudocode
- Let x be the number of treasure cards drawn, initialize to 0
- While you haven't drawn 2 Treasure Cards (x < 2)
	- If the deck is empty:
		- Shuffle the discard pile and use that as the deck
	- Draw a card from the deck
	- If the drawn card is a treasure card:
		- Increment treasure counter (x++)
	- Else:
		- Move drawn card into temporary hand to be discarded later
		- Increment counter to track how big temp hand is
- Discard temp hand to discard pile

discardCard() Method
- This method removes a card from the player's hand either by discarding it or trashing it
- The function knows whether to discard or trash based on the trashFlag parameter passed
- The function checks if the player played the last card in their hand or if the card to be discarded is the top card in their hand:
	- Decrement the count of the hand to put the discarded card outside the bounds of the hand so it cannot be accessed
- Else, the card to be discarded is in the middle of the player's hand:
	- Move the card to be discarded to the top of the player's hand, then decrement the card count
	
updateCoins() Method
- Calculates the total coins the player has
- Reset coin count to 0, then sum all treasure cards
- For each card in the player's hand:
	- If the card is either a copper, silver, or gold, add that amount to the coin count
	- 1 for copper, 2 for silver, 3 for gold
- Add any bonus coins to the total