Tanna Richardson
CS362 - Winter 2016
Assignment 4 Write-up


-------------------------------------------------------------------------------------------
	Test Development
-------------------------------------------------------------------------------------------

My random test development included the following steps:

1. Create a random game state
I wanted my random test to include as many variations of game state as possible without
bogging down the tests on invalid states. So rather than just filling the gamestate with
completely random numbers, I stepped through each element and selected a random value
out of a valid list of options as follows:
	numPlayers: 1 to 4
	supplyCount: 
		curse: 0 - 30
		victory: 0 - 12
		treasure: 0 - 40 
		kingdom: randomly chooses ten cards (adventurer - treasuremap) with 0 - 12
				 remaining cards = -1
	embargoTokens: 0 - 3 for each card used in game
	outpostPlayed: 0 or 1
	outpostTurn: 0
	whoseTurn: 0 to numPlayers-1
	phase: 0 or 1
	numActions: 0 - 3
	coins: 0 - 10
	numBuys: 0 - 3
	hand[player][position]: 0 - treasure map for each position up to handCount
	handCount[player]: 0 - MAX_DECK
	deck[player][position]: 0 - treasure map for each position up to deckCount
	deckCount[player]: 0 - MAX_DECK
	discard[player][position]: 0 - treasure map for each position up to discardCount
	discardCount[player]: 0 - MAX_DECK
	playedCards[position]: 0 - treasure map for each position up to playedCardCount
	playedCardCount: 0 - MAX_DECK

2. Create a random seed
I had some issues figuring out the random seed. I used a printGameState function to 
confirm each of the random games being created and at first I was not getting variation
from one game to the next or one test run to the next. To resolve this, I started with
a random seed number between 0 and 3, then incremented the seed each time the test loop
runs. This ensures that every loop of the test is different and the starting point each
time you run the test suite is randomly selected.

3. Create a test loop
I created a loop to run the tests over and over until a constant NUM_TESTS was reached.
I then ran the test suite a few times checking different numbers for NUM_TESTS. In the end,
I decided to go with 100,000 runs for adventurer and 50,000 runs for village. This was 
based on the time it took to run the tests and this size of the output file. In a real
test environment, these numbers could easily be adjusted to run longer.

4. Check pre-conditions
Before testing, I confirmed that the random game setup met any preconditions necessary
to run the tests. For both adventurer and village, the test card needed to be in the
players hand so it could be played. I looped through the player's hand to find the 
correct card position, or if the card was not there I added it in position 0. For 
adventurer, it was also necessary to have 2 treasure cards in the players deck or
discard. I looped through both deck and discard and if there was not a total of 2
treasure cards, the test was aborted. According to Dominion rules, adventurer works
when there are 0 or 1 treasure cards as well, but a bug in the current code creates
and infinite loop in this situation. When the bug is fixed, this check can be removed.

5. Copy game state and execute card
Once all of the setup is complete, I made a copy of the game state and executed the
test card using cardEffect().

6. Check all values against expected results
This step was the same as for assignment 3. I went through each of the game state 
values comparing the actual results with expected results and printing errors where
appropriate.

7. Collect summary info and print
While I was running the test loops, I tracked where failures occured during step 6.
At the end of the test I printed a summary of tests passed, failed, and aborted, and
total number of errors for each condition check. This information was helpful to get a
high-level view of what errors were occuring, those that occured every time the test
ran, and those that occured only periodically. It did not, however, provide enough 
information for periodic bugs to determine when bugs are occurring. To really debug, 
the random game state needs to be printed so you can see what cards are in the test and 
what exactly is changing. This could be manually added when errors are found or could be 
incorporated as a test option (because it would make the test results huge and time 
consuming to weed through).

Here is the summary results for both random tests:

	-----------------------------------------------------------
		Summary for Random Tests: Adventurer Card
	-----------------------------------------------------------
	Test Summary:
	Passed: 0
	Failed: 49959
	Aborted: 41

	Error Summary:
	[0] Invalid cardEffect return value: 0
	[1] Game state changed: 0
	[2] Other player's discard changed: 10521
	[3] Other player's deck changed: 0
	[4] Other player's hand changed: 13045
	[5] Coin bonus changed: 0
	[6] Adventurer not moved to played pile: 49959
	[7] Player's hand not changed correctly (+2 treasure, -1 adventurer): 49959
	[8] Treasure cards not removed from player's deck/discard: 0
	[9] Player's full deck count changed: 530581

	-----------------------------------------------------------
		Summary for Random Tests: Village Card
	-----------------------------------------------------------
	Test Summary:
	Passed: 96007
	Failed: 3993
	Aborted: 0

	Error Summary:
	[0] Invalid cardEffect return value: 0
	[1] Game state changed: 0
	[2] Other player's discard changed: 0
	[3] Other player's deck changed: 0
	[4] Other player's hand changed: 0
	[5] Coin bonus changed: 0
	[6] Village not moved to played pile: 197
	[7] Actions not changed correctly (+2): 0
	[8] Player's hand not changed correctly (+1 card, -1 village): 3993
	[9] Drawn card not removed from player's deck/discard: 0
	[10] Player's full deck count changed: 394

From the summary, you can see that the adventurer card is not being moved to the played
pile every time it runs (this is clearly a bug). Also multiple cards in the player's
full deck count are being changed. It is difficult to tell from the summary if this
happens every time, but based on the very large number it appears to. Finally, in some 
cases other player's cards are being affected.

