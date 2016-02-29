#include "dominion_helpers.h"
#include <stdio.h>

int main() {

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	const int numberOfPlayers = 2;
	struct gameState game;
	
	// initialize game
	printf("initialize game result: %d\n", initializeGame(numberOfPlayers , k , 1, &game) );
	// is Game over
	printf("Game is over state %d\n", isGameOver(&game));
	//whose turn
	printf("Who is turn %d\n", whoseTurn(&game));
	//Number of cards in current player
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//Score the first player
	printf("Score for the first player %d\n", scoreFor(0, &game));
	//Smithy Card
	printf("Playing smithy %d\n", playSmithy(&game, 0));
	//Number of Cards on hand
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//Score for the first player
	printf("Score for the first player %d\n", scoreFor(0, &game));
	//End turn
	printf("Ending turn %d\n", endTurn(&game));
	//Play Smithy Card
	printf("Playing smithy %d\n", playSmithy(&game, 0));
	//#of Cards
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//Score for the first player
	printf("Score for the first player %d\n", scoreFor(0, &game));
	printf("************************************\n");
	//whose turn
	printf("Who is turn %d\n", whoseTurn(&game));
	//game is over state
	printf("Game is over state %d\n", isGameOver(&game));
	
	return 0;
}