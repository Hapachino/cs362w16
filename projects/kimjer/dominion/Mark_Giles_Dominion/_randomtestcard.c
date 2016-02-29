//villagetest

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dominion.h"
#include "rngs.h"
#include <math.h>
#include "assert.h"
#define YES 1
#define NO 0 
#define NUMCARDS 10

void ASSERT2(int expVal, int realVal, char *s) 
{	
	if(expVal != realVal) 
	{
		printf("FAIL - %s\n", s);
		printf("EXPECTED value is %d; got %d", expVal, realVal);
		assert(expVal == realVal);
		exit(1);
	}
}

int isUnique(int k[]) {
	int i, j;
	for(i = 0; i < NUMCARDS; i++)
	{
		for(j = 1; j < NUMCARDS; j++)
		{	
			if(j!=i && k[i] == k[j])
				return NO;	
		}	
	}
	return YES;
}

void makeK(int k[])
{
	int i;
	for(i = 0; i < NUMCARDS; i++)
	{
		k[i] = rand()%NUMCARDS;
	}
}	

void initI(struct infosStruct *infos) 
{
	int i;

	(*infos).drawntreasure = 0;
	(*infos).drawntreasure = 0;
	(*infos).cardDrawn = 0; //random
	for(i = 0; i < MAX_HAND; i++)
		(*infos).temphand[i] = 0; //rand()%MAX_HAND
	(*infos).z = 0;
	(*infos).handPos = 0; //not used
	(*infos).i = 0; //not used either
	(*infos).currentPlayer = 0;
}

void func(int *x) 
{
	*x = 5;
}

