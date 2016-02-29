Gcov Results

The results are shown in my unittestresults.out file at the very bottom.

Coverage for all 8 test files:

File 'dominion.c'
Lines executed:28.10% of 580
Branches executed:32.05% of 415
Taken at least once:21.45% of 415
Calls executed:21.00% of 100

My unit and card tests could be improved in terms of statement and branch coverage. I only covered slightly
less than a third of 580 statement lines, and only about a third of all 415 branches were executed. Of
the roughly 32% of branches that were executed, only 21.45% of these were taken once. This means
I was not iterating over through all possible executable branches and conditionals.

One area I did not test was boundary/edge cases; I used very basic cases and always had players start with
the basic 5-card hand. I also manually set the number of players to 3 for all 8 of my test files. I
also tested most of the functions and cards functions only once, so my testing was very simple and limited.
My unit tests either passed or failed, and so the other half of the conditional if-else statements
usually weren't tested, which probably contributed to my relatively low "Branches executed" figure.
Gcov allows me to see that I could have done more rigorous testing to stress the system and iterate
through more branches.



