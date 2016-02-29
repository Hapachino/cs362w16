Smithy card: 
The Smithy card when played calls drawCard three times, passing in the currentPlayer and the gameState. It then calls discard passing in the position of the hand (the Smithy card position)

Adventurer card: 
The Adventurer card when played loops while the amount of treasure cards drawn is under two. In this while loop it checks to see if the deck is empty, if it is it shuffles. It then draws a card. It checks the card to see if it is a treasure card. If it is then it increases drawn treasure (what is used to check for the amount of treasure cards drawn), and then it repeats the loop. If it is not a treasure card then the new card gets it added to a temporary hand with an index of z, that z is incremented, and then the count of the current players hand is decremented. At the end of the above while loop there is a second while loop that goes from z to 0 where z is decremented twice each run. In this while loop the cards from the temp hand are added to the current players discard pile, and the current players discard count is incremented. 

discardCard function: 
Discard card first checks if the card is not trashed. If it isn't it adds it to the played pile in the game state and increments the played card count. It then removes the card from the players hand. If the card is the 5th card in the hand or the only card in the hand then the count of the cards in the hand is just decremented. Otherwise the discarded card gets swapped with the last card in the hand and the number of cards in hand is reduced. 

updateCoins function: 
Update coins first sets the total coins to 0. It then loops through each card in the players hand checking if the card matches a treasure card. If it does then the value of that treasure card is added to the total coins. After the for loop whatever bonus is available is added to the total coins. 

