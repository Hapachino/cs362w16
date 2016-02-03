/*
Faye Yao
CS 362
coverage.c

Coverage
Function 'compare'
Lines executed:100.00% of 6
Branches executed:100.00% of 4
Taken at least once:100.00% of 4
No calls

Function 'supplyCount'
Lines executed:100.00% of 2
No branches
No calls

Function 'fullDeckCount'
Lines executed:100.00% of 9
Branches executed:100.00% of 12
Taken at least once:75.00% of 12
No calls

Function 'whoseTurn'
Lines executed:100.00% of 2
No branches
No calls

Function 'handCard'
Lines executed:0.00% of 3
No branches
Calls executed:0.00% of 1

Function 'numHandCards'
Lines executed:0.00% of 2
No branches
Calls executed:0.00% of 1

Function 'isGameOver'
Lines executed:100.00% of 10
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
No calls

Function 'scoreFor'
Lines executed:100.00% of 24
Branches executed:100.00% of 42
Taken at least once:92.86% of 42
Calls executed:100.00% of 3

Function 'getWinners'
Lines executed:0.00% of 24
Branches executed:0.00% of 22
Taken at least once:0.00% of 22
Calls executed:0.00% of 2

Function 'getCost'
Lines executed:16.67% of 30
Branches executed:100.00% of 28
Taken at least once:10.71% of 28
No calls

Function 'discardCard'
Lines executed:92.31% of 13
Branches executed:100.00% of 6
Taken at least once:66.67% of 6
No calls

Function 'gainCard'
Lines executed:61.54% of 13
Branches executed:100.00% of 6
Taken at least once:50.00% of 6
Calls executed:100.00% of 1

Function 'buyCard'
Lines executed:0.00% of 18
Branches executed:0.00% of 6
Taken at least once:0.00% of 6
Calls executed:0.00% of 4

Function 'updateCoins'
Lines executed:100.00% of 11
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
No calls

Function 'playFeast'
Lines executed:82.61% of 23
Branches executed:80.00% of 10
Taken at least once:70.00% of 10
Calls executed:100.00% of 6

Function 'shuffle'
Lines executed:100.00% of 16
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
Calls executed:100.00% of 2

Function 'drawCard'
Lines executed:100.00% of 25
Branches executed:100.00% of 6
Taken at least once:100.00% of 6
Calls executed:100.00% of 1

Function 'playCouncil_Room'
Lines executed:0.00% of 9
Branches executed:0.00% of 4
Taken at least once:0.00% of 4
Calls executed:0.00% of 4

Function 'playVillage'
Lines executed:100.00% of 6
No branches
Calls executed:100.00% of 3

Function 'playSmithy'
Lines executed:100.00% of 6
Branches executed:100.00% of 2
Taken at least once:100.00% of 2
Calls executed:100.00% of 3

Function 'playAdventurer'
Lines executed:100.00% of 16
Branches executed:100.00% of 10
Taken at least once:90.00% of 10
Calls executed:100.00% of 2

Function 'endTurn'
Lines executed:0.00% of 20
Branches executed:0.00% of 6
Taken at least once:0.00% of 6
Calls executed:0.00% of 3

Function 'cardEffect'
Lines executed:6.50% of 200
Branches executed:13.61% of 169
Taken at least once:3.55% of 169
Calls executed:9.09% of 55

Function 'playCard'
Lines executed:0.00% of 14
Branches executed:0.00% of 10
Taken at least once:0.00% of 10
Calls executed:0.00% of 3

Function 'initializeGame'
Lines executed:85.48% of 62
Branches executed:100.00% of 46
Taken at least once:82.61% of 46
Calls executed:100.00% of 5

Function 'kingdomCards'
Lines executed:0.00% of 13
No branches
No calls

Function 'newGame'
Lines executed:0.00% of 3
No branches
No calls

File 'dominion.c'
Lines executed:41.90% of 580
Branches executed:52.54% of 413
Taken at least once:37.29% of 413
Calls executed:31.31% of 99
dominion.c:creating 'dominion.c.gcov'


Overall, my tests covered around half of the branches in dominion.c, and 41.72% of the overall lines. 
Upon further inspection of the .gcov file, I noticed that my unit tests never touch functions like 
newGame, playCard, buyCard, numHandCards, handCard, or getWinners. This makes sense because my tests 
didn't need to utilize those functions. Within cardEffect, I execute 
approximately 6% of the actual function, because the entire function is basically a 
series of switch cases that direct to the right card function/body of code that executes the card effects.
Upon further examination, I was glad to see that for all the cards I test, the branch that executes the card
I was testing was covered.

For most of my tests, I cover 100% of the branches of the function I was trying to test, which was exciting to see.
However, playFeast did not experience 100% coverage. This was because there was a conditional
while (x == 1) that always executed right after declaring x == 1. Therefore, this branch would never execute
since x will always be 1. The branch where the while loop won't execute will never be explored. 
Examining this, I was satisfied that I covered all of playFeast possible, even though gcov says that my tests have 80%
branch coverage.

Altogether, I feel my unit tests provided 100% branch coverage for the functions they were testing for.
That said, my isolated tests in themselves may not reveal as many bugs as I'd like, as I do not test the
entire process of playing Dominion. I test isolated scenarios where the game state might become unplayable or bugged
before it even gets to the tested functions in real play. As is though, my tests do reveal isolated logic errors
or improper game state changes by executing these functions alone.
 */