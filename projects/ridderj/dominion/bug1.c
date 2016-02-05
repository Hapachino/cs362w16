Testing fullDeckCount()------------------------------------------
   -No bugs found.

   
   

Testing scoreFor()------------------------------------------
   -Bug found. If there were any cards in the deck card pile,
   sometimes the score returned would be incorrect.

   Example of failed test:
   
      Testing player 0 with 3 province card(s).
      Amount in location: Deckcards: 2  HandCards: 0 DiscardCards: 1. Point Value: 6
      Score = 12, expected = 18 TEST FAILED
   
   
   I did realize my oracle code didn't catch situations where discard
   piles equaled deck card piles. Example below. This shouldn't have
   passed.
   
   Examples of a test that shouldn't have been correct:

      Testing player 0 with 4 province card(s).
      Amount in location: Deckcards: 2  HandCards: 0 DiscardCards: 2. Point Value: 6
      Score = 24, expected = 24  



      
      
      
      
      
Testing gainCard()------------------------------------------
   -No bugs found.

 


 
   
   
   
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


            
            
            
            
            

            
Testing adventurer card------------------------------------------
   TEST 1&2: Player should recieve 2 treasure cards in their hand.
   - Bugs found.
      -Player playing card would recieve 3 treasure cards instead
       2. It happened will all different kinds of treasure cards.
   
   TEST 3: If deck is empty adventurer should single that cards
      should be shuffled from discard deck and be used.
   - Bugs found.
      -Player didn't receive all cards from discard deck, one still
         remained in it.
         
   TEST 4: Other players shouldn't have any changes to their cards.
      -No bugs found. Other players cards and decks remained untouched.

      
      
      
      
      
      
      
      
      
      
Testing smithy card------------------------------------------
   TEST 1: Increase current players hand by 3 cards.
   - Bugs found.
      -The test failed. There was an extra card in hand.
      
   TEST 2: Other players shouldn't have any changes to their cards.
   -No bugs found
   
   TEST 3: Smithy card removed from current players hand after being used.
   -No bugs found
   
   TEST 4: Supply count of all cards not effected.
   -No bugs found


   
   
   
   
   
   
   
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

     


     
                    
                    
Testing cutpurse card------------------------------------------
   TEST 1:Current player +2 treasure
      -No bugs.
      
   TEST 2:Each other player discards a Copper card
      - Would take 1 copper card away from current player actually playing
        cutpurse card.This isn't suppose to happen. There was only one
        situation where current player wouldn't have
        copper taken away, that was when four players were playing and player 4
        used it.
        
         Player 4 playing cutpurse card
            Player 1 had 5 copper card, expected 4
               TEST FAILED
            Player 2 had 5 copper card, expected 4
               TEST FAILED
            Player 3 had 5 copper card, expected 4
               TEST FAILED
            Current player 1 copper card, expected 1

      -Also wouldn't ever take away a copper card from every other player, no matter
         how many players where playing.
   
   TEST 3:If other players don't have a copper, hands should remain the same.
       -No bugs.
   
   TEST 4: Card supply is uneffected when played.
       -No bugs.
       
   
