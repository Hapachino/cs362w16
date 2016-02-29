/*
Robyn Lyn's Bug Feedback
--------------------------------
-Smithy card: 1 bug
Bug 1: actual handcount after playing smithy was one more than the expected handcount
Description: Test the handcount before and after calling smithy.  The handcount will be off by 1 card.
Steps to reproduce: See cardtest1
Note: This is the bug you introduced

Fixed this so that the loop to draw cards is now i < 3 instead of i <= 3.

From:

    //+3 Cards
    for (i = 0; i <= 3; i++)
    {
        drawCard(currentPlayer, state);
    }

Changed to:

    //+3 Cards
    for (i = 0; i < 3; i++)
    {
        drawCard(currentPlayer, state);
    }

-Village card: 1 bug
Bug 1: actual number of actions after playing village was 1 more than the expected number of actions
Description: Test the handcount and number of actions before and after calling village. The number of actions will be 
off by 1.
Steps to reproduce: See cardtest3
Note: may be a bug introduced in original file dominion.c

This is because Robyn's test calls cardEffect as opposed to playCard. playCard is where numActions is subtracted after playing a card.
If we don't call playCard to invoke cardEffect, our numActions won't be subtracted properly. When tested using playCard
instead of cardEffect, the number of numActions is correct.

-Great Hall card: 1 bug
Bug 1: actual number of actions after playing great hall was 1 more than the expected number of actions
Description: Test the handcount and number of actions before and after calling great hall. The number of actions will be 
off by 1.
Steps to reproduce: See cardtest4
Note: may be a bug introduced in original file dominion.c

This is because Robyn's test calls cardEffect as opposed to playCard. playCard is where numActions is subtracted after playing a card.
If we don't call playCard to invoke cardEffect, our numActions won't be subtracted properly. When tested using playCard
instead of cardEffect, the number of numActions is correct.

-scoreFor() function: 1 bug
Bug 1: score calculated by scoreFor() function in dominion.c doesn't equal the score manually calculated in this unit test.
Description: manually add score in testScoreFor() function
Steps to reproduce: See unittest3
Note: may be a bug introduced in original file dominion.c

Fixed this so that fullDeckCount returns the sum of deckCount, discardCount, and handCount for the player. Gardens
now counts for the appropriate amount. See fullDeckCount for changes.

Shaun Stapleton's Bug Feedback
--------------------------------

Remodel Card:
Bug 1: Calling the cardEffect function fails.
Description: The function returns all of the cards instead of discarding or trashing any.
Steps to reproduce: See the cardtest1 unit test. 

This bug was due to a logic error in how we were aborting the Remodel Card effect. The condition
used to be that if the cost of the discarded card + 2 was greater than the cost of the card
we were trying to gain, we would return -1 in cardEffect. This is exactly the opposite of what
we want. We need to prevent the Remodel card effect if the cost of the discarded card + 2
is still LESS than the cost of the card we are trying to gain.

From: 
    j = state->hand[currentPlayer][choice1];  //store card we will trash

    if ( (getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2) )
    {
        return -1;
    }

Changed to:

    j = state->hand[currentPlayer][choice1];  //store card we will trash

    if ( (getCost(state->hand[currentPlayer][choice1]) + 2) < getCost(choice2) )
    {
        return -1;
    }

Council Room Card:
Bug 1: Hand counts aren't incremented properly.
Description: Test the handcount before and after calling cardEffect.
The handcount is one more than expected.
Steps to reproduce: Run cardtest4 unit test and view the hand count before and after.
Note: This is a bug you introduced.  

Fixed so that only other players draw a card, excluding the player that played the Council Room Card.

From:

    //Each other player draws a card
    for (i = 0; i < state->numPlayers; i++)
    {
        drawCard(i, state);
    }

Changed to:

    //Each other player draws a card
    for (i = 0; i < state->numPlayers; i++)
    {
        if ( i != currentPlayer )
        {
            drawCard(i, state);
        }
    }

Bug 2: No cards appear to be discarded after cardEffect function call.
Description: Test the discard pile count before and after calling cardEffect. The count is one less than expected.
Steps to reproduce: See the cardtest4 unit test.
Note: I'm not positive if this is a bug but the discardCount is not incremented in the discardCard function as I think it
should. I may be wrong. Probably don't need to fix this bug.

Adventurer Card:
No bugs found during test with my unit test or random adventurer test.

Smithy Card:
Bug 1: Hand counts aren't incremented properly.
Description: Test the handcount and deck count before and after calling cardEffect.
The handcount is one more than expected and the deck count is one less than expected.
Steps to reproduce: See the cardtest2 unit test.
Note: This is a bug you introduced.  

Fixed this so that the loop to draw cards is now i < 3 instead of i <= 3.

From:

    //+3 Cards
    for (i = 0; i <= 3; i++)
    {
        drawCard(currentPlayer, state);
    }

Changed to:

    //+3 Cards
    for (i = 0; i < 3; i++)
    {
        drawCard(currentPlayer, state);
    }

dominion.c:
Bug 1: Compile throws warning "unused variable 'z', 'cardDrawn', 'drawntreasure', 'temphand', and 'x'"
Description: These variables are defined in dominion.c but are never used.
Steps to reproduce: Compile the test using 'make unittest1'

Removed unused variables from cardEffect, as they have now been refactored into their own
playCardEffect functions.

My Introduced Bugs
---------------
playAdventurer
==============
Description: No shuffle before we begin drawing, we could end up drawing from
an empty deck!

Fixed this so that we shuffle if the deckCount of the player is less than 1.

playSmithy
==============
Description: One-off error, for loop to draw 3 cards is i <= 3, should be i < 3

Fixed so that the for loop is now i < 3 instead of i <= 3.

playFeast
==============
Description: Does not set x = 0 when we finish buying one card.

Fixed so that x = 0 is set once we finish buying a card.

playCouncil_Room
==============
Description: all players will draw a card, even when the current player that played
it should be excluded

We now check to make sure that as we loop through all players, only players that
aren't the current player will draw a card.
*/