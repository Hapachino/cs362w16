Overall, the testing methods for the random tester were easiest to test against
the teammates code. I think the reason for this is that when I created the card tests
previously, I modified the dominion code to pull out the card functions and thus
made the tests call that isolated function instead of mocking out a way to call the
code exactly how it originally was. Part of this difficulty was due to an assignment
asking us to take the card operations that were in the switch statement and
pull them out into their own functions. However once I understood how the others did
their assignments ( or changed the code since ) running my tests agains their dominion
code was relatively easy. The easiest by far was running the random tester, which
mocked out the actual cardeffect function to call the code. This made the portability
greater I think and just so happened to find the most bugs as well. One aspect of this
assignment that was interesting was comparing the code coverage metrics from running
gcov on three different sets of dominion code. It came as no surprise that they were
similar but as a newcomer to gcov it showed me how powerful gcov is as a tool.
For both of the stryffemDominionCode and the siddonjDominionCode ( both teammates ) code,
my unit tests failed to find any bugs. the only tests that found bugs were the random
testers and they found similar bugs in both code bases ( as well as my own copy of dominion )
which makes me believe that the bugs are in fact somewhere outside of the cards being
tested and are located somewhere else in the dominion code. Also, the failing tests for
the smithy card were all off by one errors, which makes my test suspect as the cause for
the bugs (i.e. it is possible that there is a bug in my test and not in the dominion code base).

Bug Reports for : stryffemDominionCode

  Title: Dominion Adventurer card fails to increment hand count correctly.

  Project: Dominion
  Version: 1.0

  Type: Bug, major
  Reported by: Andrew Pierno
  Email: piernoa@oregonstate.edu

  Created: 2/21/16
  Updated: N/A
  Resolved: N/A

  Type: Bug
  Status: Open
  Priority: Major
  Resolution: Not Resolved
  Affected Version: 1.0
  File name: dominion.c
  Environment: Mac OSX 10.11.1

  Description:
    The adventurer card failed on a test case where the hand count returned by playing the adventurer
    card was incorrect. It appears that
    this is the only test case I have seen where the count was off by more than one (after having run
      it on my code base and on the other teammates code base ). It looks like there
    is an error in the drawn tresure while loop where the inequality is <=2 causing an extra treasure
    card to be drawn.

  Code causing bug:
    while(drawntreasure <= 2)
    {
      if (state->deckCount[currentPlayer] < 1)	//if the deck is empty we need to shuffle discard and add to deck
      {
          shuffle(currentPlayer, state);
      }
      drawCard(currentPlayer, state);
      cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];	//top card of hand is most recently drawn card.
      if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
          drawntreasure++;
      else
      {
          temphand[z]=cardDrawn;
          state->handCount[currentPlayer]--;	//this should just remove the top card (the most recently drawn one).
          z++;
      }
    }

  Suggested fix:

    while(drawntreasure < 2)
    {
      ...
    }




Bug Reports for : siddonjDominionCode


  Title: Dominion Smithy Card fails to accuartely decrement hand count after playing smithy card.

  Project: Dominion
  Version: 1.0

  Type: Bug, major
  Reported by: Andrew Pierno
  Email: piernoa@oregonstate.edu

  Created: 2/21/16
  Updated: N/A
  Resolved: N/A

  Type: Bug
  Status: Open
  Priority: Major
  Resolution: Not Resolved
  Affected Version: 1.0
  File name: dominion.c
  Environment: Mac OSX 10.11.1

  Description:
    In general the bug shows up as failing to show a net increase of two cards after the smithy card is played.

    - In the smithy card a test failed when the hand count for player 0 ( of two players, zero indexed ) failed to
    show that the player had a net increase of two cards ( gain three and discard one )

    - In the smithy card a test failed when the last card in hand was played, the player should have had
    a net increase of two cards.

    - When there was only one card in hand, there was also a failing test that failed to show the player's
    hand decremented by two.

  Code causing bug:

  for (i = 0; i <= 3; i++)
  {
    drawCard(currentPlayer, state);
  }


  Suggested fix:

  for (i = 0; i < 3; i++)
  {
    drawCard(currentPlayer, state);
  }
