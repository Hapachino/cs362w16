I implemented a simple random function for each of the test methods.

For the inputChar() I just randomly assigned the char value to a random number that the ASCII table would produce as a character.
I did the same for inputString(), but just had it go through a for loop to add it five times and limited the characters to lower case,
so as to keep the randomness down a bit.

This caused the test function to run about 1.5 million times before exiting with the error. This really shows off how bad random
testing can be.
