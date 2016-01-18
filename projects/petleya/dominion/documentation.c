Ava Petley
Smithy:
Smithy is an action card that adds three cards from your deck to your hand. In the code there is a for loop that is set to loop 3 times each time it calls the drawCard function to which it passes the currentPlayers information so that players stats will be the stats that get adjusted. It also passes the state which holds the state for the players such as it indicates treasures for the player. The drawCard will add a card the player’s hand. After the for loop the discardCard function is called which will add the played smithy card to the discard pile.

Adventurer:
			
The adventurer card is an action card that allows you to look through your draw pile until two treasure cards are revealed. In the code for the adventurer card there is a variable called drawntreasure that will keep track of the treasure cards that are drawn after playing the adventurer card. Onces drawntreasure is at two the player can stop drawing cards. The while loop continues until 2 treasure cards are in the players hand. Within the while loop is the code for drawing cards and checking to see if they are treasure cards. First, the deck is checked for cards if it is empty then it is shuffled. Then a card is draw, that card is checked. If the card is a treasure card then the drawntreasure variable increases by one and the card is left in the player’s hand. Otherwise it is put into a temporary hand that will be discarded after this action card is finished. After the two treasure cards are in the players hand the drawing stops and the draw cards that were not treasure cards are put into the discard pile.

discardCard:
This method removes a card from the users hand. If the trashFlag indicates card to be trashed it will be trashed. Otherwise the card is marked as played by getting a handpost of -1. The number of cards in the players hand is decreased by one.

updateCoin:
This method recalculated the player’s coin status. First the coin state is reset to zero. Then the players hand is checked for treasure cards and the type of coin will get the appropriate value (example: copper will add one). Then any bonuses are added.






