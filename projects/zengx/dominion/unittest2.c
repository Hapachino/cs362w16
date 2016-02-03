#include <stdio.h>
#include "minunit.h"

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h> 


int tests_run = 0;
int seed = 1000;
int numPlayers = 2;
int thisPlayer = 0;
struct gameState G, testG;
int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
sea_hag, tribute, smithy, council_room };

/*for gainCard
Input: test supplypos range
test toFlag range

*/

static char * test_gain_card_add_to_deck() {
	printf("=========== test gain card add card to deck =============\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	int currentPlayer = G.whoseTurn;
	int result = gainCard(adventurer, &testG,1, currentPlayer);
	mu_assert("-error: function should succeed \n", result == 0);
	mu_assert("-error: deck count should be increased by 1\n", G.deckCount[thisPlayer] == testG.deckCount[thisPlayer] - 1);
	mu_assert("-error: last card added should be adventurer\n", testG.deck[thisPlayer][testG.deckCount[thisPlayer] - 1] == adventurer);
	mu_assert("-error: discard deck should remain the same\n", G.discardCount[thisPlayer] == testG.discardCount[thisPlayer]);
	mu_assert("-error: hand cards count should remain the same\n", G.handCount[thisPlayer] == testG.handCount[thisPlayer]);
	mu_assert("-error: supply card count should decrase by 1 \n", G.supplyCount[adventurer] == testG.supplyCount[adventurer] + 1);
	return 0;
}

static char * test_gain_card_add_to_hand() {
	printf("=========== test gain card add card to hand =============\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	int currentPlayer = G.whoseTurn;
	int result = gainCard(adventurer, &testG, 2, currentPlayer);
	mu_assert("-error: function should succeed \n", result == 0);
	mu_assert("-error: hand count should be increased by 1\n", G.handCount[thisPlayer] == testG.handCount[thisPlayer] - 1);
	mu_assert("-error: last card added should be adventurer\n", testG.hand[thisPlayer][testG.handCount[thisPlayer] - 1] == adventurer);
	mu_assert("-error: discard deck should remain the same\n", G.discardCount[thisPlayer] == testG.discardCount[thisPlayer]);
	mu_assert("-error: deck cards count should remain the same\n", G.deckCount[thisPlayer] == testG.deckCount[thisPlayer]);
	mu_assert("-error: supply card count should decrase by 1 \n", G.supplyCount[adventurer] == testG.supplyCount[adventurer] + 1);
	return 0;
}

static char * test_gain_card_add_to_discard() {
	printf("=========== test gain card add card to discard =============\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	int currentPlayer = G.whoseTurn;
	int result = gainCard(adventurer, &testG, 0, currentPlayer);
	mu_assert("-error: function should succeed \n", result == 0);
	mu_assert("-error: discard count should be increased by 1\n", G.discardCount[thisPlayer] == testG.discardCount[thisPlayer] - 1);
	mu_assert("-error: last card added should be adventurer\n", testG.discard[thisPlayer][testG.discardCount[thisPlayer] - 1] == adventurer);
	mu_assert("-error: deck count should remain the same\n", G.deckCount[thisPlayer] == testG.deckCount[thisPlayer]);
	mu_assert("-error: hand cards count should remain the same\n", G.handCount[thisPlayer] == testG.handCount[thisPlayer]);
	mu_assert("-error: supply card count should decrase by 1 \n", G.supplyCount[adventurer] == testG.supplyCount[adventurer] + 1);
	return 0;
}

static char * test_gain_card_not_enough_supply() {
	printf("=========== test gain card not enough supply card =============\n");
	G.supplyCount[adventurer] = 0; // Set adventurer count to be 0
	memcpy(&testG, &G, sizeof(struct gameState));
	int currentPlayer = G.whoseTurn;
	int result = gainCard(adventurer, &testG, 0, currentPlayer);
	mu_assert("-error: should return -1 when there is no supply \n", result == -1);
	mu_assert("-error: deck count should remain the same\n", G.deckCount[thisPlayer] == testG.deckCount[thisPlayer]);
	mu_assert("-error: hand cards count should remain the same\n", G.handCount[thisPlayer] == testG.handCount[thisPlayer]);
	mu_assert("-error: discard cards count should remain the same \n", G.discardCount[thisPlayer] == testG.discardCount[thisPlayer]);
	return 0;
}



static char * all_tests() {
	mu_run_test(test_gain_card_add_to_deck);
	mu_run_test(test_gain_card_add_to_hand);
	mu_run_test(test_gain_card_add_to_discard);
	mu_run_test(test_gain_card_not_enough_supply);
	return 0;
}

int main(int argc, char **argv) {


	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	all_tests();

	printf("Tests run: %d\n", tests_run);

	return 0;
}