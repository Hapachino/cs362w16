/*
Unit Test for gainCard() function
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
function accepts (int supplyPos, struct gameState *state, int toFlag, int currentPlayer) */

int main() {
	printf("-------------Unit Test #2: Testing gainCard() function-------------\n\n");

	//initialize variables for unit test
	int i, j, k, numPlayers, randomSeed, supplyPos, currentPlayer, toFlag;
	int success = 0;
	int error = 0;
	struct gameState post, pre;
	int kCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	//seed random number generator and create random values (within boundaries for numPlayers and randomSeed
	srand(time(NULL));
	numPlayers = (rand() % 3) + 2;
	randomSeed = (rand() % 100);
	
	
	
	//Test Case 1: Desired supply is empty
	printf("\nCASE 1: Desired supply is empty\n");
	initializeGame(numPlayers, kCards, randomSeed, &post);
	//set desired supplyCount to 0
	supplyPos = village;
	post.supplyCount[supplyPos] = 0;
	currentPlayer = 0;
	toFlag = 0;
	//check for error if empty supply
	if (gainCard(supplyPos, &post, toFlag, currentPlayer) != -1) {
		printf("Failed test case 1a: gainCard did not return -1 even though supply was empty.\n");
		success = -1;
	}
	else {
		printf("gainCard successfully returned -1 due to the empty supply.\n");
	}
	if (success == 0) {
		printf("Test case 1 successfully passed.\n");
	}
	
	
	
	//Test Case 2: Desired supply is not in the game
	printf("\nCASE 2: Desired supply is not in the game\n");
	success = 0;
	initializeGame(numPlayers, kCards, randomSeed, &post);
	//set desired supplyCount to a value not in the game
	supplyPos = remodel;
	currentPlayer = 0;
	toFlag = 0;
	//check for error if empty supply
	if (gainCard(supplyPos, &post, toFlag, currentPlayer) != -1) {
		printf("Failed test case 2a: gainCard did not return -1 even though supply was not in the game.\n");
		success = -1;
	}
	else {
		printf("gainCard successfully returned -1 due to the desired supply not being in the game.\n");
	}
	if (success == 0) {
		printf("Test case 2 successfully passed.\n");
	}
	
	
	//Test Case 3: toFlag = 0 and desired supply available
	printf("\nCASE 3: toFlag = 0 and desired supply available\n");
	success = 0;
	initializeGame(numPlayers, kCards, randomSeed, &post);
	memcpy(&pre, &post, sizeof(struct gameState));
	supplyPos = village;
	currentPlayer = 0;
	toFlag = 0;
	gainCard(supplyPos, &post, toFlag, currentPlayer);
	//Check that gained card is put in discard
	if (post.discard[currentPlayer][pre.discardCount[currentPlayer]] != supplyPos) {
		printf("Failed test case 3a: gainCard either did not add correct card to the current player's discard pile or added it at an unexpected location in the discard pile.\n");
		success = -1;
	}
	else {
		printf("Successfully added the chosen supply to the current player's discard pile.\n");
	}
	//Check that discardCount incremented by 1
	if (post.discardCount[currentPlayer] != pre.discardCount[currentPlayer]+1) {
		printf("Failed test case 3b: Current player's discard count did not increment by 1.\n");
		success = -1;
	}
	else {
		printf("Successfully incremented the current player's discard count by 1.\n");
	}
	//Check that other player's discard counts were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.discardCount[i] != pre.discardCount[i]) {
			error = -1;
		}
	}
	if (error == -1) {
		printf("Failed test case 3c: at least one other player's discard count changed.\n");
	}
	else {
		printf("No other player's discard count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 3 successfully passed.\n");
	}	
	
	

	//Test Case 4: toFlag = 1 and desired supply available
	printf("\nCASE 4: toFlag = 1 and desired supply available\n");
	success = 0;
	error = 0;
	initializeGame(numPlayers, kCards, randomSeed, &post);
	memcpy(&pre, &post, sizeof(struct gameState));
	supplyPos = village;
	currentPlayer = 0;
	toFlag = 1;
	gainCard(supplyPos, &post, toFlag, currentPlayer);
	//Check that gained card is put on deck
	if (post.deck[currentPlayer][pre.deckCount[currentPlayer]] != supplyPos) {
		printf("Failed test case 4a: gainCard either did not add correct card to the current player's deck or added it at an unexpected location in the deck.\n");
		success = -1;
	}
	else {
		printf("Successfully added the chosen supply to the current player's deck.\n");
	}
	//Check that deckCount incremented by 1
	if (post.deckCount[currentPlayer] != pre.deckCount[currentPlayer]+1) {
		printf("Failed test case 4b: Current player's deck count did not increment by 1.\n");
		success = -1;
	}
	else {
		printf("Successfully incremented the current player's deck count by 1.\n");
	}
	//Check that other player's deck counts were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.deckCount[i] != pre.deckCount[i]) {
			error = -1;
		}
	}
	if (error == -1) {
		printf("Failed test case 4c: at least one other player's deck count changed.\n");
	}
	else {
		printf("No other player's deck count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 4 successfully passed.\n");
	}
	
	
	
	//Test Case 5: toFlag = 2 and desired supply available
	printf("\nCASE 5: toFlag = 2 and desired supply available\n");
	success = 0;
	error = 0;
	initializeGame(numPlayers, kCards, randomSeed, &post);
	memcpy(&pre, &post, sizeof(struct gameState));
	supplyPos = village;
	currentPlayer = 0;
	toFlag = 2;
	gainCard(supplyPos, &post, toFlag, currentPlayer);
	//Check that gained card is put in hand
	if (post.hand[currentPlayer][pre.handCount[currentPlayer]] != supplyPos) {
		printf("Failed test case 5a: gainCard either did not add correct card to the current player's hand or added it at an unexpected location in the hand.\n");
		success = -1;
	}
	else {
		printf("Successfully added the chosen supply to the current player's hand.\n");
	}
	//Check that handCount incremented by 1
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]+1) {
		printf("Failed test case 5b: Current player's hand count did not increment by 1.\n");
		success = -1;
	}
	else {
		printf("Successfully incremented the current player's hand count by 1.\n");
	}
	//Check that other player's hand counts were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.handCount[i] != pre.handCount[i]) {
			error = -1;
		}
	}
	if (error == -1) {
		printf("Failed test case 5c: at least one other player's hand count changed.\n");
	}
	else {
		printf("No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 5 successfully passed.\n");
	}
	
	
	
	printf("\n\n-------------Unit Test #2 Complete -------------\n");
	return 0;
}