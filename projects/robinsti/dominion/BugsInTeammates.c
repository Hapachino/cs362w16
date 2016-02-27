/******************************************************************************
 ** Author: Tim Robinson
 ** Date created: 2/27/2015

Isaiah (perrotti)
-----------------
The bugs that I found were in the Adventurer card. The results of the tests
can be seen in the robinsti_unittestresults.out file, the tests for which I 
replaced a failed assertion with if and printf statement. For the adventurer 
card, we can see that the card counts are off for both the cards in hand for 
the player and the cards the player has in their possession in total.

Specifically, we have:

The player always has 1 more card than expected in their hand.
The player always has 1 fewer card than expected in their possession in total.

Will (thomasw)
--------------

The bugs that I found were also in the refactored Adventurer card function for
Will's code. As can be seen in the robinsti_unittestresults.out file, the
adventurer card function causes the total number of cards in the player's
possession to have fewer cards than expected.

Specifically, we have:

The player always has 1 fewer card than expected in their possession in total.

 *****************************************************************************/