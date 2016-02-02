/*Tanna Richardson
  CS362 - Winter 2016
  Assignment 3
  Card test for: adventurer
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
#define TEST_CARD adventurer
#define TEST_POS 0
#define EXTRA_COUNT 5
#define EXTRA_CARD estate
#define TREASURE copper
 
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
	
	printf("---Testing Card: adventurer---\n");
	
//---Test adventurer with 2 treasure cards in deck
//---(all choices = -1, no bonus)
/*---Expected result: 
	- Game and turn settings are unchanged
	- Other player's cards (hand, deck, discard) are unchanged
	- Played card count increased by 1
	- Adventurer card added to played pile (in last position)
	- Current player's deck count decreased by 2 treasures + extras
	- Other cards in player's deck unchanged
	- Current player's discard count increased by extras
	- Current player's hand count increased by 2
	- Cards added to player's hand are treasure
	- Cards added to player's discard are extras
	- No bonus coins
*/
	//Setup card options
	choice1 = -1;
	choice2 = -1;
	choice3 = -1;
	coin_bonus = 0;
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
		return -1;
	}
	//Set deck to 5 extras - 2 treasures - 5 extras
	g->deckCount[whoseTurn(g)] = 0;
	for (i = 1; i <= EXTRA_COUNT; i++){
		g->deck[whoseTurn(g)][g->deckCount[whoseTurn(g)]] = EXTRA_CARD;
		g->deckCount[whoseTurn(g)]++;
	}
	for (i = 1; i <= 2; i++){
		g->deck[whoseTurn(g)][g->deckCount[whoseTurn(g)]] = TREASURE;
		g->deckCount[whoseTurn(g)]++;
	}
	for (i = 1; i <= EXTRA_COUNT; i++){
		g->deck[whoseTurn(g)][g->deckCount[whoseTurn(g)]] = EXTRA_CARD;
		g->deckCount[whoseTurn(g)]++;
	}
	//Set test position in hand to test card
	g->hand[whoseTurn(g)][TEST_POS] = TEST_CARD;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to execute card
	result = cardEffect(TEST_CARD, choice1, choice2, choice3, g, TEST_POS, &coin_bonus);
	failed = 0;
	if (result != 0){
		printf("FAIL when 2 treasures in deck\n");
		printf("  Return value: %d, Expected: %d\n", result, 0);
		failed = 1;
	}
	//Check game/turn settings
	if (checkNumPlayers(pre, g) < 0){
		printf("FAIL when 2 treasures in deck\n");
		printf("  NumPlayers: %d, Expected: %d\n", g->numPlayers, pre->numPlayers);
		failed = 1;
	}
	result = checkSupply(pre, g);
	if (result != 0){
		printf("FAIL when 2 treasures in deck\n");
		printf("  Supply count for card %d: %d, Expected: %d\n", result, g->supplyCount[result], pre->supplyCount[result]);
		failed = 1;
	}
	result = checkEmbargo(pre, g);
	if (result != 0){
		printf("FAIL when 2 treasures in deck\n");
		printf("  Embargo for card %d: %d, Expected: %d\n", result, g->embargoTokens[result], pre->embargoTokens[result]);
		failed = 1;
	}
	if (checkOutpost(pre, g) < 0){
		printf("FAIL when 2 treasures in deck\n");
		printf("  outpostPlayed: %d, Expected: %d\n", g->outpostPlayed, pre->outpostPlayed);
		printf("  outpostTurn: %d, Expected: %d\n", g->outpostTurn, pre->outpostTurn);
		failed = 1;
	}	
	if (checkTurn(pre, g) < 0){
		printf("FAIL when 2 treasures in deck\n");
		printf("  whoseTurn: %d, Expected: %d\n", g->whoseTurn, pre->whoseTurn);
		failed = 1;
	}
	if (checkPhase(pre, g) < 0){
		printf("FAIL when 2 treasures in deck\n");
		printf("  phase: %d, Expected: %d\n", g->phase, pre->phase);
		failed = 1;
	}	
	if (checkNumActions(pre, g) < 0){
		printf("FAIL when 2 treasures in deck\n");
		printf("  numActions: %d, Expected: %d\n", g->numActions, pre->numActions);
		failed = 1;
	}	
	if (checkCoins(pre, g) < 0){
		printf("FAIL when 2 treasures in deck\n");
		printf("  coins: %d, Expected: %d\n", g->coins, pre->coins);
		failed = 1;
	}
	if (checkNumBuys(pre, g) < 0){
		printf("FAIL when 2 treasures in deck\n");
		printf("  numBuys: %d, Expected: %d\n", g->numBuys, pre->numBuys);
		failed = 1;
	}
	//Check discard unchanged for other players
	for (i = 0; i < g->numPlayers; i++){
		//skip if current player
		if (i == whoseTurn(g)){
			continue;
		}
		if (pre->discardCount[i] != g->discardCount[i]){
			printf("FAIL when 2 treasures in deck\n");
			printf("  Player %d's discardCount: %d, Expected: %d\n", i, g->discardCount[i], pre->discardCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->discardCount[i]; j++){
				if (pre->discard[i][j] != g->discard[i][j]){
					printf("FAIL when 2 treasures in deck\n");
					printf("  Player %d's discard[%d]: %d, Expected: %d\n", i, j, g->discard[i][j], pre->discard[i][j]);
					failed = 1;
				}
			}
		}
	}
	//Check deck unchanged for other players
	for (i = 0; i < g->numPlayers; i++){
		//skip if current player
		if (i == whoseTurn(g)){
			continue;
		}
		if (pre->deckCount[i] != g->deckCount[i]){
			printf("FAIL when 2 treasures in deck\n");
			printf("  Player %d's deckCount: %d, Expected: %d\n", i, g->deckCount[i], pre->deckCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->deckCount[i]; j++){
				if (pre->deck[i][j] != g->deck[i][j]){
					printf("FAIL when 2 treasures in deck\n");
					printf("  Player %d's deck[%d]: %d, Expected: %d\n", i, j, g->deck[i][j], pre->deck[i][j]);
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
			printf("FAIL when 2 treasures in deck\n");
			printf("  Player %d's handCount: %d, Expected: %d\n", i, g->handCount[i], pre->handCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->handCount[i]; j++){
				if (pre->hand[i][j] != g->hand[i][j]){
					printf("FAIL when 2 treasures in deck\n");
					printf("  Player %d's hand[%d]: %d, Expected: %d\n", i, j, g->hand[i][j], pre->hand[i][j]);
					failed = 1;
				}
			}
		}
	}
	//Check adventurer added to played pile
	if (g->playedCardCount != pre->playedCardCount + 1){
		printf("FAIL when 2 treasures in deck\n");
		printf("  Played card count: %d, Expected: %d\n", g->playedCardCount, pre->playedCardCount + 1);
		failed = 1;
	} else if (g->playedCards[g->playedCardCount - 1] != TEST_CARD){
		printf("FAIL when 2 treasures in deck\n");
		printf("  Last played card: %d, Expected: %d\n", g->playedCards[g->playedCardCount - 1], TEST_CARD);
		failed = 1;		
	}
	//Check 2 treasures + extras removed from deck; other cards remain
	if (g->deckCount[whoseTurn(g)] != pre->deckCount[whoseTurn(g)] - EXTRA_COUNT - 2){
		printf("FAIL when 2 treasures in deck\n");
		printf("  Current player's deck count: %d, Expected: %d\n", g->deckCount[whoseTurn(g)], pre->deckCount[whoseTurn(g)] - EXTRA_COUNT - 2);
		failed = 1;		
	}
	for (i = 0; i < g->deckCount[whoseTurn(g)]; i++){
		if (g->deck[whoseTurn(g)][i] != EXTRA_CARD){
			printf("FAIL when 2 treasures in deck\n");
			printf("  Current player's deck[%d]: %d, Expected: %d\n", i, g->deck[whoseTurn(g)][i], EXTRA_CARD);
			failed = 1;		
		}	
	}
	//Check 2 treasure cards added to hand
	if (g->handCount[whoseTurn(g)] != pre->handCount[whoseTurn(g)] + 2){
		printf("FAIL when 2 treasures in deck\n");
		printf("  Current player's hand count: %d, Expected: %d\n", g->handCount[whoseTurn(g)], pre->handCount[whoseTurn(g)] + 2);
		failed = 1;		
	}
	if ( (g->hand[whoseTurn(g)][g->handCount[whoseTurn(g)] - 1] != TREASURE) && (g->hand[whoseTurn(g)][g->handCount[whoseTurn(g)] - 2] != TREASURE) ){
		printf("FAIL when 2 treasures in deck\n");
		printf("  Current player's hand[%d]: %d, Expected: %d\n", g->handCount[whoseTurn(g)] - 1, g->hand[whoseTurn(g)][g->handCount[whoseTurn(g)] - 1], TREASURE);
		printf("  Current player's hand[%d]: %d, Expected: %d\n", g->handCount[whoseTurn(g)] - 2, g->hand[whoseTurn(g)][g->handCount[whoseTurn(g)] - 2], TREASURE);
		failed = 1;		
	}
	//Check extra cards added to discard
	if (g->discardCount[whoseTurn(g)] != pre->discardCount[whoseTurn(g)] + EXTRA_COUNT){
		printf("FAIL when 2 treasures in deck\n");
		printf("  Current player's discard count: %d, Expected: %d\n", g->discardCount[whoseTurn(g)], pre->discardCount[whoseTurn(g)] + EXTRA_COUNT);
		failed = 1;		
	}
	for (i = 1; i <= EXTRA_COUNT; i++){
		if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)] - i] != EXTRA_CARD){
			printf("FAIL when 2 treasures in deck\n");
			printf("  Current player's discard[%d]: %d, Expected: %d\n", g->discardCount[whoseTurn(g)] - i, g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)] - i], EXTRA_CARD);
			failed = 1;		
		}
	}
	//Check no bonus coins added
	if (coin_bonus != 0){
		printf("FAIL when 2 treasures in deck\n");
		printf("  Coin bonus after adventurer: %d, Expected: %d\n", coin_bonus, 0);
		failed = 1;		
	}	
	//Final check
	if (!failed){
		printf("PASS when 2 treasures in deck\n");
	}