The village card was much more successful (because it didn't have bugs purposefully 
introduced). It passed 96,007 times out of the 100,000 tests. Occassionally the village
card was not moved to the played pile and the player's hand did not change as expected. One
possible reason for the hand not changing is that the card drawn could also be a village card
so the hand after looks exactly the same as the hand before, even though it did actually go
through the steps of playing the village card and drawing a new one. I would need to examine
the individual test case and cards used to see if this is a false positive or a real bug.


-------------------------------------------------------------------------------------------
	Checking Correctness
-------------------------------------------------------------------------------------------

I checked for correctness of my specification in three ways:

1. Before I implemented the actual test loop, I tested just the random game creator to 
ensure it was creating valid and random game states. I did this by creating 5 games and 
printing out the complete game state. At first, I found that all 5 games that were created
were exactly the same because I wasn't changing the seed. I added a parameter to the 
randomGame() function to pass in a seed and I incremented the value that I passed in each
time. This provided the needed variation from game to game. Upon further executions, I
noticed that the games were exactly the same each time I ran the program so I randomized
the starting seed as well. In addition to making sure the games were different, I checked
that each gamestate was valid according to the definitions of the game. I used the
initializeGame() function in dominion.c to aid in selecting the max number of cards 
typically included in a game.

2. I researched Dominion rules online and made sure that I understood how the gamestate
should be changed after the card was executed. For adventurer, this led to the following 
requirements:
- Reveal cards in deck until 2 treasure cards are revealed
- If you reach end of deck and do not have 2 treasure cards, shuffle discard and deck 
    (do not include revealed cards)
- If you reach end of deck again, you get however many treasure cards were found (0 or 1)
    (this never occured in my tests because of infinite loop, I aborted if <2 treasure cards)
- Revealed treasure cards (2) are moved to hand
- Revealed non-treasure cards are moved to discard (at end; after any shuffles)
- Played card (adventurer) is moved to played pile (not discard)
- Everything else unchanged
For village, I found the following requirements:
- Increase actions by 2
- Draw card from deck and add to hand
- Played card (adventurer) is moved to played pile (not discard)
- Everything else unchanged
For both of these cards, I found a challenge with checking before/after states because
I did not "stack the deck" like I did for assignment 3. It was possible for the deck
and discard to be combined and shuffled during card execution. Therefore, I based my
tests for the after state on the full deck counts. All of the same cards should be in 
the players full deck, but they may have moved around between deck, discard, and hand. 
I also checked the contents of the hand (+2 treasures for adventurer, +1 new card for
village) and the count for deck/discard combined (-2 for adventurer, -1 for village).

3. I reviewed the dominion.c code to see what checks were performed and to confirm the
requirements in step 2. For example, the village code calls the drawCard() function. By
looking through this function, I could confirm that the discard/deck may be combined
for a shuffle and I confirmed that drawn cards come from the player's deck and go to
the player's hand. I primarily used the code commentsa as guidelines and tried to
understand the general purpose rather than looking at the detailed implementation, as
it may have bugs that I don't want to replicate in the test.


-------------------------------------------------------------------------------------------
	Coverage
-------------------------------------------------------------------------------------------

The individual coverage for my random tests are:

	Adventurer:
	Lines executed:14.06% of 562
	Branches executed:15.59% of 417
	Taken at least once:10.55% of 417
	Calls executed:7.37% of 95
	
	Village:
	Lines executed:13.52% of 562
	Branches executed:14.15% of 417
	Taken at least once:8.39% of 417
	Calls executed:6.32% of 95
	
The overall coverage for my test suite (assign 3 & 4) is:
    Lines executed:48.04% of 562 (up from 42.88%)
	Branches executed:55.40% of 417 (up from 51.56%)
	Taken at least once:39.33% of 417 (up from 34.05%)
	Calls executed:35.79% of 95 (up from 31.58%)

The improvement in coverage is primarily due to the fact that I tested a new card with
the random tests, village. The village card uses the discardCard() function which was
not covered by my previous test suite. Also because the tests this time were random and
there was a possiblity for shuffling, I used the function fullDeckCount() when checking
game states. This function also was not covered in my previous test suite.

----- Statement Coverage -----
Statement coverage was improved directly by exectuing the functions stated above. In
addition, the following un-executed lines are now executed by the test suite:

Lines 500-531: drawCard() shuffle empty deck
Using a random game state created instances where drawCard() was called with an empty
deck so these lines were executed. In my previous test suite, the deck was always stacked
with cards because I was not specifically testing drawCard().

Lines 1069 & 1073: discardCard() discard last or only card
The random game state created a few instances where the last card was discarded. It still
did not create a case where the hand contained only 1 card that was discarded. This would
most likely need to be added as an individual test.

Line 1156: runAdventurer() empty deck
The random game created instances where the deck was empty and line 1156, calling shuffle(),
needed to be executed.

----- Branch Coverage -----
Branch coverage was also improved from the previous test suite. In addition to improvements
based on the new function calls and statement coverage above, branch coverage also improved 
run Adventurer() as follows:

The true branch for "if (state->deckCount[currentPlayer] <1)" is now executed as explained 
above for line 1156. 

The silver and gold branches are now executed for 
"if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)". The previous test
suite used only copper cards. 

----- Boundary Coverage -----
Although it does not explicitly show up in gcov, boundary coverage was improved in the 
new test suite because a wider variety of inputs were tested. To truly test boundaries,
however, I need to add invalid game states to the mix.



