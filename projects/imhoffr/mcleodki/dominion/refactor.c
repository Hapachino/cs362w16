/* Kim McLeod
refactor.c
assignment 2
CS 362


The following card implementations have been modified into their own free-standing functions:


Adventurer - To modify the Adventurer implementation, the funciton needed access to the gameState variable. It was therefore passed into the function as a pointer. In the function, several variables needed to be declared. 


Gardens - The gardens implementation required only creating a function that returned the same value.


Smithy - To modify the Smithy implementation, the funciton needed access to the gameState variable and handPos variable. These were passed into the function as a pointer and int, respectively. Int i was also initialized at the beginning of the function for the for loop.


Village - To modify the village implementation,  the funciton needed access to the gameState variable and handPos variable. These were passed into the function as a pointer and int, respectively.  


Outpost - To modify the outpost implementation,  the funciton needed access to the gameState variable and handPos variable. These were passed into the function as a pointer and int, respectively.


All new functions return an int of the original return value from the switch statement. The functions are called in the return statement.




Bugs!

Small bugs were added to the following implementations:

Adventurer - The first while loop will try to find 3 treasure cards instead of 2.


Smithy - The player will receive 2 cards instead of 3.


Village - The player will receive only one extra action instead of 2.


Outpost - The outpostPlayed count will be incremented by 2 each time instead of by 1.


*/





