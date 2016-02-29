Samuel Ford
CS362-400, Winter 2016
Assignment 4

Creating Random Testers for Assignment 4
========================================

Adventurer Card
---------------
I originally implemented the function for generating the semi-random game state in a naive way, just to see how things would turn out.  This is to say, the game state would include 2-4 players, with 0-10 cards in each of their hands, decks, and discard piles, and some random cards in the playedCards pile (that aren't the played card).  The cards that were included in each of the players' hands, decks, and discard piles were chosen at random from the pool of valid cards.

The result of this initial implementation was that a third of the game states generated had zero treasure cards available between the current player's deck and discard pile.  This particular state can cause a crash on some platforms, so it's definitely a good state to test but we don't want it to be occurring quite so frequently.  I would be more comfortable with it occurring something like 15-20% of the time, so that we generate a greater number of valid game states that can potentially uncover *other* bugs.

However, that having been said, the naive approach always covered 100% of the playAdventurer function within 1000 iterations.  It may be that 100% coverage would still be achieved with fewer iterations but I planned to investigate that later.

Looking forward, I had a couple methods that I could try in an attempt to reduce the number of game states with no available treasure cards.  1) I could increase the potential number of cards generated for each player's decks and discard piles and/or 2) I could manipulate the choosing of cards in such a way that treasure cards are more likely to be chosen.

Increasing the potential number of cards generated for each player's deck and discard piles was a simple and quick modification, so I tried that first.  Generating 0-17 cards (rather than 0-10 cards) for each player's deck and discard piles led to about 18-20% of game states having no available treasure cards.  However, with a smaller number of iterations (10 rather than 1000), it ends up being more like 10-30%, so it may be better to try a different method if I have time.

I ended up reducing the number of iterations to 10 (from 1000) because this continued to achieve 100% coverage of playAdventurer() while keeping output and execution time to a minimum.  Under normal circumstances, a greater number of iterations wouldn't be a problem (if you're not printing or logging output) but I wanted to keep the randomtestadventurer.out file manageable here.

Overall, the random tester uncovered the same bugs as the handcrafted tests for Adventurer and did not uncover any new bugs.


Steward Card
------------
I decided to test a card that I hadn't tested before, so I chose steward (which is implemented in the cardEffect() function).  I started with the existing function from the Adventurer card random tester for generating a semi-random game state, though it would no doubt require *some* modification.

Once the semi-random game state is generated, the Steward random tester generates values for choice1 (the choice of Steward's available effects), choice2 (a card to trash), and choice3 (another card to trash).  If choice1 is 1 then the player should draw 2 cards from their deck.  If choice1 is 2, then the player should receive 2 coins.  If choice1 is something else, then the player will trash the choice2 and choice3 cards (which are integer values corresponding to indices of cards in the player's hand to trash).

The steward card seems simple to test on the surface but it ends up being a bit complex.  For example, when choice1 == 1, drawCard() will shuffle the player's discard pile into their deck if the deck is depleted, so you have to predict this to be able to make the correct assertions.  The most complexity comes from testing the case where choice1 isn't 1 or 2 (i.e. trash up to 2 cards).  The reason for this is that the steward card doesn't seem to make sure that:

1. choice2 and choice3 aren't the card being played
2. choice2 and choice3 aren't the same card in the hand
3. Trashing choice2 won't affect choice3
4. choice2 and choice3 are valid indices for the hand (i.e. not out of bounds)
5. There are enough cards in the hand to trash 2 cards (or fewer if there are less than 2 cards available)

With these potential issues in mind, I was curious if the random tester would end up bringing any of these bugs to light in *some* manner.  Without having done anything to specifically test for these potential bugs, some of them manifested as abnormalities in other test cases.  For example, if choice2 or choice3 was the card being played, then the test to make sure that the played card was added to the playedCards array would fail (since the card was erroneously trashed beforehand and the handPos index ends up pointing to some *other* card).

With that out of the way, I needed to add some tests to better uncover which of those potential issues actually become bugs in practice.  To do so, I had to modify the game state generation function to ensure that the cards in the player's hand are unique; this allows us to make sure that only intended cards are trashed (and not some other card).

