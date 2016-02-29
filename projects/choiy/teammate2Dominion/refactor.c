Charles Hardes
CS 362 Winter 2016
Assignment 2

refactoredAdventurer(struct gameState *state, int handpos):

Changes: while loop at end: while (z-1>=0) now is : while (z-1>0). Loop will exit too quickly, failing to discard every card required

refactoredVillage(struct gameState *state, int handPos):

Changes: trashCard flag in discardCard() set to 1. The card gets trashed instead of discarded

refactoredSmithy(struct gameState *state, int handPos):

Changes: discards handPos + 1 instead of handPos. Wrong card gets discarded

refactoredGreatHall(struct gameState *state, int handPos):

Changes: discards handPos + 1 instead of handPos. Wrong card gets discarded

refactoredGardens():

Changes: simply returns -1 (correct behavior)
