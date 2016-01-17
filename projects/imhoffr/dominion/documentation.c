/*
Regina Imhoff
CS 362 Winter 2016
Assignment 2


The following is my understanding of how various parts of Dominion work.  

Smithy:
  The Smithy card adds 3 cards from the player's deck to the player's current hand and then the 
  Smithy card is added to the discard pile.  The Smithy card   costs 4 coins to purchase.  

  In the code:  
  When the Smithy card is selected, it is passed into cardEffect() as a parameter.  drawCard() is
  called 3 times, the parameters being the player (currentPlayer) and the state. Then the card is
  discarded (discardCard).  

Adventurer:
  The Adventurer card is an Action card that reveals cards from your deck until 2 total Treasure
  cards are revealed.  The player keeps the Treasure cards and discards the non-Treasure cards
  that were drawn looking for the Treausre cards    

  In the code:
  While the drawntreasure is less than two, if the deck is empty, shuffle the discard pile.  
  Otherwise, if the card that is drawn (cardDrawn) is a copper, silver, or gold card, then
  drawntreasure is increased by one.  Any other cards go into a temporary hand (temphand) 
  as an array size z, z being increased by one each time a non-copper/silver/gold card is
  drawn.  

discardCard()
  This function determines how to handle a discarded card.  
  If the trashFlag is less than one, then the card goes from being a played card to being
  a card currently being held.  Otherwise, the card goes to the player's discard pile.  The
  played cards counter increases by one and the number of cards in the player's hand is 
  decreased by one.  The card that the player is holding (handPos) is updated each time
  to the next card in the player's hand.  

updateCoins()
  This function coverts copper, silver, and gold cards in the player's hands into 
  a coin value.  It also updates with any bonuses from other cards that may have been
  played.  

*/
