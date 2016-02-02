/*

Nelson Samayoa
CS 362
Documentation of code coverage from testing
Onid: samayoan

Cumulative (all tests) coverage on file 'dominion.c'
Lines executed:40.11% of 561
Branches executed:50.60% of 417
Taken at least once:35.25% of 417
Calls executed:30.53% of 95
Creating 'dominion.c.gcov'

Considering I only created four unit tests and four card tests, I'd say my statement coverage (lines executed)
percentage is probably pretty decent. I think I could have gotten closer to 50% if I'd varied the players'
hands a bit more, such as by having cases where they had no treasure cards, or just one card, etc... Doing so 
would have also increased the branch coverage because different paths would have been taken in the code to account
for different hands and scenarios. Over all though, I think the amount of tests was low and even with varied hands 
we shouldn't expect anywhere near 100% coverage without creating a lot more tests.

The implications of these are obviously that our code is not being tested quite enough to warrant a release. I know that
the code coverage alone cannot determine the testing quality, but I think that a figure of under 60% is low enough that
I would not feel comfortable releasing the game as-is, but in the end each developer is different and has a different 
percentage they'd feel comfortable with.

I am running gcov with the -f flag, so I was able to get a breakdown by function of my code coverage.
Below I've listed the functions that I was attempting to test. A few of these percentages are 100%, which was a nice surprise.

Functions
'updateCoins' Lines:100.00% of 11 Branches:100.00% of 8 Taken at least once:100.00% of 8
'gainCard' Lines:92.31% of 13 Branches:100.00% of 6 Taken at least once:83.33% of 6 Calls:100.00% of 1
'discardCard' Lines:100.00% of 13 Branches:100.00% of 6 Taken at least once:100.00% of 6
'scoreFor' Lines:100.00% of 27 Branches:100.00% of 42 Taken at least once:92.86% of 42 Calls:100.00% of 3
'cutpurseEffect' Lines:84.62% of 13 Branches:83.33% of 12 Taken at least once:66.67% of 12 Calls:100.00% of 3
'adventurerEffect' Lines:70.59% of 17 Branches:66.67% of 12 Taken at least once:50.00% of 12 Calls:100.00% of 2
'smithyEffect' Lines:100.00% of 5 Branches:100.00% of 2 Taken at least once:100.00% of 2 Calls:100.00% of 2
'salvagerEffect' Lines:100.00% of 7 Branches:100.00% of 2 Taken at least once:50.00% of 2 Calls:100.00% of 4

My 'cutpurseEffect' and 'adventurerEffect' tests could have been improved a bit. As I mentioned earlier, I think these especially
would benefit from varied hands. Other than that I think the only real improvement would be to have more test cases for functions and 
cards.

In the cutpurseEffect method the only section I see with no branch coverage is line 720:

    #####:  720:		      for (k = 0; k < state->handCount[i]; k++)
branch  0 never executed
branch  1 never executed

The only way to reach that section of code would be if the Copper card were at the end of the hand, or if there were no 
Copper card at all. So that would have definitely benefited from more varied hands.

The only section of the adventurerEffect method that is not hit is shown below:

    8:  683:        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
branch  2 never executed
branch  3 never executed
branch  4 never executed
branch  5 never executed
        8:  684:          drawntreasure++;
        -:  685:        else{
    #####:  686:          temphand[z]=cardDrawn;
        -:  687:          //this should just remove the top card (the most recently drawn one).
    #####:  688:          state->handCount[currentPlayer]--;
    #####:  689:          z++;
        -:  690:        }
        -:  691:      }


That section of could could have been hit if I forced the drawn card to be a some Treasure card.
I was relying too much on initializeGame to set my cards in this card test. I did, however, forge the hands in some of my
other card tests. The adventurer card test just happens to be one that really would have benefited from that, and unfortunately I did
not forge hands here.

*/
