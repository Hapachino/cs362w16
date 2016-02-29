

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
