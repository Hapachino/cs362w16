/* 	File: randomstring.c
	Author: Chris Trana
	CS 362
	
When writing inputChar() is used the rand() function to select an ascii charcter between 32 an d 127 (space and delete)
in order to cover all the cases which would advance state.

I then implemented inputString() in a similar fashion.  I used a for loop to move over the first 5 array indexes and used rand() to insert 
an ascii charcter between 32 an d 127 (space and delete).  I then entered the \0 into the last index.  I knew this method would have a very, very
low probability of hitting the final case and printing the error statement but I wanted to make sure this code would compile, run, and hit state 9 before
making sure we could hit the error message in a reasonable amount of time.

In order to achieve that I created an array that contained the letters needed to spell reset and then some other chars. My for loop would then fill inputString
with randomly selected chars from this smaller subset. This allowed the program to hit the error message in a reasonable amount of time.  I also thougt about implementing
a version that would use my small subset arrary 60% of the time and the ascii charcters between 32 an d 127 about 40% of the time in order to test a wider range of 
characters in the inputString funciton but I wasn't sold that the extra time to run this version of the test case would be offset by using other characters which
for the most part act like those I'm already testing.

*/