//Author: colvinch
//Filename: unittest1.c
//Function: getCost()
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1
#define MAX_CARDS 27

int main(){

	int i;
	int j = 0;
	int k [MAX_CARDS] = {copper, silver, gold, estate, duchy, province, adventurer, council_room,
			feast, gardens, mine, remodel, smithy, village, baron, great_hall, minion, steward,
			tribute, ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map, curse};

	for (i = 0; i < MAX_CARDS; i++){
		if (getCost(k[i]) <= 8)
			continue;
		else
			printf("%d has failed", k[i]);
			j++;
	}

	if (j == 0)
		printf("unittest1 [getCost()] shows no errors.\n");
    else
        printf("unittest1 [getCost()] shows %d errors.\n", j);


	return (0);

}
