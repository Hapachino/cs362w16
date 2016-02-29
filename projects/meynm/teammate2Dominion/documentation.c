/*

Nelson Samayoa
CS362
Assig 2
Onid: samayoan

Smithy:
Within the cardEffect function we get the best insight into the Smithy card's usage.
The first block in the 'smithy' case of the switch statement calls the drawCard funtion three times.
The smithy card thus gives the player 3 more cards and no extra buys. 

Adventurer:
In short, the adventurer card gives the player two treasure (money) cards. The way in which these cards are
retrieved is by continuously drawing from the deck (cards not yet used in the game) until two new treasure cards have been obtained. The player
then discards all non-treasure cards they have just pulled from the deck.
In the code we see that the block under the 'adventurer' case in the switch statement of the cardEffect function is wrapped in a 
while loop that runs while drawntreasure<2. Once the number of drawn treasure cards is 2, the loop stops. In the loop the code
checks if the drawn card is treasure card (copper, silver, or gold). If it is a treasure card, drawntreasure is increased; otherwise the code moves along.

discardCard():
The main purpose of the discardCard function is to get rid of a card from the player's hand after having played it.
The function does this by adding it to the played card pile if the card is not being trashed.
Then the number of cards in the player's hand is reduced by recuding the int state->handCount.
Lastly, it makes the next card in the deck the 'top' card in the stack in hand.

updateCoins():
When a player's hand has treasure cards, the updateCoins function updates the cache of total money in that players hand.
For example, if player 1 has one gold and one silver card in his/her hand, updateCoins will set state->coins to 5.

*/
