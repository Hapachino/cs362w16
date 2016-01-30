/*	
*	Author: Martin Stryffeler
*	Filename: randomstring.c
*	Description: CS 362 Random Testing Quiz 2 Write Up
*/

The development of my random tester was an iterative process.

For inputChar, I began by getting a random number corresponding to a character from the ASCII table.
I refined this to exclude characters such as backspace and delete, which are unlikely entries and
disrupt the output of the program. Selecting a random character for each iteration gets to state 9
after only a few thousand iterations, so I am satisfied with it.

For inputString, I first tried generating characters in the same way as inputChar, and simply
assembling them into a string and returning it. This will generally trigger the error after several
million iterations. This works well enough without print statements, but is far too slow and causes
too much output to be useful with print statements. I needed to test a wide range of possible entries
and cause the error in a reasonable amount of iterations. To do this, my function has a random, ~50%
chance of generating a completely random string, and a ~50% chance of generating a string from only
the characters 'r', 'e', 's', and 't'. This causes the error to occur after only a few thousand
iterations, usually, while still throwing a lot of random input at the program.