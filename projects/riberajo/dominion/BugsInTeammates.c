Kyle's Bug list -----------------------------------------------------------------

  ** Bug #1 - Test smithyCard **
  Player 1 Errors
  - Handcount mismatch, -1 instead of +3
  - deckcount mismatch - remains the same, but deck should be -3 if three were
  cards were to be taken
  - failed test

  Player 2 Errors (state change)
  - handcount mismatch - expected 0 actual 3
  - deckcount mismatch - expected 10 actual 7

  ** Bug #2  Test adventurerCard **
  Player 1 Errors
  - discard count mismatch - Expected 0 (stached deck) - actual 1

   ** Bug #3 - scoreFor function - **
     - score not computed correctly
     FAIL TEST: Scores did not compute correctly

--------------------------------------------------------------------------------


Ava's Bug List -----------------------------------------------------------------

  ** Bug #1 - Test smithy Card - **
  - deck count mismatch - expected 2 - actual 1

  ** Bug #2 Test adventurerCard - **
  Test2 fail: This case tests the function's 'ability to get cards from the
  discard pile because there is only 1 treasure card in the deck.
    FAIL: Handcount mismatch - actual + 1
    FAIL: deck count mismatch - actual -5
    FAIL: discard count mismatch - actual + 4

    Player 2 state change error
    - Handcount actual -1
    - Handcount played actual 1

 ** Bug #3 - Test council room - **
   - Infinite loop caused by dominion line 	  if ( i = currentPlayer ) #692

 ** Bug #4 - scoreFor function - **
   - score not computed correctly
   FAIL TEST: Scores did not compute correctly

--------------------------------------------------------------------------------

Code refactoring ---------------------------------------------------------------

  Due to the different ways my teammates have refactored their code I had to
  change my function calls within my tests. However, I only had to change the
  name and parameters it took (1-2 changes per test) so I think my tests are
  fairly maintainable.

  Some examples from Kyle's code:
   -   smithyCard(post, p, handPos);
   -   adventurerCard(post, p);

  Some examples from Ava's code:
   -    smith(post, handPos, p);
   -    adven(post, handPos, p, drawntreasure, cardDrawn);

   My refactored examples:
    -   playSmithy(handPos, post);
    -   playAdventurer(post);

  In one case with Ava's adventurer card I had to create variables for
  drawntreasure and cardDrawn within my test and pass it to the function.

--------------------------------------------------------------------------------



  Based on how your teammates refactored the code, what are the method names, what are the parameter passed, you have to change your tests. This will also indicate how maintainable your tests are.
