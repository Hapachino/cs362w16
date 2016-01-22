/*Tanna Richardson
  CS362 - Winter 2016
  Assignment 3
  Unit test for: shuffle()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "test_helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main () {
	int i, j;
	struct gameState *g;
		
	//Generate random games and print current game state
	for (i = 0; i < 10; i++){
		g = randomGame(i);
		
		printf("Game #%d state:\n", i);
		printGameState(g);
		
	}
		
	return 0;
}
