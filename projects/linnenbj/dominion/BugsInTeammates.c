
Testing teammate 1:  Jason Ridder


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


Smithy Card Test:
-----------------------------------------------------------------------------
-------------------------------------------------------------
TEST 1: Enough cards in player's deck to draw 3
-------------------------------------------------------------
Starting hand: [4, 4, 1, 1, 13]
Starting deck: [1, 4, 4, 4, 4]
After smithy card has been played:
        Cards in hand: 8 [7 expected]
        Cards in deck: 1 [2 expected]
        Played cards: 1 [1 expected]
        Player's hand: [4, 4, 1, 1, 4, 4, 4, 4]
        expected hand: [4, 4, 1, 1, 4, 4, 4]
        Gamestates equal: 0
-------------------------------------------------------------
TEST 1 STATUS:  **** FAILURE **** FAILURE **** FAILURE ***
-------------------------------------------------------------


Bugs discovered in the Smithy card:
-------------------------------------------------------------------------------
1. When a player's deck contains more than 3 cards, the smithy card is drawing
   4 cards instead of 3.



isGameOver() Test:
-----------------------------------------------------------------------------
Testing 0 supply counts empty....Test results: [0 fails]  [1 passes]
Testing 1 supply count empty....Test results: [0 fails]  [27 passes]
Testing 2 supply count empty....Test results: [0 fails]  [702 passes]
Testing 3 supply count empty....Test results: [3456 fails]  [14094 passes]

Bugs discovered in this test:
-----------------------------
1. isGameOver() does not check the supply counts for card #25 (sea hag) or
   card #26 (treasure map) in its check for 3 empty supply counts.


getCost() Test: 
----------------------------------------------------------------------------
all tests passed

updateCoins() Test:
----------------------------------------------------------------------------
all tests passed

fullDeckCount() Test:
----------------------------------------------------------------------------
all tests passed

village card testing:
----------------------------------------------------------------------------
all tests passed

great_hall card testing:
----------------------------------------------------------------------------
all tests passed







Testing teammate 2:  Marco Zamora

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
           Cards in hand: 7 [6 expected]
           Cards in deck: 1 [1 expected]
        Cards in discard: 1 [3 expected]
Player's hand: [4, 1, 4, 4, 7, 4, 4]
Expected hand: [4, 1, 4, 4, 4, 4]
Player's deck: [4]
Expected deck: [4]
Player's discard: [1]
Expected discard: [ 7, 1, 1]
        Gamestates equal: 0
-------------------------------------------------------------
TEST 1 STATUS:  **** FAILURE **** FAILURE **** FAILURE ***
-------------------------------------------------------------

Bugs discovered in this test:
-----------------------------
1. The adventurer card is not actually being discarded from the player's hand
2. Discarded cards do not match up with expected values.  
       Description:
          There is an estate card (#1) that is missing at the end. Before the
          adventurer card is played, there are 3 total estate cards in the hand
          and deck.  Afterwards, there are only 2 in the hand/deck/discard.



Smithy Card Test:
-----------------------------------------------------------------------------
-------------------------------------------------------------
TEST 1: Enough cards in player's deck to draw 3
-------------------------------------------------------------
Starting hand: [4, 4, 1, 1, 13]
Starting deck: [1, 4, 4, 4, 4]
After smithy card has been played:
        Cards in hand: 7 [7 expected]
        Cards in deck: 2 [2 expected]
        Played cards: 0 [1 expected]
        Player's hand: [4, 4, 1, 1, 4, 4, 4]
        expected hand: [4, 4, 1, 1, 4, 4, 4]
        Gamestates equal: 0
-------------------------------------------------------------
TEST 1 STATUS:  **** FAILURE **** FAILURE **** FAILURE ***
-------------------------------------------------------------

Bugs discovered in this test:
-----------------------------
1. The smithy card is being sent to the trash instead of the played card
   pile.



isGameOver() Test:
-----------------------------------------------------------------------------
Testing 0 supply counts empty....Test results: [0 fails]  [1 passes]
Testing 1 supply count empty....Test results: [0 fails]  [27 passes]
Testing 2 supply count empty....Test results: [0 fails]  [702 passes]
Testing 3 supply count empty....Test results: [3456 fails]  [14094 passes]

Bugs discovered in this test:
-----------------------------
1. isGameOver() does not check the supply counts for card #25 (sea hag) or
   card #26 (treasure map) in its check for 3 empty supply counts.


getCost() Test: 
----------------------------------------------------------------------------
all tests passed

updateCoins() Test:
----------------------------------------------------------------------------
all tests passed

fullDeckCount() Test:
----------------------------------------------------------------------------
all tests passed

village card testing:
----------------------------------------------------------------------------
all tests passed

great_hall card testing:
----------------------------------------------------------------------------
all tests passed