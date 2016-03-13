Charles Hardes
CS 362 Winter 2016
Assignment 2

Adventurer Card:

When the Adventurer card is played, the drawntreasure variable is first checked to ensure that it is below 2. This will be the variable that determines when enough treasure cards have been drawn, completing the action of the Adventurer card. If it is less than 2, the deck is checked to ensure there is at least one card left to be drawn, if not; it is reshuffled. A card is then drawn and checked to see if it is a treasure card. If it is, the drawntreasure variable is incremented and the loop continued. If it is not a treasure card, it is added to the temphand with an index of z incremented to keep track of how many cards are in the temp hand. Once 2 treasure cards have been drawn, all cards in the temp hand are discarded and the rest of the turn is completed.

Smithy Card:

When the Smithy Card is played, there are simply 3 additional cards drawn and the Smithy Card itself is discarded. The turn is then continued.

discardCard():

The discardCard() function is used to discard a played card back into the player's pile. This is a separate action from trashing a card. First, the trashFlag flag is checked to ensure that this is not a trashing action. If not, the card is added to the playedCards attribute of the state and the playedCardCount incremented. The handPos of the hand is then set to -1. Then, the hand and handCount attributes of the state are adjusted, decreasing the hand count and getting rid of the card.  

updateCoins():

The updateCoins function updates the value of all coins in the current player's hand. It adds 1 for each copper, 2 for each silver, and 3 for each gold coin to state->coins. A bonus is also added, if present, passed into the function directly by value.
