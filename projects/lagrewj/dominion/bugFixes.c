Jonathan Lagrew
CS362 Winter 2015
Assignment 5

BugFixes.c



/**********************************
teammate1Dominion - Nancy Chan
**********************************/


	unittest1: updateCoins()
		All tests passed.

	unittest2: fullDeckCount()
		All tests passed.

	unittest3: isGameOver()
		All tests passed.

======================================================
Bug 1 Nancy Chan - scoreFor() Testing
======================================================

Nancy's Bug report:

unittest4: scoreFor()
		***Bug found***
		2/2 tests failed.
		Scores do not equal expected values:

		----------------- Test 1 - Player 0:
		Adding the following to discard:
		    1 duchy
		    2 provinces
		    5 great halls
		    4 gardens
		    2 curses
		deckCount: 5
		discardCount: 14
		handCount: 5
		Player 0 score: 22, expected: 29

		----------------- Test 2 - Player 1:
		No changes and all cards in deck:
		deckCount: 10
		discardCount: 0
		handCount: 0
		Player 1 score: 0, expected: 3
		
Summary for fixing bug:

Nancy's bug report showed that the two tests ran for scoreFor() were not counting the score correctly. Upon further reviewed
in GDB, by stepping through the function, it was shown that fullDeckCount() was using the number of curses and not correctly
counting the number of gardens. The for loops in discard and deck are using discardCount for the player instead of deckCount for 
the player. Using GDB, the printing of fullDeckCount(player, 10, state) / 10 prints 0 because the numerator would only be 4/10, 
equaling 0. Since I did not refactor this function, this testing was quite extensive in GDB. However, after further research
and testing, I broke out the scoring for the gardens to correctly account for the proper way to score the garden cards in the 
hand and in the discard pile. 

Changes to code:
Before: Change1: i < state->discardCount[player]
		
		Change2: 
		//commented out this statement and added the below in after change 2. 
		if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };

After: Change1: i < state->deckCount[player]
	   
	   Change2: 
		  //counting the amount of gardens 
		  gardenCount = fullDeckCount(player, 10, state);
		  //discard plus hand are part of the complete deck count after the game is over
		  completeDeckCount = state->handCount[player] + state->discardCount[player] + state->deckCount[player];
		  //garden is worth 1 victory point per 10 cards in deck, always rounded down 
		  gardenCardEffect = (completeDeckCount / 10) * gardenCount;
		  //score plus the new garden card effect score
		  score = score + gardenCardEffect;

======================================================
Bug 2 Nancy Chan - Smithy Testing
======================================================

Nancy's Bug report:

cardtest1: smithy
		Changes in my test to match teammate's refactored code:
			- changed playSmithy(p, &G, 5); to playSmithy(&G, 5);
		***Possible bug found***
			Given a deck of 10 cards, an empty discard pile, and a hand of 6 cards that includes smithy,
			3 cards are correctly drawn from the deck and added to the hand. However, the played smithy
			card is not added to the discard pile which remains empty. Whether or not this is an actual
			bug is up for debate as discussed here: https://piazza.com/class/iip31fywxe72b0?cid=103
			It is unclear if discardCard() should be true to its name and actually put a card in the
			discard pile as it may be the case that this happens in endTurn() instead.
			
Summary for fixing bug:
	In GDB, I set a breakpoint to step through the function and found the bug in the disCard function where the flag was set
	to 1 which would not properly discard the smithy after being played. Changing this to 0 fixed the bug. 
	
Changes to code:
	
Before:
		//discard card from hand
	discardCard(handPos, currentPlayer, state, 1);
After:
	//discard card from hand
	discardCard(handPos, currentPlayer, state, 0);


======================================================
Bug 3 Nancy Chan - Adventurer Testing
======================================================
Nancy's Bug report:

cardtest2: adventurer
		Changes in my test to match teammate's refactored code:
			- changed playAdventurer(&testG, p); to playAdventurer(&testG);

		***Bug found***
			The adventurer card works correctly when there are treasure cards at the top of the deck.
			However, when the treasure cards are interspersed through the deck or at the bottom of the deck,
			the number of cards in the discard pile is one fewer than expected.

Summary for fixing bug:

Nancy's test shows that the function is working correctly only when there are 2 treasure cards on top. This means that there
is something incorrect with the discard function when you need to draw more than 2 cards total. By telling me that the number
of cards in the discard pile is one fewer than expected means that I initially wanted to test the while loop for discarding. 
This proved to be easy in GDB by setting a breakpoint at the while loop. Stepping through the function revealed that the 
loop was exiting one interation too early because of the "=" was taken out. Simply by adding that in there, this fixed the bug.

