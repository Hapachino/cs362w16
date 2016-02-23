Tanna Richardson
CS362 - Winter 2016
Assignment 5 Part 2
Bugs fixed in dominion.c

1. 	Bug Description: Smithy card draws incorrect number of cards
	Found By: teammate's testing
	Failure(s) Reported: handCount is 1 more than expected
						 deckCount is 1 less than expected
	Code Changes to Fix: In runSmithy(), changed for loop condition from 
	  (i = 0; i <= 3; i++) to (i = 0; i < 3; i++)

2.	Bug Description: Adventurer does not discard played card
	Found By: teammate's testing
	Failure(s) Reported: handCount is 1 more than expected
						 playedCardCount is 1 less than expected
	Code Changes to Fix: In runAdventurer(), added discardCard() call before
	  return statement; added handPos to runAdventurer() parameters so it was 
	  available for discardCard(). Parameter change effected function declaration
	  in dominion_helpers.h, function definition, and function call in cardEffect()
	  
3.	Bug Description: Adventurer does not discard non-treasure cards
	Found By: teammate's testing
	Failure(s) Reported: handCount is 3 more than expected (=extra non-treasure cards)
	Code Changes to Fix: In runAdventurer(), in else statement (for non-treasure cards)
	   added state->handCount[currentPlayer]--; to remove card from hand
	   
4.	Bug Description: Council_room draws too many cards for current player, does not
	  draw cards for other player
	Found By: teammate's testing
	Failure(s) Reported: current player's handCount is 1 more than expected
						 current player's deckCount is 1 less than expected
						 other player's handCount is 1 less than expected
						 other player's deckCount is 1 more than expected					 
	Code Changes to Fix: In runCouncilRoom() changed if conditional for other players
	   draw from ( i == currentPlayer ) to ( i != currentPlayer )
	   
4.	Bug Description: Council_room does not increment numBuys
	Found By: introduced intentionally in assignment 2
	Failure(s) Reported: numBuys 1 less than expected					 
	Code Changes to Fix: In runCouncilRoom() changed numBuys modification from
	   state->numBuys = 1 to state->numBuys++

5.	Bug Description: Smithy trashes card instead of adding to played pile
	Found By: introduced intentionally in assignment 2
	Failure(s) Reported: playedCardCount is 1 less than expected
	Code Changes to Fix: In runSmithy() changed trash flag in discardCard() call
	   from 1 to 0
	   
6.	Bug Description: Mine mixes choice 1 and 2 options
	Found By: introduced intentionally in assignment 2
	Failure(s) Reported: not found in testing
	Code Changes to Fix: In runMine() switch all choice 1 to choice 2 and vice versa
	   