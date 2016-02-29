/*************************************************
 * 
 * Todd Waddell
 * CS362W16
 * Assignment #2
 *
 * 3- (60 points) Pick five cards implemented in dominion.c. Choose 3 cards
 * of your choice and smithy and adventurer cards are mandatory. Refactor
 * the code so that these cards are implemented in their own functions,
 * rather than as part of the switch statement in cardEffect. You should
 * call the functions for these cards in the appropriate place in
 * cardEffect. Check in your changes, with appropriate git commit messages.
 * Document your changes in a text file in your dominion source directory,
 * called “refactor.c.” Your implementation of at least 4 of these 5 cards
 * should be incorrect in some way, i.e., you should introduce subtle bugs
 * that are hard to catch in your changes. Introducing bugs in smithy and
 * adventurer is mandatory.  Write information of your bugs also in
 * refactor.c  Later in this class, other students will test your code, so
 * try to keep your bugs not superficial. Refactored program should compile
 * without any error.
 * **********************************************/
//Refactoring Changes & Bugs Introduced

int adventureEffect(struct gameState *state);
//Bug introduced: changed first while loop condition to (drawntreasure <=2)
//Additional refactoring: removed the second while loop, which was
//responsible for discarding the drawn cards.  Combined that with the else
//branch in the initial while loop.

int smithyEffect(struct gameState *state, int handPos);
//Bug introduced: in refactor.c:75, changed trash flag to 1.

int feastEffect(int choice1, struct gameState *state);
//Bug introduced: in refactor.c:93, changed upate coins to 4. 

int cutpurseEffect(struct gameState *state, int s);
//Bug introduced: in refactor.c:191 changed coin from copper to gold.
