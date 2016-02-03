/*  Paul Zotz
    CS 362 Winter 2016
    Assignment 3 - bugs found

File 'dominion.c'
Lines executed:33.33% of 576
Branches executed:24.94% of 417
Taken at least once:21.58% of 417
Calls executed:18.95% of 95

unit test functions:
function kingdomCards called 1 returned 100% blocks executed 100%
function isGameOver called 3 returned 100% blocks executed 100%
function gainCard called 4 returned 100% blocks executed 100%
function handCard called 10 returned 100% blocks executed 100%


card test functions
function smithyCard called 5 returned 100% blocks executed 100%
function adventurerCard called 6 returned 100% blocks executed 100%
function villageCard called 5 returned 100% blocks executed 100%
function greatHallCard called 4 returned 100% blocks executed 100%


On one hand, this amount of coverage seems to be expected from a test suite which only tests 8 small functions.
However, it could likely have been increased somewhat by a better choice of functions to test. An adequate test for
initializeGame(), for example, would have been much more time-consuming but would have greatly increased the amount
of coverage.

In addition to functions covered by the test suite, functions used by those functions received varying degrees of coverage.
All of my functions tested by unit and card tests reached 100% coverage - which is to be expected considering that
many of them contained relatively few branches. Just looking at some of the other functions that need to be tested, the total %
of lines/branches executed could be increased by adding some of the more complex cards/functions to the test suite.

Another issue I noticed was the relatively low number of calls on all of my tested functions. While of course I realized how
many times they were being called in my test functions, seeing it output alongside the number of times related functions were
called makes me realize that more test cases, more variations of each test case, etc. would likely be beneficial.


I guess the obvious lesson here is that going for the low-hanging fruit leads to low coverage!
