Scott Williams
CS 362 - ASSIGNMENT 4
Random Testing
Due Date: 2/14/2016

Aggregate Tests Totals for Tests:
Original 8 Tests:

Lines executed: 86.23%
Branches executed: 96.34%
Taken at least once: 60.39%
Calls executed: 68.38%

Original 10 Tests:
Lines executed: 86.38%
Branches executed: 97.07%
Taken at least once: 60.88%
Calls executed: 69.83%

Adventurer Tests:

---- Assignment 3 ----

Lines executed:88.06% of 67
Branches executed:84.62% of 26
Taken at least once:69.23% of 26
Calls executed:92.31% of 26
cardTest1.c:creating 'cardTest1.c.gcov'

---- Assignment 4 ----
Lines executed:79.35% of 92
Branches executed:100.00% of 70
Taken at least once:68.57% of 70
Calls executed:60.53% of 38
randomTestAdventurer.c:creating 'randomTestAdventurer.c.gcov'


Village Tests:

---- Assignment 3 ----

Lines executed:73.17% of 41
Branches executed:100.00% of 20
Taken at least once:55.00% of 20
Calls executed:50.00% of 24
cardTest3.c:creating 'cardTest3.c.gcov'

---- Assignment 4 ----
Lines executed:85.92% of 71
Branches executed:100.00% of 14
Taken at least once:57.14% of 14
Calls executed:90.70% of 43
randomTestCard.c:creating 'randomTestCard.c.gcov'


randomTestAdventurer:

		My first tests included a lot of random testing, so I was able to use a lot of the code that I had already used.
		I also had randomized treasure draws for the first time, whereas I let the cards in the player's deck
        and hand determine whether or not certain parameters were met. I probably had less line coverage due to this.
        However, with full branch coverage, we probably have a slightly more comprehensive test.

        The biggest difference between the previous version of my test and the current version is the scale. I initially only had 20 tests, but with the new additions, I have
        closer to 1000. This could account for some of the difference in call coverage as well, as call coverage was 92.31% in the original test and only 60.53% in the current test.

        This testing suite was also set up with a seed (29365) so that some tests would succeed and others fail. The tests only failed when the player drew
        two or fewer treasure cards, which would result in the deck being reshuffled excessively and other conditions not being met. Given that this happened
        approximately 80% of the time, it gives us a reasonable expectation that there was a bug in the drawn treasure check within the adventurer card itself.

        Other issues do seem to appear as well if there are multiple treasure cards drawn, which were then discarded. This should not happen either, and it is
        probably a side effect of the implemented bugs from my original versions of the files.


Village Tests:

        My original card tests were reasonably thorough and random testing improved this further. The tests were much smaller scale; however, and there were only 14 branches versus 20 in the new
        update. I reviewed my original tests and trimmed the branches to focus primarily on the area where bugs might have been. The other player's play was also added into the suite, and I found
        that this error tends to grow over time, between both players, especially if endTurn is used, in particular if both cards are not discarded properly.

        The improvement in coverage means we are also more likely to find the bugs. Both versions of the test suit had 100% branch execution, which is good, but with an increase in proportional line execution
        we can also further isolate the bugs. And as 90.70% of all calls are now being executed with nearly twice the number, we are getting closer to an ideal test suite. There are still areas and scenarios
        that probably were not considered in this version of the test. However, the village bug is fairly simple and card discarding is easily fixed by uncommenting out the discard function.

        Currently, test failures to successes are one to one. The discardCount for both players does not work properly, and it appears the second player does not pick up the card properly either. Whether this is a
        bug of the testing suite or an actual bug within the card itself will require further testing. A big positive of this suite, is that it shows a bug that is consistent and can be readily isolated and
        hammered out with further testing and debugging. This test suite also confirms the improper discard bug from the previous tests.
