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
Bug report on Kyle's:
Bug 2:
Date : 2 / 20 / 2016
Reported By : Ava Petley
email : petleya@oregonstate.edu

File: dominion.c
Function: Adventurer
	Description: Two tests revealed an error with the adventurer card, cardtest4 and randomtestadventurer. The error is that not 		enough treasure cards are being added to the players hand.
	
	cardtest4:
		expected: two treasure cards to be added to players hand
	    	actual: players hand is short cards after play
	randomtestadventurer:
		expected: two treasure cards to be added to players hand   
		actual: incorrect number of treasure cards added.  
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
