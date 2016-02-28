UNIT TESTS - no bugs found
CARD TEST - smithy
CARD TEST - adventurer
RANDOM TESTS - fail too much

ok I got my tests running with Philips code.

Unit Tests - no fails.

Random Tests - lots of fails. Too many to be of use for now.

Card Test - smithy, after one play:
1. the hand contained an extra card.
   Expected 7 cards in hand, found 8.
2. the deck contained one less than expected.
   Expected 2 cards in deck, found 1.
3. expected 1 played card (smithy) found 13 played cards.
4. discard was ok.  passed.
5. the other player hand, deck, played, and discard passed.

Card Test - adventurer, after one play:
1. the hand contained one less card than expected.
   Expected 7 in hand, found 6.
2. the deck passed, expected 2 found 2 cards.
3. expected 1 played card but found 0.
4. expected 5 discards but found 7.
5. the other player hand, deck, played, and discard passed.



flip1 7% cardTest1
--------- Testing smithy ---------
Player 0's hand:
#  Card
0  Copper       
1  Silver       
2  Gold         
3  Curse        
4  Duchy        
5  Gardens      
6  Feast        
7  Adventurer   

Player 0's deck: 
#  Card
0  Province     

Player 0's played cards: 
#  Card
0  Smithy        

Player 0's discard: 
#  Card
0  Mine          
1  Remodel       
2  Steward       
3  Village       
4  Baron         

Player 1's hand:
#  Card
0  Estate       
1  Estate       
2  Estate       
3  Estate       
4  Estate       

Player 1's deck: 
#  Card
0  Estate       
1  Estate       
2  Estate       
3  Estate       
4  Estate       

Player 1's played cards: 
#  Card
0  Smithy        

Player 1's discard: 
#  Card
0  Estate        
1  Estate        
2  Estate        
3  Estate        
4  Estate        

test 1: smithy p0 hand           FAIL: expected 7, result 8
test 2: smithy p0 deck           FAIL: expected 2, result 1
test 3: smithy p0 played         FAIL: expected 1, result 13
test 4: smithy p0 discard        pass: expected 5, result 5
test 5: smithy p1 hand           pass: expected 5, result 5
test 6: smithy p1 deck           pass: expected 5, result 5
test 7: smithy p1 played         pass: expected 0, result 0
test 8: smithy p1 discard        pass: expected 5, result 5


flip1 8% cardTest2
--------- Testing adventurer ---------
Player 0's hand:
#  Card
0  Copper       
1  Copper       
2  Copper       
3  Smithy       
4  Adventurer   
5  Silver       

Player 0's deck: 
#  Card
0  Silver       
1  Silver       

Player 0's played cards: 

Player 0's discard: 
#  Card
0  Gold          
1  Gold          
2  Gold          
3  Village       
4  Baron         
5  Feast         
6  Gardens       

Player 1's hand:
#  Card
0  Silver       
1  Silver       
2  Silver       
3  Estate       
4  Estate       

Player 1's deck: 
#  Card
0  Copper       
1  Copper       
2  Copper       
3  Duchy        
4  Duchy        

Player 1's played cards: 

Player 1's discard: 
#  Card
0  Gold          
1  Gold          
2  Gold          
3  Province      
4  Province      

test 1: adventurer p0 hand       FAIL: expected 7, result 6
test 2: adventurer p0 deck       pass: expected 2, result 2
test 3: adventurer p0 played     FAIL: expected 1, result 0
test 4: adventurer p0 discard    FAIL: expected 5, result 7
test 5: adventurer p1 hand       pass: expected 5, result 5
test 6: adventurer p1 deck       pass: expected 5, result 5
test 7: adventurer p1 played     pass: expected 0, result 0
test 8: adventurer p1 discard    pass: expected 5, result 5


