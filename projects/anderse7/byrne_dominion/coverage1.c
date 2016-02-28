//Michael Byrne
//byrnemi@onid
//Assignment 3
//CS 362
//2-1-2016




//------- Unit Test Coverage Analysis -----------------------------------------------------------//

/*/
Lines executed:20.34% of 580
Branches executed:22.54% of 417
Taken at least once:18.94% of 417
Calls executed:7.45% of 94

For the unit tests alone, not including card tests, the four test covered just over 20 percent of the code.
For four functions in a large file with some isolated paths, this seems to be reasonable coverage. Skipped branches
are where they would be anticipated, e.g. within large sections of code related to untested gameplay logic, such as within
the playCard and getWinner functions. Examining the gcov output revealed that coverage was near total for functions
that are dependencies of the code under test.

More specifically:
    BRANCH: The number of branches explored by four unit tests is in line with the total statement coverage.
    Examining the gcov output revealed the following:
        branch 26 taken 0%
        branch 27 taken 0%
    As one of the functions tested is the getCost function, this means that my unit test was missing two
    cards. This isn't catastrophic, but it does leave a corner untested. Both tests of isgameover and
    updateCoins revealed almost complete branch coverage. Function handCard was 100 percent covered.

    BOUNDARY: Significant effort was made at testing boundary conditions. As this test suite is based
    on random testing, either complete ranges of possible values were used, or "reasonable" ranges were
    used. For example, I did not test up to the maximum allowed cards in a hand.

/*/

//------- All Test Coverage Analysis -----------------------------------------------------------//

/*/
Lines executed:37.44% of 577
Branches executed:40.53% of 417
Taken at least once:31.89% of 417
Calls executed:24.47% of 94

The total coverage for all eight tests was a little disappointing given the apparent increase for the four
new tests. I suppose some of that can be attributed to redundancy; that is, as more and more functions
are executed as a proportion of total, the less new ground is going to be covered.

Nonetheless, a function by function break down using gcov offers 100 percent coverage from the two cards
tested that had been refactored as discrete functions.

Function 'playAdventurer'
Lines executed:100.00% of 13
Branches executed:100.00% of 10
Taken at least once:100.00% of 10
Calls executed:100.00% of 1

Function 'playSmithy'
Lines executed:100.00% of 6
Branches executed:100.00% of 2
Taken at least once:100.00% of 2
Calls executed:100.00% of 2

Specifically:
    BRANCH: Branch coverage increased in proportion to the branch vs. line coverage statistics of the function
    test portion of the the test suite. This is about as expected. In manual inspection of the gcov output,
    I was unable to find a function that had been called by my test suite that had uninspected branches.

    BOUNDARY: Boundary cover had the same limitations in the full suite as in the function-only portion. For
    convenience, and because it seemed reasonable, card/discard/deck sizes were limited to 50 cards each.
    Where applicable, decks of 0 cards were tested. In every case, random ranges represented to the true
    ranges found within the game.




