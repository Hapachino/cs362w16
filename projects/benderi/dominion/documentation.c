Name:	Ian Bender
Course:	CS362
Assignment 2 - Refactoring dominion code.

Smithy:
Player draws 3 cards
Discard Smithy card from hand
return 0 on success


Adventurer:
Draw cards from deck until 2 treasure cards are revealed
Shuffle discards and add to deck if empty
Discard all drawn cards that are not treasure cards
return 0 on success


discardCard():
Input: 	int (hand position)
	int (current player)
	struct* (current game state)
	int (trash flag)
Output: return 0 succcess
Description:
	Add card to played pile if not trash
	Increment played card count
	Remove card from current hand position
	Decrement count of cards in hand


updateCoins():
Input:	int (player)
	struct* (current game state)
	int (bonus)	
Output:	return 0 on success	
Description:
	Reset coin count to 0
	Add coins according to treasure cards in player's hand
	- copper = +1 coin
	- silver = +2 coins
	- gold = +3 coins
	Add additional bonus coins if applicable


