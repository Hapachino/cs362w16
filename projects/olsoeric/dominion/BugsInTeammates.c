/*****************
 * Author: Eric Olson
 * Assignment: CS362_400 - Assignment #5
 * Description: Results of using my card, unit, and random tests on 
 *              teammates code.  Bug reports on 2 bugs identified.
 ****************/

As per the assignment I made local copies of my two teammates dominion folders.  I moved
my Card, Unit and Random test cases into each folder and refactored them to test the
dominion.c code base of my teammates.  The testing uncovered a number of bugs in the
functions under test.  Two of these identified bugs were written up in formal bug reports.
These were sent to the teammates who owned the respective code, and are also included below.


Bug Report #1 - Mark Giles - adventurerEffect()
===============================================
Title: Adventurer card not removed from hand upon use.
Bug ID: #001-olsoeric

Date: 2/21/2016
Reported By: Eric Olson (olsoeric)
Email: olsoeric@oregonstate.edu

Program: Dominion Game
Executable: dominion.c
Tested On: Linux - flip1.engr.oregonstate.edu
Reproducible: Yes
Severity - (1-10): 6 (Mild)
Priority - (1-10): 7 (High)

Description of Bug:
   At the completion of playing the adventurer card (invoking adventurerEffect() function)
   the played Adventurer card is left in the players hand.  The intended action is to move
   the played Adventurer card to the played pile, thereby removing it from the players hand.

Impacts:
   This bug leaves the Adventurer card in the players hand, allowing them (if action count
   allows) to play the card multiple times.

Steps to Produce/Reproduce:
   While this bug manifests itself upon any game state, a common example is provided below:
      1)  Initialize Kingdom Cards - k[10] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16}
      2)  Initialize Game State - initializeGame(2, k, 5, state);
      3)  Add Adventurer card to hand - state->hand[0][5] = adventurer; state->handCount[0]++;
      4)  Invoke - adventurerEffect(0, 0, 0, temphand[MAX_HAND], state);

Expected Results:
   state->handCount[0] == 7  //(6 Cards, -1 played, +2 treasures drawn)
   state->playedCount == 1

Actual Results:
   state->handCount[0] == 8
   state->playedCount == 0

Localized Bug Code (if known):
   The adventurerEffect() function is missing a call to discardCard() just before the 
   'return 0;' adventurerEffect() may need to be refactored to require handPos as a passed
   parameter in order to pass it along to discardCard().
===============================================

  

Bug Report #2 - Jerry Kim  - adventurerEffect() 
===============================================
Title: Adventurer card seg fault when fewer then 2 treasuress in deck/discard.
Bug ID: #002-olsoeric

Date: 2/21/2016
Reported By: Eric Olson (olsoeric)
Email: olsoeric@oregonstate.edu

Program: Dominion Game
Executable: dominion.c
Tested On: Linux - flip1.engr.oregonstate.edu
Reproducible: Yes
Severity - (1-10): 9 (High)
Priority - (1-10): 3 (Low)

Description of Bug:
   When playing the adventurer card if the player has fewer then 2 treasures in their
   combined deck/discard, the game can at worst trigger a seg fault, or at best return
   an invalid gamestate.

Impacts:
   This bug can either cause the game to crash (seg fault) or can leave the game state in
   an invalid state essentially nullifying the game.  The situation is somewhat rare in that
   generally a player choosing to play the adventurer card will have 2 or more treasures in
   their deck/discard.  But with cards that allow you to trash cards such as Chapel,
   Moneylender, and Remodel a player can end up with few treasure cards, and potentially have
   all of them already in hand, leaving none for the deck/discard.  The game should handle
   this scenario gracefully.
  
Steps to Produce/Reproduce:
   While this bug manifests itself anytime fewer then 2 treasure cards are present in the
   players deck/discard piles, a basic example shown below:
      1)  Initialize Kingdom Cards - k[10] = {7, 8, 9, 10, 11, 12, 13, 14, 15, 16}
      2)  Initialize Game State - initializeGame(2, k, 5, state);
      3)  Set all deck cards to non treasure - state->deck[0][0-10] = 10;
      4)  Set all discard cards to non treasure - state->discard[0][0-10] = 10;
      5)  Add Adventurer card to hand - state->hand[0][5] = adventurer; state->handCount[0]++;
      6)  setup required infos state - infos->drawntreasure = infos->currentPlayer = infos->z = 0;
      7)  Invoke - adventurerEffect(state, infos);

Expected Results:
   state->handCount[0] == 5  //(6 Cards, -1 played, +0 treasures drawn)
   state->playedCount == 1

Actual Results:
   segfault or Undefined(based on what data is in memory in unallocated positions)

Localized Bug Code (if known):
   The issue appears to be a combination of adventurerEffect() and drawCard().  When the entire
   deck/discard have been reviewed and 2 treasures not found the search continues to loop,
   eventually driving state->handCount to a negative number, this causes a lookup to an
   unintended portion of memory and causes the undefined behavior (or seg fault).  A check to
   identify when all deck/discard cards have been reviewed, and then exit the function at that
   time would allow adventurerEffect() to be called regardless of number of treasures available.
===============================================
