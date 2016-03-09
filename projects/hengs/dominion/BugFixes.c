Stephen Heng
CS 362, Winter 2016
Assignment 5
BugFixes.c

Bug #1: smithy 

The bug I introduced for smithy was that the player only drew 2 cards
instead of 3. I will change the for loop to start at 0 instead of 1.

Bug Code:

for (i = 1; i < 3; i++)
    {
      drawCard(currentPlayer, state);
    }
	
Fix:

for (i = 0; i < 3; i++)
    {
      drawCard(currentPlayer, state);
    }
	
Bug #2: adventurer

In my adventuer function, I removed the code that decreases the handcount 
of the current player. I will introduce the code back to distribute the
correct amount of hand count.

Bug Code:

temphand[z]=cardDrawn;
//state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
z++;

Fix:

temphand[z]=cardDrawn;
state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
z++;

Bug #3: village

I only gave one action instead of two when the card is played.

Bug Code:

state->numActions = state->numActions + 1;

Fix:
state->numActions = state->numActions + 2;

Bug #4: steward

I have whitedout one of the drawcards which will allow the player in choice1==1 to only draw 1 card
instead of 2 that is required.

Bug Code:
	drawCard(currentPlayer, state);
    //drawCard(currentPlayer, state);
	
Fix:
    drawCard(currentPlayer, state);
    drawCard(currentPlayer, state);


	
Teammate Observation:

My teammates were able to discover two bugs in my code when they tested it.
The village and the adventurer card were the two bugs, so there were no
bew changes I made to my code besides the bugs that I introduced earlier and 
are currently fixed.






