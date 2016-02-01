/*
Unit Test for discardCard() function
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
function accepts (int handPos, int currentPlayer, struct gameState *state, int trashFlag) */

int main() {
	printf("-------------Unit Test #1: Testing discardCard() function-------------\n\n");

	//initialize variables for unit test
	int i, numPlayers, randomSeed, handPos, currentPlayer, trashFlag;
	int success = 0;
	int error = 0;
	struct gameState post, pre;
	int kCards[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	//seed random number generator and create random values (within boundaries for numPlayers and randomSeed
	srand(time(NULL));
	numPlayers = (rand() % 3) + 2;
	randomSeed = (rand() % 100);
	
	
	
	//Test Case 1: trashFlag = 0 and discarded card is last card in hand
	printf("\nCASE 1: trashFlag = 0 and discarded card is last card in hand\n");
	initializeGame(numPlayers, kCards, randomSeed, &post);
	memcpy(&pre, &post, sizeof(struct gameState));
	currentPlayer = 0;
	handPos = post.handCount[currentPlayer];
	trashFlag = 0;
	discardCard(handPos, currentPlayer, &post, trashFlag);
	//Check that card added to Played pile
	if (post.playedCardCount != pre.playedCardCount + 1) {
		printf("Failed test case 1a: playedCardCount did not increase by 1.\n");
		success = -1;
	}
	else {
		printf("playedCardCount successfully incremented.\n");
	}
	//Check that discarded card set to -1 in player's hand
	if (post.hand[currentPlayer][post.handCount[currentPlayer]] != -1) {
		printf("Failed test case 1b: discarded card set to %d, not -1 in player's hand\n", post.hand[currentPlayer][handPos+1]);
		success = -1;
	}
	else {
		printf("Value of discarded card successfully set to -1 in current player's hand.\n");
	}
	//Check that player's hand count decremented by 1
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]-1) {
		printf("Failed test case 1c: player's hand count did not decrement\n");
		success = -1;
	}
	else {
		printf("Current player's hand size successfully decremented by 1.\n");
	}
	//Check that other player's hand sizes were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.handCount[i] != pre.handCount[i]) {
			error = -1;
		}
	}
	if (error == -1) {
		printf("Failed test case 1d: at least one other player's hand count changed.\n");
	}
	else {
		printf("No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 1 successfully passed.\n");
	}
	
	
	
	//Test Case 2: trashFlag = 0 and discarded card is only card in hand
	printf("\nCASE 2: trashFlag = 0 and discarded card is only card in hand\n");
	success = 0;
	error = 0;
	initializeGame(numPlayers, kCards, randomSeed, &post);
	currentPlayer = 0;
	handPos = 0;
	//make it so current player only has one card in hand
	for (i = 1; i < post.handCount[currentPlayer]; i++) {
		post.hand[currentPlayer][i] = -1;
	}
	post.handCount[currentPlayer] = 1;
	trashFlag = 0;
	memcpy(&pre, &post, sizeof(struct gameState));
	discardCard(handPos, currentPlayer, &post, trashFlag);
	//Check that card added to Played pile
	if (post.playedCardCount != pre.playedCardCount + 1) {
		printf("Failed test case 2a: playedCardCount did not increase by 1.\n");
		success = -1;
	}
	else {
		printf("playedCardCount successfully incremented.\n");
	}
	//Check that discarded card set to -1 in player's hand
	if (post.hand[currentPlayer][post.handCount[currentPlayer]] != -1) {
		printf("Failed test case 2b: discarded card set to %d, not -1 in player's hand\n", post.hand[currentPlayer][handPos+1]);
		success = -1;
	}
	else {
		printf("Value of discarded card successfully set to -1 in current player's hand.\n");
	}
	//Check that player's hand count decremented by 1
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]-1) {
		printf("Failed test case 2c: player's hand count did not decrement\n");
		success = -1;
	}
	else {
		printf("Current player's hand size successfully decremented by 1.\n");
	}
	//Check that other player's hand sizes were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.handCount[i] != pre.handCount[i]) {
			error = -1;
		}
	}
	if (error == -1) {
		printf("Failed test case 2d: at least one other player's hand count changed.\n");
	}
	else {
		printf("No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 2 successfully passed.\n");
	}
	
	
	
	//Test Case 3: trashFlag = 0, discarded card is not last card in hand, and hand size is greater than 1
	printf("\nCASE 3: trashFlag = 0, discarded card is not last card in hand, and hand size is greater than 1\n");
	success = 0;
	error = 0;
	initializeGame(numPlayers, kCards, randomSeed, &post);
	memcpy(&pre, &post, sizeof(struct gameState));
	currentPlayer = 0;
	handPos = post.handCount[currentPlayer];
	trashFlag = 0;
	discardCard(handPos, currentPlayer, &post, trashFlag);
	//Check that card added to Played pile
	if (post.playedCardCount != pre.playedCardCount + 1) {
		printf("Failed test case 3a: playedCardCount did not increase by 1.\n");
		success = -1;
	}
	else {
		printf("playedCardCount successfully incremented.\n");
	}
	//Check that discarded card set to last card in player's hand
	if (post.hand[currentPlayer][handPos] != pre.hand[currentPlayer][pre.handCount[currentPlayer]-1]) {
		printf("Failed test case 3b: discarded card set to %d, not last card in player's hand (%d)\n", post.hand[currentPlayer][handPos], pre.hand[currentPlayer][pre.handCount[currentPlayer]-1]);
		success = -1;
	}
	else {
		printf("Value of discarded card successfully set to value of the last card in current player's hand.\n");
	}
	//Check that last card in player's hand set to -1
	if (post.hand[currentPlayer][post.handCount[currentPlayer]] != -1) {
		printf("Failed test case 3c: last card in player's hand set to %d, not -1\n", post.hand[currentPlayer][handPos+1]);
		success = -1;
	}
	else {
		printf("Value of last card in current player's hand successfully set to -1.\n");
	}
	//Check that player's hand count decremented by 1
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]-1) {
		printf("Failed test case 3d: player's hand count did not decrement\n");
		success = -1;
	}
	else {
		printf("Current player's hand size successfully decremented by 1.\n");
	}
	//Check that other player's hand sizes were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.handCount[i] != pre.handCount[i]) {
			error = -1;
		}
	}
	if (error == -1) {
		printf("Failed test case 3e: at least one other player's hand count changed.\n");
	}
	else {
		printf("No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 3 successfully passed.\n");
	}	
	
	
	
	//Test Case 4: trashFlag = 1 and discarded card is last card in hand
	printf("\nCASE 4: trashFlag = 1 and discarded card is last card in hand\n");
	success = 0;
	error = 0;
	initializeGame(numPlayers, kCards, randomSeed, &post);
	memcpy(&pre, &post, sizeof(struct gameState));
	currentPlayer = 0;
	handPos = post.handCount[currentPlayer];
	trashFlag = 1;
	discardCard(handPos, currentPlayer, &post, trashFlag);
	//Check that card added to Played pile
	if (post.playedCardCount != pre.playedCardCount) {
		printf("Failed test case 4a: playedCardCount was affected by discardCard().\n");
		success = -1;
	}
	else {
		printf("playedCardCount successfully remained unchanged.\n");
	}
	//Check that discarded card set to -1 in player's hand
	if (post.hand[currentPlayer][post.handCount[currentPlayer]] != -1) {
		printf("Failed test case 4b: discarded card set to %d, not -1 in player's hand\n", post.hand[currentPlayer][handPos+1]);
		success = -1;
	}
	else {
		printf("Value of discarded card successfully set to -1 in current player's hand.\n");
	}
	//Check that player's hand count decremented by 1
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]-1) {
		printf("Failed test case 4c: player's hand count did not decrement\n");
		success = -1;
	}
	else {
		printf("Current player's hand size successfully decremented by 1.\n");
	}
	//Check that other player's hand sizes were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.handCount[i] != pre.handCount[i]) {
			error = -1;
		}
	}
	if (error == -1) {
		printf("Failed test case 4e: at least one other player's hand count changed.\n");
	}
	else {
		printf("No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 4 successfully passed.\n");
	}
	
	
	
	//Test Case 5: trashFlag = 1 and discarded card is only card in hand
	printf("\nCASE 5: trashFlag = 1 and discarded card is only card in hand\n");
	success = 0;
	error = 0;
	initializeGame(numPlayers, kCards, randomSeed, &post);
	currentPlayer = 0;
	handPos = 0;
	//make it so current player only has one card in hand
	for (i = 1; i < post.handCount[currentPlayer]; i++) {
		post.hand[currentPlayer][i] = -1;
	}
	post.handCount[currentPlayer] = 1;
	trashFlag = 1;
	memcpy(&pre, &post, sizeof(struct gameState));
	discardCard(handPos, currentPlayer, &post, trashFlag);
	//Check that card added to Played pile
	if (post.playedCardCount != pre.playedCardCount) {
		printf("Failed test case 5a: playedCardCount was affected by discardCard().\n");
		success = -1;
	}
	else {
		printf("playedCardCount successfully remained unchanged.\n");
	}
	//Check that discarded card set to -1 in player's hand
	if (post.hand[currentPlayer][post.handCount[currentPlayer]] != -1) {
		printf("Failed test case 5b: discarded card set to %d, not -1 in player's hand\n", post.hand[currentPlayer][handPos+1]);
		success = -1;
	}
	else {
		printf("Value of discarded card successfully set to -1 in current player's hand.\n");
	}
	//Check that player's hand count decremented by 1
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]-1) {
		printf("Failed test case 5c: player's hand count did not decrement\n");
		success = -1;
	}
	else {
		printf("Current player's hand size successfully decremented by 1.\n");
	}
	//Check that other player's hand sizes were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.handCount[i] != pre.handCount[i]) {
			error = -1;
		}
	}
	if (error == -1) {
		printf("Failed test case 5e: at least one other player's hand count changed.\n");
	}
	else {
		printf("No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 5 successfully passed.\n");
	}
	
	
	
	//Test Case 6: trashFlag = 1, discarded card is not last card in hand, and hand size is greater than 1
	printf("\nCASE 6: trashFlag = 1, discarded card is not last card in hand, and hand size is greater than 1\n");
	success = 0;
	error = 0;
	initializeGame(numPlayers, kCards, randomSeed, &post);
	memcpy(&pre, &post, sizeof(struct gameState));
	currentPlayer = 0;
	handPos = post.handCount[currentPlayer];
	trashFlag = 1;
	discardCard(handPos, currentPlayer, &post, trashFlag);
	//Check that card added to Played pile
	if (post.playedCardCount != pre.playedCardCount) {
		printf("Failed test case 6a: playedCardCount was affected by discardCard().\n");
		success = -1;
	}
	else {
		printf("playedCardCount successfully remained unchanged.\n");
	}
	//Check that discarded card set to last card in player's hand
	if (post.hand[currentPlayer][handPos] != pre.hand[currentPlayer][pre.handCount[currentPlayer]-1]) {
		printf("Failed test case 6b: discarded card set to %d, not last card in player's hand (%d)\n", post.hand[currentPlayer][handPos], pre.hand[currentPlayer][pre.handCount[currentPlayer]-1]);
		success = -1;
	}
	else {
		printf("Value of discarded card successfully set to value of the last card in current player's hand.\n");
	}
	//Check that last card in player's hand set to -1
	if (post.hand[currentPlayer][post.handCount[currentPlayer]] != -1) {
		printf("Failed test case 6c: last card in player's hand set to %d, not -1\n", post.hand[currentPlayer][handPos+1]);
		success = -1;
	}
	else {
		printf("Value of last card in current player's hand successfully set to -1.\n");
	}
	//Check that player's hand count decremented by 1
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]-1) {
		printf("Failed test case 6d: player's hand count did not decrement\n");
		success = -1;
	}
	else {
		printf("Current player's hand size successfully decremented by 1.\n");
	}
	//Check that other player's hand sizes were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.handCount[i] != pre.handCount[i]) {
			error = -1;
		}
	}
	if (error == -1) {
		printf("Failed test case 6e: at least one other player's hand count changed.\n");
	}
	else {
		printf("No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 6 successfully passed.\n");
	}

	printf("\n\n-------------Unit Test #1 Complete -------------\n");
	return 0;
}