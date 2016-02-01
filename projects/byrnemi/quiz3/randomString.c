Quiz 3
CS 362
Michael Byrne
ONID: byrnemi
1 - 31 - 2016


To produce random inputs, I created two variations of each input function. The first is "honest" and uses a set of characters representing
the actual set of characters. The second variation limits the character sets to characters found within the desired outputs.

It's expected that the first "REALMODE" option will be unable to find the error in a reasonable amount of time (or even in an unreasonable
amount of time). With REALMODE turned off, I've managed to achieve state 6 in about five minutes. One interesting thing to note is that the
randomizer functions outpace the system clock, and we wind up recycling old values. This could be avoided by inserting a sleep or pause
command.
