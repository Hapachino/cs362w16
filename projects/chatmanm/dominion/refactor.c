Myles Chatman

CS 362 Software Engineering II

Assignment 2

1/17/2016

5 functions were created in the dominion.h file and implemented in the dominion.c file.

playAdventurer()
Reveal cards from your deck until you reveal 2 Treasure cards. Put those Treasure cards in your hand and discard the other revealed cards.
playSmithy()
Draw three cards.
playSalvager()
+1 Buy, Trash a card from your hand. +Coin equal to its cost.
playGreatHall()
Trash a card from your hand. +Coin equal to its cost.
playMinion()
Choose one: +2 Coin or discard your hand, +4 Cards, and each other player with at least 5 cards in hand discards his hand and draws 4 cards.
The function getCost() returns a cost value to a specific card. This cost will determine how much the player will need to spend to obtain the card. The card will be added to their deck and once it becomes part of their hand, the cards action may be used.
Adventurer - The player gets to reveal cards in their deck. It's cost value is 6 coins and is an action card.
Smithy - This is a simple, basic action card. Upon use, the player is able to draw three more cards. It's cost value is 4 coins.

discardCard()

These newly created functions commonly use discardCard(). The game Dominion has a discard pile reserved for cards that the player(s) may have to remove from their hand. This can occur from the action of another card or at the end of a turn. This function  checks whether the card that is going to be trashed was played during the turn or forced to be trashed due to the action of another card. If it was played, then that card is moved to the played pile, otherwise it goes to the discard pile. The player's hand needs to be updated by removing that card from its hand and updating the player's number of cards.

updateCoins()

The functions above do not use updateCoins() but its purpose is to control the numerical values associated to currency copper(1), silver(2), and gold(3). Coins are always reset to the value 0 on each turn. This is an very important function in the game when the player decides to purchase different currency or a new card. The player's coins needs to be updated depending on how much they decide to spend.
