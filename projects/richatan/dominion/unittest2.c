/*Tanna Richardson
  CS362 - Winter 2016
  Assignment 3
  Unit test for: gainCard()
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
#define TEST_CARD mine
#define INVALID_CARD remodel
 
int main () {
	int i, j;			//loop controls
	int result;			//return value for function calls
	int failed;			//flags for tests
	
	struct gameState *g = malloc(sizeof(struct gameState));		//working game state
	struct gameState *pre = malloc(sizeof(struct gameState));	//reference game state; stored before functions run
	int selectedCards[10] = {adventurer, council_room, feast, gardens, mine, smithy, village, tribute, salvager, sea_hag};	
	int seed = 10;


//---Test supplyCount for card = 0 
//---Expected result: error
	printf("*** Testing supplyCount = 0 ***\n");
	printf("Errors: ");
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.");
		return -1;
	}
	//Change supplyCount for test card to 0
	g->supplyCount[TEST_CARD] = 0;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to gain card
	result = gainCard(TEST_CARD, g, 0, whoseTurn(g));
	failed = 0;
	if (result != -1){
		printf("\nReturn value: %d, Expected: %d", result, -1);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("\ngameState changed");
		failed = 1;
	} 
	//Final check
	if (failed){
		printf("\nResult: FAIL\n\n");
	} else {
		printf("none");
		printf("\nResult: PASS\n\n");
	}
	
	
	
//---Test invalid card (card not included in game; supplyCount = -1)
//---Expected result: error
	printf("*** Testing invalid game card ***\n");
	printf("Errors: ");
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.");
		return -1;
	}
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to gain invalid card
	result = gainCard(INVALID_CARD, g, 0, whoseTurn(g));
	failed = 0;
	if (result != -1){
		printf("\nReturn value: %d, Expected: %d", result, -1);
		failed = 1;
	}
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("\ngameState changed");
		failed = 1;
	} 
	//Final check
	if (failed){
		printf("\nResult: FAIL\n\n");
	} else {
		printf("none");
		printf("\nResult: PASS\n\n");
	}
	
	
//---Test invalid toFlag parameter
//---Expected result: error
	printf("*** Testing invalid toFlag ***\n");
	printf("Errors: ");
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.");
		return -1;
	}
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to gain card with invalid parameter
	result = gainCard(TEST_CARD, g, 4, whoseTurn(g));
	failed = 0;
	if (result != -1){
		printf("\nReturn value: %d, Expected: %d", result, -1);
		failed = 1;
	}	
	//Check game state is unchanged
	if (checkGameState(pre, g) < 0){
		printf("\ngameState changed");
		failed = 1;
	} 
	//Final check
	if (failed){
		printf("\nResult: FAIL\n\n");
	} else {
		printf("none");
		printf("\nResult: PASS\n\n");
	}
	
	
	
//---Test toFlag = 0
/*---Expected results: 
	- Game and turn settings are unchanged
	- Supply count for other cards are unchanged
	- Supply count for selected card is decreased by 1
	- Other player's cards (hand, deck, discard) are unchanged
	- Played cards are unchanged		
	- Current player's hand and deck are unchanged
	- Current player's discardCount is 1 more than before gainCard
	- Current player's discard is the same except additional card in last position
*/
	printf("*** Testing toFlag = 0 ***\n");
	printf("Errors: ");
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.");
		return -1;
	} 
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Run gainCard and check results
	failed = 0;
	result = gainCard(TEST_CARD, g, 0, whoseTurn(g));
	if (result == -1){
		printf("\nReturn value: %d, Expected: %d", result, 0);
		failed = 1;
	}
	//Check game/turn settings
	if (checkNumPlayers(pre, g) < 0){
		printf("\nNumPlayers: %d, Expected: %d", g->numPlayers, pre->numPlayers);
		failed = 1;
	}
	result = checkEmbargo(pre, g);
	if (result != 0){
		printf("\nEmbargo for card %d: %d, Expected: %d", result, g->embargoTokens[result], pre->embargoTokens[result]);
		failed = 1;
	}
	if (checkOutpost(pre, g) < 0){
		printf("\noutpostPlayed: %d, Expected: %d", g->outpostPlayed, pre->outpostPlayed);
		printf("\noutpostTurn: %d, Expected: %d", g->outpostTurn, pre->outpostTurn);
		failed = 1;
	}	
	if (checkTurn(pre, g) < 0){
		printf("\nwhoseTurn: %d, Expected: %d", g->whoseTurn, pre->whoseTurn);
		failed = 1;
	}
	if (checkPhase(pre, g) < 0){
		printf("\nphase: %d, Expected: %d", g->phase, pre->phase);
		failed = 1;
	}	
	if (checkNumActions(pre, g) < 0){
		printf("\nnumActions: %d, Expected: %d", g->numActions, pre->numActions);
		failed = 1;
	}	
	if (checkCoins(pre, g) < 0){
		printf("\ncoins: %d, Expected: %d", g->coins, pre->coins);
		failed = 1;
	}
	if (checkNumBuys(pre, g) < 0){
		printf("\nnumBuys: %d, Expected: %d", g->numBuys, pre->numBuys);
		failed = 1;
	}
	//Check supply for gained card is decreased by 1
	if (g->supplyCount[TEST_CARD] != pre->supplyCount[TEST_CARD]-1){
		printf("\nSupply count for card %d: %d, Expected: %d", TEST_CARD, g->supplyCount[TEST_CARD], pre->supplyCount[TEST_CARD]-1);
		failed = 1;
	}
	//Check supply for other cards remains the same
	for (i = 0; i <= treasure_map; i++){
		//if test card, skip
		if (i == TEST_CARD){
			continue;
		}
		if (pre->supplyCount[i] != g->supplyCount[i]){
			printf("\nSupply count for card %d: %d, Expected: %d", i, g->supplyCount[i], pre->supplyCount[i]);
			failed = 1;
		}
	}
	//Check all hand, deck and played cards unchanged
	if (checkHands(pre, g) < 0){
		printf("\nHands changed after gainCard\n");
		//Print expected and actual hand for each player
		for (i = 0; i < NUM_PLAYERS; i++){
			printf("    Hand for player %d:\n", i);
			printf("      Count: %d, Expected: %d\n", g->handCount[i], pre->handCount[i]);
			if (g->handCount[i] > 0){
				printf("      Actual Cards: ");
				for (j = 0; j < g->handCount[i]; j++){
					printf("%d ", g->hand[i][j]);
				}
				printf("\n      Expected Cards: ");
				for (j = 0; j < pre->handCount[i]; j++){
					printf("%d ", pre->hand[i][j]);
				}
			}
		}
		failed = 1;
	}
	if (checkDecks(pre, g) < 0){
		printf("\nDecks changed after gainCard\n");
		//Print expected and actual deck for each player
		for (i = 0; i < NUM_PLAYERS; i++){
			printf("    Deck for player %d:\n", i);
			printf("      Count: %d, Expected: %d\n", g->deckCount[i], pre->deckCount[i]);
			if (g->deckCount[i] > 0){
				printf("      Actual Cards: ");
				for (j = 0; j < g->deckCount[i]; j++){
					printf("%d ", g->deck[i][j]);
				}
				printf("\n      Expected Cards: ");
				for (j = 0; j < pre->deckCount[i]; j++){
					printf("%d ", pre->deck[i][j]);
				}
			}
		}
		failed = 1;
	}
	if (checkPlayed(pre, g) < 0){
		printf("\nPlayed cards changed after gainCard\n");
		//Print expected and actual played cards
		printf("    Played count: %d, Expected: %d\n", g->playedCardCount, pre->playedCardCount);
		if (g->playedCardCount > 0){
			printf("    Actual Cards: ");
			for (i = 0; i < g->playedCardCount; i++){
				printf("%d ", g->playedCards[i]);
			}
			printf("\n    Expected Cards: ");
			for (i = 0; i < pre->playedCardCount; i++){
				printf("%d ", pre->playedCards[i]);
			}
		}
		failed = 1;
	}
	//Check discard unchanged for other players
	for (i = 0; i < g->numPlayers; i++){
		//skip if current player
		if (i == whoseTurn(g)){
			continue;
		}
		if (pre->discardCount[i] != g->discardCount[i]){
			printf("\nPlayer %d's discardCount: %d, Expected: %d", i, g->discardCount[i], pre->discardCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->discardCount[i]; j++){
				if (pre->discard[i][j] != g->discard[i][j]){
					printf("\nPlayer %d's discard[%d]: %d, Expected: %d", i, j, g->discard[i][j], pre->discard[i][j]);
					failed = 1;
				}
			}
		}
	}	
	//Check current player's discardCount increased by 1
	if (g->discardCount[whoseTurn(g)] != pre->discardCount[whoseTurn(g)]+1){
			printf("\nCurrent player's discardCount: %d, Expected: %d", g->discardCount[whoseTurn(g)], pre->discardCount[whoseTurn(g)]+1);
			failed = 1;
	}
	//Check current player's discard contains same cards plus new card in last position
	for (i = 0; i < g->discardCount[whoseTurn(g)]-1; i++){
		if (pre->discard[whoseTurn(g)][i] != g->discard[whoseTurn(g)][i]){
			printf("\nCurrent player's discard[%d]: %d, Expected: %d", i, g->discard[whoseTurn(g)][i], pre->discard[whoseTurn(g)][i]);
			failed = 1;
		}
	}
	if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1] != TEST_CARD){
		printf("\nGained card: %d, Expected: %d\n", g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)]-1], TEST_CARD);
		failed = 1;		
	}
	
	//Final check
	if (failed){
		printf("\nResult: FAIL\n\n");
	} else {
		printf("none");
		printf("\nResult: PASS\n\n");
	}
	
