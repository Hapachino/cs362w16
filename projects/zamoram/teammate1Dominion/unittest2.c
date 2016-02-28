/* -----------------------------------------------------------------------
	* Testing shuffle()
	* This function shuffles cards in players deck
	* -----------------------------------------------------------------------
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int checkShuffle(int player, struct gameState *post)
{
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	
	int result = shuffle(player, post);
	
	if(result != 0)
	{
		printf("ERROR: shuffle function failed.\n\n");
	}
	//checking that deck is now different and no card has been lost
	else if(pre.deckCount[player] != post->deckCount[player])
	{
		printf("ERROR: Deck counts do not match.\n\n");
	}
	
	else if(memcmp(&pre.deck[player], post->deck[player], sizeof(int) * pre.deckCount[player]) == 0)
	{
		printf("ERROR: Deck was not shuffled.\n");
	}
	//assert(memcmp(&pre.deck[player], post->deck[player], sizeof(int) * pre.deckCount[player]) != 0);
	
	return 0;
}

int main()
{
	struct gameState G; 
	//cards in player decks
	int numPlayers; //players
	int p; //current player
	int i, j;
	int count; //deck count
	
	int k[10] = {adventurer, council_room, feast, gardens, mine
		   , remodel, smithy, village, baron, great_hall};
	
	SelectStream(2);
	PutSeed(3);
	printf("Testing shuffle() unittest2.\n");
	
	 for(numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) //tests up to max # of players
	 {
		for(p = 0;  p < numPlayers; p++) //test for each player currently playing
		{
			//test different deck amounts
			//not testing < 4 since its more likely that shuffled decks won't change
			for(count = 4; count < 50; count++) 
			{
				for (i = 0; i < sizeof(struct gameState); i++) { //from the lessons, random gameState
					((char*)&G)[i] = floor(Random() * 256);
				}
				
				//fill in some real cards
				for(j = 0; j < count; j++)
				{
					int card = floor(Random() * 10);
					G.deck[p][j] = k[card];
				}
				//set other necessary state settings
				G.numPlayers = numPlayers;
				G.deckCount[p] = count;
				
				checkShuffle(p, &G);
			}
		}
	 }
	 printf ("SHUFFLE TESTS FINISHED\n\n");
	
	return 0;
}