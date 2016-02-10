//Description: This program is the Smithy card test.
//Smithy Effect: The user draws three cards from their own deck. Smithy is removed from the players hand and moved to the "played" pile. At the end of the turn, smithy is moved from the "played" pile to the discard pile.
//Business Specifications:
//Player's Hand - (1): Players hand gains three new cards. (2): Smithy is appropiately moved to "played" pile from players hand. (3): Hand Count is incremented by two.
//Player's Deck - (1): Three drawn cards are accessed from the top of the deck. (2): Deck count is decremented by 3. (3) No other changes to deck are made.
//Player's Played Pile - (1): Smithy is added to played pile, considered unplayable after playing. (2): Played Pile count incremented by 1.
//Player's Discard Deck -  (1): No card is discarded after playing Smithy. Should be moved to "played" pile.
//Other Players - (1): Nothing is changed
//Other Piles - (1): Nothing is changed
//NOTE: 


#include "dominion_helpers.h"
#include "dominion.h"
#include "rngs.h"
#include "interface.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>



//#define DECKCOUNT0 0
//#define DECKCOUNT1 0

#define DRAWCOUNT0 1
#define DRAWCOUNT1 0

#define DISCARDCOUNT0 1
#define DISCARDCOUNT1 0

#define TESTCARDVAL 14

#define PLAYEDCARDTEST 0
//Global Supply Value changes. 
#define COPPERCHANGE 0
#define SILVERCHANGE 0
#define GOLDCHANGE 0
#define ESTATECHANGE 0
#define DUCHYCHANGE 0
#define PROVINCECHANGE 0
#define CURSECHANGE 0 

#define TESTACTION 1
#define TESTBUYS 0
#define TESTCOINS 0

#define CHOICE1 0
#define CHOICE2 0
#define CHOICE3 0

void displaySupply(struct gameState *preTest)
{
	printf("\n\n\tVictory Point Data\n");
	printf("Estate Count: %d \t", preTest->supplyCount[estate]);
	printf("Duchy Count: %d \t", preTest->supplyCount[duchy]);
	printf("Province Count: %d \t", preTest->supplyCount[province]);
	printf("Curse Count: %d",preTest->supplyCount[curse]);
	printf("\n\n\tTreasure Data\n");
	printf("Copper Count: %d \t", preTest->supplyCount[copper]);
	printf("Silver Count: %d \t", preTest->supplyCount[silver]);
	printf("Gold Count: %d \t", preTest->supplyCount[gold]);

}

int *_getDeck(struct gameState *g, int player)
{	
	int deckIndex;
	int deckCount = g->deckCount[player];
	if(deckCount == 0) return 0;
	int *deck = malloc(sizeof(int*)*deckCount);
	for(deckIndex = 0; deckIndex < deckCount; deckIndex++)
	{
		deck[deckIndex] = g->deck[player][deckIndex];
	}
	return deck; 
}

int *_getHand(struct gameState *g, int player)
{
	int handIndex;
	int handCount = g->handCount[player];
	if(handCount == 0) return 0;
	int *hand = malloc(sizeof(int*)*handCount);
	for(handIndex = 0; handIndex < handCount; handIndex++)
	{
		hand[handIndex] = g->hand[player][handIndex];
	}
	return hand; 
}

int *_getPlayed(struct gameState *g, int player)
{
	int playedIndex;
	int playedCount = g->playedCardCount;
	if(playedCount == 0) return 0;
	int *played = malloc(sizeof(int*)*playedCount);
	for(playedIndex = 0; playedIndex < playedCount; playedIndex++)
	{
		played[playedIndex] = g->playedCards[playedIndex];
	}
	return played; 
}

int *_getDiscard(struct gameState *g, int player)
{
	int discardIndex;
	int discardCount = g->discardCount[player];
	if(discardCount == 0) return 0;
	int *discard = malloc(sizeof(int*)*discardCount);
	for(discardIndex = 0; discardIndex < discardCount; discardIndex++)
	{
		discard[discardIndex] = g->discard[player][discardIndex];
	}
	return discard; 
}

int *_getSupp(struct gameState *g)
{
	int es = g->supplyCount[1];
	int du = g->supplyCount[2];
	int pr = g->supplyCount[province];
	int cu = g->supplyCount[curse];
	int co = g->supplyCount[copper];
	int si = g->supplyCount[silver];
	int go = g->supplyCount[gold];
	int *supply = malloc(sizeof(int*)*7);
	int hold[7] = {cu,es, du, pr, co, si, go};
	memcpy(supply,(int*)hold,sizeof(int)*7);
	return supply;
}

