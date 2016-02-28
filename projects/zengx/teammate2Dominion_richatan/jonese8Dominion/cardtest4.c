/*Tanna Richardson
  CS362 - Winter 2016
  Assignment 3
  Card test for: baron
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
#define TEST_CARD baron
#define TEST_POS 0
#define EXTRA_CARD copper
 
int main () {
	int i, j;			//loop controls
	int result;			//return value for function calls
	int failed;			//flags for tests
	
	struct gameState *g = malloc(sizeof(struct gameState));		//working game state
	struct gameState *pre = malloc(sizeof(struct gameState));	//reference game state; stored before functions run
	int selectedCards[10] = {adventurer, council_room, feast, gardens, mine, smithy, village, tribute, salvager, sea_hag};	
	int seed = 10;
	
	int choice1, choice2, choice3;	//choices for card effect
	int coin_bonus;					//coins added by card
	
	
//---Test baron with discard = true (choice1=1) and estate card in hand
/*---Expected result: 
	- Game and turn settings are unchanged
	- All player's decks are unchanged
	- Other player's hands and discards are unchanged
	- Played card count increased by 1
	- Baron card added to played pile (in last position)
	- Baron card removed from hand
	- Supply is unchanged
	- Current player's hand count is decreased by 2 (-1 estate, -1 baron)
	- All other cards in player's hand remain (all EXTRA_CARD)
	- Current player's discard count is increased by 1
	- Last card in current player's discard = estate
	- numBuys increased by 1
	- coins increased by 4 (coins added to gamestate, not bonus)
*/
	printf("*** Testing choice1 = 1, estate in hand ***\n");
	printf("Errors: ");
	//Setup card options
	choice1 = 1;
	choice2 = -1;
	choice3 = -1;
	coin_bonus = 0;
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.\n");
		return -1;
	}
	//Set hand to include test card + 1 estate + 4 extras
	g->deckCount[whoseTurn(g)] = 6;
	g->deck[whoseTurn(g)][1] = estate;
	for (i = 2; i < 6; i++){
		g->deck[whoseTurn(g)][i] = EXTRA_CARD;
	}	
	//Set test position in hand to test card
	g->hand[whoseTurn(g)][TEST_POS] = TEST_CARD;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to execute card
	result = cardEffect(TEST_CARD, choice1, choice2, choice3, g, TEST_POS, &coin_bonus);
	failed = 0;
	if (result != 0){
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
	//Check all player's deck unchanged
	if (checkDecks(pre, g) < 0){
		printf("\nDecks changed after baron\n");
		//Print expected and actual decks for each player
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
	//Check discard and hand unchanged for other players
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
	//Check baron added to played pile
	if (g->playedCardCount != pre->playedCardCount + 1){
		printf("\nPlayed card count: %d, Expected: %d", g->playedCardCount, pre->playedCardCount + 1);
		failed = 1;
	} else if (g->playedCards[g->playedCardCount - 1] != TEST_CARD){
		printf("\nLast played card: %d, Expected: %d", g->playedCards[g->playedCardCount - 1], TEST_CARD);
		failed = 1;		
	}
	//Check supply count is unchanged
	result = checkSupply(pre, g);
	if (result != 0){
		printf("\nSupply count for card %d: %d, Expected: %d", result, g->supplyCount[result], pre->supplyCount[result]);
		failed = 1;
	}
	//Check estate and baron cards removed from player's hand; other cards unchanged (all EXTRA_CARD)
	if (g->handCount[whoseTurn(g)] != pre->handCount[whoseTurn(g)] - 2){
		printf("\nCurrent player's hand count: %d, Expected: %d", g->handCount[whoseTurn(g)], pre->handCount[whoseTurn(g)] - 2);
		failed = 1;
	}
	for (i = 0; i < g->handCount[whoseTurn(g)]; i++){
		if (g->hand[whoseTurn(g)][i] != EXTRA_CARD){
			printf("\nCurrent player's hand[%d]: %d, Expected: %d", i, g->hand[whoseTurn(g)][i], EXTRA_CARD);
			failed = 1;
		}
	}
	//Check estate card added to discard in last position
	if (g->discardCount[whoseTurn(g)] != pre->discardCount[whoseTurn(g)] + 1){
		printf("\nCurrent player's discard count: %d, Expected: %d", g->discardCount[whoseTurn(g)], pre->discardCount[whoseTurn(g)] + 1);
		failed = 1;
	}
	if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)] - 1] != estate){
		printf("\nCard added to current player's discard: %d, Expected: %d", g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)] - 1], estate);
		failed = 1;
	}
	//Check numBuys increased by 1
	if (g->numBuys != pre->numBuys + 1){
		printf("\nnumBuys: %d, Expected: %d", g->numBuys, pre->numBuys + 1);
		failed = 1;
	}
	//Check gamestate coins increased by 4
	if (g->coins != pre->coins + 4){
		printf("\nCoins after baron: %d, Expected: %d", g->coins, pre->coins + 4);
		failed = 1;		
	}
	//Check 0 bonus coins added
	if (coin_bonus != 0){
		printf("\nCoin bonus after baron: %d, Expected: %d", coin_bonus, 0);
		failed = 1;		
	}	
	//Final check
	if (failed){
		printf("\nResult: FAIL\n\n");
	} else {
		printf("none");
		printf("\nResult: PASS\n\n");
	}

	
