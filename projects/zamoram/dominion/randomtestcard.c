/* -----------------------------------------------------------------------
	* Author: Marco Zamora
	* CS 362
	* Random Testing for smithy card
	* -----------------------------------------------------------------------
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

#define LOUDER_TEST 1 //0 for on, 1 for off

void fillDecks(struct gameState *G);
void fillHands(struct gameState *G);
void testSmithy(struct gameState *G, int handPos);
void compareStates(struct gameState *pre, struct gameState *post);
void checkPlayerDetails(struct gameState *pre, struct gameState *post);

int main()
{
	//set up variables used for testing
	int numPlayers,
		player,
		handPos,
		i;
	struct gameState pre, post;
	int numTests = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall};
		
	int seed;
	
	//loop for amount of tests
	for(i = 0; i < numTests; i++)
	{
		printf("****TEST %i****\n", i+1);
		//randomize each of our test variables
		numPlayers = floor(Random() * (MAX_PLAYERS-2)) + 2; //at least 2 players
		player = floor(Random() * numPlayers);
		printf("Player playing adventurer: #%i\n", player);
		//initialize game
		memset(&post, 23, sizeof(struct gameState)); 
		seed = floor(Random() * MAX_DECK);
		int init = initializeGame(numPlayers, k, seed, &post);
		if(init != 0)
		{
			printf("Error initializing game.\n");
			return -1;
		}
		//random player test
		post.whoseTurn = player;
		
		//fill out player decks
		fillDecks(&post);
		
		//fill out player hands
		fillHands(&post);
		
		//sneak an smithy into a random handPos so we can play it
		handPos = floor(Random() * post.handCount[player]);
		post.hand[player][handPos] = smithy;
		
		//copy game
		// memset(&pre, 23, sizeof(struct gameState)); 
		memcpy(&pre, &post, sizeof(struct gameState));
		// printf("The hand count for player %i is %i\n", player, post.handCount[player]);
		// printf("The deck count for player %i is %i\n", player, post.deckCount[player]);
		
		//play smithy
		int playcardState = playCard(handPos, 0,0,0, &post);
		if(playcardState != 0)
		{
			printf("There was an error playing the card\n");
		}
		
		//imitate playing smithy
		testSmithy(&pre, handPos);
		
		//compare the game states
		compareStates(&pre, &post);
		
		printf("****FINISHED TEST %i****\n\n", i);
	}
	
	return 0;
}

//fills in random cards for all player decks
void fillDecks(struct gameState *G)
{
	int numPlayers = G->numPlayers;
	int deckCount, i, j;
	for(i = 0; i < numPlayers; i++)
	{
		deckCount = floor(Random() * MAX_DECK);
		G->deckCount[i] = deckCount;
		for(j = 0; j < deckCount; j++)
		{
			G->deck[i][j] = floor(Random() * (treasure_map+1));
		}
	}
}

//fills in random cards for all player hands
//depending on deck count; total count cannot exceed 500
void fillHands(struct gameState *G)
{
	int numPlayers = G->numPlayers;
	int max, handCount, i, j;
	for(i = 0; i < numPlayers; i++)
	{
		max = MAX_DECK - G->deckCount[i];
		handCount = floor(Random() * max);
		G->handCount[i] = handCount;
		for(j = 0; j < handCount; j++)
		{
			G->hand[i][j] = floor(Random() * (treasure_map+1));
		}
	}
}

//set the changes for playing an adventurer card manually
void testSmithy(struct gameState *G, int handPos)
{
	int i;
	int player = G->whoseTurn;

	
	//use up an action
	G->numActions--;
	
	//draw 3 Cards
	for (i = 0; i < 3; i++)
	{
		drawCard(player, G);
	}
	
	//discard card
	discardCard(handPos, player, G, 0);
	
	//update coins
	G->coins = 0;
	for (i = 0; i < G->handCount[player]; i++)
	{
		 if (G->hand[player][i] == copper)
		{
			G->coins += 1;
		}
		else if (G->hand[player][i] == silver)
		{
			G->coins += 2;
		}
		 else if (G->hand[player][i] == gold)
		{
			G->coins += 3;
		}
	}
}

//compare the two structs
void compareStates(struct gameState *pre, struct gameState *post)
{
	int i, j;
	// int preP= pre->whoseTurn;
	// int postP = post->whoseTurn;
	//did players change?
	if(pre->numPlayers != post->numPlayers)
		printf("ERROR w/ numPlayers: Expected: %i, Actual: %i\n", pre->numPlayers, post->numPlayers);
	else if (LOUDER_TEST == 0)
		printf("OK: number of players\n");
	
	//check supply counts; nothing was bought so nothing should have changed anyway
	for(i = 0; i < treasure_map+1; i++)
	{
		if(pre->supplyCount[i] != post->supplyCount[i])
			printf("ERROR: Supply count for card #%i does not match:  Expected: %i, Actual: %i\n", i, pre->supplyCount[i] , post->supplyCount[i]);
		else if (LOUDER_TEST == 0)
			printf("OK: Supply count for card #%i\n", i);
	}
	//same player should still be playing
	if( pre->whoseTurn != post->whoseTurn)
		printf("ERROR: WhoseTurn has changed: Expected: %i, Actual: %i\n", pre->whoseTurn , post->whoseTurn);
	else if (LOUDER_TEST == 0)
		printf("OK: whose turn\n");
	//check coins; this should have been changed because of drawing treasure cards
	if(pre->coins != post->coins)
		printf("ERROR: Coin counts do not match: Expected: %i, Actual: %i\n", pre->coins , post->coins);
	else if (LOUDER_TEST == 0)
		printf("OK: coin count\n");
	//check number of buysl should not have been affected
	if(pre->numBuys != post->numBuys)
		printf("ERROR: numBuys counts do not match: Expected: %i, Actual: %i\n", pre->numBuys , post->numBuys);
	else if (LOUDER_TEST == 0)
		printf("OK: number of buys\n");
	//number of actions should have been reduced
	if(pre->numActions != post->numActions)
		printf("ERROR: numActions counts do not match: Expected: %i, Actual: %i\n", pre->numActions , post->numActions);
	else if (LOUDER_TEST == 0)
		printf("OK: number of actions\n");
	
	// //check hand count
	// if(pre->handCount[preP] != post->handCount[postP])
		// printf("ERROR: hand counts:  Expected: %i, Actual: %i\n", pre->handCount[preP], post->handCount[postP]);
	// else if (LOUDER_TEST)
		// printf("OK: hand counts\n");
	
	// //check deck count
	// if(pre->deckCount[preP] != post->deckCount[postP])
		// printf("ERROR: deck counts:  Expected: %i, Actual: %i\n", pre->deckCount[preP], post->deckCount[postP]);
	// else if (LOUDER_TEST)
		// printf("OK: deck counts\n");
	
	// //check discard count
	// if(pre->discardCount[preP] != post->discardCount[postP])
		// printf("ERROR: discard counts:  Expected: %i, Actual: %i\n", pre->discardCount[preP], post->discardCount[postP]);
	// else if (LOUDER_TEST)
		// printf("OK: discard counts\n");
	
	//check played card count
	if(pre->playedCardCount != post->playedCardCount)
		printf("ERROR: played card counts:  Expected: %i, Actual: %i\n", pre->playedCardCount, post->playedCardCount);
	else if (LOUDER_TEST == 0)
		printf("OK: played card counts\n");
	
	//check is game over
	if( isGameOver(pre) != isGameOver(post) )
		printf("ERROR: Game over check: Expected: %i, Actual: %i\n", isGameOver(pre), isGameOver(post));
	else if (LOUDER_TEST == 0)
		printf("OK: Game over check\n");
	
	//check scores
	for(j = 0; j < pre->numPlayers; j++)
	{
		if(scoreFor(j, pre) != scoreFor(j, post))
			printf("ERROR: Score for %i: Expected: %i, Actual: %i\n", j, scoreFor(j, pre), scoreFor(j, post));
	}
	//check other players
	checkPlayerDetails(pre, post);
}

//check all player settings
void checkPlayerDetails(struct gameState *pre, struct gameState *post)
{
	int i;
	for(i = 0; i < pre->numPlayers; i++)
	{
		//check hand count
		if(pre->handCount[i] != post->handCount[i])
			printf("ERROR: hand count for player %i:  Expected: %i, Actual: %i\n", i, pre->handCount[i], post->handCount[i]);
		else if (LOUDER_TEST == 0)
			printf("OK: hand counts for player %i\n", i);
		
		//check deck count
		if(pre->deckCount[i] != post->deckCount[i])
			printf("ERROR: deck count for player %i:  Expected: %i, Actual: %i\n", i, pre->deckCount[i], post->deckCount[i]);
		else if (LOUDER_TEST == 0)
			printf("OK: deck counts for player %i\n", i);
		
		//check discard count
		if(pre->discardCount[i] != post->discardCount[i])
			printf("ERROR: discard count for  for player %i:  Expected: %i, Actual: %i\n", i, pre->discardCount[i], post->discardCount[i]);
		else if (LOUDER_TEST == 0)
			printf("OK: discard counts for player %i\n", i);
	}
}