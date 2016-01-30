/*
Kyle Johnson
johnsky3
1/26/16

Random Testing Quiz 2

The testme() function will only print the error message when the state variable = 9 and 
the string variable reads 'reset' (with a \0 character at the end of the array).  The 
specifications call for the inputChar() and inputString() functions to produce random
values, which is how I approached the testing of testme() to eventually print the error message.

inputChar():
I implemented this function to return a single random character using the ASCII codes
for the set of printable characters as the range of values.  This is because the character
values in testme() include both letters and punctuation.  There was no need to restrict the
random values to a smaller set since the condition for eventually reaching state 9 is only
dependent on a single character at a time for each state.

inputString():
I tried a few different implementations of this function before settling on one that 
creates a character array of random length between 1 and 5.  The array is then populated
at each index with a random value from a character pool of {'r', 'e', 's', 't'} and the last index at n
is set to \0 to terminate the string. The character pool was determined by using all of the characters
that appear in the string index values it testme(), so it was assumed this was the entire set for
reasons discussed below. The length of the string was made random since the character pool was
restricted.

In earlier iterations, I used random length arrays populated with random characters from a-z, 
which I quickly changed to an array of set length of 5 characters due to impractical runtimes.  Even with
the length of the array set, the odds of getting the correct character sequence in the correct order was
very low, but I tried it out of curiosity since the lectures said testing harder with a large number of 
iterations is sometimes better than testing smarter in random testing. Interestingly, I got lucky and 
saw the error message after only 8 million iterations:

...
Iteration 8355668: c = ^, s = nplob, state = 9
Iteration 8355669: c = T, s = ejarf, state = 9
Iteration 8355670: c = ", s = ksviu, state = 9
Iteration 8355671: c = x, s = twvef, state = 9
Iteration 8355672: c = Q, s = inrkp, state = 9
Iteration 8355673: c = ., s = reset, state = 9
error flip3 ~/test 397%

After seeing piazza post post @61, https://piazza.com/class/iip31fywxe72b0?cid=61 however, I realized
the assignment wasn't about pure random testing and restricted the characters in the string to the pool
of given characters from the values in testme(), and re-introduced the random length of the string to 
ensure enough randomness.

This resulted in the error message showing up in significantly fewer iterations, mostly between 2,000 
and 15,000 iterations, with the state variable reaching 9 usually before 3,000 iterations.
*/