#include "dominion_helpers.h"
#include <stdio.h>

/*
   Test plan:
1.Create game
2.Initialize
3.Check if game is over
4.Who is turn
5.Update coins, change player, check result for several times

*/

int main() {
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	const int numberOfPlayers = 2;
	struct gameState game;
	//Initialize game 
	printf("initialize game result: %d\n", initializeGame(numberOfPlayers , k , 1, &game) );
	//game is over?
	printf("Game is over state %d\n", isGameOver(&game));
	//whose turn
	printf("Who is turn %d\n", whoseTurn(&game));
	//#of cards in current player hand
	printf("Number of cards in current player hand %d\n", numHandCards(&game));
	//update coins
	printf("Updating coins %d\n", updateCoins(0, &game, 100));
	printf("Coins in game %d\n", game.coins);
	//end turn
	printf("Ending turn %d\n", endTurn(&game));
	//update coins
	printf("Updating coins %d\n", updateCoins(0, &game, 50));
	printf("Coins in game %d\n", game.coins);
	printf("Ending turn %d\n", endTurn(&game));
	//update coins
	printf("Updating coins %d\n", updateCoins(0, &game, 25));
	printf("Coins in game %d\n", game.coins);
	printf("Ending turn %d\n", endTurn(&game));	
	//update coins
	printf("Updating coins %d\n", updateCoins(0, &game, 1));
	printf("Coins in game %d\n", game.coins);
	printf("Ending turn %d\n", endTurn(&game));	
	printf("************************************\n");
	printf("Game is over state %d\n", isGameOver(&game));
	
	return 0;
}

