/**
 * randomstring.c
 * Student:  Jeannine Amm
 * email:  ammj@oregonstate.edu
 * class: cs362w16
 *
 * Instructions:
 * Implement a random tester for the function testme() in testme.c
 * that is capable of printing the error message.  You should implement
 * inputChar() and inputString() to produce random values. Write up the
 * development of your random tester and how it finds the error message
 * as randomstring.c. Submit testme.c and randomstring.c under your onid
 * directory in class github. (under your onid directory and not under
 * dominion directory).
 *
 * Running testme:
 * make testme
 * depending on your platform you will either run:
 * > ./testme OR > testme
 * to put results into unittestsresults.out
 * > make runTests
 *
 * RandomTester Implementation:
 * The goal of the test was to find the trigger for the exit code.
 *
 * The test code initializes with state set to 0.
 * The code uses the single char stored in c to move up in states.
 * when it reaches state 9 it looks at the value in state.  When state
 * contains reset\0 it exits the code.
 *
 * The characters the code looks for in c are contained in the ascii
 * table between the lower bound of 32 and the upper bound of 125.  For the
 * value for c returned by inputChar, a random number was generated between
 * these limits and converted into it's character form.
 *
 * Testing characters outside these bounds would have made the test more
 * random but would have resulted in a lot of data we may not necessarily
 * have cared about.
 *
 * The bounds could have been further reduced to contain only the
 * characters [,(,{, ,a,x,},),},] but if the test were testing a
 * program where other inputs could be expected, adding the remaining
 * characters in the range does not increase the test time significantly.
 *
 * The string the code looks for once it has moved into state 9 is a
 * string of 6 containing reset\0.
 *
 * While a true random string generator would produce a lot of test results
 * only the characters inside that string would produce the exit code.
 *
 * The test could have been shortened to have inputString() only return
 * reset but this would not be considered random.  It also would only test
 * that when reset is encountered in state 9 it exits but would not test for
 * the possibly of other inputs being entered in state 9 that might result in
 * unexpected occurrences.
 *
 * For inputChar and inputString to be truly random, all the possible entries
 * would have needed to be a possibility to be chosen. InputString would need
 * to return a wider variety in the length of the string. The increase in
 * possibilities available would result in a significant increase testing time
 * for minimal return.
 *
 */
