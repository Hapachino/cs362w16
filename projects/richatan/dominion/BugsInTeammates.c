Tanna Richardson
CS362 - Winter 2016
Assignment 5: Bugs Found in Teammate's Dominion Code


-------------------------------------------------------------------------------------------
	Emmalee Jones (jonese8)
-------------------------------------------------------------------------------------------

[1] adventurer card: Segmentation fault when deck contains only copper

Description: When playing a game with only copper treasure cards in the player's
  deck, a segmentation fault occurs and the adventurer card does not complete execution.

Steps to Reproduce:
	1. Create a game
	2. Ensure current player's hand contains an adventurer card
	3. "Stack" the current player's deck so it contains 10 kingdom cards and 2 copper cards
	4. Call cardEffect() on the adventurer card from step 2.	

Expected Results: 2 copper cards are revealed from deck and added to hand

Actual Results: Segmentation fault

------------------------------------------------------------------------------------------

[2] council_room card: numBuys increased by 4 rather than 1

Description: The council room card increases numBuys in the game state by 4. It should
  only increase it by 1 according to Dominion rules.

Steps to Reproduce:
	1. Create any valid game
	2. Ensure current player's hand contains a council_room card
	3. Store or record the current numBuys
	4. Call cardEffect() on the council_room card from step 2.	

Expected Results: numBuys is 1 more than previous amount recorded in step 3.

Actual Results: numBuys is 4 more than previous amount recorded in step 3.

------------------------------------------------------------------------------------------

Test Refactoring: the only change I made was to cardtest2.c to avoid the segmentation
fault discovered in bug 1 so that I could continue testing. I changed the line
#define TREASURE copper to #define TREASURE gold so that the treasure cards I stacked
the deck with were gold cards that allowed the full test to complete.


-------------------------------------------------------------------------------------------
	Xiaohan Zeng (zengx)
-------------------------------------------------------------------------------------------

[1] village card: numActions incremented by 1 rather than 2

Description: The village card rules are +1 card, +2 actions. numActions in the game state
  is currently only incremented by 1; it should be incremented by 2.

Steps to Reproduce:
	1. Create a game
	2. Ensure current player's hand contains a village card
	3. Store or record the current numActions
	4. Call cardEffect() on the village card from step 2.	

Expected Results: numActions is 2 more than the value recorded in step 3.

Actual Results: numActions is 1 more than the value recorded in step 3.

------------------------------------------------------------------------------------------

[2] smithy card: 2 cards drawn rather than 3

Description: The smithy card removes 2 cards from the current player's deck and adds
  them to the player's hand. It should move 3 cards to the player's hand according to
  Dominion rules.

Steps to Reproduce:
	1. Create a game
	2. Ensure current player's hand contains a smithy card
	3. Store or record the current player's hand count and deck count
	4. Call cardEffect() on the smithy card from step 2.	

Expected Results: player's deck count is decreased by 3
				  player's hand count is increased by 3

Actual Results: player's deck count is decreased by 2
				player's hand count is increased by 2

------------------------------------------------------------------------------------------

Test Refactoring: none; the tests worked as is

