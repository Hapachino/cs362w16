
Dominion Bug 1
==============================
To: James Linnenburger

Title:  Smithy card

Class: Serious Bug

Date: 02-22-2016          
Reported By: Jason Ridder
Email: ridderj@oregonstate.edu    


Product: Dominion                   
Platform: Linux                   
Browser: NA                    
URL: NA        

Is it reproducible: Yes

Description
===========
   Smithy card not removed from players hand after being used.  


Steps to Produce/Reproduce
--------------------------

   Play smith card from players hand.
   
   From bug test:
         TEST 3: Smithy card removed from current players hand after being used.
            What is hand count 7
               Total 1 smithy cards in hand,expected 0

Expected Results
----------------
   One smith card in hand. After being player card should be gone.


Actual Results
--------------
   Card is still in players hand after being used. 

***************************************************************************************








Dominion Bug 2
==============================
To: James Linnenburger

Title:  Cutpurse Card

Class: Serious Bug

Date: 02-22-2016          
Reported By: Jason Ridder
Email: ridderj@oregonstate.edu    


Product: Dominion                   
Platform: Linux                   
Browser: NA                    
URL: NA        

Is it reproducible: Yes

Description
===========
   Players are not discarding copper cards from thier hands. 


Steps to Produce/Reproduce
--------------------------

Happens in every instance when the current player uses the card.
Has been tested with 2-4 players and happens with any player. 

Test Results:

   Testing with 2 players
   
          Player 1 playing cutpurse card 
             Current player 1 copper card, expected 1
              Player 2 had 5 copper card, expected 4
                  TEST FAILED
          Player 2 playing cutpurse card 
              Player 1 had 5 copper card, expected 4
                  TEST FAILED
             Current player 1 copper card, expected 1
             
       Testing with 3 players
       
          Player 1 playing cutpurse card 
             Current player 1 copper card, expected 1
              Player 2 had 5 copper card, expected 4
                  TEST FAILED
              Player 3 had 5 copper card, expected 4
                  TEST FAILED
          Player 2 playing cutpurse card 
              Player 1 had 5 copper card, expected 4
                  TEST FAILED
             Current player 1 copper card, expected 1
              Player 3 had 5 copper card, expected 4
                  TEST FAILED
          Player 3 playing cutpurse card 
              Player 1 had 5 copper card, expected 4
                  TEST FAILED
              Player 2 had 5 copper card, expected 4
                  TEST FAILED
             Current player 1 copper card, expected 1
             
       Testing with 4 players
       
          Player 1 playing cutpurse card 
             Current player 1 copper card, expected 1
              Player 2 had 5 copper card, expected 4
                  TEST FAILED
              Player 3 had 5 copper card, expected 4
                  TEST FAILED
              Player 4 had 5 copper card, expected 4
                  TEST FAILED
          Player 2 playing cutpurse card 
              Player 1 had 5 copper card, expected 4
                  TEST FAILED
             Current player 1 copper card, expected 1
              Player 3 had 5 copper card, expected 4
                  TEST FAILED
              Player 4 had 5 copper card, expected 4
                  TEST FAILED
          Player 3 playing cutpurse card 
              Player 1 had 5 copper card, expected 4
                  TEST FAILED
              Player 2 had 5 copper card, expected 4
                  TEST FAILED
             Current player 1 copper card, expected 1
              Player 4 had 5 copper card, expected 4
                  TEST FAILED
          Player 4 playing cutpurse card 
              Player 1 had 5 copper card, expected 4
                  TEST FAILED
              Player 2 had 5 copper card, expected 4
                  TEST FAILED
              Player 3 had 5 copper card, expected 4
                  TEST FAILED
             Current player 1 copper card, expected 1


Expected Results
----------------
   In situation with 2 players. Player 1 plays card. Player 2 initially
   has a hand of 5 copper cards. After playing the cutpurse card, Player 2
   should have only 4 copper cards.


Actual Results
--------------
   In situation with 2 players. Player 1 plays card. Player 2 initially
   has a hand of 5 copper cards. After playing the cutpurse card, Player 2
   still has 5 copper cards.

   
   
   
   
   
  

***************************   
-----------------------------------------
 Results From All Test Ran Below  
-----------------------------------------
***************************  
   
   
   
   
   
   
/* -----------------------------------------------------------------------
 * Testing fullDeckCount()
 Basic requirements of fullDeckCount()
   1)Count how many of one card are in all of
      the decks.
 * -----------------------------------------------------------------------
 */
 
 -No bugs.
 
 
 /* -----------------------------------------------------------------------
 * Testing scoreFor()
 Basic requirements of fullDeckCount()
   1)Return score for player by counting cards with values
     across all card piles.
   2)Only cards in deck pile return correct score.
   3)Only cards in hand return correct score.
   4)Only cards in discard pile return correct score.   
 * -----------------------------------------------------------------------
 */
 
 
 -Bug found. Sometimes the score returned would be incorrect.

