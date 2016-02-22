/*
 
                                        bug1.c
 Patrick Burrell
 CS 362 - Winter 2016
 Assignment 3
 Bug reporting
 
 unittest1.c - drawCard()
 The drawCard() function passed all test conditions with the exception of the instance
 where the function is called for a player with an empty deck (deckCount = 0). After 
 tracing through the code in the drawCard() for the deckCount <= 0 condition, it became
 clear that this error comes about because refilling the deck with cards from the 
 discard pile doesn't accomplish anything when the discard pile is empty. After this 
 attempt, the deckCount is set equal to discardCount, and drawCard() returns -1 when
 deckCount = 0. Since drawCard() draws cards from the discard pile, it is appropriate for 
 the call to the function to fail under these conditions (where there is no card to draw), 
 but it might be appropriate to include an error message when this condition is met that 
 prompts a player that that option is unavailable.
 
 
 unittest2.c - buyCard()
 The buyCard() function passed all test conditions.
 
 
 unittest3.c - discardCard()
 The discardCard() function passed all test conditions. 
 
 
 unittest4.c - updateCoins()
 The updateCoins() function passed all test conditions.
 
 
 cardtest1.c - smithy
 On the initial run, this test failed for properly changing the player's hand count, 
 discard count, and deck count. My original version of the test only printed a failure
 message saying the respective value did not change by the correct amount, so I added
 the amount that the value did change by to get a better sense of what was going wrong. 
 This showed that the bug was causing the player's hand count to increase by one more
 card than it should have, the discard count to remain the same, and the deck count to
 decrease by one more than it should have. The errors in changes to deck and hand count
 can be traced to a bug in the loop written for playSmithy() that causes it to run four
 times rather than three. The issue with discard count not changing is either due to an
 error in the discardCard() function or a misunderstanding on my part about the change
 to expect to discardCount() after a smithy card is played.
 
 cardtest2.c - adventurer
 This card was a little more difficult to develop a unit test for, and I ended up 
 writing the test for a call to playCard() for the adventurer card rather than just
 calling playAdventurer.
 The bugs discovered for the test suite were both related to discarding: the player's
 discard count did not increase by the expected amount (it didn't change at all), and the
 cards in the player's discard pile did not match up with what should have been discarded
 during the turn. This bug was introduced by me into the code.
 Note: the last condition tested is the special case where two treasure cards are not found
 before all cards in the deck were searched. Due to the random nature of shuffle, the test
 did not account for changes to a player's discard or deck size, but tested all other state
 changes, including that the proper coin amount was added to a player's total after the
 shuffle. These tests were all passed for the shuffle case.
 
 cardtest3.c - great_hall
 The structure of this test was very similar to the one for smithy (cardtest1.c) except 
 that it tested the function after a call to playCard() rather than a specific all to 
 playSmithy(). The results were similar, with great_hall only failing tests related to the 
 discard count for the playing player. The test was written to expect a one card increase 
 in discard count, but the count stays the same after a call to playCard involving Great 
 Hall. As this error still occurs after a full play of the card, it seems that there is a 
 bug in the overall implementation of dominion where cards are not being properly 
 discarded.
 
 
 cardtest4.c - embargo
 Testing for embargo followed a very similar format to that of the tests for smithy and
 adventurer, but the tests showed some strange bugs. In every run of playing the embargo 
 card, the player's coin total was not updated correctly. It should have increased by 2 
 but was always decreased by either 1 or 5. Another error only occured for the highest
 player in the game (e.g. player 3 in a 3 player game) - card 499 (the last card) in the 
 hand of one of the other players seemed to have changed. After tracing back through the 
 code for playCard(), cardEffect(), and the embargo case in the switch statement, I am at
 a loss for what is causing the errors to occur. I have also reviewed my test conditions 
 closely but have not found an obvious error there either.
 
 */

