//Author: colvinch
//Filename: unittest2.c
//Function: whoseTurn()
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int main(){

	struct gameState game;
	int i;
	int j = 0;
	int testSwitch = 0;

	for (i = 0; i < 4; i++){
		game.whoseTurn = i;
		if (whoseTurn(&game) != i){
			printf("Error: player %d turn produced an error.\n", i);
			testSwitch = 1;
			j++;
		}
	}
	if (testSwitch == 0)
		printf("unittest2 [whoseTurn()] shows no errors.\n");
    else
        printf("unittest2 [whoseTurn()] shows %d errors.\n", j);
}
