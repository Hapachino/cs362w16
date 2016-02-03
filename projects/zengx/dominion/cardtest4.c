/* for steward test
1: it has 3 choice
		if choice1 ==1, check if card in hand +2 and -1 the one used(choose to discard) and if card on deck -2 
		if choice1 ==2, check if money +2
		if choice1 ==3, set 5 card, random choose trash 2 of them check card on hand and card on deck are correct.
*/
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

#define TESTCARD "steward"

int tests_run = 0;

int foo = 7;
int bar = 4;

int newCards = 0;
int discarded = 1;
int xtraCoins = 0;
int shuffledCards = 0;

int i, j, m;
int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
int remove1, remove2;
int seed = 1000;
int numPlayers = 2;
int thisPlayer = 0;
struct gameState G, testG;
int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
sea_hag, tribute, smithy, council_room };

//if choice1 ==1, check if card in hand +2 and -1 the one used(choose to discard) and if card on deck -2 
static char * test_add_2_cards() {
	printf("=========== test steward add 2 cards ===========\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

	newCards = 2;
	xtraCoins = 0;
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - 1);
	printf("deck count = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards );
	printf("coins = %d, expected = %d\n", testG.coins, G.coins + xtraCoins);
	mu_assert("-error: handCard number not correct", testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - 1);
	mu_assert("-error: deckCard number not correct", testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards );
	mu_assert("-error: coins not correct", testG.coins == G.coins + xtraCoins);
	return 0;
}
//if choice1 ==2, check if money +2
static char * test_add_2_coins() {
	printf("============= test steward add 2 coins =========\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	choice1 = 2;
	cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);
	mu_assert("-error: coins number not correct", G.coins == testG.coins - 2);
	return 0;
}
//if choice1 ==3, set 5 card, random choose trash 2 of them check card on hand and card on deck are correct.
static char * test_trash_2_cards() {
	printf("============test steward card trash 2 cards ===========\n");
	choice1 = 3;
	int count = 0;
	while (count < 100)
	{
		G.hand[thisPlayer][0] = adventurer;
		G.hand[thisPlayer][1] = copper;
		G.hand[thisPlayer][2] = embargo;
		G.hand[thisPlayer][3] = village;
		G.hand[thisPlayer][4] = minion;
		memcpy(&testG, &G, sizeof(struct gameState));
		srand(time(NULL));


		choice2 = rand() % 4 + 1;
		choice3 = rand() % 4 + 1;
		if (choice3 == choice2)
		{
			choice3 = (choice2 + 1) % 5;
			if (choice3 == 0)
			{
				choice3++;
			}
		}

		int saveCard1 = G.hand[thisPlayer][choice2];
		int saveCard2 = G.hand[thisPlayer][choice3];
		cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);
		//check trashed card not in hand anymore
		int m = 0;
		for (m = 0; m < testG.handCount[thisPlayer]; m++)
		{
		//	printf("card in hand: %d ; trashed card1: %d\n", testG.hand[thisPlayer][m], saveCard1);
			mu_assert("-error:choice2 card not trash", testG.hand[thisPlayer][m] != saveCard1);
		//	printf("card in hand: %d ; trashed card2: %d\n", testG.hand[thisPlayer][m], saveCard2);
			mu_assert("-error:choice3 card not trash", testG.hand[thisPlayer][m] != saveCard2);
		}
	//	printf("befor run on hand: %d ; after run on hand: %d\n", G.handCount[thisPlayer], testG.handCount[thisPlayer]);
	//	printf("befor run on deck: %d ; after run on deck: %d\n", G.deckCount[thisPlayer], testG.deckCount[thisPlayer]);
		mu_assert("-error:card number not correct", G.handCount[thisPlayer] == testG.handCount[thisPlayer] + 3);
		mu_assert("-error: deck number not correct", G.deckCount[thisPlayer] == testG.deckCount[thisPlayer]);
		count++;
	}
	return 0;

}


static char * all_tests() {
	mu_run_test(test_add_2_cards);
	mu_run_test(test_add_2_coins);
	mu_run_test(test_trash_2_cards);

	return 0;
}

int main(int argc, char **argv) {


	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	all_tests();
	printf("Tests run: %d\n", tests_run);

	return 0;
}
