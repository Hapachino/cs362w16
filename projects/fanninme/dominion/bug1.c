//unit tests
1)unit Test 1: Play card function

Errors type 1: 2000 Error in playCard function bad exit status.
Errors type 2: 0 Error action count was not decrimented 

Bug:
PlayCard returns -1 indicating an error that was caught in the function itself, there are several possible causes for this unfortunately and it's unclear which although likely it relates to input that is outside of expected bounds

2) unit test 2: game is over function
Errors type 1: 0 Error memory size wrong.
Errors type 2: 0 Error bad return value from function 
Errors type 3: 991 Error negative supply count 

Bug:
The supply count is some how getting decrimented below 0 (which should end the game).

3) unit test 3: end of turn function
Testing end turn function.
RANDOM TESTS.
Segmentation fault (core dumped)

Bug: The end of turn function segfaults ending the unitTest program early. There is likely a out of bound memory access error in end of turn function however to catch it we would need to alter the source code or use a debugger on tthe source code to determine where the segfault is occuring.


4)Unit Test 4: full deck count
Errors type 1: 0 Error in end turn function.
Errors type 2: 0 Error in full deck function.
Errors type 3: 2000 Memory size different.

Bug:
We caught a bug where in the memory size of the game state is different than it was when it began. We should look at the ways in which the game state is altered by this function to determine what caused this.

5) card unit test 1: Adventurer
Bug:

6)card unit test 2:
Bug:

7)card unit test 3: Testing smithy Card.
bug:

8)card unit test 4:Testing village Card.
bug:

