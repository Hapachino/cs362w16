randomtestadventurer.c ahcheived a 23.49% coverage of dominion.c according to gcov. Looking specifically
at the lines of code pertaining to refactoredAdventurer(), however, it can be seen that all lines were 
covered.

My choice of cards to use for randomtestcard.c was the council_room. This acheived a 24.14% coverage rate. 
Again, when observing only the pertinent lines of code, every line is covered. 

My method of testing was to randomize all state variables. Tests were made much more thorough than in the 
unit tests. In these tests, all state variables are tested to ensure they were either correctly or 
incorrectly altered. 

In order to randomize, I chose to base the seed on the time and run 100 iterations of the same tests. I ran
into a problem that I should have forseen but didn't. I was reseeding the randomization at every iteration
but I failed to realize that since the seeding was based on the time and there were dozens of tests being run
every second, the vaules were being repeated rather than being randomized, which drastically skewed 
results. I fixed this by adding the index of the iteration to the seed in order to ensure the seed 
changed on every iteration.
