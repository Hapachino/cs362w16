#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define TESTCARD "embargo"
#define VERBOSE 0


int main() {
    srand(time(NULL));
    int i, j, r, c, result, thisPlayer, numPlayers, newCards, newCoins, discarded, stream;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int k[10];
	struct gameState G, testG;



	stream = 0;
	c = 0;
	while (c<100)
	{		
		//determine random kingdom cards
		k[0] = 22; //make sure the emabargo card is picked
		i = 1;
		while (i < 10)
		{
		    r = floor(Random() * 20);    //random kingdom card
		    j = 0;
		    while (j < i) //loop through all kingdom cards already picked
		    {
		    	if (k[j] == r + 7)      //make sure it's not a duplicate
		    	{
		        	r = floor(Random() * 20);
		        	j = 0;
		    	}
		    	else 
		    	{
		        	j++;
		    	}
		  	}
		  	k[i] = r + 7;
		  	i++;            //increment i after success
		}			
		printf("\n >>>>> Testing Card %s, iteration %d <<<<<\n\n", TESTCARD, c+1);	

		//make a new randomized game
		G = newRandomGame(k, stream);
		stream++;
		thisPlayer = G.whoseTurn;
		numPlayers = G.numPlayers;

		//pick random spot for adventurer card and put it in hand (replace existing card)
		handpos = floor(Random() * G.handCount[thisPlayer]);
		G.hand[thisPlayer][handpos] = embargo;

		//show randomized deck and discard for each player
		if (VERBOSE == 1)
		{
			i = thisPlayer;
			printf("\nc: %d, current player: %d\n", c, thisPlayer);
			//for (i = 0; i < numPlayers; i++)
			//{

				printf("deckCount player %d = %d\n", i, G.deckCount[i]);
				for (j = 0; j < G.deckCount[i]; j++)
				{
					printf("\tcard %d: %d\n", j, G.deck[i][j]);					
				}
				printf("discardCount player %d = %d\n", i, G.discardCount[i]);
				for (j = 0; j < G.discardCount[i]; j++)
				{
					printf("\tcard %d: %d\n", j, G.discard[i][j]);				
				}
				printf("handCount player %d = %d\n", i, G.handCount[i]);
				for (j = 0; j < G.handCount[i]; j++)
				{
					printf("\tcard[%d]: %d\n", j, G.hand[i][j]);			
				}
			//}
			
		}

		for (i = 0; i < 10; i++)
		{
			choice1 = k[i];

			// copy the game state to a test case
			memcpy(&testG, &G, sizeof(struct gameState));
			result = cardEffect(embargo, choice1, choice2, choice3, &testG, handpos, &bonus);
			assert(result == 0);
			if (VERBOSE == 1)
			{
				i = thisPlayer;
				printf("\nc: %d, current player: %d\n", c, thisPlayer);
				//for (i = 0; i < numPlayers; i++)
				//{

					printf("deckCount player %d = %d\n", i, G.deckCount[i]);
					for (j = 0; j < G.deckCount[i]; j++)
					{
						printf("\tcard %d: %d\n", j, G.deck[i][j]);					
					}
					printf("discardCount player %d = %d\n", i, G.discardCount[i]);
					for (j = 0; j < G.discardCount[i]; j++)
					{
						printf("\tcard %d: %d\n", j, G.discard[i][j]);				
					}
					printf("handCount player %d = %d\n", i, G.handCount[i]);
					for (j = 0; j < G.handCount[i]; j++)
					{
						printf("\tcard[%d]: %d\n", j, G.hand[i][j]);			
					}
				//}
			}		

			newCoins = 2;
			newCards = 0;
			discarded = 1;
			if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded)
			{
				printf("Problem Found!\n\thandCount = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
			}
			if (testG.deckCount[thisPlayer] != G.deckCount[thisPlayer] - newCards)
			{
				printf("Problem Found!\n\tdeckCount = %d, expected = %d\n", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
			}
			if (testG.coins != G.coins + newCoins)
			{
				printf("Problem Found!\n\tcoins = %d, expected = %d\n",testG.coins, G.coins + newCoins);
			}
			//card is trashed, so playedCardCount should not increment
			if (testG.playedCardCount != G.playedCardCount)
			{
				printf("Problem Found!\n\tplayedCardCount = %d, expected = %d\n",testG.playedCardCount, G.playedCardCount);
			}
			if (testG.embargoTokens[k[i]] != G.embargoTokens[k[i]] + 1)
			{
				printf("Problem Found!\n\tembargo tokens on k[i] = %d, expected = %d\n",testG.embargoTokens[k[i]], G.embargoTokens[k[i]] + 1);
			}
		
			//restore changed values and compare with original game
			testG.handCount[thisPlayer] = G.handCount[thisPlayer];
			testG.deckCount[thisPlayer] = G.deckCount[thisPlayer];
			testG.embargoTokens[k[i]] = G.embargoTokens[k[i]];
			testG.coins = G.coins;
			memcpy(&testG.playedCards, &G.playedCards, sizeof(G.playedCards));
			memcpy(&testG.deck[thisPlayer], &G.deck[thisPlayer], sizeof(G.deck[thisPlayer]));
			memcpy(&testG.hand[thisPlayer], &G.hand[thisPlayer], sizeof(G.hand[thisPlayer]));
			result = memcmp(&testG, &G, sizeof(struct gameState));
			if (result != 0)
			{
				printf("Problem Found!\n\tvalid pile memcmp result = %d, expected = %d\n", result, 0);
			}
		}
		printf("\n");
		//test invalid pile
		choice1 = floor(Random() * 20);    //random kingdom card
    	j = 0;
    	while (j < 10) //loop through all kingdom cards already picked
    	{	
	    	if (k[j] == choice1 + 7)      //make sure it doesn't exist in the kingdom card piles
	    	{
	        	choice1 = floor(Random() * 20);	//if it does, pick a new one
	        	j = 0;				//and start the count over
		    }
		    else 
		    {
		    	j++;
		    }
		}
		choice1 = choice1 + 7;

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		result = cardEffect(embargo, choice1, choice2, choice3, &testG, handpos, &bonus);
		//this should fail since it's not a valid pile
		if (result != -1)
		{
			printf("Problem Found!\n\treturn value from invalid pile cardEffect = %d, expected = %d\n", result, -1);
		}

		//game should be unchanged
		result = memcmp(&testG, &G, sizeof(struct gameState));
		if (result != 0)
		{
			printf("Problem Found!\n\tinvalid pile memcmp result = %d, expected = %d\n", result, 0);
		}
		printf("\n");	

		c++;	
	} //end of testing loop
	return 0;
}


