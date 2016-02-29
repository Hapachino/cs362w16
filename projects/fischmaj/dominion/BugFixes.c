/***************************************************************
The following is a list of the bugs that I located and fixed in
my own code: 

1. Bug 1 found by Huy - 
BUG: playSmithy incorrectly had the trash
flag set in discardCard().  Caused card to be trashed instead
of discarded. 
FIX: Changed trash flag to 0. 


2. Bug 2 found by Huy - 
BUG:playAdventurer incorrectly drawing cards
until 3 cards discovered instead of two.  
FIX: Changed the while condition
from "while (drawntreasure <=2)" to "while (drawntreasure < 2)" 


3. Bug 3 found by Huy - 
BUG: deck count one less than it should be, 
possible that the card is trashed rather than put back in the 
deck. 
FIX: incorrectly had trash flag set to 1, so changed it to 0.

4. Bug 3 found by Huy-
BUG: council_room hand count is 1 more than normal (5 vs 4). 
FIX:  Could not duplicate this bug.


5. Bug 1a found by Xisheng-
BUG: playAdventurer draws 3 treasures vs. 2
FIX: duplicate of Bug 2.  Already fixed.

6. Bug 1b found by Xisheng- 
BUG: Missing code that implements when deckCount ==0. 
FIX: Could not duplicate this bug. 

7. Bug 1c found by Xisheng-
BUG: Missing code that dumps the handCard just played
FIX: could not duplicate this bug. 

8. Bug 2 found by Xisheng-
BUG: playSmithy trashes the played smithy card.
FIX: duplicate of bug 1 above. Already fixed.

9. Bug 3 found by Xisheng-
BUG: infinite while loop in playFeast
FIX: playFeast has no user interaction, so if user picks an 
empty pile to buy, or a card which is too expensive, there 
is no way to reprompt user, which causes the infinite loop. 
I removed the while loop entirely, and simply return a -1 in 
either of these cases, indicating to the main program an error
has occurred. 

10. Bug 4 found by Xisheng- 
BUG: scoreFor() calls fullDeckCount() which is incorrectly 
implemented. 
FIX: could not duplicate bug. 

11.  Bug 1 found by me-  
BUG: isGameOver not detecting some endstates
problem was a for loop checking all the piles using a hardcoded
and incorrect number.  
FIX:  Added constant to dominion.h and used 
that constant in  for (i = 0; i < 25; i++) instead of '25'. 

12. Bug 2 found by me-
BUG: smithy card not in discard pile
FIX: duplicate of BUG 1 above. Already fixed

13: Bug 3 found by me-
BUG: in playSmithy, discard not increased by 1
FIX: duplicate of Bug 1/Bug 12. Aleady fixed

14: Bug 4 found by me-
BUG: in playAdventurer, too many or too few cards discarded. 
FIX: duplicate of Bug 2. Already fixed above. 

15: Bug 5 found by me-
BUG: player hand count not increased by 2 (too many or too few
cards in the hand). 
FIX: Duplicate of Bug 2/Bug 14. Already fixed

16: Bug 6 found by me-
BUG: player deck count improperly decreased (too many or too
few cards in player's deck)
FIX: Duplicate of Bug 2/14/15 above. Fixed.

17: Bug 7 found by me-
BUG: in great hall, when the position of the great hall card 
is the final card in the hand, the card gained into the hand 
from the great hall is immediately discarded. 
FIX: moved the discard of the great hall card above the call
to the drawCard function. 

18: Bug 8 found by me- 
BUG: in playVillage, discarded village card not placed in 
played cards after play.  
FIX: moved the discard of the played village card above the
call to drawCard function. 

19: Bug 9 found by me-
BUG: in playVillage when the discarded village card is the last
card in the hand, the next card in the deck is not added to the
deck, and instead a -1 is recorded there. 
FIX: Same as bug 18, similar to bug 17 in great hall-- moved 
the call to discard above drawCard. 