//---Test adventurer with 1 treasure card in deck, 1 in discard
//---(all choices = -1, no bonus)
/*---Expected result: 
	- Game and turn settings are unchanged
	- Other player's cards (hand, deck, discard) are unchanged
	- Played card count increased by 1
	- Adventurer card added to played pile (in last position)
	- Current player's deck count decreased by 1 treasure + extras
	- Current player's discard count increased by extras, decreased by 1 treasure
	- Current player's hand count increased by 2
	- Cards added to player's hand are treasure
	- Cards added to player's discard are extras
	- No bonus coins

-------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------
NOTICE: Test disabled because of bug in current code causing infinite loop.
When deck is empty, adventurer code does not add discard pile to deck before shuffle.
-------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------
*/
	printf("FAIL when 1 treasure in deck, 1 in discard\n");
	printf("  Test disabled because of infinite loop\n");
	/*
	//Setup card options
	choice1 = -1;
	choice2 = -1;
	choice3 = -1;
	coin_bonus = 0;
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
		return -1;
	}
	//Set deck to 1 treasure - 5 extras
	g->deckCount[whoseTurn(g)] = 0;
	g->deck[whoseTurn(g)][g->deckCount[whoseTurn(g)]] = TREASURE;
	g->deckCount[whoseTurn(g)]++;
	for (i = 1; i <= EXTRA_COUNT; i++){
		g->deck[whoseTurn(g)][g->deckCount[whoseTurn(g)]] = EXTRA_CARD;
		g->deckCount[whoseTurn(g)]++;
	}
	//Set discard to 1 treasure
	g->discardCount[whoseTurn(g)] = 0;
	g->discard[whoseTurn(g)][g->deckCount[whoseTurn(g)]] = TREASURE;
	g->discardCount[whoseTurn(g)]++;
	//Set test position in hand to test card
	g->hand[whoseTurn(g)][TEST_POS] = TEST_CARD;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to execute card
	result = cardEffect(TEST_CARD, choice1, choice2, choice3, g, TEST_POS, &coin_bonus);
	failed = 0;
	if (result != 0){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  Return value: %d, Expected: %d\n", result, 0);
		failed = 1;
	}
	//Check game/turn settings
	if (checkNumPlayers(pre, g) < 0){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  NumPlayers: %d, Expected: %d\n", g->numPlayers, pre->numPlayers);
		failed = 1;
	}
	result = checkSupply(pre, g);
	if (result != 0){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  Supply count for card %d: %d, Expected: %d\n", result, g->supplyCount[result], pre->supplyCount[result]);
		failed = 1;
	}
	result = checkEmbargo(pre, g);
	if (result != 0){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  Embargo for card %d: %d, Expected: %d\n", result, g->embargoTokens[result], pre->embargoTokens[result]);
		failed = 1;
	}
	if (checkOutpost(pre, g) < 0){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  outpostPlayed: %d, Expected: %d\n", g->outpostPlayed, pre->outpostPlayed);
		printf("  outpostTurn: %d, Expected: %d\n", g->outpostTurn, pre->outpostTurn);
		failed = 1;
	}	
	if (checkTurn(pre, g) < 0){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  whoseTurn: %d, Expected: %d\n", g->whoseTurn, pre->whoseTurn);
		failed = 1;
	}
	if (checkPhase(pre, g) < 0){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  phase: %d, Expected: %d\n", g->phase, pre->phase);
		failed = 1;
	}	
	if (checkNumActions(pre, g) < 0){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  numActions: %d, Expected: %d\n", g->numActions, pre->numActions);
		failed = 1;
	}	
	if (checkCoins(pre, g) < 0){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  coins: %d, Expected: %d\n", g->coins, pre->coins);
		failed = 1;
	}
	if (checkNumBuys(pre, g) < 0){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  numBuys: %d, Expected: %d\n", g->numBuys, pre->numBuys);
		failed = 1;
	}
	//Check discard unchanged for other players
	for (i = 0; i < g->numPlayers; i++){
		//skip if current player
		if (i == whoseTurn(g)){
			continue;
		}
		if (pre->discardCount[i] != g->discardCount[i]){
			printf("FAIL when 1 treasure in deck, 1 in discard\n");
			printf("  Player %d's discardCount: %d, Expected: %d\n", i, g->discardCount[i], pre->discardCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->discardCount[i]; j++){
				if (pre->discard[i][j] != g->discard[i][j]){
					printf("FAIL when 1 treasure in deck, 1 in discard\n");
					printf("  Player %d's discard[%d]: %d, Expected: %d\n", i, j, g->discard[i][j], pre->discard[i][j]);
					failed = 1;
				}
			}
		}
	}
	//Check deck unchanged for other players
	for (i = 0; i < g->numPlayers; i++){
		//skip if current player
		if (i == whoseTurn(g)){
			continue;
		}
		if (pre->deckCount[i] != g->deckCount[i]){
			printf("FAIL when 1 treasure in deck, 1 in discard\n");
			printf("  Player %d's deckCount: %d, Expected: %d\n", i, g->deckCount[i], pre->deckCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->deckCount[i]; j++){
				if (pre->deck[i][j] != g->deck[i][j]){
					printf("FAIL when 1 treasure in deck, 1 in discard\n");
					printf("  Player %d's deck[%d]: %d, Expected: %d\n", i, j, g->deck[i][j], pre->deck[i][j]);
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
			printf("FAIL when 1 treasure in deck, 1 in discard\n");
			printf("  Player %d's handCount: %d, Expected: %d\n", i, g->handCount[i], pre->handCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->handCount[i]; j++){
				if (pre->hand[i][j] != g->hand[i][j]){
					printf("FAIL when 1 treasure in deck, 1 in discard\n");
					printf("  Player %d's hand[%d]: %d, Expected: %d\n", i, j, g->hand[i][j], pre->hand[i][j]);
					failed = 1;
				}
			}
		}
	}
	//Check adventurer added to played pile
	if (g->playedCardCount != pre->playedCardCount + 1){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  Played card count: %d, Expected: %d\n", g->playedCardCount, pre->playedCardCount + 1);
		failed = 1;
	} else if (g->playedCards[g->playedCardCount - 1] != TEST_CARD){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  Last played card: %d, Expected: %d\n", g->playedCards[g->playedCardCount - 1], TEST_CARD);
		failed = 1;		
	}
	//Check 1 treasure + extras removed from deck
	if (g->deckCount[whoseTurn(g)] != pre->deckCount[whoseTurn(g)] - EXTRA_COUNT - 1){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  Current player's deck count: %d, Expected: %d\n", g->deckCount[whoseTurn(g)], pre->deckCount[whoseTurn(g)] - EXTRA_COUNT - 1);
		failed = 1;		
	}
	//Check 2 treasure cards added to hand
	if (g->handCount[whoseTurn(g)] != pre->handCount[whoseTurn(g)] + 2){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  Current player's hand count: %d, Expected: %d\n", g->handCount[whoseTurn(g)], pre->handCount[whoseTurn(g)] + 2);
		failed = 1;		
	}
	if ( (g->hand[whoseTurn(g)][g->handCount[whoseTurn(g)] - 1] != TREASURE) && (g->hand[whoseTurn(g)][g->handCount[whoseTurn(g)] - 2] != TREASURE) ){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  Current player's hand[%d]: %d, Expected: %d\n", g->handCount[whoseTurn(g)] - 1, g->hand[whoseTurn(g)][g->handCount[whoseTurn(g)] - 1], TREASURE);
		printf("  Current player's hand[%d]: %d, Expected: %d\n", g->handCount[whoseTurn(g)] - 2, g->hand[whoseTurn(g)][g->handCount[whoseTurn(g)] - 2], TREASURE);
		failed = 1;		
	}
	//Check extra cards added to discard and treasure removed
	if (g->discardCount[whoseTurn(g)] != pre->discardCount[whoseTurn(g)] + EXTRA_COUNT - 1){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  Current player's discard count: %d, Expected: %d\n", g->discardCount[whoseTurn(g)], pre->discardCount[whoseTurn(g)] + EXTRA_COUNT - 1);
		failed = 1;		
	}
	for (i = 1; i <= EXTRA_COUNT; i++){
		if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)] - i] != EXTRA_CARD){
			printf("FAIL when 1 treasure in deck, 1 in discard\n");
			printf("  Current player's discard[%d]: %d, Expected: %d\n", g->discardCount[whoseTurn(g)] - i, g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)] - i], EXTRA_CARD);
			failed = 1;		
		}
	}
	//Check no bonus coins added
	if (coin_bonus != 0){
		printf("FAIL when 1 treasure in deck, 1 in discard\n");
		printf("  Coin bonus after adventurer: %d, Expected: %d\n", coin_bonus, 0);
		failed = 1;		
	}	
	//Final check
	if (!failed){
		printf("PASS when 1 treasure in deck, 1 in discard\n");
	}
	*/

