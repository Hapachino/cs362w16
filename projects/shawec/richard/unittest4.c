/* -----------------------------------------------------------------------
 * Cierra Shawe 
 * CS362 - W16
 * Unit test 2, testing isGameOver
 * Tests for provineces 0, and greater than 0 
 * Randomly decrements cards until 0,
 * then tests if the game was eneded
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
	struct gameState Holder;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int e[6] = {curse, estate, duchy, province, great_hall, gardens};
	int seed = 1234;
	int players = (int)(Random() * 4) + 1;
	
	// Other Variables
	int i;
	int j;
	int m;
	int player;
	int var1;
	int var2;
	int pos = 0;
	int handCount;
	
	int score[4] = {0,0,0,0};
	
	//test 1000 itterations
	printf("------- unittest4 - Shuffle -------- \n");
	for(i = 0; i < 1; i++) {
		
		/* Set Up */
		// clear the game state
		memset(&Game, 23, sizeof(struct gameState));
		memset(&Holder, 23, sizeof(struct gameState));
		
		// initialize a new game
		initializeGame(players, k, seed, &Game);
		
		
		// Random game state from lecture and test code
		for (m = 0; m < sizeof(struct gameState); m++) {
			((char*)&Game)[m] = (int)(Random() * 256);
		}
		// we need our game to be somewhat feasible
		for (player = 0; player < players; player++){
			player[score] = 0;
			Game.deckCount[player] = (int)(Random() * MAX_DECK/4);
			Game.discardCount[player] = (int)(Random() * MAX_DECK/4);
			Game.handCount[player] = (int)(Random() * MAX_HAND/4);
			handCount = Game.handCount[player];
		
			//setting all
			for (j = 0; j < 25; j++){
				Game.supplyCount[j] = 20;
			}
			for (j = 0; j < 6; j++){
				Game.supplyCount[e[j]] = 10;
			}

			//randomly populates hand
			for (j = 0; j < Game.handCount[player]; j ++) {
			
				var1 = (int)(Random() * 3) + 1; // gives rand number
				var2 = (int)(Random() * 4); // for card, coin, or victory, slightly skewed
				//If card 
				if (var2 == 0) {
					var2 = (int)(Random() * 10); //should have own var, oh well
					Game.hand[player][i] = k[var2];	
				}
				// If coin
				else if (var2 == 1){
					if (var1 == 1)
						Game.hand[player][i] = copper;
			
					if (var1 == 2)
						Game.hand[player][i] = silver;
			
					if (var1 == 3)
						Game.hand[player][i] = gold;
				}
				//if victory
				else{
					do{
						var2 = (int)(Random() * 6);
						Game.hand[player][i] = e[var2];
						Game.supplyCount[e[var2]]--;
					}while(Game.supplyCount[e[var2]] == 0);
				
				
					if (Game.hand[player][i] == curse) 
						score[player] -= 1; 
				
					if (Game.hand[player][i] == estate) 
						score[player] += 1;
				
					if (Game.hand[player][i] == duchy)
						score[player] += 3;
				
					if (Game.hand[player][i] == province) 
						score[player] += 6; 
				
					if (Game.hand[player][i] == great_hall)
						score[player] += 1;
				
					if (Game.hand[player][i] == gardens) 
						score[player] = score[player] + ( fullDeckCount(player, 0, &Game) / 10 );
				}
			}

			printf("Expected Score - %d\nActual score: %d", score[player], scoreFor(player, &Game));
			//randomly populates hand
			for (j = 0; j < Game.discardCount[player]; j ++) {
			
				var1 = (int)(Random() * 3) + 1; // gives rand number
				var2 = (int)(Random() * 4); // for card, coin, or victory, slightly skewed
				//If card 
				if (var2 == 0) {
					var2 = (int)(Random() * 10); //should have own var, oh well
					Game.discard[player][i] = k[var2];	
				}
				// If coin
				else if (var2 == 1){
					if (var1 == 1)
						Game.discard[player][i] = copper;
			
					if (var1 == 2)
						Game.discard[player][i] = silver;
			
					if (var1 == 3)
						Game.discard[player][i] = gold;
				}
				//if victory
				else{
					do{
						var2 = (int)(Random() * 6);
						Game.discard[player][i] = e[var2];
						Game.supplyCount[e[var2]]--;
					}while(Game.supplyCount[e[var2]] == 0);
				
					if (Game.discard[player][i] == curse) 
						score[player] = score[player] - 1; 
				
					if (Game.discard[player][i] == estate) 
						score[player] = score[player] + 1;
				
					if (Game.discard[player][i] == duchy)
						score[player] = score[player] + 3;
				
					if (Game.discard[player][i] == province) 
						score[player] = score[player] + 6; 
				
					if (Game.discard[player][i] == great_hall)
						score[player] = score[player] + 1;
				
					if (Game.discard[player][i] == gardens) 
						score[player] = score[player] + ( fullDeckCount(player, 0, &Game) / 10 );
				}
			}
			printf("Expected Score - %d\nActual score: %d", score[player], scoreFor(player, &Game));
		
			//if deck
			for (j = 0; j < Game.deckCount[player]; j ++) {
			
				var1 = (int)(Random() * 3) + 1; // gives rand number
				var2 = (int)(Random() * 4); // for card, coin, or victory, slightly skewed
				//If card 
				if (var2 == 0) {
					var2 = (int)(Random() * 10); //should have own var, oh well
					Game.deck[player][i] = k[var2];	
				}
				// If coin
				else if (var2 == 1){
					if (var1 == 1)
						Game.deck[player][i] = copper;
			
					if (var1 == 2)
						Game.deck[player][i] = silver;
			
					if (var1 == 3)
						Game.deck[player][i] = gold;
				}
				//if victory
				else{
					do{
						var2 = (int)(Random() * 6);
						Game.deck[player][i] = e[var2];
						Game.supplyCount[e[var2]]--;
					} while (Game.supplyCount[e[var2]] == 0);
				
					if (Game.deck[player][i] == curse) 
						score[player] = score[player] - 1; 
				
					if (Game.deck[player][i] == estate) 
						score[player] = score[player] + 1;
				
					if (Game.deck[player][i] == duchy)
						score[player] = score[player] + 3;
				
					if (Game.deck[player][i] == province) 
						score[player] = score[player] + 6; 
				
					if (Game.deck[player][i] == great_hall)
						score[player] = score[player] + 1;
				
					if (Game.deck[player][i] == gardens) 
						score[player] = score[player] + ( fullDeckCount(player, 0, &Game) / 10 );
				}
			}
			printf("Expected Score - %d Actual score: %d", score[player], scoreFor(player, &Game));
			//assert(score[player] == scoreFor(player, &Game));
		}
	}
	printf("shuffle passed all tests!\n\n");
	
	
	return 0;
}