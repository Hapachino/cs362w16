/*Tanna Richardson
  CS362 - Winter 2016
  Assignment 3
  Card test for: smithy
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PLAYERS 2
#define TEST_CARD smithy
#define TEST_POS 0
 
int main () {
	int i, j;			//loop controls
	int result;			//return value for function calls
	int failed;			//flags for tests
	
	struct gameState *g = malloc(sizeof(struct gameState));		//working game state
	struct gameState *pre = malloc(sizeof(struct gameState));	//reference game state; stored before functions run
	int selectedCards[10] = {adventurer, council_room, feast, gardens, mine, smithy, village, tribute, salvager, sea_hag};	
	int seed = 10;
	
	int choice1, choice2, choice3;	//choices for card effect
	int coin_bonus;				//coins added by card
	
	
//---Test smithy (all choices = -1, no bonus)
/*---Expected result: 
	- Game and turn settings are unchanged
	- Other player's cards (hand, deck, discard) are unchanged
	- Current player's discard is unchanged
	- Played card count increased by 1
	- Smithy card added to played pile (in last position)
	- Smithy card removed from hand
	- Last 3 cards of current player's deck moved to hand
	- Current player's deckCount is decreased by 3
	- Current player's handCount is increased by 2 (+3 new cards, -1 smithy)
	- No bonus coins
*/
	printf("*** Testing valid smithy ***\n");
	printf("Errors: ");
	//Setup card options
	choice1 = -1;
	choice2 = -1;
	choice3 = -1;
	coin_bonus = 0;
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.\n");
		return -1;
	}
	//Set deck to 5 copper cards
	g->deckCount[whoseTurn(g)] = 5;
	for (i = 0; i < 5; i++){
		g->deck[whoseTurn(g)][i] = copper;
	}
	//Set test position in hand to test card
	g->hand[whoseTurn(g)][TEST_POS] = TEST_CARD;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to execute card
	result = cardEffect(TEST_CARD, choice1, choice2, choice3, g, TEST_POS, &coin_bonus);
	failed = 0;
	if (result != 0){
		printf("\nReturn value: %d, Expected: %d\n", result, 0);
		failed = 1;
	}
	//Check game/turn settings
	if (checkNumPlayers(pre, g) < 0){
		printf("\nNumPlayers: %d, Expected: %d\n", g->numPlayers, pre->numPlayers);
		failed = 1;
	}
	result = checkSupply(pre, g);
	if (result != 0){
		printf("\nSupply count for card %d: %d, Expected: %d\n", result, g->supplyCount[result], pre->supplyCount[result]);
		failed = 1;
	}
	result = checkEmbargo(pre, g);
	if (result != 0){
		printf("\nEmbargo for card %d: %d, Expected: %d\n", result, g->embargoTokens[result], pre->embargoTokens[result]);
		failed = 1;
	}
	if (checkOutpost(pre, g) < 0){
		printf("\noutpostPlayed: %d, Expected: %d\n", g->outpostPlayed, pre->outpostPlayed);
		printf("\noutpostTurn: %d, Expected: %d\n", g->outpostTurn, pre->outpostTurn);
		failed = 1;
	}	
	if (checkTurn(pre, g) < 0){
		printf("\nwhoseTurn: %d, Expected: %d\n", g->whoseTurn, pre->whoseTurn);
		failed = 1;
	}
	if (checkPhase(pre, g) < 0){
		printf("\nphase: %d, Expected: %d\n", g->phase, pre->phase);
		failed = 1;
	}	
	if (checkNumActions(pre, g) < 0){
		printf("\nnumActions: %d, Expected: %d\n", g->numActions, pre->numActions);
		failed = 1;
	}	
	if (checkCoins(pre, g) < 0){
		printf("\ncoins: %d, Expected: %d\n", g->coins, pre->coins);
		failed = 1;
	}
	if (checkNumBuys(pre, g) < 0){
		printf("\nnumBuys: %d, Expected: %d\n", g->numBuys, pre->numBuys);
		failed = 1;
	}
	//Check all player's discard unchanged
	if (checkDiscards(pre, g) < 0){
		printf("\nDiscards changed after smithy\n");
		//Print expected and actual discards for each player
		for (i = 0; i < NUM_PLAYERS; i++){
			printf("    Discard pile for player %d:\n", i);
			printf("      Count: %d, Expected: %d\n", g->discardCount[i], pre->discardCount[i]);
			if (g->discardCount[i] > 0){
				printf("      Actual Cards: ");
				for (j = 0; j < g->discardCount[i]; j++){
					printf("%d ", g->discard[i][j]);
				}
				printf("\n      Expected Cards: ");
				for (j = 0; j < pre->discardCount[i]; j++){
					printf("%d ", pre->discard[i][j]);
				}
			}
		}
		failed = 1;
	}
	//Check deck unchanged for other players
	for (i = 0; i < g->numPlayers; i++){
		//skip if current player
		if (i == whoseTurn(g)){
			continue;
		}
		if (pre->deckCount[i] != g->deckCount[i]){
			printf("\nPlayer %d's deckCount: %d, Expected: %d", i, g->deckCount[i], pre->deckCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->deckCount[i]; j++){
				if (pre->deck[i][j] != g->deck[i][j]){
					printf("\nPlayer %d's deck[%d]: %d, Expected: %d", i, j, g->deck[i][j], pre->deck[i][j]);
					failed = 1;
				}
			}
		}
	}
	//Check hand unchanged for other players
	for (i = 0; i < g->numPlayers; i++){
		//skip if current player
		if (i == whoseTurn(g)){
			continue;
		}
		if (pre->handCount[i] != g->handCount[i]){
			printf("\nPlayer %d's handCount: %d, Expected: %d", i, g->handCount[i], pre->handCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->handCount[i]; j++){
				if (pre->hand[i][j] != g->hand[i][j]){
					printf("\nPlayer %d's hand[%d]: %d, Expected: %d", i, j, g->hand[i][j], pre->hand[i][j]);
					failed = 1;
				}
			}
		}
	}
	//Check smithy added to played pile
	if (g->playedCardCount != pre->playedCardCount + 1){
		printf("\nPlayed card count: %d, Expected: %d", g->playedCardCount, pre->playedCardCount + 1);
		failed = 1;
	} else if (g->playedCards[g->playedCardCount - 1] != TEST_CARD){
		printf("\nLast played card: %d, Expected: %d", g->playedCards[g->playedCardCount - 1], TEST_CARD);
		failed = 1;		
	}
	//Check 3 cards added to hand and smithy removed
	if (g->handCount[whoseTurn(g)] != pre->handCount[whoseTurn(g)] + 2){
		printf("\nCurrent player's hand count: %d, Expected: %d", g->handCount[whoseTurn(g)], pre->handCount[whoseTurn(g)] + 2);
		failed = 1;		
	}
	//Check 3 cards removed from deck
	if (g->deckCount[whoseTurn(g)] != pre->deckCount[whoseTurn(g)] - 3){
		printf("\nCurrent player's deck count: %d, Expected: %d", g->deckCount[whoseTurn(g)], pre->deckCount[whoseTurn(g)] - 3);
		failed = 1;		
	}
	//Check cards removed from deck = cards added to hand
	for(i = 1; i <= 3; i++){
		if (g->hand[whoseTurn(g)][g->deckCount[whoseTurn(g)] - i] != pre->deck[whoseTurn(g)][pre->deckCount[whoseTurn(g)] - i]){
			printf("\nCurrent player's hand[%d]: %d, Expected: %d", g->handCount[whoseTurn(g)] - i, g->hand[whoseTurn(g)][g->deckCount[whoseTurn(g)] - i], pre->deck[whoseTurn(g)][pre->deckCount[whoseTurn(g)] - i]);
			failed = 1;		
		}	
	}
	//Check no bonus coins added
	if (coin_bonus != 0){
		printf("\nCoin bonus after smithy: %d, Expected: %d", coin_bonus, 0);
		failed = 1;		
	}	
	//Final check
	if (failed){
		printf("\nResult: FAIL\n");
	} else {
		printf("none");
		printf("\nResult: PASS\n");
	}

	
	return 0;
}
