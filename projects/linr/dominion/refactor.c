Robyn Lin
CS 362-Winter 2016

Refactored:
-I moved these 5 cards from the cardEffect() function to their own separate functions: Smithy, Adventurer, Village, Remodel,
and Mine.

Bugs:
-Smithy: changed the 3 in the for loop line to 4.
-Adventurer: deleted "cardDrawn == gold" from the line if(cardDrawn == copper || cardDrawn == silver, etc).
-Village: changed the line for +2 Actions from state->numActions + 2 to state->numActions + 1.
-Mine: changed the line j = state->hand[currentPlayer][choice1] to j = state->hand[currentPlayer][choice2].
