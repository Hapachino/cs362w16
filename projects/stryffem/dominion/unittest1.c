/*
*	updateCoins() unit testing
*	Initializes a gamestate, then tests update coins with a hand full of each
*	treasure type and a range of bonuses for each player. 
*
*	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main()
{
	int i;
	int seed = 1000;
	int numPlayer = 2;
	int maxBonus = 10;
	int player, handCount;
	int bonus;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState state;
	int maxHandCount = 5;

	//Initialize arrays of coppers, silvers, and golds
	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];
	for(i = 0; i < MAX_HAND; i++)
	{
		coppers[i] = copper;
		silvers[i] = silver;
		golds[i] = gold;
	}

	printf("\nTESTING updateCoins():\n");
	for(player = 0; player < numPlayer; player++)
	{
		for(handCount = 1; handCount <= maxHandCount; handCount++)
		{
			for(bonus = 0; bonus <= maxBonus; bonus++)
			{
				printf("\nTest player %d with %d treasure card(s) and %d bonus.\n", player, handCount, bonus);

				memset(&state, 23, sizeof(struct gameState));					//Clear the game state
				initializeGame(numPlayer, k, seed, &state);						//Initialize a new game
				state.handCount[player] = handCount;							//Set number of cards in hand
				
				memcpy(state.hand[player], coppers, sizeof(int)*handCount);		//Set all cards to copper
				updateCoins(player, &state, bonus);

				if(state.coins == handCount * 1 + bonus)
					printf("PASS: state.coins = %d, expected = %d\n", state.coins, handCount * 1 + bonus);
				else
					printf("FAIL: state.coins = %d, expected = %d\n", state.coins, handCount * 1 + bonus);
				
				memcpy(state.hand[player], silvers, sizeof(int)*handCount);		//Set all cards to silver
				updateCoins(player, &state, bonus);

				if(state.coins == handCount * 2 + bonus)
					printf("PASS: state.coins = %d, expected = %d\n", state.coins, handCount * 2 + bonus);
				else
					printf("FAIL: state.coins = %d, expected = %d\n", state.coins, handCount * 2 + bonus);

				memcpy(state.hand[player], golds, sizeof(int)*handCount);		//Set all cards to gold
				updateCoins(player, &state, bonus);

				if(state.coins == handCount * 3 + bonus)
					printf("PASS: state.coins = %d, expected = %d\n", state.coins, handCount * 3 + bonus);
				else
					printf("FAIL: state.coins = %d, expected = %d\n", state.coins, handCount * 3 + bonus);

			}
		}
	}

	return 0;
}