Eric Anderson
CS362 Winter 2016
Assignment 2

Submit a file called documentation.c (.c file because github thinks you are using github for file storage if you 
use many .txt files) that contains documentation of smithy, adventurer cards. Documentation should contain 
your understanding of smithy and adventurer cards (code). It should also contain documentation of your understanding
of discardCard() and updateCoins() method.  Keep your documentation short, though there is no upper limit.
Documentation.c file should contain at least 100 words.  

Smithy: The action associated with the Smithy card is to draw three cards into the player’s hand. The smithy
case loops over the drawCard() function three times to draw 3 cards (this is the action for this card). It
then calls the discardCard() function to end the effect of the Smithy card.

Adventurer: The action associated with the adventurer card is to reveal cards from your deck until you
reveal 2 Treasure cards. Put those Treasure cards in your hand and discard the other revealed cards. The
case first checks to see if you have drawn two treasure cards.  This then checks to see if the player’s
deck is empty, if it is, then shuffle the player’s deck.  Then draw a card from the deck.  Set the CardDrawn
variable to the card type (gold, silver, copper) and check to see if the cardDrawn is a treasure card by
comparing its name to the hard coded values of copper, silver or gold.  If it is any of these then increment
the drawntreasure counter.  if it is not, add the card value to the temp hand array, decrement the handCount
array index and increment the index for tempHand.  Soon as we have drawn two treasure cards and the temp hard
array is not empty, set the discardCount (in other words increment it) to the size of temp hand -1 (so the
indexes match), then set the hand Count to include the temp hand so we discard everything at the end of the
turn and reset temphand for the next time the action card is used. 

discardCard(): This function is called 24 times in the cardEffect function to dismiss action cards or to
dismiss cards if that is the result of an action card.  The discardCard() function first checks the trashFlag
to see if it has been set (a 1 if set).  If it has not been set, then the card is added back to the played
pile (playedCards array) indexed at the current position.  Then we “flag” the card as being out of the players
current hand by setting the value at the index of this card to -1 in the hand array that represents the cards
the player has in their hands.  We then check to see how many cards the user has in their hand.  First we
check to see if this is the last card in the hand array, if it is, we decrement handCount effectively
eliminating this card.  OR we check to see if this is the only card in the array, if it is, it too is
decremented meaning we have no cards in the user hands.  Otherwise, we need to set the card to be the last
card in the array, then we treat it like the first case and decrement the count and eliminate the card.
Then we “return” back to cardEffect() indicating that the actions card or sub action has been completed.

updateCoins(): updateCoins() is called from 4 different functions; initializeGame, playCard, endTurn, and
cardEffect (twice). The updateCoins function begins by resetting the player’s coin count to 0.  It then
iterates though the players hand (based on handCount) to determine if the player has a treasure card (labeled
copper, silver or gold) and for each card that matches it adds one coin for each copper, two for each
silver, and three for each gold to the coins object.  Finally, if a bonus was passed to the function, it adds
the value (in coins) of the bonus passed in to the coins object and then the function returns to the calling
function.  
