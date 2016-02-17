#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "interface.h"

#define TESTCARD adventurer
#define DRAWTEST1 1 //net change in deckCount for player 0
#define DRAWTEST2 0

#define ACTIONS -1
#define BUYS 0
#define OUTPOST 0
#define COINS 0

#define VERBOSE 1

//Num players hardcoded to 2.

//Rand test for adventurer. 

//Randomly create kingdom cards array
int *randKingdom()
{
	int i,card,kingCards[26]; //i=iterator, card = random card val, kingCards = array of possible card choices
	int *k = malloc(sizeof(int)*17); //array of chosen rand cards to be returned
	memset(kingCards,0,sizeof(kingCards));
	for(i = 0; i < 10; i++) 
	{
		card = 7 + rand() % 20; //get random card value
		if(kingCards[card] == 1) //if card is already chosen
		{
			i--; //decrement i to redo trial
			continue; //return to start of for loop
		}
		else //card not previously chosen
		{
			k[i] = card; //card becomes kingdom card
			kingCards[card] = 1;
		}
		if(i<=7)
		{
			k[i+10] = i;  //create treasure and victory cards
		}
	}
	return k; //remember to free when done
}
//Randomly create a deck of random size.
void randDeck(struct gameState *g, int player, int *k)
{
	int deckSize = rand() % 20; //deckSize 0-19 (last card in hand will be the tested card)
	int i,card;
	for(i=0;i<deckSize;i++)
	{
		card = k[rand()%17];
		g->deck[player][i] = card;
		g->deckCount[player]++;
	}
}
//randomly create hand of random size
void randHand(struct gameState *g, int player, int *k)
{
	int handSize = rand() % 50; //handSize 0-49 last card in hand will be tested card
	int i,card;
	for(i=0;i<handSize;i++)
	{
		card = k[rand()%17];
		g->hand[player][i] = card;
		g->handCount[player]++;
	}
}
//randomly create discard of random size
void randDiscard(struct gameState *g, int player, int *k)
{
	int discardSize = rand() % 20; //discardSize 0-19
	int i,card;
	for(i=0;i<discardSize;i++)
	{
		card = k[rand()%17];
		g->discard[player][i] = card;
		g->discardCount[player]++;
	}
}
//Randomize kingdom/treasure/province count from 1-maxValue (maxValue = maxValue of that specific card);
void randSupply(struct gameState *g, int *k)
{
	int i;
//Province Initilization
	for(i=0;i<=3;i++)
	{
		g->supplyCount[i] = rand() % 8 + 1;
	}
//Kingdom Initilization
	for(i=0;i<10;i++)
	{
		g->supplyCount[k[i]] = rand() % 10 + 1;
	}
//Treasure Initilization
	g->supplyCount[4] = rand() % 46 + 1;
	g->supplyCount[5] = rand() % 40 + 1;
	g->supplyCount[6] = rand() % 30 + 1;
}

void randState(struct gameState *g)
{
	g->phase=0; //Must be phase 0 to play cards.
	g->numActions = rand()%10+1;
	g->numBuys = rand()%10+1;
	g->coins = rand()%10;
	g->playedCardCount = 0; //Doesn't matter, played cards go off into Nether at the end of turn anyways (already known to be bugged, no initilization done)
	g->whoseTurn = 0; //Player 0's turn (testing player)
	g->outpostPlayed = 0; //No idea what the outpost is
}
//just inserts card
void insertCard(struct gameState *g, int player)
{
	g->hand[player][g->handCount[player]] = 7;
	g->handCount[player]++;
}

int coinsCount(struct gameState *pre, struct gameState *post)
{
	int i;
	int coins = 0; //default if no treasure are added to hand
	for(i=pre->handCount[0];i<post->handCount[0]; i++)
	{
		if(post->hand[0][i] >= 4 && post -> hand[0][i] <= 6)
		{
			coins+=post->hand[0][i]-3;
		}
	}
	return coins;	
}

//Testing Supply State (count of kingdom cards, treasure cards, province cards not controlled by a player) -- Should not change for adventurer
void testSupply(struct gameState *pre, struct gameState *post)
{
	
	printf("\n****SUPPLY TEST*****\n");
	int i;
	int flag = 0;
	char name[50];
	for(i=0;i<27;i++)
	{
		if(pre->supplyCount[i] != post->supplyCount[i])
		{
			cardNumToName(i,name);		
			if(VERBOSE==1)	printf("Error, supply count changed! Card %s had count %d. After test, new count is %d.\n",name, pre->supplyCount[i], post->supplyCount[i]);
			flag = 1;
		}
	}
	if(flag == 0)
	{
		if(VERBOSE==1) printf("*****SUPPLY TEST PASSED*****\n");
	}
	else
	{
		
		if(VERBOSE==1) printf("*****SUPPLY TEST FAILED*****\n");
	}
}


