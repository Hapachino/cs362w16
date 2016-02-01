Random Testing Quiz 2
James Linnenburger
CS 362 - Winter 2016

for inputChar():

looking at the code in testme(), I was able to determine which characters
were necessary in order to advance the state from 1 - 9.  These characters
'[', ']', '(', ')', '{', '}', 'a', ' ', 'x' are possible 
values for the random characters and I  built inputChar to return one
of these 9 values.

for *inputString():
Looking at the code in testme(), I saw that the string needed to contain
the letters 'r' 'e' 's' and 't'.  So I built an array of characters with
these populating it.  Then I  built the String a character at a time
by choosing a random value from the character set.

It finds the error message by progressing through states 1 - 9
by randomly picking the correct character for that state.  Once it is 
state 9, it looks for the string to be "reset\0".  Once both of those
conditions are met, the error message pops up.