int *_getUtility(struct gameState *g)
{
	int a = g->numActions;
	int c = g->coins;
	int b = g->numBuys;
	int *utility = malloc(sizeof(int*)*3);
	int hold[3] = {a,b,c};
	memcpy(utility,(int*)hold,sizeof(int)*3);
	return utility;
}

void displayPlayers(struct gameState *g, int player)
{
	int playerIndex;
	printf("\n\n\tPlayer Data\n");	
	for(playerIndex = 0; playerIndex <= 1; playerIndex++)
	{
		printf("Player %d: \tDeck Count: %d \t\tHand Count: %d \t\tDiscard Count %d\n\n",playerIndex,g->deckCount[playerIndex],g->handCount[playerIndex],g->discardCount[player]);
	}
}

void insertCard(struct gameState *g,int player)
{
	int handCount = g->handCount[player];
	g->hand[player][handCount] = TESTCARDVAL;
	g->handCount[player]+=1;
}

void display(struct gameState *g,int player)
{
	printSupply(g);
	displayPlayers(g,player);
	printDeck(player,g);
	printHand(player,g);
	printDiscard(player,g);
	printDeck(player+1,g);
	printHand(player+1,g);
	printDiscard(player+1,g);
}

void testDraw(struct gameState *preTest,struct gameState *postTest,int player)
{
	printf("\n\tTesting Draw Specifications\n");
	int i,c;
	int countTest[2] = {DRAWCOUNT0,DRAWCOUNT1};
	int flag = 0;
	for(c = 0; c <= 1; c++)
	{
		int *deck = _getDeck(preTest,player+c);
		int *hand = _getHand(postTest,player+c);
		int diffDeck = preTest->deckCount[player+c] - postTest->deckCount[player+c]; //check if # of cards drawn were correct
		if(diffDeck!=countTest[c])
		{
			printf("Error in deck count for player %d! Player deck count = %d instead of %d\n",player,diffDeck,countTest[c]);
			flag  = 1;
		}
		for(i=0;i<countTest[c];i++)
		{
			int offSet = countTest[c]-i;
			if( (deck[preTest->deckCount[player+c]-offSet]) != (hand[postTest->handCount[player+c]-offSet-1]))
			{
				printf("Error, mistmached card drawn for player %d! Did not come from top of deck\n", player+c);
				flag = 1;
			}
		}
		free(deck);
		free(hand);
	}
	if(flag == 0)
	{
		printf("Draw Test passed.\n");
	}
	else
	{
		printf("Draw Test failed.\n");
	}
}

void testHand(struct gameState *preTest, struct gameState *postTest, int player)
{
	int c,i;
	int flag = 0;
	int offSet[2] = {DRAWCOUNT0,DRAWCOUNT1};
	printf("\n\tTesting Hand Specifications\n");
	for(c = 0; c <= 1; c++) //player index
	{
		int *preHand = _getHand(preTest,player+c);
		int *postHand = _getHand(postTest,player+c);
		for(i = 0; i <= preTest->handCount[player+c] - offSet[player+c]-1; i++)
		{
			if(preHand[i] != postHand[i])
			{
				char name[50];
				char name2[50];
				cardNumToName(preHand[i],name);
				cardNumToName(postHand[i],name2);
				printf("Error, hand for player %d altered incorrectly. Card at position %d is %s. Should be %s\n",player+c,i,name2,name);
				flag = 1;
			}
		}
		free(preHand);
		free(postHand);
	}
	if(flag == 1)
	{
		printf("Hand Test failed\n");
	}
	else
	{
		printf("Hand Test passed\n");
	}
}

void testDiscard(struct gameState *preTest,struct gameState *postTest, int player)
{
	printf("\n\tTesting Discard Specifications\n");
	int c,i;
	int countTest[2] = {DISCARDCOUNT0,DISCARDCOUNT1};
	int flag = 0;
	for(c = 0; c <= 1; c++)
	{
		if(postTest->discardCount[c] != preTest->discardCount[c])
		{
			printf("Discard Test error. Player %d has %d cards in discard pile. Should have %d.\n",c,postTest->discardCount[c],preTest->discardCount[c]);
		}
	//	for(i = 0; i <= 
	}
	if(flag == 1)
	{
		printf("Discard Test failed.\n");
	}
	else
	{
		printf("Discard Test passed.\n");
	}
}

