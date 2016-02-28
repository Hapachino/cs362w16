/*
Card Test for Adventurer card
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
	printf("\n-------------Card Test #3: Testing adventurer card-------------\n\n");

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
	
	
	
	//Test Case 1: Current player has 2 or more coins in their deck to draw with adventurer
	printf("\nCASE 1: Current player has 2 or more coins in their deck to draw with adventurer\n");
	//initialize game state and copy to second game state
	initializeGame(numPlayers, kCards, randomSeed, &post);
	//set card in handPos to Adventurer
	post.hand[currentPlayer][handPos] = adventurer;
	memcpy(&pre, &post, sizeof(struct gameState));
	//check AdventurerEffect
	if (cardEffect(adventurer, choice1, choice2, choice3, &post, handPos, &bonus) == 1) {
		printf("Failed function: cardEffect(adventurer,...) threw an error state.\n");
		success = -1;
	}
	//Check that currentPlayer handCount increased by 1 (+2 for added coins, -1 for playing adventurer)
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]+1) {
		printf("Failed test case 1a: handCount of currentPlayer did not increase by 1 (+2 for added coins, -1 for playing adventurer)\n");
		success = -1;
	}
	else {
		printf("Passed test case 1a: handCount of currentPlayer successfully increased by 1 (+2 for added coins, -1 for playing adventurer).\n");
	}
	//Check that adventurer card added to played pile
	if  (post.playedCards[pre.playedCardCount] != adventurer) {
		printf("Failed test case 1b: Adventurer card was not successfully added to the played card pile\n");
		success = -1;
	}
	else {
		printf("Passed test case 1b: Adventurer card successfully added to the played card pile.\n");
	}
	//Check that playedCardCount incremented by 1
	if  (post.playedCardCount != pre.playedCardCount + 1) {
		printf("Failed test case 1c: playedCardCount not incremented by 1\n");
		success = -1;
	}
	else {
		printf("Passed test case 1c: playedCardCount successfully incremented by 1.\n");
	}
	//Check that added cards are coins
	int addedCard = post.hand[currentPlayer][post.handCount[currentPlayer]-2];
	if ((addedCard != copper) && (addedCard != silver) && (addedCard != gold)) {
		printf("Failed test case 1d: first card added to hand was not a coin.\n");
	}
	else {
		printf("Passed test case 1d: first card added to hand was a coin.\n");
	}
	addedCard = post.hand[currentPlayer][post.handCount[currentPlayer]-1];
	if ((addedCard != copper) && (addedCard != silver) && (addedCard != gold)) {
		printf("Failed test case 1e: second card added to hand was not a coin\n");
	}
	else {
		printf("Passed test case 1e: second card added to hand was a coin.\n");
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
	
	
	
	
	//Test Case 2: Current player has 1 coin in their deck and discard pile combined to draw with adventurer
	printf("\nCASE 2: Current player has 1 coin in their deck and discard pile combined to draw with adventurer\n");
	//initialize game state and copy to second game state
	initializeGame(numPlayers, kCards, randomSeed, &post);
	//set card in handPos to Adventurer
	post.hand[currentPlayer][handPos] = adventurer;
	//set cards in deck equal to non-coin cards so that only 1 coin remains
	for (i = 1; i < post.deckCount[currentPlayer]; i++) {
		post.deck[currentPlayer][i] = duchy;
	}
	//copy gamestate prior to testing adventurer
	memcpy(&pre, &post, sizeof(struct gameState));
	//check AdventurerEffect
	if (cardEffect(adventurer, choice1, choice2, choice3, &post, handPos, &bonus) == 1) {
		printf("Failed function: cardEffect(adventurer,...) threw an error state.\n");
		success = -1;
	}
	//Check that currentPlayer handCount remained the same (+1 for added coin, -1 for playing adventurer)
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]) {
		printf("Failed test case 2a: handCount of currentPlayer did not remain the same (+1 for added coin, -1 for playing adventurer)\n");
		success = -1;
	}
	else {
		printf("Passed test case 2a: handCount of currentPlayer successfully remained the same (+1 for added coin, -1 for playing adventurer).\n");
	}
	//Check that adventurer card added to played pile
	if  (post.playedCards[pre.playedCardCount] != adventurer) {
		printf("Failed test case 2b: Adventurer card was not successfully added to the played card pile\n");
		success = -1;
	}
	else {
		printf("Passed test case 2b: Adventurer card successfully added to the played card pile.\n");
	}
	//Check that playedCardCount incremented by 1
	if  (post.playedCardCount != pre.playedCardCount + 1) {
		printf("Failed test case 2c: playedCardCount not incremented by 1\n");
		success = -1;
	}
	else {
		printf("Passed test case 2c: playedCardCount successfully incremented by 1.\n");
	}
	//Check that added card is a coin
	addedCard = post.hand[currentPlayer][post.handCount[currentPlayer]-1];
	if ((addedCard != copper) && (addedCard != silver) && (addedCard != gold)) {
		printf("Failed test case 2d: card added to hand was not a coin\n");
	}
	else {
		printf("Passed test case 2d: card added to hand was a coin.\n");
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
		printf("Failed test case 2e: at least one other player's deck count changed.\n");
	}
	else {
		printf("Passed test case 2e: No other player's deck count was affected.\n");
	}
	if (error2 == -1) {
		printf("Failed test case 2f: at least one other player's hand count changed.\n");
	}
	else {
		printf("Passed test case 2f: No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 2 successfully passed.\n");
	}
	else {
		printf("Test case 2 completed with errors.\n");
	}
	
	
	
	printf("\n\n-------------Card Test #3 Complete -------------\n\n\n");
	return 0;
}