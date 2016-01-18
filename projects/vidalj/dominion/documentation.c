/*
Understanding of smithy:
Smithy seems to be a fairly basic case where a for loop is ran for 3 iterations where the drawCard()
function is call once each iteration.  Once the for loop is complete, discardCard() is called to remove the card 
from the players hand.

drawCard as part of Smithy will attempt to draw a card from the deck but if it detects that the deck is empty
it will add the discard pile back into the deck and reshuffle the deck so that cards can be drawn appropriatly


Understanding of adventurer:
This card will trigger cards to begin being drawn from the deck using drawCard().  If the deck is empty the
discard pile will be shuffled back into the deck and the the process will continue.  If a treasure
card is drawn (copper, silver, or gold) the drawntreasure variable will increment or if it is not a 
treasure card  it will be  put into a temphand array and when drawntreasure which begins at 0 increases
to 2 the process ends the temphand is discarded using a loop.



Understanding of discardCard():
First it checks if card is being trashed, if not then it marks its state as played.  Then if the card was last
in hand array it reduces array by one, if there was only one card in hand then it reduces array by one, otherwise
it replaces the removed card with the last card in the hand array, and then reduces the hand array by one.

Understanding of updateCoins():
This resets the coins that are available to the player to 0 and then  adds 1 coin for every copper, 2 coins for 
every silver, and 3 coins for every gold in the players hand plus any bonus that may be present.
*/