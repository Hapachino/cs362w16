/*
Nelson Samayoa
CS362
Bug fixes and code changes
 
 
Bug 1 
    (Summaries provided by teammates)
    Often, after playing the adventurer card, the total set of cards in the
    player's possession (among all piles) is altered. This is contrary to
    what would be expected, since the adventurer card only draws cards from
    the player's own deck. More specifically, it appears that when the last
    two cards in the pre-test player's deck do not happen to be treasure 
    cards, the post- player has gained a treasure card that seems not to 
    have come from that player's deck... As can be seen, it appears as though 
    one Estate card (enum 1) has been transformed into a copper card (enum 4).
    
    This bug happens to be one I introduced in assignment 2. To fix it I simply
    changed the line below in the adventurerEffect card:
    
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]=copper;
    
    I change that card to the following:
    
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];
    

Bug 2 fixed    
    When Adventurer card is played, the playing player's deck count is always increased 
    by exactly two cards, regardless of conditions in the player's hand and deck. 

    After debugging using GDB, I discovered that the issue here is not actually in my code
    specifically, but rather caused by the fact that the DiscardMethod is not called in any
    of the card effect methods. This issue has been discussed on Piazza and would require 
    a lot of changes to make the tests pass, but may result in broken code when the game 
    is actually played outside of a testing scenario.


Bug 3 fixed
    In the original implementation of dominion.c, there was a line that set unused cards to -1:
    
    state->hand[currentPlayer][handPos] = -1;
    
    This was causing a problem when calculating the final score causing the score to be less 
    than expected. The reason is that -1 is the value of the curse card. So when the scoreFor
    method was run it would count one or more curse cards, thus reduced the final score. I 
    changed the line to the following:
    
    state->hand[currentPlayer][handPos] = 99;
    
    This fixed the issue because there are no cards in the 99th index of the card enum, thus no
    "valid" cards were incorrectly included in the final score calculation.

Bug 4 fixed
    One of the bugs I introduced was in the line that was originally 

    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]

    I added "=copper" to the end and the result was this:
    
    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]=copper
    
    This resulted in incorrect coin counts in the tests. Upon changing it back, the coin counts in
    the tests became correct.
    
Bug 5 fixed
    In the smithyEffect card I had introduced a bug in the for loop which increments the index 
    before checking it (++i). It was originally incrementing after checking (i++) as would be
    expected in a for loop. The result was not seen until Bug 4 was fixed, and yet the symptoms
    of Bug 4 persisted when copper cards were toward the end of the hand. Setting it back to the
    original fixed bug 4 completely.
    
Bug 6 fixed
    The last bug I introduced is in line "discardCard(handPos, currentPlayer, state, 0);" of the method 
    cutpurseEffect. I changed it to 
    
    discardCard(handPos, currentPlayer, state, 1);
    
    The result was that the wrong card was getting discarded, sometimes causing incorrect coin counts and 
    failures when tests checked for the correct card being discarded. Once I changed it back to the original,
    the discard counts in the tests that check for it became correct.
    
Bug 7 fixed
    In the original implementation of dominion.c there was a check that was incorrect. The result was
    that the cutpurse card never discarded any copper cards as expected. The block of code for the 
    following if statement was never executed because the value of j never reached the handcount.
    
    if (j == state->handCount[i])
        
    The for loop that wraps the if statement (and defines j) sets j to 0, and exits when j becomes
    equal to the handcount:
    
    for (j = 0; j < state->handCount[i]; j++)
        
    I fixed the bug by changing the if statment to this:
        
    if (j == state->handCount[i] - 1)
        
    Upon rerunning my tests the discard and deckcounts became correct.
*/