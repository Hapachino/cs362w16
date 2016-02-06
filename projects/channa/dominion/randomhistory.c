Nancy Chan
CS 362
Winter 2016
Assignment 4: randomhistory.c

Adding the random testers improved coverage in all aspects:

Assignment 3:
Aggregate coverage for all 8 test files:
Lines executed:37.04% of 575
Branches executed:47.96% of 417
Taken at least once:36.21% of 417
Calls executed:21.05% of 95

Assignment 4:
Aggregate coverage for all 10 test files:
Lines executed:41.57% of 575
Branches executed:48.92% of 417
Taken at least once:41.01% of 417
Calls executed:23.16% of 95

randomtestadventurer:

	I developed the random tester by creating a deck of 10 random cards, an empty discard pile,
	and a fixed hand of 5 cards. I then saved pre-test values to compare with post-test values.
	I calculated expected values for three scenarios: 1) no treasures in the deck, 2) one treasure
	in the deck, and 3) at least 2 treasures in the deck. I compared the expected values with the
	actual values in the changes to the deck, discard, and hand after playing the adventurer card. 
	
	In terms of coverage, for Assignment 3, I had not tested the behavior of adventurer in the case
	of an empty deck and so the shuffle line in the playAdventurer function had not been executed.
	Adding the random tester gave a more realistic assortment of cards which could result in an
	empty deck as the player may go through the entire deck in a deck containing no treasures.

	-: 1258:      //if the deck is empty we need to shuffle discard and add to deck
   20: 1259:      shuffle(currentPlayer, state);

   Effort to check the correctness of the specification:

   At least 2 treasures:

   Exactly 2 treasures:

   1 treasure:

   No treasures:

randomtestcard:

	I developed the random tester by 

	In terms of coverage, 

	Effort to check the correctness of the specification:

	Cost of gainCard > Cost of trashCard + 2:

	Cost of gainCard = Cost of trashCard + 2:

	Cost of gainCard < Cost of trashCard + 2:
