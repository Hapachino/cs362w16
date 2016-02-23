Emmalee Jones
CS362 - Winter 2016
Assignment 5: Bugs Fixed in Dominion Code

Bug Fix for Adventurer Card

The bug was that when only copper in deck received segmentation fault. Added copper as one of the items to test for.

From: 
int runAdventurer(struct gameState *state, int drawntreasure, int currentPlayer, int cardDrawn, int temphand[], int z)
{
  while(drawntreasure<2){
	if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
	  shuffle(currentPlayer, state);
	}
	drawCard(currentPlayer, state);
	cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
	if (cardDrawn == silver || cardDrawn == gold) //refactor to remove cardDrawn == copper
	  drawntreasure++;  

To:	
int runAdventurer(struct gameState *state, int drawntreasure, int currentPlayer, int cardDrawn, int temphand[], int z)
{
  while(drawntreasure<2){
	if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
	  shuffle(currentPlayer, state);
	}
	drawCard(currentPlayer, state);
	cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
	if (cardDrawn == cooper || cardDrawn == silver || cardDrawn == gold)  
	  drawntreasure++;  

Bug Fix for Council Room Card

The bug was that the number of buys should have been 1 but was 4.  Moved the buy code
out of the for interation to below the for iteration to fix the error.


From: 

int runCouncilRm(struct gameState *state, int currentPlayer, int handPos)
{
    int i;  
    //+4 Cards
      for (i = 0; i < 4; i++)
	{
	  drawCard(currentPlayer, state); 
				
      //+1 Buy
      state->numBuys++; //refactor so buy is included in for loop and occurs multiple times
	}
To:	
int runCouncilRm(struct gameState *state, int currentPlayer, int handPos)
{
    int i;  
    //+4 Cards
      for (i = 0; i < 4; i++)
	{
	  drawCard(currentPlayer, state); 
				
	}	
	      //+1 Buy
      state->numBuys++;    