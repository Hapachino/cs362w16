Susan Eldridge
eldridgs
CS 362
Winter 2016

<<<<<<< HEAD:projects/eldridgs/dominion/documentation.c
Smithy:
This allows the current player to draw three cards, adding to the total number of cards in their hand.
Then the Smithy card is discarded as it can only be used once.
=======
/* adventurer: */
This card draws cards from the player's deck until the player draws three
treasure cards total. All cards drawn from the player's deck that were not
treasure cards are moved into the player's discard pile.
>>>>>>> 86f5fb16c2c1797902d608386527b1fdb83758fd:projects/swaffork/dominion/documentation.c

Adventurer:
While drawntreasure is less than two, this reshuffles if the deck is empty, then draws a card.  If the
card that is drawn is a copper, silver, or gold (treasure), then drawntreasure is increased by 1.
Since drawntreasure starts with a value of 0, this makes the cards continue to be drawn until a total of
3 treasure cards are found.
If the drawn card is not a treasure card, cards are continued to be drawn.  The else statement keeps
a tally of the number of cards drawn.  Once drawntreasure is equal to 2, the second while statement
puts the tallied cards into the discard pile.

DiscardCard():
This function is given the hand position of the card to be discarded, the information about who's turn
it is, the state of the game, and the trash flag.
If the trash flag is 0, the card is not trashed.  This means that the card in the current player's
hand position is played.  This causes the number of cards in the player's hand to decrease by one.

UpdateCoins():
This function is given the information for the player who's turn it is, the state of the game, and
any bonus.  Coin count starts at 0.
The number of coins is tallied from the treasure cards by adding up copper coins for +1, silver coins
for +2, and gold coins for +3.  Then the bonus (from other cards in the hand) is added to the total number of coins found
from the treasuer cards.