Changes to code: 
Before:

while(z-1>0){
		state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;
	}
After: 

while(z-1>=0){
		state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;
	}


======================================================
Bug 4 Nancy Chan - Cutpurse Testing
======================================================
Nancy's Bug report:

	cardtest3: cutpurse
		Changes in my test to match teammate's refactored code:
			- changed playCutpurse(p, &testG, 5); to cardEffect(cutpurse, 0, 0, 0, &testG, 5, 0);
		***Bug found***
			3/4 tests passed.
			3 tests passed: 4 hands with coppers, 3 hands with coppers, 2 hands with coppers.
			1 test failed: One of the players has zero coppers.
			Check if satisfied condition for revealing cards
			(j == handCount):
			j = 9, handCount: 10
			----------------- TEST FAILED!
			Playing the cutpurse card when all players have coppers in their hands results in all tests passing.
			Each other player correctly discards a copper.
			A bug appears when one of the players has a hand with no coppers.
			In this case, the player with no coppers to discard should be revealing his hand. The code to reveal cards
			in the hand is executed when (j == state->handCount[i]). However, j does not increment enough to satisfy
			that condition.

Summary for fixing bug:
In GDB I stepped through the function and noticed that the if conditional in the reveal only stepped through if debugging was turned on.
Removing this conditional allows for Nancy's bug to be resolved. 

Before:

			  if (j == state->handCount[i])
		    {
		      for (k = 0; k < state->handCount[i]; k++)
			{
			  if (DEBUG)
			    printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
			}	
		      break;
		    }

After:

		  if (j == state->handCount[i])
		    {
		      for (k = 0; k < state->handCount[i]; k++)
			{
			  //if (DEBUG) commenting this out allows only if debugging is on 
			    printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
			}	
		      break;
		    }

======================================================
Bug 5 Nancy Chan - Remodel Testing
======================================================
Nancy's Bug report:

cardtest4: remodel
		Changes in my test to match teammate's refactored code:
			- changed playRemodel(state, p, 1, toTest[i], 0); to cardEffect(remodel, 1, toTest[i], 0, state, 0, 0);

		***Bug found***
			choice1 is the card to trash
			choice2 is the card to gain
			Remodel makes the player trash a card to gain a card costing up to 2 more coins than the trashed card.
			A successful trash for gain returns 0. If unsuccessful, it returns -1.

			Most of the tests failed. Here are a few examples:
				choice1 cost: 2, choice2 cost: 2
				Result: -1, Expected: 0

				choice1 cost: 2, choice2 cost: 3
				Result: -1, Expected: 0

				choice1 cost: 2, choice2 cost: 4
				Result: 0, Expected: 0

				choice1 cost: 2, choice2 cost: 5
				Result: 0, Expected: -1

				choice1 cost: 2, choice2 cost: 6
				Result: 0, Expected: -1

Summary for fixing bug:
In GDB, the breakpoints I set didn't add any insight into where this bug was coming from. So, I dove deeper into the getCost and
gainCard functions with no luck there either. There has been a bug mentioned on the forums related to the discards not 
accurately working. I was unable to fix this bug. 

	
======================================================
Bug 6 Nancy Chan - random testing Adventurer
======================================================
Nancy's Bug report:

randomtestadventurer:
		Changes in my test to match teammate's refactored code:
			- changed playAdventurer(&testG, p); to playAdventurer(&testG);
		***Bug found***
			Discard count and hand count are incorrect when there are no treasures in the deck.
			----------------- Random Deck Test 2
			----------------- Initial counts
			DECK
			Position 0, Card: 14
			Position 1, Card: 10
			Position 2, Card: 11
			Position 3, Card: 22
			Position 4, Card: 11
			Position 5, Card: 12
			Position 6, Card: 13
			Position 7, Card: 14
			Position 8, Card: 11
			Position 9, Card: 10
			DISCARD
			HAND
			Position 0, Card: 1
			Position 1, Card: 1
			Position 2, Card: 1
			Position 3, Card: 1
			Position 4, Card: 1
			----------------- After playAdventurer
			DECK
			Deck count: 0, Expected: 0
			DISCARD
			Position 0, Card: 1
			Position 1, Card: 1
			Position 2, Card: 1
			Position 3, Card: 1
			Position 4, Card: 1
			Position 5, Card: 1
			Position 6, Card: 14
			Position 7, Card: 10
			Position 8, Card: 11
			Position 9, Card: 22
			Position 10, Card: 11
			Position 11, Card: 12
			Position 12, Card: 13
			Position 13, Card: 14
			Position 14, Card: 11
			Discard count: 15, Expected: 10
			----------------- TEST FAILED!
			HAND
			Hand count: -1, Expected: 5
			----------------- TEST FAILED!

