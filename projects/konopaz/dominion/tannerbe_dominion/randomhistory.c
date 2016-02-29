My first goal was to develop a function that would produce a random game state newRandomGame(). I put this in dominion.c. 
This function attempts to make a totally random game state, but tries to lean towards realistic game states. 
Only 1% of the time does it test extreme cases (large handCount, deckCount, etc.)
Picking the kingdom cards is handled by the randomtestadventurer and randomtestcard so that they can ensure the card being tested exists in the game.
Since the system clock is used to seed the RNG, I selected a different stream with every test so that tests are duplicated by the RND producing the same values.

The actual tests are very similar to those done in the unittest assignment, but have been refactored to print an error when it is detected instead of using assert. 
If assert was used, the random tester would crash every time an error was found.

To see how my tests improved covered of dominion.c compared to my unittests, I first ran my original card tests from assignment 3 and found coverage information. 
Then I ran my random test and found coverage information again. This can be found in dominion.c.gcov.cardtest2 and dominion.c.gcov.cardtest4 (text files)

My coverage for the embargo card was already 100%, but coverage overall in dominion.c improved by about 50%. This improved covereage was from the compare function (83%-->100%),
the initialize game function (82%-->94%), the drawcard function (38%-->92%), and the discard card function (67%-->78%).

My coverage for the adventurer card improved slightly (from 93% to 100%) because now the deck was not empty for every test and the if block for shuffling the deck 
when that is true could fallthrough. Similiar gains in coverage overall in dominion.c were also seen because of the newRandomGame() function.

Note: make sure to do Make clean between executing make randomtestcard.out and make randomtestadventurer.out in order to see difference in coverage between random test and unit test.