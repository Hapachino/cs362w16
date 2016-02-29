/*
Card Test for Remodel card
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
	printf("\n-------------Card Test #4: Testing remodel card-------------\n\n");

	//initialize variables for card test
	int i, numPlayers, handPos, choice1, choice2, randomSeed;
	int choice3 = 0, bonus = 0;
	int currentPlayer = 0, success = 0, error1 = 0, error2 = 0, playedCardsCorrection = 0;
	struct gameState pre, post;
	int kCards[10] = {adventurer, remodel, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	//seed random number generator and create random values (within boundaries for numPlayers and randomSeed
	srand(time(NULL));
	numPlayers = (rand() % 3) + 2;
	randomSeed = (rand() % 100);
	
	
	
	//Test Case 1: Current player exchanges a card for another costing exactly 2 coins more which has positive supply
	printf("\nCASE 1: Current player exchanges a card for another costing exactly 2 coins more which has positive supply\n");
	//initialize game state and copy to second game state
	initializeGame(numPlayers, kCards, randomSeed, &post);
	handPos = 0, choice1 = 1, choice2 = duchy;
	//set card in handPos to Remodel, choice1 to silver
	post.hand[currentPlayer][handPos] = remodel;
	post.hand[currentPlayer][choice1] = silver;
	
	memcpy(&pre, &post, sizeof(struct gameState));
	//check remodel
	if (cardEffect(remodel, choice1, choice2, choice3, &post, handPos, &bonus) == 1) {
		printf("Failed function: cardEffect(remodel,...) threw an error state.\n");
		success = -1;
	}
	
	//Check that currentPlayer handCount decreased by 2 (+0 because added card went to discard and -2 for trashed card and playing remodel)
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]-2) {
		printf("Failed test case 1a: handCount of currentPlayer did not decrease by 2 (+0 because added card went to discard and -2 for trashed card and playing remodel)\n");
		success = -1;
	}
	else {
		printf("Passed test case 1a: handCount of currentPlayer successfully decreased by 2 (+0 because added card went to discard and -2 for trashed card and playing remodel).\n");
	}
	//Check that remodel card added to played pile
	if  (post.playedCards[pre.playedCardCount] == remodel) {
		printf("Passed test case 1b: Remodel card successfully added to the played card pile.\n");
		success = -1;
	}
	else {
		printf("Failed test case 1b: Remodel card was not successfully added to the played card pile\n");
	}
	//Check that choice2 card added to discard
	if (post.discard[currentPlayer][0] != choice2) {
		printf("Failed test case 1c: card added to discard pile was not choice2.\n");
	}
	else {
		printf("Passed test case 1c: choice2 successfully added to discard pile.\n");
	}
	//Check that choice2 supply decremented
	if (post.supplyCount[choice2] != pre.supplyCount[choice2]-1) {
		printf("Failed test case 1d: choice2 supplyCount did not decrement by 1.\n");
	}
	else {
		printf("Passed test case 1d: choice2 supplyCount successfully decremented by 1.\n");
	}
	//Check where choice1 card went (should be trashed)
	if (post.discard[currentPlayer][post.discardCount[currentPlayer]-1] == pre.hand[currentPlayer][choice1]) {
		printf("Failed test case 1e: choice1 card added to discard rather than trashed.\n");
	}
	else if (post.playedCards[post.playedCardCount-1] == pre.hand[currentPlayer][choice1]) {
		printf("Failed test case 1e: choice1 card added to playedCards rather than trashed.\n");
		playedCardsCorrection = 1;
	}
	else {
		printf("Passed test case 1e: choice1 card successfully trashed.\n");
	}
		//Check that playedCardCount incremented correctly
	if  (post.playedCardCount != pre.playedCardCount + 1 + playedCardsCorrection) {
		printf("Failed test case 1f: playedCardCount not incremented appropriately\n");
		success = -1;
	}
	else {
		printf("Passed test case 1f: playedCardCount successfully incremented.\n");
	}
	//Check that other player's handCount and discardCount were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.discardCount[i] != pre.discardCount[i]) {
			error1 = -1;
		}
		if (post.handCount[i] != pre.handCount[i]) {
			error2 = -1;
		}
	}
	if (error1 == -1) {
		printf("Failed test case 1g: at least one other player's discard count changed.\n");
	}
	else {
		printf("Passed test case 1g: No other player's discard count was affected.\n");
	}
	if (error2 == -1) {
		printf("Failed test case 1h: at least one other player's hand count changed.\n");
	}
	else {
		printf("Passed test case 1h: No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 1 successfully passed.\n");
	}
	else {
		printf("Test case 1 completed with errors.\n");
	}
	
	
	
	
	
	
	//Test Case 2: Current player exchanges a card for another costing more than 2 coins more than trashed card
	printf("\nCASE 2: Current player exchanges a card for another costing more than 2 coins more than trashed card\n");
	//initialize game state and copy to second game state
	initializeGame(numPlayers, kCards, randomSeed, &post);
	handPos = 0, choice1 = 1, choice2 = adventurer, playedCardsCorrection = 0;
	//set card in handPos to Remodel, choice1 to copper
	post.hand[currentPlayer][handPos] = remodel;
	post.hand[currentPlayer][choice1] = copper;

	memcpy(&pre, &post, sizeof(struct gameState));
	//check remodel
	if (cardEffect(remodel, choice1, choice2, choice3, &post, handPos, &bonus) == 1) {
		printf("Failed function: cardEffect(remodel,...) threw an error state.\n");
		success = -1;
	}
	
	//Check that currentPlayer handCount decreased by 2 (+0 because added card went to discard and -2 for trashed card and playing remodel)
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]-2) {
		printf("Failed test case 2a: handCount of currentPlayer did not decrease by 2 (+0 because added card went to discard and -2 for trashed card and playing remodel)\n");
		success = -1;
	}
	else {
		printf("Passed test case 2a: handCount of currentPlayer successfully decreased by 2 (+0 because added card went to discard and -2 for trashed card and playing remodel).\n");
	}
	//Check that remodel card added to played pile
	if  (post.playedCards[pre.playedCardCount] == remodel) {
		printf("Passed test case 2b: Remodel card successfully added to the played card pile.\n");
		success = -1;
	}
	else {
		printf("Failed test case 2b: Remodel card was not successfully added to the played card pile\n");
	}
	//Check that choice2 card added to discard
	if (post.discard[currentPlayer][0] == choice2) {
		printf("Failed test case 2c: choice2 added to discard even though too expensive.\n");
	}
	else {
		printf("Passed test case 2c: choice2 was too expensive, so not added to discard pile.\n");
	}
	//Check where choice1 card went (should be trashed)
	if (post.discard[currentPlayer][post.discardCount[currentPlayer]-1] == pre.hand[currentPlayer][choice1]) {
		printf("Failed test case 2d: choice1 card added to discard rather than trashed.\n");
	}
	else if (post.playedCards[post.playedCardCount-1] == pre.hand[currentPlayer][choice1]) {
		printf("Failed test case 2d: choice1 card added to playedCards rather than trashed.\n");
		playedCardsCorrection = 1;
	}
	else {
		printf("Passed test case 2d: choice1 card successfully trashed.\n");
	}
		//Check that playedCardCount incremented correctly
	if  (post.playedCardCount != pre.playedCardCount + 1 + playedCardsCorrection) {
		printf("Failed test case 2e: playedCardCount not incremented appropriately\n");
		success = -1;
	}
	else {
		printf("Passed test case 2e: playedCardCount successfully incremented.\n");
	}
	//Check that other player's handCount and discardCount were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.discardCount[i] != pre.discardCount[i]) {
			error1 = -1;
		}
		if (post.handCount[i] != pre.handCount[i]) {
			error2 = -1;
		}
	}
	if (error1 == -1) {
		printf("Failed test case 2f: at least one other player's discard count changed.\n");
	}
	else {
		printf("Passed test case 2f: No other player's discard count was affected.\n");
	}
	if (error2 == -1) {
		printf("Failed test case 2g: at least one other player's hand count changed.\n");
	}
	else {
		printf("Passed test case 2g: No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 2 successfully passed.\n");
	}
	else {
		printf("Test case 2 completed with errors.\n");
	}
	
	
	
	
	//Test Case 3: Current player exchanges a card for another costing 1 coin more than trashed card
	printf("\nCASE 3: Current player exchanges a card for another costing 1 coin more than trashed card\n");
	//initialize game state and copy to second game state
	initializeGame(numPlayers, kCards, randomSeed, &post);
	handPos = 0, choice1 = 1, choice2 = smithy, playedCardsCorrection = 0;
	//set card in handPos to Remodel, choice1 to silver
	post.hand[currentPlayer][handPos] = remodel;
	post.hand[currentPlayer][choice1] = silver;
	post.supplyCount[choice2] = 0;
		
	memcpy(&pre, &post, sizeof(struct gameState));
	//check remodel
	if (cardEffect(remodel, choice1, choice2, choice3, &post, handPos, &bonus) == 1) {
		printf("Failed function: cardEffect(remodel,...) threw an error state.\n");
		success = -1;
	}
		
	//Check that currentPlayer handCount decreased by 2 (+0 because added card went to discard and -2 for trashed card and playing remodel)
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]-2) {
		printf("Failed test case 3a: handCount of currentPlayer did not decrease by 2 (+0 because added card went to discard and -2 for trashed card and playing remodel)\n");
		success = -1;
	}
	else {
		printf("Passed test case 3a: handCount of currentPlayer successfully decreased by 2 (+0 because added card went to discard and -2 for trashed card and playing remodel).\n");
	}
	//Check that remodel card added to played pile
	if  (post.playedCards[pre.playedCardCount] == remodel) {
		printf("Passed test case 3b: Remodel card successfully added to the played card pile.\n");
		success = -1;
	}
	else {
		printf("Failed test case 3b: Remodel card was not successfully added to the played card pile\n");
	}
	//Check that choice2 card added to discard
	if (post.discard[currentPlayer][pre.discardCount[currentPlayer]] != choice2) {
		printf("Failed test case 3c: choice2 not added to discard even though it should have been.\n");
	}
	else {
		printf("Passed test case 3c: choice2 successfully added to discard pile.\n");
	}
	//Check that choice2 supply decremented
	if (post.supplyCount[choice2] != pre.supplyCount[choice2]-1) {
		printf("Failed test case 3d: choice2 supplyCount did not decrement even though card should have been gained.\n");
	}
	else {
		printf("Passed test case 3d: choice2 supplyCount successfully decremented.\n");
	}
	//Check where choice1 card went (should be trashed)
	if (post.discard[currentPlayer][post.discardCount[currentPlayer]-1] == pre.hand[currentPlayer][choice1]) {
		printf("Failed test case 3e: choice1 card added to discard rather than trashed.\n");
	}
	else if (post.playedCards[post.playedCardCount-1] == pre.hand[currentPlayer][choice1]) {
		printf("Failed test case 3e: choice1 card added to playedCards rather than trashed.\n");
		playedCardsCorrection = 1;
	}
	else {
		printf("Passed test case 3e: choice1 card successfully trashed.\n");
	}
		//Check that playedCardCount incremented correctly
	if  (post.playedCardCount != pre.playedCardCount + 1 + playedCardsCorrection) {
		printf("Failed test case 3f: playedCardCount not incremented appropriately\n");
		success = -1;
	}
	else {
		printf("Passed test case 3f: playedCardCount successfully incremented.\n");
	}
	//Check that other player's handCount and discardCount were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.discardCount[i] != pre.discardCount[i]) {
			error1 = -1;
		}
		if (post.handCount[i] != pre.handCount[i]) {
			error2 = -1;
		}
	}
	if (error1 == -1) {
		printf("Failed test case 3g: at least one other player's discard count changed.\n");
	}
	else {
		printf("Passed test case 3g: No other player's discard count was affected.\n");
	}
	if (error2 == -1) {
		printf("Failed test case 3h: at least one other player's hand count changed.\n");
	}
	else {
		printf("Passed test case 3h: No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 3 successfully passed.\n");
	}
	else {
		printf("Test case 3 completed with errors.\n");
	}
	
	
	
	
	
	
	//Test Case 4: Current player exchanges the remodel card being played for another card costing exactly 2 coins more (zero supply)
	printf("\nCASE 4: Current player exchanges a card for another costing exactly 2 coins more which has zero supply\n");
	//initialize game state and copy to second game state
	initializeGame(numPlayers, kCards, randomSeed, &post);
	handPos = 0, choice1 = 1, choice2 = duchy;
	//set card in handPos to Remodel, choice1 to silver, and supply of choice2 = 0
	post.hand[currentPlayer][handPos] = remodel;
	post.hand[currentPlayer][choice1] = silver;
	post.supplyCount[choice2] = 0;
	
	memcpy(&pre, &post, sizeof(struct gameState));
	//check remodel
	if (cardEffect(remodel, choice1, choice2, choice3, &post, handPos, &bonus) == 1) {
		printf("Failed function: cardEffect(remodel,...) threw an error state.\n");
		success = -1;
	}
	
	//Check that currentPlayer handCount decreased by 2 (+0 because added card went to discard and -2 for trashed card and playing remodel)
	if (post.handCount[currentPlayer] != pre.handCount[currentPlayer]-2) {
		printf("Failed test case 4a: handCount of currentPlayer did not decrease by 2 (+0 because added card went to discard and -2 for trashed card and playing remodel)\n");
		success = -1;
	}
	else {
		printf("Passed test case 4a: handCount of currentPlayer successfully decreased by 2 (+0 because added card went to discard and -2 for trashed card and playing remodel).\n");
	}
	//Check that remodel card added to played pile
	if  (post.playedCards[pre.playedCardCount] == remodel) {
		printf("Passed test case 4b: Remodel card successfully added to the played card pile.\n");
		success = -1;
	}
	else {
		printf("Failed test case 4b: Remodel card was not successfully added to the played card pile\n");
	}
	//Check that choice2 card not added to discard
	if ((post.discard[currentPlayer][0] == choice2) && (post.discardCount[currentPlayer] == pre.discardCount[currentPlayer]+1)){
		printf("Failed test case 4c: choice2 added to discard pile even though supply was empty.\n");
	}
	else {
		printf("Passed test case 4c: choice2 not added to discard pile since supply was empty.\n");
	}
	//Check that choice2 supply is zero
	if (post.supplyCount[choice2] != 0) {
		printf("Failed test case 4d: choice2 supplyCount is not zero.\n");
	}
	else {
		printf("Passed test case 4d: choice2 supplyCount is zero.\n");
	}
	//Check where choice1 card went (should be trashed)
	if (post.discard[currentPlayer][post.discardCount[currentPlayer]-1] == pre.hand[currentPlayer][choice1]) {
		printf("Failed test case 4e: choice1 card added to discard rather than trashed.\n");
	}
	else if (post.playedCards[post.playedCardCount-1] == pre.hand[currentPlayer][choice1]) {
		printf("Failed test case 4e: choice1 card added to playedCards rather than trashed.\n");
		playedCardsCorrection = 1;
	}
	else {
		printf("Passed test case 4e: choice1 card successfully trashed.\n");
	}
		//Check that playedCardCount incremented correctly
	if  (post.playedCardCount != pre.playedCardCount + 1 + playedCardsCorrection) {
		printf("Failed test case 4f: playedCardCount not incremented appropriately\n");
		success = -1;
	}
	else {
		printf("Passed test case 4f: playedCardCount successfully incremented.\n");
	}
	//Check that other player's handCount and discardCount were not changed
	for (i = 1; i < numPlayers; i++) {
		if (post.discardCount[i] != pre.discardCount[i]) {
			error1 = -1;
		}
		if (post.handCount[i] != pre.handCount[i]) {
			error2 = -1;
		}
	}
	if (error1 == -1) {
		printf("Failed test case 4g: at least one other player's discard count changed.\n");
	}
	else {
		printf("Passed test case 4g: No other player's discard count was affected.\n");
	}
	if (error2 == -1) {
		printf("Failed test case 4h: at least one other player's hand count changed.\n");
	}
	else {
		printf("Passed test case 4h: No other player's hand count was affected.\n");
	}
	if (success == 0) {
		printf("Test case 4 successfully passed.\n");
	}
	else {
		printf("Test case 4 completed with errors.\n");
	}





/*	
	printf("Prior to playing remodel:\ncurrentPlayer = %d\ncard in handPos = %d\nremodel = %d\ncard at choice1 = %d\nsilver = %d\nchoice2 = %d\nduchy = %d\nhandCount = %d\nplayedCardCount = %d\ndiscardCount = %d\nhand contains ", currentPlayer, post.hand[currentPlayer][handPos], remodel, post.hand[currentPlayer][choice1], silver, choice2, duchy, post.handCount[currentPlayer], post.playedCardCount, post.discardCount[currentPlayer]);
	for (i = 0; i < post.handCount[currentPlayer]-1; i++) {
		printf("%d, ", post.hand[currentPlayer][i]);
	}
	printf("%d\ndiscard pile contains: ", post.hand[currentPlayer][i]);
	for (i = 0; i < post.discardCount[currentPlayer]-1; i++) {
		printf("%d, ", post.discard[currentPlayer][i]);
	}
	printf("%d\nplayed card pile contains: ", post.discard[currentPlayer][i]);
	for (i = 0; i < post.playedCardCount-1; i++) {
		printf("%d, ", post.playedCards[i]);
	}
	printf("%d\n\n", post.playedCards[i]);
*/	
/*	
	printf("After playing remodel:\ncurrentPlayer = %d\ncard in handPos = %d\nremodel = %d\ncard at choice1 = %d\nsilver = %d\nchoice2 = %d\nduchy = %d\nhandCount = %d\nplayedCardCount = %d\ndiscardCount = %d\nhand contains ", currentPlayer, post.hand[currentPlayer][handPos], remodel, post.hand[currentPlayer][choice1], silver, choice2, duchy, post.handCount[currentPlayer], post.playedCardCount, post.discardCount[currentPlayer]);
	for (i = 0; i < post.handCount[currentPlayer]-1; i++) {
		printf("%d, ", post.hand[currentPlayer][i]);
	}
	printf("%d\ndiscard pile contains: ", post.hand[currentPlayer][i]);
	for (i = 0; i < post.discardCount[currentPlayer]-1; i++) {
		printf("%d, ", post.discard[currentPlayer][i]);
	}
	printf("%d\nplayed card pile contains: ", post.discard[currentPlayer][i]);
	for (i = 0; i < post.playedCardCount-1; i++) {
		printf("%d, ", post.playedCards[i]);
	}
	printf("%d\n\n", post.playedCards[i]);
*/
	
	printf("\n\n-------------Card Test #4 Complete -------------\n\n\n");
	return 0;
}