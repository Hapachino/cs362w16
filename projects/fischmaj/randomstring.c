/*
Jeremy Fischman
Quiz 2 (testme.c)


WHAT I DID: 
   I implemented inputChar to generate a single random character with an ASCII
value between 32 and 127 (all of the printable characters), and inputString
to generate a 5 digit string of lower-case letters. I also slightly modified
testme(), because as written it calls inputString with no parameters, which 
means the only way to return a string is to malloc a new string in the 
function with each run.  But, because there is no parameter, there is no way
to free each newly created string, which would quickly result in the program
using all of its available memory. 


WHY: 
CHOICES AFFECTING INPUTCHAR():
  The first thing I did was consider the number of test cases that would be 
required to likely generate the error.  Before any error can be caught the 
program must reach state '9'.  This is accomplished by the 'c' variable being
set to the following values: [, (, {, " ", a, x, }, ), and ] in that order. 
There are 95 possible characters in the ASCII set if you exclude the first 31
control characters, so it seemed as though the program should reach state 9
relatively quickly. For each state, there is a 1/95 chance of hitting the 
key character each run and advancing the state.  Once hitting state 9, the 
program remains in state 9, and the 'c' variable is no longer required. The 
chance of hitting the desired character in n tries is equal to one minus 
the chance of not hitting it after n tries: 1 - (94/95)^n. There is about a 
97% chance of hitting the desired character after 340 tries.  

  Therefore I implemented the inputChar() function by generating a random value
between 32 and 127, and casting that as a char, which is then returned. Based
on the probability above, I estimated progressing to state 9 after approx. 
3060 runs, or 9*340. Experimentally, it turned out to be much quicker on avg. 


CHOICES AFFECTING INPUTSTRING():
  The second thing that needed to happen to reach the error state was that the
string input needed to be set to "reset".  We were not given a length of the
input string, nor a desired domain of characters over which to iterate, so 
I considered which sets of characters to generate randomly to have a chance of
generating the error in a reasonable period of time. Since there are 5 
characters in reset, I chose to return 5 random characters, terminated by null.

  However, using all 95 possible characters in the ASCII set, as I did above 
would mean 95^5 possible input strings, or trying to generate by chance 1 out
of about 7.9 billion possilbe strings. To have a 95% chance of success it
takes approximately 24 billion runs.  Since my system runs about 10 million
test iterations every minute, that would require 57 hours.

  Therefore, I narrowed the choice of characters to  only lower-case letters,
yielding 11,881,376 possible input strings. There is about a 63% chance of 
randomly generating "reset" in the first 11,881,376 runs (about the first 
minute and 10 seconds, on my system), and a better than 99.9% chance of 
generating the string  randomly in the first 118,813,760 runs, which is about 
11-12 minutes on my system. This seemed like a reasonable run-time for a short 
quiz.   

