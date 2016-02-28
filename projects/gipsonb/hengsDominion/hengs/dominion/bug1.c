Stephen Heng
CS 362 winter 2016
Assignment 3: bug1.c

Unit Tests:

1. unittest1: initializeGame()
No bugs discovered for initializeGam() function. All tests that I ran passed. Which consisted of
supply count and player state in the game.

2. unittest2: updateCoins()
No bugs discovered. Covered the tests for coin update of gold, silver, copper, and mixed coins.

3. unittest3: isGameOver()
No bugs discovered. I ran test on different states of the game. One is the initial start of the game,
the other was exhausting the supply of province and also exhausting the supply of 1, 2, and/or 3
supply count cards. These tests passed.

4. unittest4: getCost()
No bugs found when returning the correct value of each dominion card.

Card Tests:

1. cardtest1: smithy()
Yes, there was a bug found in the smithy() function that gives the player 3 extra cards.
Besides the bugs that I introduced earlier, I found that the card was not being added
to the discard pile to the player after it was played. This could be in relation to the 
discard function instead. My test showed the card was not discarded when checked against
the expected initial state.

2. cardtest2: adventurer()
Yes, there was a bug in the adventurer card function. Besides the discard pile not being
counted properly when played, my tests revealed that treasure cards were not being kept
in the players hand as indicated. It showed one less card in the hand. The discard pile, hand count,
and deck count are also incorrect. I could be that the discarded card was not placed by in either pile but
just taken away from the game. When I also ran to see if the coins added up correctly in the 
players hand, it showed up as being less than the original state. 

3. cardtest3: village()
Yes, there is a bug in the village card. It did not properly increment an additional action to the player.
My tests revealed that it only gave 1 additional action instead of the two required.

4. cardtest4: council_room()
No bugs detected. The hand count, additional buys, and additional card added up exactly.