Summary for fixing bug:
Bug was identified in first adventurer test and was due to my refactored code. Already fixed. 

======================================================
Bug 7 Nancy Chan - Random testing adventurer
======================================================
Nancy's Bug report:

	***Possible bug found***
			Discard count is off by one.
			----------------- Random Deck Test 1
			----------------- Initial counts
			DECK
			Position 0, Card: 13
			Position 1, Card: 4
			Position 2, Card: 11
			Position 3, Card: 21
			Position 4, Card: 6
			Position 5, Card: 6
			Position 6, Card: 12
			Position 7, Card: 21
			Position 8, Card: 22
			Position 9, Card: 4
			DISCARD
			HAND
			Position 0, Card: 1
			Position 1, Card: 1
			Position 2, Card: 1
			Position 3, Card: 1
			Position 4, Card: 1
			----------------- After playAdventurer
			DECK
			Position 0, Card: 13
			Position 1, Card: 4
			Position 2, Card: 11
			Position 3, Card: 21
			Position 4, Card: 6
			Deck count: 5, Expected: 5
			DISCARD
			Position 0, Card: 12
			Position 1, Card: 21
			Discard count: 2, Expected: 3
			----------------- TEST FAILED!
			HAND
			Position 0, Card: 1
			Position 1, Card: 1
			Position 2, Card: 1
			Position 3, Card: 1
			Position 4, Card: 1
			Position 5, Card: 4
			Position 6, Card: 6
			Hand count: 7, Expected: 7

Summary for fixing bug:
This was due to the refactored code of not discarding correctly. Bug fixed. 

======================================================
Bug 8 Nancy Chan - Random testing remodel
======================================================

	randomtestcard:
		Changes in my test to match teammate's refactored code:
			- changed playRemodel(&testG, p, trashIndex, gainCard, 0); to cardEffect(remodel, 1, toTest[i], 0, &testG, 0, 0);

		***Bug found***
			Sometimes, playing the remodel card results in a correct return value. Other times, remodel does a trash for gain
			when the card to gain has a value that is more than 2 coins the value of the card being trashed. Additionally,
			remodel may fail to trash a card to gain a card that the player is eligible to gain.

			Random Test 30
			choice1 cost: 3, choice2 cost: 6
			Result: 0, Expected: -1

			Random Test 993
			choice1 cost: 6, choice2 cost: 3
			Result: -1, Expected: 0
			
			Random Test 994
			choice1 cost: 5, choice2 cost: 4
			Result: -1, Expected: 0

			Random Test 995
			choice1 cost: 5, choice2 cost: 3
			Result: 0, Expected: 0


	
Summary for fixing bug:
As with the initial testing of remodel, this bug was not fixed. I could not pin point the exact cause of this error. 	

			
			
/**********************************
teammate2Dominion - Andrew Calhoun 
**********************************/


======================================================
Bug 1 Andrew Calhoun - Adventurer
======================================================

Andrew's bug report: 

cardTest1:
    playAdventurer():
    Jon's does not properly draw a card if the proper conditions are met. (drawnTreasure > 2)

Summary for fixing bug:
Andrew's test found that there were issues with the discarding when more than 2 cards were drawn. Nancy's test did a better job of pin pointing the exact cause. 

======================================================
Bug 1 Andrew Calhoun - Smithy
======================================================

Andrew's bug report: 

 cardTest2:
    playSmithy():
    I had to refactor my card to work with Jon's version. Compared to my code, Jon's did not return the expected number of cards. The expected value is always one higher than the result.

Summary for fixing bug:
This test correctly identified the smithy bug introduced in the refactoring. 

======================================================
Bug 1 Andrew Calhoun - Random Testing Adventurer
======================================================

Andrew's bug report: 

 RandomTestAdventurer:    playAdventurer()
    This identified the error, as causing too many cards to be drawn for the handCount and thus causing a failure.
    Further refactored my code to identify the exact issue -- results are always one greater than they should be. This
    is caused by the cards not discarding properly and being removed from the hand, from the tests being run.

Summary for fixing bug:
Andrew's test did pin point that the discard count was off by one but incorrectly identified that drawing too many
cards was the cause. This was due to the already stated refactored code. 

    
   
   
   
    





No issues found in Jon's version of Minion.