/*
Jack Holkeboer
OSU cs362
holkeboj@onid.oregonstate.edu

*******************
Overall coverage:
*******************
File 'dominion.c'
Lines executed:32.16% of 656
Branches executed:35.70% of 423
Taken at least once:27.42% of 423
****
I wouldn't expect that testing four functions and four cards
would get us anywhere close to 100% coverage.  Still,
32% will be a baseline going forward.  I noticed that even after
running only Unit Test 1, my line coverate was at 18%.
This is probably due to the invoking of initializeGame()
and other helper functions.  


*******************
Unit Test 1: isGameOver()
*******************
Function 'isGameOver'
Lines executed:100.00% of 12
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
****
For isGameOver() I was able to achieve 100% branch
and statement coverage.  However the test could be improved
by adding coverage for more boundary conditions (i.e.
testing every possible permutation of supply pile counts).

*******************
Unit Test 2: updateCoins()
*******************
Function 'updateCoins'
Lines executed:100.00% of 14
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
****
This function is covered 100% by testing every possible permutation
of player and bonus value on six test hands specifically designed
to activate every branch.


*******************
Unit Test 3: discardCard()
*******************
Function 'discardCard'
Lines executed:86.67% of 15
Branches executed:100.00% of 6
Taken at least once:83.33% of 6
****


*******************
Unit Test 4: getCost()
*******************
Function 'getCost'
Lines executed:96.67% of 30
Branches executed:100.00% of 28
Taken at least once:96.43% of 28
****
It was easy to achieve 100% coverage for this function
simply by testing every possible case switch value.

*******************
Card Test 1: Smithy
*******************
Function 'smithy_card'
Lines executed:100.00% of 7
Branches executed:100.00% of 4
Taken at least once:100.00% of 4
****
This card is 100% covered.  This is achieved
by checking every possible player and hand position.
Hand position was important because it caught my bug.

*******************
Card Test 2: Adventurer
*******************
Function 'adventurer_card'
Lines executed:52.38% of 21
Branches executed:71.43% of 14
Taken at least once:35.71% of 14
****


*******************
Card Test 3: Council Room
*******************
        -:  772:    case council_room:
        -:  773:      //+4 Cards
       40:  774:      for (i = 0; i < 4; i++)
branch  0 taken 80%
branch  1 taken 20%
        -:  775:	{
       16:  776:	  drawCard(currentPlayer, state);
       16:  777:	}
        -:  778:			
        -:  779:      //+1 Buy
        4:  780:      state->numBuys++;
        -:  781:			
        -:  782:      //Each other player draws a card
       24:  783:      for (i = 0; i < state->numPlayers; i++)
branch  0 taken 67%
branch  1 taken 33%
        -:  784:	{
        8:  785:	  if ( i != currentPlayer )
branch  0 taken 50%
branch  1 taken 50%
        -:  786:	    {
        4:  787:	      drawCard(i, state);
        4:  788:	    }
        8:  789:	}
        -:  790:			
        -:  791:      //put played card in played card pile
        4:  792:      discardCard(handPos, currentPlayer, state, 0);
        -:  793:			
        4:  794:      return 0;
****
Since council_room and great_hall are contained within a switch statement,
I instead show the raw gcov output.
For council room I have 100% branch and statement coverage.
We can see each statement was executed at least 4 times.

*******************
Card Test 1: Great Hall
*******************
        -:  948:    case great_hall:
        -:  949:      //+1 Card
        4:  950:      drawCard(currentPlayer, state);
        -:  951:			
        -:  952:      //+1 Actions
        4:  953:      state->numActions++;
        -:  954:			
        -:  955:      //discard card from hand
        4:  956:      discardCard(handPos, currentPlayer, state, 0);
        4:  957:      return 0;
****
For Great Hall I have 100% statement coverage.
There are no branches so branch coverage is not relevant here.




*/


/* FULL OUTPUT OF `gcov dominion.c -f -b`

*/