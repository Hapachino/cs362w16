/********************************************************************************************************************************************************
*** Filename: coverage1.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Due date: 1/31/2015
*** Assignment 3
*** Description: Report your findings by discussing your tests' coverages (statement, branch, boundary, etc.), and describe their implications
***              for the tests in a file called coverage1.c, also checked in to your dominion directory. I want you to look at the dominion code coverage
***              and find out what parts of your code are not covered so that in future you can improve your test suite. 
***
*******************************************************************************************************************************************************

Coverage of dominion.c code:

File 'dominion.c'
Lines executed: 34.66% of 577
Branches executed: 34.05% of 417
Taken at least once: 29.50% of 417
Calls executed: 16.84% of 95

unittest1- function updateCoins called 72602 returned 100% blocks executed 100%
unittest2- function fullDeckCount called 71874 returned 100% blocks executed 100%
unittest3- function isGameOver called 12722 returned 100% blocks executed 100%
unittest4– function gainCard() called 270 returned 100% blocks executed 100%
cardtest1– function playSmithy() called 2 returned 100% blocks executed 100%
cardtest2- function playAdventurer() called 2 returned 100% blocks executed 93%
cardtest3- function playVillage() called 2 returned 100% blocks executed 100%
cardtest4- function playSalvager() called 54 returned 100% blocks executed 100%


Implications:
In terms of dominion code coverage, the unit tests and card tests did well in achieving 100% statement and branch coverage for the chosen functions
and card effects except for playAdventurer(). However, after reviewing the coverage results and looking back at the unit tests, I know that there must be 
test cases that I am missing as evident by playAdventurer card test. I realized I neglected to test for cases where a shuffle of the discard pile into the deck was needed.
By writing more tests that loop through a wide range of input or even randomize them, it is probable to test for more hard to think of boundary cases. 
Line execution was 34.66% and branch execution was 34.05%. These would be improved as more and more domimion.c functions are tested.  Calls executed was 16.84% and is low due
to the functions I chose to test. The chosen functions did not make many calls to other functions and was therefore easier to isolate bugs without having to trace too deeply
into untested functions. I found it easier to start with the smaller functions and move on to the larger ones.  Line execution would greatly increase by testing functions such
as playCard() which calls many functions, but would definitely be tough to think of all the test cases without first dividing it up.

*/