/**Jennifer Frase
  CS 362
  Assignment 2
  This file simply contains documentation for the smithy and adventurer cards as well
  as the discardCard() and updateCoins() functions. Card costs where determined be looking at the
  getCost function while the pasted codes below for the cards where copied from the cardEffect
  function. Since the getCost function is just a switch statement that returns the cost of the card,
  it's code was not included.
*/

/**Smithy Card's code:

  This card will draw 3 cards from the players deck for a cost of 4 and add those cards to the players hand.
  After all three cards are drawn the smithy card is discarded.*/


/**Adventurer Card's code:

  This card will continually draw from the deck until 2 treasure cards are drawn at the cost of 6 coins.
  Once a card is drawn it is added to the current player's hand. If that card is not a treasure card,
  then the card is removed from the player's hand and added to the discard pile through the use of a temporary hand.*/



/**discardCard's code:

  This function will take a card and if the card is not being trashed then it is added to the discard pile(playedCards array).
  In either case then the card removed from the players hand by giving it a nonrecognizable value for the card. If the
  card is in the middle of the players hand then the current highest indexed card and it are swapped before the highest
  indexed card in the player's hand is removed.*/

/**updateCoins's code:

  This function will loop through all the cards in a players hand and if the card at the current index is a
  treasure card then the monetary value of the card is added to the players coins. After all the cards have
  been examined then the passed in bonus value is added to the coins.*/
