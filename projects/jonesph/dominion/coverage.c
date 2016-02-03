/********************************

Philip Jones
Winter 2016

*********************************/


/********************************
buyCard()
File 'unittest1.c'
Lines executed:100.00% of 34
Branches executed:100.00% of 24
Taken at least once:79.17% of 24
Calls executed:70.59% of 17

isGameOver()
File 'unittest2.c'
Lines executed:97.30% of 37
Branches executed:100.00% of 26
Taken at least once:84.62% of 26
Calls executed:80.00% of 20

shuffle()
File 'unittest3.c'
Lines executed:87.50% of 40
Branches executed:100.00% of 20
Taken at least once:85.00% of 20
Calls executed:88.24% of 17

discardCard()
File 'unittest4.c'
Lines executed:84.31% of 51
Branches executed:92.31% of 26
Taken at least once:69.23% of 26
Calls executed:72.73% of 22

Village Card
File 'cardtest1.c'
Lines executed:97.62% of 42
Branches executed:100.00% of 22
Taken at least once:86.36% of 22
Calls executed:95.83% of 24

Adventurer Card
File 'cardtest2.c'
Lines executed:97.67% of 43
Branches executed:100.00% of 28
Taken at least once:92.86% of 28
Calls executed:93.75% of 16

Smithy Card
File 'cardtest3.c'
Lines executed:96.77% of 31
Branches executed:100.00% of 12
Taken at least once:75.00% of 12
Calls executed:94.44% of 18
cardtest3.c:creating 'cardtest3.c.gcov'

Great Hall Card
File 'cardtest4.c'
Lines executed:93.75% of 32
Branches executed:100.00% of 10
Taken at least once:70.00% of 10
Calls executed:88.89% of 18

File 'dominion.c'
Lines executed:23.54% of 582
Branches executed:23.26% of 417
Taken at least once:13.67% of 417
Calls executed:18.18% of 99

*******************************/
/******************************

My four unit tests all had high coverage-- the parts keeping
them from 100% on unittest 2, 3, and 4 were mostly printf
statements that I put in place of asserts. Test 4 aditionally
had an if statement that didn't get followed on, but it
led to an error/dead-end-- so it's understandable that it
as well didn't get run.

The four card tests also all had close-to-perfect coverage,
with the 3-6% off being accounted for by printf statements
instead of asserts. Other than that, their coverage was
close to perfect (at least in lines executed).

The dominion code had close to 25% coverage-- that isn't great
for checking the total, but given that I was only testing four
functions each, I'm actually fairly pleased with about 1/4.
Dominion.c is a big program, and a quarter of it (in an 
intentionally limited test) is not too shabby.

None of this indicates that my code is bug-free, of course.
And it doesn't indicate that the results I got from the tests
are 100% accurate. All that it does indicate is that I've 
managed to cover a certain percentage of lines and branch
statements for a given program/test. Basically, the quantity
of the tests can be more or less determined by coverage,
but quality remains to be determined based upon the actual
tests I run.

*******************************/