/*	Author: 	Martin Stryffeler
	Filename:	BugFixes.c
	Date:		2/28/2016

Reported by Teammates
Bug #1
Reported by: Andrew Pierno
Title: Dominion Adventurer card fails to increment hand count correctly

Description of Fix: This bug causes one too many cards to be added to the player's
hand when adventurer is played. Andrew's bug report points out an off by one error
in the function's while loop, allowing the loop to draw one too many cards. 
Changing "<= 2" to a "< 2" fixed the bug.

Bug #2
Reported by: Justin Siddon
Title: Smithy doesn't increase the players hand total by the correct amount

Description of Fix: This bug causes too few cards to be drawn when the smithy is
played. Instead of drawing three cards, the player drawns only two. Justin's bug
report points out an off by one error in the function's for loop, causing one too
few cards to be drawn. Fixing the off by one error fixes the bug.


Bugs I Introduced
Bug #3
Title: Village sets available actions incorrectly

Description of Fix: Instead of incrementing the number of actions by two, this bug
causes the number of actions to be set to a seemingly unrelated number. Inspecting the
setting of numActions within the village function reveals the fault: numActions is
set relative to the number of coins rather than actions, resulting in the bug.
Setting numActions to numActions + 2 fixes the bug.

Bug #4
Title: Cutpurse skips player 0 when determining who is affected by the card

Description of Fix: A for loop is initialized to 1 rather than 0, causing player 0
to be skipped when determining who is affected by the cutpurse card. Fixing this for
loop by initializing i to 0 fixes the bug.


Bugs I Found
Bug #5
Title: ScoreFor Miscounts Victory Cards in the Player's Deck

Description of Fix: The scoreFor function, when calculating the score of cards in
the deck, iterates through the deck up to the discardCount, rather than the 
deckCount. This results in undercounting the deck score if the discardCount is lower,
or iterating into undefined territory if the discardCount is greater. Setting the
for loop to iterate up to deckCount fixes the bug.

*/
