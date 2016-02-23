/*
 BugFixes.c
 by Matthew Meyn
 2016/2/22

------------------------------------------------------------------------------------
------------------------------------------------------------------------------------
------------------------------------------------------------------------------------

 Bug #1

 Title: Player's hand count increases by incorrect number when Smithy card is played

 Classification: Severe

 Platform: Linux

 Description:

    Playing the Smithy card results in a player drawing three additional cards, and

    then discarding the played card, resulting in an expected net increase of 2 cards

    in the player's hand. My test indicates that a player's hand count either increases

    by 3 or decreases by 1 after playing the Smithy card.



    The most common result is a change for +3 cards. The change of -1 occurs for player

    2 in a two player game and player 2 in a four player game. Player 4 in a four player

    game was the only condition that did not result in this error.

 Steps to reproduce:

    Inside teammate2dominion folder, run following commands:

        $ gcc dominion.c rngs.c cardFunctions.c cardtest1-2.c -o prog

        $ ./prog

------------------------------------------------------------------------------------

 FIX:

 The cases in which the player ended up with a hand count increase of 3 rather than 2
 are fairly straightforward to explain: line 26 in cardFunctions.c

 	 	 discardCard( currentPlayer, handPos, state, 1 );

 is improperly written. discardCard() takes the arguments

 	 	 int handPos, int currentPlayer, struct gameState *state, int trashFlag

 which means that in my implementation, currentPlayer and handPos were swapped.
 Therefore, discardCard() was attempting to operate on the wrong player's hand, so
 unless the current player and the hand position happened to be the same, the
 current player's hand would almost certainly not be affected by this funciton call.
 That means that the current player's hand count is never decremented as it should
 be decremented, and the player in effect keeps the smithy card in the player's hand
 and therefore has 3 more cards than before the card was played.

 The case in which the player's hand count becomes -1 is less obvious, but I believe
 I have traced it to the same bad function call. Because currentPlayer and handPos
 are in the wrong order, there is no guarantee the program is even modifying the
 hand of a player in the game; in fact it is certain, if handPos is greater than or
 equal to the number of players in the game, that the function will be writing
 beyond the bounds of the gameState->hand array-of-arrays.

 It appears that in a gameState structure, the handCount array immediately follows
 the hand array-of-arrays. So it is quite likely that if the value passed as
 currentPlayer is one more than the last player, the data that will be corrupted is
 the handCount array. It appears that in the test when the fourth player of four
 plays the card, the line

 	 	 state->hand[currentPlayer][handPos] = -1;

 which is line 1398 of dominion.c, assigns -1 to the handCount of the fourth player.
 The debugger confirms that at precisely this point in execution, the player's hand
 count becomes -1.

 The solution is simple: change the order of arguments in line 26 of
 cardFunctions.c to be:

 	 	 discardCard( handPos, currentPlayer, state, 1 );




 ------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------




 Bug #2

 Title: playedCardCount does not increase by 1 after Smithy card is played

 Classification: Severe

 Platform: Linux

 Description:

    After playing Smithy, the card is moved from the player's hand and into the played

    card pile as part of the discardCard() function in the call to Smithy. This should

    result in the playedCardCount being incremented by 1 after Smithy is played. My

    test results show that playedCardCount is not incremented after Smithy is played;

    it's value remains the same before and after Smithy is played.



    This error was present in all initial game conditions that were created prior to

    playing the Smithy card.

 Steps to reproduce:

    Inside teammate2dominion folder, run following commands:

        $ gcc dominion.c rngs.c cardFunctions.c cardtest1-2.c -o prog

        $ ./prog

 ------------------------------------------------------------------------------------

 FIX:

 The bug is in the same line as Bug #1. In line 26 of cardFunctions.c,

 	 	 discardCard( currentPlayer, handPos, state, 1 );

 the last argument, trashFlag, is set to 1 when it should be set to 0. To fix the
 problem, change the last argument to 0:

  	 	 discardCard( handPos, currentPlayer, state, 0 );

 When fixes to Bugs #1 and #2 are applied, the tests are passed.




 ------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------




 Bug #3

 Title: Player's hand count, deck count, and coin total don't change after Adventurer

    card is played

 Classification: Severe

 Platform: Linux

 Description:

    Playing the Adventure card should result in a player's handCount increasing by two

    from drawing two additional treasure cards, the player's coin total increasing by

    2-6 depending on what treasure cards were drawn, and the player's deck count

    decreasing by the number of  cards drawn over the course of drawing the two treasure

    cards. My tests show that none of these values are changed when the Adventurer card

    is played.



    This error was present in all initial game conditions that were created prior to

    playing the Adventurer card.


 Steps to reproduce:

    Inside teammate2dominion folder, run following commands:

        $ gcc dominion.c rngs.c cardFunctions.c cardtest2.c -o prog

        $ ./prog

  ------------------------------------------------------------------------------------

 FIX:

 The first source of this failure is an uninitialized variable. The tests fail
 because the player has not drawn any cards. The problem is with the variable
 drawntreasure. The function playAdventurer() draws cards while drawntreasure is
 less than 2.

		while ( drawntreasure < 2 )
		{
			...
		}

 But drawntreasure is not initialized. It appears that some compilers will
 initialize it to zero, which is what it should be, but this only happens the first
 time the function is called. For all subsequent calls, the value at that location
 in memory still apparently contains its last value, or at least some value greater
 than 1. Therefore, the loop body never executes again, no cards are drawn, and none
 of the player's variables change.

 The fix to this problem is, of course, to initialize drawnTreasure to 0.

 When the fix is applied, another bug is revealed in cardFunctions.c, line 53:

 	 	 state->handCount[currentPlayer--]

 should be state->handCount[currentPlayer]--, which decrements the handCount of the
 current player, rather than decrementing the current player, which is obviously
 wrong and tends to cause segmentation faults.

 Finally, there is the problem of the variable z. This variable is supposed to keep
 track of how many non-treasure cards have been drawn. In the current version, z is
 uninitialized, which creates problems because it is used as an index into the array
 temphand. When z is initialized to zero, the cards still are not replaced properly.
 This is because z needs to be incremented each time a card is appended to temphand.

 So, in short, the fix is to initialize drawntreasure and z to zero, to increment z
 each time a card is added to temphand, and to fix line 53. The correct function
 follows:

	void playAdventurer( int currentPlayer, struct gameState *state )
	{
		int drawntreasure = 0, cardDrawn, z = 0;
		int temphand[MAX_HAND];
		//keep drawing cards until 2 treasure cards are drawn
		while ( drawntreasure < 2 )
		{
			//if the deck is empty we need to shuffle discard and add to deck
			if (state->deckCount[currentPlayer] < 1)
			{
				shuffle( currentPlayer, state );
			}
			drawCard( currentPlayer, state );

			//top card of hand is most recently drawn card.
			cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];
			if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
				drawntreasure++;
			else
			{
				temphand[z] = cardDrawn;
				//remove the top card
				state->handCount[currentPlayer]--;
				z++;
				//z needs to be incremented
			}
		}
		while ( z - 1 >= 0 )
		{
			//discard all cards in play that have been drawn
			state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z - 1];
			z = z - 1;
		}
		return;
	}



 ------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------



 Bug #4

    Title: scoreFor method is not calculating the player's score correctly.
    Product: Dominion game
    Classification: Severe
    Platform: Ubuntu Linux 15.04 running Dominion in Code::Blocks IDE
    Can it be reproduced?: Yes
    Description: Under certain conditions, the score return by scoreFor is 2 less than expected. Note that 
        sometimes the score is correct, and just three of the 6 total test runs fail.
    Steps to reproduce: Go into the teammate1dominion folder and run command "make unittest4.out".
        Look at results and note that some test runs failed.
    Expected results: All scores should be accurately calculated.
    Actual results: The score is often not correctly calculated.
    Workaround: No workarounds exist that could be used by the player.

  ------------------------------------------------------------------------------------
  
 FIX:
 
 The first problem is that the function scoreFor() has a bug causing it to assess 
 points based on the number of cards in the wrong pile. It's on line 509:
 
 		for (i = 0; i < state->discardCount[player]; i++)
 		
 It should be:
 
 		for (i = 0; i < state->deckCount[player]; i++)
 		
 The second problem is that the effect of the Gardens card is not properly 
 implemented. When the card is encountered, the bonus is calculated based on the 
 count of curse cards, which is not helpful. It should be calculated based on total
 deck count when all the player's cards have been merged into the deck.
 
 I fixed this bug by keeping a running count of Gardens cards. Then, after all the 
 other cards have been counted, I apply the appropriate bonus for each Gardens card,
 integer-dividing the total card count by 10 to get the correct bonus. The corrected
 function looks like this:
 
	int scoreFor( int player, struct gameState *state )
	{
		int totalCards = 0;
		int gardensCards = 0;
		int i;
		int score = 0;
		//score from hand
		for (i = 0; i < state->handCount[player]; i++)
		{
			if (state->hand[player][i] == curse)
			{
				score = score - 1;
			};
			if (state->hand[player][i] == estate)
			{
				score = score + 1;
			};
			if (state->hand[player][i] == duchy)
			{
				score = score + 3;
			};
			if (state->hand[player][i] == province)
			{
				score = score + 6;
			};
			if (state->hand[player][i] == great_hall)
			{
				score = score + 1;
			};
			if (state->hand[player][i] == gardens)
			{
				gardensCards++;
				//score = score + ( fullDeckCount( player, 0, state ) / 10 );
			};
			totalCards++;
		}

		//score from discard
		for (i = 0; i < state->discardCount[player]; i++)
		{
			if (state->discard[player][i] == curse)
			{
				score = score - 1;
			};
			if (state->discard[player][i] == estate)
			{
				score = score + 1;
			};
			if (state->discard[player][i] == duchy)
			{
				score = score + 3;
			};
			if (state->discard[player][i] == province)
			{
				score = score + 6;
			};
			if (state->discard[player][i] == great_hall)
			{
				//score = score + 1;
				score = score + 0;
			};
			if (state->discard[player][i] == gardens)
			{
				gardensCards++;
				//score = score + ( fullDeckCount( player, 0, state ) / 10 );
			};
			totalCards++;
		}

		//score from deck
		for (i = 0; i < state->deckCount[player]; i++) {
				if (state->deck[player][i] == curse)
				{
					score = score - 1;
				};
				if (state->deck[player][i] == estate)
				{
					score = score + 1;
				};
				if (state->deck[player][i] == duchy)
				{
					score = score + 3;
				};
				if (state->deck[player][i] == province)
				{
					score = score + 6;
				};
				if (state->deck[player][i] == great_hall)
				{
					score = score + 1;
				};
				if (state->deck[player][i] == gardens)
				{
					gardensCards++;
					//score = score + ( fullDeckCount( player, 0, state ) / 10 );
				};
				totalCards++;
		}

		for( i = 0; i < gardensCards; i++){
			score += totalCards / 10;
		}

		return score;
	}
	 
 
 ------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------



 Bug #5
 
    Title: After a player plays the Salvager card, the coin count is often incorrect.
    Product: Dominion game
    Classification: Severe
    Platform: Ubuntu Linux 15.04 running Dominion in Code::Blocks IDE
    Can it be reproduced?: Yes
    Description: After a player plays the Salvager card, the coin count is often incorrect by varying amounts.
    
    Steps to reproduce: Go into the teammate1dominion folder and run command "make cardtest3.out". 
                        Note that this test takes a few seconds to run.
                        
    Expected results: All coin counts should be accurately calculated because the Salvager card should correctly
                     give the user the value of their trashed card.
                     
    Actual results: The value of the trashed card seems to not be correctly calculated.
    
    Workaround: No workarounds exist that could be used by the player.
    
  ------------------------------------------------------------------------------------
  
  FIX:
  
  The problem here is line 1365:
  
  			//gain coins equal to trashed card
			state->coins = state->coins + getCost( handCard( choice1, state ) );
			
  The variable choice1, as passed to cardEffect(), is the enum value of the card.
  But choice1 is being passed on to handCard() as if it were a hand position. Note
  the signature
  
  			int handCard( int handPos, struct gameState *state )

  Thus, the number of coins the player gets from the card is unpredictable. The fix
  is quite easy: replace the call to handCard() with the card enum itself:
  
  			state->coins = state->coins + getCost( choice1 );
  
  This fix causes the tests to allocate the correct number of coins.



 ------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------
 ------------------------------------------------------------------------------------
 */