//Return number of cards drawn to get deckCount and discardCount. Returns status on whether there is a shuffle. Returns treasureCount. Doesn't check if treasure card is drawn. testHand does that instead 
int getDrawnCards(struct gameState *pre, int player, int *isShuffle, int *compareTreasure)
{
	int deckCount = pre->deckCount[player];
	int discardCount = pre->discardCount[player];
	int card;
	int drawnCards = 0;
	int i;
	int treasureCount = 0;
	for(i=deckCount-1;i>=0;i--)
	{
		card = pre->deck[player][i];
		drawnCards++;
		if(card>=4&&card<=6)
		{
			treasureCount++;
			if(treasureCount>=2)
			{
				*isShuffle = 0;
				*compareTreasure = treasureCount;
				return drawnCards;	
			}
		}
	}
	if(treasureCount<2) //Shuffle must occur.
	{
		for(i=discardCount-1;i>=0;i--)
		{
			card = pre->discard[player][i];
			if(card>=4&&card<=6)
			{
				treasureCount++;
				if(treasureCount>=2)
				{
					*isShuffle = 1;
					*compareTreasure = treasureCount;
					return 0; //Signify shuffle occurs, there are 2 treasures
				}
			}
		}
	}
	if(treasureCount<2)
	{
		*isShuffle = -1;
		*compareTreasure = treasureCount;
		return -1; //Signify not enough treasures.
	}
}	

void testDeck(struct gameState *pre, struct gameState *post, int player, int cardsDrawn, int isShuffle)
{
	int i,j;
	int drawNum[2] = {cardsDrawn,0};
	int flag = 0;
	char name[50];
	char name2[50];
	//Deck Count test 

	if(VERBOSE == 1) printf("\n**********DECK TEST**************\n");
	switch(isShuffle) //Test Both players - no shuffle easy test
	{
		case(0):
			for(i=0;i<=1;i++)
			{
			if( (post->deckCount[player+i]) != pre->deckCount[player+i]-drawNum[i])
			{
				
				if(VERBOSE == 1) printf("Error. Incorrect # of cards in deck for player %d. Expecting %d. Have %d.\n", i, (pre->deckCount[player+i]-drawNum[i]),post->deckCount[player+i]);
				flag = 1;
			}
				for(j=0;j<post->deckCount[player+i]-drawNum[i];j++) //Check deck to see if cards remain unchanged. No shuffle occured so safe.
				{
					if(pre->deck[player+i][j]!=post->deck[player+i][j])
					{
						cardNumToName(pre->deck[player+i][j],name);
						cardNumToName(post->deck[player+i][j],name2);
						if(VERBOSE == 1) printf("Error in deck. Card at position %d is %s. Should be %s.\n",j,name,name2);
						flag = 1;
					}
				}
			}
		break;

		case(1): //Shuffle occured. Can't check order or deckCount.
			if(VERBOSE == 1) printf("Shuffle occured. Unable to check deckOrder/deckCount. Resuming test. Will still check treasure in deck.\n");
		break;
		case(-1): //Not enough treasures. 
			if(post->deckCount[player] != 0)
			{
				if(VERBOSE == 1) printf("Error. %d cards still in deck after finding no treasures. Should be 0.\n",post->deckCount[player]);
			}
		break;		
	}
	if(isShuffle == 1 && i == 1) //Test player 1 (idle player) if shuffle
	{
		if(pre->deckCount[player+i] != post -> deckCount[player+i])
		{
			if(VERBOSE == 1) printf("Error. Incorrect # of cards in deck for player %d. Expecting %d. Actual %d\n",i,pre->deckCount[player+i],post->deckCount[player+i]);
			flag = 1;
		}
	}
	//DeckCount Test Complete		
	if(flag==0 && VERBOSE == 1)
	{
		printf("**********DECK TEST PASSED******\n");
	}
}

