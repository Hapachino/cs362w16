/* ---------------------------------------------------------------------------
 * Unit test for getCost function. Since there is a limited number of choices
 * I'm using brute force
 * ---------------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testGetCost(int cardNumber);

int main() {
	int n, randCard;
	int k[27] = {curse, estate, duchy, province, copper, silver, gold,
				adventurer, council_room, feast, gardens, mine, remodel,
				smithy, village, baron, great_hall, minion, steward, tribute,
				ambassador, cutpurse, embargo, outpost, salvager, sea_hag, treasure_map};
		   
	SelectStream(2);
    PutSeed(3);
	
	for (n = 0; n < 2000; n++){
		printf ("--------------------------\n");
      printf ("Running test series %d ...\n", n+1);
		randCard = floor(Random() * 27); //Selects a random card from the list of cards
		testGetCost(k[randCard]);
		printf ("--------------------------\n\n");
	}
    
	
	return 0;
}

/* --------------------------------------------------------------------------------------------------------
 * All this function really does is manually set the cost for each card based on the random card passed in
 * It then compares that manually set cost to the return value of the getCost function. getCost returns the
 * cost of the card so they should be equal.
 *---------------------------------------------------------------------------------------------------------
 */
int testGetCost(int cardNumber) {
	int cost;
	
	if (cardNumber == curse){
		cost = 0;
	}
	else if (cardNumber == estate) {
		cost = 2;
	}
	else if (cardNumber == duchy) {
		cost = 5;
	}
	else if (cardNumber == province) {
		cost = 8;
	}
	else if (cardNumber == copper) {
		cost = 0;
	}
	else if (cardNumber == silver) {
		cost = 3;
	}
	else if (cardNumber == gold) {
		cost = 6;
	}
	else if (cardNumber == adventurer) {
		cost = 6;
	}
	else if (cardNumber == council_room) {
		cost = 5;
	}
	else if (cardNumber == feast) {
		cost = 4;
	}
	else if (cardNumber == gardens) {
		cost = 4;
	}
	else if (cardNumber == mine) {
		cost = 5;
	}
	else if (cardNumber == remodel) {
		cost = 4;
	}
	else if (cardNumber == smithy) {
		cost = 4;
	}
	else if (cardNumber == village) {
		cost = 3;
	}
	else if (cardNumber == baron) {
		cost = 4;
	}
	else if (cardNumber == great_hall) {
		cost = 3;
	}
	else if (cardNumber == minion) {
		cost = 5;
	}
	else if (cardNumber == steward) {
		cost = 3;
	}
	else if (cardNumber == tribute) {
		cost = 5;
	}
	else if (cardNumber == ambassador) {
		cost = 3;
	}
	else if (cardNumber == cutpurse) {
		cost = 4;
	}
	else if (cardNumber == embargo) {
		cost = 2;
	}
	else if (cardNumber == outpost) {
		cost = 5;
	}
	else if (cardNumber == salvager) {
		cost = 4;
	}
	else if (cardNumber == sea_hag) {
		cost = 4;
	}
	else if (cardNumber == treasure_map) {
		cost = 4;
	}
	
	assert (cost == getCost(cardNumber));
	
	printf ("Test passed\n");
	return 0;
}