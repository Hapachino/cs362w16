Philip Jones
CS362 - Winter 2016

-Moved the adventurer, smithy, village, feast, and council room functionality into separate functions. These functions are at the bottom of the code and called whenever the switch case is reached. The functions were previously declared in the header file.

-Changed the for loop in playSmithy() from i < 3 to i <= 3.

-Adjusted the starting value of drawntreasure in the playAdventurer() function from 0 to 1.

-In playVillage(), removed the line for discarding the card after it's been used.

-Gave the player 10 coins when cashing in a feast instead of the 5 as required by the rules.