void testSupply(struct gameState *preTest,struct gameState *postTest)
{
	int i;
	char name[50];
	int flag = 0;
	int *supplyPre = _getSupp(preTest);
	int *supplyPost = _getSupp(postTest);
	int supplyCheck[7] = {CURSECHANGE,ESTATECHANGE,DUCHYCHANGE,PROVINCECHANGE,COPPERCHANGE,SILVERCHANGE,GOLDCHANGE};
	printf("\n\tTesting Supply Specifications\n");
	for(i = 0; i <= 6; i++)
	{
		if( (supplyPre[i]-supplyPost[i]) != supplyCheck[i])
		{
			cardNumToName(i,name);
			printf("Supply card: %s incorrectly altered to %d. Should be %d\n",name,supplyPost[i],supplyPost[i]+supplyCheck[i]);
			flag = 1;
		}
	}
	if(flag == 1)
	{
		printf("Supply Test failed.\n");
	}
	else
	{
		printf("Supply Test passed.\n");
	}
	free(supplyPre);
	free(supplyPost);
}
void testPlayed(struct gameState *preTest,struct gameState *postTest)
{
	int i;
	int card,card2;
	int diff = postTest->playedCardCount - (preTest -> playedCardCount + 1);
	char name[50];
	char name2[50];
	int flag = 0;
	printf("\n\tTesting Played Specifications\n");
	if(diff != PLAYEDCARDTEST)
	{
		printf("PlayedCardCount incorrect. Off by %d\n",diff-PLAYEDCARDTEST); //NEGATIVE VALUE INDICATES TOO FEW CARDS MOVED TO PLAYED PILE
		flag = 1;
	}
	
	if(postTest->playedCards[0] != TESTCARDVAL)
	{
		printf("Wrong card found in played pile.\n");
		flag = 1;
	}
	for(i = 0; i <= preTest->playedCardCount -1; i++) 
	{
		if(preTest->playedCards[i] != postTest->playedCards[i])
		{
			flag = 1;
			card = preTest->playedCards[i];
			card2 = postTest->playedCards[i];
			cardNumToName(card,name);
			cardNumToName(card2,name2);
			printf("Error in playedCards pile. Card found is %s, should be %s.\n",name,name2);
		}						
	}
	if(flag == 1)
	{
		printf("Played Test failed\n");
	}
	else
	{
		printf("Played Test passed.\n");
	} 		
}

void testUtility(struct gameState *preTest, struct gameState *postTest)
{
	int *preUtility = _getUtility(preTest);
	int *postUtility = _getUtility(postTest);
	int i;
	int flag = 0;
	int diff[3] = {TESTACTION,TESTBUYS,TESTCOINS};
	char *utility;
	printf("\n\tTesting Utility\n");
	for(i = 0; i < 3; i++)
	{
		if( (postUtility[i] - preUtility[i]) != diff[i])
		{
			switch(i)
			{
				case(1):
				utility = "Action";
				case(2):
				utility = "Buy";
				case(3):
				utility = "Coins";
			}
			printf("Error in utility skill (%s) detected\n",utility);
			flag = 1;
		}
	}
	if(flag == 1)
	{
		printf("Utility Test failed\n");
	}
	else
	{
		printf("Utility Test passed\n");
	}
	free(preUtility);
	free(postUtility);
}
int main()
{
	int i;
	int seed = 1000;
	int numPlayers = 2;
	int player  = 0;
	int *deckZero,*deckOne;
	struct gameState preTest, postTest;
	int k[10] = {adventurer, council_room, feast, gardens, mine ,remodel, smithy, village, baron, great_hall};
	/* Test Specification Variables */
	int drawCountTestZero = 3;
	int drawCountTestOne = 0;

	initializeGame(numPlayers,k,seed,&postTest);
	printf("\n\nBeginning Test for Village...\n\n");
	memcpy(&preTest,&postTest,sizeof(struct gameState));
	insertCard(&postTest,player);
	playCard((postTest.handCount[player]-1),0,0,0,&postTest);
	testDraw(&preTest,&postTest,player);
	testHand(&preTest,&postTest,player);
	testDiscard(&preTest,&postTest,player);
	testSupply(&preTest,&postTest);
	testPlayed(&preTest,&postTest);
	testUtility(&preTest,&postTest);
	printf("\n\tTesting finished\n\n");
}
