Emmalee Jones
CS362 - Winter 2016
Assignment 5: Bugs Found in Teammate's Dominion Code


-------------------------------------------------------------------------------------------
	Tanna Richardson (richatan) 
-------------------------------------------------------------------------------------------
smithy card: +3 Cards

Bug [1] smithy card: The handcount was one card higher than it should have been. The deck count was
one card lower than it should have been. 

Steps to Reproduce:
	1. Set game criteria including valid cards.
	2. Initialize a game with 2 players, 10 cards, seed of 1000 and new gamestate.
	3. Call cardEffect() on the smithy card.
	4. Run comparisions to test for valid card play.	

Expected Results: Expected 7 cards in hand count for current player, 2 cards in deck count for
current player.

Actual Results: 8 cards in hand count for current player, 1 card in deck count for current player.

------------------------------------------------------------------------------------------
council_room card: +4 Cards, +1 Buy, Each player draws a card

Bug [2] council_room card: The handcount was one card higher than it should have been for the current
player.  The deck count was one card lower than it should have been for the current player. The 
handcount was one card higher than it should have been for the next player.  The deck count was 
one card higher than it should have been for the next player.    

Steps to Reproduce:
	1. Set game criteria including valid cards
	2. Initialize a game with 2 players, 10 cards, seed of 1000 and new gamestate
	3. Call cardEffect() on the council_room card.
	4. Run comparisions to test for valid card play.		

Expected Results: Expected 8 cards in hand count for current player, 1 card in deck count for
current player. Expected 1 card in hand count for next player, 9 cards in deck count next player.

Actual Results: 9 cards in hand count for current player, 0 card in deck count for current player.
0 cards in hand count for next player, 10 cards in deck count next player.

-------------------------------------------------------------------------------------------
	Xiaohan Zeng (zengx)
-------------------------------------------------------------------------------------------

smithy card: +3 Cards

Bug [1] smithy card: The handcount was one card lower than it should have been. The deck count was
one card higher than it should have been. 

Steps to Reproduce:
	1. Set game criteria including valid cards.
	2. Initialize a game with 2 players, 10 cards, seed of 1000 and new gamestate.
	3. Call cardEffect() on the smithy card.
	4. Run comparisions to test for valid card play.	

Expected Results: Expected 7 cards in hand count for current player, 2 cards in deck count for
current player.

Actual Results: 6 cards in hand count for current player, 3 card in deck count for current player.

------------------------------------------------------------------------------------------

village card: +1 Card +2 Actions

Bug [2] village card: The Number of actions was one card lower than it should have been.

Steps to Reproduce:
	1. Set game criteria including valid cards.
	2. Initialize a game with 2 players, 10 cards, seed of 1000 and new gamestate.
	3. Call cardEffect() on the village card.
	4. Run comparisions to test for valid card play.	

Expected Results: Expected 3 actions for current player.

Actual Results: 2 actions for current player.