void testDiscard(struct gameState *pre, struct gameState *post, int player, int drawCount, int isShuffle, int compareTreasure)
{
	int i,j=1;
	int flag = 0;
	char name[50];
	char name2[50];

	printf("\n*******DISCARD TEST*******\n");
	if(isShuffle == 0)
	{
		if( (pre->discardCount[player]) != (post->discardCount[player] + (compareTreasure-drawCount)))
		{
			flag = 1;
			if(VERBOSE == 1)
			{
				printf("Error in discard count. Expected %d. Actual %d\n", (pre->discardCount[player]-compareTreasure+drawCount),post->discardCount[player]);
			}
		}
		for(i=0;i<=pre->discardCount[player]-1;i++)
		{
			if(pre->discard[player][i] != post->discard[player][i])
			{
				flag = 1;
				if(VERBOSE == 1)
				{
					cardNumToName(pre->discard[player][i],name);
					cardNumToName(post->discard[player][i],name2);
				 	printf("Error in discard. Expected card at position %d to be %s. Actual card %s\n",i,name,name2);
				}
			}
		}
		
		for(i=pre->discardCount[player];i<post->discardCount[player];i++)
		{
			if( post -> discard[player][i] != pre -> deck[player][pre->deckCount[player] - drawCount + j])
			{
				if(pre->deck[player][pre->deckCount[player]-drawCount+j] >= 4 && pre->deck[player][pre->deckCount[player]-drawCount+j] <= 6)
				{
						j++;
						i--;
						continue;
				}
				flag = 1;
				if(VERBOSE == 1)
				{	
					cardNumToName(post->discard[player][i],name);
					cardNumToName(pre->deck[player][(pre->deckCount[player]-j)],name2);	
				 	printf("Error in discard. Expected card at position %d to be %s. Actual card %s\n",i,name2,name);
				}
			}
			j++;
		}		
	}
	else if(isShuffle == 1)
	{
		for(i=0;i<post->discardCount[player];i++)
		{
			if(post->discard[player][i] >= 4 && post->discard[player][i] <= 6)
			{
				flag = 1;
				if(VERBOSE == 1) printf("Error in discard. Detected treasure after shuffle at position %d. No treasures should be in discard after shuffle\n",i);
			}
		}
	}
	else if(isShuffle == -1 && compareTreasure == 0)
	{
		if(post->discardCount[player] != (pre->deckCount[player]+pre->discardCount[player]))
		{
			if(VERBOSE == 1) printf("Discard Count off when no treasures found. Expected count %d. Actual count %d.\n",(pre->deckCount[player]+pre->discardCount[player]),post->discardCount[player]);
		}
	}	
	if(flag == 0)
	{
		if(VERBOSE == 1) printf("*******DISCARD TEST PASSED*******\n");
	}
	else
	{
		if(VERBOSE == 1) printf("******DISCARD TEST FAILED********\n");
	}
}	

void testState(struct gameState *pre, struct gameState *post)
{
	int flag = 0;
	int coins = coinsCount(pre,post);
	//Get coins val
	
	printf("\n*****STATE TEST*****\n");
	if( (pre->numBuys+BUYS) != post->numBuys)
	{	
		if(VERBOSE == 1) printf("Buys state failed. Expected Val %d Actual Val %d\n",pre->numBuys,post->numBuys);
		flag =  1;
	}
	if( (pre->numActions+ACTIONS) != post->numActions)
	{	
		if(VERBOSE == 1) printf("Actions state failed. Expected Val %d Actual Val %d\n",(pre->numActions)+ACTIONS,post->numActions);
		flag =  1;
	}
	if(pre->phase != post->phase)
	{	
		if(VERBOSE == 1) printf("Phase state failed. Expected Val %d Actual Val %d\n",pre->phase,post->phase);
		flag =  1;
	}
	if(pre->whoseTurn != post->whoseTurn)
	{	
		if(VERBOSE == 1) printf("Whoseturn state failed. Expected Player %d Actual Player %d\n",pre->whoseTurn,post->whoseTurn);
		flag =  1;
	}
	if( (pre->coins+coins) != post->coins)
	{	
		if(VERBOSE == 1) printf("Coins state failed. Expected Val %d Actual Val %d\n",pre->coins+coins,post->coins);
		flag =  1;
	}
	if(pre->outpostPlayed+OUTPOST != post->outpostPlayed)
	{
		if(VERBOSE == 1) printf("Outpost state failed. Expected Val %d Actual Val %d\n",pre->outpostPlayed,post->outpostPlayed);
		flag = 1;
	}
	if(flag == 1)
	{
		if(VERBOSE == 1) printf("*****STATE TEST FAILED*****\n");
	}
	else
	{
		if(VERBOSE == 1) printf("*****STATE TEST PASSED*****\n");
	}
}

