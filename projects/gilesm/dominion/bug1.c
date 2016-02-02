--------------------------- NON CARD - UNIT TEST 1 ---------------------------
Name: buyCard
Parameters:
	- int supplyPos
	- struct gameState *state
Return Type: int

Description:

buyCard takes as parameters a specified card index and a pointer
to a struct gameState. The function purchases the card for the specified
player, decrementing the player's coins for the cost of the card, removes the
card from the state's card supply, and adds it to the player's discard deck.

Test Findings: 

The first set of tests were based on asserting successful 
conditions. Under successful conditions, it is expected that the card will be
removed from the supply deck and placed in the current player's discard deck.
It is also expected that the cost of the card will be decremented from the
player's coins. Each of these tests passed successfully.

The second condition tested is in the case that the player does not 
currently have enough coins to purchase the card. If the card costs more than
the player has available, the game state should not change at all and cycle
back to the buy phase. These test conditions also passed.
	
The third condition tested is if the function is run on a particular card
that has a supply count of 0 (or less). If the supply count is not greater
than or equal to 1, the game state should not change. This condition also
passed successfully.

The fourth condition tested if the function attempts to run when the
number of buys available is set to zero. In order to make a purchase, the
player must have at least one buy. If the function is called with zero buys,
the game state should not change. This test passed successfully.

--------------------------- NON CARD - UNIT TEST 2 ---------------------------
Name: numHandCards
Parameters:
	- struct gameState *state
Return Type: int

Description:

Test Findings:

--------------------------- NON CARD - UNIT TEST 3 ---------------------------
Name: gainCard
Parameters:
	- int supplyPos
	- struct gameState *state
	- int toFlag
	- int player
Return Type: int

Description:

Test Findings:


--------------------------- NON CARD - UNIT TEST 4 ---------------------------
Name: updateCoints
Parameters:
	- int player
	- struct gameState *state
	- int bonus
Return Type: int

Description:

Test Findings:


----------------------------- CARD - UNIT TEST 1 -----------------------------
Name: smithy
Parameters:
	- int currentPlayer
	- struct gameState *state
	- int handpos
Return Type: int

Description:

Test Findings:


----------------------------- CARD - UNIT TEST 2 -----------------------------
Name: adventurer
Parameters:
	- int currentPlayer
	- int drawntreasure
	- int cardDrawn
	- int temphand[]
	- struct gameState *state
Return Type: int

Description:

Test Findings:


----------------------------- CARD - UNIT TEST 3 -----------------------------
Name: village
Parameters:
	- int currentPlayer
	- int choice1
	- int choice2
	- struct gameState *state
	- int handpos
Return Type: int

Description:

Test Findings:


----------------------------- CARD - UNIT TEST 4 -----------------------------
Name: remodel
Parameters:
	- int currentPlayer
	- int choice1
	- int choice2
	- struct gameState *state
	- int handpos
Return Type: int

Description:

Test Findings:


