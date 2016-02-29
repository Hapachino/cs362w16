File: BugFixes.c
	Author: Chris Trana
	CS 362

Bugs found by teammate

getCost
All tests pass

updateCost
All tests pass

isGameOver
Bug found when setting random piles of 3 to 0. Some pass and some fail, meaning that there is a bug
with one or more of the cards. My test indicates that the bug is when treasure map and/or sea hag is
set to 0. These 2 cards are the source of the bug.

To fix this used my test and updated to check for these two 
cards.  I then ran my test in GDB to step through the code to see they were not being checked.
I corrected an incorrect loop counter to check all card piles
From:

int isGameOver(struct gameState *state) {
  int i;
  int j;
	
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
    {
      return 1;
    }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)
    {
      if (state->supplyCount[i] == 0)
	{
	  j++;
	}
    }
  if ( j >= 3)
    {
      return 1;
    }

  return 0;
}

To;
int isGameOver(struct gameState *state) {
  int i;
  int j;
	
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
    {
      return 1;
    }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 27; i++)//changed loop counter to check all 27 card piles.
    {
      if (state->supplyCount[i] == 0)
	{
	  j++;
	}
    }
  if ( j >= 3)
    {
      return 1;
    }

  return 0;
}

buyCard
All tests Pass

villageCard
Actions do not increment. Stayed the same.

To fix this I used my test cases in GDB to find the cause.
To correct this I corrected the addition logic for actions.

From:
int villageCard(int handPos, int currentPlayer, struct gameState *state)
{
      //+1 Card
      drawCard(currentPlayer, state);
			
      //+2 Actions
      state->numActions = state->numActions ++;
			
      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
}

To:
int villageCard(int handPos, int currentPlayer, struct gameState *state)
{
      //+1 Card
      drawCard(currentPlayer, state);
			
      //+2 Actions
      state->numActions = state->numActions + 2;//correction made here
			
      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
}

smithyCard
deckCount of current player decreases by 4
handCount increased incorrectly

To fix this I used my test cases in GDB to find the cause.
To correct this I corrected the for loop to increment the correct number of times.

From:
int smithyCard(int handPos, int currentPlayer, struct gameState *state)
{
	int i;

	//+3 Cards
    for (i = 0; i <= 3; i++)
	{
		drawCard(currentPlayer, state);
	}
			
    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    return 0;
}
To:
int smithyCard(int handPos, int currentPlayer, struct gameState *state)
{
	int i;

	//+3 Cards
    for (i = 0; i < 3; i++)//removed = sign  to only icrement the correct number of times, 3.
	{
		drawCard(currentPlayer, state);
	}
			
    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    return 0;
}

adventurerCard
discardCount for current player increases drastically (pre:39 post:127)
deckCount decreased drastically(pre:95 post:5)

This is not an error but due to a large and unlikely gamestate in which 90 cards are drawn before 2 treasure cards are found.

Fixed my introduced bug of drawing an extra treasure card when available
From:
while(drawntreasure <= 2)
  	{
		if (state->deckCount[currentPlayer] < 1)	//if the deck is empty we need to shuffle discard and add to deck
		{
	  		shuffle(currentPlayer, state);
		}
		drawCard(currentPlayer, state);
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];	//top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  		drawntreasure++;
		else
		{
	  		temphand[z]=cardDrawn;
	  		state->handCount[currentPlayer]--;	//this should just remove the top card (the most recently drawn one).
	  		z++;
		}
    }
    
	ret = z + drawntreasure;
	
    while(z-1>=0)
    {
		state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;
    }

    return ret;
}
To:
while(drawntreasure < 2)//corrected logic to increment correct number of times
  	{
		if (state->deckCount[currentPlayer] < 1)	//if the deck is empty we need to shuffle discard and add to deck
		{
	  		shuffle(currentPlayer, state);
		}
		drawCard(currentPlayer, state);
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];	//top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  		drawntreasure++;
		else
		{
	  		temphand[z]=cardDrawn;
	  		state->handCount[currentPlayer]--;	//this should just remove the top card (the most recently drawn one).
	  		z++;
		}
    }
    
	ret = z + drawntreasure;
	
    while(z-1>=0)
    {
		state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;
    }

    return ret;
}

Last bug I introduced that was not found by teammates was in council_room. I found this error using my tests
and localized the fault using GDB. To fix this error I corrected the logic for incresing the number of buys.

From:
int council_roomCard ( int currentPlayer, int handPos,  struct gameState *state)
{    
	//+4 Cards
	int i; 
    for (i = 0; i < 4; i++)
	{
	  drawCard(currentPlayer, state);
	}
			
     //+1 Buy
     state->numBuys--;
			
     //Each other player draws a card
    for (i = 0; i < state->numPlayers; i++)
	{
	  if ( i != currentPlayer )
	  {
	      drawCard(i, state);
	  }
	}
			
    //put played card in played card pile
    discardCard(handPos, currentPlayer, state, 0);
	
	return 0;
}

To:

int council_roomCard ( int currentPlayer, int handPos,  struct gameState *state)
{    
	//+4 Cards
	int i; 
    for (i = 0; i < 4; i++)
	{
	  drawCard(currentPlayer, state);
	}
			
     //+1 Buy
     state->numBuys = state->numBuys + 1;
			
     //Each other player draws a card
    for (i = 0; i < state->numPlayers; i++)
	{
	  if ( i != currentPlayer )
	  {
	      drawCard(i, state);
	  }
	}
			
    //put played card in played card pile
    discardCard(handPos, currentPlayer, state, 0);
	
	return 0;
}