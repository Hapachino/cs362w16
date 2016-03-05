#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Test update Coins

//Helper function to count coins in player Hand. Does not include bonus coins.
int _countCoins(struct gameState *g, int player)
{
	int coins = 0;
	int i;
	int cardCount = g->handCount[player];
	for(i = 0; i <= cardCount; i++)
	{
		if(g->hand[player][i] == 4)
		{
			coins+=1;
		}
		else if(g->hand[player][i] == 5)
		{
			coins+=2;
		}
		else if(g->hand[player][i] == 6)
		{
			coins+=3;
		}
	}
	return coins;
}

void _setCoins(struct gameState *g, int player)
{
	int i;
	g->handCount[player] = 12;
	int coins;
	for(i=0; i<= 11; i++)
	{
		if(i<=3)
		{
			g->hand[player][i] = 4;
		}
		else if(i<=7)
		{
			g->hand[player][i] = 5;
		}
		else
		{
			g->hand[player][i] = 6;
		}
	}
}

//Set player hand to empty. Set coinState to 0.
void _zeroHand(struct gameState *g, int player)
{
	int i;
	for(i=0;i<g->handCount[player];i++)
	{
		g->hand[player][i] = -1;
	}
	g->handCount[player] = 0;
	g->coins=0;
}
void testHand(struct gameState *g, int player)
{
//	_setCoins(g,player);
//	g->handCount[player] = 12;
//	updateCoins(player,g,0);


//	int coinsUpdate = g->coins;
//	int testCoins = _countCoins(g,player);
	_zeroHand(g,player);	
	updateCoins(player,g,0);
	int coinsUpdate = g->coins;
	int testCoins = _countCoins(g,player);

	printf("\n\n\tTesting updateCoins for empty player hand\n\n");
	if(coinsUpdate != testCoins)
	{		
		printf("Error. Total number of coins in hand is not included in coins state for player %d! Coins in hand = %d. Coins in coinState = %d\n",player,testCoins,coinsUpdate);
	}
	else
	{
		printf("Success! Total number of coins for player %d is %d and coin state is %d\n",player,testCoins,coinsUpdate);
	}

	_setCoins(g,player);
	g->handCount[player] = 12;
	updateCoins(player,g,0);

	coinsUpdate = g->coins;
	testCoins = _countCoins(g,player);

	printf("\n\n\tTesting updateCoins without Bonus Coins\n\n");
	if(coinsUpdate != testCoins)
	{
		printf("Error. Total number of coins in hand is not included in coins state for player %d! Coins in hand = %d. Coins in coinState = %d\n",player,testCoins,coinsUpdate);
	}
	else
	{
		printf("Success! Total number of coins for player %d is %d and coin state is %d\n",player,testCoins,coinsUpdate);
	}

	printf("\n\n\tTesting updateCoins with 500 Bonus Coins!!\n\n");
	updateCoins(player,g,500);
	testCoins = testCoins+500;
	coinsUpdate = g->coins;
	
	if(coinsUpdate != testCoins)
	{
		printf("Error. Total number of coins in hand is not included in coins state for player %d! Coins in hand = %d. Coins in coinState = %d\n",player,testCoins,coinsUpdate);
	}
	else
	{
		printf("Success! Total number of coins for player %d is %d and coin state is %d\n",player,testCoins,coinsUpdate);
	}

	printf("\n\n\tTesting updateCoins with 1000 Bonus Coins!!\n\n");
	updateCoins(player,g,1000);
	testCoins = testCoins+500;
	coinsUpdate = g->coins;
	
	if(coinsUpdate != testCoins)
	{
		printf("Error. Total number of coins in hand is not included in coins state for player %d! Coins in hand = %d. Coins in coinState = %d\n",player,testCoins,coinsUpdate);
	}
	else
	{
		printf("Success! Total number of coins for player %d is %d and coin state is %d\n",player,testCoins,coinsUpdate);
	}

	printf("\n\n\tTesting updateCoins with 1500 Bonus Coins!!\n\n");
	updateCoins(player,g,1500);
	testCoins = testCoins+500;
	coinsUpdate = g->coins;
	
	if(coinsUpdate != testCoins)
	{
		printf("Error. Total number of coins in hand is not included in coins state for player %d! Coins in hand = %d. Coins in coinState = %d\n",player,testCoins,coinsUpdate);
	}
	else
	{
		printf("Success! Total number of coins for player %d is %d and coin state is %d\n",player,testCoins,coinsUpdate);
	}

	printf("\n\n\tTesting updateCoins with negative 1500 Bonus Coins!!\n\n");
	updateCoins(player,g,-1500);
	testCoins = testCoins+-3000;
	coinsUpdate = g->coins;
	
	if(coinsUpdate != testCoins)
	{
		printf("Error. Total number of coins in hand is not included in coins state for player %d! Coins in hand = %d. Coins in coinState = %d\n",player,testCoins,coinsUpdate);
	}
	else	
	{
		printf("Success! Total number of coins for player %d is %d and coin state is %d\n",player,testCoins,coinsUpdate);
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
	printf("\n\nUpdate Coins test\n\n");
	testHand(&postState,player);
	printf("\n\n\tCoins update complete\n\n");
}

