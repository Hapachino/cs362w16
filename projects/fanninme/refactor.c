#Fanninme 
#Note: this is not code but rather documentation please ignore .c file type.
#Refactor.c describes refactoring done to create functions for Smithy,Adventurer and other cards additionally documenting bugs which were added to these functions.

//#Adventurer
Function:
Removed variable z, cardDrawn and drawntreasure from cardEffect and incorported them into the adventurer function.The variable extraCardsCount replaces z as a counter and drawn treasures is initialized to 0. 
The parameters of the function are a pointer to the state and the current player
Bugs:
line 653 :[state->handCount[currentPlayer]-1]; changed to
[state->handCount[currentPlayer]]; 

//#
Function:
Bugs:

//#
Function:
Bugs:

//#
Function:
Bugs:

//#Smithy
Function:
Bugs:
