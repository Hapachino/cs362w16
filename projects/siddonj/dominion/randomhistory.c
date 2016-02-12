NOTE:
I had to change line 1295 from the playAdventurer method.
The line I changed was the bug I introducted earlier, it was causing a segmentation
fault and without the fix I was unable to do any random testing on the method.

I changed:
  "if (cardDrawn != copper || cardDrawn == silver || cardDrawn == gold)"

To:
  "if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)"


** randomtestadventurer **
Developing my random test adventurer occured over multiple iterations.
First I began by randomizing more basic player state attributes like: coins,
number of buys, number of actions, number of players. These tests resulted in:
  - playAdventurer():
    100% block coverage, 93% statement coverage
    The missing statement of execution was under the condition of the Players
    deck being empty.
  - dominion.c
    Lines executed:21.20% of 566
    Branches executed:19.09% of 419
    Taken at least once:16.23% of 419
    Calls executed:9.38% of 96

Since the statement coverage in the playAdventurer method wan't perfect I
added some additional random value generators that would target the 0 Cards
in players deck condition. I added methods to randomize the: current player,
players deck, players hand, players discard pile, as well as types of cards
in each. These changes resulted in:
  - playAdventurer():
    Assignment 3 - 100% block coverage, 100% statement coverage
    Assignment 4 - 100% block coverage, 100% statement coverage
  - dominion.c
    Lines executed:24.20% of 566
    Branches executed:20.05% of 419
    Taken at least once:18.62% of 419
    Calls executed:11.46% of 96

The addition of 4 simple randomization methods increased all of my code coverage
metrics across the dominion.c file, meaning one test function was covering more
program code.

While my assignment 3 and 4 playAdventurer() method coverage was the same, the random
tests implemented in assignment 4 tested edge case branches more throughly than non-random tests.
For example the call to the "shuffle()" method if the player doesn't have any Cards
in their deck was called 216 time with the random tests compared to 1 in non-random tests.
This give me more assurance that the conditional is working with with various players and
other attributes in the state aren't preventing the shuffle from happening.

While checking specification of adventurer I realized that they player only gets to draw one card
if they were only able to reveal one treasure card from their deck, and discard pile (after shuffling
it into their deck). To meet this condition I created a test that counts the total
treasure count in the deck and discard piles then if that count is < 1, it checks to see
if the player only added 1 card to their hand.


** randomtestcard **
The other card I developed a random tester for was the smithy card. Smithy has
a simpler function than adventurer but I was still able to improve my initial random
testor coverage results by implementing more player randomization like I had built
in the adventurer method. My initial coverage results were:
  - playSmithy():
    100% block coverage, 100% statement coverage
  - dominion.c
    Lines executed:22.61% of 566
    Branches executed:18.14% of 419
    Taken at least once:15.99% of 419
    Calls executed:10.42% of 96

Adding the player randomization yeilded the following coverage results:
  - playSmithy():
    100% block coverage, 100% statement coverage
  - dominion.c
    Lines executed:22.61% of 566
    Branches executed:19.09% of 419
    Taken at least once:16.23% of 419
    Calls executed:10.42% of 96

While this didn't increase the total dominion lines executed it did improve
my branch execution by 1 percent. This change had no effect on the line or branch
execution for playSmithy();

While reviewing the smithy specification I realized I was missing a case to test which
was the player having less than 3 cards in their deck and discard combined. This would
cause the player to only draw all of the cards available instead of the normal 3.
I added tests to check for hand size increasing based on this condition as well as
decksize increasing. These changes didn't change my playSmithy() or dominion test
coverage results but did change tests that were failing in my general test output
to passing, since I now knew that this condition would cause the player to draw
less than they should.
