/*
* Test for discardCard function.
* discardCard() alters the gamestate by editing current player's cards.
* trash_flag is used to determine if card is removed from deck - otherwise just discarded.
* Some code has been sourced from lecture videos.
*/

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

// Replicates discardCard function. Uses pre/post state from lecture to compare
// expected results. result should == 0 for successful discard.
int testDiscard(int hand_position, int currentPlayer, struct gameState *post, int trash_flag)
{
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int result = discardCard(hand_position, currentPlayer, post, trash_flag);	// call discardCard on post game state.

	// change pre game state manually
	if (trash_flag < 1)	// trash_flag changes playedCardCOunt
		pre.playedCardCount++;

	pre.handCount[currentPlayer]--;	// reduce handCount by 1 (discarding)


	if (result != 0)	// Test return value of discardCard function on pre gamestate
		printf("Error found: discardCard did not return 0. Function failed.\n");
	else if (pre.playedCardCount != post->playedCardCount)	// Test that playedCardCount is the same for pre & post
		printf("Error found: discardCard did not correctly alter playedCardCount. Function failed.\n");
	else if (pre.handCount[currentPlayer] != post->handCount[currentPlayer])	// Test that handCount is the same for pre & post
		printf("Error found: discardCard did not correctly alter handCount[currentPlayer]. Function failed.\n");

	return 0;
}

int main()
{
	int player_num; //players
	int current_player; 
	int hand_position; 
	struct gameState G;
	int trash_flag;
	int i;

	int maxHand = 10; //hand will always have 10 cards and hand_position will go 0-9
	int playedCardCount = 0;

	SelectStream(2);
	PutSeed(3);

	printf("Testing...\n");

	for (player_num = 2; player_num <= MAX_PLAYERS; player_num++)
	{
		for (current_player = 0; current_player < player_num; current_player++)	// Test each player
		{
			for (hand_position = 0; hand_position < maxHand; hand_position++)	// Test each card
			{
				for (i = 0; i < sizeof(struct gameState); i++)	// Create random game state
				{
					((char*)&G)[i] = floor(Random() * 256);
				}
				G.numPlayers = player_num;
				G.playedCardCount = playedCardCount;
				G.handCount[current_player] = maxHand;
				trash_flag = floor(Random() * 2); // Sets trash flag %50 of the time

				testDiscard(hand_position, current_player, &G, trash_flag);	// call test function
			}
		}
	}

	printf("discardCard function - Test Complete\n");

	return 0;
}