void testHand(struct gameState *pre, struct gameState *post, int player, int isShuffle, int compareTreasure)
{
	int drawCount[2] = {DRAWTEST1,DRAWTEST2};
	int i,j,flag=0;
	char name[50],name2[50];
	int treasureCount = 0;
	
	if(VERBOSE == 1) printf("\n*******HAND TEST***********\n");
	for(i=0;i<=1;i++)
	{
		int preHandCount = pre->handCount[player+i];
		int postHandCount = post->handCount[player+i];
		if(postHandCount-preHandCount!=drawCount[i])
		{
			if(VERBOSE == 1) printf("Error in hand count for player %d. Expected %d. Actual %d.\n",i,preHandCount+drawCount[i],postHandCount);
			flag = 1;
		}
		for(j=0;j<preHandCount;j++) //Check Previous cards in hand to see if they changed
		{
			if(pre->hand[player+i][j] != post->hand[player+i][j])
			{
				cardNumToName(pre->hand[player+i][j],name);
				cardNumToName(post->hand[player+i][j],name2);
				if(VERBOSE == 1) printf("Error in Player %d's hand. Expected card: %s. Actual card: %s\n",i,name,name2);
				flag = 1;
			}
		}
	}
	for(j=pre->handCount[player]-1;j<post->handCount[player];j++) //Won't run for second player. Verify cards in top of hand are treasures. 
	{
		if(post->hand[player][j] < 4 || post->hand[player][j] > 6)
		{
			cardNumToName(post->hand[player][j],name);
			if(VERBOSE == 1) printf("Error in Player %d's hand. Expected card #%d to be treasure. Actual card: %s\n",player,j,name);
			flag = 1;
		}
		else//card at most recent handCount+ is a treasure!
		{
			treasureCount++;
		}
	}
	if(treasureCount != compareTreasure)
	{
		if(VERBOSE == 1) printf("Error gathering treasures in hand.\n");
		flag = 1;
	}
	if(flag == 0)
	{
		if(VERBOSE == 1) printf("*****HAND TEST PASSED******\n");
	}
	else
	{
		if(VERBOSE == 1) printf("*****HAND TEST FAILED******\n");
	}
}

void testPlayed(struct gameState *post, int player)
{
	int i;
	int flag = 0;
	char name[50];
	
	printf("\n*******PlAYED TEST***********\n");
	for(i=0;i<1;i++)
	{
		if(post->playedCards[i] != 7)
		{
			flag = 1;
			cardNumToName(post->playedCards[i],name);
			if(VERBOSE == 1) printf("Error in played at position %d. Expecting adventurer in played pile. Actual card %s\n",i,name);
		}
	}	
	if(post->playedCardCount != 1)
	{	
		flag = 1;
		if(VERBOSE == 1) printf("Error in played. Expecting 1 card played. Actual # of cards played %d\n",post->playedCardCount);
	}
	
	if(flag == 0)
	{
		if(VERBOSE == 1) printf("*****PLAYED TEST PASSED******\n");
	}
	else
	{
		if(VERBOSE == 1) printf("*****PLAYED TEST FAILED******\n");
	}
}
void testSuite()
{
	struct gameState preTest,postTest;
	int player = 0;
	int *k;
	int i,isShuffle;
	int cardsDrawn;
	time_t t;
	srand((unsigned)time(&t));
	static struct gameState PURGE; // reset the gameState struct.
	for(i=1;i<=3000;i++)
	{
		printf("\n----------Rand Test of Adv. ITR# %d.----------",i);
		int compareTreasure = 0;
		//Initilization of random scenario.
		k = randKingdom();
		//q
		//player 0 init
		randDeck(&postTest,player,k);
		randHand(&postTest,player,k);
		randDiscard(&postTest,player,k);
		//player 1 init
		randDeck(&postTest,player+1,k);
		randHand(&postTest,player+1,k);
		randDiscard(&postTest,player+1,k);
		//game init
		randSupply(&postTest,k);
		randState(&postTest);
		//insert the card to be played
		insertCard(&postTest,player);
		//update coins for player 0, no need to do this for player 1 due to gameState struct organization		
		updateCoins(player,&postTest,0);
		//save gameState before playing card
		memcpy(&preTest,&postTest,sizeof(struct gameState));
		//play the card
		playCard((postTest.handCount[player]-1),0,0,0,&postTest);
		testPlayed(&postTest,player);
		//get number of cards drawn to be used to check deckCount, deckOrder. if shuffle occurs cardsDrawn won't be used and isShuffle will flag for testDeck and testDiscard functions
		cardsDrawn = getDrawnCards(&preTest,player,&isShuffle,&compareTreasure);
		//simple test, verify the kingdom cards remain unchanged
		testSupply(&preTest,&postTest);
		//checks deckOrder (ensure cards that haven't been drawn haven't changed position in deck), deckCount (appropiately changed per number of cards drawn). in event of shuffle deckCount and deckOrder will not be examined.
		//in event of no treasures, validate deckCount is 0.
		testDeck(&preTest,&postTest,player,cardsDrawn,isShuffle);
		testDiscard(&preTest,&postTest,player,cardsDrawn,isShuffle,compareTreasure);
	//	printHand(player,&preTest);
		//test hand for handCount, handOrder, and # of treasures
		testHand(&preTest,&postTest,player,isShuffle,compareTreasure); //error for low deckCount,discardCount. hand discards up to next treasure card. i did not introduce this change (I think)
	//	printHand(player,&postTest);
		//test state to see if it remains unchanged
		testState(&preTest,&postTest);	
		//refresh the struct
		postTest = PURGE;
		free(k);
		printf("------------------------------------------\n\n\n");
	}
}

int main()
{
	testSuite();
	return 1;
}
