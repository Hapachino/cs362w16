#include "dominion_helpers.h"
#include <stdio.h>

int main() {
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	const int numberOfPlayers = 2;
	struct gameState game;
	
	printf("initialize game result: %d\n", initializeGame(numberOfPlayers , k , 1, &game) );
	printf("Game is over state %d\n", isGameOver(&game));
	printf("Who is turn %d\n", whoseTurn(&game));
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	printf("Score for the first player %d\n", scoreFor(0, &game));
	printf("Playing adventurer %d\n", playAdventurer(&game));
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	printf("Score for the first player %d\n", scoreFor(0, &game));
	printf("Ending turn %d\n", endTurn(&game));
	printf("Playing adventurer %d\n", playAdventurer(&game));
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	printf("Score for the first player %d\n", scoreFor(0, &game));
	printf("************************************\n");
	printf("Who is turn %d\n", whoseTurn(&game));
	printf("Game is over state %d\n", isGameOver(&game));
	
	return 0;
}