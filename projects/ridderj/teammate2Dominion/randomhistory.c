/*
James Linnenburger
CS362 - Assignment 4
randomhistory.co

Results from testing the adventurer card:

Function 'playCardAdventurer'
Lines executed:100.00% of 18
Branches executed:100.00% of 12
Taken at least once:100.00% of 12
Calls executed:100.00% of 3

File 'dominion.c'
Lines executed:9.05% of 597
Branches executed:6.27% of 415
Taken at least once:5.06% of 415
Calls executed:4.21% of 95

The method that I chose test the adventurer card was to isolate the function of the card itself. 
I chose to call the playAdventurer() function directly in the test instead of go through other functions
like playCard().  My reason for this was to try and isolate any specific issues from within the 
playAdventurer() function.  My random tester did a good job of isolating and getting all of the different
branches from within the playAdventurer function covered many times.  It also was able to find the
same bugs that my unit test was able to find. Once testing on the playAdventurer card has been complete and
and the bugs fixed, then I would broaden the test to include calling the playAdventurer card through use of 
the playCard() function.  My tester not only looked for expected results with things that the adventurer
card specificly does, but it also makes sure that nothing unexpected changes with the rest of the game
state as well.  This test had no improvement in coverage over the unittest for the same card from assignment 3
as the unit test also had 100% coverage.


Results from testing the smithy card:

Function 'playCardSmithy'
Lines executed:100.00% of 6
Branches executed:100.00% of 2
Taken at least once:100.00% of 2
Calls executed:100.00% of 2

File 'dominion.c'
Lines executed:10.55% of 597
Branches executed:6.27% of 415
Taken at least once:5.78% of 415
Calls executed:5.26% of 95

I used a similar strategy for the random smithy card tester.  Again, I chose to isolate the playCardSmithy() function 
instead of calling it from other functions.  This was done to try and isolate any bugs that are in
the smithy function first.  Again, once any bugs that are found are fixed, then testing can be broadened
to be called from the playCard() function for extended coverage.  The random tester found the same bug as 
the unit test did for the smithy card and it had 100% coverage (just like the unit test).





*/