/*********************************************************************
** Program Filename: unittest2.c
** Author: Kyle Johnson
** Date: 2/2/2016
** Description: implementation file for discardCard() testing
*********************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <math.h>

int testDiscardCard(int handPos, int currentPlayer, struct gameState *G, int trashFlag)
{
	//copy of game state
	struct gameState testG;
	memcpy(&testG, G, sizeof(struct gameState));
	
	int call;
	call = discardCard(handPos, currentPlayer, G, trashFlag);
	
	if( trashFlag < 1)
		testG.playedCardCount++;
	
	testG.handCount[currentPlayer]--;
	
	if(call != 0)
		printf("FAILED - function call failed\n");
	else
		printf("PASSED - function call did not fail\n");
	
	if(testG.playedCardCount != G->playedCardCount)
		printf("FAILED - number of played cards does not match\n");
	else
		printf("PASSED - number of played cards matches\n");
		
	if(testG.handCount[currentPlayer] != G->handCount[currentPlayer])
		printf("FAILED - player hand count does not match\n");
	else
		printf("PASSED - player hand count matches\n");
	
	return 0;
}

int main()
{
	int numPlayers = 2; 
	int p; 
	int handPos; 
	struct gameState G; 
	int trashFlag; 
	int i;
	int currentHand;
	int maxHand = 5; 
	int playedCardCount = 0;
	
	//random game state methodology sourced from lecture 11, CS362
	SelectStream(2);
	PutSeed(3);
	printf("----------------- Testing discardCard(): ----------------\n");
		//loop for number of players, hand of 1-5, and all hand positions
		for(p = 0;  p < numPlayers; p++)
		{
			for(currentHand = 1; currentHand <= maxHand; currentHand++)
			{
				for(handPos = 0; handPos < currentHand; handPos++)
				{
					//code from lecture 11 for random game state
					for (i = 0; i < sizeof(struct gameState); i++) 
						((char*)&G)[i] = floor(Random() * 256);
					
					G.numPlayers = numPlayers;
					G.playedCardCount = playedCardCount;
					G.handCount[p] = currentHand;
					trashFlag = floor(Random()*2); //trash flag can be 1 or 0, Random: http://stackoverflow.com/questions/21483667
					testDiscardCard(handPos, p, &G, trashFlag);
				}
			}
		}
	 
	 
	 printf ("discardCard() testing completed\n");
	 
	 return 0;
}