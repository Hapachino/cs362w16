/*

Kyle Johnson
johnsky3
CS362
2/28/16

Bugs in Teammates' Code for Assignment 5

All tests were run using the Make command for total of 10 tests
- make unittestresults.out, randomtestadventurer.out, randomtestcard.out

*****************************************************************************************
Teammate Ava Jacoba
*****************************************************************************************

Bug 1: Smithy card gives player 1 extra card in hand.
Found with card test 1:

hand count = 8, expected = 7
FAILED - player hand count does not match

Bug 2: Smithy card removes 1 extra card from the player deck.
Found with card test 1:

deck count = 1, expected = 2
FAILED - player deck count changed

Bug 3: Deck and hand counts are incorrect after playing the adventurer card.
Found with card test 2 and randomtestadventurer:

hand count = -1139, expected = 6
FAILED - player hand count does not match
deck count = 0, expected = 3
FAILED - player deck count changed

hand count = -98, expected = 13
deck count = 144, expected = 19

Bug 4: Playing adventurer card does not increment played card count.
Found with card test 2 and randomtestadventurer:

played card count = 0, expected = 1
FAILED - played card count does not match

Bug 5: After playing the village card, the player has an extra card in hand and
the next player loses a card from their hand.
Found with card test 3 and randomtestcard:
Player
hand count = 13, expected = 14
Next Player
hand count = 2, expected = 1

Results Summary (10,000 runs):
-------------------------------------------
Player hand count failures: 10000
Player deck count failures: 0
Next player hand count failures: 10000
Next player deck count failures: 0
Played card count failures: 0
Action point count failures: 0
Victory card supply failures: 0

*****************************************************************************************
Teammate Josh Ribera
*****************************************************************************************

Bug 1: Smithy gives 1 less card to player than expected.
Found with card test 1:

hand count = 6, expected = 7
FAILED - player hand count does not match

Bug 2: Smithy card deck count is 1 higher than expected after playing the card.

deck count = 3, expected = 2
FAILED - player deck count changed

Bug 3: Playing smithy card does not increment played card count as expected.
Found with card test 1:

played card count = 0, expected = 1
FAILED - played card count does not match

Bug 4: Player deck count is higher than expected after playing the adventurer card.
Found with card test 2 and randomtestadventurer:

deck count = 4, expected = 3
FAILED - player deck count changed

Bug 5: Playing adventurer card does not increment played card count.
Found with card test 2 and randomtestadventurer:

played card count = 0, expected = 1
FAILED - played card count does not match

*/


