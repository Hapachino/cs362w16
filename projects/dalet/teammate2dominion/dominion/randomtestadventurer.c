#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void checkState(struct gameState pre, struct gameState post, int currentPlayer){
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
	//assert(pre.handCount[currentPlayer] + 1 == post.handCount[currentPlayer]);    //should draw 2 cards but lose adventurer for a net gain of 1
	

	/*if (pre.handCount[currentPlayer] + 1 != post.handCount[currentPlayer])
	{
		printf("hand count inccorect TEST FAILED\n");
	}
	//assert(pre.deckCount[currentPlayer] - post.discardCount[currentPlayer]  - 2 == post.deckCount[currentPlayer]);    //should remove cards from the deck equal to discard  2 (2 go into hand)
	if (pre.deckCount[currentPlayer] - post.discardCount[currentPlayer] - 2 != post.deckCount[currentPlayer])
	{
		printf("deck count incorrect TEST FAILED\n");
	}
	//assert(post.discardCount[currentPlayer] == (pre.deckCount[currentPlayer] - post.deckCount[currentPlayer] - 2));    //checks discard based on same princable as deck count
	if (post.discardCount[currentPlayer] != (pre.deckCount[currentPlayer] - post.deckCount[currentPlayer] - 2))
	{
		printf("discard count incorrect TEST FAILED\n");
	}*/


	//assert(pre.playedCardCount + 1 == post.playedCardCount); //should have played 1 card
	if (pre.playedCardCount + 1 != post.playedCardCount)
	{
		printf("Played card Count incorrect TEST FAILED\n");
	}
	//assert(pre.playedCards[pre.playedCardCount - 1] == post.playedCards[pre.playedCardCount - 1]);         //checks the card before the last card is the same to see only 1 card being played
	if (pre.playedCards[pre.playedCardCount - 1] != post.playedCards[pre.playedCardCount - 1])
	{
		printf("Last card played in pre is not second last card in post TEST FAILED\n");
	}
	//assert(post.playedCards[post.playedCardCount - 1] == adventurer);									   //checks if the last card played is a adventurer
	if (post.playedCards[post.playedCardCount - 1] != adventurer)
	{
		printf("Last card played is not correct TEST FAILED\n");
	}
}


