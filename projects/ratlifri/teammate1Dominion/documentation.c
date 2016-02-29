Philip Jones
CS362 - Winter 2016


All cards are selected via a switch statement. When the smithy case is reached, this means that the smithy case will run a loop 3 times, calling the drawCard() function each time-- essentially, 
it will draw 3 random cards. The smithy card will then discard itself using the discardCard() function, and return 0.

Here is what happens in the adventurer case : A loop is set up to check that the case ends when two treasures are drawn. While that count (drawntreasure) remains less than 2, the code loops. 
First, we check to see if the deck has fewer than 2 cards in it. If at any point in the loop the deck dips below 1 card, then the discard pile is shuffled back in with the shuffle() function.
During the loop, first a card is drawn using drawCard(). If this card is any of the treasures (copper, silver, or gold) then the drawntreasure counter is incremented by one.
If the card is not a treasure, then the card is added to a temporary hand. Once two treasures have been drawn as noticed by the drawntreasure variable, the loop ends and all of the cards in the temporary hand
are discarded. 

The discardCard() function is meant to move a card from the player's hand to the discard pile. It takes an int for the handPos, an int for the currentPlayer, a struct pointer to the gameState,
and an int for the trashFlag. If the trashFlag is active (1), then the card gets put in the trash and won't be used again in the game. However, if it's less than 1, then it is added to the playedCards/discard
pile. The playedCardCount is incremented as the card is added to its pile. Similarly, the player's hand count is decremented as the card is removed from there. If there are any cards left in the players'
hand, then the new last one is moved up to be the card at the top. Otherwise, if there are no cards to do anything with, nothing else happens.

The updateCoins function takes an int to identify the player, a struct pointer to the gameState, and an int representing the bonus. What it does is first clear the coin state to 0 so it can do its work. The function
then enters a for loop that calculates coins in the player's hand (that they are using). If the code detects a copper, it adds 1 to the coin coint, a silver adds 2, and a gold adds 3. Finally, once the hand has
been worked through and the loop ended, any bonus coins are added before returning and ending the function.