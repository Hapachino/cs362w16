/*
 * Author: Ato Jackson-Kuofie
 * File: unittest2.c
 * Description:  Random test generator for DiscardCard function in game of dominion
 * Summer 362

 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

int checkdiscardCard(int handPos, int currentPlayer, struct gameState *post,
		int trashFlag) {

	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int r, startPlayedCardCount, startHandCount;

	startPlayedCardCount = post->playedCardCount;
	startHandCount = post->handCount[currentPlayer];

	r = discardCard(handPos, currentPlayer, post, trashFlag);

	if (trashFlag < 1) {
		pre.playedCards[pre.playedCardCount] = pre.hand[currentPlayer][handPos];
		pre.playedCardCount++;

		assert(post->playedCardCount == (startPlayedCardCount + 1));
	}

	//Set the played card to -1

	pre.hand[currentPlayer][handPos] = -1;

	// Remove card from players hand if last in hand
	if (handPos == (pre.handCount[currentPlayer] - 1)) {
		pre.handCount[currentPlayer]--;
		assert(post->handCount[currentPlayer] == (startHandCount - 1));

	}
	//Remove card from player
	else if (pre.handCount[currentPlayer] == 1) {
		pre.handCount[currentPlayer]--;
		assert(post->handCount[currentPlayer] == (startHandCount - 1));
	}
	//Replace card in hand and decrease hand count
	else {
		pre.hand[currentPlayer][handPos] =
				pre.hand[currentPlayer][(pre.handCount[currentPlayer] - 1)];
		pre.hand[currentPlayer][pre.handCount[currentPlayer] - 1] = -1;
		pre.handCount[currentPlayer]--;
		assert(post->handCount[currentPlayer] == (startHandCount - 1));
	}

	assert(r == 0);

	//Make sure Pre and Post are equal
	assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);

	return 0;
}

int main() {

	int i, n, p, handPos, trashFlag;

	struct gameState G;

	printf("Testing DiscardCard.\n");

	printf("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);

	//Initialize game state with random array of character bytes
	for (n = 0; n < 2000; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*) &G)[i] = floor(Random() * 256);
		}



		//Random player cannot be more than 4 players
		G.numPlayers = 2 + floor(Random() * (MAX_PLAYERS - 1));
		p = floor(Random() * G.numPlayers);
		G.whoseTurn = p;
		//Random trash flag 0  to 2
		trashFlag = floor(Random() * 3);

		G.deckCount[p] = floor(Random() * MAX_DECK);
		G.discardCount[p] = floor(Random() * MAX_DECK);
		G.handCount[p] = floor(Random() * MAX_HAND);
		G.playedCardCount = floor(Random() * MAX_DECK);

		//Random hand position.
		handPos = floor(Random() * G.handCount[p]);

		//Valid cards in hand
		for (i = 0; i < G.handCount[p]; i++) {
			G.hand[p][i] = floor(Random() * (treasure_map + 1));
		}

		//Valid card in playedCard pile
		for (i = 0; i < G.playedCardCount; i++) {
			G.playedCards[i] = floor(Random() * (treasure_map + 1));
		}

		//Call test function
		checkdiscardCard(handPos, p, &G, trashFlag);

	}

	printf("ALL TESTS OK\n");

	exit(0);
}