int main() {

	srand(time(NULL));
	int i, j, ret;
	struct gameState *g;
	struct infosStruct infos;
	g = newGame();
	int k[NUMCARDS]; 
	int n;
	int handCount, deckCount, discardCount, actionCount;
	int handCountExp, deckCountExp, discardCountExp, actionCountExp;

	//Make sure draw card is working correctly
	for(n=0; n < 2000; n++)
	{
		//make unique kingdom cards
		do 
		{
			makeK(k);
		}
		while(!isUnique(k));

		initializeGame(2, k, 3, g);

		//randomize number of players
		int numPlayers = (rand()%MAX_PLAYERS)+1;
		g->numPlayers = numPlayers;

		//randomize unused properties
		g->outpostPlayed = rand();
		g->outpostTurn = rand();
		g->whoseTurn = rand(); //this may be important
		g->phase = rand();
		g->numActions = rand();
		g->coins = rand();
		g->numBuys = rand();

		//randomized player hands
		for(i = 0; i < numPlayers; i++)
		{
			int numCards;
			do
			{
				numCards = floor(rand()%(MAX_HAND/3));
			}
			while(numCards < 13);

			for(j = 0; j < numCards; j++)
			{
				g->hand[i][j] = rand()%15;
			}
			g->handCount[i] = numCards;
		}

		//randomized player decks
		for(i = 0; i < numPlayers; i++)
		{
			int numCards;

			numCards = rand()%(MAX_HAND/3);


			for(j = 0; j < numCards; j++)
			{
				g->deck[i][j] = rand()%15;
			}
			g->deckCount[i] = numCards;
		}
		deckCount = g->deckCount[numPlayers-1];

		//randomized player discard counts
		for(i = 0; i < numPlayers; i++)
		{
			int numCards;
			do
			{
				numCards = rand()%(MAX_HAND/3);
			}
			while(numCards == 0 && g->deckCount[i] == 0);

			for(j = 0; j < numCards; j++)
			{
				g->discard[i][j] = rand()%15;
			}
			g->discardCount[i] = numCards;
		}
		discardCount = g->discardCount[numPlayers-1];
		//initialize infosStruct
		infos.drawntreasure = 0;
		infos.drawntreasure = 0;
		infos.cardDrawn = 0; //random
		for(i = 0; i < MAX_HAND; i++)
			infos.temphand[i] = rand(); //rand()%MAX_HAND
		infos.z = 0;
		infos.handPos = 0; //not used
		infos.i = 0; //not used either

		//randomly select current player
		do
		{
			infos.currentPlayer = rand()%MAX_PLAYERS;
		}
		while(infos.currentPlayer >= numPlayers);

		//get gameState values before calling drawCard()
		handCount = g->handCount[numPlayers-1];
		//handle case when deckCount is 0
		if(deckCount == 0)
		{
			deckCountExp = discardCount;
			deckCountExp--; //because draw card
			discardCountExp = 0;
		}
		else //discardCount is not affected
		{
			discardCountExp = discardCount;
			deckCountExp = deckCount - 1;
		}
		
		handCountExp = handCount + 1;

		drawCard(numPlayers-1, g);

		handCount = g->handCount[numPlayers-1];
		deckCount = g->deckCount[numPlayers-1];
		discardCount = g->discardCount[numPlayers-1];

		ASSERT2(handCountExp, handCount, "handCount after drawCard()");
		ASSERT2(deckCountExp, deckCount, "deckCount after drawCard()");
		ASSERT2(discardCountExp, discardCount, "discardCount after drawCard()");
	}
	puts("drawCard(): PASSED");
	//make sure player has two more cards after effectAdventurer
	for(n=0; n < 2000; n++)
	{
		//make unique kingdom cards
		do 
		{
			makeK(k);
		}
		while(!isUnique(k));

		initializeGame(2, k, 3, g);

		//randomize number of players
		int numPlayers = (rand()%MAX_PLAYERS)+1;
		g->numPlayers = numPlayers;
		//randomly select current player
		do
		{
			infos.currentPlayer = rand()%MAX_PLAYERS;
		}
		while(infos.currentPlayer >= numPlayers);

		//randomize unused properties
		g->outpostPlayed = rand();
		g->outpostTurn = rand();
		g->whoseTurn = rand(); //this may be important
		g->phase = rand();
		g->numActions = rand();
		g->coins = rand();
		g->numBuys = rand();

		//randomized player hands
		for(i = 0; i < numPlayers; i++)
		{
			int numCards;
			do
			{
				numCards = floor(rand()%(MAX_HAND/3));
			}
			while(numCards < 13);

			for(j = 0; j < numCards; j++)
			{
				g->hand[i][j] = rand()%15;
			}
			g->handCount[i] = numCards;
		}

		//randomized player decks
		for(i = 0; i < numPlayers; i++)
		{
			int numCards;
			int coinCount = 0;
			do
			{

			numCards = rand()%(MAX_HAND/3);
				for(j = 0; j < numCards; j++)
				{
					int coin = rand()%15;
					if(coin == copper)
						coinCount++;
					if(coin == silver)
						coinCount++;
					if(coin == gold)
						coinCount++;
					g->deck[i][j] = coin;
				}
			}
			while(coinCount < 2);
			g->deckCount[i] = numCards;
		}
		deckCount = g->deckCount[infos.currentPlayer];
		

		//randomized player discard counts
		for(i = 0; i < numPlayers; i++)
		{
			int numCards;
			do
			{
				numCards = rand()%(MAX_HAND/3);
			}
			while(numCards == 0 && g->deckCount[i] == 0);

			for(j = 0; j < numCards; j++)
			{
				g->discard[i][j] = rand()%15;
			}
			g->discardCount[i] = numCards;
		}
		discardCount = g->discardCount[infos.currentPlayer];

		//initialize infosStruct
		infos.drawntreasure = 0;
		infos.drawntreasure = 0;
		infos.cardDrawn = 0; //random
		for(i = 0; i < MAX_HAND; i++)
			infos.temphand[i] = rand(); //rand()%MAX_HAND
		infos.z = 0;
		infos.handPos = 0; //not used
		infos.i = 0; //not used either

		//get gameState values before calling drawCard()
		handCount = g->handCount[infos.currentPlayer];
		//handle case when deckCount is 0
		if(deckCount == 0)
		{
			deckCountExp = discardCount;
			deckCountExp--; //because draw card
			discardCountExp = 0;
		}
		else //discardCount is not affected
		{
			discardCountExp = discardCount;
			deckCountExp = deckCount - 1;
		}
				//printf("hand count is %d\n", handCount);
		handCountExp = handCount;
		actionCount = g->numActions;
		actionCountExp = actionCount + 2;
		effectVillage(g, &infos);


		actionCount = g->numActions;
		handCount = g->handCount[infos.currentPlayer];
		//printf("hand count is %d\n", handCount);
		ASSERT2(handCountExp, handCount, "handCount");
		ASSERT2(actionCountExp, actionCount, "actionCount");
	}
	puts("effectVillage(): Passed");
	return 0; 
}

