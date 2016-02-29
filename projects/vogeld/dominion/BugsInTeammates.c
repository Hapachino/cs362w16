David Vogel
CS362, Assignment 5, Bugs in Teammates' Code
Due: 2-28-2016

Teammate 1 - Robert Jackson:
Test Case Changes
- cardtest1.c: changed test from cardEffect() to smithyCard() which is the refactored function. cardEffect() takes parameters for card name, choices, game state, hand position, & bonus. Teammate's has game state & hand position.
- cardtest4.c: needed to use refactored method adventurerCard() instead of cardEffect(). Parameters differed as in cardtest1.
- adventureRandomTest.c: original test file was randomtestadventurer.c. I chanaged the name so the makefile would not have to be altered. Parameters differed as cardtest1.
- smithyRandomTest.c: same as with other random test. Smithy method, as mentioned above is smithyCard().

Bugs
1. In adventurerCard(), hand count fails
2. In smithyCard(), hand count and deck count fail.


Teammate 2 - Ian Bender:
Test Case Changes
- cardtest1.c: used refactored playSmithy() instead of cardEffect(). Former only takes player, game state, & hand position. Latter takes parameters for card name, choices, game state, hand position, & bonus.
- cardtest4.c: used refactored playAdventurer() instead of cardEffect(). Former only takes player & game state, latter takes parameters as in cardtest1.
- randomtestadventurer.c: refactored adventurer method is as in cardtest4.
- randomtestcard.c: refactored smithy method is as in cardtest1.

Bugs
1. In adventurerCard(), hand count and deck count fail.
2. In smithyCard(), hand count, deck count, & extra coins fail.