Example of failed test:

   Testing player 0 with 3 province card(s).
   Amount in location: Deckcards: 2  HandCards: 0 DiscardCards: 1. Point Value: 6
   Score = 12, expected = 18 TEST FAILED
   
   
   
 
Testing player 0 with 0 curse card(s).
Amount in location: Deckcards: 0  HandCards: 0 DiscardCards: 0. Point Value: -1
Score = 0, expected = 0

Testing player 0 with 1 curse card(s).
Amount in location: Deckcards: 0  HandCards: 1 DiscardCards: 0. Point Value: -1
Score = -1, expected = -1


Testing player 1 with 3 gardens card(s).
Amount in location: Deckcards: 0  HandCards: 1 DiscardCards: 2. Point Value: 0
Score = 0, expected = 0 


Testing player 0 with 1 curse card(s).
Amount in location: Deckcards: 0  HandCards: 0 DiscardCards: 1. Point Value: -1
Score = 0, expected = -1 TEST FAILED


Testing player 1 with 11 great_hall card(s).
Amount in location: Deckcards: 4  HandCards: 4 DiscardCards: 3. Point Value: 1
Score = 10, expected = 11 TEST FAILED

Testing player 1 with 4 province card(s).
Amount in location: Deckcards: 4  HandCards: 0 DiscardCards: 0. Point Value: 6
Score = 0, expected = 24 TEST FAILED



I did realize my oracle code didn't catch situations where discard
piles equaled deck card piles. Example below. This shouldn't have
passed.
   
   Examples of a test that shouldn't have been correct:

      Testing player 0 with 4 province card(s).
      Amount in location: Deckcards: 2  HandCards: 0 DiscardCards: 2. Point Value: 6
      Score = 24, expected = 24  

      Testing player 1 with 10 great_hall card(s).
      Amount in location: Deckcards: 4  HandCards: 1 DiscardCards: 5. Point Value: 1
      Score = 10, expected = 10
      
      
      
/* -----------------------------------------------------------------------
 * Testing gainCard()
 Basic requirements of gainCard()
   1)Fail if card is not in supplyCount()
   2)Add card to players deck - check if deck has been updated.
   3)Add card to players hand - check if hand has been updated.
   4)Add card to players discard - check if discard has been updated.
   5)Was supplyCount decressed in size.
 * -----------------------------------------------------------------------
 */
 
TESTING gainCard():

Test 1 - gainCard should return -1 if supplyCount is empty
return value = -1, expected = -1

Test 2 - Add card to player 1 discard deck - check if discard deck has been updated
discard pile count = 1, expected discard pile count = 1
card = 0, expected card = 0

Test 3 - Add card to player 1 deck - check if deck has been updated
deck pile count = 1, expected deck pile count = 1
card = 0, expected card = 0

Test 4 - Add card to player 1 hand - check if hand has been updated
hand pile count = 1, expected hand pile count = 1
card = 0, expected card = 0

Test 5 - Testing supplyCount decressed in size after func completed.
supply count for curse = 0, expected supply count for curse = 0


 -No bugs.
 
 
 /* -----------------------------------------------------------------------
 * Testing isGameOver()
 Basic requirements of isGameOver()
   1)Does game end when provience cards are empty?
   2)Game shouldn't end with a provience card.
   3)Does game end when only 2 or less supply piles are empty?
   4)Does game end when a certain type of card 
      is included when the 3 piles are gone?
 * -----------------------------------------------------------------------
 */
 
 
-Bug found on test 4. Function doesn't work correctly with card piles
sea_hag and treasure_map run to zero.


-Examples of test fails
 Testing curse, estate, and sea_hag
     Return value = 0, expected = 1
       TEST FAIL******

 Testing curse, estate, and treasure_map
     Return value = 0, expected = 1
       TEST FAIL******
       
  Testing curse, duchy, and sea_hag
     Return value = 0, expected = 1
       TEST FAIL******
 
  Testing curse, duchy, and treasure_map
     Return value = 0, expected = 1
       TEST FAIL******
  
   Testing curse, gardens, and sea_hag
     Return value = 0, expected = 1
       TEST FAIL******

   Testing curse, gardens, and treasure_map
     Return value = 0, expected = 1
       TEST FAIL******
   
   Testing salvager, village, and treasure_map
     Return value = 0, expected = 1
       TEST FAIL******
       
  /* -----------------------------------------------------------------------
 * Testing adventurer card
 Basic requirements of adventurer card
   1)Player should recieve 2 treasure cards in their hand.
   2)Adventurer card should work with all treasure coins.
   3)If deck is empty adventurer should single that cards
      should be shuffled from discard deck and be used.
   4)Other players shouldn't have any changes to their cards.
 * -----------------------------------------------------------------------
 */
 
 
 -No bugs found
 
 ///////////
 //Random Testing
 ///////////