//---Test baron with discard = true (choice1=1) but no estate in hand
/*---Expected result: 
	- Game and turn settings are unchanged
	- All player's decks are unchanged
	- Other player's discards and hands are unchanged
	- Played card count increased by 1
	- Baron card added to played pile (in last position)
	- Baron card removed from hand
	- SupplyCount for estate is decreased by 1
	- Current player's discard count is increased by 1
	- Last card in current player's discard = estate
	- Current player's hand count is decreased by 1 (-1 baron)
	- Other cards in current player's hand unchanged
	- numBuys increased by 1
	- coins is unchanged
*/
	printf("*** Testing choice1 = 1, NO estate in hand ***\n");
	printf("Errors: ");
	//Setup card options
	choice1 = 1;
	choice2 = -1;
	choice3 = -1;
	coin_bonus = 0;
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.\n");
		return -1;
	}
	//Set hand to include 5 extras
	g->handCount[whoseTurn(g)] = 5;
	for (i = 1; i < 5; i++){
		g->hand[whoseTurn(g)][i] = EXTRA_CARD;
	}	
	//Set test position in hand to test card
	g->hand[whoseTurn(g)][TEST_POS] = TEST_CARD;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to execute card
	result = cardEffect(TEST_CARD, choice1, choice2, choice3, g, TEST_POS, &coin_bonus);
	failed = 0;
	if (result != 0){
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
	//Check all player's deck unchanged
	if (checkDecks(pre, g) < 0){
		printf("\nDecks changed after baron\n");
		//Print expected and actual decks for each player
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
	//Check discard and hand unchanged for other players
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
	//Check baron added to played pile
	if (g->playedCardCount != pre->playedCardCount + 1){
		printf("\nPlayed card count: %d, Expected: %d", g->playedCardCount, pre->playedCardCount + 1);
		failed = 1;
	} else if (g->playedCards[g->playedCardCount - 1] != TEST_CARD){
		printf("\nLast played card: %d, Expected: %d", g->playedCards[g->playedCardCount - 1], TEST_CARD);
		failed = 1;		
	}
	//Check supply count for estate decreased by 1; others unchanged
	for (i = 0; i <= treasure_map; i++){
		if (i == estate){
			if (g->supplyCount[i] != pre->supplyCount[i] - 1){
				printf("\nSupply count for estate card: %d, Expected: %d", g->supplyCount[i], pre->supplyCount[i] - 1);
				failed = 1;
			}
		} else {
			if (g->supplyCount[i] != pre->supplyCount[i]){
				printf("\nSupply count for card %d: %d, Expected: %d", i, g->supplyCount[i], pre->supplyCount[i]);
				failed = 1;
			}
		}	
	}
	//Check estate card added to discard in last position
	if (g->discardCount[whoseTurn(g)] != pre->discardCount[whoseTurn(g)] + 1){
		printf("\nCurrent player's discard count: %d, Expected: %d", g->discardCount[whoseTurn(g)], pre->discardCount[whoseTurn(g)] + 1);
		failed = 1;
	}
	if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)] - 1] != estate){
		printf("\nCard added to current player's discard: %d, Expected: %d", g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)] - 1], estate);
		failed = 1;
	}
	//Check baron card removed from player's hand; other cards unchanged (all EXTRA_CARD)
	if (g->handCount[whoseTurn(g)] != pre->handCount[whoseTurn(g)] - 1){
		printf("\nCurrent player's hand count: %d, Expected: %d", g->handCount[whoseTurn(g)], pre->handCount[whoseTurn(g)] - 1);
		failed = 1;
	}
	for (i = 0; i < g->handCount[whoseTurn(g)]; i++){
		if (g->hand[whoseTurn(g)][i] != EXTRA_CARD){
			printf("\nCurrent player's hand[%d]: %d, Expected: %d", i, g->hand[whoseTurn(g)][i], EXTRA_CARD);
			failed = 1;
		}
	}
	//Check numBuys increased by 1
	if (g->numBuys != pre->numBuys + 1){
		printf("\nnumBuys: %d, Expected: %d", g->numBuys, pre->numBuys + 1);
		failed = 1;
	}
	//Check gamestate coins unchanged
	if (g->coins != pre->coins){
		printf("\nCoins after baron: %d, Expected: %d", g->coins, pre->coins);
		failed = 1;		
	}
	//Check 0 bonus coins added
	if (coin_bonus != 0){
		printf("\nCoin bonus after baron: %d, Expected: %d", coin_bonus, 0);
		failed = 1;		
	}	
	//Final check
	if (failed){
		printf("\nResult: FAIL\n\n");
	} else {
		printf("none");
		printf("\nResult: PASS\n\n");
	}


