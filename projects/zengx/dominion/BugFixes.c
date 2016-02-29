// cs 362 Xiaohan Zeng assignment5


Bugs fix for ones found by teammates

[1] village card : numActions incremented by 1 rather than 2

Description : The village card rules are + 1 card, +2 actions.numActions in the game state
			  is currently only incremented by 1; it should be incremented by 2.

			  Steps to Reproduce :
1. Create a game
2. Ensure current player's hand contains a village card
3. Store or record the current numActions
4. Call cardEffect() on the village card from step 2.

Expected Results : numActions is 2 more than the value recorded in step 3.

Actual Results : numActions is 1 more than the value recorded in step 3.


Fix:
   In void playVillage(int handPos, int currentPlayer, struct gameState *state) function increase action by 2 instead of 1

   //+2 Actions
   state->numActions = state->numActions + 2;

[2] smithy card : 2 cards drawn rather than 3

Description : The smithy card removes 2 cards from the current player's deck and adds
			  them to the player's hand. It should move 3 cards to the player's hand according to
			  Dominion rules.

			  Steps to Reproduce :
1. Create a game
2. Ensure current player's hand contains a smithy card
3. Store or record the current player's hand count and deck count
4. Call cardEffect() on the smithy card from step 2.

Expected Results : player's deck count is decreased by 3
player's hand count is increased by 3

Actual Results : player's deck count is decreased by 2
player's hand count is increased by 2

Fix :
	In playSmithy function fix the for loop to draw three cards

	for (i = 0; i < 3; i++)
	{
	drawCard(currentPlayer, state);
	}







Bugs fix for ones introduced by me

1. Bug : playAdventurer will dismiss one leass card
Fix : change while (z - 1>0) to z-1>=0

2. Bug : playSteward choice 1 and 2 condition are swapped
Fix: Swap two if statements 
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
3. Bug: playCutpurse , extra = is added to for loop
Fix: remove extra =
	 for (i = 0; i < state->numPlayers; i++)