Discard supply count is never correct. In the situation below, 18 cards were
drawn in total before 2 treasure cards were found. Two of the 18, the treasure cards,
should go to the hand, leaving 16 cards discarded. The Adventurer card also needs to be
discard so that brings the total to 17 cards discarded. The 17 is added to the discard
pile count which was 19. So after everything the dscard supply count should be 36.


+18   - 18 cards drawn from card deck to find 2 Treasure cards.
- 2   - Two of those cards(the Treasure cards) go to the players hand.
--------
 16
+ 1   - The baron card after it is played, needs to be put into the discard
         Pile
-------------
 17
+19   - Before the Adventruer card was played, there were 19 cards in the
        discard pile.
--------------
 36   - This is what the total count for the discard supply count should be
        after the Adventurer card has been played.

The test only shows 34 cards are in the discard pile so it's incorrect.        


 
TEST START---------------------------------
TEST NUM: 58792 Deck: 500 Hand: 90 Discard: 19 Player: 2 DiscardCount: 16
ADVENTURER CARD---
Hand Supply Count = 92 ,expected 92
Discard Supply Count = 34,expected 36
TEST FAIL
Coins = 22 ,expected 22
Number of buys = 8,expected 8



 
 /* -----------------------------------------------------------------------
 * Testing smithy card
 Basic requirements of smithy card
   1)Increase current players hand by 3 cards
   2)Other players shouldn't have any changes to their cards.
   3)Smithy card removed from current players hand after being used.
   4)Supply count of all cards not effected.
 * -----------------------------------------------------------------------
 */

Smithy card not removed from players hand after being used.
 
TEST 3: Smithy card removed from current players hand after being used.
What is hand count 7
    Total 1 smithy cards in hand,expected 0
  
  /* -----------------------------------------------------------------------
 * Testing village card
 Basic requirements of smithy card
   1)Increase current players hand by 1 card
   2)Actions increased by 2
   3)Increase current players hand +1 card and +2 actions with different player sizes.
   4)Play village card when players deck is empty.
 * -----------------------------------------------------------------------
 */
 
TEST 1: Increase current players hand by 1 card.
    Total 6 cards in hand,expected 5
    
    
TEST 2: Actions increased by 2.
     Current Actions 2 ,expected 3
 
 
 
TEST 3: Increase current players hand +1 card and +2 actions with different player sizes.
    Testing with 2 players
        Current Actions 2 ,expected 3
          TEST FAIL
        Total 6 cards in hand,expected 5
          TEST FAIL
    Testing with 3 players
        Current Actions 2 ,expected 3
          TEST FAIL
        Total 6 cards in hand,expected 5
          TEST FAIL
    Testing with 4 players
        Current Actions 2 ,expected 3
          TEST FAIL
        Total 6 cards in hand,expected 5
          TEST FAIL
       
       
       
TEST 4: Play village card when players deck is empty.
    Testing with 2 players
     Current deck count 4, hand count 6, and actions 2;expected 4,5,&3
       TEST FAIL
    Testing with 3 players
     Current deck count 4, hand count 6, and actions 2;expected 4,5,&3
       TEST FAIL
    Testing with 4 players
     Current deck count 4, hand count 6, and actions 2;expected 4,5,&3
       TEST FAIL
 
/* -----------------------------------------------------------------------
 * Testing cutpurse card
 Basic requirements of smithy card
   1)Increase current players hand by 1 card
   2)Actions increased by 2
   3)Increase current players hand +1 card and +2 actions with different player sizes.
   4)Play village card when players deck is empty.
 * -----------------------------------------------------------------------
 */ 
 
 
-----------------------Each other player discards a Copper card
 
 Players are not discarding copper cards.

         
