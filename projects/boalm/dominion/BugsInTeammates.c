
Below is the information as I emailed it to my teammates.  More details below these emails.


I'm not sure how much detail we're supposed to go into for the bug reports, but here are the first two bugs I found in your code:


TEST 2: = Play adventurer card
kept card count = 1, expected = 2
Assertion failed: ((G.deckCount[thisPlayer] + G.discardCount[thisPlayer]) - (testG.deckCount[thisPlayer] + testG.discardCount[thisPlayer]) == 2)

It looks like the number of kept cards should have been two, but only one card is kept after adventurer is played.  
After looking at the code, the first thing I noticed is that the drawntreasure variable is being incremented by 2 instead of by one, when a treasure card is drawn.  This would cause only one card to be drawn, if the first card is a treasure card.

----------------- Testing Card: village ----------------
TEST 1: = Play village card
drawn card count = 1, expected = 1
hand count before hand = 5, newCards = 1, discarded = 1
hand count = 6, expected = 5

There is one too many cards in the hand after playing the village card.  
It looks like the discardCard method, for discarding the village card from the hand, is commented out.  
Thus the village card will stay in the hand after being played.


I also tested smithy and council_room and they seem to be working fine.  I'm not sure how much additional detail we need to go into.  
Please let me know if you need or would like more detail.  If you'd like me to find more bugs, let me know.  :)

Good Luck and have a good night.

-Matt



I'm not sure how much detail we're supposed to go into for the bug reports, but here are the first two bugs I found in your code:


TEST 2: = Play adventurer card
kept card count = 3, expected = 2

The number of cards in the hand is 1 higher than it should be.  This indicates that 
either the adventurer is not being discarded, or too many cards are being drawn.  After looking at the code, it's 
clear that the line to discard the adventurer card is missing.


TEST 3: = Play village card
drawn card count = 0, expected = 1

It looks like the village card did not draw a card.  It should have drawn two cards.  
The line to draw a card is missing from this function.


I also tested smithy and council_room and they seem to be working fine.  I'm not sure how much additional detail we need to go into.  
Please let me know if you need or would like more detail.  If you would like me to find more bugs, let me know.  :)

Good Luck and have a good night.

-Matt



More information.  As you can see above, I found two bugs in each of my teammates code.  Regarding the usability of my tests,
I found that I didn't need to refactor my tests to work with their code.  I wasn't sure if this would be the case, but it was successful.
For what it's worth, I was able to run tests against their code beyond just the 'card code' as well.  I assume this means my tests 
were generic enough to work.  I didn't get the chance to change my tests, since they worked, so it is hard for me to comment on their
maintainability.  I tried to add some comments, to make them easy to read, but I am aware that some of the reporting is somewhat difficult
to understand unless you have a deep understanding of what the test is doing.  Especially with the random tester.  