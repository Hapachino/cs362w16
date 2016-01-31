/*
Random Testing Quiz 2
CS362
Jack Holkeboer
holkeboj@onid.oregonstate.edu

=============
DEVELOPMENT
=============
For this assignment, I will implement two functions, inputChar() and inputString(),
which will generate random inputs to the testme() function.  The goal is to write
test conditions broad enough that they are guaranteed to trigger the error message.

I can see in testme.c that in order to get the error message, we need to first 
reach "state 9" by achieving a certain string of characters.  Then, we must 
have the null-terminated string "reset".  If we reach state 9 and have this string, 
the error message will print.

Each time a character triggers a state change, that state is preserved.  Therefore,
we only need to guarantee that each ASCII character will be selected.  
We can do this by having inputChar() generate a random ASCII character between 0 and 127.

For the string, we will generate random 5 letter strings with random
lowercase letters of the alphabet.


=============
PERFORMANCE
=============
The randomChar() function does not have performance implications.  The test reaches state 9
on each iteration very quickly.  The part that takes longer is guessing the random string.
There are several ways you could write the random generator for the string.  I decided to use 
the lower case alphabet and a five-letter string for this assignment, because it would finish in 
an reasonable amount of time and because I encountered errors using the full range of ASCII characters
(for example, every once in a while a certain generate key input would try to print the console0).

I ran my test suite 3 times.  Each time it was able to print the error message.
Trial 1: 29 seconds
Trial 2:  111 seconds
Trial 3: 103 seconds


*/