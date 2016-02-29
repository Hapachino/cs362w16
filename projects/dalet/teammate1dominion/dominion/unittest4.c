/*
Unit Test for isGameOver() function
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
function accepts (struct gameState *state) */

int main() {
	printf("\n-------------Unit Test #4: Testing isGameOver() function-------------\n\n");

	//initialize variables for unit test
	int i, numPlayers, randomSeed;
	int success = 0;
	struct gameState state;
	int kCards[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
	
	//seed random number generator and create random values (within boundaries for numPlayers and randomSeed
	srand(time(NULL));
	numPlayers = (rand() % 3) + 2;
	randomSeed = (rand() % 100);
	
	
	//Test Case 1: Game is not over. 0 supply piles are empty
	printf("\nCASE 1: Game is not over. 0 supply piles are empty\n");
	initializeGame(numPlayers, kCards, randomSeed, &state);
	//check isGameOver correctly determines outcome
	if (isGameOver(&state) == 1) {
		printf("Failed function: isGameOver incorrectly determined that game was over.\n");
		success = -1;
	}
	else {
		printf("isGameOver successfully determined that game was not over.\n");
	}
	if (success == 0) {
		printf("Test case 1 successfully passed.\n");
	}
	
	
	
	//Test Case 2: Game is not over. 1 supply pile (not Province) is empty
	printf("\nCASE 2: Game is not over. 1 supply pile (not Province) is empty\n");
	success = 0;
	initializeGame(numPlayers, kCards, randomSeed, &state);
	
	//alter game state to empty one supply pile (not Province)
	state.supplyCount[copper] = 0;
	
	//check isGameOver correctly determines outcome
	if (isGameOver(&state) == 1) {
		printf("Failed function: isGameOver incorrectly determined that game was over.\n");
		success = -1;
	}
	else {
		printf("isGameOver successfully determined that game was not over.\n");
	}
	if (success == 0) {
		printf("Test case 2 successfully passed.\n");
	}
	
	
	
	//Test Case 3: Game is over. 1 supply pile is empty and it is the Province pile
	printf("\nCASE 3: Game is over. The Province supply pile is empty\n");
	success = 0;
	initializeGame(numPlayers, kCards, randomSeed, &state);
	
	//alter game state to empty Province supply pile
	state.supplyCount[province] = 0;
	
	//check isGameOver correctly determines outcome
	if (isGameOver(&state) == 0) {
		printf("Failed function: isGameOver incorrectly determined that game was not over.\n");
		success = -1;
	}
	else {
		printf("isGameOver successfully determined that game was over.\n");
	}
	if (success == 0) {
		printf("Test case 3 successfully passed.\n");
	}
	
	
	
	//Test Case 4: Game is not over. 2 supply piles (neither Province) is empty
	printf("\nCASE 4: Game is not over. 2 supply piles (neither Province) is empty\n");
	success = 0;
	initializeGame(numPlayers, kCards, randomSeed, &state);
	
	//alter game state to empty two supply piles (not Province)
	state.supplyCount[copper] = 0;
	state.supplyCount[minion] = 0;
	
	//check isGameOver correctly determines outcome
	if (isGameOver(&state) == 1) {
		printf("Failed function: isGameOver incorrectly determined that game was over.\n");
		success = -1;
	}
	else {
		printf("isGameOver successfully determined that game was not over.\n");
	}
	if (success == 0) {
		printf("Test case 4 successfully passed.\n");
	}
	
	
	
	//Test Case 5: Game is over. 2 supply piles are empty and one is the Province pile
	printf("\nCASE 5: Game is over. 2 supply piles are empty and one is the Province pile\n");
	success = 0;
	initializeGame(numPlayers, kCards, randomSeed, &state);
	
	//alter game state to empty two supply piles (one Province)
	state.supplyCount[copper] = 0;
	state.supplyCount[province] = 0;
	
	//check isGameOver correctly determines outcome
	if (isGameOver(&state) == 0) {
		printf("Failed function: isGameOver incorrectly determined that game was not over.\n");
		success = -1;
	}
	else {
		printf("isGameOver successfully determined that game was over.\n");
	}
	if (success == 0) {
		printf("Test case 5 successfully passed.\n");
	}
	
	
	
	//Test Case 6: Game is over. copper, minion, and sea_hag supply piles are empty
	printf("\nCASE 6: Game is over. opper, sea_hag, and minion supply piles are empty\n");
	success = 0;
	initializeGame(numPlayers, kCards, randomSeed, &state);
	
	//alter game state to empty three supply piles (not Province)
	state.supplyCount[copper] = 0;
	state.supplyCount[minion] = 0;
	state.supplyCount[sea_hag] = 0;
	
	//check isGameOver correctly determines outcome
	if (isGameOver(&state) == 0) {
		printf("Failed function: isGameOver incorrectly determined that game was not over.\n");
		success = -1;
	}
	else {
		printf("isGameOver successfully determined that game was over.\n");
	}
	if (success == 0) {
		printf("Test case 6 successfully passed.\n");
	}
	
	
	
	//Test Case 7: Game is over. 3 supply piles are empty (none Province)
	printf("\nCASE 7: Game is over. 3 supply piles are empty (none Province)\n");
	success = 0;
	initializeGame(numPlayers, kCards, randomSeed, &state);
	
	//alter game state to empty three supply piles (not Province)
	state.supplyCount[copper] = 0;
	state.supplyCount[minion] = 0;
	state.supplyCount[adventurer] = 0;
	
	//check isGameOver correctly determines outcome
	if (isGameOver(&state) == 0) {
		printf("Failed function: isGameOver incorrectly determined that game was not over.\n");
		success = -1;
	}
	else {
		printf("isGameOver successfully determined that game was over.\n");
	}
	if (success == 0) {
		printf("Test case 6 successfully passed.\n");
	}
	
	
	
	//Test Case 8: Game is over. 3 supply piles are empty (one is Province)
	printf("\nCASE 8: Game is over. 3 supply piles are empty (one is Province)\n");
	success = 0;
	initializeGame(numPlayers, kCards, randomSeed, &state);
	
	//alter game state to empty three supply piles (one Province)
	state.supplyCount[copper] = 0;
	state.supplyCount[minion] = 0;
	state.supplyCount[province] = 0;
	
	//check isGameOver correctly determines outcome
	if (isGameOver(&state) == 0) {
		printf("Failed function: isGameOver incorrectly determined that game was not over.\n");
		success = -1;
	}
	else {
		printf("isGameOver successfully determined that game was over.\n");
	}
	if (success == 0) {
		printf("Test case 8 successfully passed.\n");
	}
	
	
	
	//Test Case 9: Game is over. 12 supply piles are empty
	printf("\nCASE 9: Game is over. 12 supply piles are empty\n");
	success = 0;
	initializeGame(numPlayers, kCards, randomSeed, &state);
	
	//alter game state to empty all supply piles
	for (i = 0; i < 12; i++) {
		state.supplyCount[i] = 0;
	}
	
	//check isGameOver correctly determines outcome
	if (isGameOver(&state) == 0) {
		printf("Failed function: isGameOver incorrectly determined that game was not over.\n");
		success = -1;
	}
	else {
		printf("isGameOver successfully determined that game was over.\n");
	}
	if (success == 0) {
		printf("Test case 9 successfully passed.\n");
	}
	
	
	
	//Test Case 10: Game is over. All supply piles are empty
	printf("\nCASE 10: Game is over. All supply piles are empty\n");
	success = 0;
	initializeGame(numPlayers, kCards, randomSeed, &state);
	
	//alter game state to empty all supply piles
	for (i = 0; i < 25; i++) {
		state.supplyCount[i] = 0;
	}
	
	//check isGameOver correctly determines outcome
	if (isGameOver(&state) == 0) {
		printf("Failed function: isGameOver incorrectly determined that game was not over.\n");
		success = -1;
	}
	else {
		printf("isGameOver successfully determined that game was over.\n");
	}
	if (success == 0) {
		printf("Test case 10 successfully passed.\n");
	}
	
	printf("\n\n-------------Unit Test #4 Complete -------------\n\n\n");
	return 0;
}