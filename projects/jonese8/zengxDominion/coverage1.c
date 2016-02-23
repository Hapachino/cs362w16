/* Xiaohan Zeng code coverage report for assignmen3

Line coverage, branch coverage are as shown below
File 'dominion.c'
Lines executed:30.65% of 584
Branches executed:29.98% of 417
Taken at least once:21.82% of 417
Calls executed:24.21% of 95
dominion.c:creating 'dominion.c.gcov'

From above we can see that some amount of code is covered while testing 4 cards and 4 functions. Obviously there are improvement to be made. To take a closer look at what's not covered we should take a look at function coverage. 

I will focus on 4 cards and 4 function that I tested

4 cards:
Function 'playSteward'
Lines executed:100.00% of 10
Branches executed:100.00% of 4
Taken at least once:100.00% of 4
Calls executed:100.00% of 5

Function 'playVillage'
Lines executed:100.00% of 5
No branches
Calls executed:100.00% of 2

Function 'playSmithy'
Lines executed:100.00% of 6
Branches executed:100.00% of 2
Taken at least once:100.00% of 2
Calls executed:100.00% of 2

Function 'playAdventurer'
Lines executed:93.33% of 15
Branches executed:100.00% of 12
Taken at least once:75.00% of 12
Calls executed:50.00% of 2

4 functions
Function 'gainCard'
Lines executed:100.00% of 13
Branches executed:100.00% of 6
Taken at least once:100.00% of 6
Calls executed:100.00% of 1

Function 'discardCard'
Lines executed:92.31% of 13
Branches executed:100.00% of 6
Taken at least once:83.33% of 6
No calls

Function 'isGameOver'
Lines executed:90.00% of 10
Branches executed:100.00% of 8
Taken at least once:87.50% of 8
No calls

Function 'updateCoins'
Lines executed:100.00% of 11
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
No calls


It's easy to see that we have 100% coverage for all cards except for Adventurer. After taking a look at gcov file I find out I didn't cover the case where deck is empty, this can be a future improvement
For the functions 
In discarCard I found I didn't test the case when there is only one card in hand
In isGameOver I found I didn't test the case when province card is empty