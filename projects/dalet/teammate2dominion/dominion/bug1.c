/*
Rishi Bhandarkar
CS 362 - bug1.c
*/

- scoreFor() Function
In the scoreFor() function, I noticed a bug where the scores of the players were not being calculated correctly after the game was first initialized.
I figured out it was this way because the for loop that is meant to calculate the points in each players' deck is accidentally limited by the cards
in the discard pile, not the cards in the deck. Since the game was just initialized, there are no discard cards so the for loop is never entered so none
of the points residing in the deck of each player is not counted.

- discardCard() Function
In the discardCard() function, there is a bug where the discard matrix and the discard count array are not being updated. When you discard a card, the 
hand and deck attributes are properly managed, but the discard matrix and disacrd count array are missing from the function. Whether the card is being discarded
from the middle, the end of the hand, or if it is the last card in the hand, these parameters need to be updated.

- Smithy Card
The Smithy card was one of the card functions that I altered in Week 2 with an intentional bug. The tester I build rightfully caught the bug I introduced,
and said that the Smithy was adding an incorrect number of cards to the players' hand. Other than that intentional bug, no other bug was found.

- Adventurer Card
The Adventurer card was another card function that I intentionally introduced a bug into in Week 2. In this case, the while loop was altered so that instead of
2 treasures getting added, it will add 3. My tester was able to identify this problem, but aside from that, the tester found no errors.

- Village Card
The Village card is another card that I introduced a bug into in Week 2. For this one, I changed the arithmetic to + 3 instead of + 2 when increasing the action
points for the user. This came through when I used my test on the Village card and the correct number of action points was not given.

- Council Room Card
The Council Room card is yet another card I altered in Week 2 to introduce a bug. In this case, I decremented the amount of buys the player gets instead 
of incrementing it, and the testing module was able to catch this error. Other than that, there is no other bug in the card.