//---Test toFlag = 1
/*---Expected results: 
	- Game and turn settings are unchanged
	- Supply count for other cards are unchanged
	- Supply count for selected card is decreased by 1
	- Other player's cards (hand, deck, discard) are unchanged
	- Played cards are unchanged		
	- Current player's hand and discard are unchanged
	- Current player's deckCount is 1 more than before gainCard
	- Current player's deck is the same except additional card in last position
*/
	printf("*** Testing toFlag = 1 ***\n");
	printf("Errors: ");
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.");
		return -1;
	} 
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Run gainCard and check results
	failed = 0;
	result = gainCard(TEST_CARD, g, 1, whoseTurn(g));
	if (result == -1){
		printf("\nReturn value: %d, Expected: %d", result, 0);
		failed = 1;
	}
	//Check game/turn settings
	if (checkNumPlayers(pre, g) < 0){
		printf("\nNumPlayers: %d, Expected: %d", g->numPlayers, pre->numPlayers);
		failed = 1;
	}
	result = checkEmbargo(pre, g);
	if (result != 0){
		printf("\nEmbargo for card %d: %d, Expected: %d", result, g->embargoTokens[result], pre->embargoTokens[result]);
		failed = 1;
	}
	if (checkOutpost(pre, g) < 0){
		printf("\noutpostPlayed: %d, Expected: %d", g->outpostPlayed, pre->outpostPlayed);
		printf("\noutpostTurn: %d, Expected: %d", g->outpostTurn, pre->outpostTurn);
		failed = 1;
	}	
	if (checkTurn(pre, g) < 0){
		printf("\nwhoseTurn: %d, Expected: %d", g->whoseTurn, pre->whoseTurn);
		failed = 1;
	}
	if (checkPhase(pre, g) < 0){
		printf("\nphase: %d, Expected: %d", g->phase, pre->phase);
		failed = 1;
	}	
	if (checkNumActions(pre, g) < 0){
		printf("\nnumActions: %d, Expected: %d", g->numActions, pre->numActions);
		failed = 1;
	}	
	if (checkCoins(pre, g) < 0){
		printf("\ncoins: %d, Expected: %d", g->coins, pre->coins);
		failed = 1;
	}
	if (checkNumBuys(pre, g) < 0){
		printf("\nnumBuys: %d, Expected: %d", g->numBuys, pre->numBuys);
		failed = 1;
	}
	//Check supply for gained card is decreased by 1
	if (g->supplyCount[TEST_CARD] != pre->supplyCount[TEST_CARD]-1){
		printf("\nSupply count for card %d: %d, Expected: %d", TEST_CARD, g->supplyCount[TEST_CARD], pre->supplyCount[TEST_CARD]-1);
		failed = 1;
	}
	//Check supply for other cards remains the same
	for (i = 0; i <= treasure_map; i++){
		//if test card, skip
		if (i == TEST_CARD){
			continue;
		}
		if (pre->supplyCount[i] != g->supplyCount[i]){
			printf("\nSupply count for card %d: %d, Expected: %d", i, g->supplyCount[i], pre->supplyCount[i]);
			failed = 1;
		}
	}
	//Check all hand, discard and played cards unchanged
	if (checkHands(pre, g) < 0){
		printf("\nHands changed after gainCard\n");
		//Print expected and actual hand for each player
		for (i = 0; i < NUM_PLAYERS; i++){
			printf("    Hand for player %d:\n", i);
			printf("      Count: %d, Expected: %d\n", g->handCount[i], pre->handCount[i]);
			if (g->handCount[i] > 0){
				printf("      Actual Cards: ");
				for (j = 0; j < g->handCount[i]; j++){
					printf("%d ", g->hand[i][j]);
				}
				printf("\n      Expected Cards: ");
				for (j = 0; j < pre->handCount[i]; j++){
					printf("%d ", pre->hand[i][j]);
				}
			}
		}
		failed = 1;
	}
	if (checkDiscards(pre, g) < 0){
		printf("\nDiscards changed after gainCard\n");
		//Print expected and actual discards for each player
		for (i = 0; i < NUM_PLAYERS; i++){
			printf("    Discard for player %d:\n", i);
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
	if (checkPlayed(pre, g) < 0){
		printf("\nPlayed cards changed after gainCard\n");
		//Print expected and actual played cards
		printf("    Played count: %d, Expected: %d\n", g->playedCardCount, pre->playedCardCount);
		if (g->playedCardCount > 0){
			printf("    Actual Cards: ");
			for (i = 0; i < g->playedCardCount; i++){
				printf("%d ", g->playedCards[i]);
			}
			printf("\n    Expected Cards: ");
			for (i = 0; i < pre->playedCardCount; i++){
				printf("%d ", pre->playedCards[i]);
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
	//Check current player's deckCount increased by 1
	if (g->deckCount[whoseTurn(g)] != pre->deckCount[whoseTurn(g)]+1){
			printf("\nCurrent player's deckCount: %d, Expected: %d", g->deckCount[whoseTurn(g)], pre->deckCount[whoseTurn(g)]+1);
			failed = 1;
	}
	//Check current player's deck contains same cards plus new card in last position
	for (i = 0; i < g->deckCount[whoseTurn(g)]-1; i++){
		if (pre->deck[whoseTurn(g)][i] != g->deck[whoseTurn(g)][i]){
			printf("\nCurrent player's deck[%d]: %d, Expected: %d", i, g->deck[whoseTurn(g)][i], pre->deck[whoseTurn(g)][i]);
			failed = 1;
		}
	}
	if (g->deck[whoseTurn(g)][g->deckCount[whoseTurn(g)]-1] != TEST_CARD){
		printf("\nGained card: %d, Expected: %d", g->deck[whoseTurn(g)][g->deckCount[whoseTurn(g)]-1], TEST_CARD);
		failed = 1;		
	}
	
	//Final check
	if (failed){
		printf("\nResult: FAIL\n\n");
	} else {
		printf("none");
		printf("\nResult: PASS\n\n");
	}

	
//---Test toFlag = 2
/*---Expected results: 
	- Game and turn settings are unchanged
	- Supply count for other cards are unchanged
	- Supply count for selected card is decreased by 1
	- Other player's cards (hand, deck, discard) are unchanged
	- Played cards are unchanged		
	- Current player's deck and discard are unchanged
	- Current player's handCount is 1 more than before gainCard
	- Current player's hand is the same except additional card in last position
*/
	printf("*** Testing toFlag = 2 ***\n");
	printf("Errors: ");
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.");
		return -1;
	} 
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Run gainCard and check results
	failed = 0;
	result = gainCard(TEST_CARD, g, 2, whoseTurn(g));
	if (result == -1){
		printf("\nReturn value: %d, Expected: %d", result, 0);
		failed = 1;
	}
	//Check game/turn settings
	if (checkNumPlayers(pre, g) < 0){
		printf("\nNumPlayers: %d, Expected: %d", g->numPlayers, pre->numPlayers);
		failed = 1;
	}
	result = checkEmbargo(pre, g);
	if (result != 0){
		printf("\nEmbargo for card %d: %d, Expected: %d", result, g->embargoTokens[result], pre->embargoTokens[result]);
		failed = 1;
	}
	if (checkOutpost(pre, g) < 0){
		printf("\noutpostPlayed: %d, Expected: %d", g->outpostPlayed, pre->outpostPlayed);
		printf("\noutpostTurn: %d, Expected: %d", g->outpostTurn, pre->outpostTurn);
		failed = 1;
	}	
	if (checkTurn(pre, g) < 0){
		printf("\nwhoseTurn: %d, Expected: %d", g->whoseTurn, pre->whoseTurn);
		failed = 1;
	}
	if (checkPhase(pre, g) < 0){
		printf("\nphase: %d, Expected: %d", g->phase, pre->phase);
		failed = 1;
	}	
	if (checkNumActions(pre, g) < 0){
		printf("\nnumActions: %d, Expected: %d", g->numActions, pre->numActions);
		failed = 1;
	}	
	if (checkCoins(pre, g) < 0){
		printf("\ncoins: %d, Expected: %d", g->coins, pre->coins);
		failed = 1;
	}
	if (checkNumBuys(pre, g) < 0){
		printf("\nnumBuys: %d, Expected: %d", g->numBuys, pre->numBuys);
		failed = 1;
	}
	//Check supply for gained card is decreased by 1
	if (g->supplyCount[TEST_CARD] != pre->supplyCount[TEST_CARD]-1){
		printf("\nSupply count for card %d: %d, Expected: %d", TEST_CARD, g->supplyCount[TEST_CARD], pre->supplyCount[TEST_CARD]-1);
		failed = 1;
	}
	//Check supply for other cards remains the same
	for (i = 0; i <= treasure_map; i++){
		//if test card, skip
		if (i == TEST_CARD){
			continue;
		}
		if (pre->supplyCount[i] != g->supplyCount[i]){
			printf("\nSupply count for card %d: %d, Expected: %d", i, g->supplyCount[i], pre->supplyCount[i]);
			failed = 1;
		}
	}
	//Check all deck, discard and played cards unchanged
	if (checkDecks(pre, g) < 0){
		printf("\nDecks changed after gainCard\n");
		//Print expected and actual deck for each player
		for (i = 0; i < NUM_PLAYERS; i++){
			printf("    Deck for player %d:\n", i);
			printf("      Count: %d, Expected: %d\n", g->deckCount[i], pre->deckCount[i]);
			if (g->deckCount[i] > 0){
				printf("      Actual Cards: ");
				for (j = 0; j < g->deckCount[i]; j++){
					printf("%d ", g->deck[i][j]);
				}
				printf("\n      Expected Cards: ");
				for (j = 0; j < pre->deckCount[i]; j++){
					printf("%d ", pre->deck[i][j]);
				}
			}
		}
		failed = 1;
	}
	if (checkDiscards(pre, g) < 0){
		printf("\nDiscards changed after gainCard\n");
		//Print expected and actual discards for each player
		for (i = 0; i < NUM_PLAYERS; i++){
			printf("    Discard for player %d:\n", i);
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
	if (checkPlayed(pre, g) < 0){
		printf("\nPlayed cards changed after gainCard\n");
		//Print expected and actual played cards
		printf("    Played count: %d, Expected: %d\n", g->playedCardCount, pre->playedCardCount);
		if (g->playedCardCount > 0){
			printf("    Actual Cards: ");
			for (i = 0; i < g->playedCardCount; i++){
				printf("%d ", g->playedCards[i]);
			}
			printf("\n    Expected Cards: ");
			for (i = 0; i < pre->playedCardCount; i++){
				printf("%d ", pre->playedCards[i]);
			}
		}
		failed = 1;
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
	//Check current player's handCount increased by 1
	if (g->handCount[whoseTurn(g)] != pre->handCount[whoseTurn(g)]+1){
			printf("\nCurrent player's handCount: %d, Expected: %d", g->handCount[whoseTurn(g)], pre->handCount[whoseTurn(g)]+1);
			failed = 1;
	}
	//Check current player's hand contains same cards plus new card in last position
	for (i = 0; i < g->handCount[whoseTurn(g)]-1; i++){
		if (pre->hand[whoseTurn(g)][i] != g->hand[whoseTurn(g)][i]){
			printf("\nCurrent player's hand[%d]: %d, Expected: %d", i, g->hand[whoseTurn(g)][i], pre->hand[whoseTurn(g)][i]);
			failed = 1;
		}
	}
	if (g->hand[whoseTurn(g)][g->handCount[whoseTurn(g)]-1] != TEST_CARD){
		printf("\nGained card: %d, Expected: %d", g->hand[whoseTurn(g)][g->handCount[whoseTurn(g)]-1], TEST_CARD);
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
