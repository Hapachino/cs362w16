--------------
Adventurer
--------------
Description: Inifinite loop occurs when less than 2 treasures available to draw
Cause: Does not make sure it only gets shuffled once
Fix: made sure that the discard pile was not 0 before attempting a reshuffle
Result: All tests passing
Note: Noticed shuffle does not access the discard pile. What is it actually shuffling?
	Every card that the player has. Does this include the cards in the players hand?
	After comparing with the drawCard function, it seems that discard pile is moved
	to deck BEFORE calling shuffle. This means that a bug is revealed within 
	the adventurer function becuase it does not do this. 
	UPDATE: Shuffle was not needed at all since it reshuffles in drawcard, just 
	needed to check for the reshuffle

NOTE: Needed to add a test for adventurer. Did not check for if treasures were
in the discard pile
Description: Adventurer did not reshuffle cards back to deck correctly
Cause: Cards were not moved from discard to deck before calling shuffle
Fix: Moved discard cards to deck before calling shuffle
Result: All tests passing
UPDATE: Since drawcard moves cards to deck from discard, only need to check if the shuffle
needed to occur. Just need to take out some unnecessary code. 

Description: Deals extra cards, does not correctly discard non-treasure cards

Cause: Does not make sure it only gets shuffled once
Fix: Fixed in above test
Result: passing

--------------
Smithy
--------------
Description: 
Description: Hand effects failed
Cause: Error in test, accidentally checked deck effects, not hand effects
Fix: Correctly checked the hand
Result: Test passing

--------------
Village
--------------
Description: does not draw card
Note: Bug not reproducable

--------------
Feast
--------------
Description: If attempted card to be bough is not available, then there is no retry
Cause: Extra x = 0 statement in each if statement
Fix: Only put x = 0 in the else statement
Result: passing

--------------
EndTurn
--------------
Description: played cards do no go to discard pile
Cause: Code not implemented
Fix: Implemented code to move played cards to discard pile
Result: passing
