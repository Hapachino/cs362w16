#include "dominion.h"
#include "test_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//For printing card names 
const char* Card_Strings[] = {"curse", "estate", "duchy", "province", "copper", "silver" ,
  "gold", "adventurer", "council_room", "feast", "gardens", "mine", "remodel", "smithy", 
  "village", "baron", "great_hall", "minion", "steward", "tribute", "ambassador", "cutpurse", 
  "embargo", "outpost", "salvager", "sea_hag", "treasure_map"};
  
//Create a gameState with random, but valid, values
struct gameState* randomGame(int randInt){
	int i, j;
	int numCards = 0;
	int selectedCard;
	struct gameState* g = malloc(sizeof(struct gameState));
	
	//Seed random number generator
	SelectStream(randInt+1);
	PutSeed(randInt+2);
	
	//Random players between 1 and MAX
	g->numPlayers = ceil(Random() * MAX_PLAYERS);
	if (g->numPlayers == 0){   //handle special case where Random returns exactly 0
		g->numPlayers = 1;
	}
	
	//--Set supplyCount for all cards
	//Victory cards
	g->supplyCount[curse] = floor(Random() * MAX_CURSE);
	g->supplyCount[estate] = floor(Random() * MAX_VICTORY);
	g->supplyCount[duchy] = floor(Random() * MAX_VICTORY);
	g->supplyCount[province] = floor(Random() * MAX_VICTORY);
	
	//Treasure cards
	g->supplyCount[copper] = floor(Random() * MAX_TREASURE);
	g->supplyCount[silver] = floor(Random() * MAX_TREASURE);
	g->supplyCount[gold] = floor(Random() * MAX_TREASURE);
	
	//Action Cards
	//Mark all cards unselected (supplyCount = -1)
	for (i = adventurer; i <= treasure_map; i++){
		g->supplyCount[i] = -1;
	}
	//Select 10 random cards for game and set supply to random value
	while (numCards < 10){
		selectedCard = (floor(Random() * (treasure_map - adventurer))) + adventurer;
		//if not already selected, set supply count and increment loop control
		if (g->supplyCount[selectedCard] == -1){
			g->supplyCount[selectedCard] = floor(Random() * MAX_ACTION);
			numCards++;
		}
	}
	//---end set supplyCount
	
	//Set embargoTokens for supply piles
	//set random embargo for all victory and treasure cards
	for (i = 0; i < adventurer; i++){
		g->embargoTokens[i] = floor(Random() * MAX_EMBARGO);
	}
	//set random embergo for kingdom cards only if they are part of game
	for (i = adventurer; i <= treasure_map; i++){
		if (g->supplyCount[i] == -1){
			g->embargoTokens[i] = 0;
		} else {
			g->embargoTokens[i] = floor(Random() * MAX_EMBARGO);
		}
	}
	
	//Set turn values
	g->outpostPlayed = floor(Random());
	g->outpostTurn = 0;
	g->whoseTurn = floor(Random() * (g->numPlayers-1));
	g->phase = floor(Random());
	g->numActions = floor(Random() * 3);
	g->coins = floor(Random() * MAX_COINS);
	g->numBuys = floor(Random() * 3);
	
	//Set hand values
	//Set random handCount for each player
	for (i = 0; i < g->numPlayers; i++){
		g->handCount[i] = floor(Random() * MAX_DECK);
	}
	//Fill each player's hand with correct amount of random cards
	for (i = 0; i < g->numPlayers; i++){
		for (j = 0; j < g->handCount[i]; j++){
			g->hand[i][j] = floor(Random() * treasure_map);
		}
	}
	
	//Set deck values
	//Set random deckCount for each player
	for (i = 0; i < g->numPlayers; i++){
		g->deckCount[i] = floor(Random() * MAX_DECK);
	}
	//Fill each player's deck with correct amount of random cards
	for (i = 0; i < g->numPlayers; i++){
		for (j = 0; j < g->deckCount[i]; j++){
			g->deck[i][j] = floor(Random() * treasure_map);
		}
	}	
	
	//Set discard values
	//Set random discardCount for each player
	for (i = 0; i < g->numPlayers; i++){
		g->discardCount[i] = floor(Random() * MAX_DECK);
	}
	//Fill each player's discard pile with correct amount of random cards
	for (i = 0; i < g->numPlayers; i++){
		for (j = 0; j < g->discardCount[i]; j++){
			g->discard[i][j] = floor(Random() * treasure_map);
		}
	}	
	
	//Set played values
	g->playedCardCount = floor(Random() * MAX_DECK);
	for (i = 0; i < g->playedCardCount; i++){
		g->playedCards[i] = floor(Random() * treasure_map);
	}
	
	//Random setup complete
	return g;
}

//Print current game state
void printGameState(struct gameState *g){
	
	int i, j;
	
	printf("Number of players: %d\n", g->numPlayers);
	printf("-------------\n");
	
	printf("Supply Counts:\n");
	for (j = 0; j <= treasure_map; j++){
		if (g->supplyCount[j] > 0){
			printf("%s: %d\n", Card_Strings[j], g->supplyCount[j]);
		}
	}
	printf("-------------\n");
	
	printf("Embargo Tokens:\n");
	for (j = 0; j <= treasure_map; j++){
		if (g->embargoTokens[j] > 0){
			printf("%s: %d\n", Card_Strings[j], g->embargoTokens[j]);
		}
	}
	printf("-------------\n");
	
	printf("Current Turn:\n");
	printf("Outpost Played: %d\n", g->outpostPlayed);
	printf("Outpost Turn: %d\n", g->outpostTurn);
	printf("Who's Turn: %d\n", g->whoseTurn);
	printf("Turn Phase: %d\n", g->phase);
	printf("Number of Actions: %d\n", g->numActions);
	printf("Number of Coins: %d\n", g->coins);
	printf("Number of Buys: %d\n", g->numBuys);
	printf("-------------\n");
	
	for (i = 0; i < g->numPlayers; i++){
		printf("Player %d's Hand:\n", i);
		for (j = 0; j < g->handCount[i]; j++){
			printf("%s\t", Card_Strings[g->hand[i][j]]);
		}	
		printf("\n");
	}
	printf("-------------\n");
	
	for (i = 0; i < g->numPlayers; i++){
		printf("Player %d's Deck:\n", i);
		for (j = 0; j < g->deckCount[i]; j++){
			printf("%s\t", Card_Strings[g->deck[i][j]]);
		}	
		printf("\n");
	}
	printf("-------------\n");
	
	for (i = 0; i < g->numPlayers; i++){
		printf("Player %d's Discard Pile:\n", i);
		for (j = 0; j < g->discardCount[i]; j++){
			printf("%s\t", Card_Strings[g->discard[i][j]]);
		}	
		printf("\n");
	}
	printf("-------------\n");
	
	printf("Played Cards:\n");
	for (i = 0; i < g->playedCardCount; i++){
		printf("%s\t", Card_Strings[g->playedCards[i]]);
	}	
	printf("\n");
	printf("-------------\n");
	
	return;
}