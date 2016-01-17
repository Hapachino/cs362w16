Smithy Card - Action card that can be played during the first half of a
player's turn. When played the player immediately draws three more cards
from their deck into their hand. If necessary reshuffle your discard into
your deck.

Adventurer Card - Action card that can be played during the first half of a 
player's turn. When played the player reveals cards one by one from their deck
until two treasure cards are revealed. The non-treasure cards are then
discarded and the treasure cards are added to the players hand.

discardCard() - First: if the card isn't going to be trashed it is added to
the player's discard pile by assigning the integer value of the card to the
players "playedCards" array's last position and incrementing the count of
the players played cards. Second: the card is removed from the array 
representing the players hand by setting the array element at the index of the
card to -1. Third: If the players hand is now empty or only contains one card
the game state is updated just by decrementing the count of the players hand.
If there are more than one cards remaining in the array representing the 
players hand then the last element of the array is moved into the position
that was just set to -1 and the count of the hand is decremented.

updateCoins() - First: reset the game states coin count to 0. Second: iterate
over the player's hand and increment the coin count appropriately for each
of the coins found in the hand. 1 for copper, 2 for silver and 3 for gold.
Third: increment the coin count with the bonus.
