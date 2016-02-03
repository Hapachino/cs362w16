/*
* Unit Test for scoreFor()
*
* Business Requirements:
*	
*   1. Should add together to find a total score the player
*   2. None of the gameState should be affected by finding a score
*   3. Estates should be worth 1 each
*   4. Duchys should be worth 3 each
*   5. Provinces should be worth 6 each
*   6. Gardens should be worth total number of cards / 10 rounded down each
*   7. Curses should be worth - 1 each
*   8. Great Halls should be worth 1 each
*   9. Each victory card should only be counted wether they are in hand deck or discard and only once per card
*
* unittest3: unittest3.c dominion.o rngs.o
*	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>

void checkState(struct gameState pre, struct gameState post){
	int i;
	//assert(pre.numPlayers == post.numPlayers); //number of players
	if (pre.numPlayers != post.numPlayers)
	{
		printf("Num Players Changed TEST FAILED\n");
	}
	for (i = 0; i < treasure_map; i++)
	{
		//assert(pre.supplyCount[i] == post.supplyCount[i]);
		if (pre.supplyCount[i] != post.supplyCount[i])
		{
			printf("Supply Counts Changed TEST FAILED\n");
		}
		//assert(pre.embargoTokens[i] == post.embargoTokens[i]);
		if (pre.embargoTokens[i] != post.embargoTokens[i])
		{
			printf("Embargo Tokens Changed TEST FAILED\n");
		}
	}
	//assert(pre.outpostPlayed == post.outpostPlayed);
	if (pre.outpostPlayed != post.outpostPlayed)
	{
		printf("outpost played changed TEST FAILED\n");
	}
	//assert(pre.outpostTurn == post.outpostTurn);
	if (pre.outpostTurn != post.outpostTurn)
	{
		printf("outpost turn changed TEST FAILED\n");
	}
	//assert(pre.whoseTurn == post.whoseTurn);
	if (pre.whoseTurn != post.whoseTurn)
	{
		printf("whose turn changed TEST FAILED\n");
	}
	//assert(pre.phase == post.phase);
	if (pre.phase != post.phase)
	{
		printf("phase changed TEST FAILED\n");
	}
	//assert(pre.numActions == post.numActions);
	if (pre.numActions != post.numActions)
	{
		printf("num actions changed TEST FAILED\n");
	}
	//assert(pre.coins == post.coins);
	if (pre.coins != post.coins)
	{
		printf("num coins changed TEST FAILED\n");
	}
	//assert(pre.numBuys == post.numBuys);
	if (pre.numBuys != post.numBuys)
	{
		printf("num buys changed TEST FAILED\n");
	}
	//assert(pre.playedCardCount == post.playedCardCount);
	if (pre.playedCardCount != post.playedCardCount)
	{
		printf("num played cards changed TEST FAILED\n");
	}

}

int main() {
	int i, n, p, j, randCard, x, temp, count, r, gardensScore;
	struct gameState G;
	struct gameState pre;
	int maxCount = 5;
	int numPlayer = 2;
	int seed = 1000;

	int k[16] = { adventurer, council_room, gardens, curse, mine
		, remodel, smithy, village, baron, great_hall, copper, silver, gold, estate, duchy, province };

	//creates random seed
	srand(time(NULL));

	SelectStream(2);
	PutSeed(3);

	//arrays of all estate, duchy, province, great_hall, curse
	int estates[MAX_HAND];
	int duchys[MAX_HAND];
	int provinces[MAX_HAND];
	int great_halls[MAX_HAND];
	int curses[MAX_HAND];
	int gardenss[MAX_HAND];
	for (i = 0; i < MAX_HAND; i++)
	{
		estates[i] = estate;
		duchys[i] = duchy;
		provinces[i] = province;
		great_halls[i] = great_hall;
		curses[i] = curse;
		gardenss[i] = gardens;
 
	}

	printf("Running unittest3 for scoreFor()\n");

	//check that estates, duchys, provices, great_halls, curse calculate correctly in hand

	for (p = 0; p < numPlayer; p++)
	{
		for (count = 0; count <= maxCount; count++)
		{
			memset(&G, 23, sizeof(struct gameState));				// clear the game state
			r = initializeGame(numPlayer, k, seed, &G);				// initialize a new game
			G.handCount[p] = count;								// set the number of cards
			G.discardCount[p] = 0;
			G.deckCount[p] = 0;
			

			for (i = 0; i < G.handCount[p]; i++)
			{
				G.hand[p][i] = estate;
			}
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == handCount * 1);							// check if the score is correct
			if (temp != count * 1)
			{
				printf("Estates not added correctly in hand TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change
			
			for (i = 0; i < G.handCount[p]; i++)
			{
				G.hand[p][i] = duchy;
			}
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == handCount * 3);							// check if the score is correct
			if (temp != count * 3)
			{
				printf("Duchys not added correctly in hand TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

			for (i = 0; i < G.handCount[p]; i++)
			{
				G.hand[p][i] = province;
			}
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == handCount * 6);							// check if the score is correct
			if (temp != count * 6)
			{
				printf("Provinces not added correctly in hand TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

			for (i = 0; i < G.handCount[p]; i++)
			{
				G.hand[p][i] = great_hall;
			}
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == handCount * 1);							// check if the score is correct
			if (temp != count * 1)
			{
				printf("great halls not added correctly in hand TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

			for (i = 0; i < G.handCount[p]; i++)
			{
				G.hand[p][i] = curse;
			}
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == handCount * -1);							// check if the score is correct
			if (temp != count * -1)
			{
				printf("curses not added correctly in hand TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

		}
	}

	//check that estates, duchys, provices, great_halls, curse calculate correctly in discard
	
	for (p = 0; p < numPlayer; p++)
	{
		for (count = 0; count <= maxCount; count++)
		{
			memset(&G, 23, sizeof(struct gameState));				// clear the game state
			r = initializeGame(numPlayer, k, seed, &G);				// initialize a new game
			G.handCount[p] = 0;								// set the number of cards
			G.discardCount[p] = count;
			G.deckCount[p] = 0;

			memcpy(G.hand[p], estates, sizeof(int) * count);	         // set all the cards to estate
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == handCount * 1);							// check if the score is correct
			if (temp != count * 1)
			{
				printf("Estates not added correctly in discard TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

			memcpy(G.hand[p], duchys, sizeof(int) * count);	         // set all the cards to duchy
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == count * 3);							// check if the score is correct
			if (temp != count * 3)
			{
				printf("Duchys not added correctly in hand TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

			memcpy(G.hand[p], provinces, sizeof(int) * count);	// set all the cards to provinces
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == count * 6);							// check if the score is correct
			if (temp != count * 6)
			{
				printf("Provinces not added correctly in hand TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

			memcpy(G.hand[p], great_halls, sizeof(int) * count);// set all the cards to great_hall
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == count * 1);							// check if the score is correct
			if (temp != count * 1)
			{
				printf("great halls not added correctly in hand TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

			memcpy(G.hand[p], curses, sizeof(int) * count);		// set all the cards to great_hall
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == count * -1);							// check if the score is correct
			if (temp != count * -1)
			{
				printf("curses not added correctly in hand TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

		}
	}
	
	//check that estates, duchys, provices, great_halls, curse calculate correctly in deck

	for (p = 0; p < numPlayer; p++)
	{
		for (count = 0; count <= maxCount; count++)
		{
			memset(&G, 23, sizeof(struct gameState));				// clear the game state
			r = initializeGame(numPlayer, k, seed, &G);				// initialize a new game
			G.deckCount[p] = count;								// set the number of cards on hand																			

			memcpy(G.deck[p], estates, sizeof(int) * count);	// set all the cards to estate
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == count * 1);							// check if the score is correct
			if (temp != count * 1)
			{
				printf("Estates not added correctly in deck TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

			memcpy(G.deck[p], duchys, sizeof(int) * count);	    // set all the cards to duchy
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == count * 3);							// check if the score is correct
			if (temp != count * 3)
			{
				printf("Duchys not added correctly in deck TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

			memcpy(G.deck[p], provinces, sizeof(int) * count);	// set all the cards to provinces
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == count * 6);							// check if the score is correct
			if (temp != count * 6)
			{
				printf("provinces not added correctly in deck TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

			memcpy(G.deck[p], great_halls, sizeof(int) * count);// set all the cards to great_hall
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == count * 1);							// check if the score is correct
			if (temp != count * 1)
			{
				printf("great halls not added correctly in deck TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

			memcpy(G.deck[p], curses, sizeof(int) * count);		// set all the cards to great_hall
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			//assert(temp == count * -1);							// check if the score is correct
			if (temp != count * -1)
			{
				printf("curses not added correctly in deck TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

		}
	}

	//check if gardens work in hand
	
	for (p = 0; p < numPlayer; p++)
	{
		for (count = 0; count <= 30; count++)
		{
			memset(&G, 23, sizeof(struct gameState));				// clear the game state
			r = initializeGame(numPlayer, k, seed, &G);				// initialize a new game
			G.handCount[p] = count;								// set the number of cards on hand

			memcpy(G.hand[p], gardenss, sizeof(int) * count);	// set all the cards to great_hall
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			gardensScore = count * (count / 10);			// number of gardens (cards in hand) * number of total cards / 10
			//assert(temp == gardensScore);							// check if the score is correct
			if (temp != gardensScore)
			{
				printf("Gardens not added correclty in hand TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

		}
	}

	//check if gardens work in discard

	for (p = 0; p < numPlayer; p++)
	{
		for (count = 0; count <= 30; count++)
		{
			memset(&G, 23, sizeof(struct gameState));				// clear the game state
			r = initializeGame(numPlayer, k, seed, &G);				// initialize a new game
			G.discardCount[p] = count;								// set the number of cards on discard

			memcpy(G.discard[p], gardenss, sizeof(int) * count);	// set all the cards to great_hall
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			gardensScore = count * (count / 10);			// number of gardens (cards in hand) * number of total cards / 10
			//assert(temp == gardensScore);							// check if the score is correct
			if (temp != gardensScore)
			{
				printf("Gardens not added correclty in discard TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

		}
	}

	//check if gardens work in deck

	for (p = 0; p < numPlayer; p++)
	{
		for (count = 0; count <= 30; count++)
		{
			memset(&G, 23, sizeof(struct gameState));				// clear the game state
			r = initializeGame(numPlayer, k, seed, &G);				// initialize a new game
			G.deckCount[p] = count;								// set the number of cards on deck

			memcpy(G.deck[p], gardenss, sizeof(int) * count);	// set all the cards to great_hall
			memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
			temp = scoreFor(p, &G);
			gardensScore = count * (count / 10);			// number of gardens (cards in hand) * number of total cards / 10
			//assert(temp == gardensScore);							// check if the score is correct
			if (temp != gardensScore)
			{
				printf("Gardens not added correclty in deck TEST FAILED\n");
			}
			checkState(pre, G);										// check new gamestate vs old nothing should change

		}
	}
	

	//create a random gamestate keeping deckCount discardCount and handCount inside MAX limits and random numPlayers
	for (n = 0; n < 30; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
			((char*)&G)[i] = floor(Random() * 256);
		}
		p = rand() % 4 + 1;
		G.numPlayers = p;
		int manualCount[p];
		int currentCount;
		int gardensCount;
		for (i = 0; i < p; i++)
		{
			currentCount = 0;
			gardensCount = 0;
			//determine random deck count
			G.deckCount[i] = rand() % MAX_DECK + 1;
			//fill deck with random cards
			for (j = 0; j < G.deckCount[i]; j++)
			{
				randCard = rand() % 16;							// random card from list of cards
				G.deck[i][j] = k[randCard];
				if (k[randCard] == estate)
				{
				//	printf(" \n Adding estate Before = %d", currentCount);
					currentCount++;
					//printf(" After = %d \n", currentCount);
				}
				else if (k[randCard] == duchy)
				{
					//printf(" \n Adding duchy Before = %d", currentCount);
					currentCount = currentCount + 3;
					//printf(" After = %d \n", currentCount);

				}
				else if (k[randCard] == province)
				{
					//printf(" \n Adding province Before = %d", currentCount);
					currentCount = currentCount + 6;
					//printf(" After = %d \n", currentCount);
				}
				else if (k[randCard] == great_hall)
				{
					//printf(" \n Adding greathall Before = %d", currentCount);
					currentCount++;
					//printf(" After = %d \n", currentCount);
				}
				else if (k[randCard] == curse)
				{
					//printf(" \n Adding curse Before = %d", currentCount);
					currentCount--;
					//printf(" After = %d \n", currentCount);
				}
				else if (k[randCard] == gardens)
				{
					gardensCount++;
				}
			}

			//determine random discard count
			G.discardCount[i] = rand() % MAX_DECK + 1;
			//fill discard with random cards
			for (j = 0; j < G.discardCount[i]; j++)
			{
				randCard = rand() % 16;							// random card from list of cards
				G.discard[i][j] = k[randCard];
				if (k[randCard] == estate)
				{
					//printf(" \n Adding estate Before = %d", currentCount);
					currentCount++;
					//printf(" After = %d \n", currentCount);
				}
				else if (k[randCard] == duchy)
				{
					//printf(" \n Adding duchy Before = %d", currentCount);
					currentCount = currentCount + 3;
					//printf(" After = %d \n", currentCount);

				}
				else if (k[randCard] == province)
				{
				//	printf(" \n Adding province Before = %d", currentCount);
					currentCount = currentCount + 6;
					//printf(" After = %d \n", currentCount);
				}
				else if (k[randCard] == great_hall)
				{
					//printf(" \n Adding greathall Before = %d", currentCount);
					currentCount++;
					//printf(" After = %d \n", currentCount);
				}
				else if (k[randCard] == curse)
				{
					//printf(" \n Adding curse Before = %d", currentCount);
					currentCount--;
					//printf(" After = %d \n", currentCount);
				}
				else if (k[randCard] == gardens)
				{
					gardensCount++;
				}
			}

			//determine random hand count
			G.handCount[i] = rand() % MAX_HAND + 1;
			//fill hand with random cards
			for (j = 0; j < G.handCount[i]; j++)
			{
				randCard = rand() % 16;							// random card from list of cards
				G.hand[i][j] = k[randCard];
				if (k[randCard] == estate)
				{
					//printf(" \n Adding estate Before = %d", currentCount);
					currentCount++;
					//printf(" After = %d \n", currentCount);
				}
				else if (k[randCard] == duchy)
				{
					//printf(" \n Adding duchy Before = %d", currentCount);
					currentCount = currentCount + 3;
					//printf(" After = %d \n", currentCount);
					
				}
				else if (k[randCard] == province)
				{
					//printf(" \n Adding province Before = %d", currentCount);
					currentCount = currentCount + 6;
					//printf(" After = %d \n", currentCount);
				}
				else if (k[randCard] == great_hall)
				{
					//printf(" \n Adding greathall Before = %d", currentCount);
					currentCount++;
					//printf(" After = %d \n", currentCount);
				}
				else if (k[randCard] == curse)
				{
					//printf(" \n Adding curse Before = %d", currentCount);
					currentCount--;
					//printf(" After = %d \n", currentCount);
				}
				else if (k[randCard] == gardens)
				{
					gardensCount++;
				}
			}

					
			//number of cards in deck divided by 10 rounded down used for gardens score
			x = ((G.deckCount[i] + G.handCount[i] + G.discardCount[i]));
			//printf("\n X = %d \n", x);
			x = x / 10;
			//printf("\n X / 10 = %d \n", x);
			//manual score count
			//printf("\n gardensCount = %d \n", gardensCount);
			manualCount[i] = currentCount + (gardensCount * x);
			//printf("\n manualCount = %d \n", manualCount[i]);
			//printf("\n scoreFor = %d \n", scoreFor(i, &G));

		}
		memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate
		for (i = 0; i < p; i++)
		{
			//assert(manualCount[i] == scoreFor(i, &G));			// check manual score calculation is same as scoreFor
			if (manualCount[i] != scoreFor(i, &G))
			{
				printf("Creating random scoreing cards in full deck did not add correctly TEST FAILED\n");
			}
		}
		checkState(pre, G);										// make sure game state didnt change

	}
	
	printf("Finished running unittest3 for scoreFor()\n");

	return 0;
}