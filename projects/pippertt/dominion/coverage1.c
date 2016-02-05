/**
Author: Thomas "Adam" Pippert
Due Date: 2-February-2016
File: coverage1.c
Purpose: Discuss coverage for four unit tests, four card tests, and
overall coverage of dominion.c.
**/

/*

COVERAGE, TOTAL AMOUNT OF DOMINION.C
File 'dominion.c'
  Lines Executed: 29.88% of 576
  Branches Executed: 30.46% of 417
  Taken at Least Once: 23.26% of 417
  Calls Executed: 24.21% of 95

Analysis: At first glance 29.88% of line coverage and 30.46% of branch coverage doesn't appear to be sufficient. However, there are a significant number of functions that we were not asked to test.  Since we only tested four functions and four cards, and many of those tests were created using a limited number of arbitrary decks or hands to ensure consistency, it does seem reasonable that there was only roughly 30% coverage.  A good number of lines in the total program are implementations of specific cards and scenarios.  With that taken into consideration, the coverage in the 30% range begins to indicate that, though not enough to test the entire game, the tests that I did create were producing decent coverage. Line and branch coverage percentages being so close seems to be an indicator that I was doing a good job of covering user choices.

Though we did discuss "coverage for the sake of coverage" as being a dangerous precedence in testing, it is important to note that I could have included more coverage of complex functions to increase these percentages.  Also, given more time to develop tests, and having sufficient practice at creating tests, boundary testing in a future test suite may help achieve a more broad coverage pattern.

Most of the tests I ran achieved 100% line coverage and 100% branch coverage of their particular functions in dominion.c, and I achieved overall dominion.c coverage in the 20% range. The two tests that did not 
(adventurerCard and discardCard) were still in the 90% range for both line and branch coverage. Certainly if given more time to create a more comprehensive test suite, I could increase test quality for these as well. 



******-----------
UNIT TEST COVERAGE, FOUR UNIT TESTS:

Function 'updateCoins'
Function Results:
  Lines Executed: 100.00% of 11
  Branches Executed: 100.00% of 8
  Taken at Least Once: 100.00% of 8


Analysis: To start testing updateCoins, I walked through each line of code in the function and attempted to create a test that tested the purpose of the statement, as well as took into account what would happen if there was incorrect input. By doing this I achieved 100% line covereage, and 100% branch coverage. Overall, though coverage for the sake of coverage is not desired, this indicates a thorough spread of tests. If I  were to go back and improve upon the tests, I would look more in depth at boundary testing, perhaps stressing the bonus section. For the purpose of these tests, I kept all input within the expected domain.  Perhaps, in amore rigorous test suite, I'd test a wider domain for security or othe reasons.


****************

Function 'isGameOver'
Function Results:
  Lines Executed: 100.00% of 10
  Branches Executed: 100.00% of 8
  Taken at Least Once: 100.00% of 8


Analysis: I approached this from the standpoint of defining invalid and valid game states.  First, by simply going through the code and ensuring that the intent of each statement matched its output,  I managed to create 100% statement coverage. There were very few branches to take, so I simply made sure that I took each branch at least once. Thus, 100% branch coverage. I also decided to test the impact of the function on supply counts that were not supposed to be impacted by merely changing the game over status, to ensure that they were not changed unintentionally. This may or may not have been necessary in hindsight.  I also made sure that the game did not prematurely end at a lower card count or with non-empty piles. More thorough coverage could have been achieved by testing each pile individually instead of arbitrarily grouping these piles into a single test.


****************

Function 'discardCard'
Function Results:
  Lines Executed: 92.31% of 13
  Branches Executed: 100.00% of 6
  Taken at Least Once: 83.33% of 6

Analysis: This is the test I didn't get 100% coverage in, but did get 100% branch coverage.  I think this is because I specifically discarded the a specific card, and then checked that said card was removed from the hand. This did not specifically check the hand count, but served the same purpose.  I did check the full deck in addition to just a single card.  I think the testing was very good, even if it did not quite do both branch and line coverage at 100%.

****************

Function 'gainCard'
Function Results:
  Lines Executed: 100.00% of 13
  Branches Executed: 100.00% of 6
  Taken at Least Once: 100.00% of 6
  Calls Executed: 100.00% of 1

Analysis: I achieved 100% line and branch coverage. While this alone is not an indicator of a good test suite, I believe I covered logical bases as well as boundary cases. I tested for a player attempting to gain a card that was at supply count 0, a player attempting to gain a card that was not in the game, and a valid card. I then tested each available flag, and made sure that gaining the card resulted in no unintended effects for the opponent or for the game state. Then, I tested for card location (hand, deck, discard).


****************

CARD TEST COVERAGE, FOUR CARDS:

Function 'stewardCard'
Function Results:
  Lines Executed: 100.00% of 10
  Branches Executed: 100.00% of 4
  Taken at Least Once: 100.00% of 4
  Calls Executed: 100.00% of 5

Analysis: I achieved 100% line and 100% branch coverage, and I believe that in this case the coverage
tool is a good indicator of the test suite. I tested all three available options for the choice1 flag,
and for each of the options I made sure that the stated impact occured, and that no gains were made to the
other player or the valid world state.  Additionally, I made sure that no unintended gains or losses occured
for the player during these choices. When I tested the "else" for choice1, I also made sure that the trash
flag was tested, so it wasn't simply reducing the handCount and not being appropriately trashed. Due to
this I believe that I had a good test suite  and coverage, though more work could perhaps go into boundary
testing. An example would be what would happen if the player had less than two cards in their deck and
opted for the choice to discard.

****************

Function 'villageCard'
Function Results:
  Lines Executed: 100.00% of 5
  No Branches
  Calls Executed: 100.00% of 2


Analysis: Village has no branches, so it was very easy to cover.  I tested for unexpected losses or gains in supply cards for player and opponent, and checked game state. I tested gaining the appropriate amount of cards and the appropriate amount of actions, and made sure no other changes occured.  I also ensured the played
card was put back into the appropriate pile after use.  Boundary case analysis was nearly impossible for this card. In future testing, this card could possibly receive only a generic test if one was created that could cover almost every card type.

****************

Function 'smithyCard'
Function Results:
  Lines Executed: 100.00% of 5
  Branches Executed: 100.00% of 2
  Taken at Least Once: 100.00% of 2
  Calls Executed: 100.00% of 2


Analysis: Smithy was pretty easy to integrate into the test suite. I achieved 100% line coverage and 100% branch coverage because it's small and only has 2 branches.  In fact, in this case I might have gone overkill with game state and some other tests to cover accidental state changes elsewhere.  In the future, instead of writing these kinds of things into individual function tests, I could have an overall test that runs automatically on any function which should not change the game state, and leave that test out explicitly on functions which do make state changes.  This would reduce the code complexity of the test suite, and make it much easier to write.

****************

Function 'adventurerCard'
Function Results:
  Lines Executed: 81.25% of 16
  Branches Executed: 100.00% of 12
  Taken at Least Once: 83.33% of 12
  Calls Executed: 50.00% of 2


Analysis: Note 100% branch coverage, but not 100% line coverage.  I forgot to test this function:

while(drawntreasure<2){
        if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
               shuffle(currentPlayer, state);
        }

In looking at these results, I'm still fairly happy with my overall test suite. The lines within the adventurer card itself that stated an output or expected an input were tested, as well as any unintended game state consequences. It does indicate an area for test suite improvement, as an empty deck would indicate a boundary case I should account for.


****************
Coverage of other functions:

Function 'compare'
  Lines Executed: 83.33% of 6
  Branches Executed: 100.00% of 4
  Taken at Least Once: 75.00% of 4
  No Calls

Function 'supplyCount'
  Lines Executed: 100.00% of 2
  No Branches
  No Calls

Function 'fullDeckCount'
  Lines Executed: 0.00% of 9
  Branches Executed: 0.00% of 12
  Taken at Least Once: 0.00% of 12
  No Calls

Function 'whoseTurn'
  Lines Executed: 100.00% of 2
  No Branches
  No Calls

Function 'handCard'
  Lines Executed: 0.00% of 3
  No Branches
  Calls Executed: 0.00% of 1

Function 'numHandCards'
  Lines Executed: 0.00% of 2
  No Branches
  Calls Executed: 0.00% of 1

Function 'isGameOver'
  Lines Executed: 100.00% of 10
  Branches Executed: 100.00% of 8
  Taken at Least Once: 100.00% of 8
  No Calls

Function 'scoreFor'
  Lines Executed: 0.00% of 24
  Branches Executed: 0.00% of 42
  Taken at Least Once: 0.00% of 42
  Calls Executed: 0.00% of 3

Function 'getWinners'
  Lines Executed: 0.00% of 24
  Branches Executed: 0.00% of 22
  Taken at Least Once: 0.00% of 22
  Calls Executed: 0.00% of 2

Function 'getCost'
  Lines Executed: 0.00% of 30
  Branches Executed: 0.00% of 28
  Taken at Least Once: 0.00% of 28
  No Calls

Function 'shuffle'
  Lines Executed: 93.75% of 16
  Branches Executed: 100.00% of 8
  Taken at Least Once: 87.50% of 8
  Calls Executed: 100.00% of 2

Function 'drawCard'
  Lines Executed: 36.00% of 25
  Branches Executed: 33.33% of 6
  Taken at Least Once: 16.67% of 6
  Calls Executed: 0.00% of 1

Function 'endTurn'
  Lines Executed: 0.00% of 20
  Branches Executed: 0.00% of 6
  Taken at Least Once: 0.00% of 6
  Calls Executed: 0.00% of 3

Function 'cardEffect'
  Lines Executed: 11.82% of 203
  Branches Executed: 16.98% of 159
  Taken at Least Once: 5.66% of 159
  Calls Executed: 18.87% of 53

Function 'playCard'
  Lines Executed: 0.00% of 14
  Branches Executed: 0.00% of 10
  Taken at Least Once: 0.00% of 10
  Calls Executed: 0.00% of 3

Function 'initializeGame'
  Lines Executed: 83.87% of 62
  Branches Executed: 95.65% of 46
  Taken at Least Once: 80.43% of 46
  Calls Executed: 100.00% of 5

Function 'kingdomCards'
  Lines Executed: 0.00% of 13
  No Branches
  No Calls

Function 'newGame'
  Lines Executed: 0.00% of 3
  No Branches
  No Calls

*/
