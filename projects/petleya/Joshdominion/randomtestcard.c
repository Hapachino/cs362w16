#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//testing smith function

int main(){
	int player=0;
	int other=0;
	struct gameState G;
	srand(time(0));
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
//initialize the Game for four players
	initializeGame(2, k, 73, &G);
	int i;
	int hcbefore;
	int obefore;
	int odis;
	int odeck;
	int j;
	for(j=0; j<10; j++){
//hand count before function call
		hcbefore = G.handCount[player];
		obefore = G.handCount[other];
		odis = G.discardCount[other];
		odeck = G.discardCount[other];
//adds cards to deck and discard to simulate random times of the game 
		G.deckCount[player] = rand()%20;
		G.discardCount[player] = 20 - G.deckCount[player];
	for(i=0; i<G.deckCount[player]; i++){
		G.deck[player][i] = rand() % 27;
	}
	for(i=0; i<G.discardCount[player]; i++){
		G.discard[player][i] = rand() % 27;
	}
	printf("deck count before is: %d\n", G.deckCount[player]);
	printf("dicard count before is %d\n", G.discardCount[player]);
	playSmithy(0, &G);
	if(G.handCount[player] != hcbefore + 2){
		printf("Fail: The players hand not increased by the correct amount\n");
		if(G.handCount[player] > hcbefore +2){
			printf("hand count too high: %d hand Count before:%d\n", G.handCount[player], hcbefore);
		}
		if(G.handCount[player] < hcbefore +2){
			printf("hand count is too low. should increase by two");
		}
	}
	else{
		printf("Pass: The correct hand count\n");
	}
	if(G.handCount[other] != obefore || G.deckCount[other] != odeck || G.discardCount[other] != odis){
		printf("Fail: The other players status have been effected\n");
		if(G.handCount[other] != obefore){
			printf("The other players hand count is %d it should be %d\n", G.handCount[other], obefore);
		}
		if(G.deckCount[other] != odeck){
			printf("The other players deck was effected it is %d and it should be %d\n", G.deckCount[other], odeck);
		}
		if(G.discardCount[other] != odis){
			printf("The other players discard pile was effect it is %d and it should be %d\n", G.discardCount[other], odis);
		}
	}
	else{
		printf("Pass: The other players status no effected\n");
	}
	}
return 0;
}
