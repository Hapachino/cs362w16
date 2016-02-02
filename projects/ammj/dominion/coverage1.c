/**
 * Converage.c
 * Student: Jeannine Amm
 * Email:  ammj@oregonstate.edu
 * Class: CS362w2016
 *
 * Coverage in unittestresults.out
 *
 * Overall Coverage:
 * File 'dominion.c'
 * Lines executed:55.50% of 582
 * Branches executed:65.47% of 417
 * Taken at least once:57.79% of 417
 * Calls executed:30.69% of 101
 *
 * Lines executed: 55.5%
 * to get 100% line coverage for dominion.c more of the functions would need
 * to be tested.
 *
 * Branches executed: 65.47%
 * testing only 4 functions and 4 cards resulted in 65.57% branch coverage.
 * Testing larger functions that call smaller functions would increase coverage
 * but would make finding the source of bugs more difficult.  Testing the
 * smaller functions and then moving onto the larger ones may be a more
 * effective strategy. Even though a larger function has good test coverage
 * it doesn't infer that a smaller function called inside of it is getting a
 * good branch coverage or that the smaller function is functioning correctly
 * in each implementation required.
 *
 * Taken at least once: 57.79%
 *
 *
 *
 * Calls executed: 30.69%
 * to increase the percentage of calls executed more functions and function
 * calls would need to be tested.  Of the 101 calls to functions in dominion.c
 * the functions and cards chosen only executed 30.69% of them.
 *
 * unittests (Functions)
 * getCost()
 * Line Coverage: 100%
 * Branch Coverage: 100%
 * Taken at least once: 100%
 * Calls executed: 100% (no calls to other functions)
 * getCosts was a simple function which had no bugs.  It was a good function
 * to start with.
 *
 * getCost called no other functions.
 *
 * updateCoins()
 * Line Coverage 100%
 * Branch Coverage 100%
 * Taken at least once: 100%
 * Calls executed: 100%
 *
 * line 1208:  Branch 1 had a small percentage
 * Testing with values of handCount <= 0 would increase this percentage.
 *
 * Line 1210, 1214, 1218: Branch 0 had a small percentage
 * Testing iterations with hands individually heavy on copper, gold,
 * silver and no treasure values would increase these percentages
 * and increase coverage.
 *
 * updateCoins calls:
 * 	whoseTurn which had 100% coverage
 * 	shuffle which had 100% coverage
 * 	drawCard which had 100% coverage
 *
 * shuffle()
 * Line Coverage 100%
 * Branch Coverage 100%
 * Taken at least once: 100%
 * Calls executed: 100%
 *
 * Line 214: Branch 0 had low percentages
 * Testing iterations with deckCounts < 1 would increase the percentage
 *
 * Line 219:  Branch 1 had a low percentage
 * Testing iterations with deckCounts <= 0 would increase the percentage
 *
 * Line 223 & 228:  Branch 1 had a low percentage
 * Increasing this percentage may be possible by sending a large number
 * of instances where the deckCount is 2 after the discard pile is added.
 * Sending more instances where 2 cards are shuffled would not increase
 * the possibility of finding more bugs as 2 shuffled cards often end up
 * in the same positions after the shuffle.
 *
 * calls in shuffle were isolated to built in functions.
 *
 * getWinners()
 * Line Coverage: 100%
 * Branch Coverage: 100%
 * Taken at least once: 100%
 * Calls Executed: 100%
 *
 * This test suite had good percentages on all branches.
 * This function called scoreFor and whoseTurn
 * whoseTurn had 100% coverage as did scoreFor but scoreFor
 * had some low percentages on a lot of the branches.  Testing
 * more iterations weighting the number of victory cards of the same
 * type more heavily on different iterations would increase the
 * percentages on the scoreFor branches.
 *
 * Boundary testing:
 *
 *
 * playSmithy:
 * function playSmithy called 8 returned 100% blocks executed 100%
 * playSmithy had 100% line coverage
 * playSmithy had 100% branch coverage
 * playSmithy had all branches taken at least once
 * playSmithy executed all calls and returned 100% of the time.
 *
 * Boundary testing:
 * Testing focused on not having cards to draw and all cards drawn being coins.
 * Increasing tests around the boundaries like only having 1 card in the deck to draw from.
 *
 *
 * playAdventurer:
 * playAdventurer had 100% line coverage
 * playAdventurer had 100% branch coverage
 * playAdventurer had all branches taken at least once
 * 	2 branches had a relatively low execution rate.  To even out the coverage
 * 	the mix of copper, silver, gold and non-treasure coins drawn could be
 * 	evened out.
 * playAdventurer executed all calls and returned 100% of the time.
 *
 * Boundary Testing:
 * No treasures in deck, No treasures in discard
 * No deck, no discard
 * 1 treasure across deck and discard
 * all treasures in deck and discard
 * Treasure in last card of deck
 *
 * Boundary testing focused on the result of no treasures in the discard or deck.
 * Testing around the boundaries could increase the probability of finding bugs in the code.
 *
 *
 * case baron:
 * 	the statements in cardEffect under case baron resulted in the following:
 * 	line and branch coverage were not 100%.
 * 	One branch did not have both paths taken
 * 	testing more different combinations of estate in hand, choice and available
 * 	estates would result in 100% coverage.
 *
 *	Branch Coverage:
 * 	The fallthrough rate for the statement on line 845:
 *  if (state->hand[currentPlayer][p] == estate)
 *  was low at 4%.  Putting estates in different positions in the
 *  hand (closer to the end) would increase this percentage.
 *
 *  The percentage of Branch 0 for the statement on line 856 was
 *  also low.  Increasing the incidence of hands with no estates
 *  would increase the percentage.
 *
 *  Line 866 was never run to check if the game was over.  Testing
 *  with no estates in hand, choosing discard estate and only one estate
 *  left on the pile would increase the percentage and run the function.
 *
 *  Line 883 was never run to check if the game was over.  Testing
 *  with no estates in hand, choosing take estate and only one estate
 *  left on the pile would increase the percentage and run the function.
 *
 *  By not executing these lines we haven't tested the ability for
 *  the function to indicate the game might be over.
 *  Testing these lines would also increase the boundary coverage for
 *  estate supply.
 *
 *  Boundary Coverage:
 *  Possible Boundaries:
 *  No estate in hand
 *  All estates in hand
 *  No estates in supply pile
 *  Full estate supply pile
 *  No cards in hand
 *  All cards in hand
 *
 *  Boundary coverage could be increased by testing the areas around the
 *  boundaries such as the prior missed lines mentioned that would have
 *  executed had iterations where estate supply been equal to 1 during
 *  testing.
 *
 * case tribute:
 *  Line Coverage: 100%
 *  Branch Coverage: 100%
 *  Taken at least once: 100% (in the base function)
 *  Calls executed: 100% returning 100%.
 *
 *	Branch Testing:
 *  Line 993 branch 0 had a low percentage
 *  increasing the probability of duplicate cards would increase the
 *  percentage
 *
 *  Line 1000: branches 1, 3 and 4 were significantly low percentages
 *  Increasing he frequency of treasures in the revealed cards would
 *  increase the percentages.
 *
 *  Line 1004: branches 1, 3, 5, 7, 8 were low percentages
 *  Increasing these number of victory cards in the hands would
 *  result in better percentages and coverage of the if statement.
 *
 * 	Large amounts of random testing may increase the coverage percentages
 * 	for this card.
 *
 * 	Boundary Coverage:
 * 	Card boundaries:  both the same, both dead, no cards to reveal
 * 	Boundary testing was achieved by iterating through all possible combinations
 * 	of 2 cards.
 *
 * 	Player deck boundary:  No card in deck
 *
 * 	Boundaries where deck + discard exceed what can be held in a deck and needs
 * 	a shuffle was not tested.  This does have the possibility of occuring if
 * 	something is not working correctly in other portions of the program but
 * 	would not be a situation in normal play.  Testing and accommodating this
 * 	would make the program more robust and allow identification of possible
 * 	bugs in other functions.
 *
 * 	Overall Coverage:
 *
 * 	While the tests executed had good branch coverage, line coverage,
 * 	branches taken at least once, and calls executed, evening out the percentages
 * 	branches are taken would make this test suite a better test suite.
 *  Ensuring both paths are taken in a branch an adequate amount of times
 *  gives a good opportunity to ensure and adequate number of scenarios are
 *  tested in each branch.
 *
 *  Increasing the coverage for baron card to include the scenario of 1 estate
 *  with no estate in the hand and choice of both discard and take an estate would
 *  execute the isGameOver statement and may uncover bugs in the function isGameOver.
 *  Executing isGameOver would also increase the coverage percentages for dominion.c
 *  overall.
 *
 *  Increasing path coverage would definitely increase the instances of finding bugs
 *  but would require an exponentially larger amount of tests suites.
 *
 *  Increasing the logic coverage may find more bugs as well.  By testing the results of
 *  controlling the outcome of the logic expressions we can determine if issues with the
 *  logic are causing the program to fail.
 *
 *
 *
 */
