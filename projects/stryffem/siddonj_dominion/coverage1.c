Statement, branch, boundary

Total coverage of dominion.c: 36.22%
Lines executed:36.54% of 583
Branches executed:32.94% of 419
Taken at least once:26.25% of 419
Calls executed:25.00% of 96

-- UNIT TESTS --

initilizeGame()
Statement Coverage: My statement coverage within the initializeGame method is very good. I am only missing
one statement from executing. It is a statement that checks to see if the
game is being initialized with two piles of the same kingdom cards. In future tests
I will need to add an initialization statement so a game is created with the duplicates.
I am also missing coverage of a statement that check is the players shuffle was successful so I will need to
add a condition that will trigger this statement.
Branch Coverage:
My branch coverage for most statements seemed to be fair. I should improve by setting duplicate kingdom cards
again. I had 100% fallthrough in that portion of the code (jumping of the conditional) and again when the
shuffle call failed.

buyCard()
Statement Coverage: I had good statement coverage of this method. The only statements that didn't get
tested were statements associated with the "DEBUG" flag.
Branch Coverage:
My branch coverage was also very good. I never took any debug branches so these reported as '0'
but since I wasn't testing the debug statements I think this was ok.
Block Coverage:
I had 93% of the blocks get covered and again the blocks that were missed were the debug blocks.

updateCoins()
Statement Coverage: Each statement in this method was executed at least 5 times when running my test suite.
Branch Coverage: Branch coverage was also 100% when running my tests.
Block Coverage: I had 100% block coverage for the updateCoins() method.

drawCard()
Statement Coverage: I had 100% statement coverage with my tests. I do have some lines in my code that are
only being executed 1 or 2 times. These lines handle the case when a players deck is empty. I think it
would be a good idea to continue to develop tests that would exercise these functions.
Branch Coverage: My branch coverage was balanced, but lacking for cases where the players
deck was empty.
Block Coverage: I had 100% block coverage for the drawCard() method.


-- CARD TESTS --

playSmithy()
Statement Coverage: I had 100% statement coverage with my tests.
Branch Coverage: I had good branch coverage but there also wasn't any real logic branches in the code to take.
Bugs I found indicated additional branches need to be implemented to make sure this function
completes the correct behavior (makes sure player has an action to play the card, etc.).
Block Coverage: I had 100% block coverage for the drawSmithy() method. The problem with my play smithy tests
are the function it self is only being executed one time, this number needs to be increased.

playAdventurer()
Statement Coverage: I had 100% statement coverage with my tests.
Branch Coverage: My branch coverage was well balanced between conditions that can cause 'trickyness' when Playing
the adventurer card, like no cards in deck or only one treasure in the library.
Block Coverage: I had 100% block coverage for the playAdventurer() method and it was called 4 times.

playRemodel()
Statement Coverage: I missed some statements towards the end of my function. The statements that aren't being exercised
are being skipped from the bug I introducted in the first portion of this assignment (at the beginning of the function).
I am setting a variable 'j' to be the card the player wants to trash, which causes the card to get discarded
instead of trashed.
Branch Coverage: My branch coverage was balanced except for the the branch that would discard a card based on the users
choice, as noted above in my statement coverage.
Block Coverage: I had 86% block coverage for the playRemodel() method.

playVillage()
Statement Coverage: I had 100% statement coverage with my tests.
Branch Coverage: I covered all branches. Within  this method there were no branches to branch on though.
The lack of checks in the function was made apparent during testing, it didn't behave as expected when
players decks were empty, etc.
Block Coverage: I had 100% block coverage for the playVillage() method.
