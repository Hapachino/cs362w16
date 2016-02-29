/*
Jack Holkeboer
Oregon State University
holkeboj@onid.oregonstate.edu
CS362
Assignment 5

I ran the following tests against both teammates' code:
make unittestresults.out (unit tests and card tests)
make randomtestadventurer.out (random test of Adventurer card)
make randomtestcard.out (random test of Great Hall card)

In order to run these tests properly, I had to remove several asserts
that were not failing in my tests, but were failing for my teammates' code.
I replaced these with print statements that allowed the tests to run.

Since there are bugs in the code as it was given to us all, I tried to focus on 
areas where the test results for my code diverged from those for my teammates.

************************************
Teammate 1: Kyle Collins (collikyl)
************************************

Bug 1: 
********************************************************************************
*** Adventurer does not always give player two treasure cards ***
********************************************************************************
Look in unittestresults.out for the following line:
---- Did player 1 receive two treasure cards?
Pre: 3	Post: 7
Failed.

You'll notice that when the test was run for player 1, the treasure count 
goes up by 4 instead of 2.  However, this test passes when it is run for player 0:
---- Did player 0 receive two treasure cards?
Pre: 3	Post: 5
Passed.

Here is the code of the test:

        printf("---- Did player %d receive two treasure cards?\n", player);
        printf("Pre: %d\tPost: %d\n",preTreasureCount,postTreasureCount);
        if (preTreasureCount + 2 == postTreasureCount) {
            printf("Passed.\n");
            testsPassed++;
        } else {
            printf("Failed.\n");
        }
        testsRun++;

To fix this, you'd need to figure out why there would be a scenario when adventurer 
awards more than 2 treasure cards.

How to reproduce: Run my tests (make unittestresults.out), or play adventeurer for player 1 on a clean game.


************************************
Teammate 2: Shaine Afzal (afzals)
************************************


Bug 1: in Great Hall card
********************************************************************************
*** Player does not gain an action. ***
********************************************************************************
Look at the test results in randomtestcard.out after running the test with "make randomtestcard.out"
You will see many failed tests that look like this:
---- Did player 0 gain one action?
Test Failed.
---- Did player 1 gain one action?
Test Failed.

The Great Hall card is supposed to award one action to the player who plays it.
This issue happens for any player who plays the Great Hall.
This is how the test looks in my code:
    
    if (testGame.numActions == cleanGame.numActions + 1) {
        // printf("Test Passed\n");
        localTestsPassed++;
    } else {
        printf("---- Did player %d gain one action?\n",player);
        printf("Test Failed.\n");
    }

How to reproduce: Play the Great Hall card with any player on a clean game.

Bug 2: 
********************************************************************************
*** Playing adventurer alters the other player's deck count  ***
********************************************************************************
Look at the test results in randomtestadventurer.out after running the test with "make randomtestadventurer.out"
You will see many results like this:

    ---- Did the other player's deck change?
    Test Failed.

This did not happen when I ran the tests on my code.
The way this is checked in the code is like this:

    if (testGame.deckCount[otherPlayer] == cleanGame.deckCount[otherPlayer]) {
        // printf("Test Passed\n");
        localTestsPassed++;
    } else {
        printf("---- Did the other player's deck change?\n");
        printf("Test Failed.\n");
    }
    localTestsRun++;

So it is not actually looking at the contents of the deck, but rather the deckCount.

How to reproduce: Start a game with two players, have player 1 play an adventuer, then see if 
player 2's deckCount has changed.

*/