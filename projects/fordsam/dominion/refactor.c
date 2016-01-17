Samuel Ford
CS362-400, Winter 2016
Assignment 2

Refactoring
===========

Summary
-------
As requested, I refactored the Smithy and Adventurer cards into their own functions (e.g. playSmithy() and playAdventurer()).  I also did this for the Council Room, Feast, and Mine cards (making playCouncilRoom(), playFeast(), and playMine() functions).

This primarily involved moving the code from the relevant portions of the switch statement in the cardEffect() function into separate functions.  Besides that, I also had to copy variables from the cardEffect() function into these new functions so that they would continue to work properly.  As a result, some of the variables in the cardEffect() function were no longer necessary and were removed.

At the same time, I cleaned up the code in these functions (standardizing it with regard to the prevailing style) so that it would be much more readable and understandable.  The indentation throughout the file is a mixture of tabs and spaces, so I modified these functions to use only spaces (two spaces for each indentation).  [It's worth noting that the rest of the file still mixes tabs and spaces and it would be better to use one standard.]


Bugs Introduced
---------------
1. playAdventurer() was modified to introduce an off-by-one bug.  Namely, the loop condition when discarding the non-treasure cards that were drawn went from "while (z - 1 >= 0)" to "while (z - 1 > 0)".  This results in one of the non-treasure cards that were drawn not being discarded.

2. playFeast() was modified to introduce a bug in a condition, such that code will be executed when it's actually inappropriate.  Namely, "else if (state->coins < getCost(choice1))" turned into "else if (state->coins <= getCost(choice1))".

3. playMine() was modified to introduce a bug in the "discard trashed card" for loop (near the end of the function). Namely, the break statement was removed, so playMine() will actually remove *all* cards that match choice1.

4. playSmithy() is a very brief function, so there was limited opportunity to introduce bugs.  I simply changed the trashFlag in the call to discardCard() from 0 to 1, so playSmithy() trashes the card rather than discarding it.
