
/***********************************
//FROM Marco Zamora
/***********************************
* Testing Jason Ridder's dominion card functions
* smithyCardFunc
* Bugs:
	ERROR: hand count for player 0:  Expected: 162, Actual: 163
	ERROR: deck count for player 0:  Expected: 84, Actual: 83
* Description:
	It seems like there is an extra card from the deck in the hand.
*********************/

Extra drawCard on line 684. Deleted. Show below.

for (i = 0; i < 3; i++)
   {
   drawCard(currentPlayer, state);
   }
      drawCard(currentPlayer, state);  //LINE 684 - Removed to fix bug.

/***********************************
//FROM Marco Zamora      
/***********************************
* adventurerCardFunc
* Bugs:
	Player playing adventurer: #0
	ERROR: played card counts:  Expected: 1, Actual: 0
	ERROR: Score for 0: Expected: 73, Actual: 79
	ERROR: hand count for player 0:  Expected: 161, Actual: 176
	ERROR: deck count for player 0:  Expected: 72, Actual: 71
	ERROR: discard count for  for player 0:  Expected: 13, Actual: 14
* Description:
	It seems like the card is not counted as played or discarded.
	Elsewhere in the function, cards are getting lost or moved to the
	wrong place, because several deck numbers are off.
	Finally, the test does not finish all testing because it hits a seg fault soon
	after test #12.
*********************/

Fix 1:
   Line 662 update from this:
   cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-2]; //LINE 662

   To this:
   cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]; //LINE 662

   Negative 2 update to negative 1, cardDrawn now take from top of card.

Fix 2:
   Line 665:
     state->handCount[currentPlayer]; //this should just remove the top card (the most recently drawn one).

   Should be this:
     state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one). 


 /***********************************
//FROM James Linnenburger    
/***********************************
Adventurer Card Test:
-----------------------------------------------------------------------------
-------------------------------------------------------------
TEST 1: At least 2 treasure cards in player's deck
-------------------------------------------------------------
Starting hand: [4, 1, 4, 4, 7]
Starting deck: [4, 4, 1, 1, 4]
Starting discard: [ ]
# coin cards: 3
After adventurer card has been played:
           Cards in hand: 10 [6 expected]
           Cards in deck: 0 [1 expected]
        Cards in discard: 3 [3 expected]
            Played cards: 0 [0 expected]
Player's hand: [4, 1, 4, 4, 7, 4, 1, 1, 4, 4]
Expected hand: [4, 1, 4, 4, 4, 4]
Player's deck: [ ]
Expected deck: [4]
Player's discard: [1, 1, 7]
Expected discard: [7, 1, 1]
        Gamestates equal: 0
-------------------------------------------------------------
TEST 1 STATUS:  **** FAILURE **** FAILURE **** FAILURE ***
-------------------------------------------------------------
-------------------------------------------------------------
TEST 3: Only 1 treasure available
-------------------------------------------------------------
-------------------------------------------------------------
TEST 4: 0 treasures available
-------------------------------------------------------------

Bugs discovered in the Adventure card:
---------------------------------------------------------------------------------------------
1. Adventurer card was not removed from the player's hand when played. (See test 1 details)
2. Non treasure cards drawn were not removed from the player's hand.   (See test 1 details)
3. 3 treasure cards were drawn instead of only 2                       (See test 1 details)
4. Program hangs when there is only 1 treasure available in the 
   player's deck/discard.
*********************/

Fix 1(Fixes bug 1):
   Added handPost parameter in file dominion.c:
      int adventurerCardFunc(struct gameState *state, int handPos) //LINE 647
   Added handPost parameter in file dominion_helpers.h:
      int adventurerCardFunc(struct gameState *state, int handPos); //LINE 13
   Added discardCard function so card is removed.
      discardCard(handPos, currentPlayer, state, 0);//LINE 674

 -Other bugs fixed in Marco Zamora bug report.
 
 
 
 
/***********************************
//FROM Jason Ridder(Me)   
/*********************************** 
Testing scoreFor()------------------------------------------
   -Bug found. If there were any cards in the deck card pile,
   sometimes the score returned would be incorrect.

   Example of failed test:
   
      Testing player 0 with 3 province card(s).
      Amount in location: Deckcards: 2  HandCards: 0 DiscardCards: 1. Point Value: 6
      Score = 12, expected = 18 TEST FAILED
  ***********************************/   
  
  
  
  
   Fix 1: Changed state->discardCount[player] to state->deckCount[player]
   
     for (i = 0; i < state->deckCount[player]; i++) //LINE 444 updated
     
 
 
 
 
/***********************************
//FROM Jason Ridder(Me)   
/***********************************
Testing isGameOver()------------------------------------------
   -Bug found on test 4. Function doesn't work correctly with card piles
   sea_hag and treasure_map run to zero.
      
      Test Assert Fail:
         Testing estate, tribute, and sea_hag
         Return value = 0, expected = 1
            TEST FAIL******

         Testing estate, tribute, and treasure_map
         Return value = 0, expected = 1
            TEST FAIL******
    ***********************************/ 

    Fix: There are cards 0-26 in the array, the for loop statement only has
      25, it should be 27

   Original:
      for (i = 0; i < 25; i++)  //LINE 402 

   Update:
       for (i = 0; i < 27; i++)  //LINE 402
       
       
       
/***********************************
//FROM Jason Ridder(Me)   
/***********************************
Testing village card------------------------------------------
   TEST 1: Increase current players hand by 1 card.
   -No bugs found

   TEST 2: Actions increased by 2.
   -No bugs found
   
   TEST 3: Increase current players hand +1 card and +2 actions with different player sizes.
   - Bugs found.
      -No bugs found when only 2 players, actions increase not correct when > 2 players.
      
            Testing with 2 players
               Current Actions 3 ,expected 3
               Total 5 cards in hand,expected 5
            Testing with 3 players
               Current Actions 4 ,expected 3
                  TEST FAIL
               Total 5 cards in hand,expected 5
            Testing with 4 players
               Current Actions 5 ,expected 3
                  TEST FAIL
               Total 5 cards in hand,expected 5
   
   TEST 4: Play village card when players deck is empty.
   - Bugs found.
       -Same action bug found in test 3. Having empty deck using village card
         show no bugs.
         
            Testing with 2 players
               Current deck count 4, hand count 5, and actions 3;expected 4,5,&3
            Testing with 3 players
               Current deck count 4, hand count 5, and actions 4;expected 4,5,&3
                    TEST FAIL
            Testing with 4 players
               Current deck count 4, hand count 5, and actions 5;expected 4,5,&3
                     TEST FAIL
    ***********************************/

Updated line 700
From:
state->numActions = state->numActions + state->numPlayers;
To:
state->numActions = state->numActions + 2;  