TEST 2:Each other player discards a Copper card

    Testing with 2 players
       Player 1 playing cutpurse card 
          Current player 1 copper card, expected 1
           Player 2 had 5 copper card, expected 4
               TEST FAILED
       Player 2 playing cutpurse card 
           Player 1 had 5 copper card, expected 4
               TEST FAILED
          Current player 1 copper card, expected 1
          
    Testing with 3 players
       Player 1 playing cutpurse card 
          Current player 1 copper card, expected 1
           Player 2 had 5 copper card, expected 4
               TEST FAILED
           Player 3 had 5 copper card, expected 4
               TEST FAILED
       Player 2 playing cutpurse card 
           Player 1 had 5 copper card, expected 4
               TEST FAILED
          Current player 1 copper card, expected 1
           Player 3 had 5 copper card, expected 4
               TEST FAILED
       Player 3 playing cutpurse card 
           Player 1 had 5 copper card, expected 4
               TEST FAILED
           Player 2 had 5 copper card, expected 4
               TEST FAILED
          Current player 1 copper card, expected 1
          
    Testing with 4 players
       Player 1 playing cutpurse card 
          Current player 1 copper card, expected 1
           Player 2 had 5 copper card, expected 4
               TEST FAILED
           Player 3 had 5 copper card, expected 4
               TEST FAILED
           Player 4 had 5 copper card, expected 4
               TEST FAILED
       Player 2 playing cutpurse card 
           Player 1 had 5 copper card, expected 4
               TEST FAILED
          Current player 1 copper card, expected 1
           Player 3 had 5 copper card, expected 4
               TEST FAILED
           Player 4 had 5 copper card, expected 4
               TEST FAILED
       Player 3 playing cutpurse card 
           Player 1 had 5 copper card, expected 4
               TEST FAILED
           Player 2 had 5 copper card, expected 4
               TEST FAILED
          Current player 1 copper card, expected 1
           Player 4 had 5 copper card, expected 4
               TEST FAILED
       Player 4 playing cutpurse card 
           Player 1 had 5 copper card, expected 4
               TEST FAILED
           Player 2 had 5 copper card, expected 4
               TEST FAILED
           Player 3 had 5 copper card, expected 4
               TEST FAILED
          Current player 1 copper card, expected 1
          
 /* -----------------------------------------------------------------------
 * Random Testing baron card
 * -----------------------------------------------------------------------
 */
 
 Bug found - Estate supply count is deprecated by more then 1 on both
 choice 1 
 
 TEST START---------------------------------
CARD: 1
CHOICE: 0
TEST NUM: 1 Deck: 80 Hand: 90 Discard: 58 Player 1
GET ESTATE CARD---
Coins = 0 ,expected 0
Number of buys = 2,expected 2
Estate Supply Count = 38 ,expected 39
TEST FAIL
Hand Supply Count = 90 ,expected 90
Discard Supply Count = 59 ,expected 59



on situation where choice 1 it's depcreated > then 1. Shouldn't
be deprecated at all since player never had the card.

TEST START---------------------------------
CARD: 0
CHOICE: 1
TEST NUM: 9 Deck: 28 Hand: 5 Discard: 24 Player 2
ESTATE CARD NOT FOUND---
Coins = 10 ,expected 10
Number of buys = 20,expected 20
Estate Supply Count = 66 ,expected 68
TEST FAIL
Deck Supply Count = 28 ,expected 28
Hand Supply Count = 5 ,expected 6
TEST FAIL
Discard Supply Count = 25 ,expected 25




works great on choice 1 when they have card.

TEST START---------------------------------
CARD: 1
CHOICE: 1
TEST NUM: 4 Deck: 5 Hand: 88 Discard: 98 Player 2
DISCARD ESTATE CARD---
Coins = 29 ,expected 29
Number of buys = 11,expected 11
Estate Supply Count = 6 ,expected 6
Hand Supply Count = 87 ,expected 87
Discard Supply Count = 99 ,expected 99




bug 2 - Hand shouldn't be deprecated when player doesn't have baron
card.


TEST START---------------------------------
CARD: 0
CHOICE: 1
TEST NUM: 9 Deck: 28 Hand: 5 Discard: 24 Player 2
ESTATE CARD NOT FOUND---
Coins = 10 ,expected 10
Number of buys = 20,expected 20
Estate Supply Count = 66 ,expected 68
TEST FAIL
Deck Supply Count = 28 ,expected 28
Hand Supply Count = 5 ,expected 6
TEST FAIL
Discard Supply Count = 25 ,expected 25

bug 3  - Coins shouldn't be increased by 4 if player doesn't have card.


TEST START---------------------------------
CARD: 0
CHOICE: 1
TEST NUM: 11 Deck: 98 Hand: 62 Discard: 38 Player 2
ESTATE CARD NOT FOUND---
Coins = 21 ,expected 17
TEST FAIL
Number of buys = 14,expected 14
Estate Supply Count = 76 ,expected 76
Deck Supply Count = 98 ,expected 98
Hand Supply Count = 61 ,expected 63
TEST FAIL
Discard Supply Count = 39 ,expected 39
   