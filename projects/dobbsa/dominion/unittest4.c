#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>


#define RSEED 5 // change rand()om seed here

int internalPointsCalc(int numCurse, int numEstate, int numDuchy, int numProvince, int numGardens, int numGreatHall, int deckCount) {
	int duchypts = numDuchy * 3;
	printf("Duchypts: %d\n", duchypts);
	int provincepts = numProvince * 6;
	printf("provincepts: %d\n",provincepts);
	int gardenpts = numGardens * (deckCount / 10);
	printf("gardenpts: %d\n", gardenpts);
	printf("estatepts: %d\n", numEstate);
	printf("cursepts: -%d\n", numCurse);
	printf("great hall: %d\n", numGreatHall);
	int total = numEstate + duchypts + provincepts + gardenpts + numGreatHall - numCurse;
	return total;
}

void customInit (int players, int cards[10], struct gameState *state) {
	initializeGame(players, cards, RSEED, state);
	int i;
	for (i = 0; i < players; i++) {
		state->handCount[i] = 0;
		state->discardCount[i] = 0;
		state->deckCount[i] = 0;
	}
}

int main() {

	printf("TEST: SCOREFOR\n\n");
	srand(RSEED);

	int players, numCurse, numEstate, numDuchy, numProvince, numGardens, numGreatHall, victoryCount, curseCount;
	players = rand() % (MAX_PLAYERS - 2) + 2;

	if (players == 2) {
		victoryCount = 8;
		curseCount = 10;
	}
	else if (players == 3) {
		victoryCount = 12;
		curseCount = 20;
	}
	else {
		victoryCount = 12;
		curseCount = 30;
	}


	struct gameState state;
	int cards[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	customInit(players, cards, &state);
	printf("TEST: Cards in hand\n");

	int i, j, k;
	for (i = 0; i < players; i++) {
		printf("Player %d\n", i + 1);
		numCurse = rand() % (curseCount + 1);
		printf("Curse: %d\n", numCurse);
		numEstate = rand() % (victoryCount + 1);
		printf("Estate: %d\n", numEstate);
		numDuchy = rand() % (victoryCount + 1);
		printf("Duchy: %d\n", numDuchy);
		numProvince = rand() % (victoryCount + 1);
		printf("Province: %d\n", numProvince);
		numGardens = rand() % (victoryCount + 1);
		printf("Gardens: %d\n", numGardens);
		numGreatHall = rand() % (victoryCount + 1);
		printf("Great Hall: %d\n", numGreatHall);

		k = 0;
		j = 0;
		while (j < numCurse) {
			state.hand[i][k] = curse;
			state.handCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numEstate) {
			state.hand[i][k] = estate;
			state.handCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numDuchy) {
			state.hand[i][k] = duchy;
			state.handCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numProvince) {
			state.hand[i][k] = province;
			state.handCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numGardens) {
			state.hand[i][k] = gardens;
			state.handCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numGreatHall) {
			state.hand[i][k] = great_hall;
			state.handCount[i]++;
			j++;
			k++;
		}
		j = 0;

		int deck = state.deckCount[i] + state.handCount[i] + state.discardCount[i];
		printf("Total deck: %d\n", deck);
		int internalsum = internalPointsCalc(numCurse, numEstate, numDuchy, numProvince, numGardens, numGreatHall, deck);
		int score = scoreFor(i, &state);
		printf("Expected score: %d\n", internalsum);
		printf("Calculated score: %d\n", score);
		if (internalsum == score)
			printf("PASSED\n");
		else
			printf("FAILED\n");

	}

	customInit(players, cards, &state);
	printf("TEST: Cards in deck\n");
		for (i = 0; i < players; i++) {
		printf("Player %d\n", i + 1);
		numCurse = rand() % (curseCount + 1);
		printf("Curse: %d\n", numCurse);
		numEstate = rand() % (victoryCount + 1);
		printf("Estate: %d\n", numEstate);
		numDuchy = rand() % (victoryCount + 1);
		printf("Duchy: %d\n", numDuchy);
		numProvince = rand() % (victoryCount + 1);
		printf("Province: %d\n", numProvince);
		numGardens = rand() % (victoryCount + 1);
		printf("Gardens: %d\n", numGardens);
		numGreatHall = rand() % (victoryCount + 1);
		printf("Great Hall: %d\n", numGreatHall);

		k = state.deckCount[i];
		j = 0;
		while (j < numCurse) {
			state.deck[i][k] = curse;
			state.deckCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numEstate) {
			state.deck[i][k] = estate;
			state.deckCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numDuchy) {
			state.deck[i][k] = duchy;
			state.deckCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numProvince) {
			state.deck[i][k] = province;
			state.deckCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numGardens) {
			state.deck[i][k] = gardens;
			state.deckCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numGreatHall) {
			state.deck[i][k] = great_hall;
			state.deckCount[i]++;
			j++;
			k++;
		}
		j = 0;

		
		int deck = state.deckCount[i] + state.handCount[i] + state.discardCount[i];
		printf("Total deck: %d\n", deck);
		int internalsum = internalPointsCalc(numCurse, numEstate, numDuchy, numProvince, numGardens, numGreatHall, deck);
		int score = scoreFor(i, &state);

		printf("Expected score: %d\n", internalsum);
		printf("Calculated score: %d\n", score);
		if (internalsum == score)
			printf("PASSED\n");
		else
			printf("FAILED\n");

	}

	customInit(players, cards, &state);
	printf("TEST: Cards in discard\n");
		for (i = 0; i < players; i++) {
		printf("Player %d\n", i + 1);
		numCurse = rand() % (curseCount + 1);
		printf("Curse: %d\n", numCurse);
		numEstate = rand() % (victoryCount + 1);
		printf("Estate: %d\n", numEstate);
		numDuchy = rand() % (victoryCount + 1);
		printf("Duchy: %d\n", numDuchy);
		numProvince = rand() % (victoryCount + 1);
		printf("Province: %d\n", numProvince);
		numGardens = rand() % (victoryCount + 1);
		printf("Gardens: %d\n", numGardens);
		numGreatHall = rand() % (victoryCount + 1);
		printf("Great Hall: %d\n", numGreatHall);

		k = 0;
		j = 0;
		while (j < numCurse) {
			state.discard[i][k] = curse;
			state.discardCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numEstate) {
			state.discard[i][k] = estate;
			state.discardCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numDuchy) {
			state.discard[i][k] = duchy;
			state.discardCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numProvince) {
			state.discard[i][k] = province;
			state.discardCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numGardens) {
			state.discard[i][k] = gardens;
			state.discardCount[i]++;
			j++;
			k++;
		}
		j = 0;
		while (j < numGreatHall) {
			state.discard[i][k] = great_hall;
			state.discardCount[i]++;
			j++;
			k++;
		}
		j = 0;

		
		int deck = state.deckCount[i] + state.handCount[i] + state.discardCount[i];
		printf("Total deck: %d\n", deck);
		int internalsum = internalPointsCalc(numCurse, numEstate, numDuchy, numProvince, numGardens, numGreatHall, deck);
		int score = scoreFor(i, &state);

		printf("Expected score: %d\n", internalsum);
		printf("Calculated score: %d\n", score);
		if (internalsum == score)
			printf("PASSED\n");
		else
			printf("FAILED\n");

	}

	customInit(players, cards, &state);
	printf("TEST: random distribution\n");
		for (i = 0; i < players; i++) {
		printf("Player %d\n", i + 1);
		numCurse = rand() % (curseCount + 1);
		printf("Curse: %d\n", numCurse);
		numEstate = rand() % (victoryCount + 1);
		printf("Estate: %d\n", numEstate);
		numDuchy = rand() % (victoryCount + 1);
		printf("Duchy: %d\n", numDuchy);
		numProvince = rand() % (victoryCount + 1);
		printf("Province: %d\n", numProvince);
		numGardens = rand() % (victoryCount + 1);
		printf("Gardens: %d\n", numGardens);
		numGreatHall = rand() % (victoryCount + 1);
		printf("Great Hall: %d\n", numGreatHall);

		for (j = 0; j < numCurse; j++) {
			k = rand() % 3;
			if (k == 0) {
				state.deck[i][state.deckCount[i]] = curse;
				state.deckCount[i]++;
			}
			else if (k == 1) {
				state.discard[i][state.discardCount[i]] = curse;
				state.discardCount[i]++;
			}
			else {
				state.hand[i][state.handCount[i]] = curse;
				state.handCount[i]++;
			}
		}

		for (j = 0; j < numEstate; j++) {
			k = rand() % 3;
			if (k == 0) {
				state.deck[i][state.deckCount[i]] = estate;
				state.deckCount[i]++;
			}
			else if (k == 1) {
				state.discard[i][state.discardCount[i]] = estate;
				state.discardCount[i]++;
			}
			else {
				state.hand[i][state.handCount[i]] = estate;
				state.handCount[i]++;
			}
		}

		for (j = 0; j < numDuchy; j++) {
			k = rand() % 3;
			if (k == 0) {
				state.deck[i][state.deckCount[i]] = duchy;
				state.deckCount[i]++;
			}
			else if (k == 1) {
				state.discard[i][state.discardCount[i]] = duchy;
				state.discardCount[i]++;
			}
			else {
				state.hand[i][state.handCount[i]] = duchy;
				state.handCount[i]++;
			}
		}

		for (j = 0; j < numProvince; j++) {
			k = rand() % 3;
			if (k == 0) {
				state.deck[i][state.deckCount[i]] = province;
				state.deckCount[i]++;
			}
			else if (k == 1) {
				state.discard[i][state.discardCount[i]] = province;
				state.discardCount[i]++;
			}
			else {
				state.hand[i][state.handCount[i]] = province;
				state.handCount[i]++;
			}
		}

		for (j = 0; j < numGardens; j++) {
			k = rand() % 3;
			if (k == 0) {
				state.deck[i][state.deckCount[i]] = gardens;
				state.deckCount[i]++;
			}
			else if (k == 1) {
				state.discard[i][state.discardCount[i]] = gardens;
				state.discardCount[i]++;
			}
			else {
				state.hand[i][state.handCount[i]] = gardens;
				state.handCount[i]++;
			}
		}

		for (j = 0; j < numGreatHall; j++) {
			k = rand() % 3;
			if (k == 0) {
				state.deck[i][state.deckCount[i]] = great_hall;
				state.deckCount[i]++;
			}
			else if (k == 1) {
				state.discard[i][state.discardCount[i]] = great_hall;
				state.discardCount[i]++;
			}
			else {
				state.hand[i][state.handCount[i]] = great_hall;
				state.handCount[i]++;
			}
		}
		

		
		int deck = state.deckCount[i] + state.handCount[i] + state.discardCount[i];
		printf("Total deck: %d\n", deck);
		int internalsum = internalPointsCalc(numCurse, numEstate, numDuchy, numProvince, numGardens, numGreatHall, deck);
		int score = scoreFor(i, &state);

		printf("Expected score: %d\n", internalsum);
		printf("Calculated score: %d\n", score);
		if (internalsum == score)
			printf("PASSED\n");
		else
			printf("FAILED\n");

	}	
	return 0;
}