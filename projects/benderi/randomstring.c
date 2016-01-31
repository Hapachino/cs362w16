/* Author:  Ian Bender
 * Course:  CS362
 * Project: Random Testing Quiz 2
 */

For my random testing implementation, I first started by attempting to find the
string 'reset\0' from a random selection of any 5 lowercase letters and
hardcoding in the ending '\0' character. Allowing for any lowercase letter, the
test took 17,765,250 iterations to find a match and end with the error.

I decided to increase the probability by limiting the random character
selection for the string to any letter in the range 'e' through 't'. With this
minor modification, I was able to get the error in only 838,249 iterations.
