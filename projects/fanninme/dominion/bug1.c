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
The supply count is some how getting decrimented below 0 (which should end the game). This could be addressed by checking inputs and any iterating loops which may affect the value of the supply count.

3)Unit Test 3: full deck count
Errors type 1: 0 Error in end turn function.
Errors type 2: 0 Error in full deck function.
Errors type 3: 2000 Memory size different.

Bug:
We caught a bug where in the memory size of the game state is different than it was when it began. We should look at the ways in which the game state is altered by this function to determine what caused this.


4) unit test 4: end of turn function
Test Results:
Testing end turn function.
RANDOM TESTS.
unitTest4: unitTest4.c:31: unitTest: Assertion `memcmp(&pre,post, sizeof(struct gameState))==0' failed.
Aborted (core dumped)

Bug:
Segmentation fault (core dumped) occurs in dominion.c line 357, the current player value is 1817024117 which seems to indicate there maybe a flaw 
in line 353 "int currentPlayer = whoseTurn(state);"
I then altered the code to ensure that the whoseTurn variable was no larger than max players however the current player value after this change was still much larger than max players.


5) card unit test 1: Adventurer
Bug:segfault
cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]];
the card drawn is equal to a negative number which causes a segfault.


6)card unit test 2:Feast
Bug:segfault
When the supply count of a card is returned. That is because the choice1 is greater than the available choices

7)card unit test 3: Testing smithy Card.
bug:segfault
The segfault is occuring in the discardCard function on line 357, the current player value is very high (in the hundreds of thousands) which seems to indicate there maybe a flaw 
in line 353 "int currentPlayer = whoseTurn(state);"


8)card unit test 4:Testing village Card.
bug:segfault.
The segfault is occuring in the discardCard function on line 1259, the current player value is very high (in the hundreds of thousands) which seems to indicate there maybe a flaw 
in line 353 "int currentPlayer = whoseTurn(state);"



