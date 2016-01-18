refactor.c

playSmithy:
The variable i in the drawcard for loop is initialized to 1 instead of 0. Leading to two cards being drawn
instead of 3.

playAdventurer:
Changed the condition in the discrard while loop from z-1>=0 to z-1>0. To one card being left in the
current players hand at the end of the turn.

playCouncil_room
The variable i in the drawcard for loops is initialized to 1 instead of 0. Leading to 3 cards being drawn
instead of 4.

playRemodel
j = state->hand[currentPlayer][choice2] instead of j = state->hand[currentPlayer][choice1];

playVillage
No bugs added.