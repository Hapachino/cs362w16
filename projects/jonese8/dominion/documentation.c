CS 362 Assignment 2
documentation.c
Emmalee Jones


Smithy - This card draws the next three cards in your deck and adds them to your hand using the drawCard method.
After it is played the discardCard function is called to send the smithy card to the discard pile and returns 0.

Adventurer - While the drawntreasure counter is less than 2 the following process is repeated. The function checks
if the deck is empty. If it is, the discard deck is reshuffled and added to the deck.  Then the drawCard function
is called. If the top card is a treasure card, a drawntreasure counter is incremented. Otherwise,  the card is 
stored in a temporary hand.  This loop is repeated until two treasure cards are found, or you reach the end of 
the deck without finding two treasure cards.  The function finishes with discarding all cards in the temporary 
hand back to the deck and then returns 0.  

discardCard() - The function first tests the trash flag attribute on the card to determine if the card will go to 
the discard card pile or to trash.  If the trash flag is not set, the card is added to the discard pile, the
discarded card count is incremented, and the card is marked as played (-1).  If the last card in the hand is
played or the hand count is equal to one card, the hand count is reduced by 1. Otherwise it replaces the 
discarded card with the last card in the hand.  It also sets the discarded card as played (-1) and reduces the 
number of cards in the hand. It then returns 0.

updateCoins() – The function resets the coin count to zero and then loops through each treasure card in the player’s 
hand adding the number of coins equal to the type of treasure identified to the coin count.  Copper is one coin, 
silver is two, and gold is three. Any bonus coins are added in at the end of the function from action cards.  The 
total coins are the amount that can be used for purchases. It then returns 0.
