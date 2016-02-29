/*
* Test for shuffle function.
* shuffle() returns 0 if shuffle was successful.
* testShuffle shuffles the post gamestate and compares results between
* pre and post to make sure the function works correctly.
* Some code has been sourced from lecture videos.
*/

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

// Replicates shuffle function. Uses pre/post state from lecture to compare
// expected results. result should == 0 for successful shuffle.
int testShuffle(int player, struct gameState *post)
{
	struct gameState pre;
	// Copy current game state
	memcpy(&pre, post, sizeof(struct gameState));

	int result = shuffle(player, post);

	if (result != 0)	// Test return value of shuffle function on post gamestate.
		printf("Error found: shuffle did not return 0. Function failed.\n");
	else if (pre.deckCount[player] != post->deckCount[player])	// Test that deckCount was not altered.
		printf("Error found: shuffle altered deckCount. Function failed.\n");
	else if (memcmp(&pre.deck[player], post->deck[player], sizeof(int)* pre.deckCount[player]) == 0)	// Test that deck was shuffled
		printf("Error found: Deck is the same.\n");

	return 0;
}

int main()
{
	struct gameState G;
	//cards in player decks
	int player_num; //players
	int current_player; //current player
	int i, j;
	int count; //deck count

	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };

	SelectStream(2);
	PutSeed(3);

	printf("Testing...\n");

	for (player_num = 2; player_num <= MAX_PLAYERS; player_num++) 
	{
		for (current_player = 0; current_player < player_num; current_player++) //test for each player currently playing
		{
			//test different deck amounts
			//not testing < 4 since its more likely that shuffled decks won't change
			for (count = 4; count < 50; count++)
			{
				for (i = 0; i < sizeof(struct gameState); i++) {	// Create random game state
					((char*)&G)[i] = floor(Random() * 256);
				}

				//fill in some real cards
				for (j = 0; j < count; j++)
				{
					int card = floor(Random() * 10);
					G.deck[current_player][j] = k[card];
				}
				//set other necessary state settings
				G.numPlayers = player_num;
				G.deckCount[current_player] = count;

				testShuffle(current_player, &G);
			}
		}
	}
	printf("shuffle function - Test Complete\n");

	return 0;
}