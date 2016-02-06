Stephen Heng
CS 362 winter 2016
Assignment 3: coverage1.c

1. unittest1: initializeGame()

File 'unittest1.c'
Lines executed:74.38% of 121
Branches executed:100.00% of 74
Taken at least once:58.11% of 74
Calls executed:56.34% of 71

For unittest 1, my statement coverage is almost complete at 100%. I have written many 
if statements that produce errors for the user to see instead of insert, for which were ignored and therefore not executed.
My unit test 1 for the initialization of the game function tested to see if the supply amount is correct for 
the kingdom cards and the treasure cards. It also made sure that the appropriate amount of players are allowed.
It tests the inital state of the game where the setup is exact as the amount of cards and an empty
deck, hand, and dicard count.

2. unittest2: updateCoins()

Lines executed:92.31% of 52
Branches executed:100.00% of 14
Taken at least once:71.43% of 14
Calls executed:82.61% of 23

This function tested if the coins were updated correctly. Again, it covered most of the statements and branches 
and neglected the failed if statements. The code inputted and tested 5 treasure cards. There were 4 scenarios
of which the entire hand was gold, silver, copper, and mixed. It was duplicated twice for player 2 and checked
against a formula to see if the results matched. 100% of the branches were covered. The failed if statements
were never executed.

3. unitest3: isGameOver()

Lines executed:86.96% of 46
Branches executed:100.00% of 12
Taken at least once:50.00% of 12
Calls executed:77.78% of 27

This function checked whether the game was over or not due the province cards running out or if 3 supplies were
out. This covered 100% of branches and 87% of lines were executed. The ones that were ignore passed the test and 
didn't active the fail and is with the case of if statements instead of assert.

4. unittest4: getCost()

Lines executed:90.00% of 10
Branches executed:100.00% of 4
Taken at least once:75.00% of 4
Calls executed:66.67% of 3

This checked for the costs of each card. 100% branch coverage and 90% lines executed. Only the never executed if statement
fell through if the function call and check was correct.

5. cardtest1: smithy()

Lines executed:85.42% of 48
Branches executed:100.00% of 14
Taken at least once:50.00% of 14
Calls executed:73.08% of 26

This function took the smithy card, which is plus 3 more cards to the players hand count. 100% of branches executed 

6. cardtest2: adventurer()

Lines executed:84.62% of 52
Branches executed:100.00% of 32
Taken at least once:75.00% of 32
Calls executed:70.37% of 27

The adventurer function had 100% branches executed. However, I believe there was a bug that didn't get two treasuer cards correctly.
I could of called a function to test if the deck was shuffled or not

7. cardtest3: village()

Lines executed:86.49% of 37
Branches executed:100.00% of 10
Taken at least once:50.00% of 10
Calls executed:75.00% of 20

This function tested the village card which added another card and two actions. The branch executed was 100%.

8. cardtest4: council_room()

Lines executed:86.84% of 38
Branches executed:100.00% of 10
Taken at least once:50.00% of 10
Calls executed:75.00% of 20

100% branches were executed. However some lines were passed over do to part of the if statements that were never triggered.