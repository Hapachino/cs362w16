/smithytest 
handCount: 495
handCount: 5
discard count 0
Hand count before: 5; hand count after: 8
Deck count before: 495; deck count after: 491
smithytest: _smithyTest.c:122: main: Assertion `(Gcopy.deckCount[p1]-3) == G.deckCount[p1]' failed.
Aborted (core dumped)

Bug in smithyEffect was found to be in the part to modify the current player's deck count after three cards 
more cards have been pulled from it. It draws actually 4 cards instead of 3, affecting both the deckCount 
and handCount. Bug seems to be isolated in the loop exit condition that is in charge of drawing the cards, 
which makes it cycle 4 times instead of 3. The final card count of the hand seems to end up as the correct
 value because there is a discardCard executed after the loop, which decrements the hand count. 

------------------------------------------------------------------------------------------
/villagetest 
villagetest: _villageTest.c:102: main: Assertion `numActions1 +2 == numActions2' failed.
Aborted (core dumped)

Only one bug was found in village test, which has to do with dealing out the correct number of actions. 
It happens currently to deal only one action whereas correctly it should deal out two actions. Probably 
easily fixed with a loop, which has the slight, added benefit of making the code more maintainable. 