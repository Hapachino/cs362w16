/*
randomstring.c

Matthew Meyn

My random tester finds the error message by having inputChar() generate random characters and having 
inputString() generate a string of random characters within a relatively small range: each of the 5 
non-null characters will be within a range of 5 characters of the corresponding "error" value. This 
decreases the amount of time required to get the string "reset". Generating completely random letters
takes a very long time before the string "reset" is produced. But when the chances of finding the "bad"
character (for example, 'r' for the first one) are increased to 1 out of 10 characters rather than 1 
out of 26, the "bad" string is very likely to be generated within the first few hundred thousand tries,
often within around 100,000.

*/
