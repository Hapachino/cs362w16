Random Testing quiz Jonathon hicke

This testing procudure requires two random generating functions
InputChar
	In input char I use the srand and rand function to pick a character
	From 32 to 127 on the ASCII table(all Upper lower and sysmbols. Than
	return the char;
inputString
	In input string I create a char array to hold the string limited to the size 
	of the word reset (4+'\0') Than I loop through each point of the array and insert
	a random char using inputChar. This cause the program to continue to run as their are
	to many permunations allowed. So I changed the function to randomly pick use the chars
	'r''e''s''t' this allowed the random tester to meet the requirement of string = reset
	with in a practical timeframe. 

A key takeaway is that by not limiting my inputs to the string I was randomly testing 
test cases that were uninteresting and fail to test the cases that did matter. 