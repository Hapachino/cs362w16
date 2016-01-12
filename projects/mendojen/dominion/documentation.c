 smithy- Draw 3+ cards. When this card is played, the drawCard() and discardCard() functions are 
 called. The card count in a player’s hand is increased by 3 (by calling drawCard() function 3 times) 
 while the deck card count is decreased. The smithy card is then discarded with the discardCard() function.
 
 adventurer- Reveal cards from your deck until you reveal 2 Treasure cards. Put those Treasure cards 
 into your hand and discard the other revealed cards. In the code, the number of treasures are being 
 tracked by a variable. DrawCard() function is again called to draw until drawntreasure is 2. If the 
 deck runs out of cards, the discard deck is shuffled. The cards that are not treasures are discarded.
 
 discardCard()- First, the trashFlag integer variable is checked to see if it is a 0 or 1. If it is 0, 
 the card is added to the played pile (or discard pile). If trashFlag is 1, this means that the card was 
 trashed and is removed from the game. This function also keeps track of the number of cards that are still 
 in a player’s hand. 
 
 updateCoins()- This function updates the number of coins a player has in their hand depending on the 
 type of card. First, the coin count is set to 0. Then, each card is read to see if the card is a copper, 
 silver, or gold. If copper, 1 is added to the coin count. If the card is silver, 2 is added, and if card is 
 gold, 3 is added. At the end, a bonus is added. Once the function completes, the total number of coins in a 
 player’s hand is counted.
