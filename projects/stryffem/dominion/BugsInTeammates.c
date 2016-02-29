/*	Author: 	Martin Stryffeler
	Filename:	BugsInTeammates.c
	Date:		2/28/2016

Justin Siddon
To run my tests on Justin's code required minor adjustment of my function calls to match his. 
Three bugs were found in total. One bug was found in two separate tests independently. 
There seem to be bugs in the scoreFor, village, and smithy functions.

Unit Tests
Unit Test 1 - updateCoins - Pass
Unit Test 2 - ScoreFor - Fail - Misses victory cards in the deck.
Unit Test 3 - isGameOver - Pass
Unit Test 4 - gainCard - Pass

Card Tests
Card Test 1 - Smithy - Fail - Draws one too many cards. Too few cards in deck, too many in hand.
Card Test 2 - Adventurer - Pass
Card Test 3 - Village - Fail - Gives three too many actions.
Card Test 4 - Steward - Pass

Random Tests
Random Village Test - Fail - Gives three too many actions.
Random Adventurer Test - Pass

Bug #1
Title: ScoreFor Miscounts Victory Cards in the Player's Deck
Project: Dominion

Type: Bug, major
Filename: dominion.c

Description: The scoreFor function misses victory cards in the deck when the discardCount is lower
than the deckCount. The bug is reproducible by filling the deck with victory cards and having fewer
cards in the discard pile than the deck. The function will only count deck cards up to the number of
discardCount, resulting in the player's score being lower than it should be.

Bug #2
Title: Village Card Gives Player Too Many Actions
Project: Dominion

Type: Bug, major
Filename: dominion.c

Description: When the village card is played, the player receives three too many actions. The bug
occurs every time that the village card is played. It is expected that the player's action count
will increase by two, but instead it increases by five.

Bug #3
Title: Smithy Draws Too Many Cards
Project: Dominion

Type: Bug, major
Filename: dominion.c

Description: When the smithy card is played, the player draws three cards. The bug occurs every 
time the smithy card is played. It is expected that two cards will be removed from the deck and
added to the hand, but instead, three cards are removed from the deck and added to the hand.




Onur Ozay
Running my tests on Onur's code required no adjustment due to the similarities in which we implemented our card functions.
Two bugs were found. One affecting the scoreFor function and another affecting the Adventurer function.

Unit Tests
Unit Test 1 - updateCoins - Pass
Unit Test 2 - ScoreFor - Fail - Misses victory cards in the deck.
Unit Test 3 - isGameOver - Pass
Unit Test 4 - gainCard - Pass

Card Tests
Card Test 1 - Smithy - Pass
Card Test 2 - Adventurer - Pass
Card Test 3 - Village - Pass
Card Test 4 - Steward - Pass

Random Tests
Random Village Test - Pass
Random Adventurer Test - Fail - Affects other players' hands and states, instead of the current player's. 
Symptoms: Wrong cards in player's hand (added cards should be treasures only), other players' hand count 
and deck count changed by adventurer cardEffect.

Bug #1
Title: ScoreFor Miscounts Victory Cards in the Player's Deck
Project: Dominion

Type: Bug, major
Filename: refactor.c

Description: The scoreFor function misses victory cards in the deck when the discardCount is lower
than the deckCount. The bug is reproducible by filling the deck with victory cards and having fewer
cards in the discard pile than the deck. The function will only count deck cards up to the number of
discardCount, resulting in the player's score being lower than it should be.

Bug #2
Title: Other Players Draw Cards when Adventurer is Played
Project: Dominion

Type: Bug, major
Filename: refactor.c

Description: When the adventurer card is played, the current player does not draw cards, but other
players do. The bug occurs every time adventurer is played. It is expected that the current player
will get two additional treasure cards, and other players will draw no cards. However, each other
player gets additional cards while the current player gets no cards.




Andrew Pierno
Running my tests on Andrew's code required no adjustment due to the similarities in which we implemented our card functions.
Two bugs were found. One occurs in the scoreFor function and another in the adventurer function.

Unit Tests
Unit Test 1 - updateCoins - Pass
Unit Test 2 - ScoreFor - Fail - Misses victory cards in the deck.
Unit Test 3 - isGameOver - Pass
Unit Test 4 - gainCard - Pass

Card Tests
Card Test 1 - Smithy - Pass
Card Test 2 - Adventurer - 	Adventurer hangs indefinitely. I suspect that the number of treasures drawn may not be 
							getting counted correctly, resulting in an infinite loop.
Card Test 3 - Village - Pass
Card Test 4 - Steward - Pass

Random Tests
Random Village Test - Pass
Random Adventurer Test - 	Adventurer hangs indefinitely. I suspect that the number of treasures drawn may not be 
							getting counted correctly, resulting in an infinite loop.

Bug #1
Title: ScoreFor Miscounts Victory Cards in the Player's Deck
Project: Dominion

Type: Bug, major
Filename: dominion.c (Old version pulled from GitHub history)

Description: The scoreFor function misses victory cards in the deck when the discardCount is lower
than the deckCount. The bug is reproducible by filling the deck with victory cards and having fewer
cards in the discard pile than the deck. The function will only count deck cards up to the number of
discardCount, resulting in the player's score being lower than it should be.

Bug #2
Title: Adventurer Hangs Indefinitely
Project: Dominion

Type: Bug, major
Filename: dominion.c (Old version pulled from GitHub history)

Description: Adventurer gets stuck and hangs indefinitely, crashing the game. The bug occurs every time
adventurer is played. The bug can be traced to a fault which causes the number of treasures found not to
be incremented. This results in adventurer getting stuck in an infinite loop.

*/
