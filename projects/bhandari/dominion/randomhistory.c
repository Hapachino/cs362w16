/*
Rishi Bhandarkar
CS 362 - randomhistory.c
*/

To generate my random testers, I attempted to randomize as many elements of the Gamestate
as I could before playing the card to test. To do this, I began with randomlly choosing
between 2 and 4 players inclusively. After this, I randomlly chose a random player to be 
the current player. After that, for each player in the game, I randomlly chose a number of
cards to be in their hand, between 0 and MAX_HAND (which was set to 500). I then randomlly 
filled the hand with real cards. To build each players' deck, I first calculated the maximum
size of the deck. This was determined by sutracting each players' current hand size from 
MAX_DECK (which was set to 500). This was the maximum size of the deck remaining since adding 
our hand to the deck should still be less than or equal to MAX_DECK. As this point, I randomlly 
chose a number 0 to MAX_DECK-handSize, and this was the amount of cards in a players' deck. Then,
I randomlly chose that many cards to make up the deck. These numbers were different for each player.
This was the extent of the randomization. After this, added the card under test to my hand, then played
the card. After playing the card, I was able to test the gameState based on the specifications.

File: 'randomtestadventurer.c'
Lines executed: 27.89% of 588
Branches executed: 29.50% of 417
Taken at least once: 20.62% of 417
Calls executed: 18.00% of 100
Function: playAdventurer(struct GameState*)
blocks executed: 100%

In the previous, non-random version of the card test that tested the
Adventurer card, the test achieved 67% of blocks executed. This means that
by implementing a random tester, we were able to achieve greater coverage. 
This can be because the random generation of test cases allows for better test cases,
as well as the fact that we generated 1000 test cases rather than just using
1 case. In addition, using this random method allowed me to discover an additional
bug that I didn't discover in the previous test. In the 1000 tests, there were some
instances where the cards drawn from the Adventurer card were cards other than
treasure cards. The random tester was also able to detect the intentional bug 
introduced back in week 1, where the adventurer card drew an additional treasure card.
While creating the test module, I had to think about the specification of the handCount
at the end of playing the Adventurer. The Adventurer card does not bother discarding the 
Adventurer card after playing it, but I believe this is a bug and the card should be discarded
after 2 treasure cards are drawn. Because of this, I believe the hand count should increase by 1,
and not 2.


File: 'randomtestcard.c'
Lines executed: 28.06% of 588
Branches executed: 28.54% of 417
Taken at least once: 19.18% of 417
Calls executed: 18.00% of 100
Function: playSmithy(struct GameState*)
blocks executed: 100%

In the previous, non-random version of the card test that tested the Smithy card,
the test achieved 100% coverage of the Smithy function. The random tester for the 
Smithy card also achived 100% coverage. While using this random tester, it was able
to detect the bug intentionally introduced to the Smithy card that allowed the player
to draw 4 cards instead of 3. In addition, I had to think about how much a hand should
increase by after using this card. I decided that the discard should occur immediately after
drawing three cards, so the hand should increase by 2 cards.