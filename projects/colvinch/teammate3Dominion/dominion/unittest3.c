//Author: colvinch
//Filename: unittest3.c
//Function: numHands()
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int main()
{
	struct gameState game;
	int i;
	int j;
	int m = 0;
	int testSwitch = 0;

	game.numPlayers = 4;

	for(i = 0; i < 4 ; i ++){ //iterate one time for each player
		game.whoseTurn = i;
		for (j = 0; j < MAX_HAND; j++){
			game.handCount[i] = j;

			if (numHandCards(&game) != j){
				printf("Card %d for player %d has failed. \n", j, i+1);
				testSwitch = 1;
				m++;
			}

		}
	}

	if (testSwitch == 0)
		printf("unittest 3 [numHandCards()] shows no errors.\n");
    else
        printf("unittest 3 [numHandCards()] shows %d errors.\n", m);
	return 0;
}
