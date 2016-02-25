/************
 * Eric Olson
 * Assignment #5 
 * Log of Errors Introduced to dominion.c
 ************/

As part of assignment #5 I corrected any known errors found in the dominion.c file.  Errors
corrected were either self imposed in assignment #2, self identified in the base code or
reported by teammates as part of Assignment #5.  Once all corrections made tests were rerun
and no errors found in code.

smithy_play():
Fix #001 - Self-Imposed Bug:  Changed the trash flag in the discardCard function call to 0.  
           Previouslly 1 this was causing the card to be trashed upon play rather then moved
           to the played pile, and then discarded.

adventurer_play():
Fix #002 - Self-Imposed Bug:  Changed the check for treasure card to include gold.  Previouslly
           this only checked for copper and silver meaning gold cards would not be drawn to hand.

Fix #003 - Original Bug:  Added a counter equal to total cards in deck+discard.  This counter is
           decremented each time a card is evaluated for treasure.  If all cards have been evaluated
           and 2 treasures not found the process stops.  Previouslly this would cause a seg fault
           if fewer then 2 treasures were in deck+discard.

Fix #004 - Original Bug:  Added a call to discardCard() to properly remove the adventurer card from
           the players hand once played.  Previouslly this was not present leaving the adventurer
           card in hand and could be played multiple times.  

council_room_play():
Fix #005 - Self-Imposed Bug:  Changed the +1 increment to corectly increment numBuys instead of
           numActions.  Previouslly this added an action instead of a Buy as intended.

cardEffect():
Fix #006 - Self-Imposed Bug:  Changed the order of paramaters passed to village_play() to be correctly
           (currentPlayer, state, handPos).  Previouslly currentPlayer and handPos were swapped and this
           led to some undefined behavior(including a possible seg fault) depending on the values in each.

village_play():
Fix #007 - Self-Imposed Bug:  Changed the assignment statement for numActions to a = rather then an ==.
           This results in the actions actually being increased, rather then an equality check and no
           action at all.

cutpurse_play():
Fix #008 - Self-Imposed Bug:  Changed the equality statement int he second imbeded if statement to an
           == rather then an =.  Previouslly this was assigning a copper to each card in hand, and
           returning true always, rather then checking IF the card was a copper.
