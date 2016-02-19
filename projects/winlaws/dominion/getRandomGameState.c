#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "getRandomGameState.h"

void initSupplyCount(struct gameState* state);
void getRandKingdomCards(int* kingdomCards);
void printGameState(struct gameState* state);
void dealRandPlayerDecks(struct gameState* state);

struct gameState* getRandomGameState()
{
	int i;

	struct gameState* randGameState = malloc(sizeof(struct gameState));
	
	randGameState->numPlayers = ((rand() % (MAX_PLAYERS - 2)) + 2); 
  	
  	initSupplyCount(randGameState);
  	
  	for(i = 0; i < treasure_map; i++)
  	{
  		randGameState->embargoTokens[i] = 0;
  	}
  	randGameState->outpostPlayed = 0;
  	randGameState->outpostTurn = 0;
  	
  	randGameState->whoseTurn = (rand() % randGameState->numPlayers);
  	
  	randGameState->phase = 0;
  	
  	randGameState->numActions = rand() % 5; 
  	randGameState->coins = 0; 
  	randGameState->numBuys = rand() % 5; 
  	
  	dealRandPlayerDecks(randGameState);
  	//randGameState->deck[MAX_PLAYERS][MAX_DECK];
  	//randGameState->deckCount[MAX_PLAYERS];

  	//randGameState->discard[MAX_PLAYERS][MAX_DECK];
  	//randGameState->discardCount[MAX_PLAYERS];

  	//randGameState->hand[MAX_PLAYERS][MAX_HAND];
  	//randGameState->handCount[MAX_PLAYERS];
  	
  	//randGameState->playedCards[MAX_DECK];
  	//randGameState->playedCardCount;

  	return randGameState;
}

void initSupplyCount(struct gameState* state)
{
	int i;
	int j;
	int kingdomCards[10];

	getRandKingdomCards(kingdomCards);

	if (state->numPlayers == 2)
    {
      state->supplyCount[curse] = 10;
    }
  	else if (state->numPlayers == 3)
    {
      state->supplyCount[curse] = 20;
    }
  	else
    {
      state->supplyCount[curse] = 30;
    }

  	//set number of Victory cards
  	if (state->numPlayers == 2)
    {
      state->supplyCount[estate] = 8;
      state->supplyCount[duchy] = 8;
      state->supplyCount[province] = 8;
    }
  	else
    {
      state->supplyCount[estate] = 12;
      state->supplyCount[duchy] = 12;
      state->supplyCount[province] = 12;
    }

  	//set number of Treasure cards
  	state->supplyCount[copper] = 60 - (7 * state->numPlayers);
  	state->supplyCount[silver] = 40;
  	state->supplyCount[gold] = 30;

  	//set number of Kingdom cards
  	for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
    {
    	for (j = 0; j < 10; j++)           		//loop chosen cards
		{
	  		if (kingdomCards[j] == i)
	    	{
	      		//check if card is a 'Victory' Kingdom card
	      		if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
				{
		  			if (state->numPlayers == 2)
		  			{ 
		    			state->supplyCount[i] = 8; 
		  			}
		  			else
		  			{ 
		  				state->supplyCount[i] = 12; 
		  			}
				}
	      		else
				{
		  			state->supplyCount[i] = 10;
				}
	      		break;
	    	}
	  		else    //card is not in the set choosen for the game
	    	{
	      		state->supplyCount[i] = -1;
	    	}
		}
    }
}

void getRandKingdomCards(int* kingdomCards)
{
	int i;
	int j;
	bool cardSelected = false;
	bool alreadySelected = false;
	int n = adventurer;
	
	for(i = 0; i < 10; i++)
	{
		while(!cardSelected)
		{
			if(rand() % 10 == 0)
			{
			//printf("i = %i\n", i);
				for(j = 0; j < i; j++)
				{
					if(n == kingdomCards[j])
					{
						alreadySelected = true;
					}
				}
				if(!alreadySelected)
				{
					kingdomCards[i] = n;
					cardSelected = true;
				}

			}
			
			if((!cardSelected) && (n++ > treasure_map))
			{
				n = adventurer;
			}
			alreadySelected = false;
		}
		cardSelected = false;
	}
}

void dealRandPlayerDecks(struct gameState* state)
{
	int i;
	int j;
	int randNumCards;
	int randCard;

	for (i = 0; i < state->numPlayers; i++)
	{
		//generate random player deck
		state->deckCount[i] = 0;
		randNumCards = rand() % MAX_DECK;
		for(j = 0; j < randNumCards; j++)
		{
			randCard = rand() % (treasure_map + 1);
			state->deck[i][j] = randCard;
	  		state->deckCount[i]++;
		}

		//generate random player hand
		state->handCount[i] = 0;
		if(state->deckCount[i] > 0)
			randNumCards = rand() % state->deckCount[i];
		else 
			randNumCards = 0;	
		for(j = 0; j < randNumCards; j++)
		{
			drawCard(i, state);
		}

		//generate random player discard deck
		state->discardCount[i] = 0;
		if(state->deckCount[i] > 0)
			randNumCards = rand() % state->deckCount[i];
		else 
			randNumCards = 0;	
		for(j = 0; j < randNumCards; j++)
		{
			state->discard[i][state->discardCount[i]] = state->deck[i][state->deckCount[i] - 1];
    		state->deckCount[i]--;
    		state->discardCount[i]++;
		}

		state->playedCardCount = 0;
		randNumCards = rand() % MAX_DECK;
		for(j = 0; j < randNumCards; j++)
		{
			state->playedCards[i] = rand() % (treasure_map + 1);
    		state->playedCardCount++;
		}
	}
}

/*int main()
{
	struct gameState* randGameState = getRandomGameState();

	printGameState(randGameState);
	/*int i;
	int kingdomCards[10];
	getRandKingdomCards(kingdomCards);

	srand(time(0));


	for(i = 0; i < (sizeof(kingdomCards)/sizeof(int)); i++)
	{
		printf("%i\n", kingdomCards[i]);
	}
	return 0;
}*/

void printGameState(struct gameState* state)
{
	int i;
	printf("numPlayers: %i\n", state->numPlayers);
	/*printf("supplyCount: \n");
	for(i = curse; i < (treasure_map + 1); i++)
	{
		printf("\t%i: %i", i, state->supplyCount[i]);
	}
	*/
	for(i = 0; i < state->numPlayers; i++)
	{
		printf("Player %i Hand:\n", i+1);
		printf("\tdeckCount: %i\n", state->deckCount[i]);
		printf("\thandCount: %i\n", state->handCount[i]);
		printf("\tdiscardCount: %i\n", state->discardCount[i]);
		printf("\ttotalDeck: %i\n", state->deckCount[i] + state->handCount[i] + state->discardCount[i]);
	}
}