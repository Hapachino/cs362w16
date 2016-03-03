Name:   Ian Bender
Course: CS362
Date:   2/28/2016
Assignment 5 - Bugs in teammmates' code.

Bugs Found by Teammates
-----------------------
Location: dominion.c:682
Function: playSmith()
Description: Hand count is decremented by one card, rather than incremented
    by two cards.
Expected: Hand count is incremented by two cards.
Corrections Made: 
    Error in for (i = 0; i > 3; i++) - Condition is incorrect on this and
    should be i < 3, otherwise the loop body never executes. This particular
    loop performs the drawCard() function for the current player. Three cards
    were never drawn because of this, but one card is still discarded at the
    end of the function, which matches the bug description.


Location: dominion.c:660
Function: playAdventurer()
Description: Hand count is unchanged, discard is unchanged.
Expected: Hand count is incremented by two cards, discard should increase.
Corrections Made:
    Closing bracket for if statement starting in line 656 was in the wrong
    position. Because of this, the drawCard() function was only called if the
    deck was already empty. By moving the closing bracket to immediately after
    the shuffle() function, the error is corrected and cards are drawn as
    expected.



