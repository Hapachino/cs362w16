/*

Nelson Samayoa
CS 362
Documentation of random testing
Onid: samayoan

CUTPURSE CARD
    Old coverage numbers:
    Function 'cutpurseEffect'
    Lines executed:84.62% of 13
    Branches executed:83.33% of 12
    Taken at least once:66.67% of 12
    Calls executed:100.00% of 3
    
    function cutpurseEffect called 1 returned 100% blocks executed 79%
    ...
    3:  718:		  if (j == state->handCount[i])
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:  719:		    {
    #####:  720:		      for (k = 0; k < state->handCount[i]; k++)
branch  0 never executed
branch  1 never executed
        -:  721:			{
        -:  722:			  if (DEBUG)
        -:  723:			    printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
        -:  724:			}
    #####:  725:		      break;
        -:  726:		    }
    ...
    
    I cut out lines that aren't of interest. The entire output can be seen in randomtestcard.out    
    The block that was never executed (lines 720 to 725) were missed because the discarded copper (gold in this code because of an introduced bug) was never at the end of the hand. The break at line 716 forces an exit from the for loop as soon as the copper (gold)
    card is detected, meaning line 720 is never reached. In order to reach lines 722 and 733, I had to also set DEBUG to 1 before 
    running the test. I varied the hands by making it so sometimes the hands will have no treasure cards at all, and when there is a 
    treasure card it is now added to a random hand position in the hand.

The resulting coverage is:
    Function 'cutpurseEffect'
    Lines executed:100.00% of 14
    Branches executed:100.00% of 12
    Taken at least once:91.67% of 12
    Calls executed:100.00% of 4

    Notice this is a huge improvement with the old coverage numbers. In order to get these numbers I did have to set the value of
    the constant DEBUG to 1, and fix some big bugs, as noted below.

Bugs that I fixed in order to improve coverage:
    1) In the discardCard method, the line
        state->hand[currentPlayer][handPos] = -1;
        I changed to 
        state->hand[currentPlayer][handPos] = 99;
        
        I made the change because -1 is the curse card, so my coin counts were always wrong due to a unneeded curse that was
        added to the hand when the player played any card.
        
    2) In the cutpurseEffect method I changed this line:
        if (j == state->handCount[i]){
       to this:
       if (j == state->handCount[i] - 1){

        I made the change because when j is set (j = 0; j < state->handCount[i]; j++), it is set to never reach the handCount.
        That meant that the if statement was never true before I made the change. Now it is true under the right conditions,
        significantly improving my coverage.

    3) I reverted the bug I introduced in assignment 2 because I wanted to see correct coin counts.
        The line:
        if (state->hand[i][j] == gold){
        Is now:
        if (state->hand[i][j] == copper){
            
        Which was the original correct line of code.
        
        
ADVENTURER CARD
    Old coverage numbers:
    Function 'adventurerEffect'
    Lines executed:70.59% of 17
    Branches executed:66.67% of 12
    Taken at least once:50.00% of 12
    Calls executed:100.00% of 2

  ...
        8:  682:        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]=copper;
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

    The block that was never getting executed is the else statement starting at line 685. There were two reasons this was 
    never executed. The first reason is that my test code tended to have treasures at the end of the deck. So the player
    would draw the top card of the deck, and it would be a treasure. Lines 683 and 684 would be run and the else block
    would not. The player would draw another card and again, the else block was never executed. At this point the player
    would have two treasures and the execution would break out of the while loop.
    The second reason the else block was not getting executed was due to a bug I introduced in assignment 2. Line 682 has
    "=copper" at the end. This makes it so any drawn card will always be perceived as copper, which would cause the else
    block to get bypassed. I fixed the bug and modified my test code to ensure there was a non-treasure in between the last
    treasures in the deck. The result was a huge improvement in my code coverage.
    

The resulting coverage is:
    Function 'adventurerEffect'
    Lines executed:100.00% of 17
    Branches executed:100.00% of 12
    Taken at least once:100.00% of 12
    Calls executed:100.00% of 2
    
    Both my tests are correct in that they check the important values such as coin count, hand count, and deck count. Any inaccuracies
    in the values are caused by bugs in the dominion code. Some I fixed if they help coverage, but I left the bugs that didn't help
    raise the coverage percentage. 

    In this assignment we were not supposed to fix the bugs, so upon reverting my changes to dominion.c, the resulting coverage was:
    
    CUTPURSE CARD
    Lines executed:78.57% of 14
    Branches executed:83.33% of 12
    Taken at least once:75.00% of 12
    Calls executed:75.00% of 4
    
    ADVENTURER CARD
    Lines executed:70.59% of 17
    Branches executed:66.67% of 12
    Taken at least once:50.00% of 12
    Calls executed:100.00% of 2

    
    Note that although the coverage was not 100%, the changes to the cutpurse card's test code noted above did help increase 
    the coverage percentages. The adventurer card's test code changes had no affect on the coverage without the bug fixes. This
    was suprising because I introduced some randomization and increased the repetition by a lot. In the end, fixing the bugs 
    is what produces the greatest increase in coverage.
    
*/