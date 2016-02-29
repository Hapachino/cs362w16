#include "dominion_helpers.h"
#include <stdio.h>

int main() {
	
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	const int numberOfPlayers = 2;
	struct gameState game;
	
	//Initialize the game
	printf("initialize game result: %d\n", initializeGame(numberOfPlayers , k , 1, &game) );
	// Game is over state
	printf("Game is over state %d\n", isGameOver(&game));
	//Get whose turn
	printf("Who is turn %d\n", whoseTurn(&game));
	//#of cards
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//Score
	printf("Score for the first player %d\n", scoreFor(0, &game));
	//Village Card
	printf("Playing village %d\n", playVillage(&game, 0));
	//#of Cards
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//Score for the first player
	printf("Score for the first player %d\n", scoreFor(0, &game));
	//End turn
	printf("Ending turn %d\n", endTurn(&game));
	//Play village
	printf("Playing village %d\n", playVillage(&game, 0));
	//#of cards
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//Score
	printf("Score for the first player %d\n", scoreFor(0, &game));
	printf("************************************\n");
	//Whose turn
	printf("Who is turn %d\n", whoseTurn(&game));
	//Game is over
	printf("Game is over state %d\n", isGameOver(&game));
	
	return 0;
}

