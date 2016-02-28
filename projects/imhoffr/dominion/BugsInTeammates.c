/*********************
 Regina Imhoff
 CS 362
 imhoffr@oregonstate.edu
 Assignment 5
 
 
# Bugs in Lynn Herrick's Code
 
## Village

```
Before Play Village
Deck:
  Position 0, Card: smithy
  Position 1, Card: minion
  Position 2, Card: mine
  Position 3, Card: mine
  Position 4, Card: cutpurse
  Position 5, Card: village
  Position 6, Card: sea hag
  Position 7, Card: council room
  Position 8, Card: smithy
  Position 9, Card: mine
Hand:
  Position 0, Card: village
Played Cards:
After Play Village
Deck:
  Position 0, Card: smithy
  Position 1, Card: minion
  Position 2, Card: mine
  Position 3, Card: mine
  Position 4, Card: cutpurse
  Position 5, Card: village
  Position 6, Card: sea hag
  Position 7, Card: council room
  Position 8, Card: smithy
Deck count: 9, Expected: 9
Played Cards:
  Position 0, Card: curse
Played card count: 1, Expected: 1
Hand:
  Position 0, Card: village
  Position 1, Card: mine
Hand count: 2, Expected: 1
>>>>>>> ERROR: TEST 3 FAILED >>>>>>>
Number of Actions: 4
Action count: 4, Expected: 4
```

The handcount is always one more than expected.
 

## bugs in c_adventurer
 
Caught by randomtestadventurer
 
```
----------------- Testing Card: adventurer ----------------
Random Test 1/2
Before Play Adventurer
Deck:
  Position 0, Card: council room
  Position 1, Card: mine
  Position 2, Card: salvager
  Position 3, Card: minion
  Position 4, Card: salvager
  Position 5, Card: sea hag
  Position 6, Card: copper
  Position 7, Card: outpost
  Position 8, Card: salvager
  Position 9, Card: adventurer
Hand:
  Position 0, Card: copper
  Position 1, Card: copper
  Position 2, Card: copper
  Position 3, Card: copper
  Position 4, Card: estate
Discard:

Program received signal SIGBUS, Bus error.
0x000000010000cb0c in c_adventurer (drawntreasure=0, state=0x7fff5fbf2500,
    currentPlayer=0, cardDrawn=0, temphand=0x7fff5fbf8bd0, z=7436, handPos=0)
    at dominion.c:748
748	      temphand[z]=cardDrawn;
```

This catches a bug where z is not checked against MAX_HAND, which is 500 (here when it crashes z is up to 7436!)  

The same bug is caught with a different z for cardtest1
 
```
Card Tests:
 Cardtest1: Smithy
 No errors were found.
 ----------------- Testing Card: smithy ----------------
 Test 1: There are no cards in the deck
 Hand count = 0, expected = 0
 
 Test 2: one card in hand
 Hand count = 1, expected = 1
 Card in hand = 1, expected = 1
 
 Test 3: two cards in hand
 Hand count = 2, expected = 2
 Card in first position = 1, expected = 1
 Card in second position = 2, expected = 2
 
 Test 4: three cards in hand
 Hand count = 3, expected = 3
 Card 1 in hand = 1, expected = 1
 Card 2 in hand = 1, expected = 1
 Card 3 in hand = 1, expected = 1
 
 
 >>>>> SUCCESS: Testing complete smithy <<<<<
 
 Cardtest2:

 ----------------- Testing Card: adventurer ----------------
 
 Program received signal SIGBUS, Bus error.
 0x000000010000ad8c in c_adventurer (drawntreasure=0, state=0x7fff5fbf2590,
 currentPlayer=0, cardDrawn=32767, temphand=0x7fff5fbff310, z=828,
 handPos=0) at dominion.c:748
 748	      temphand[z]=cardDrawn;
 
 
 This was the same error that was found in the randomtestadventurer.  
 
 
 Cardtest3:  village
 
 ----------------- Testing Card: village ----------------
 Test 1: draw one card from empty deck
 Hand Count = 1, expected = 0
 Number of Actions = 3, expected = 3
 
 Assertion failed: (testGame.handCount[player] == 0), function main, file cardtest3.c, line 63.
 
 The handcount does not equal 0.  
 
 
 Cardtest4:  great_hall
 
 ----------------- Testing Card: great_hall ----------------
 Test 1: draw one card from empty deck
 Hand Count = 0, expected = 0
 Number of Actions = 2, expected = 2
 
 Test 2: draw one card from non-empty deck
 Hand Count = 1, expected = 1
 Number of Actions = 2, expected = 2
 
 Test 3: number of actions increases by 1
 Card found in hand = 0, expected 0
 Number of Actions = 2, expected = 2
 
 
 >>>>> SUCCESS: Testing complete great_hall <<<<<
 
 No errors found.  
 
 
 
 Unittest1: isGameOver()
 ----------------- Testing Function: isGameOver() ----------------
 TEST 1: Game is over when no provinces are left
 When there is at least 1 province card:
 TEST 2: Game continues when no supply pile is zero
 TEST 3: Game continues when 1 supply pile is zero
 TEST 4: Game continues when 2 supply piles are zero
 TEST 5: Game is over when 3 supply piles are zeroTEST 6: Game is over when 3 or more supply piles are zero
 
 >>>>> SUCCESS: Testing complete isGameOver() <<<<<
 
 No errors found
 
 Unittest2:
 ----------------- Testing Function: gainCard() ----------------
 TEST 1: No cards left in the pile
 TEST 2: Sending card to deck
 deck count = 6, expect = 6
 Last card in deck = 1, expect = 1
 supply count = 0, expect = 0
 TEST 3: Sending card to hand
 hand count = 6, expect = 6
 Last card in hand = 1, expect = 1
 supply count = 0, expect = 0
 TEST 4: Sending card to discard
 discard count = 1, expect = 1
 Last card in discard = 1, expect = 1
 supply count = 0, expect = 0
 
 >>>>> SUCCESS: Testing complete gainCard() <<<<<
 
 No errors found
 
 Unittest3: 
 ----------------- Testing Function: updateCoins() ----------------
 Test 1: coins get reset - if no bonus and handCount
 coins = 0, expected = 0
 Test 2: empty hand, 5 bonus coins
 coins = 5, expected = 5
 Test 3: copper coin adds 1
 coins = 1, expected = 1
 Test 4: silver coin adds 2
 coins = 2, expected = 2
 Test 5: gold coin adds 3
 coins = 3, expected = 3
 TEST 6: add 1 copper, 2 silver, 1 gold, one bonus
 coins = 9, expected = 9
 
 >>>>> SUCCESS: Testing complete updateCoins() <<<<<
 
 Unittest4:
 
 ----------------- Testing Function: fullDeckCount() ----------------
 Test 1: Full deck count is zero when deck count, hand count, and discard count are all zero
 Full deck count = 0, expected 0
 TEST 2: Mix of cards, two of same card testing deckCount
 Full deck count = 2, expected = 2
 TEST 3: Mix of cards, two of same card testing handCount
 Full hand count = 2, expected = 2
 TEST 4: Mix of cards, two of same card testing discardCount
 Full hand count = 2, expected = 2
 
 >>>>> SUCCESS: Testing complete fullDeckCount() <<<<<
 
 No errors found.  
 
 
 
 Kim McLeod's code:
 
 randomtestadventurer:
 
 ----------------- Testing Card: adventurer ----------------
 Random Test 1/2
 Before Play Adventurer
 Deck:
 Position 0, Card: council room
 Position 1, Card: mine
 Position 2, Card: salvager
 Position 3, Card: minion
 Position 4, Card: salvager
 Position 5, Card: sea hag
 Position 6, Card: copper
 Position 7, Card: outpost
 Position 8, Card: salvager
 Position 9, Card: adventurer
 Hand:
 Position 0, Card: copper
 Position 1, Card: copper
 Position 2, Card: copper
 Position 3, Card: copper
 Position 4, Card: estate
 Discard:
 After Play Adventurer
 ------ TEST 1 ------
 Hand:
 Position 0, Card: copper
 Position 1, Card: copper
 Position 2, Card: copper
 Position 3, Card: copper
 Position 4, Card: estate
 Position 5, Card: copper
 Hand count: 6, Expected: 6
 ------ TEST 2 ------
 Deck:
 Deck count: 0, Expected: 0
 ------ TEST 3 ------
 Discard:
 Position 0, Card: council room
 Position 1, Card: mine
 Position 2, Card: salvager
 Position 3, Card: minion
 Position 4, Card: salvager
 Position 5, Card: sea hag
 Position 6, Card: outpost
 Position 7, Card: salvager
 Position 8, Card: adventurer
 Discard count: 9, Expected: 9
 Random Test 2/2
 Before Play Adventurer
 Deck:
 Position 0, Card: sea hag
 Position 1, Card: mine
 Position 2, Card: council room
 Position 3, Card: smithy
 Position 4, Card: gardens
 Position 5, Card: cutpurse
 Position 6, Card: treasure map
 Position 7, Card: village
 Position 8, Card: baron
 Position 9, Card: duchy
 Hand:
 Position 0, Card: copper
 Position 1, Card: copper
 Position 2, Card: copper
 Position 3, Card: copper
 Position 4, Card: estate
 Discard:
 After Play Adventurer
 ------ TEST 1 ------
 Hand:
 Position 0, Card: copper
 Position 1, Card: copper
 Position 2, Card: copper
 Position 3, Card: copper
 Hand count: 4, Expected: 5
 >>>>>>> ERROR: TEST 1 FAILED >>>>>>>
 ------ TEST 2 ------
 Deck:
 Deck count: 0, Expected: 0
 ------ TEST 3 ------
 Discard:
 Position 0, Card: estate
 Position 1, Card: sea hag
 Position 2, Card: mine
 Position 3, Card: council room
 Position 4, Card: smithy
 Position 5, Card: gardens
 Position 6, Card: cutpurse
 Position 7, Card: treasure map
 Position 8, Card: village
 Position 9, Card: baron
 Position 10, Card: duchy
 Discard count: 11, Expected: 10
 >>>>>>> ERROR: TEST 3 FAILED: >>>>>>>
 
 >>>>>> ONE OR MORE TESTS FAILED >>>>>>
 
 This shows that the card is not going to the hand count and instead is going into the discard count.  
 
 randomtestcard:
 
 Random Trial 999/1000
 Before Play Village
 Deck:
 Position 0, Card: sea hag
 Position 1, Card: embargo
 Position 2, Card: council room
 Position 3, Card: minion
 Position 4, Card: sea hag
 Position 5, Card: cutpurse
 Position 6, Card: adventurer
 Position 7, Card: council room
 Position 8, Card: cutpurse
 Position 9, Card: smithy
 Hand:
 Position 0, Card: village
 Played Cards:
 After Play Village
 Deck:
 Position 0, Card: sea hag
 Position 1, Card: embargo
 Position 2, Card: council room
 Position 3, Card: minion
 Position 4, Card: sea hag
 Position 5, Card: cutpurse
 Position 6, Card: adventurer
 Position 7, Card: council room
 Position 8, Card: cutpurse
 Deck count: 9, Expected: 9
 Played Cards:
 Position 0, Card: village
 Played card count: 1, Expected: 1
 Hand:
 Position 0, Card: smithy
 Hand count: 1, Expected: 1
 Number of Actions: 3
 Action count: 3, Expected: 4
 >>>>>>> ERROR: TEST 4 FAILED >>>>>>>
 Random Trial 1000/1000
 Before Play Village
 Deck:
 Position 0, Card: smithy
 Position 1, Card: minion
 Position 2, Card: mine
 Position 3, Card: mine
 Position 4, Card: cutpurse
 Position 5, Card: village
 Position 6, Card: sea hag
 Position 7, Card: council room
 Position 8, Card: smithy
 Position 9, Card: mine
 Hand:
 Position 0, Card: village
 Played Cards:
 After Play Village
 Deck:
 Position 0, Card: smithy
 Position 1, Card: minion
 Position 2, Card: mine
 Position 3, Card: mine
 Position 4, Card: cutpurse
 Position 5, Card: village
 Position 6, Card: sea hag
 Position 7, Card: council room
 Position 8, Card: smithy
 Deck count: 9, Expected: 9
 Played Cards:
 Position 0, Card: village
 Played card count: 1, Expected: 1
 Hand:
 Position 0, Card: mine
 Hand count: 1, Expected: 1
 Number of Actions: 3
 Action count: 3, Expected: 4
 >>>>>>> ERROR: TEST 4 FAILED >>>>>>>
 1000 Random Trials complete
 
 >>>>>> ONE OR MORE TESTS FAILED >>>>>>
 
 This shows that the number of actions are off by one!
 
 Cardtest1:
 ----------------- Testing Card: smithy ----------------
 Test 1: There are no cards in the deck
 Hand count = 0, expected = 0
 
 Test 2: one card in hand
 Hand count = 1, expected = 1
 Card in hand = 1, expected = 1
 
 Test 3: two cards in hand
 Hand count = 2, expected = 2
 Card in first position = 1, expected = 1
 Card in second position = 2, expected = 2
 
 Test 4: three cards in hand
 Hand count = 2, expected = 3
 Card 1 in hand = 0, expected = 1
 Card 2 in hand = 1, expected = 1
 Card 3 in hand = 1, expected = 1
 
 Assertion failed: (handCountAfter == 3), function main, file cardtest1.c, line 127.
 
 The handcount is off, meaning that there is an off by one error somewhere.  
 
 cardtest2:
 ----------------- Testing Card: adventurer ----------------
 Test 1: drawn treasure = 1 when the treasure is copper
 Card 4 in hand = 1, expected = 1
 
 Test 2:drawn treasure = 1 when the treasure is silver
 Card 5 in hand = 1, expected = 1
 
 Test 2:drawn treasure = 1 when the treasure is gold
 Card 6 in hand = 1, expected = 1
 
 
 >>>>> SUCCESS: Testing complete adventurer <<<<<
 
 No errors found.
 
 cardtest3:
 ----------------- Testing Card: village ----------------
 Test 1: draw one card from empty deck
 Hand Count = 0, expected = 0
 Number of Actions = 2, expected = 3
 
 Assertion failed: (afterNumberOfActions == beforeNumberOfActions + 2), function main, file cardtest3.c, line 64.
 The number of actions are off, same as was found in the random test.
 
 cardtest4:
 ----------------- Testing Card: great_hall ----------------
 Test 1: draw one card from empty deck
 Hand Count = 0, expected = 0
 Number of Actions = 2, expected = 2
 
 Test 2: draw one card from non-empty deck
 Hand Count = 1, expected = 1
 Number of Actions = 2, expected = 2
 
 Test 3: number of actions increases by 1
 Card found in hand = 0, expected 0
 Number of Actions = 2, expected = 2
 
 
 >>>>> SUCCESS: Testing complete great_hall <<<<<
 No errors found.
 
 
 
 Unittest1:
 ----------------- Testing Function: isGameOver() ----------------
 TEST 1: Game is over when no provinces are left
 When there is at least 1 province card:
 TEST 2: Game continues when no supply pile is zero
 TEST 3: Game continues when 1 supply pile is zero
 TEST 4: Game continues when 2 supply piles are zero
 TEST 5: Game is over when 3 supply piles are zeroTEST 6: Game is over when 3 or more supply piles are zero
 
 >>>>> SUCCESS: Testing complete isGameOver() <<<<<
 
 No errors found.
 
 Unittest2:
 ----------------- Testing Function: gainCard() ----------------
 TEST 1: No cards left in the pile
 TEST 2: Sending card to deck
 deck count = 6, expect = 6
 Last card in deck = 1, expect = 1
 supply count = 0, expect = 0
 TEST 3: Sending card to hand
 hand count = 6, expect = 6
 Last card in hand = 1, expect = 1
 supply count = 0, expect = 0
 TEST 4: Sending card to discard
 discard count = 1, expect = 1
 Last card in discard = 1, expect = 1
 supply count = 0, expect = 0
 
 >>>>> SUCCESS: Testing complete gainCard() <<<<<
 No errors found.
 
 Unittest3:
 ----------------- Testing Function: updateCoins() ----------------
 Test 1: coins get reset - if no bonus and handCount
 coins = 0, expected = 0
 Test 2: empty hand, 5 bonus coins
 coins = 5, expected = 5
 Test 3: copper coin adds 1
 coins = 1, expected = 1
 Test 4: silver coin adds 2
 coins = 2, expected = 2
 Test 5: gold coin adds 3
 coins = 3, expected = 3
 TEST 6: add 1 copper, 2 silver, 1 gold, one bonus
 coins = 9, expected = 9
 
 >>>>> SUCCESS: Testing complete updateCoins() <<<<<
 No errors found.
 
 Unittest4:
 ----------------- Testing Function: fullDeckCount() ----------------
 Test 1: Full deck count is zero when deck count, hand count, and discard count are all zero
 Full deck count = 0, expected 0
 TEST 2: Mix of cards, two of same card testing deckCount
 Full deck count = 2, expected = 2
 TEST 3: Mix of cards, two of same card testing handCount
 Full hand count = 2, expected = 2
 TEST 4: Mix of cards, two of same card testing discardCount
 Full hand count = 2, expected = 2
 
 >>>>> SUCCESS: Testing complete fullDeckCount() <<<<<
 No errors found.  
 
 
 *********************/
