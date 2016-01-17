Nathan Thunem
CS362 Winter 2016 -- Assignment 2


Pick five cards implemented in dominion.c. Choose 3 cards of your choice and smithy and adventurer cards are 
mandatory. Refactor the code so that these cards are implemented in their own functions, rather than as part 
of the switch statement in cardEffect. You should call the functions for these cards in the appropriate place 
in cardEffect. Check in your changes, with appropriate git commit messages. Document your changes in a text file 
in your dominion source directory, called “refactor.c.” Your implementation of at least 4 of these 5 cards should 
be incorrect in some way, i.e., you should introduce subtle bugs that are hard to catch in your changes. Introducing 
bugs in smithy and adventurer is mandatory.  Write information of your bugs also in refactor.c.   Later in this class, 
other students will test your code, so try to keep your bugs not superficial. Refactored program should compile 
without any error.


Refactored cards:
Adventurer: In the second while loop, the loop should run as long as z-1 >= 0, not greater than 0.

Smithy: In the call to the discardCard function, the value being passed as trashFlag is 1 instead of 0. 

Council_Room: In the for loop, the number of cards should be less than 4, not less than 5.

Village: state->numActions should add 2, not 1

GreatHall: There are no bugs in this function 