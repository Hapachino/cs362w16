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
	int seed = 1234;
	int players = 2;
	
	// Other Variables
	int i;
	int j;
	int m;
	int player;
	int count = 0;
	int var1;
	int var2;
	int returnVal;
	int handCount;
	
	//test 1000 itterations
	printf("------- unittest3 - Shuffle -------- \n");
	for(i = 0; i < 1000; i++) {
		
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
		player = (int)(Random() * 2);
		Game.deckCount[player] = (int)(Random() * MAX_DECK);
		Game.discardCount[player] = (int)(Random() * MAX_DECK);
		Game.handCount[player] = (int)(Random() * MAX_HAND);
		handCount = Game.handCount[player];
		
		//Making sure that it tests for the condition 1/13 times for single card
		if(i % 13 == 0){
			Game.deckCount[player] = 1;
			Game.handCount[player] = 1;
			handCount = 1;	
		}
		//randomly populates hand
		for (j = 0; j < handCount; j ++) {
			
			//Making sure that it tests for the condition 1/17 times for empty deck
			if(i % 41 == 0){
				Game.deckCount[player] = 0;
				break;
			}
			
			var1 = (int)(Random() * 3) + 1; // gives rand number
			var2 = (int)(Random() * 2); // for Bool of card or coin
			//If card 
			if (var2 == 0) {
				var2 = (int)(Random() * 10); //should have own var, oh well
				Game.hand[player][i] = k[var2];	
			}
			// If coin
			else {
				if (var1 == 1)
					Game.hand[player][i] = copper;
			
				if (var1 == 2)
					Game.hand[player][i] = silver;
			
				if (var1 == 3)
					Game.hand[player][i] = gold;
			}
		}
		
		//copy the game into the holder struct
		memcpy(&Holder, &Game, sizeof(struct gameState));
		
		//call shuffle, and store the return value to make sure it was successful
		returnVal = shuffle(player, &Game);
		if (returnVal == -1){
			assert(Game.deckCount[player] == 0);
		}
		else {
			assert(Game.deckCount[player] > 0);
		}
		assert(Holder.deckCount[player] == Game.deckCount[player]); 
		
		count = 0; // We'll keep track of things overlapping
		if (Game.deckCount[player] > 1){
			for (j = 0; j < handCount; j++) {
				if(Holder.deck[player][j] == Game.deck[player][j]) {
					count++;
					if (count > handCount/4){
						printf("Deck might not be fully shuffled.\n");
					}
				}
			}
		}
		//if single card in deck
		else if (Game.deckCount[player] == 1){
			assert(Holder.deck[player][0] == Game.deck[player][0]); 
		}
	}
	printf("shuffle passed all tests!\n\n");
	
	return 0;
}