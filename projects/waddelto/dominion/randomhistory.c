/***********************************************
 *  Todd Waddell
 *  CS 362 400 W16
*   Assignment 4
*  
*  We developed random testers for all functions and cards in Assignment 3.
*  Moreover, we had pretty good coverage for those tests.  So, we struggled
*  with this assignment a bit to try to find out where we could improve
*  coverage.  In the end, we made marginal improvements to each function as
*  detailed, below.
*
*  Adventurer Card (randomtestadventurer.c)
*  Assignment 3 coverage 92% blocks.  Assignment 4 coverage 100% blocks
*
*  For assignment *3*, we implemented a random tester, ran 3000 calls and
*  returned 100%, with 92% of blocks executed.  Our goal with assignment 4
*  was to get 100% of blocks executed, and to run enough test cases that we
*  were getting a good number of cases down into those nooks and crannies. 
*
*  Mostly, for assignment 4, we wanted to get good coverage of the shuffle
*  routine.  We included a randomizer % 3 in which the deck would be moved
*  to the discard pile, forcing a shuffle. 
*
*  We tested five test paths:
*	1) Error in the cardEffect function, returned -1
*	2) Shuffle: tested that card counts after the shuffle were correct for
*	hand, deck and draw
*	3) Treasure tested the amount of treasure drawn.  (As noted earlier, we
*	introduced a bug here for an earlier assignment)
*	4) Incorrect discard - we want to check that the correct number of
*	cards have been discarded in adventurer play
*	5) Drew the wrong cards - we check to see that the treasure was
*	actually drawn into the hand correctly
*
*  We also cleaned up the results reporting.  For assignment 3, we
*  generated output a message to screen on each test failure.  For
*  assignment 4, we changed that to a summary of each test path. It's
*  likely that error by error would aid in troubleshooting.  But for our
*  purposes, line by line error reporting seems to create  a messy file for
*  the TA/instructor grading the assignment. 
*
*
* Minion  (case minion)
* Minion is a comparatively complex cards with many different paths.
* As with adventurer, we wrote a random tester for minion for Assignment 3.
* Our goal, here, then was to evaluate, extend and deepen our coverage.  We
* now have 100% coverage within case minion.
*
* There are a couple of bugs in minon that are worth highlighting here.
* Most important is how minion adds coins for choice 1 (+2 coins).  In that
* case, dominion.c adds coins to state->coins.  However, the updateCoins
* function doesn't look for bonus coins there.  It looks for them in an
* integer pointer bonus_coins, passed from the playCards function.  In
* fact, update coins resets state->coins to 0 upon entry.  So any bonus
* coins in that variable are erased.  Furthermore, the playCards function
* and the case minion don't return the coins_bonus variable.  The only real
* ways to discover the error are to track how minion interacts with other,
* subsequent functions of game play, and/or to test update coins in various
* scenarios. 
*
* The other problem with minion is that it calls the discardCards function.
* discardCards is buggy, it moves cards from the hand to the played cards
* pile, where they disappear forever. 
*
* For minion, we tested the following 9 test_paths:
*	1) Playcard function returned -1
*	2) failed to add one action
*	3) failed to record coins correctly
*	4) failed to discard played cards
*	Path 2:
*	5) Current player failed to discard hand
*	6) Current player failed to draw four cards
*	7) Other player didn't discard hand >= 5
*	8) Other player didn't draw new hand
*	9) Other player discarded when shouldn't have. 
*	
*/


