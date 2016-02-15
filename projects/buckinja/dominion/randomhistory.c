Janel Buckingham
CS 362 Winter 2016
Assignment 4


For testing adventurer, I first initialized the game in a more generic way than I had for unit tests.  Instead of 
initializing a 2 player game and "stacking the deck" so that I would know exactly the cards in the deck, hand, and
discards, I merely initialized a 2 player game this time and passed in an array of cards that would be in play.  

Once inside the testing function, the players are randomly assigned random decks (within the legal range of a deck size), 
3 coppers in their discards to avoid a potential bug where both the deck and discards are empty (not possible in legal game 
play), and the decks are shuffled.  Random hands (random hand size within legal hand size limits, and random content from the
cards in play, coins, and estate cards) are assigned to the players.  Then the state of the supply count and kingdom cards
is saved for future comparisons, and the amounts of cards in both players' hands, decks, and discards is recorded for 
comparisons later on.  In order to hit edge cases more frequently, the hand count is in the highest 50 possibilities half of the time, 
in the lowest 50 possibilities <40% of the time, and in the middle range >10% of the time.

I attempted to test the function with all range of deck sizes and hand sizes including empty and max number.  I also chose the cards randomly, 
although one improvement might be to forcibly limit the number of coins in the deck and hand to further stress the function.

Improvements in coverage:  My unit tests covered 100% of playAdventurer() in line coverage and branch coverage.  My random tester for 
adventurer was also able to the achieve 100% coverage, so there was no improvement because the max had already been reached, but coverage 
remained at max with the random tester.  

A new bug was discovered with the random tester for the adventurer card: After the random tester has been running for a few seconds, the 
second player's discard is altered, which shouldn't be possible.  In the cases I have seen, the discard holds a mid-to-high number (500-1500)
before calling playAdventurer(), and a low number of cards (3-20) afterward.  I have not been able to locate the bug.  playAdventurer() doesn't 
appear to increment player, or change discards in an unusual way that I can see.  Added to bugs1.c.  When this bug is encountered, I have it 
exiting with a code of 0 so that the gcov can run correctly and we can see the result of the line that caused the error before exiting.

Otherwise, all bugs in playAdventurer() have been previously reported in bugs1.c.


For testing smithy, I initialized the game more generically than with unit tests similar to the method used for testing adventurer.  A 2 
player game is initialized with the array of cards in play.  

Inside the random tester, the players are randomly assigned decks within the legal range of a deck size, random hands in the same manner they 
were assigned for testing adventurer, and 3 coppers are placed in the discards to ensure enough cards are in play in case a shuffle is needed.
Similarly, the state of the supply count, kingdom cards, and each player's hand count, discard count, and deck count are saved before calling
the playSmithy() function.  Since no additional bugs (beyond those that were found with unit testing) were found with the random tester, I let
the random tester run for a set number of loops so that it finishes within a few minutes.  Originally I had it run for several hours with no
found bugs, so I shorted the length of time for running gcov knowing that a longer run produces the same results.

I attempted to test the function with all range of deck sizes and hand sizes including empty and max number.

Improvements in coverage:  My unit tests covered 100% of playSmithy() in line coverage and branch coverage.  My random tester for 
smithy was also able to the achieve 100% coverage, so there was no improvement because the max had already been reached, but coverage 
remained at max with the random tester.  

