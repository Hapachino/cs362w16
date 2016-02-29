/* Will Thomas
CS 362
BugFixes Report

My teammates reported 2 bugs in my code: 

One reported that adventurer is not discarding the correct number of non treasure cards.
The other reported that village only adds 1 action when played instead of 2.

1.
For the adventurer card if you test with GDB you can step through and see that the variable z is never used and thus the final while loop:
	while(z-1>=0)
Never executes. Since z is meant to track non-treasure cards I added an incrementor in the else statement after drawing a card.
    else{
        temphand[z]=cardDrawn;
        state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
        z++; // Bug fix
    }

2.
The village card was not increasing the gamestate's numActions value correctly. The problem code was:
	state->numActions = state->numActions + 1;
This statement was only increasing numActions for the active player by 1. I simply changed the 1 to a 2 to fix this problem:
	state->numActions = state->numActions + 2;


Other bug fixes:
3.
Smithy card draws 4 cards for the player. If you trace this function call step by step you see that it calls the draw function 4 times instead of 3 as it is supposed to.
If you inspect the code itself at the point where the function is called you see the for loop set to run 4 times instead of 3:
	for (i = 0; i < 4; i++)
    {
        drawCard(currentPlayer, state);
    }
Fixing this is a matter of changing the loop as such:
	for (i = 0; i < 3; i++)
    {
        drawCard(currentPlayer, state);
    }

4. Finally the last bug I introduced was into the Council Room card. I had to build a simple test instance to look into this function. You find that 
The player gets an extra buy. Council Room should give the player 1 extra buy, but they are getting 2. After stepping through the code you find the following:
    int i;
    state->numBuys++;
    //+4 Cards
    for (i = 0; i < 4; i++)
    {
        drawCard(currentPlayer, state);
    }

    //+1 Buy
    state->numBuys++;

The obvious problem here is that state->numBuys++; is executed twice. I went ahead and removed the first instance of this in the code to fix.