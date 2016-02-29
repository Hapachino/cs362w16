#include "dominion_helpers.h"
#include <stdio.h>

/*
Test plan:
  Create game
  Initialize
  For each player do the next:
  Check if the game is over
  Check number of cards
  Check score
  Play adventure / Smithy game
  Check the score
  Check number of cards
  Check if the game is over

*/

int main() {
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	const int numberOfPlayers = 2;
	struct gameState game;
	
	//initialize the game 
	printf("initialize game result: %d\n", initializeGame(numberOfPlayers , k , 1, &game) );
	printf("************************************\n");
	printf("Game is over state %d\n", isGameOver(&game));
	//whose turn
	printf("Who is turn %d\n", whoseTurn(&game));
	//# of cards
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//score for the first player
	printf("Score for the first player %d\n", scoreFor(0, &game));
	//Play adventurer
	printf("Playing adventurer for the first player %d\n", playAdventurer(&game));
	//#of cards
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//print the score
	printf("Score for the first player %d\n", scoreFor(0, &game));
	//end the turn for the player
	printf("Ending first player turn %d\n", endTurn(&game));
	printf("************************************\n");
	//print gavemis over state
	printf("Game is over state %d\n", isGameOver(&game));
	//whose turn
	printf("Who is turn %d\n", whoseTurn(&game));
	//# of cards
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//Get the score for the second player
	printf("Score for the second player %d\n", scoreFor(1, &game));
	//play adventurer for the second player
	printf("Playing adventurer for the second player %d\n", playAdventurer(&game));
	//# of cards in current hand
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//Score for the player
	printf("Score for the second player %d\n", scoreFor(1, &game));
	//end turn
	printf("Ending second player turn %d\n", endTurn(&game));
	printf("************************************\n");
	printf("Game is over state %d\n", isGameOver(&game));
	//get whose turn
	printf("Who is turn %d\n", whoseTurn(&game));
	//#of cards
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//score for the palyer
	printf("Score for the first player %d\n", scoreFor(0, &game));
	//play smithy card
	printf("Playing smithy for the first player %d\n", playSmithy(&game, 0));
	//#of cards
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//get the score for the current player
	printf("Score for the first player %d\n", scoreFor(0, &game));
	printf("Ending first player turn %d\n", endTurn(&game));
	printf("************************************\n");
	// game is over state
	printf("Game is over state %d\n", isGameOver(&game));
	//get whose turn
	printf("Who is turn %d\n", whoseTurn(&game));
	//#of cards
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//get the score for the second player
	printf("Score for the second player %d\n", scoreFor(1, &game));
	//smithy card for the current player
	printf("Playing smithy for the second player %d\n", playSmithy(&game, 4));
	//# of cards
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//get the score
	printf("Score for the second player %d\n", scoreFor(1, &game));
	//end Turn
	printf("Ending second player turn %d\n", endTurn(&game));
	
	return 0;
}

