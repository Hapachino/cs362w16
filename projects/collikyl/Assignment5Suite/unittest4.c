#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Fulldeck Count test


// To empty a pile, set card to -1 and reset to 1.
void _setHand(struct gameState *g,int player,int max, int card, int reset)
{
	int i;
	g->handCount[player] = 0;
	for(i = 0; i<= max-1; i++)
	{
		g->hand[player][i] = card;
		if(reset == 0)
		g->handCount[player]++;
	}
}

void _setDeck(struct gameState *g, int player,int max, int card, int reset)
{
	int i;
	g->deckCount[player] = 0;
	for(i = 0; i<= max-1; i++)
	{
		g->deck[player][i] = card;
		if(reset == 0)
		g->deckCount[player]++;
	}
}

void _setDiscard(struct gameState *g, int player,int max,int card, int reset)
{
	int i;
	g->discardCount[player] = 0;
	for(i = 0; i<= max-1; i++)
	{
		g->discard[player][i] = card;
		if(reset == 0)
		g->discardCount[player]++;
	}
}

void testFullDeck(struct gameState *g, int player)
{
	int handCount,deckCount,discardCount,cardCount;
	
	_setHand(g,player,15,3,0);
	_setDeck(g,player,25,4,0);
	_setDiscard(g,player,35,5,0);

	printf("\n\n\tRunning FullDeck test\n\n");
	cardCount = fullDeckCount(player,3,g); 	
	if(cardCount != 15) printf("fullDeckCount failed checking hand pile for card exclusive to hand pile.\n");
	else printf("fullDeckCount passed checking hand pile for card exclusive to hand pile.\n\n");

	cardCount = fullDeckCount(player,4,g); 	
	if(cardCount != 25) printf("fullDeckCount failed checking deck pile for card exclusive to hand pile.\n");
	else printf("fullDeckCount passed checking deck pile for card exclusive to deck pile.\n\n");

	cardCount = fullDeckCount(player,5,g); 	
	if(cardCount != 35) printf("fullDeckCount failed checking discard pile for card exclusive to discard pile.\n");	
	else printf("fullDeckCount passed checking discard pile for card exclusive to discard pile.\n\n");

	_setHand(g,player,15,3,0);
	_setDeck(g,player,25,3,0);
	_setDiscard(g,player,35,3,0);
	
	cardCount = fullDeckCount(player,3,g); 	
	if(cardCount != 75) printf("fullDeckCount failed checking all piles for card in all piles.\n");	
	else printf("fullDeckCount passed checking all piles for card in all piles.\n\n");

	_setHand(g,player,0,-1,1);
	_setDeck(g,player,0,-1,1);
	_setDiscard(g,player,0,-1,1);
	
	cardCount = fullDeckCount(player,-1,g); 	
	if(cardCount != 0) printf("fullDeckCount failed checking all piles for card with empty piles.\n");	
	else printf("fullDeckCount passed checking all piles for card with empty piles (there are 0 cards).\n\n");

	_setHand(g,player,MAX_HAND,1,0);
	_setDeck(g,player,MAX_DECK,1,0);
	_setDiscard(g,player,MAX_HAND+MAX_DECK,1,0);
	
	cardCount = fullDeckCount(player,1,g); 	
	if(cardCount != 2000) printf("fullDeckCount failed checking all piles for card in all piles with max count.\n");	
	else printf("fullDeckCount passed checking all piles for card with max count.\n\n");

	printf("\n\tEnd of fullDeck Test\n\n");

}

int main()
{
        int i;
        int seed = 1000;
        int numPlayers = 2;
        int player  = 0;
        struct gameState preState, postState;
        int k[10] = {adventurer, council_room, feast, gardens, mine ,remodel, smithy, village, baron, great_hall};
        initializeGame(numPlayers,k,seed,&postState);
        memcpy(&preState,&postState,sizeof(struct gameState));
	printf("\n\nFullDeck test\n\n");
	testFullDeck(&postState,player);
}


