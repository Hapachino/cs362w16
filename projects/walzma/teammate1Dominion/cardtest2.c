/*
Card Test for Village card
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


int main() {
	printf("\n-------------Card Test #2: Testing village card-------------\n\n");

	//initialize variables for card test
	int i, numPlayers, handPos, randomSeed;
	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int currentPlayer = 0, success = 0, error1 = 0, error2 = 0;
	struct gameState pre, post;
	int kCards[10] = {adventurer, remodel, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	//seed random number generator and create random values (within boundaries for numPlayers, handPos, and randomSeed
	srand(time(NULL));
	numPlayers = (rand() % 3) + 2;
	handPos = (rand() % 5);
	randomSeed = (rand() % 100);
	
	
	
	//Test Case 1: Current player has enough cards in their deck to draw without shuffling
	printf("\nCASE 1: Current player has enough cards in their deck to draw without shuffling\n");
	//initialize game state and copy to second game state
	initializeGame(numPlayers, kCards, randomSeed, &post);
	//set card in handPos to Village
	post.hand[currentPlayer][handPos] = village;
	memcpy(&pre, &post, sizeof(struct gameState));
	//check village
	if (cardEffect(village, choice1, choice2, choice3, &post, handPos, &bonus) == 1) {
		printf("Failed function: cardEffect(village,...) threw an error when calling village.\n");
		success = -1;
	}
	//Check that currentPlayer handCount did not change (+1 for drawn cards and -1 for playing village)
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]) {
		printf("Failed test case 1a: handCount of currentPlayer did not remain the same (+1 for drawn card and -1 for playing village)\n");
		success = -1;
	}
	else {
		printf("Passed test case 1a: Successfully maintained handCount of currentPlayer (+1 for drawn cards and -1 for playing village).\n");
	}
	//Check that village card added to played pile
	if  (post.playedCards[pre.playedCardCount] != village) {
		printf("Failed test case 1b: Village card was not successfully added to the played card pile\n");
		success = -1;
	}
	else {
		printf("Passed test case 1b: Village card successfully added to the played card pile.\n");
	}
	//Check that playedCardCount incremented by 1
	if  (post.playedCardCount != pre.playedCardCount + 1) {
		printf("Failed test case 1c: playedCardCount not incremented by 1\n");
		success = -1;
	}
	else {
		printf("Passed test case 1c: playedCardCount successfully incremented by 1.\n");
	}
	//Check that deckCount decremented by 1
	if  (post.deckCount[currentPlayer] != pre.deckCount[currentPlayer] - 1) {
		printf("Failed test case 1d: deckCount for currentPlayer not decremented by 1\n");
		success = -1;
	}
	else {
		printf("Passed test case 1d: deckCount for currentPlayer successfully decremented by 1.\n");
	}
	//Check that numActions incremented by 2
	if  (post.numActions != pre.numActions + 2) {
		printf("Failed test case 1e: numActions was not incremented by 2\n");
		success = -1;
	}
	else {
		printf("Passed test case 1e: numActions successfully incremented by 2.\n");
	}
	//Check that other player's deckCount and handCount were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.deckCount[i] != pre.deckCount[i]) {
			error1 = -1;
		}
		if (post.handCount[i] != pre.handCount[i]) {
			error2 = -1;
		}
	}
	if (error1 == -1) {
		printf("Failed test case 1f: at least one other player's deck count changed.\n");
	}
	else {
		printf("Passed test case 1f: No other player's deck count was affected.\n");
	}
	if (error2 == -1) {
		printf("Failed test case 1g: at least one other player's hand count changed.\n");
	}
	else {
		printf("Passed test case 1g: No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 1 successfully passed.\n");
	}
	else {
		printf("Test case 1 completed with errors.\n");
	}
	
	
	
	
	//Test Case 2: Current player has 0 cards in their deck, but at least 1 card in their combined deck and discard pile
	printf("\nCASE 2: Current player has 0 cards in their deck, but at least 1 card in their combined deck and discard pile\n");
	success = 0, error1 = 0, error2 = 0;
	
	//initialize game state and copy to second game state
	initializeGame(numPlayers, kCards, randomSeed, &post);
	//set card in handPos to Village
	post.hand[currentPlayer][handPos] = village;
	//add cards from deck to discard till no cards remain in deck
	for (i = 0; i < post.deckCount[currentPlayer]; i++) {
		post.discard[currentPlayer][post.discardCount[currentPlayer]] = post.deck[currentPlayer][i];
		post.deck[currentPlayer][i] = -1;
		post.discardCount[currentPlayer]++;
	}
	post.deckCount[currentPlayer] = 0;
	//copy game state
	memcpy(&pre, &post, sizeof(struct gameState));
	
	//check village
	if (cardEffect(village, choice1, choice2, choice3, &post, handPos, &bonus) == 1) {
		printf("Failed function: cardEffect(village,...) threw an error when calling village.\n");
		success = -1;
	}
	//Check that currentPlayer handCount did not change (+1 for drawn cards and -1 for playing village)
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]) {
		printf("Failed test case 2a: handCount of currentPlayer did not remain the same (+1 for drawn card and -1 for playing village)\n");
		success = -1;
	}
	else {
		printf("Passed test case 2a: Successfully maintained handCount of currentPlayer (+1 for drawn cards and -1 for playing village).\n");
	}
	//Check that village card added to played pile
	if  (post.playedCards[pre.playedCardCount] != village) {
		printf("Failed test case 2b: Village card was not successfully added to the played card pile\n");
		success = -1;
	}
	else {
		printf("Passed test case 2b: Village card successfully added to the played card pile.\n");
	}
	//Check that playedCardCount incremented by 1
	if  (post.playedCardCount != pre.playedCardCount + 1) {
		printf("Failed test case 2c: playedCardCount not incremented by 1\n");
		success = -1;
	}
	else {
		printf("Passed test case 2c: playedCardCount successfully incremented by 1.\n");
	}
	//Check that deckCount equals (discardCount + deckCount - 1)
	if  (post.deckCount[currentPlayer] != (pre.deckCount[currentPlayer] + pre.discardCount[currentPlayer] - 1)) {
		printf("Failed test case 2d: deckCount for currentPlayer does not equal the total number of cards in currentPlayer's deck and discard pile prior to village being played minus 1\n");
		success = -1;
	}
	else {
		printf("Passed test case 2d: deckCount for currentPlayer successfully recalculated (equals the total number of cards in currentPlayer's deck and discard pile prior to village being played minus 1).\n");
	}
	//Check that numActions incremented by 2
	if  (post.numActions != pre.numActions + 2) {
		printf("Failed test case 2e: numActions was not incremented by 2\n");
		success = -1;
	}
	else {
		printf("Passed test case 2e: numActions successfully incremented by 2.\n");
	}
	//Check that other player's deckCount and handCount were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.deckCount[i] != pre.deckCount[i]) {
			error1 = -1;
		}
		if (post.handCount[i] != pre.handCount[i]) {
			error2 = -1;
		}
	}
	if (error1 == -1) {
		printf("Failed test case 2f: at least one other player's deck count changed.\n");
	}
	else {
		printf("Passed test case 2f: No other player's deck count was affected.\n");
	}
	if (error2 == -1) {
		printf("Failed test case 2g: at least one other player's hand count changed.\n");
	}
	else {
		printf("Passed test case 2g: No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 1 successfully passed.\n");
	}
	else {
		printf("Test case 1 completed with errors.\n");
	}
	
	
	
	
	//Test Case 3: Current player has 0 cards combined in their deck and discard pile
	printf("\nCASE 3: Current player has 0 cards combined in their deck and discard pile\n");
	success = 0, error1 = 0, error2 = 0;
	
	//initialize game state and copy to second game state
	initializeGame(numPlayers, kCards, randomSeed, &post);
	//set card in handPos to Village
	post.hand[currentPlayer][handPos] = village;
	//add cards from deck and discard pile to hand till no cards remain in deck
	for (i = 0; i < post.deckCount[currentPlayer]; i++) {
		post.hand[currentPlayer][post.handCount[currentPlayer]] = post.deck[currentPlayer][i];
		post.deck[currentPlayer][i] = -1;
		post.handCount[currentPlayer]++;
	}
	post.deckCount[currentPlayer] = 0;
	for (i = 0; i < post.discardCount[currentPlayer]; i++) {
		post.hand[currentPlayer][post.handCount[currentPlayer]] = post.discard[currentPlayer][i];
		post.discard[currentPlayer][i] = -1;
		post.discardCount[currentPlayer]++;
	}
	post.deckCount[currentPlayer] = 0;
	//copy game state
	memcpy(&pre, &post, sizeof(struct gameState));
	
	//check village
	if (cardEffect(village, choice1, choice2, choice3, &post, handPos, &bonus) == 1) {
		printf("Failed function: cardEffect(village,...) threw an error when calling village.\n");
		success = -1;
	}
	//Check that currentPlayer handCount decremented by 1 (no card to draw and -1 for playing village)
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer] - 1) {
		printf("Failed test case 3a: handCount of currentPlayer did not decrement by 1 (no card to draw and -1 for playing village)\n");
		success = -1;
	}
	else {
		printf("Passed test case 3a: Successfully decremented handCount of currentPlayer (no card to draw and -1 for playing village).\n");
	}
	//Check that village card added to played pile
	if  (post.playedCards[pre.playedCardCount] != village) {
		printf("Failed test case 3b: Village card was not successfully added to the played card pile\n");
		success = -1;
	}
	else {
		printf("Passed test case 3b: Village card successfully added to the played card pile.\n");
	}
	//Check that playedCardCount incremented by 1
	if  (post.playedCardCount != pre.playedCardCount + 1) {
		printf("Failed test case 3c: playedCardCount not incremented by 1\n");
		success = -1;
	}
	else {
		printf("Passed test case 3c: playedCardCount successfully incremented by 1.\n");
	}
	//Check that deckCount equals 0
	if  (post.deckCount[currentPlayer] != 0) {
		printf("Failed test case 3d: deckCount for currentPlayer does not equal 0\n");
		success = -1;
	}
	else {
		printf("Passed test case 3d: deckCount for currentPlayer equals 0.\n");
	}
	//Check that numActions incremented by 2
	if  (post.numActions != pre.numActions + 2) {
		printf("Failed test case 3e: numActions was not incremented by 2\n");
		success = -1;
	}
	else {
		printf("Passed test case 3e: numActions successfully incremented by 2.\n");
	}
	//Check that other player's deckCount and handCount were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.deckCount[i] != pre.deckCount[i]) {
			error1 = -1;
		}
		if (post.handCount[i] != pre.handCount[i]) {
			error2 = -1;
		}
	}
	if (error1 == -1) {
		printf("Failed test case 3f: at least one other player's deck count changed.\n");
	}
	else {
		printf("Passed test case 3f: No other player's deck count was affected.\n");
	}
	if (error2 == -1) {
		printf("Failed test case 3g: at least one other player's hand count changed.\n");
	}
	else {
		printf("Passed test case 3g: No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 1 successfully passed.\n");
	}
	else {
		printf("Test case 1 completed with errors.\n");
	}
	
	
	
	printf("\n\n-------------Card Test #2 Complete -------------\n\n\n");
	return 0;
}