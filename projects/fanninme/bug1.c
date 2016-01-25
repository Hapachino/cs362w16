//unit tests
1)Play card unit test1: Play card function
RANDOM TESTS.
Error in playCard.
Bug:
PlayCard returns -1 indicating an error that was caught in the function itself, there are several possible causes for this unfortunately and it's unclear which although likely it relates to input that is outside of expected bounds

2) unittest2: game is over function
segfault assert post→supply-count[providence] > 0 failed
Bug:
This is a design flaw, and should have allowed for the possibility of there to be three empty stacks of any type of card as an alternative to no remaining providences.

3) unit test 3: end of turn function
Testing end turn function.
RANDOM TESTS.
Segmentation fault (core dumped)
Bug:
unfortunately a segfault doesn't tell us a lot about what failed or how we do know that it occurred while attempting to run the function though. 

4)Unit Test 4: full deck count
./unitTest4
Testing full deck count.
RANDOM TESTS.
Memory size different.
Bug:
We caught a but where in the memory size of the game state is different than it was when it began.

5) card unit test 1: Adventurer
Testing adventurer card.
RANDOM TESTS.
Segmentation fault (core dumped)
Bug:
unfortunately a segfault doesn't tell us a lot about what failed or how we do know that it occurred while attempting to run the function though. 

6)card unit test 2:
Testing Feast Card.
RANDOM TESTS.
Segmentation fault (core dumped)
Bug:
unfortunately a segfault doesn't tell us a lot about what failed or how we do know that it occurred while attempting to run the function though. 

7)card unit test 3: Testing smithy Card.
Testing smithy Card.
RANDOM TESTS.
Segmentation fault (core dumped)
bug:
unfortunately a segfault doesn't tell us a lot about what failed or how we do know that it occurred while attempting to run the function though. 

8)card unit test 4:Testing village Card.
Testing village Card.
RANDOM TESTS.
Segmentation fault (core dumped)
bug:
unfortunately a segfault doesn't tell us a lot about what failed or how we do know that it occurred while attempting to run the function though. 