/*
int effectVillage(struct gameState *state, struct infosStruct *infos)
{

  int currentPlayer= infos->currentPlayer;

  int handPos = infos->handPos;
  //+1 Card
  drawCard(currentPlayer, state);

  //+2 Actions
  state->numActions = state->numActions + 2;

  //discard played card from hand
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}
*/

/*
int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
{
  //if card is not trashed, added to Played pile 
  if (trashFlag < 1)
  {
    //add card to played pile
    state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos]; 
    state->playedCardCount++;
  }
	
  //set played card to -1
  state->hand[currentPlayer][handPos] = -1;
	
  //remove card from player's hand
  if ( handPos == (state->handCount[currentPlayer] - 1) ) 	//last card in hand array is played
  {
    //reduce number of cards in hand
    state->handCount[currentPlayer]--;
  }
  else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
  {
    //reduce number of cards in hand
    state->handCount[currentPlayer]--;
  }
  else 	
  {
    //replace discarded card with last card in hand
    state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
    //set last card to -1
    state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
    //reduce number of cards in hand
    state->handCount[currentPlayer]--;
  }
	
  return 0;
}
*/
// int drawCard(int player, struct gameState *state)
// {	
//	 int count;
//   int deckCounter;
//   if (state->deckCount[player] <= 0){//Deck is empty
    
//     //Step 1 Shuffle the discard pile back into a deck
//     int i;
//     //Move discard to deck
//     for (i = 0; i < state->discardCount[player];i++){
//       state->deck[player][i] = state->discard[player][i];
//       state->discard[player][i] = -1;
//     }

//     state->deckCount[player] = state->discardCount[player];
//     state->discardCount[player] = 0;//Reset discard

//     //Shufffle the deck
//     shuffle(player, state);//Shuffle the deck up and make it so that we can draw
   
//     if (DEBUG){//Debug statements
//       printf("Deck count now: %d\n", state->deckCount[player]);
//     }
    
//     state->discardCount[player] = 0;

//     //Step 2 Draw Card
//     count = state->handCount[player];//Get current player's hand count
    
//     if (DEBUG){//Debug statements
//       printf("Current hand count: %d\n", count);
//     }
    
//     deckCounter = state->deckCount[player];//Create a holder for the deck count

//     if (deckCounter == 0)
//       return -1;

//     state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to hand
//     state->deckCount[player]--;
//     state->handCount[player]++;//Increment hand count
//   }

//   else{
//     int count = state->handCount[player];//Get current hand count for player
//     int deckCounter;
//     if (DEBUG){//Debug statements
//       printf("Current hand count: %d\n", count);
//     }

//     deckCounter = state->deckCount[player];//Create holder for the deck count
//     state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to the hand
//     state->deckCount[player]--;
//     state->handCount[player]++;//Increment hand count
//   }

//   return 0;
// }


// struct gameState {
//   int numPlayers; //number of players
//   int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
//   int embargoTokens[treasure_map+1];
//   int outpostPlayed;
//   int outpostTurn;
//   int whoseTurn;
//   int phase;
//   int numActions; /* Starts at 1 each turn */
//   int coins; /* Use as you see fit! */
//   int numBuys; /* Starts at 1 each turn */
//   int hand[MAX_PLAYERS][MAX_HAND];
//   int handCount[MAX_PLAYERS];
//   int deck[MAX_PLAYERS][MAX_DECK];
//   int deckCount[MAX_PLAYERS];
//   int discard[MAX_PLAYERS][MAX_DECK];
//   int discardCount[MAX_PLAYERS];
//   int playedCards[MAX_DECK];
//   int playedCardCount;
// };


// int effectAdventure(struct gameState *state, struct infosStruct *infos) 
// {
//   int drawntreasure2 = infos->drawntreasure;
//   int currentPlayer = infos->currentPlayer;
//   int cardDrawn = infos->cardDrawn;
//   int *temphand = (infos->temphand);
//   int z = infos->z;
//   int handPos = infos->handPos;
//   int i = infos->i;

//   while(drawntreasure2<2) 
//   {
//     if (state->deckCount[currentPlayer] <1) 
//     {//if the deck is empty we need to shuffle discard and add to deck
//       shuffle(currentPlayer, state);
//     }

//     drawCard(currentPlayer, state);

