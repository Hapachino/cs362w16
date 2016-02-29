/********************************************************************************
*	David Vogel
*	CS362 Assignment 2: refactor.c
*	Due: 1/17/16
*	Assignment Requirements:
*		- Pick five cards implemented in dominion.c.
*		- Choose 3 cards of your choice; smithy and adventurer cards are mandatory.
*		- Refactor the code so that these cards are implemented in their own functions, 
*			rather than as part of the switch statement in cardEffect.
*		- You should call the functions for these cards in the appropriate place in cardEffect. 	
*		- Check in your changes, with appropriate git commit messages. 
*		- Document your changes in a text file in your dominion source directory, called “refactor.c.”
*		- Your implementation of at least 4 of these 5 cards should be incorrect in some way, 
*			i.e., you should introduce subtle bugs that are hard to catch in your changes.
*		- Introducing bugs in smithy and adventurer is mandatory.
*		- Write information of your bugs also in refactor.c
*		- Later in this class, other students will test your code, so try to keep your bugs not superficial.
*		- Refactored program should compile without any error.
********************************************************************************/

Refactored Cards:
	adventurer, smithy, feast, remodel, and baron

Changes:
	dominion.h: Function prototypes for refactored cards
		int playAdventurer(struct gameState *state, int currentPlayer);
		int playSmithy(struct gameState *state, int handPos, int currentPlayer);
		int playFeast(struct gameState *state, int currentPlayer, int choice1);
		int playRemodel(struct gameState *state, int currentPlayer, int choice1, int choice2, int handPos);
		int playBaron(struct gameState *state, int currentPlayer, int choice1);

	dominion.c: Function definitions for refactored cards. New functions are called in cardEffect() switch statement
		Refactored functions are defined right before the cardEffect() function

Bugs Introduced:
	playAdventurer(): in the if statement for cardDrawn, changed the drawntreasure increment from ++ to +=2
	
	playSmithy(): changed end of for loop from i<3 to i<=3

	playFeast(): changed else if statement in the buy card while loop:
		was:
			else if (state->coins < getCost(choice1))
		changed to:
			else if (state->coins <= getCost(choice1))

	playRemodel(): changed if condition:
		was:
			if ((getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2))
		changed to:
			if ((getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2))