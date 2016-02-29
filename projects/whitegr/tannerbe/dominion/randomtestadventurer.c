#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define TESTCARD "adventurer"
#define VERBOSE 0

int main() {
    srand(time(NULL));
    int i, j, r, c, result, thisPlayer, newCards, discarded, stream;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int numPlayers, k[10];
	struct gameState G, testG;

	c = 0;
	stream = 0;
	while (c<100000)
	{		
		//determine random kingdom cards
		k[0] = 7; //make sure the adventurer card is picked
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
		G.hand[thisPlayer][handpos] = 7;

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

		//make a copy of our game
		memcpy(&testG, &G, sizeof(struct gameState));

		//play the card		
		result = cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
		assert(result == 0);

		if (VERBOSE == 1)
		{
			printf("\nAfter playing card:\n");
			i = thisPlayer;
			//for (i = 0; i < numPlayers; i++)
			//{
				printf("deckCount player %d = %d\n", i, testG.deckCount[i]);
				for (j = 0; j < testG.deckCount[i]; j++)
				{
					printf("\tcard %d: %d\n", j, G.deck[i][j]);					
				}
				printf("discardCount player %d = %d\n", i, testG.discardCount[i]);
				for (j = 0; j < testG.discardCount[i]; j++)
				{
					printf("\tcard %d: %d\n", j, testG.discard[i][j]);				
				}
				printf("handCount player %d = %d\n", i, testG.handCount[i]);
				for (j = 0; j < testG.handCount[i]; j++)
				{
					printf("\tcard[%d]: %d\n", j, testG.hand[i][j]);			
				}				
			//}
			
		}
		
	    newCards = 2;
	    discarded = 1;
		if (testG.handCount[thisPlayer] != G.handCount[thisPlayer] + newCards - discarded)
		{
			printf("Problem Found!\n\thandCount = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
		}
		if (testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer] != G.deckCount[thisPlayer] - newCards + G.discardCount[thisPlayer])
		{
			printf("Problem Found!\n\tdeckCount + discardCount = %d, expected = %d\n", testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer], G.deckCount[thisPlayer] + G.discardCount[thisPlayer] - newCards + discarded);
		}
		if (testG.playedCardCount != G.playedCardCount + 1)
		{
			printf("Problem Found!\n\tplayedCardCount = %d, expected = %d\n",testG.playedCardCount, G.playedCardCount + 1);
		}
		if (testG.playedCards[0] != adventurer)
		{
			printf("Problem Found!\n\tplayedCard = %d, expected = %d\n", testG.playedCards[testG.playedCardCount - 1], 7);
		}

		//check if there are two more treasures in the player's hand.
		int preCardTreasureCountDeck = 0; //this is how many treasures existed in the deck and discard prior to playing the card.
		for (i = 0; i < G.deckCount[thisPlayer]; i++)
		{
		    if (G.deck[thisPlayer][i] == copper || G.deck[thisPlayer][i] == silver || G.deck[thisPlayer][i] == gold) 
		    {
		    	preCardTreasureCountDeck++;
		    }
		}
		for (i = 0; i < G.discardCount[thisPlayer]; i++)
		{
		    if (G.discard[thisPlayer][i] == copper || G.discard[thisPlayer][i] == silver || G.discard[thisPlayer][i] == gold) 
		    {
		    	preCardTreasureCountDeck++;
		    }
		}

		int postCardTreasureCountDeck = 0; //this is how many treasures existed in the deck and discard after playing the card.
		for (i = 0; i < testG.deckCount[thisPlayer]; i++)
		{
		    if (testG.deck[thisPlayer][i] == copper || testG.deck[thisPlayer][i] == silver || testG.deck[thisPlayer][i] == gold) 
		    {
		    	postCardTreasureCountDeck++;
		    }
		}
		for (i = 0; i < testG.discardCount[thisPlayer]; i++)
		{
		    if (testG.discard[thisPlayer][i] == copper || testG.discard[thisPlayer][i] == silver || testG.discard[thisPlayer][i] == gold) 
		    {
		    	postCardTreasureCountDeck++;
		    }
		}

		int preCardTreasureCountHand = 0; //this is how many treasures existed in the hand prior to playing the card.
		for (i = 0; i < G.handCount[thisPlayer]; i++)
		{
			if (G.hand[thisPlayer][i] == copper || G.hand[thisPlayer][i] == silver || G.hand[thisPlayer][i] == gold)
			{
				preCardTreasureCountHand++;
			}
		}

		int postCardTreasureCountHand = 0; //this is how many treasures existed in the hand after playing the card.
		for (i = 0; i < testG.handCount[thisPlayer]; i++)
		{
			if (testG.hand[thisPlayer][i] == copper || testG.hand[thisPlayer][i] == silver || testG.hand[thisPlayer][i] == gold)
			{
				postCardTreasureCountHand++;
			}
		}
		if (VERBOSE == 1)
		{
			printf("\t%d\t%d\t%d\t%d\n", preCardTreasureCountDeck, postCardTreasureCountDeck, preCardTreasureCountHand, postCardTreasureCountHand);
		}

		if (preCardTreasureCountDeck < 2)
		{
			//there weren't enough treasures, which IS a possible scenario, it means the player just gets what they find
			if (postCardTreasureCountHand != preCardTreasureCountHand + preCardTreasureCountDeck)
			{
				printf("Problem Found!\n\tIncorrect number of treasures\n");
			}
			if (postCardTreasureCountDeck != 0)
			{
				printf("Problem Found!\n\tIncorrect number of treasures\n");
			}
		}
		else
		{
			if (postCardTreasureCountHand != preCardTreasureCountHand + 2)
			{
				printf("Problem Found!\n\tIncorrect number of treasures\n");
			}
			if (preCardTreasureCountDeck != postCardTreasureCountDeck + 2)
			{
				printf("Problem Found!\n\tIncorrect number of treasures\n");
			}
		}

		//restore changed values and compare with original game
		testG.handCount[thisPlayer] = G.handCount[thisPlayer];
		testG.deckCount[thisPlayer] = G.deckCount[thisPlayer];
		testG.discardCount[thisPlayer] = G.discardCount[thisPlayer];
		testG.playedCardCount = G.playedCardCount;
		memcpy(&testG.playedCards, &G.playedCards, sizeof(G.playedCards));
		memcpy(&testG.discard[thisPlayer], &G.discard[thisPlayer], sizeof(G.discard[thisPlayer]));
		memcpy(&testG.deck[thisPlayer], &G.deck[thisPlayer], sizeof(G.deck[thisPlayer]));
		memcpy(&testG.hand[thisPlayer], &G.hand[thisPlayer], sizeof(G.hand[thisPlayer]));
		result = memcmp(&testG, &G, sizeof(struct gameState));
		if (result != 0)
		{
			printf("Problem Found!\n\tmemcmp result = %d, expected = %d\n", result, 0);
		}

		c++;	
	} //end of testing loop

	return 0;
}


