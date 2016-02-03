/* Paul Zotz
 * CS 362 Winter 2016
 * Assignment 3 - unit test 1 - kingdomCards() */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int k1 = 0;
	int k2 = 1;
	int k3 = 2;
	int k4 = 3;
	int k5 = 4;
	int k6 = 5;
	int k7 = 6;
	int k8 = 7;
	int k9 = 8;
	int k10 = 9;

    int i = 0;
    int* kingdomCardsTest;
    printf ("TESTING kingdomCards():\n");
    kingdomCardsTest = kingdomCards(k1, k2, k3, k4, k5, k6, k7, k8, k9, k10);
    for (i = 0; i < 10; i++)
    {
#if (NOISY_TEST == 1)
        printf("Test value of k%d\n", i + 1);
        printf("k%d = %d, expected = %d\n", i + 1, kingdomCardsTest[i], i);
        printf("\n");
#endif
        assert(kingdomCardsTest[i] == i);
    }
	printf("All tests passed.\n");
	return 0;
}
