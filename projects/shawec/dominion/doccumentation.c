Smithy -
* This card uses a for loop to draw three cards, and adds them to the players hand

Adventurer -
* While the number of treasure drawn isn't 2 (<2), then it checks to make sure that there is a card to draw, if not, it shuffles the discard pile and adds them into the pile. In the mean time, it's adding every card that isn't treasure to a temporary hand. After that, it discards everything in the temporary hand that wasn't treasure.

discardCard() -
* Checks if the card is supposed to be trashed, and as long is it isn't, it's added to the played pile, then set to -1 as a flag, is removed from the players hand. 

updateCoins() -
* Resets the coin count to 0, then goes through the players hand and adds coins based on one for copper, two for silver, and three for gold, plus any bonus the player has accumulated. 