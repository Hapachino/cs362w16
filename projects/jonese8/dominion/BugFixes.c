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
	  
Bug Fix for Smithy Card

The bug was that so that the next player gets an extra card.

From: 

int runSmithy(struct gameState *state, int currentPlayer, int handPos, int nextPlayer)
{
    int i;
/*+3 Cards   */
      for (i = 0; i < 3; i++) //refactor to provide the next player an extra card on iteration 3
	{
	  if (i == 2)
	  {
		   drawCard(currentPlayer, state);
		   drawCard(nextPlayer, state);
	  }	
	  else	  
	  drawCard(currentPlayer, state);
To:	
int runSmithy(struct gameState *state, int currentPlayer, int handPos, int nextPlayer)
{
      for (i = 0; i < 3; i++) 
	{
	  drawCard(currentPlayer, state);
	}
	  
Bug Fix for Steward Card

The bug was Get error message shows under test steward card trash 2 cards: played card number not correct. The played the played card number +3 after run. One of the three card should be the steward. Other two could be cards need to trash.


From: 

int runSteward(struct gameState *state, int currentPlayer, int choice1, int choice2, int choice3, int handPos) 
{
  if (choice1 == 1)
	{
	  //+2 cards
	  drawCard(currentPlayer, state);
	  drawCard(currentPlayer, state);
	}
      else if (choice1 == 2)
	{
	  //+2 coins
	  state->coins = state->coins + 2;
	}
      else
	{
	  //trash 2 cards in hand
	  discardCard(choice2, currentPlayer, state, 0);//refactor so that cards are discarded to deck instead of trash
	  discardCard(choice3, currentPlayer, state, 0);
To:	
int runSteward(struct gameState *state, int currentPlayer, int choice1, int choice2, int choice3, int handPos) 
{
  if (choice1 == 1)
	{
	  //+2 cards
	  drawCard(currentPlayer, state);
	  drawCard(currentPlayer, state);
	}
      else if (choice1 == 2)
	{
	  //+2 coins
	  state->coins = state->coins + 2;
	}
      else
	{
	  //trash 2 cards in hand
	  discardCard(choice2, currentPlayer, state, 1); 
	  discardCard(choice3, currentPlayer, state, 1); 

	  
Bug Fix for scoreFor

There appears to be a bug where the wrong number of deck count is being used for 
scoreFor.  The bug only shows if the number of cards between discardCount and
deckCount is different. 
	  
From: 
	  
int scoreFor (int player, struct gameState *state) {

  ...

  //score from deck
  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->deck[player][i] == curse) { score = score - 1; };
      if (state->deck[player][i] == estate) { score = score + 1; };
      if (state->deck[player][i] == duchy) { score = score + 3; };
      if (state->deck[player][i] == province) { score = score + 6; };
      if (state->deck[player][i] == great_hall) { score = score + 1; };
      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }

To: 

 int scoreFor (int player, struct gameState *state) {

  ...

  //score from deck
  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == curse) { score = score - 1; };
      if (state->deck[player][i] == estate) { score = score + 1; };
      if (state->deck[player][i] == duchy) { score = score + 3; };
      if (state->deck[player][i] == province) { score = score + 6; };
      if (state->deck[player][i] == great_hall) { score = score + 1; };
      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    }