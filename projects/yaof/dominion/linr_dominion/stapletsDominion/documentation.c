Shaun Stapleton
CS 362
Assignment 2

Smithy - The Smithy costs 4 coins and is an action/kingdom card. The code loops through the
drawCard() function three times in order to pull three new cards for the player from which they
can use in their current hand. The discardCard() function is then called on the current smithy
card which is discarded from the hand. 

Adventurer - The Adventurer costs 6 coins and allows the player to pull cards from their deck 
until they pull two treasure cards. The code for this runs a while loop that is based on the
condition that less than two treasure cards have been drawn. While there are less than two,
the deckCount is checked to see if it needs reshuffling. After that the drawCard() function
is called on the top card of the deck. If a treasure card is pulled the drawntreasure count is
incremented. If not treasure card is pulled the top card is pulled off and we move to the next
card. Once we have incremented the drawntreasure to the count of two we break the loop and 
another while loop is entered which will discard each of the non treasure cards that were
pulled during the first while loop.

discardCard()- The discardCard() function receives the hand position of the card, the current
player, the game state, and a trash flag. First the trash flag is checked and if it is not
marked then it is placed into the played pile. Next the played card is set to -1 and checked
to see if the player has anymore cards in their hand. The number of cards in hand is reduced
regardless of whether the play has 0,1, or several cards left.

UpdateCoins()- The UpdateCoins() function receives the player name, game state, and bonus amount.
The coin total is set to 0 and then a loop iterates through the players hand and counts how
many treasure cards the player has and what the value of the card is when it is passed over.
After the loop, if there is a bonus it is added to the coin total for the player.