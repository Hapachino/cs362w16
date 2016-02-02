To implement the random tester I first started with the solution to the 
inputChar. Since the chars used by the program span most of the ASCII 
character set, I decided to randomly generate inputs based on the entire 
ASCII set until all of the states were reached. This was done with a single
random number generated with % 128 used to check the entire character set range.
I ran into one problem, that the ASCII character associated with 5 makes PUTTY 
output PUTTY to the command line after program execution. I decided to filter
this out so that echo $? would work to return the exit value.

For the development of inputString I originally tried to create a for loop that
would generate random strings based on constants defined above. The constants 
determine the ASCII character range (min and max), and the length of the string.
Once state 9 is achieved this string would be compared against the goal string,
until the strings match and the error was found. However, the problem with that
is there are 26^5 possible combinations on a 5 character string (closing character
automatically added). As such, after achieving state 9 the random input string
would take ~11 million iterations to find. Since this wasn't happening in under 
a couple minutes except once, I decided to add a while loop that makes sure reset
is always passed in. If you comment out the while loop you can find the original 
version of my code that works, but takes too long. 

The problem I see with random testing is that I had to modify my code to not be
random anymore, just to make it fit within a practical time constraint. This 
test case might be a little arbitrary, but it also doesn't really prove much, 
other than that my code is able to brute force its way to a solution. It doesn't
determine if bad or unexpected inputs can be handled without error, or other 
possible problems if this was production code.
