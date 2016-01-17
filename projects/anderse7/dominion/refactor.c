Eric Anderson
CS362 Winter 2016
Assignment 2

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

Adventurer: In the adventurer() card implementation, I deleted the -- decrementer from the state->handCount[currentPlayer]--;
statement, this will be real easy to miss and the discard will not be right.  Really subtle!

Council_Room: In the council_room() card implementation, state->numBuys is incremented, I changed this to 
decrement. The action is doing the opposite and subtracting coins. Ouch!

Smithy: In the smithy() card implementation, I changed the i++ to ==i, this will cause an increment before the loop
is executed resulting in on less card. 

Village: In the village() card implementation, I introduce two bugs.  First I set numActions to three, the
card is only supposed to have two.  It will all work but the player will get an additional action than they
should have. and second,when discardCard() is called, a 1 is passed in as the trash flag. The discardCard()
function only checks if the trash flag is <1, Passing a 1 to it will cause the logic to be skipped and it will
always return 0.  

Great_Hall: This one is correct.

