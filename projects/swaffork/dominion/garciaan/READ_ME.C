My tests will be very complicated to read and understand since I wrote so 
many functions for them. The hardest ones to understand are checkError and 
checkStates. 

CheckError is based off of assert, but it does not exit the 
program, it just sets the error flag (just a global variable) if a 0 (false) 
is passed. At the end of each test, I print the result according to this 
error flag. 

CheckStates returns a 1 (true) if the 2 states given have the same value of 
all of their members except for the given array of excludes, which is an 
array of 0s and 1s corresponding to the order of the members in the 
gameState struct. I used an enum of similar names to make it easier to 
understand. Example: gameState->numActions is mapped to the exclude array as 
excludes[num_actions]. If you set excludes[num_actions] to 0, it will not 
check if it is the same. This comes in handy when you know something is going 
to change and you want to just check everything else. You will see this all 
throughout my tests. 

I based all of my tests on the checkStates function. I do a quick auto check
of everything that shouldn't change, and then manually check everything that
should.
