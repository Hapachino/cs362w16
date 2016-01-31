/*
 * Chris Durham
 * CS362 - Software Engineering II
 * January 29, 2016
 * Quiz 2
 *
 * inputChar()
 * Because input is a limited subset of the full ascii table, inputChar only
 * finds a random character from these limited values 32 - 125 for 93 possible
 * results. This provides enough randomness to fully test the results - though 
 * a more thorough test would include all 256 ascii characters to test some of the
 * more unique inputs.
 *
 * inputString()
 * There are several ways to introduce entropy to this function. The length of the 
 * string and the possible characters. Using all combinations of letters for each
 * letter within a character array of 6 letters (and one special character) would 
 * 387,420,489 possible combinations. Instead, I used the unique characters within
 * 'reset\0' to create a random string from those characters. 
 *
 * Between the two functions, the exit code tends to be hit at 25,000 iterations.
 */
