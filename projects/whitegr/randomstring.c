/*
Greg White
Random Testing Quiz 2

SUMMARY:
First I reviewed the testme() function and then I implemented the two required functions so that 
there would be an eventual end to the testme program by allowing the code to move through all its "states":

inputChar() generates a random char for the entire text like subset of the ascii characters
I use the formula for a random range as (rand() % (max+1 - min)) + min and the program quickly goes through the states.

inputString() limits the random characters to just e through t in the ascii table so as to complete quicker. The range of the random
numbers is calculated with the above formula. I liked some student examples that created a static array of predefined letters
and numbers and then the program picked random numbers from that.

In conclusion the program runs quite a few time before it completes - I just ran it and it was 264,364 iterations before "rest" was spelled but 
that really only took maybe less than a minute so it was kinda neat to consider using random testing to find all sorts of bugs in things by
trying millions of combinations at once.
*/
 