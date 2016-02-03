/*
 * Andrew Gremmo
 * CS362 - Quiz 2 - Random Testing
 *
 * inputChar generates a random ASCII between 0 and 127.  The way this interacts
 * with the random test is that it first needs to generate '[' in order to reach
 * state 1.  Then it needs to generate '(' in order to reach state 2 and so on.
 * It is guaranteed to eventually generate all of the necessary characters it
 * needs in order to progress through the states.
 *
 * inputString generates a random string of 1-5 characters selected from "erst".
 * Only once the testing has reached state 9 from generating random chars does
 * the string that has generated matter.  The test will keep looping until
 * "reset" is generated as a result of the inputString function, "error" will
 * be output and the program will terminate.
 */