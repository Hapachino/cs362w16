Tanna Richardson
CS362 - Winter 2016
Assignment 3 part 3
Bugs found during unit and card testing

------------------------------------------------------------------------------------------
[1] gainCard(): Invalid toFlag not caught

Description: When calling gainCard() with an invalid toFlag, the function
  executes and returns with a success code.

Steps to Reproduce:
	1. Create a game with adequate supply of desired card
	2. Call gainCard() with toFlag = 4

Expected Results: returns error and no card is gained

Actual Results: returns success and card is added to discard

------------------------------------------------------------------------------------------
[2] buyCard(): Embargo tokens not enforced

Description: When a supply pile has embargo tokens and buyCard() is executed,
  there are no embargo-related actions taken.

Steps to Reproduce:
	1. Create a game with adequate supply of desired card
	2. Add embargo token to desired card
	3. Call buyCard()

Expected Results:
	- Desired card is added to discard (and supply decreased)
	- Curse card is added to discard (and supply decreased)
	- Embargo token is removed from supply pile

Actual Results:
	- Desired card is added to discard (and supply decreased) - OK
	- No curse cards are moved
	- No embargo tokens are changed
	
------------------------------------------------------------------------------------------
[3] smithy: Card not moved to played pile

Description: The smithy card is not moved from the player's hand to the played pile
  after the card is executed.

Steps to Reproduce:
	1. Create a game with smithy card in current player's hand
	2. Call cardEffect() with smithy card and hand position

Expected Results: smithy card is removed from hand and added to played

Actual Results: smithy card remains in hand

------------------------------------------------------------------------------------------
[4] smithy: Draws too many cards

Description: The smithy card removes 4 cards from the player's deck rather than 3.

Steps to Reproduce:
	1. Create a game with smithy card in current player's hand
	2. Record current deck count
	3. Call cardEffect() with smithy card and hand position

Expected Results: 
	- Deck count is reduced by 3 cards
	- Hand count is increased by 2 cards (+3 drawn, -1 smithy)

Actual Results: 
	- Deck count is reduced by 4 cards
	- Hand count is increased by 3 cards

------------------------------------------------------------------------------------------
[5] adventurer: Card not moved to played pile

Description: The adventurer card is not moved from the player's hand to the played pile
  after the card is executed.

Steps to Reproduce:
	1. Create a game with adventurer card in current player's hand
	2. Call cardEffect() with adventurer card and hand position

Expected Results: adventurer card is removed from hand and added to played

Actual Results: adventurer card remains in hand

------------------------------------------------------------------------------------------
[6] adventurer: Non-treasure cards not discarded

Description: The adventurer card moves all revealed cards to the player's hand rather
  than placing non-treasure cards in discard pile.

Steps to Reproduce:
	1. Create a game with adventurer card in current player's hand
	2. Ensure deck contains 2 treasure cards after some non-treasure cards
	3. Call cardEffect() with adventurer card and hand position

Expected Results:
	- 2 treasure cards are added to hand
	- Non-treasure cards revealed from deck are moved to discard

Actual Results: 
	- 2 treasure cards are added to hand - OK
	- Non-treasure cards revealed from deck are added to hand

------------------------------------------------------------------------------------------
[7] adventurer: Hangs when <2 treasure cards exist

Description: If the adventurer card is executed when less than 2 treasure cards exist,
  an infinite loop is created.

Steps to Reproduce:
	1. Create a game with adventurer card in current player's hand
	2. Ensure deck contains 1 or 0 treasure cards
	3. Call cardEffect() with adventurer card and hand position
	
Expected Results: 0 or 1 treasure cards from deck added to player's hand

Actual Results: program hangs

------------------------------------------------------------------------------------------
[8] adventurer: Treasure card in discard pile not found

Description: Adventurer card can only find treasure cards placed in deck. It should be
  able to shuffle in discard pile and find treasure cards there as well.

Steps to Reproduce:
	1. Create a game with adventurer card in current player's hand
	2. Ensure deck contains 1 treasure card and discard contains 1 treasure card
	3. Call cardEffect() with adventurer card and hand position

Expected Results: 2 treasure cards (1 from deck, 1 from discard) added to player's hand

Actual Results: program hangs

------------------------------------------------------------------------------------------
[9] council_room: Draws too many cards

Description: The council_room card removes 5 cards from the player's deck rather than 4.

Steps to Reproduce:
	1. Create a game with council_room card in current player's hand
	2. Record current deck and hand count
	3. Call cardEffect() with council_room card and hand position

Expected Results: 
	- Deck count is reduced by 4 cards
	- Hand count is increased by 3 cards (+4 drawn, -1 council_room)

Actual Results: 
	- Deck count is reduced by 5 cards
	- Hand count is increased by 4 cards
	
------------------------------------------------------------------------------------------
[10] council_room: Drawn cards are not from player's deck

Description: The cards added to player's hand do not match those removed from the
  player's deck.

Steps to Reproduce:
	1. Create a game with council_room card in current player's hand
	2. Stack the deck with known cards (all copper)
	3. Call cardEffect() with council_room card and hand position

Expected Results: Cards in hand are same cards from deck (all copper)

Actual Results: Cards in hand do not match cards from deck (e.g. estate, curse)

------------------------------------------------------------------------------------------
[11] council_room: Opponents do not draw card

Description: There is no change to opponent's deck or hand to indicate a draw occurred.

Steps to Reproduce:
	1. Create a game with more than 1 player and council_room card in current player's hand
	2. Record other player's deck and hand counts
	3. Call cardEffect() with council_room card and hand position

Expected Results: 
	- Other player's deck count is reduced by 1 card
	- Other player's hand count is increased by 1 card

Actual Results: 
	- No change in other player's deck count
	- No change in other player's hand count
	
------------------------------------------------------------------------------------------
[12] council_room: Number of buys not incremented

Description: There is no change in the number of buys.

Steps to Reproduce:
	1. Create a game with council_room card in current player's hand
	2. Confirm current numBuys = 1
	3. Call cardEffect() with council_room card and hand position

Expected Results: numBuys incremented to 2

Actual Results: numBuys remains 1

------------------------------------------------------------------------------------------
[13] baron: Card not moved to played pile

Description: The baron card is not moved from the player's hand to the played pile
  after the card is executed.

Steps to Reproduce:
	1. Create a game with baron card in current player's hand
	2. Call cardEffect() with baron card and hand position

Expected Results: baron card is removed from hand and added to played

Actual Results: baron card remains in hand

------------------------------------------------------------------------------------------
[14] baron: Estate card removed from supply twice

Description: The supplyCount for estate is decreased by 2, but only 1 estate card is 
  added to discard pile

Steps to Reproduce:
	1. Create a game with baron card in current player's hand
	2. Call cardEffect() with baron card and hand position

Expected Results:
	- 1 estate card is added to discard pile
	- Supply count for estate card is decreased by 1

Actual Results: 
	- 1 estate card is added to discard pile - OK
	- Supply count for estate card is decreased by 2

------------------------------------------------------------------------------------------
