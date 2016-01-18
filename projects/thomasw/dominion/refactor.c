/*
Name: Will Thomas
Class CS 362
Assignment 2
1/17/2016

I made changes to the following code:
     I refactored 5 of the card effects from the switch within cardEffect() into their own functions. All five of these are located within dominion.c.
     Within the switch, if that card's case is triggered the function is now called instead. The cards are: Smithy, Adventurer, Council Room,
     Village and Embargo.

     I also added function declarations into the dominion.h header file for all 5 of these new functions.

I introduced the following bugs into my code refactor:
     adventurerCard()'s check for treasure cards now ignores copper. I removed it from the conditional statement. Treasure drawn
          will only increase when the player draws silver and gold now.
     smithyCard()'s for loop now counts to 4, so the player draws 4 cards instead of 3.
     councilRoomCard() repeats state->numBuys++ in 2 locations. It should only happen once.
     villageCard() now only adds 1 action instead of 2:     state->numActions = state->numActions + 1;          
*/