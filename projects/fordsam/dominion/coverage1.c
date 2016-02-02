Samuel Ford
CS362-400, Winter 2016
Assignment 3

Code Coverage
=============

Tested Functions
----------------

While I was writing the unit tests for my four functions and four cards, I was paying attention to the code coverage and looking at the dominion.c.gcov file to see if my tests failed to cover any portions of what I was testing. As a result, I ended up with 100% coverage for the "lines executed", "branches executed", and "taken at least once" measurements for the functions I specifically tested.  These functions are listed below:

* shuffle()             100% line, 100% branch, 100% taken at least once
* kingdomCards()        100% line, no branches
* buyCard()             100% line, 100% branch, 100% taken at least once
* updateCoins()         100% line, 100% branch, 100% taken at least once
* playAdventurer()      100% line, 100% branch, 100% taken at least once
* playCouncilRoom()     100% line, 100% branch, 100% taken at least once
* playMine()            100% line, 100% branch, 100% taken at least once
* playSmithy()          100% line, 100% branch, 100% taken at least once

Having 100% coverage of the functions that I tested doesn't necessarily mean that I found all the possible bugs.  100% coverage simply means that I met all the conditions required to explore the entire function.  It doesn't mean that I properly tested the function by any means; checking code coverage can help you improve your tests but it can also lull you into a state of false confidence if you're not careful.


Untested Functions with Coverage
--------------------------------

Besides the parts that I explicitly tested, the following functions were indirectly covered to varying degrees as a result (i.e. they were called within functions that I tested):

* compare()             83.33% line, 100% branch, 75% taken at least once
* supplyCount()         100% line, no branches
* whoseTurn()           100% line, no branches
* drawCard()            100% line, 100% branch, 100% taken at least once
* getCost()             23.3% line, 100% branch, 17.86% taken at least once
* discardCard()         86.67% line, 100% branch, 83.33% taken at least once
* gainCard()            80% line, 100% branch, 83.33% taken at least once

While this is a nice side-effect of having tested the other functions, I wouldn't look at this as testing.  It's quite possible that these functions contains bugs or were otherwise ill-conceived and we will only find that out through testing the functions directly.  As such, these functions should definitely be tested in the future.


Functions with No Coverage
--------------------------

Currently, the functions that are completely untested include:

* newGame()
* initializeGame()
* playCard()
* numHandCards()
* handCard()
* fullDeckCount()
* endTurn()
* isGameOver()
* scoreFor()
* getWinners()
* cardEffect()
* playFeast()


Summary
-------

Altogether, this amounts to 26.88% lines executed (of 651), 25.42% branches executed (of 417), and 19.18% "taken at least once" (of 417).

With future improvements in mind, it would definitely be good to test the initializeGame() function since it's used in every game and is relatively long (78 lines); even executing it one time will add 10% coverage.  initializeGame() was used in the example tests to set up the gameState but I thought it would be better not to trust it (since it's untested at this point).  Instead, I initialized gameState structs to 0 ({0}) and set all the variables myself so that there would be no mystery about the game state.  It's much easier to reason about the game state in this case because a member value will normally be 0 unless I changed it myself or it was changed by a function-under-test.
