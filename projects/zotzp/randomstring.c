/*  Paul Zotz
    CS 362 Winter 2015
    Random Testing Quiz
*/

/*
inputChar() uses an ASCII range wide enough to generate all characters needed to get to state 9, which happens pretty quickly. Using an inadequate range results in the tester never reaching state 9.
inputString() - originally utilized inputChar but a range of chars this large would take a very, very long time to trigger an error. Using the exact length needed and a range of characters limited to those needed resulted in the error being triggered in a reasonable amount of time.

I eventually hit an error at 961,603 iterations. In previous tests, the number of iterations could easily go for many more iterations if left alone for long enough (at which point I would give up and scale back the range).

The lesson here seems to be that completely random testing is inefficient. In order for a test to be effective, the amount of randomization involved should be carefully considered.
*/
