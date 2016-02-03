#include "dominion.h"
#include <stdio.h>

/* 
  Test plan:
  1.Create game
  2.Initialize
  3.Check if game is over
  4.Who is turn
  5.Try to play any card
*/


int main(){

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	const int numberOfPlayers = 2;
	struct gameState game;
    // initiliaze game result
	printf("initialize game result: %d\n", initializeGame(numberOfPlayers , k , 1, &game) );
	// game is over state
	printf("Game is over state %d\n", isGameOver(&game));
	//whose turn
	printf("Who is turn %d\n", whoseTurn(&game));
	//#of cards
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//# of cards
	printf("Playing a card for the first player %d\n", 	playCard(1, 2, 2, 2, &game));
	printf("************************************\n");
	//whose turn
	printf("Who is turn %d\n", whoseTurn(&game));
	//is game over
	printf("Game is over state %d\n", isGameOver(&game));
	//end turn 
	printf("Ending first player turn %d\n", endTurn(&game));
	
	return 0;
}