//     cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    
//     if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
//     {
//       drawntreasure2++;
//     }
//     else
//     {
//       temphand[z]=cardDrawn;
//       state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
//       z++;
//     }
//   }

//   while(z-1>=0)
//   {
//     state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
//     z=z-1;
//   }
//   return 0;  
// }



// int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state) 
// {
//   int i;
//   int j;
//   int it;			
//   //set up random number generator
//   SelectStream(1);
//   PutSeed((long)randomSeed);
  
//   //check number of players
//   if (numPlayers > MAX_PLAYERS || numPlayers < 2)
//     {
//       return -1;
//     }

//   //set number of players
//   state->numPlayers = numPlayers;

//   //check selected kingdom cards are different
//   for (i = 0; i < 10; i++)
//     {
//       for (j = 0; j < 10; j++)
//         {
// 	  if (j != i && kingdomCards[j] == kingdomCards[i])
// 	    {
// 	      return -1;
// 	    }
//         }
//     }

//   //initialize supply
//   ///////////////////////////////

//   //set number of Curse cards
//   if (numPlayers == 2)
//     {
//       state->supplyCount[curse] = 10;

//     }
//   else if (numPlayers == 3)
//     {
//       state->supplyCount[curse] = 20;
//     }
//   else
//     {
//       state->supplyCount[curse] = 30;
//     }

//   //set number of Victory cards
//   if (numPlayers == 2)
//     {
//       state->supplyCount[estate] = 8;
//       state->supplyCount[duchy] = 8;
//       state->supplyCount[province] = 8;
//     }
//   else
//     {
//       state->supplyCount[estate] = 12;
//       state->supplyCount[duchy] = 12;
//       state->supplyCount[province] = 12;
//     }

//   //set number of Treasure cards
//   state->supplyCount[copper] = 60 - (7 * numPlayers);
//   state->supplyCount[silver] = 40;
//   state->supplyCount[gold] = 30;

//   //set number of Kingdom cards
//   for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
//   {
//     for (j = 0; j < 10; j++)           		//loop chosen cards
//     {
//       if (kingdomCards[j] == i)
//       {
//         //check if card is a 'Victory' Kingdom card
//         if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
//         {
//           if (numPlayers == 2)
//           { 
//             state->supplyCount[i] = 8; 
//           }
//           else
//           {
//             state->supplyCount[i] = 12;
//           }
//         }
//         else
//         {
//           state->supplyCount[i] = 10;
//         }
//         break;
//       }
//       else    //card is not in the set choosen for the game
//       {
//         state->supplyCount[i] = -1;
//       }
//     }
//   }

//   ////////////////////////
//   //supply intilization complete

//   //set player decks
//   for (i = 0; i < numPlayers; i++)
//   {
//     state->deckCount[i] = 0;
//     for (j = 0; j < 3; j++)
//   	{
//   	  state->deck[i][j] = estate;
//   	  state->deckCount[i]++;
//   	}
//     for (j = 3; j < 10; j++)
//   	{
//   	  state->deck[i][j] = copper;
//   	  state->deckCount[i]++;		
//   	}
//   }
//   //shuffle player decks
//   for (i = 0; i < numPlayers; i++)
//     {
//       if ( shuffle(i, state) < 0 )
// 	{
// 	  return -1;
// 	}
//     }

//   //draw player hands
//   for (i = 0; i < numPlayers; i++)
//     {  
//       //initialize hand size to zero
//       state->handCount[i] = 0;
//       state->discardCount[i] = 0;
//       //draw 5 cards
//       // for (j = 0; j < 5; j++)
//       //	{
//       //	  drawCard(i, state);
//       //	}
//     }
  
//   //set embargo tokens to 0 for all supply piles
//   for (i = 0; i <= treasure_map; i++)
//     {
//       state->embargoTokens[i] = 0;
//     }

//   //initialize first player's turn
//   state->outpostPlayed = 0;
//   state->phase = 0;
//   state->numActions = 1;
//   state->numBuys = 1;
//   state->playedCardCount = 0;
//   state->whoseTurn = 0;
//   state->handCount[state->whoseTurn] = 0;
//   //int it; move to top

//   //Moved draw cards to here, only drawing at the start of a turn
//   for (it = 0; it < 5; it++){
//     drawCard(state->whoseTurn, state);
//   }
//   updateCoins(state->whoseTurn, state, 0);

//   return 0;
// }



