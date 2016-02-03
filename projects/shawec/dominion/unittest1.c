/* -----------------------------------------------------------------------
 * Cierra Shawe 
 * CS362 - W16
 * Unit test 1, testing updateCoins
 * Tests for hand of all cooper, silver, and gold, 
 * Then mixed copper, silver, and gold, 
 * And finally it tests for a mix of cards.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set VERBOSE to 0 to remove printfs from output
#define VERBOSE 0

int main() {
	
	//Things needed to init game
	struct gameState Game;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int seed = 1234;
	int players = 2;
	
	// Other Variables
	int i;
	int maxBonus = 10;
	int player;
	int handCount;
	int bonus;
	int maxHand = 7;
	int count = 0;
	int var1;
	int var2;
	
	printf ("Testing updateCoins():\n");
	for (player = 0; player < players; player++) {
		for (handCount = 1; handCount <= maxHand; handCount++){
			for (bonus = 0; bonus <= maxBonus; bonus++) {
				
#if (VERBOSE == 1)
				printf("Test player %d with %d treasure card(s) and %d bonus.\n", player, handCount, bonus);
#endif				
				/* Set Up */
				// clear the game state
				memset(&Game, 23, sizeof(struct gameState));
				// initialize a new game   
				initializeGame(players, k, seed, &Game);
				// set the number of cards on hand
				Game.handCount[player] = handCount;
				assert(Game.handCount[player] == handCount);
				
				/* Tests */
				//All copper
				count = bonus;
				for (i = 0; i < handCount; i ++) {
					Game.hand[player][i] = copper;
					count += 1;
				}
				updateCoins(player, &Game, bonus);
				
#if (VERBOSE == 1)
				printf("Copper: coins = %d, expected = %d\n", Game.coins, count);
#endif
				assert(Game.coins == count);
				
				//All Silver
				count = bonus;
				for (i = 0; i < handCount; i ++) {
					Game.hand[player][i] = silver;
					count += 2;
				}
				updateCoins(player, &Game, bonus);
				
#if (VERBOSE == 1)
				printf("All Silvercoins = %d, expected = %d\n", Game.coins, count);
#endif				
				assert(Game.coins == count);
				
				//All Gold
				count = bonus;
				for (i = 0; i < handCount; i ++) {
					Game.hand[player][i] = gold;
					count += 3;
				}
				updateCoins(player, &Game, bonus);
				
#if (VERBOSE == 1)
				printf("All gold: coins = %d, expected = %d\n", Game.coins, count);
#endif
				assert(Game.coins == count);
				
				//Mixed Just coins
				count = bonus;
				for (i = 0; i < handCount; i ++) {
					var1 = (int)(Random() * 3) + 1;
					
					if (var1 == 1){
						Game.hand[player][i] = copper;
						count += 1;
					}
					
					if (var1 == 2){
						Game.hand[player][i] = silver;
						count += 2;
					}
					
					if (var1 == 3){
						Game.hand[player][i] = gold;
						count += 3;
					}
				}
				updateCoins(player, &Game, bonus);
				assert(Game.coins == count);
				
				// Mixed Cards
				count = bonus;
				for (i = 0; i < handCount; i ++) {
					var1 = (int)(Random() * 3) + 1; // gives rand number
					var2 = (int)(Random() * 2); // for Bool of card or coin
					//If card 
					if (var2 == 0) {
						var2 = (int)(Random() * 10); //should have own var, oh well
						Game.hand[player][i] = k[var2];
						
					}
					// If coin
					else {
						if (var1 == 1){
							Game.hand[player][i] = copper;
							count += 1;
						}
					
						if (var1 == 2){
							Game.hand[player][i] = silver;
							count += 2;
						}
					
						if (var1 == 3){
							Game.hand[player][i] = gold;
							count += 3;
						}
					}
				}
				updateCoins(player, &Game, bonus);
				assert(Game.coins == count);
				
			}
		}
	}

	printf("Woot woot, everything passed for unittest1!!\n");

	return 0;
}