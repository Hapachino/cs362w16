/*Tanna Richardson
  CS362 - Winter 2016
  Assignment 3
  Card test for: council_room
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PLAYERS 3
#define TEST_CARD council_room
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
	
	printf("---Testing Card: council_room---\n");
	
//---Test council_room (all choices = -1, no bonus)
/*---Expected result: 
	- Game and turn settings are unchanged
	- All player's discard is unchanged
	- Played card count increased by 1
	- Council_room card added to played pile (in last position)
	- Council_room removed from hand
	- Last 4 cards of current player's deck moved to hand
	- Current player's deckCount is decreased by 4
	- Current player's handCount is increased by 3 (+4 cards, -1 council_room)
	- Last 1 card of all other player's deck moved to hand
	- Other player's deckCount is decreased by 1
	- Other player's handCount is increased by 1
	- numBuys increased by 1
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
	//Set decks for all players to 5 extra cards
	for (i = 0; i < g->numPlayers; i++){
		g->deckCount[i] = 5;
		for (j = 0; j < 5; j++){
			g->deck[i][j] = EXTRA_CARD;
		}	
	}
	//Set test position in hand to test card
	g->hand[whoseTurn(g)][TEST_POS] = TEST_CARD;
	//Save current state
	memcpy(pre, g, sizeof(struct gameState));
	//Attempt to execute card
	result = cardEffect(TEST_CARD, choice1, choice2, choice3, g, TEST_POS, &coin_bonus);
	failed = 0;
	if (result != 0){
		printf("FAIL return check\n");
		printf("  Return value: %d, Expected: %d\n", result, 0);
		failed = 1;
	}
	//Check game/turn settings
	if (checkNumPlayers(pre, g) < 0){
		printf("FAIL gameState check\n");
		printf("  NumPlayers: %d, Expected: %d\n", g->numPlayers, pre->numPlayers);
		failed = 1;
	}
	result = checkSupply(pre, g);
	if (result != 0){
		printf("FAIL gameState check\n");
		printf("  Supply count for card %d: %d, Expected: %d\n", result, g->supplyCount[result], pre->supplyCount[result]);
		failed = 1;
	}
	result = checkEmbargo(pre, g);
	if (result != 0){
		printf("FAIL gameState check\n");
		printf("  Embargo for card %d: %d, Expected: %d\n", result, g->embargoTokens[result], pre->embargoTokens[result]);
		failed = 1;
	}
	if (checkOutpost(pre, g) < 0){
		printf("FAIL gameState check\n");
		printf("  outpostPlayed: %d, Expected: %d\n", g->outpostPlayed, pre->outpostPlayed);
		printf("  outpostTurn: %d, Expected: %d\n", g->outpostTurn, pre->outpostTurn);
		failed = 1;
	}	
	if (checkTurn(pre, g) < 0){
		printf("FAIL gameState check\n");
		printf("  whoseTurn: %d, Expected: %d\n", g->whoseTurn, pre->whoseTurn);
		failed = 1;
	}
	if (checkPhase(pre, g) < 0){
		printf("FAIL gameState check\n");
		printf("  phase: %d, Expected: %d\n", g->phase, pre->phase);
		failed = 1;
	}	
	if (checkNumActions(pre, g) < 0){
		printf("FAIL gameState check\n");
		printf("  numActions: %d, Expected: %d\n", g->numActions, pre->numActions);
		failed = 1;
	}	
	if (checkCoins(pre, g) < 0){
		printf("FAIL gameState check\n");
		printf("  coins: %d, Expected: %d\n", g->coins, pre->coins);
		failed = 1;
	}
	//Check all player's discard unchanged
	if (checkDiscards(pre, g) < 0){
		printf("FAIL discard check\n");
		printf("  Discards changed after smithy\n");
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
				printf("\n");
			}
		}
		failed = 1;
	}
	//Check council_room added to played pile
	if (g->playedCardCount != pre->playedCardCount + 1){
		printf("FAIL played cards check\n");
		printf("  Played card count: %d, Expected: %d\n", g->playedCardCount, pre->playedCardCount + 1);
		failed = 1;
	} else if (g->playedCards[g->playedCardCount - 1] != TEST_CARD){
		printf("FAIL played cards check\n");
		printf("  Last played card: %d, Expected: %d\n", g->playedCards[g->playedCardCount - 1], TEST_CARD);
		failed = 1;		
	}
	//Check 4 cards add to current player's hand, council_room removed
	if (g->handCount[whoseTurn(g)] != pre->handCount[whoseTurn(g)] + 3){
		printf("FAIL added 4 cards\n");
		printf("  Current player's hand count: %d, Expected: %d\n", g->handCount[whoseTurn(g)], pre->handCount[whoseTurn(g)] + 3);
		failed = 1;		
	}
	//Check 3 cards removed from current player's deck
	if (g->deckCount[whoseTurn(g)] != pre->deckCount[whoseTurn(g)] - 4){
		printf("FAIL remove 4 cards from deck\n");
		printf("  Current player's deck count: %d, Expected: %d\n", g->deckCount[whoseTurn(g)], pre->deckCount[whoseTurn(g)] - 4);
		failed = 1;		
	}
	//Check cards removed from current deck = cards added to hand
	for(i = 1; i <= 4; i++){
		if (g->hand[whoseTurn(g)][g->deckCount[whoseTurn(g)] - i] != pre->deck[whoseTurn(g)][pre->deckCount[whoseTurn(g)] - i]){
			printf("FAIL move 4 cards from deck to hand\n");
			printf("  Current player's hand[%d]: %d, Expected: %d\n", g->handCount[whoseTurn(g)] - i, g->hand[whoseTurn(g)][g->deckCount[whoseTurn(g)] - i], pre->deck[whoseTurn(g)][pre->deckCount[whoseTurn(g)] - i]);
			failed = 1;		
		}	
	}
	//Check 1 card added to all other player's hands
	for (i = 1; i < g->numPlayers; i++){
		if (g->handCount[i] != pre->handCount[i] + 1){
			printf("FAIL added 1 card to opponents\n");
			printf("  Player %d's hand count: %d, Expected: %d\n", i, g->handCount[i], pre->handCount[i] + 1);
			failed = 1;		
		}	
	}
	//Check 1 cards removed from all other player's decks
	for (i= 1; i < g->numPlayers; i++){
		if (g->deckCount[i] != pre->deckCount[i] - 1){
			printf("FAIL remove 1 card from opponent's deck\n");
			printf("  Player %d's deck count: %d, Expected: %d\n", i, g->deckCount[i], pre->deckCount[i] - 1);
			failed = 1;		
		}	
	}
	//Check cards removed from other's deck = cards added to hand
	for(i = 1; i <= g->numPlayers; i++){
		if (g->hand[i][g->deckCount[i] - 1] != pre->deck[i][pre->deckCount[i] - i]){
			printf("FAIL move 1 card from opponent's deck to hand\n");
			printf("  Player %d's hand[%d]: %d, Expected: %d\n", i, g->handCount[i] - 1, g->hand[i][g->deckCount[i] - 1], pre->deck[i][pre->deckCount[i] - 1]);
			failed = 1;		
		}	
	}
	//Check numBuys increased by 1
	if (g->numBuys != pre->numBuys + 1){
		printf("FAIL numBuys check\n");
		printf("  numBuys: %d, Expected: %d\n", g->numBuys, pre->numBuys + 1);
		failed = 1;
	}
	//Check no bonus coins added
	if (coin_bonus != 0){
		printf("FAIL coin bonus = 0\n");
		printf("  Coin bonus after smithy: %d, Expected: %d\n", coin_bonus, 0);
		failed = 1;		
	}	
	//Final check
	if (!failed){
		printf("PASS all smithy checks\n");
	}

	
	return 0;
}
