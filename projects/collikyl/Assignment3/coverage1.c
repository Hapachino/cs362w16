Description:
Unit test coverage was fairly good. I wrote them specific for the function they were supposed to be testing.
Taken at least once was the lowest of the coverage area but with random testing that could be fixed.

Card test coverage was the lowest by far. This is because I tried to create a program where I could change the defined variables and have it test the card. This would lead to less lines being executed
and elss branches being takend depending on the card that has been chosen, along with specific values associated with that card (how many cards its supposed to draw, supply states, discard count, etc...)
OVerall, an area of improvement would be to avoid writing a general test suite for all cards and rather use many of the functions in my test suite as helper functions (for instance checking if any variables changed
that weren't supposed to) depending on the card being tested, as opposed to including them all in one program. 

File 'unittest1.c'
Lines executed:92.45% of 53
Branches executed:100.00% of 12
Taken at least once:66.67% of 12
Calls executed:88.89% of 27
unittest1.c:creating 'unittest1.c.gcov'

File 'unittest2.c'
Lines executed:77.27% of 88
Branches executed:100.00% of 22
Taken at least once:63.64% of 22
Calls executed:84.62% of 52
unittest2.c:creating 'unittest2.c.gcov'

File 'unittest3.c'
Lines executed:92.86% of 84
Branches executed:100.00% of 28
Taken at least once:78.57% of 28
Calls executed:81.25% of 32
unittest3.c:creating 'unittest3.c.gcov'

File 'unittest4.c'
Lines executed:100.00% of 65
Branches executed:100.00% of 24
Taken at least once:62.50% of 24
Calls executed:82.86% of 35
unittest4.c:creating 'unittest4.c.gcov'

File 'cardtest1.c'
Lines executed:65.87% of 208
Branches executed:81.25% of 64
Taken at least once:56.25% of 64
Calls executed:45.07% of 71
cardtest1.c:creating 'cardtest1.c.gcov'

File 'cardtest2.c'
Lines executed:66.35% of 211
Branches executed:81.82% of 66
Taken at least once:56.06% of 66
Calls executed:45.83% of 72
cardtest2.c:creating 'cardtest2.c.gcov'

File 'cardtest3.c'
Lines executed:66.03% of 209
Branches executed:81.25% of 64
Taken at least once:56.25% of 64
Calls executed:45.07% of 71
cardtest3.c:creating 'cardtest3.c.gcov'

File 'cardtest4.c'
Lines executed:65.24% of 210
Branches executed:76.47% of 68
Taken at least once:52.94% of 68
Calls executed:45.71% of 70
cardtest4.c:creating 'cardtest4.c.gcov'

