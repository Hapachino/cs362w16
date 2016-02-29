Shaun Stapleton
CS 362
Assignment 3

Execute your unit tests and describe any bugs you find in a file named bug1.c. 

Remodel unit test:
I created a unit test for remodel which found a bug in the dominion.c code which was halting my execution. This bug was in the 
remodel case statement logic. The evaluation as to whether the new card is no greater than the trashed card plus two
was incorrect. It would evaluate to true if the trashed card plus two was greater than the new card and in doing
so would return from remodel. This led to my unit test not removing the correct cards or adding a new card and
I would have a segmentation fault. I added an error print out whenever this issue would arise in the code.

Smithy unit test:
I created a unit test for smithy as required and I used my refactored code from last week therefore I knew a bug
was coming. The assert functions were aborting the execution so I went ahead with just printf functions to output
the errors. I found that there was one more card being added than anticipated per my own doing. Therefore my
tests on the hand before and after catch this error. I also catch if the deck count is different.
Between these two checks, I know what cards were gained and differences.

Adventurer unit test:
I created a unit test for adventurer as required and I used my refactored code from last week, so I knew that
the adventurer code would not know if it came across a silver treasure card since I removed that logic. With
the testing I was unable to make this error show, however I created the logic to catch it in case it does. I have
a loop to check the discard pile for the user to see if any treasure cards were discard after the card is played.

Council Room unit test:
I set up a unit test for council room for my last card test. I had refactored code once more for this card, so
I wanted to test against it to find the errors involved. I had introduced an error for trashing the action card
after use and not placing it into the discard pile. My code tests are set up for that and caught it. I also
have the card adding 3 instead of 4 cards, which my test additionally caught.

Function updateCoins() unit test:
I set up a unit test based off the example but made sure to test the 0 edge case of the loop which was left. I
did several test's on the game state, however this function did not end up giving me any bugs.

Function isGameOver() unit test:
Tested this function against my tests and did not reveal any bugs. 

Function getCost() unit test:
Tested this function against my tests and did not reveal any bugs. 

Function fullDeckCount() unit test:
Tested this function against my tests and did not reveal any bugs.