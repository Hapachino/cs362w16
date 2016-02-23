#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//4=copper, 5=silver, 6 = gold

int main(){
	int player=1;
	struct gameState G;
	srand(time(0));
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
//initialize the Game for four players
	initializeGame(2, k, 73, &G);
	int c=0;
	int b=0;
	int i;
	int h=0;
//hand count before function call
	int hcbefore;
	int j=0;
	int n;
	for(n=0; n<10; n++){
		hcbefore = G.handCount[player];
		for(i=0; i<G.handCount[player]; i++){
			printf("in hand position %d card %d\n", i, G.hand[player][i]);
			if(G.hand[player][i] == 6 || G.hand[player][i] == 5 || G.hand[player][i] == 4){
				c++;
			}
		}
//adds cards to deck and discard to simulate random times of the game 
		G.deckCount[player] = rand()%20;
		G.discardCount[player] = 20 - G.deckCount[player];
		for(i=0; i<G.deckCount[player]; i++){
			G.deck[player][i] = rand() % 27;
//keeps track of treasure cards added to deck
			if(G.deck[player][i] == 6 || G.deck[player][i] == 5 || G.deck[player][i] == 4){
				j++;
			}
		}
		for(i=0; i<G.discardCount[player]; i++){
//if there are not at least two treasure card in the deck then some are added to discard to access when shuffled
			if(j<2){
				G.discard[player][i] = 5;
				j++;
			}
			else{
				G.discard[player][i] = rand() % 27;
			}
		}
		printf("deck count before is: %d\n", G.deckCount[player]);
		printf("dicard count before is %d\n", G.discardCount[player]);
//checks discard pile for tresures before start
		adven(&G, 1, player, 0, 5);
//checks discard pile for tresures after
		for(i=0; i<G.discardCount[player]; i++){
			if(G.discard[player][i] == 4 || G.discard[player][i] == 5 || G.discard[player][i]==6){
				b++;
				printf("Treasure card found in discard %d\n", G.discard[player][i]);
			}
				
		}
		for(i=0; i<G.deckCount[player]; i++){
			if(G.deck[player][i] == 4 || G.deck[player][i] == 5 || G.deck[player][i]==6){
				b++;
			}
				
		}
		for(i=0; i<G.handCount[player]; i++){
			if(G.hand[player][i] == 6 || G.hand[player][i] == 5 || G.hand[player][i] == 4){
				if(i>=hcbefore){
				printf("added treasure card in hand position %d treasure card %d\n", i, G.hand[player][i]);
				}
				h++;
			}

		}
		if(h-c != 2){
			printf("Fail: incorrect number of treasure cards added\n");
		}
		if(b-j > 0){
			printf("Fail: a treasure card was discarded\n");
		}
		if(G.handCount[player] - hcbefore < 2){
			printf("Fail: handcount is : %d and hcbefore is %d\n", G.handCount[player], hcbefore);
		}
		else{
			printf("Pass: The player has the minimum amount of added cards the hand count is %d\n", G.handCount[player]);			
		}
	}
	return 0;	
}
