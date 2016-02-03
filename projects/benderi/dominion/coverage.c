/* Author:      Ian Bender
 * Course:      CS362
 * Due Date:    2/3/2016
 * Description: Assignment 3 coverage report. 
 */

In most of the unit and card tests, the branch coverage is 100%, while the
statement coverage is in the 80 to 90% range. There should never be 100%
statement coverage in these tests, as that would mean that a test criteria was
both a success and a failure. In this assignment, I did not explicitly call
functions to test both scenarios.

The 100% branch coverage is somewhat misleading, as the actual percentage taken
at least once tends to be significantly lower. I believe this is because in my
if...else branches, typically only one of the branches is taken (success vs.
error).

The coverage results for dominion.c are likely a more accurate representation
of the code that was actually covered. The statements and branches in this file
are far more varied and conditional statements are often more involved than a
simple success/error statement.

unittest1.c
lines: 90% of 30
branches: 100% of 14

unittest2.c
lines: 87.5% of 16
branches: 100% of 8

unittest3.c
lines: 84.21% of 19
branches: 100% of 8

unittest4.c
lines: 85.71% of 28
branches: 87.5" of 16

cardtest1.c
lines: 80% of 30
branches: 100% of 12

cardtest2.c
lines: 87.88% of 33
branches: 100% of 26

cardtest3.c
lines: 82.14% of 28
branches: 100% of 12

cardtest4.c
lines: 84% of 25
branches: 100% of 8

dominion.c
lines: 39.82% of 560
branches: 39.09% of 417
