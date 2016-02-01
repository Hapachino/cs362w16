In developing the random tester, I recognized that the bounds of input should be based on values that will actually affect the state of the program during execution.

The first function, inputChar(), returns a random character from the set "[({ ax})]" by generating a random index into the set. This function effectively filters out inputs that would have no chance of affecting execution of the testme() function; thus the character returned from this function is both randomly generated and guaranteed to affect the state machine.

The inputString() function returns a random permutation of the string "reset" for the same reasons; the string returned will be randomly generated, but will be composed of characters that can actually affect the state of the program, so that eventually the word 'reset' will be generated. The permutations are generated from running a simple shuffling algorithm on the original string.

Generally, the error message is usually returned somewhere in the range of 60-250 iterations. Only once the inputChar() function has returned the characters in the necessary order to get the state machine to state 9 does the generated string from inputString() matter. Since the state machine does not leave state 9, it is only a matter of time until inputString() returns the string "reset", thereby producing the error message.