In the end, I found the following bugs in the Steward card implementation:

1. Steward allows the player to trash the card being played (which it shouldn't).
2. Steward allows the player to attempt to trash the same card for choice2 and choice3 (which it shouldn't), leading to a card being trashed that wasn't intended to be trashed.
3. Steward doesn't account for any impact that trashing choice2 may have on the subsequent removal of choice3.  If choice3 is the last card in the hand, then choice3 will be moved to the choice2 index when choice2 is removed.  As a result, the choice3 index becomes stale and points to an index that is not only incorrect (i.e. not pointing to the card that was originally at the choice3 index) but also out of the bounds of the hand.  Since discardCard() doesn't do any bounds checking, the last card in the hand is moved to the out of bounds location and we effectively lose that card.
4. Similar to the previous bug, Steward doesn't account for the effect that trashing cards will have on handPos (i.e. the index of the played card).  If handPos is near the end of the hand, then it can get moved when discardCard() switches a card for the last card before decrementing the array count (to do an efficient removal when order doesn't matter).  As a result, handPos can end up pointing to a card that either isn't the card being played or isn't within the bounds of the hand when it comes time to discard the played card.
5. Steward doesn't allow the player to trash only one card when they only have one card available (NOT including the card being played).  [This can lead to a negative handCount in some cases but this problem partly lies with the discardCard() function.]

Steward doesn't do any bounds checking but I didn't configure the random tester to generate out of bounds values to specifically demonstrate this.  As mentioned above, we run into issues with accessing values that are out of bounds simply through normal testing.  However, due to how the game state is being generated, these issues won't crash the program.  These invalid indices are beyond the array's count but the hand/deck/discard/playedCards arrays are large enough that the out of bounds index is still within the array's allocated memory.  If one of those arrays was completely full and we ran into one of these out of bounds index issues at the end of the array then it could potentially crash the program but that seemed like a bit too much to test here; this is mostly a discardCard() issue, so I would save that sort of testing for that function.

In general, the Steward card appears to work properly when choice1 is 1 (+2 cards) or 2 (+2 coins) but it only works properly about 20% of the time for the third option (trash 2 cards in hand).  The implementation for the third choice1 option is a bit optimistic and doesn't account for potential issues that can arise.  Part of the issues that steward runs into result from using indices for handPos, choice2, and choice3; indices can become stale when modifications are made to the relevant array and this definitely plays out here.


Summary
-------
My original tests for the Adventurer card produced 100% coverage of the playAdventurer() function, so the random tester of the same card couldn't possibly improve the coverage of that function.  However, the random tester does improve the overall line coverage for the combined tests from 26.88% to 27.04% and "Taken at least once" from 19.18% to 19.42% because the compare() function gained more indirect coverage.

The random tester for the Adventurer card didn't find any bugs that I didn't already know about from the previous tests.  The random tester was actually working at a disadvantage compared to the handcrafted test cases because the use of shuffle() in playAdventurer() prevents us from being able to make certain types of assertions; in the test cases, we can establish a specific setup that we can reason about in concrete ways but the random tester produces a random gameState for each test.  I wrote some weaker assertions in an attempt to cover similar ground but the handcrafted tests make up for this shortcoming, at least.

The random tester for the Steward card ended up achieving 100% coverage of the steward case in the cardEffect() function with only 10 iterations.  No part of cardEffect() had been tested before, so cumulative coverage for all the tests (randomtestadventurer included) increased to 30.26% line coverage, 31.89% branch coverage, and 21.34% "Taken at least once" with the inclusion of randomtestcard.

In general, I changed the way that I was outputting assertion information between Assignment 3 and Assignment 4.  Assignment 3 used a style like "Should discard all other drawn cards", which obscured the underlying assertion information.  For assignment 4, I moved to an observed vs. expected style like "state.deckCount[0] = 7, expected = 7".  We lose the explanatory *purpose* of assertions with this setup but I left comments in the tester around the assertion to explain what should be occurring.  [I would normally go back and convert the older tests to this style but I won't for this class (unless given the opportunity).  Going back and editing those tests at this point might make it seem like I was working on Assignment 3 past the due date and I don't want to take that risk.]