//---Test adventurer with 1 treasure card in deck (only 1 treasure total)
//---(all choices = -1, no bonus)
/*---Expected result: 
	- Game and turn settings are unchanged
	- Other player's cards (hand, deck, discard) are unchanged
	- Played card count increased by 1
	- Adventurer card added to played pile (in last position)
	- Current player's deck count decreased by 1 treasure + extras
	- Other cards in player's deck unchanged
	- Current player's discard count increased by extras
	- Current player's hand count increased by 1
	- Card added to player's hand is treasure
	- Cards added to player's discard are extras
	- No bonus coins

-------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------
NOTICE: Test disabled because of bug in current code causing infinite loop. 
While loop does not have exit condition for case when only 1 treasure exists.
-------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------
*/
	printf("FAIL when 1 treasure in deck\n");
	printf("  Test disabled because of infinite loop\n");
	/*
	//Setup card options
	choice1 = -1;
	choice2 = -1;
	choice3 = -1;
	coin_bonus = 0;
	//Create clean game
	if (initializeGame(NUM_PLAYERS, selectedCards, seed, g) == -1){
		printf("Could not initialize game. Testing aborted.\n");
		return -1;
	}
	//Set deck to 5 extras - 1 treasure - 5 extras
	g->deckCount[whoseTurn(g)] = 0;
	for (i = 1; i <= EXTRA_COUNT; i++){
		g->deck[whoseTurn(g)][g->deckCount[whoseTurn(g)]] = EXTRA_CARD;
		g->deckCount[whoseTurn(g)]++;
	}
	g->deck[whoseTurn(g)][g->deckCount[whoseTurn(g)]] = TREASURE;
	g->deckCount[whoseTurn(g)]++;
	for (i = 1; i <= EXTRA_COUNT; i++){
		g->deck[whoseTurn(g)][g->deckCount[whoseTurn(g)]] = EXTRA_CARD;
		g->deckCount[whoseTurn(g)]++;
	}
	//Set test position in hand to test card
	g->hand[whoseTurn(g)][TEST_POS] = TEST_CARD;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to execute card
	result = cardEffect(TEST_CARD, choice1, choice2, choice3, g, TEST_POS, &coin_bonus);
	failed = 0;
	if (result != 0){
		printf("FAIL when 1 treasure in deck\n");
		printf("  Return value: %d, Expected: %d\n", result, 0);
		failed = 1;
	}
	//Check game/turn settings
	if (checkNumPlayers(pre, g) < 0){
		printf("FAIL when 1 treasure in deck\n");
		printf("  NumPlayers: %d, Expected: %d\n", g->numPlayers, pre->numPlayers);
		failed = 1;
	}
	result = checkSupply(pre, g);
	if (result != 0){
		printf("FAIL when 1 treasure in deck\n");
		printf("  Supply count for card %d: %d, Expected: %d\n", result, g->supplyCount[result], pre->supplyCount[result]);
		failed = 1;
	}
	result = checkEmbargo(pre, g);
	if (result != 0){
		printf("FAIL when 1 treasure in deck\n");
		printf("  Embargo for card %d: %d, Expected: %d\n", result, g->embargoTokens[result], pre->embargoTokens[result]);
		failed = 1;
	}
	if (checkOutpost(pre, g) < 0){
		printf("FAIL when 1 treasure in deck\n");
		printf("  outpostPlayed: %d, Expected: %d\n", g->outpostPlayed, pre->outpostPlayed);
		printf("  outpostTurn: %d, Expected: %d\n", g->outpostTurn, pre->outpostTurn);
		failed = 1;
	}	
	if (checkTurn(pre, g) < 0){
		printf("FAIL when 1 treasure in deck\n");
		printf("  whoseTurn: %d, Expected: %d\n", g->whoseTurn, pre->whoseTurn);
		failed = 1;
	}
	if (checkPhase(pre, g) < 0){
		printf("FAIL when 1 treasure in deck\n");
		printf("  phase: %d, Expected: %d\n", g->phase, pre->phase);
		failed = 1;
	}	
	if (checkNumActions(pre, g) < 0){
		printf("FAIL when 1 treasure in deck\n");
		printf("  numActions: %d, Expected: %d\n", g->numActions, pre->numActions);
		failed = 1;
	}	
	if (checkCoins(pre, g) < 0){
		printf("FAIL when 1 treasure in deck\n");
		printf("  coins: %d, Expected: %d\n", g->coins, pre->coins);
		failed = 1;
	}
	if (checkNumBuys(pre, g) < 0){
		printf("FAIL when 1 treasure in deck\n");
		printf("  numBuys: %d, Expected: %d\n", g->numBuys, pre->numBuys);
		failed = 1;
	}
	//Check discard unchanged for other players
	for (i = 0; i < g->numPlayers; i++){
		//skip if current player
		if (i == whoseTurn(g)){
			continue;
		}
		if (pre->discardCount[i] != g->discardCount[i]){
			printf("FAIL when 1 treasure in deck\n");
			printf("  Player %d's discardCount: %d, Expected: %d\n", i, g->discardCount[i], pre->discardCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->discardCount[i]; j++){
				if (pre->discard[i][j] != g->discard[i][j]){
					printf("FAIL when 1 treasure in deck\n");
					printf("  Player %d's discard[%d]: %d, Expected: %d\n", i, j, g->discard[i][j], pre->discard[i][j]);
					failed = 1;
				}
			}
		}
	}
	//Check deck unchanged for other players
	for (i = 0; i < g->numPlayers; i++){
		//skip if current player
		if (i == whoseTurn(g)){
			continue;
		}
		if (pre->deckCount[i] != g->deckCount[i]){
			printf("FAIL when 1 treasure in deck\n");
			printf("  Player %d's deckCount: %d, Expected: %d\n", i, g->deckCount[i], pre->deckCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->deckCount[i]; j++){
				if (pre->deck[i][j] != g->deck[i][j]){
					printf("FAIL when 1 treasure in deck\n");
					printf("  Player %d's deck[%d]: %d, Expected: %d\n", i, j, g->deck[i][j], pre->deck[i][j]);
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
			printf("FAIL when 1 treasure in deck\n");
			printf("  Player %d's handCount: %d, Expected: %d\n", i, g->handCount[i], pre->handCount[i]);
			failed = 1;
		} else {   //check each card
			for (j = 0; j < g->handCount[i]; j++){
				if (pre->hand[i][j] != g->hand[i][j]){
					printf("FAIL when 1 treasure in deck\n");
					printf("  Player %d's hand[%d]: %d, Expected: %d\n", i, j, g->hand[i][j], pre->hand[i][j]);
					failed = 1;
				}
			}
		}
	}
	//Check adventurer added to played pile
	if (g->playedCardCount != pre->playedCardCount + 1){
		printf("FAIL when 1 treasure in deck\n");
		printf("  Played card count: %d, Expected: %d\n", g->playedCardCount, pre->playedCardCount + 1);
		failed = 1;
	} else if (g->playedCards[g->playedCardCount - 1] != TEST_CARD){
		printf("FAIL when 1 treasure in deck\n");
		printf("  Last played card: %d, Expected: %d\n", g->playedCards[g->playedCardCount - 1], TEST_CARD);
		failed = 1;		
	}
	//Check 1 treasure + extras removed from deck; other cards remain
	if (g->deckCount[whoseTurn(g)] != pre->deckCount[whoseTurn(g)] - EXTRA_COUNT - 1){
		printf("FAIL when 1 treasure in deck\n");
		printf("  Current player's deck count: %d, Expected: %d\n", g->deckCount[whoseTurn(g)], pre->deckCount[whoseTurn(g)] - EXTRA_COUNT - 1);
		failed = 1;		
	}
	for (i = 0; i < g->deckCount[whoseTurn(g)]; i++){
		if (g->deck[whoseTurn(g)][i] != EXTRA_CARD){
			printf("FAIL when 1 treasure in deck\n");
			printf("  Current player's deck[%d]: %d, Expected: %d\n", i, g->deck[whoseTurn(g)][i], EXTRA_CARD);
			failed = 1;		
		}	
	}
	//Check 1 treasure card added to hand
	if (g->handCount[whoseTurn(g)] != pre->handCount[whoseTurn(g)] + 1){
		printf("FAIL when 1 treasure in deck\n");
		printf("  Current player's hand count: %d, Expected: %d\n", g->handCount[whoseTurn(g)], pre->handCount[whoseTurn(g)] + 1);
		failed = 1;		
	}
	if (g->hand[whoseTurn(g)][g->handCount[whoseTurn(g)] - 1] != TREASURE){
		printf("FAIL when 1 treasure in deck\n");
		printf("  Current player's hand[%d]: %d, Expected: %d\n", g->handCount[whoseTurn(g)] - 1, g->hand[whoseTurn(g)][g->handCount[whoseTurn(g)] - 1], TREASURE);
		failed = 1;		
	}
	//Check extra cards added to discard
	if (g->discardCount[whoseTurn(g)] != pre->discardCount[whoseTurn(g)] + EXTRA_COUNT){
		printf("FAIL when 1 treasure in deck\n");
		printf("  Current player's discard count: %d, Expected: %d\n", g->discardCount[whoseTurn(g)], pre->discardCount[whoseTurn(g)] + EXTRA_COUNT);
		failed = 1;		
	}
	for (i = 1; i <= EXTRA_COUNT; i++){
		if (g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)] - i] != EXTRA_CARD){
			printf("FAIL when 1 treasure in deck\n");
			printf("  Current player's discard[%d]: %d, Expected: %d\n", g->discardCount[whoseTurn(g)] - i, g->discard[whoseTurn(g)][g->discardCount[whoseTurn(g)] - i], EXTRA_CARD);
			failed = 1;		
		}
	}
	//Check no bonus coins added
	if (coin_bonus != 0){
		printf("FAIL when 1 treasure in deck\n");
		printf("  Coin bonus after adventurer: %d, Expected: %d\n", coin_bonus, 0);
		failed = 1;		
	}	
	//Final check
	if (!failed){
		printf("PASS when 1 treasure in deck\n");
	}
	*/

	return 0;
}
