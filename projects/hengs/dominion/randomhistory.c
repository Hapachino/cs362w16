Stephen Heng
CS 362, Winter '16
Assignment 4 randomhistory.c


1. randomtestadventurer.c

File 'randomtestadventurer.c'
Lines executed:98.63% of 73
Branches executed:100.00% of 48
Taken at least once:97.92% of 48
Calls executed:96.55% of 29
randomtestadventurer.c:creating 'randomtestadventurer.c.gcov'

For the randomtestadventurer.c program, I created a random tester to test the adventure card. In the random test,
I implemented a randomizer to initialize the game for a different seed everytime it is played. I also created
a randomizer for the player. Afterwards, I used the floor function as seen on the professor's bettertestdraw.c
program to create a random number of deck count, discard count, and hand count for each game. I also randomized
which cards will be placed in each deck, discard, and hand pile. Afterwards, i create a copy of the game state
and utilize the adventurer card to see the results of the coverage. I noticed that the coverage is high for the
tester. However, there might be some bugs in the adventurer card or the initilization of the game because 
certain seeds will not initialize the game as it return the same state as before the game started. There are some
checks that I left out for the adventurer card such as if there is no two treasure cards in the deck which 
would result in an empty deck and unfulfilled amount of treasure cards in the hand. Also, I add the card
automatically in the first hand without checking to see if the card is already placed in the hand. As with my
previous test, certain statements are not hit or hit half of the time due to if statements that are not triggered.


2. randomtestcard.c

File 'randomtestcard.c'
Lines executed:97.87% of 47
Branches executed:100.00% of 14
Taken at least once:92.86% of 14
Calls executed:96.15% of 26
randomtestcard.c:creating 'randomtestcard.c.gcov'

For the randomtestcard.c program, I applied the same random testing as the above tester. I used the floor function
to create a randomized count and fill the piles with random cards. The coverage for branches is 100% and many of
the lines are executed. As with the adventurer card, the smithy tester triggers the if statements so about half
of the statements are not runned if they don't fit the criteria. I believe there is one bug in the smithy function.
It is either that the card is not removing the used smithy card to the discard pile count.