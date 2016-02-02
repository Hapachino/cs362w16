By examining the testme function you can see the function requires a specific
sequence of characters from inputChar to reach a specific state. Once in that state
it requires a specific string to reach the error state. A couple of things
worth noting are that once the code is in the first step to the error state it
can't reset and at that point the probability of the error state occuring is the
probability of the inputString function generating the "reset\0" string.

My initial attempts at implementing involved generating random ascii characters
for the input char and then random length random strings for the input string.
All this got me was an effectively infinite loop (presumably it would have hit
it eventually but sys has dinged me for long running processes before so I decided
not to experiment).

Eventually I settled on generating the input chars only that would advance the
but in a random order and generate a randomly ordered string of the correct length
to trigger the final error state from the characters "reset1234". With this
combination I saw runs as long as a couple hundred thousand and as low as 750.
