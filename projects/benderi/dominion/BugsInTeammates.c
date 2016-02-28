Name:   Ian Bender
Course: CS362
Date:   2/28/2016
Assignment 5 - Bugs in teammmates' code.

Teammate 1 (David Vogel):
Test Case Changes (my reference only)
- cardtest1.c: function parameter order changed to match teammate's code
- cardtest2.c: function parameter order changed to match teammate's code
- cardtest3.c: had to rewrite code to call cardEffect() function instead of the
                refactored playCouncil_room() function that I created in my
                version.
- randomtestadventurer.c: function parameter order changed
- randomtestcard.c: function parameter order changed

*BUGS (for teammate correction)
1. playSmithy() - Player does not gain/discard the correct # of cards.
    NOTES: Player is gaining 4 cards instead of 3, error in for loop.



Teammate 2 (Robert Jackson):
Test Case Changes (my reference only)
- cardtest1.c: refactored code for Smithy card is named smithyCard() instead
                of playSmithy(), only passes gameState and handPos
- cardtest2.c: refactored code for Adventurer card is named adventurerCard()
                instead of playAdventurer(), only passes gameState
- cardtest3.c: refactored code for Council Room card is named
                councilRoomCard() instead of playCouncil_room(), reordered same                 parameters 
- cardtest4.c: refactored code for Village card is named villageCard(), passes
                only gameState and handPos
- randomtestadventurer.c: refactored Adventurer call, same as cardtest2
- randomtestcard.c: refactored Smithy call, same as cardtest1

*BUGS (for teammate correction)
1. smithyCard() - Player does not gain/discard correct # of cards.
    NOTES: Player is gaining 4 cards instead of 3, error in for loop.
3. councilRoomCard() - Players 2-4 did not draw a card.
    NOTES: Iteration variable, i, not reset to 0 in second for loop, where
    other players draw a card. The loop body is never executed.
4. villageCard() - Player did not gain/discard correct # of cards.
    NOTES: Player discarded but missing function call to draw additional card.
