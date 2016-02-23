/* -----------------------------------------------------------------------
	* Testing discardCard
	* This function discards a card from the player's hand into either a played 
	*card pile or, if it's trashed, the value is overwritten to -1
	* -----------------------------------------------------------------------
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int checkDiscardCard(int handPos, int currentPlayer, struct gameState *post, int trashFlag)
{
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	
	int result;
	
	result = discardCard(handPos, currentPlayer, post, trashFlag);
	
	//mimic discarding
	if( trashFlag < 1)
	{
		pre.playedCardCount++;
	}
	
	pre.handCount[currentPlayer]--;
	
	//assert(result == 0);
	
	if(result != 0)
	{
		printf("ERROR: discardCard function failed.\n\n");
	}
	else if(pre.playedCardCount != post->playedCardCount)
	{
		printf("ERROR: Played card counts do not match.\n\n");
	}
	//assert(pre.playedCardCount == post->playedCardCount);
	else if(pre.handCount[currentPlayer] != post->handCount[currentPlayer])
	{
		printf("ERROR: Player's hand card counts do not match.\n\n");
	}
	//assert(pre.handCount[currentPlayer] == post->handCount[currentPlayer]);
	
	return 0;
}

int main()
{
	int numPlayers; //players
	int p; //current player
	int handPos; //card position in hand
	struct gameState G; 
	int trashFlag; //trash card binary
	int i;
	
	int maxHand = 10; //hand will always have 10 cards and handPos will go 0-9
	int playedCardCount = 0;
	
	SelectStream(2);
	PutSeed(3);
	printf("Testing discardCard() unittest1.\n");
	 for(numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) //tests up to max # of players
	 {
		for(p = 0;  p < numPlayers; p++) //test for each player currently playing
		{
			for(handPos = 0; handPos < maxHand; handPos++)//test card in each hand position
			{
				for (i = 0; i < sizeof(struct gameState); i++) { //from the lessons, random gameState
					((char*)&G)[i] = floor(Random() * 256);
				}
				G.numPlayers = numPlayers;
				G.playedCardCount = playedCardCount;
				G.handCount[p] = maxHand;
				trashFlag = floor(Random()*2); //trash half the time
				
				//printf("TEST- player: %d numPlayers: %d, handPos: %d, trashFlag: %d RESULT:", p, numPlayers, handPos, trashFlag);
				
				checkDiscardCard(handPos, p, &G, trashFlag);
				//printf(" PASS \n");
			}
		}
	 }
	 
	 printf ("DISCARD CARD TESTS FINISHED\n\n");
	 
	 return 0;
}