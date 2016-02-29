Shaun Stapleton
CS 362
Assignment 2

Document your changes in a text file in your dominion source directory, called “refactor.c.” 
Your implementation of at least 4 of these 5 cards should be incorrect in some way, i.e., you 
should introduce subtle bugs that are hard to catch in your changes. Introducing bugs in smithy 
and adventurer is mandatory.  Write information of your bugs also in refactor.c 

Card Changes:

Adventurer- I removed the check on if the silver card is drawn during the card drawing process. This
will place the silver card in the temp hand, not update the drawntreasure and make it so a player
cannot pull a silver when playing the adventurer card.

Smithy- Added a size variable and gave it a value of 4 and placed it in the for loop, so that the
card will pull four cards instead of three. I figured if I used size in the for loop and not 4 explicitly
it may throw off the tester.

Council Room- I edited the for loop, so that the user will only gain 3 cards instead of 4 when this
card is played. I also set the trash flag to 1 instead of 0, similar to the Village, so that
the card is trashed and not placed in the discard pile.

Feast- I set the value of the supply count for choice1 card to be <= 1 instead of 0. This will
tell the user that particular supply card is no longer available when there is still one left.

Village- In the village function when the discardCard is called I set the trash flag to 1 instead of
0, so that the card will be trashed, instead of being placed into the discard pile.
