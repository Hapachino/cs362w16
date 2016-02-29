Bug report on Kyle's:
Bug 1:
Date: 2/20/2016
Reported By: Ava Petley
email: petleya@oregonstate.edu

File: dominion.c
Function: smithy
  Description: Two tests revealed an error with smithy function. The test are cardtest1 and randomtestcard. 
	  The handcount of the current player is incorrect and another players status is effected
	cardtest1: 
		expected: hand to increase by 2 after 3 cards are added and one is discarded.
		actual : the hand count remained the same( 5 before and 5 after)
	randomtestcard:
		expected: current players hand to increase by 2 and other players hand to not be effected
		actual: the players hands not increased by the correct amount the hand count is too low
		          the other players status has been effected.		
***********************************************************************************************************************************
Bug report on Kyle's:
Bug 2:
Date : 2 / 20 / 2016
Reported By : Ava Petley
email : petleya@oregonstate.edu

File: dominion.c
Function: Adventurer
  Description: Two tests revealed an error with the adventurer card, cardtest4 and randomtestadventurer. The error is that not 		        enough treasure cards are being added to the players hand.
	cardtest4:
		expected: two treasure cards to be added to players hand
	  actual: players hand is short cards after play
	randomtestadventurer:
		expected: two treasure cards to be added to players hand   
		actual: incorrect number of treasure cards added.  
**************************************************************************************************************************************
Bug Report on Kyle's:
Bug 3:
Date 2/20/2016
Reported By:Ava Petley
email: petleya@oregonstate.edu

File: dominion.c
Function: village
	Description: an error was discoved with the village function actions were not added
	cardtest2:
		expected: 2 actions to be added
		actual: actions not added
**************************************************************************************************************************************
Bug report on Josh's:
Bug 1:
Date: 2/20/2016
Reported By: Ava Petley
email: petleya@oregonstate.edu

file: dominion.c
function: adventurer
  Description: two tests found errors in the adventurer function
	cardtest4:
		expected: two treasure cards to be added to hand and the players hand to increase by 1 because two cards are added and 		one is        discard.
		actual: players hand not increased correctly
	randomtestadventurer:
		expected: two treasure cards are added to the players hand. No drawn treasure cards are discarded. Players hand is 			increase        by one.
		actual: some treasure cards are being discarded. The hand count is not changing and the incorrect number of treasure 			cards         are added.
**************************************************************************************************************************************
Bug report on Josh's
Bug 2:
Date: 2/20/2016
Reported By: Ava Petley
email: petleya@oregonstate.edu

file: dominion.c
function: smithy
  discription: randomcardtest found some errors with the smithy function.
	randomcardtest:
		expected: current players hand to increase by 2 since 3 are added and 1 is discarded. Other players hands are not 			effected.
		actual: the other players hand count is increased. the other players deck and discard piles are also effected.
**************************************************************************************************************************************
Bug report on Josh's
Bug 3:
Date: 2/20/2016
Reported By: Ava Petley
email: petleya@oregonstate.edu

file: dominion.c
function: steward
	description: cardtest3 found an error with the steward function
	  expected: handcount to increase by one. Coins increases by 2.
	actual: hand count not adjusted correctly.

************************************************************************************************************************************
Test Results: fragments of the results for each test on Kyle's code:
unittest1 on updateCoins:
	no errors
unittest2 on discardCard:
	no error
unittest3 on gainCardL
	no error
unittest4 on isGameOver:
	Pass: game not ended correctly identified
	Pass: Correctly identified end of game due to provinces out
	Pass: Correctly identified end of game for three piles empty
cardtest1 on smithy:
	Fail: The players hand should be increase by 2, 3 added 1 discarded
	hand Count: 5 hc:5
cardtest2 on village:
	Pass: the hand count doesn't change
	Fail: actions should be added
cardtest3 on steward:
	no error
cardtest4 on adventurer:
	Pass: no treasure cards were discarded
	Fail: The player hand increases by at least one card
randomtestcard
	Fail: The players hand not increased by the correct amount
	hand count is too low. should increase by two
	Fail: The other players status have been effected
randomtestadventurer:
	Fail: incorrect number of treasure cards added
	Fail: handcount is : 9 and hcbefore is 8
************************************************************************************************************************************
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

