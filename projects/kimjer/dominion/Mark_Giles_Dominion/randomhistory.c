I was able to get at least 30% coverage, which is increased compared to last time.

This involved initializing certain parts of the infosStruct to dummy values and randomizing all others in such a way that they meet the preconditions for it to succeed. 

In the adventure card test, I made sure to test the two main fail cases: one located in the drawCard() function and another in the logic of the adventurer card effect function. 

When randomizing the decks of the cards, I had to make sure to take into to account the initializing of the deckCount, handCount, etc. values manually and compare them after the gameState struct is passed into drawCard(). Two cases were dealt with regarding the deckCount - when it was equal to 0 and when it was non-zero. When the deck count is 0, it was necessary that the discard pile be non-zero in order that the deck may be replenished. So this was checked for. 

When it was non-zero, the discard pile could be at any value. The drawCard() function affected, of course, the handCount, deckCount, and the discardCount, all of which were checked. 

In the testing of the adventurer effect logic, it was necessary, as with the drawCard(), to account for the two cases of the deckCount. However, I realized that my tests would crash every time because I had not made sure that my decks or discard piles contained at least two treasure cards from which the player should draw. To make things easier, I coded it so that the deck always contains at least two treasure cards. 

I felt that this was sufficient testing in the general case but to be more robust I think I can actually check to make sure that each value of the decks, discard piles and hands were correct before and after. 

The testing of the village card was in many ways similar to the adventurer card but with the added check of the action count of the player and to make sure that the hand count was the same before and after since the village card itself is discarded once used. 

No bugs were able to be detected during in these tests. 

I