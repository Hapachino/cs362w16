/*
Unit Test for drawCard() function
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG 0

/*
Preconditions:
function accepts (int currentPlayer, struct gameState *state) */

int main() {
	printf("-------------Unit Test #3: Testing drawCard() function-------------\n\n");

	//initialize variables for unit test
	int i, numPlayers, randomSeed, currentPlayer;
	int success = 0;
	int error1 = 0;
	int error2 = 0;
	struct gameState post, pre;
	int kCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	//seed random number generator and create random values (within boundaries for numPlayers and randomSeed
	srand(time(NULL));
	numPlayers = (rand() % 3) + 2;
	randomSeed = (rand() % 100);
	
	
	
	//Test Case 1: Deck is not empty
	printf("\nCASE 1: Deck is not empty\n");
	initializeGame(numPlayers, kCards, randomSeed, &post);
	memcpy(&pre, &post, sizeof(struct gameState));
	currentPlayer = 0;
	//check for error thrown by drawCard function
	if (drawCard(currentPlayer, &post) == -1) {
		printf("Failed function: drawCard returned -1.\n");
		success = -1;
	}
	//check that current player added top card from deck to hand
	if (post.hand[currentPlayer][pre.handCount[currentPlayer]] != pre.deck[currentPlayer][pre.deckCount[currentPlayer]-1]) {
		printf("Failed test case 1a: drawCard either did not add top card from deck to the current player's hand or added it at an unexpected location in the hand.\n");
		success = -1;
	}
	else {
		printf("Successfully added the top card from deck to the current player's hand.\n");
	}
	//check that current player hand count incremented
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]+1) {
		printf("Failed test case 1b: current player's hand count was not incremented by 1.\n");
		success = -1;
	}
	else {
		printf("Successfully incremented the current player's hand count by 1.\n");
	}
	//check that current player deck count decremented
	if (post.deckCount[currentPlayer] != pre.deckCount[currentPlayer]-1) {
		printf("Failed test case 1c: current player's deck count was not decremented by 1.\n");
		success = -1;
	}
	else {
		printf("Successfully decremented the current player's deck count by 1.\n");
	}
	//verify no other player's had their deck size or hand size modified
	for (i = 1; i < numPlayers; i++) {
		if (post.deckCount[i] != pre.deckCount[i]) {
			error1 = -1;
		}
		if (post.handCount[i] != pre.handCount[i]) {
			error2 = -1;
		}
	}
	if (error1 == -1) {
		printf("Failed test case 1d: at least one other player's deck count changed.\n");
	}
	else {
		printf("No other player's deck count was affected.\n");
	}
	if (error2 == -1) {
		printf("Failed test case 1e: at least one other player's hand count changed.\n");
	}
	else {
		printf("No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 1 successfully passed.\n");
	}
	
	
	
	//Test Case 2: Deck is empty and needs to be shuffled. Cards exist in the discard pile
	printf("\nCASE 2: Deck is empty and needs to be shuffled\n");
	success = 0;
	error1 = 0;
	error2 = 0;
	initializeGame(numPlayers, kCards, randomSeed, &post);
	currentPlayer = 0;
	
	//change game states so that current player has an empty deck
	//move deck to discard pile
	for (i = 0; i < post.deckCount[currentPlayer]; i++) {
		post.discard[currentPlayer][post.discardCount[currentPlayer]+i] = post.deck[currentPlayer][i];
		post.deck[currentPlayer][i] = -1;
	}
	//update deck and discard counts
	post.discardCount[currentPlayer] = post.discardCount[currentPlayer] + post.deckCount[currentPlayer];
	post.deckCount[currentPlayer] = 0;

	//now that deck is empty, copy game state and then call drawCard
	memcpy(&pre, &post, sizeof(struct gameState));
	if (drawCard(currentPlayer, &post) == -1) {
		printf("Failed function: drawCard returned -1 in test case 2.\n");
		success = -1;
	}
	//check that deck was shuffled
	if (post.deckCount[currentPlayer] != pre.discardCount[currentPlayer]-1) {
		printf("Failed test case 2a: the deck does not have the correct number of cards after shuffling the discard pile.\n");
		success = -1;
	}
	else {
		printf("Successfully shuffled the discard pile into the deck.\n");
	}
	//check that current player added a card with value != -1 to their hand
	if (post.hand[currentPlayer][pre.handCount[currentPlayer]] == -1) {
		printf("Failed test case 2b: the current player did not add a card to their hand after shuffling the discard pile into the deck.\n");
		success = -1;
	}
	else {
		printf("Successfully added a card from the newly shuffled deck to current player's hand.\n");
	}
	//check that current player hand count incremented
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]+1) {
		printf("Failed test case 2c: current player's hand count was not incremented by 1.\n");
		success = -1;
	}
	else {
		printf("Successfully incremented the current player's hand count by 1.\n");
	}
	//check that current player deck count decremented
	if (post.deckCount[currentPlayer] != pre.discardCount[currentPlayer]-1) {
		printf("Failed test case 2d: current player's deck count was not decremented by 1 after shuffling.\n");
		success = -1;
	}
	else {
		printf("Successfully decremented the current player's newly shuffled deck count by 1.\n");
	}
	//verify no other player's had their deck size or hand size modified
	for (i = 1; i < numPlayers; i++) {
		if (post.deckCount[i] != pre.deckCount[i]) {
			error1 = -1;
		}
		if (post.handCount[i] != pre.handCount[i]) {
			error2 = -1;
		}
	}
	if (error1 == -1) {
		printf("Failed test case 2e: at least one other player's deck count changed.\n");
	}
	else {
		printf("No other player's deck count was affected.\n");
	}
	if (error2 == -1) {
		printf("Failed test case 2f: at least one other player's hand count changed.\n");
	}
	else {
		printf("No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 2 successfully passed.\n");
	}
	
	
	printf("\n\n-------------Unit Test #3 Complete -------------\n");
	return 0;
}