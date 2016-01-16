Made the following changes to the function:

--------------
play_smithy()
--------------
Removed the discardCard function call from existence in 
this function. The smithy card will never get discarded
and will remain in players hand at all times. 

-------------
play_adventurer()
-------------
cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1]
Became
cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]]
This causes the cardDrawn to NOT be filled with the card that was drawn.

state->handCount[currentPlayer]--;
Became
state->handCount[currentPlayer]-1;
This causes the hand cound to not actually decrease and forces an infinite loop. 

-------------
feast()
-------------
Added x = 0 to each if else-if else statement so that every card chosen is a valid card. 
This causes the error checking for the chosen card to not work. 

-------------
play_village()
-------------
state->numActions = state->numActions + 2;
became 
state->numActions = state->numBuys + 2;
This will just be wrong by using the current number of buys instead of current number of actions
as the base. 
