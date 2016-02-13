/*Tanna Richardson
  CS362 - Winter 2016
  Assignment 4
  Random test for: village
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 		//for random number generator

#define TEST_CARD village
#define NUM_TESTS 5000
 
int main () {
	
	//Test variables
	int i, j, k;			//loop controls
	int result;				//return value for function calls
	int failed;				//flags for tests
	int found;				//flag for search loops
	int testsPassed = 0;	//counts total tests passed
	int testsFailed = 0;	//counts total tests failed
	int testsAborted = 0;	//counts total tests aborted due to incorrect setup
	int errors[11] = {0};	//count for each check failed
	
	//Game variables
	struct gameState *g;										//working game state
	struct gameState *pre = malloc(sizeof(struct gameState));	//reference game state; stored before functions run
	int seed;													//random seed for generating game
	
	//Test card variables
	int choice1, choice2, choice3;	//choices for card effect
	int coin_bonus;					//coins added by card
	int position;					//position of test card in hand

	//Setup random seed
	srand(time(NULL));
	seed = rand() % 3;
	
	//Randomly generate NUM_TESTS games, run Adventurer and check results
	for (k = 1; k <= NUM_TESTS; k++){
		printf("*** Test: %d ***\n", k);
		printf("Errors: ");
		
		//Setup card options
		choice1 = rand() % 3;
		choice2 = rand() % 3;
		choice3 = rand() % 3;
		coin_bonus = 0;
		
		//Create random game
		g = randomGame(seed++);
		
		//Check that hand contains test card; If not set pos 0 = test card
		found = 0;
		for (i = 0; i < g->handCount[whoseTurn(g)]; i++){
			if (g->hand[whoseTurn(g)][i] == TEST_CARD){
				found = 1;
				position = i;
				break;
			}
		}
		if (!found){
			g->hand[whoseTurn(g)][0] = TEST_CARD;
			position = 0;
		}

		//Save current state
		memcpy(pre, g, sizeof(struct gameState));
		
		//[0] Attempt to execute card
		result = cardEffect(TEST_CARD, choice1, choice2, choice3, g, position, &coin_bonus);
		failed = 0;
		if (result != 0){
			printf("\nReturn value: %d, Expected: %d", result, 0);
			failed = 1;
			errors[0]++;
		}

		//[1] Check game/turn settings
		//Expected Result: unchanged
		if (checkNumPlayers(pre, g) < 0){
			printf("\nNumPlayers: %d, Expected: %d", g->numPlayers, pre->numPlayers);
			failed = 1;
			errors[1]++;
		}
		result = checkSupply(pre, g);
		if (result != 0){
			printf("\nSupply count for card %d: %d, Expected: %d", result, g->supplyCount[result], pre->supplyCount[result]);
			failed = 1;
			errors[1]++;
		}
		result = checkEmbargo(pre, g);
		if (result != 0){
			printf("\nEmbargo for card %d: %d, Expected: %d", result, g->embargoTokens[result], pre->embargoTokens[result]);
			failed = 1;
			errors[1]++;
		}
		if (checkOutpost(pre, g) < 0){
			printf("\noutpostPlayed: %d, Expected: %d", g->outpostPlayed, pre->outpostPlayed);
			printf("\noutpostTurn: %d, Expected: %d", g->outpostTurn, pre->outpostTurn);
			failed = 1;
			errors[1]++;
		}	
		if (checkTurn(pre, g) < 0){
			printf("\nwhoseTurn: %d, Expected: %d", g->whoseTurn, pre->whoseTurn);
			failed = 1;
			errors[1]++;
		}
		if (checkPhase(pre, g) < 0){
			printf("\nphase: %d, Expected: %d", g->phase, pre->phase);
			failed = 1;
			errors[1]++;
		}	
		if (checkCoins(pre, g) < 0){
			printf("\ncoins: %d, Expected: %d", g->coins, pre->coins);
			failed = 1;
			errors[1]++;
		}
		if (checkNumBuys(pre, g) < 0){
			printf("\nnumBuys: %d, Expected: %d", g->numBuys, pre->numBuys);
			failed = 1;
			errors[1]++;
		}
		
		//[2] Check discard for other players
		//Expected Result: unchanged
		for (i = 0; i < g->numPlayers; i++){
			//skip if current player
			if (i == whoseTurn(g)){
				continue;
			}
			if (pre->discardCount[i] != g->discardCount[i]){
				printf("\nPlayer %d's discardCount: %d, Expected: %d", i, g->discardCount[i], pre->discardCount[i]);
				failed = 1;
				errors[2]++;
			} else {   //check each card
				for (j = 0; j < g->discardCount[i]; j++){
					if (pre->discard[i][j] != g->discard[i][j]){
						printf("\nPlayer %d's discard[%d]: %d, Expected: %d", i, j, g->discard[i][j], pre->discard[i][j]);
						failed = 1;
						errors[2]++;
					}
				}
			}
		}
		
		//[3] Check deck for other players
		//Expected Result: unchanged
		for (i = 0; i < g->numPlayers; i++){
			//skip if current player
			if (i == whoseTurn(g)){
				continue;
			}
			if (pre->deckCount[i] != g->deckCount[i]){
				printf("\nPlayer %d's deckCount: %d, Expected: %d", i, g->deckCount[i], pre->deckCount[i]);
				failed = 1;
				errors[3]++;
			} else {   //check each card
				for (j = 0; j < g->deckCount[i]; j++){
					if (pre->deck[i][j] != g->deck[i][j]){
						printf("\nPlayer %d's deck[%d]: %d, Expected: %d", i, j, g->deck[i][j], pre->deck[i][j]);
						failed = 1;
						errors[3]++;
					}
				}
			}
		}
		
		//[4] Check hand for other players
		//Expected Result: unchanged
		for (i = 0; i < g->numPlayers; i++){
			//skip if current player
			if (i == whoseTurn(g)){
				continue;
			}
			if (pre->handCount[i] != g->handCount[i]){
				printf("\nPlayer %d's handCount: %d, Expected: %d", i, g->handCount[i], pre->handCount[i]);
				failed = 1;
				errors[4]++;
			} else {   //check each card
				for (j = 0; j < g->handCount[i]; j++){
					if (pre->hand[i][j] != g->hand[i][j]){
						printf("\nPlayer %d's hand[%d]: %d, Expected: %d", i, j, g->hand[i][j], pre->hand[i][j]);
						failed = 1;
						errors[4]++;
					}
				}
			}
		}
	
		//[5] Check bonus coins
		//Expected Results: unchanged
		if (coin_bonus != 0){
			printf("\nCoin bonus after adventurer: %d, Expected: %d", coin_bonus, 0);
			failed = 1;	
			errors[5]++;			
		}	
		
		//[6] Check played pile for test card
		//Expected Result: count = +1, last card in played pile = test card
		if (g->playedCardCount != pre->playedCardCount + 1){
			printf("\nPlayed card count: %d, Expected: %d", g->playedCardCount, pre->playedCardCount + 1);
			failed = 1;
			errors[6]++;
		} else if (g->playedCards[g->playedCardCount - 1] != TEST_CARD){
			printf("\nLast played card: %d, Expected: %d", g->playedCards[g->playedCardCount - 1], TEST_CARD);
			failed = 1;		
			errors[6]++;
		}
		
		//[7] Check for +2 actions
		//Expected Results: numActions increased by 2
		if (g->numActions != pre->numActions + 2){
			printf("\nnumActions: %d, Expected: %d", g->numActions, pre->numActions + 2);
			failed = 1;
			errors[7]++;
		}	
		
		//[8] Check 1 card added to hand, test card removed
		//Expected Results: handCount unchanged (+1 card, -1 village), cards in hand changed
		if (g->handCount[whoseTurn(g)] != pre->handCount[whoseTurn(g)]){
			printf("\nCurrent player's hand count: %d, Expected: %d", g->handCount[whoseTurn(g)], pre->handCount[whoseTurn(g)]);
			failed = 1;	
			errors[8]++;			
		}
		found = 0;	//found = change found
		for (i = 0; i < g->handCount[whoseTurn(g)]; i++){
			if (g->hand[whoseTurn(g)][i] != pre->hand[whoseTurn(g)][i]){
				found = 1;
				break;
			}
		}
		if (!found){
			printf("\nContents of current player's hand did not change");
			failed = 1;	
			errors[8]++;
		}
		
		//Note: deck and discard may be combined and shuffled during card execution.
		//[9] Check 1 card removed from deck/discard
		//Expected Results: deckCount + discardCount = -1
		if ( (g->deckCount[whoseTurn(g)] + g->discardCount[whoseTurn(g)]) != (pre->deckCount[whoseTurn(g)] + pre->discardCount[whoseTurn(g)] - 1) ){
			printf("\nCurrent player's hand count: %d, Expected: %d", (g->deckCount[whoseTurn(g)] + g->discardCount[whoseTurn(g)]), (pre->deckCount[whoseTurn(g)] + pre->discardCount[whoseTurn(g)] - 1));
			failed = 1;	
			errors[9]++;						
		}
		
		//[10] Check current player's total cards unchanged (1 card just moved from deck/discard to hand) EXCEPT test card moved to played
		//Expected Results: full deck count unchanged for every card, except test card -1
		for (i = 0; i <= treasure_map; i++){
			if (i == TEST_CARD){
				if (fullDeckCount(whoseTurn(g), i, g) != fullDeckCount(whoseTurn(g), i, pre) - 1){
				printf("\nCurrent player's full count for card %d: %d, Expected: %d", i, fullDeckCount(whoseTurn(g), i, g), fullDeckCount(whoseTurn(g), i, pre) - 1);
				failed = 1;	
				errors[10]++;			
				}
			} else { 
				if (fullDeckCount(whoseTurn(g), i, g) != fullDeckCount(whoseTurn(g), i, pre)){
					printf("\nCurrent player's full count for card %d: %d, Expected: %d", i, fullDeckCount(whoseTurn(g), i, g), fullDeckCount(whoseTurn(g), i, pre));
					failed = 1;	
					errors[10]++;			
				}
			}
		}

		//Final check
		if (failed){
			printf("\nResult: FAIL\n\n");
			testsFailed++;
		} else {
			printf("none");
			printf("\nResult: PASS\n\n");
			testsPassed++;
		}

	//end current test
	} 
	
	//Print test summary
	printf("-----------------------------------------------------------\n");
	printf("\tSummary for Random Tests: Village Card\n");
	printf("-----------------------------------------------------------\n");
	printf("Test Summary:\n");
	printf("Passed: %d\n", testsPassed);
	printf("Failed: %d\n", testsFailed);
	printf("Aborted: %d\n", testsAborted);
	if (testsFailed > 0){
		printf("\nError Summary:\n");
		printf("[0] Invalid cardEffect return value: %d\n", errors[0]);
		printf("[1] Game state changed: %d\n", errors[1]);
		printf("[2] Other player's discard changed: %d\n", errors[2]);
		printf("[3] Other player's deck changed: %d\n", errors[3]);
		printf("[4] Other player's hand changed: %d\n", errors[4]);
		printf("[5] Coin bonus changed: %d\n", errors[5]);
		printf("[6] Village not moved to played pile: %d\n", errors[6]);
		printf("[7] Actions not changed correctly (+2): %d\n", errors[7]);
		printf("[8] Player's hand not changed correctly (+1 card, -1 village): %d\n", errors[8]);
		printf("[9] Drawn card not removed from player's deck/discard: %d\n", errors[9]);
		printf("[10] Player's full deck count changed: %d\n", errors[10]);
	}
		
	return 0;
}
