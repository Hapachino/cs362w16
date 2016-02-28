File 'randomtestcard.c'
Lines executed:75.61% of 41
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:54.17% of 24

File 'randomtestadventurer.c'
Lines executed:77.27% of 44
Branches executed:100.00% of 18
Taken at least once:66.67% of 18
Calls executed:56.52% of 23

Implications:	All branches have been executed, whereas only 75.61% and 77.27%
	of lines of randomtestcard.c and randomtestadventurer.c, respectively, have 
	been executed.  This is expected as some of the code contains statements 
	that only execute if the tests fail. 


In developing and running the random testers for the Village Card and the 
Adventurer Card, I made several efforts to verify the correctness of my 
tests.  First I ran and verified the success of my previous card tests.  I
then compared these results to the results I obtained from my random 
tests.  Each random test generated 2000 tests to ensure a thorough coverage
of all possible combinations.  