//---Test baron with discard = false
/*---Expected result: 
	- Game and turn settings are unchanged
	- All player's decks are unchanged
	- Other player's discards and hands are unchanged
	- Played card count increased by 1
	- Baron card added to played pile (in last position)
	- Baron card removed from hand
	- SupplyCount for estate is decreased by 1
	- Current player's discard count is increased by 1
	- Last card in current player's discard = estate
	- Current player's hand count is decreased by 1 (-1 baron)
	- Other cards in current player's hand unchanged
	- numBuys increased by 1
	- coins is unchanged
*/
	printf("*** Testing choice1 = 0 ***\n");
	printf("Errors: ");
	//Setup card options
	choice1 = 0;
	choice2 = -1;
	choice3 = -1;
	coin_bonus = 0;
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("\nCould not initialize game. Testing aborted.\n");
		return -1;
	}
	//Set hand to include 5 extras
	g->handCount[whoseTurn(g)] = 5;
	for (i = 1; i < 5; i++){
		g->hand[whoseTurn(g)][i] = EXTRA_CARD;
	}	
	//Set test position in hand to test card
	g->hand[whoseTurn(g)][TEST_POS] = TEST_CARD;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to execute card
	result = cardEffect(TEST_CARD, choice1, choice2, choice3, g, TEST_POS, &coin_bonus);
	failed = 0;
	if (result != 0){
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
	//Check all player's deck unchanged
	if (checkDecks(pre, g) < 0){
		printf("\nDecks changed after baron\n");
		//Print expected and actual decks for each player
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
				printf("\n");
			}
		}
		failed = 1;
	}
	//Check discard and hand unchanged for other players
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
	//Check baron added to played pile
	if (g->playedCardCount != pre->playedCardCount + 1){
		printf("\nPlayed card count: %d, Expected: %d", g->playedCardCount, pre->playedCardCount + 1);
		failed = 1;
	} else if (g->playedCards[g->playedCardCount - 1] != TEST_CARD){
		printf("\nLast played card: %d, Expected: %d", g->playedCards[g->playedCardCount - 1], TEST_CARD);
		failed = 1;		
	}
	//Check supply count for estate decreased by 1; others unchanged
	for (i = 0; i <= treasure_map; i++){
		if (i == estate){
			if (g->supplyCount[i] != pre->supplyCount[i] - 1){
				printf("\nSupply count for estate card: %d, Expected: %d", g->supplyCount[i], pre->supplyCount[i] - 1);
				failed = 1;
			}
		} else {
			if (g->supplyCount[i] != pre->supplyCount[i]){
				printf("\nSupply count for card %d: %d, Expected: %d", i, g->supplyCount[i], pre->supplyCount[i]);
				failed = 1;
			}
		}	
	}
	//Check estate card added to discard in last position
	if (g->discardCount[whoseTurn(g)] != pre->discardCount[whoseTurn(g)] + 1){
		printf("\nCurrent player's discard count: %d, Expected: %d", g->discardCount[whoseTurn(g)], pre->discardCount[whoseTurn(g)] + 1);
		failed = 1;
	}
	if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)] - 1] != estate){
		printf("\nCard added to current player's discard: %d, Expected: %d", g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)] - 1], estate);
		failed = 1;
	}
	//Check baron card removed from player's hand; other cards unchanged (all EXTRA_CARD)
	if (g->handCount[whoseTurn(g)] != pre->handCount[whoseTurn(g)] - 1){
		printf("\nCurrent player's hand count: %d, Expected: %d", g->handCount[whoseTurn(g)], pre->handCount[whoseTurn(g)] - 1);
		failed = 1;
	}
	for (i = 0; i < g->handCount[whoseTurn(g)]; i++){
		if (g->hand[whoseTurn(g)][i] != EXTRA_CARD){
			printf("\nCurrent player's hand[%d]: %d, Expected: %d", i, g->hand[whoseTurn(g)][i], EXTRA_CARD);
			failed = 1;
		}
	}
	//Check numBuys increased by 1
	if (g->numBuys != pre->numBuys + 1){
		printf("\nnumBuys: %d, Expected: %d", g->numBuys, pre->numBuys + 1);
		failed = 1;
	}
	//Check gamestate coins unchanged
	if (g->coins != pre->coins){
		printf("\nCoins after baron: %d, Expected: %d", g->coins, pre->coins);
		failed = 1;		
	}
	//Check 0 bonus coins added
	if (coin_bonus != 0){
		printf("\nCoin bonus after baron: %d, Expected: %d", coin_bonus, 0);
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
