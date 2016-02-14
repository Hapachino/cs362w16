#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Draw Card Test


void countCheck(struct gameState *preState, struct gameState *postState, int player)
{
	int drawCountCheck = postState->deckCount[player] - preState->deckCount[player];
	if( drawCountCheck != -1)
	{
		printf("\nError updating deckCount. Returned value %d should be %d\n",drawCountCheck,preState ->deckCount[player]-1);
	}
	else
	{
		printf("Passed deckCount check\n");
	}
}

void deckCheck(struct gameState *preState, struct gameState *postState, int player)
{
	int postCount = postState->deckCount[player];
	int i;
	int flag = 0;
	for(i = 0; i <= postCount; i++)
	{
		if(postState->deck[player][i] != preState->deck[player][i])
		{
			flag = 1;
			printf("Error. Card at position %d in deck has been changed.\n",i);
		}
	}
	if(flag == 0)
	{
		printf("Passed deck check\n");
	}
}

void checkCard(struct gameState *preState, struct gameState *postState, int player)
{
	if(preState->deck[player][preState->deckCount[player]-1] != postState->hand[player][postState->handCount[player]-1])
	{
		printf("Error, did not draw top card from deck\n");
	}
	else
	{
		printf("Passed checkCard. Drew top card from deck\n");
	}
}
int main()
{
	int i;
        int seed = 1000;
        int numPlayers = 2;
        int player  = 0;
        struct gameState preState, postState;
        int k[10] = {adventurer, council_room, feast, gardens, mine ,remodel, smithy, village, baron, great_hall};
        initializeGame(numPlayers,k,seed,&postState);
	memcpy(&preState,&postState,sizeof(struct gameState));
	//Check Draw with deckCount > drawCount
	printf("\n\nDrawCard test\n\n");
	printf("\nTesting drawCard for deckCount > drawCount\n");
	drawCard(player,&postState);
	printf("\nTesting deckCount\n");
	countCheck(&preState,&postState,player);
	printf("\nTesting deck for prohibited alterations\n");
	deckCheck(&preState,&postState,player);
	printf("\nTesting drawn card to see if it came from top of deck\n");
	checkCard(&preState,&postState,player);
	printf("\n\n\t\tPassed three cases for deckCount > drawCount. Examining deckCount < drawCount (shuffle occurs)\n\n");
	for(i = 0; i < postState.deckCount[player]; i++)
	{
		drawCard(player,&postState);
		postState.discard[player][i] = 1;
		postState.discardCount[player]++;
	}
	memcpy(&preState,&postState,sizeof(struct gameState));
	drawCard(player,&postState);
	printf("\nTesting deckCount\n");
	countCheck(&preState,&postState,player);
	printf("\nTesting deck for prohibited alterations\n");
	deckCheck(&preState,&postState,player);
	printf("\nTesting drawn card to see if it came from top of deck\n");
	checkCard(&preState,&postState,player);
	printf("\nPassed three cases for deckCount > drawCount. Examining deckCount < drawCount\n");
	printf("\n\n\t\tTest Complete\n\n");
}
