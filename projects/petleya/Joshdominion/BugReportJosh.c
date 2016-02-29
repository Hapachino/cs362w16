Bug report on Josh's:

Bug 1:
file: dominion.c
function: adventurer
description: two tests found errors in the adventurer function
	cardtest4:
		expected: two treasure cards to be added to hand and the players hand to increase by 1 because two cards are added and 		one is discard.
		actual: players hand not increased correctly
	randomtestadventurer:
		expected: two treasure cards are added to the players hand. No drawn treasure cards are discarded. Players hand is 			increase by one.
		actual: some treasure cards are being discarded. The hand count is not changing and the incorrect number of treasure 			cards are added.

Bug 2:
file: dominion.c
function: smithy
discription: randomcardtest found some errors with the smithy function.
	randomcardtest:
		expected: current players hand to increase by 2 since 3 are added and 1 is discarded. Other players hands are not 			effected.
		actual: the other players hand count is increased. the other players deck and discard piles are also effected.
		
Bug 3:
file: dominion.c
function: steward
	description: cardtest3 found an error with the steward function
	expected: handcount to increase by one. Coins increases by 2.
	actual: hand count not adjusted correctly.


results from tests for Josh's code: 

unittest1 on updateCoins:
	no errors
unittest2 on discardCard:
	no errors
unittest3 on gainCardL
	no errors
unittest4 on isGameOver:
	no errors
cardtest1 on smithy:
	pass
cardtest2 on village:
	Pass: the hand count doesn't change
	Pass: two actions added
cardtest3 on steward:
	Fail: Hand count not adjusted correctly
	Pass: The amount of coins increases by 2
cardtest4 on adventurer:
	Pass: no treasure cards were discarded
	Fail: The player hand increases by at least one card
randomtestcard
deck count before is: 8
dicard count before is 12
Pass: The correct hand count
Fail: The other players status have been effected
The other players hand count is 19 it should be 17
The other players deck was effected it is 5 and it should be 6
The other players discard pile was effect it is 12 and it should be 6
deck count before is: 14
dicard count before is 6
Pass: The correct hand count
Fail: The other players status have been effected
The other players hand count is 21 it should be 19
The other players deck was effected it is 11 and it should be 12
The other players discard pile was effect it is 6 and it should be 12
deck count before is: 1
dicard count before is 19
Pass: The correct hand count
Fail: The other players status have been effected
The other players hand count is 23 it should be 21
The other players deck was effected it is 17 and it should be 6
The other players discard pile was effect it is 0 and it should be 6
deck count before is: 15
dicard count before is 5
Pass: The correct hand count
Fail: The other players status have been effected
The other players hand count is 25 it should be 23
The other players deck was effected it is 12 and it should be 0
The other players discard pile was effect it is 5 and it should be 0

randomtestadventurer:
deck count before is: 16
dicard count before is 4
Treasure card found in discard 6
Fail: incorrect number of treasure cards added
Fail: a treasure card was discarded
Fail: handcount is : 5 and hcbefore is 5
in hand position 0 card 4
in hand position 1 card 4
in hand position 2 card 4
in hand position 3 card 4
in hand position 4 card 4
deck count before is: 14
dicard count before is 6
Treasure card found in discard 4
Fail: incorrect number of treasure cards added
Fail: a treasure card was discarded
Fail: handcount is : 5 and hcbefore is 5
in hand position 0 card 4
in hand position 1 card 4
in hand position 2 card 4
in hand position 3 card 4
in hand position 4 card 4
deck count before is: 8
dicard count before is 12
Treasure card found in discard 4
Treasure card found in discard 6
Fail: incorrect number of treasure cards added
Fail: a treasure card was discarded
Fail: handcount is : 5 and hcbefore is 5
in hand position 0 card 4
in hand position 1 card 4
in hand position 2 card 4
in hand position 3 card 4
in hand position 4 card 4
deck count before is: 19
dicard count before is 1
Treasure card found in discard 5
Fail: incorrect number of treasure cards added
Fail: a treasure card was discarded
Fail: handcount is : 5 and hcbefore is 5
in hand position 0 card 4
in hand position 1 card 4
in hand position 2 card 4
in hand position 3 card 4
in hand position 4 card 4
deck count before is: 13
dicard count before is 7
Fail: incorrect number of treasure cards added
Fail: a treasure card was discarded
Fail: handcount is : 5 and hcbefore is 5
in hand position 0 card 4
in hand position 1 card 4
in hand position 2 card 4
in hand position 3 card 4
in hand position 4 card 4
deck count before is: 0
dicard count before is 20
Fail: incorrect number of treasure cards added
Fail: a treasure card was discarded
Fail: handcount is : 5 and hcbefore is 5
in hand position 0 card 4
in hand position 1 card 4
in hand position 2 card 4
in hand position 3 card 4
in hand position 4 card 4
deck count before is: 14
dicard count before is 6
Treasure card found in discard 6
Fail: incorrect number of treasure cards added
Fail: a treasure card was discarded
Fail: handcount is : 5 and hcbefore is 5
in hand position 0 card 4
in hand position 1 card 4
in hand position 2 card 4
in hand position 3 card 4
in hand position 4 card 4
deck count before is: 0
dicard count before is 20
Fail: incorrect number of treasure cards added
Fail: a treasure card was discarded
Fail: handcount is : 5 and hcbefore is 5

