/*
Thomas "Adam" Pippert
Date: 31-January-2016
Assignment: Quiz 2

*** Development of Random Tester ***

The Problem:
The random tester needed to be built in such a way that the error message could be produced.  Somehow, the fuzzer had to create the characters "reset" all in a row.  Since those characters were all lowercase, I limited the characters and the strings to only lowercase letters.  Had the bounds of the problem required uppercase letters, I would have left those in, but in the interest of time I reduced the problem size.

Solution:
I looked at an ASCII chart and saw the range of lowercase characters in the chart.  I built a randomizer for characters to correspond to the appropriate range (32 to 127), and put this in inputChar().  For inputString(), I used the same range of letters, and created length [5] (6 characters, 0-5) strings to match, since I knew looking at the code that the string to match was "reset\0" (One cannot forget the null terminator in a C string, or the algorithm would run forever).  When the correct combination is returned, the if statement activates in testme() to call the error message.


Results:
Even only using the domain of lowercase letters, it still takes a long time (a few minutes) to run the test.  My first run went to Iteration 7778255, for example.  Obviously, since the domain of the problem is 26*26*26*26*26 possible combinations (11881376 possible combinations), and there are possibilities for repeats before the problem is even solved, this is a very large domain.  This very easily illustrates, even using a very small problem, how difficult truly random testing can be on broadly defined domains.
*/
