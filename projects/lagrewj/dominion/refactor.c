/*Jonathan Lagrew
CS 362 Winter 2016
Assignment 2

Pick five cards implemented in dominion.c. Choose 3 cards of your choice and smithy and adventurer cards are mandatory. 
Refactor the code so that these cards are implemented in their own functions, rather than as part of the switch statement in cardEffect. 
You should call the functions for these cards in the appropriate place in cardEffect. Check in your changes, with appropriate git commit messages. 
Document your changes in a text file in your dominion source directory, called “refactor.c.” Your implementation of at least 4 of these 5 cards 
should be incorrect in some way, i.e., you should introduce subtle bugs that are hard to catch in your changes. Introducing bugs in smithy and adventurer is mandatory. 
Write information of your bugs also in refactor.c  Later in this class, other students will test your code, so try to keep your bugs not superficial. 
Refactored program should compile without any error.

Documented Changes:

Smithy:
new function: playSmithy
Notes: Changed from 3 cards drawn to only 2. 

adventurer:
new function: playAdventurer
Notes: commented out z++ from else statement in first while loop so that z will not increment, thus in the second while loop not all cards drawn will be discarded

remodel:
new function: playRemodel
Notes: Changed last parameter in function from 0 to 1. In turn, this sets the trash flag to put the card in the trash pile instead 
	   of the discard pile, thus removing it from play. 
	   
	  //discard card from hand
      discardCard(handPos, currentPlayer, state, 1);

village:
new function: playVillage
Notes: Changed number of actions village card gives from 2 to 1. 
	  //+2 Actions
	  state->numActions = state->numActions + 1;
	  
great_hall:
new function: playGreat_Hall
Notes: Opposite of village bug, new great hall increases actions by 2 instead of 1. 
	  //+1 Actions
	  state->numActions + 2;
*/
