Name:	Ian Bender
Course:	CS362
Assignment 2 - Refactoring dominion code.

int playAdventurer(int currentPlayer, struct gameState *state)
Bugs: 
    line 658: moved } to line below drawCard, should be below shuffle
    line 669: Changed while(z-1>=0) to while(z-1>0)
	

int playSmithy(int currentPlayer, struct gameState *state, int handPos)
Bugs:
    line 681: changed < to > in for loop


int playCouncil_room(int currentPlayer, struct gameState *state, int handPos)
Bugs:


int playMine(int currentPlayer, struct gameState *state, int handPos,
            int choice1, int choice2)
Bugs:
    line 749: reversed i and j in comparison,
              should be [currentPlayer][i] == j
    line 752: commented out break statement


int playRemodel(int currentPlayer, struct gameState *state, int handPos,
            int choice1, int choice2)
Bugs:
    line 773: calling gainCard twice
    line 779: changed comparison from i < state.. to i <= state..