int main() {

	int i, n, p, j, m, randCard, r, q;

	bool willShuffle;
	bool find2;

	int k[10];
	struct gameState G;
	struct gameState pre;
	int seed = 1000;

	srand(time(NULL));
	SelectStream(2);
	PutSeed(3);

	int preTreasureCount, preCopperCount, preSilverCount, preGoldCount;
	int postTreasureCount, postCopperCount, postSilverCount, postGoldCount;

	printf("Running random test for adventurer()\n");

	//create random kingdom cards
	int counter = 0;
	bool use;
	while (counter < 10) 
	{
		use = true;
		q = rand() % 20 + 7; //picks a random card from the kingdom cards
		//check to see if already used
		for (i = 0; i < counter; i++)
		{
			//if already used set that we will use to false
			if (k[i] == q)
			{
				use = false;
			}
		}
		if (use)
		{
			//if we are using set k card to q and incremenet counter
			k[counter] = q;
			counter++;
		}
	}

	//make sure test card is in the kingdom pile
	bool hasTest;
	hasTest = false;
	for (i = 0; i < 10; i++)
	{
		if ( k[i] == adventurer )
		{
			hasTest = true;
		}
	}
	if (!hasTest)
	{
		q = rand() % 10;
		k[q] = adventurer;
	}

	
	//set up a card array to use for random card gen
	//will have the 10 picked cards + static cards
	int cards[17];
	//0 - 6 are cards 0-6 in CARD enum
	for (i = 0; i < 7; i++)
	{
		cards[i] = i;
	}
	//remaining 10 cards are the kingdom cards
	j = 0;
	for (i = 7; i < 17; i++)
	{
		cards[i] = k[j];
		j++;
	}
	
	for (n = 0; n < 100; n++) {

		p = rand() % 3 + 2;  //random player amount
		memset(&G, 23, sizeof(struct gameState));				// clear the game state
		r = initializeGame(p, k, seed, &G);	         			// initialize a new game

		//set up each players hands decks discards and playerd cards
		for (j = 0; j < G.numPlayers; j++)
		{
			G.handCount[j] = rand() % 6 + 1;					//create a hand with up to 1-5 cards
			for (m = 0; m < G.handCount[j]; m++)
			{
				randCard = rand() % 17;
				G.hand[j][m] = cards[randCard];
			}
			G.deckCount[j] = rand() % 11;	     			//creates a random deck of up to 0 - 10 cards
			for (m = 0; m < G.deckCount[j]; m++)
			{
				randCard = rand() % 17;
				G.deck[j][m] = randCard;
			}
			G.discardCount[j] = rand() % 11;				//creates random discard pile of 0 - 10 cards
			for (m = 0; m < G.discardCount[j]; m++)
			{
				randCard = rand() % 17;
				G.discard[j][m] = randCard;
			}
		}

		G.playedCardCount = 0;                		     // playedCardCount set to 0

		//pick random player to play adventurer
		G.whoseTurn = rand() % G.numPlayers;

		//make sure that player has adventurer in hand track its handPos
		int handPos;
		hasTest = false;
		for (j = 0; j < G.handCount[G.whoseTurn]; j++)
		{
			if (G.hand[G.whoseTurn][j] == adventurer)
			{
				hasTest = true;
				handPos = j;
			}
		}
		if (!hasTest)
		{
			q = rand() % G.handCount[G.whoseTurn];
			G.hand[G.whoseTurn][q] = adventurer;
			handPos = q;			
		}
				

		memcpy(&pre, &G, sizeof(struct gameState));				// save a copy of current gamestate

		//check hand for treasure cards
		preTreasureCount = 0;
		preCopperCount = 0;
		preSilverCount = 0;
		preGoldCount = 0;
		for (i = 0; i < G.handCount[G.whoseTurn]; i++)
		{
			if (G.hand[G.whoseTurn][i] == copper)
			{
				preCopperCount++;
				preTreasureCount++;
			}
			else if (G.hand[G.whoseTurn][i] == silver)
			{
				preSilverCount++;
				preTreasureCount++;
			}
			else if (G.hand[G.whoseTurn][i] == gold)
			{
				preGoldCount++;
				preTreasureCount++;
			}
		}

		//track how many treasure cards are in the deck and discard piles
		int preDeckCoin = 0;
		int preDiscardCoin = 0;
		for (i = 0; i < G.deckCount[G.whoseTurn]; i++)
		{
			if (G.deck[G.whoseTurn][i] == copper)
			{
				preDeckCoin++;
			}
			else if (G.deck[G.whoseTurn][i] == silver)
			{
				preDeckCoin++;
			}
			else if (G.deck[G.whoseTurn][i] == gold)
			{
				preDeckCoin++;
			}
		}

		for (i = 0; i < G.discardCount[G.whoseTurn]; i++)
		{
			if (G.discard[G.whoseTurn][i] == copper)
			{
				preDiscardCoin++;
			}
			else if (G.discard[G.whoseTurn][i] == silver)
			{
				preDiscardCoin++;
			}
			else if (G.discard[G.whoseTurn][i] == gold)
			{
				preDiscardCoin++;
			}
		}
		//tracks if shuffle will happen because not 2 coins in the deck
		willShuffle = false;
		if (preDeckCoin < 2)
		{
			willShuffle = true;
		}

		//tracks if adventurer will find 2 coins
		find2 = false;
		if ((preDeckCoin + preDiscardCoin) >= 2)
		{
			find2 = true;
		}

		
		printf("\nPlaying Adventurer Card as Player %d Iteration %d Current Counts: Hand %d , Deck %d , Discard %d , Played %d , Treasures in Hand %d: Copper %d, Silver %d, Gold %d. Shuffle: %d  find2: %d preDeckCoin : %d, preDiscardCoin : %d\n", G.whoseTurn, n + 1, G.handCount[G.whoseTurn], G.deckCount[G.whoseTurn], G.discardCount[G.whoseTurn], G.playedCardCount, preTreasureCount, preCopperCount, preSilverCount, preGoldCount, willShuffle, find2, preDeckCoin, preDiscardCoin);
		
		//play TEST CARD
		playAdventurer(&G);
		
		//check for treasure post adventurer
		//check hand for treasure cards
		postTreasureCount = 0;
		postCopperCount = 0;
		postSilverCount = 0;
		postGoldCount = 0;
		for (i = 0; i < G.handCount[G.whoseTurn]; i++)
		{
			if (G.hand[G.whoseTurn][i] == copper)
			{
				postCopperCount++;
				postTreasureCount++;
			}
			else if (G.hand[G.whoseTurn][i] == silver)
			{
				postSilverCount++;
				postTreasureCount++;
			}
			else if (G.hand[G.whoseTurn][i] == gold)
			{
				postGoldCount++;
				postTreasureCount++;
			}
		}

		printf("Played Adventurer Card as Player %d Iteration %d Current Counts: Hand %d , Deck %d , Discard %d , Played %d , Treasures in Hand %d: Copper %d, Silver %d, Gold %d\n", G.whoseTurn, n + 1, G.handCount[G.whoseTurn], G.deckCount[G.whoseTurn], G.discardCount[G.whoseTurn], G.playedCardCount, postTreasureCount, postCopperCount, postSilverCount, postGoldCount);

		//assert(preTreasureCount + 2 == postTreasureCount);				//checks that 2 treasures were added to hand
		
		if (find2)
		{
			if (preTreasureCount + 2 != postTreasureCount)
			{
				printf("Tresure count changed by an amount different than 2 when at least 2 treasure were present TEST FAILED\n");
			}
		}

		if (!find2) 
		{
			//means there should have only been 0-1 inside deck and disard adding whatever those counts are to pretreasure should = post
			if ((preTreasureCount + preDeckCoin + preDiscardCoin) != postTreasureCount)
			{
				printf("PreTreasur: %d, preDeck : %d, preDiscard : %d\n", preTreasureCount, preDeckCoin, preDiscardCoin);
				printf("Treasure Count did not change correctly based on cards when 0-1 treasure present in desk/discard TEST FAILED\n");
			}
		}

		checkState(pre, G, G.whoseTurn);										// check new gamestate vs old using modified checkState
	}

	printf("Finished running random test for play_adventurer()\n");
	return 0;
}