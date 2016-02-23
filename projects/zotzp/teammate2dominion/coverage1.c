Janel Buckingham
CS 362 Winter 2016
Assignment 3 coverage1.c

gcov for all tests is:
File 'dominion.c'
Lines executed:38.85% of 574
Branches executed:37.41% of 417
Taken at least once:30.46% of 417
Calls executed:26.32% of 95

Use gcov to measure code coverage for all of these tests. Report your findings by discussing your tests' coverages (statement, branch, boundary, etc.), and describe their implications for the tests in a file called coverage1.c, also checked in to your dominion directory. I want you to look at the dominion code coverage and find out what parts of your code are not covered so that in future you can improve your test suite. 

Statement coverage: So far, the test suite executes 38.85% of 574 lines.  The implications of this are not very significant since the test suite is not testing the entire code base, and some parts of the code that are reported as being executed are not actually being tested.  However, a manual check of the code reveals that my test suite has a very strong statement coverage for the sections of code that were tested in the test suite.  

function playAdventurer called 3 returned 100% blocks executed 100%
function playSmithy called 2 returned 100% blocks executed 100%
function playCutpurse called 3 returned 100% blocks executed 74%
function playRemodel called 4 returned 100% blocks executed 100%

function discardCard called 27 returned 100% blocks executed 88%
function gainCard called 10 returned 100% blocks executed 100%
function isGameOver called 9 returned 100% blocks executed 100%
function buyCard called 7 returned 100% blocks executed 100%

The two functions that did not get 100% block coverage was playCutpurse() and discardCard().  
In the case of discardCard(), I failed to reach a state of discarding the final card in the hand, so this boundary case would need to be added in order to strengthen the test suite and reach 100% statement coverage on discardCard().  However, in the case of playCutpurse(), the only statements that were not reached were debug mode statements, so it is perfectly fine to leave coverage as it is.  All statements included in the live code are covered.

Branch coverage:
Branches executed:37.41% of 417.  Again, this overall statement means little since the test suite doesn't cover the entire code.  However, looking at individual functions gives a better understanding of branch coverage within the test suite.

function playAdventurer -- This function shows that all branches were executed.  
function playSmithy -- This function shows that all branches were executed.  
function playCutpurse -- This function shows that all important (not debug) branches were executed.  
function playRemodel -- This function shows that all branches were executed.  

function discardCard  -- This function shows that all but one branch was executed.  
function gainCard -- This function shows that all branches were executed.  
function isGameOver -- This function shows that all branches were executed.  
function buyCard -- This function shows that all branches were executed.  

Branch coverage gave similar feedback to statement coverage, but it is possible to see where a branch was only covered rarely.  In my test suite, these seem to be boundary cases, so it would be unlikely to execute those branches as often as normal cases.

Boundary coverage:

I have done fairly well covering edge/boundary cases based on gcov alone since I managed high statement and branch coverage in all areas.  I attempted to cover as many edge cases as possible in my test suite, testing empty arrays, cases with 1 or 0 or higher-than-normal numbers, etc.  However, I know that I did not cover them completely, so it shows that branch/statement coverage is not enough of an indication that all boundary cases have been looked at, especially since they are the source of so many bugs.  If all code was covered by the test suite, there could be cases that were not included in the code and would reveal a bug if a test was written for that case.  