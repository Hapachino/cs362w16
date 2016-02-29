#include "dominion_helpers.h"
#include <stdio.h>

/*
 Test plan:
 Create game
 Initialize
 Check if game is over
 Who is turn
 Buy card
 Check number of cards in hand
 Get player score
 Gain extra card
 Check number of cards in game
 Get player score


*/

int main() {

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	const int numberOfPlayers = 2;
	struct gameState game;

    //initiliaze game 
	printf("initialize game result: %d\n", initializeGame(numberOfPlayers , k , 1, &game) );
	printf("Game is over state %d\n", isGameOver(&game));
	//whose turn
	printf("Who is turn %d\n", whoseTurn(&game));
	//#of cards
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//buy a card for the first player
	printf("Buying a card for the first player %d\n", 	buyCard(0, &game));
	//#of cards
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//buy cards for the first player
	printf("Buying a card for the first player %d\n", 	buyCard(1, &game));
	printf("Buying a card for the first player %d\n", 	buyCard(2, &game));
	printf("Buying a card for the first player %d\n", 	buyCard(3, &game));
	printf("Buying a card for the first player %d\n", 	buyCard(4, &game));
	////play a card
	printf("Playing a card for the first player %d\n", 	playCard(0, adventurer, gardens, embargo, &game));
	//score for the first player
	printf("Score for the first player %d\n", scoreFor(0, &game));
	//gain a card
	printf("Gaining a card %d\n", gainCard(0, &game, 0, 0));
	//# of cards in current player
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//score
	printf("Score for the first player %d\n", scoreFor(0, &game));
	printf("************************************\n");
	//whose turn
	printf("Who is turn %d\n", whoseTurn(&game));
	//game is over turn
	printf("Game is over state %d\n", isGameOver(&game));
	printf("Ending first player turn %d\n", endTurn(&game));;	
	printf("************************************\n");
	printf("Game is over state %d\n", isGameOver(&game));
	
	return 0;
}






















