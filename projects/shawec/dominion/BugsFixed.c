BUG FIXES
===================================
Smithy - Bug found by both teammates:
Both of my teammates found that there were bugs in smithy. 
Using their feedback, (philips was the most helpful) I was able to use gdb to find that the problem was drawcard was called 4 times and when looking closer into it, I had >= rather than >. 

Adventurer - This bug was fixed due to my knowledge of it, however briefly found by Richard:
Richard's feedback did not allow me to find what the issue was within adventuruer. This was a bug that I introduced, and what happened is that shuffle is at 1 or less, rather than when the deck is at 0. I think the premature shuffle was what caused the numbers to be off. Had I not know what the error was to begin with, then I probably wouldn't have been able to figure out what was causing it very easily. 

Village - Bug found by Philip: 
Philip found that the actions weren't matching up, and that it wasn't adding the two actions. Using GDB, I was able to see state wasn't updating after setting watch on state. Even compiling will show this bug though as a warning, since it's a pointless statement to have. 

Embargo - Neither teammate found bugs (which I'm guessing this is because they didn't do tests for it)
I did use GDB to test this, and noticed that the coin state wasn't updating. This is super simple to do by using watch on the state and you can see when values change. It was a very similar bug to the village. Even compiling will show this bug though as a warning, since it's a pointless statement to have. 

TEAMMATE FEEDBACK
======================
Feedback From Richard:

I got my tests running with Cierra's code.  Summary:

Unit Tests - no fails.

Random Tests - lots of fails. Too many to be of use for now.

Card Test - smithy, after one play:
1. the hand contained an extra card.
   Expected 7 cards in hand, found 8.
2. the deck contained one less than expected.
   Expected 2 cards in deck, found 1.
3. expected 1 played card (smithy) found 1 played cards.
4. discard was ok.  passed.
5. the other player hand, deck, played, and discard passed.

Card Test - adventurer, after one play:
1. the hand contained passed, 7 expected, 7 found.
2. the deck had 1 less card than expected.
   2 expected 1 found.
3. expected 1 played card (adventurer), found 0.
4. expected 5 discards but found 7.
5. the other player hand, deck, played, and discard passed.

After playing one smithy:

--------- Testing smithy ---------
Player 0's hand:
#  Card
0  Copper
1  Silver
2  Gold
3  Curse
4  Duchy
5  Gardens
6  Feast
7  Adventurer

Player 0's deck:
#  Card
0  Province

Player 0's played cards:
#  Card
0  Smithy

Player 0's discard:
#  Card
0  Mine
1  Remodel
2  Steward
3  Village
4  Baron


After playing one adventurer:

--------- Testing adventurer ---------
Player 0's hand:
#  Card
0  Copper
1  Copper
2  Copper
3  Smithy
4  Adventurer
5  Silver
6  Silver

Player 0's deck:
#  Card
0  Silver

Player 0's played cards:

Player 0's discard:
#  Card
0  Gold
1  Gold
2  Gold
3  Village
4  Baron
5  Feast
6  Gardens

===============================
Feedback From Philip:

Smithy card:
Bug: The after state of the handcount was higher than it should be
Description: It appears that instead of drawing 3 cards, the Smithy card is drawing 4 or more. 
How to Reproduce: Run cardTest3(). 

Village card:
Bug: The player's actions don't match the +2 that they should after using the card
Description: No actions are added when using the Village card.
How to Reproduce: Run cardTest1().

