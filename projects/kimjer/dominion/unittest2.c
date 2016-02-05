#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>

int main() {

	printf("-------------------------------------\n");
	printf("START of the unittest2 - KingdomCards\n");
	printf("-------------------------------------\n");

	int i;
	int k1[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int *k2 = kingdomCards(adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall);

	for(i = 0; i < 10; i++) {
		int ret = compare(&k1[i], &	k2[i]);
		if(ret != 0)
			printf("FAIL: return val should be 0, got %d\n", ret);
		assert(ret == 0);
	}
	printf("PASS: kingdom cards allocated correctly\n");

	return 0;
}
