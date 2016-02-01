CS 362 - Software Engineering II
Random Testing Quiz 2
Mark Giles

The testme() function goes through a series of stages that must take place
before an error is produced. The first nine stages simply check the result
of a random character generating function called inputChar(). inputChar()
takes no arguments, and when called, it simply returns a random character.
My implementation is not completely random, but it does use the rand()
function to select an ASCII value for all printable characters of the ASCII
table, which is the range from 32 to 126. I use an additional position 127
to represent the null character \0. The character is returned by the caller.
Since each of the first nine requirements to reach the error are all ASCII
characters in the specified range, these requirements are met relatively
quickly in the while loop.

For the final requirement, another function is used to generate a random
string. The condition will only pass if the string is exactly the word 'reset'
with a null character at the end. In order to make the possibility of reaching
 the error realistic, I wrote the inputString() function to only produce a
string with 6 characters. The first method I attempted to write the inputString
function as close to random as possible. It simply produces a string by
calling the inputChar() function 6 times. After several attempts to run this
program, my terminal session was disconnected before reaching the error. One
of the test runs iterated nearly 50 million times without producing the error.
In order to force the error, I created an alternative method of the inputString
function. The second method still produces a string of 6 characters, but it
only selects random characters from the specified set: {'r', 'e', 's', 't', '\0'}.
This set enables the probability of reaching the 'reset' string more quickly.
Over 10 runs of the program, this method generally produces the error in
approximately 20,000 iterations.

The testme.c file is currently set using the second method. If you would like
to test the true random attempt, simply set method equal to 0 on line 20 of
the file. However, I think it would take a day or two of processing before
the error would be reached. This is an excellent example of why random testing
can be very wasteful in time and resources if the random tests are not guided
toward the right method of testing.
