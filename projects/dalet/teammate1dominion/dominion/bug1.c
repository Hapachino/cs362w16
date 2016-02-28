/*
Matt Walz
CS 362 Assignment 3
bug1.c

_____________________________________________________________________________________________________
Unit Tests:

1) discardCard() method
Ran 6 test scenarios:

CASE 1: trashFlag = 0 and discarded card is last card in player's hand
	Ran successfully
CASE 2: trashFlag = 0 and discarded card is only card in player's hand
	Ran successfully
CASE 3: trashFlag = 0, discarded card is not last card in hand, and hand size is greater than 1
	Ran successfully
CASE 4: trashFlag = 1 and discarded card is last card in hand
	Ran successfully
CASE 5: trashFlag = 1 and discarded card is only card in hand
	Ran successfully
CASE 6: trashFlag = 1, discarded card is not last card in hand, and hand size is greater than 1
	Ran successfully


	
2) gainCard() method
Ran 5 test scenarios:
	
CASE 1: Desired card's supply is empty
	Ran successfully. Function returned -1 and no card was taken from supply.

CASE 2: Desired supply is not in the game
	Ran successfully. Function returned -1 and no card was taken from supply.

CASE 3: toFlag = 0 and desired supply available
	Ran successfully
	
CASE 4: toFlag = 1 and desired supply available
	Ran successfully

CASE 5: toFlag = 2 and desired supply available
	Ran successfully


	
3) drawCard() method
Ran 2 test scenarios:

CASE 1: Deck is not empty
	Ran successfully
	
CASE 2: Deck is empty, but discard pile is not
	Ran successfully

CASE 3: Deck is empty and discard pile is empty
	Ran successfully: function returned a -1 and did not draw a card


	
4) isGameOver() method
Ran 10 test scenarios:

CASE 1: Game is not over. 0 supply piles are empty
	Ran successfully

CASE 2: Game is not over. 1 supply pile (not Province) is empty
	Ran successfully
	
CASE 3: Game is over. The Province supply pile is empty
	Ran successfully
	
CASE 4: Game is not over. 2 supply piles (neither Province) is empty
	Ran successfully
	
CASE 5: Game is over. 2 supply piles are empty and one is the Province pile
	Ran successfully

CASE 6: Game is over. Copper, sea_hag, and minion supply piles are empty
	Bug found. Ran successfully when 3 piles were empty except when one of those piles was the sea hag card. In this scenario the check incorrectly determined that the game was not over.
	
CASE 7: Game is over. 3 supply piles are empty (none Province) (and none Sea Hag)
	As mentioned in CASE 6, this scenario ran correctly except in the instance when the Sea Hag was one of the empty piles.
	
CASE 8: Game is over. 3 supply piles are empty (one is Province)
	Ran successfully.
	
CASE 9: Game is over. 12 supply piles are empty
	Ran successfully.
	
CASE 10: Game is over. All supply piles are empty
	Ran successfully.


_____________________________________________________________________________________________________
Card Tests:

1) Smithy
Ran 3 test scenarios:

CASE 1: Current player has more than 3 cards in their deck
	Ran successfully with all expected outcomes except that the Smithy card was not added to the played cards pile and the played cards count did not increment. This was an error I introduced in the previous assignment and documented in refactor.c.
	
CASE 2: Current player has fewer than 3 cards in their deck, but more than 3 cards in their combined deck and discard pile
	Ran successfully with all expected outcomes except that the Smithy card was not added to the played cards pile and the played cards count did not increment. This was an error I introduced in the previous assignment and documented in refactor.c.

CASE 3: Current player has 1 card combined in their deck and discard pile
	Ran successfully with all expected outcomes (drew the one remaining card and hand count and deck count were properly adjusted) except that the Smithy card was not added to the played cards pile and the played cards count did not increment. This was an error I introduced in the previous assignment and documented in refactor.c.

	
	
2) Village
Ran 3 test scenarios:

CASE 1: Current player has enough cards in their deck to draw without shuffling
	Ran successfully with all expected outcomes.
	
CASE 2: Current player has 0 cards in their deck, but at least 1 card in their combined deck and discard pile
	Ran successfully with all expected outcomes.

CASE 3: Current player has 0 cards combined in their deck and discard pile
	Ran successfully with all expected outcomes.
	
	

3) Adventurer
Ran 2 test scenarios:

CASE 1: Current player has 2 or more coins in their deck to draw with adventurer
	Player successfully drew cards until they added two coins to their hand, but adventurer was not put into the played card pile and the player's hand count was not appropriately maintained.
	
CASE 2: Current player has 1 coin in their deck and discard pile combined to draw with adventurer
	Player successfully drew all cards in deck and discard pile and added just the one coin to their hand, but adventurer was not put into the played card pile and the player's hand count was not appropriately maintained.

	

4) Remodel
Ran 4 test scenarios:

CASE 1: Current player exchanges a card for another costing exactly 2 coins more than trashed card (positive supply of new card)
	Ran successfully with player adding new card to their discard pile. However, the card (choice1) which was supposed to be trashed as a result of Remodel was only moved to the played cards pile.
	
CASE 2: Current player exchanges a card for another costing more than 2 coins more than trashed card
	This incorrectly added the desired card to the player's discard pile even though the card was too expensive. Also, the card (choice1) which was supposed to be trashed as a result of Remodel was only moved to the played cards pile.
	
CASE 3: Current player exchanges a card for another costing 1 coin more than trashed card
	This incorrectly did not add the desired card to the player's discard pile even though the card was within the price range. Also, the card (choice1) which was supposed to be trashed as a result of Remodel was only moved to the played cards pile. Additionally, because the player did not get the desired card added to their discard pile, the card effect should have some error handling to request a different card be chosen or to undo the other effects (cards played and trashed, actions spent, etc.) of the card since it could not be used.
	
CASE 4: Current player exchanges a card for another costing exactly 2 coins more than trashed card (zero supply)
	This correctly prevented the player from adding the selected card to their discard pile because the supply was empty. However, the card (choice1) which was supposed to be trashed as a result of Remodel was only moved to the played cards pile. Additionally, because the player did not get the desired card added to their discard pile, the card effect should have some error handling to request a different card be chosen or to undo the other effects (cards played and trashed, actions spent, etc.) of the card since it could not be used.