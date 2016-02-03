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
player's coins. To test this I made a copy of the game state, called the
function, and compared the new results to a copy of the original gamestate.
Each of these tests passed successfully.

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
numHandCards takes a pointer to a struct gameState as an argument and returns
the number of cards currently in the player's hand.

Test Findings:
The condition for the first test assessed the value of the number of cards
in each player's hand. Cards are delt at the beginning of a new turn,
therefore only the first player has cards in the hand pile after
initialization. There are five cards delt, so the active player should
initially have 5 cards while the non-starting player should have zero cards.
Tests were conducted by initializing the game state, calling the numHandCards
with the gameState and comparing it to five. In the case of the alternate player,
I set the whoseTurn value to 1, and ran the function again. The results of these
tests were 5 and 0 respectively, therefore these tests passed successfully.

The secondary test checked the player's hand cards and ensured that the five
cards placed in the player's hand pile were active cards for the game. In
order to do this, I checked each of the cards to ensure they are not set to -1,
indicating the card is inactive during this iteration of the game.

--------------------------- NON CARD - UNIT TEST 3 ---------------------------
Name: gainCard
Parameters:
	- int supplyPos
	- struct gameState *state
	- int toFlag
	- int player
Return Type: int

Description: 
gainCard takes a specified card to be added, a flag indicating which pile to
add the card, and a player that will receive the card as parameters. As long
as the supply is available, the card is then added to the specified pile.

Test Findings:
The toFlag option presents an opportunity to provide three different options
to the function and compare the results to ensure the card was added to the
correct pile. To do so, I passed similar values to the gainCard function, only
changing the toFlag value. Using each value, I added a smithy card to the deck
and compared two items for each iteration: (1) I checked to see if the deck
count was incremented by one and (2) that the specified card was on top of the
selected deck. Each of these tests passed.

During the first set of conditions, I also checked to see if the supply count
for smithy was decremented by one. I did this by comparing the supply count
for smithy in the tested version against the supply count for smithy in the
original version. All other supply positions were checked to ensure they 
remain unchanged in the process.

While continuing to use the same game state for testing purposes, I conducted
the tests on a specified player, which means the other player should not have
a change in any pile. These tests passed. To verify these, I used helper
functions in testTools.c to verify that each of the card piles for player 2
were the same in the original game state and the modified game state. Each of
these tests passed successfully.

Finally, the gainCard function should not add a card to the any pile if the
supply value for the specified card is not at least 1. I reset the game state
and set the supply value for the smithy card to 0. After running gainCard
for smithy, it was identified that the entire game state did not change, and
therefore the test passed.

--------------------------- NON CARD - UNIT TEST 4 ---------------------------
Name: updateCoins
Parameters:
	- int player
	- struct gameState *state
	- int bonus
Return Type: int

Description:
Update coins takes an index specifying a player, a game state, and an index
specifying the number of bonus coins to add, and adds them to the coin 
attribute for the game state.

Test Findings:
The primary options and branches for this function come from the types of
cards in the player's hand. In order to test each branch, I tested a hand
combination that included each of the type of treasure cards: copper, silver,
and gold. Each of the resulting values passed the tests in this case.

I tested the hand count aspect of the function by testing a valid coin value
from a combination of cards then reducing the hand count by one. The
function passed the test by including the same amount of coins in the 
previous attempt minus the value of the card at the top of the hand.

Another variable feature of the function is in the bonus attribute, and I
tested a value in the bonus section in conjunction with treasure cards. The
resulting value with the bonus attribute in play also passed.

Each of these changes in card combinations uses accessor methodology to
calculate the coins, which means that the card piles themselves should not
change. I checked the values of each card pile after the completion of
previous tests to ensure nothing was modified. These tests also passed
successfully.

----------------------------- CARD - UNIT TEST 1 -----------------------------
Name: smithy
Parameters:
	- int currentPlayer
	- struct gameState *state
	- int handpos
Return Type: int

Description:
The smithy card and smithyEffect function discards the smithy card from the
player's hand and draws 3 cards to be added to the player's hand.

Test Findings:
The basic functionality of smithy is simple to test. The first condition is
that the smithy card is removed from the player's hand and overall count is
decremented by one. However, the function also adds three cards, so hand
count detection must incorporate both the add and remove at the same time for
a net gain of +2 cards. I made a copy of the game state before running the
function and found that at the end the overall number of cards in the player's
hand was not +2, therefore an error is identified in the overall exchange
between the three drawcard functions or the discard function.

Given that the hand count was 1 greater than expected after the smithy function
call, I tested the top card on the pile to find that it was legitimately
taken from the deck. This implies that a fourth card is drawn from the deck.

I tested the supply counts for all cards, and none of them were checked. I did
this by looping over each of the cards, comparing their values to the value of
the backup copy, and found that they all remained the same, so this test
passed successfully.

I also checked the second player's decks to ensure that none of the cards were
modified. These tests passed and were verified by using the help function that
compares all cards in a deck to the same deck of the backup copy taken before
the function call.

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
Adventurer allows the player to reveal the deck one card at a time until two
treasure cards are shown. The non-treasure cards are placed into the player's
discard deck and the treasure cards are added to the player's hand.

Test Findings:
The first test case assesses whether or not the non-treasure cards are added
to the discard pile. In order to determine this, I cycle from the top of the
deck to the bottom of the deck to determine how many cards must be added to the
discard pile and what cards will be added. To test the condition, I compare
the results of the game state modified by calling the function. In looking at
the discard pile, it did successully contain the additional cards removed from
the deck while looking for two adventure cards.

The second test case checks the player's hand to determine if the two treasure
cards are added to the player's hand. Looking at the top two positions of the
player's hand, I identified that in fact were not the new adventure cards. During
this phase I also check to see if the handCount for the modified game state is
appropriately incremented by two and it is not.

In order to verify consistency, both the other player's deccks and the supply
decks were compared to the original version to ensure nothing changed, and these
tests passed as the decks remained unmodified.

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
Village adds one draw card, two actions, and discards the village card from
the player's hand to the discard deck.

Test Findings:
Testing the total hand count for the player proved challenging since there are
two operations of add/remove on cards that offset each other. The first test
I conducted checked to see if the drawn card placed on top of the player's
hand was the card on top of the original deck. This test passed and I was able
to verify by comparing the backup copy of the game state deck to the modified
game state player hand.

The second test checks that two actions are added to the game state. This was
compared directly by looking at the new game state's numActions attribute
and comparing it to the original game state's numActions attribute. This test
did not pass accordingly as the results were not 2 additional actions.

The third test checked to ensure that the village card was removed from the
player's hand and placed on the discard pile. This test passsed successfully
verified by comparing the modified game state's discard pile as well as both
versions of the game state's player  hand.

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
Remodel allows you to trash a card from your hand and gain a card up to 2 coins
more than the trashed card.

Test Findings:
The first condition for remodel is to check that the chosen trash card is removed
from the player's hand if a valid call to the function is made. This test passed
and verified by the comparison of attributes between game states.

The second condition I tested was that the game state should not change if an
invalid submission is made. This test is produced by attempting to trash a
card and choose a card that is more than two in value compared to the trashed
card. This test was successful and the game state did not change as the function
exited with an error.

The third condition checks to see if the new card is added to the player's deck.
This was conducted successfully as well as checking to see if the trashed card
was removed from the player's hand and placed in the discard pile.
