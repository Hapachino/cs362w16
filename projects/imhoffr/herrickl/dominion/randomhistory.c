/**************************************************************************
* CS 362-400 Assignment 4 
* By:  Lynn Herrick
* Date: 2/9/16
* Description: Write up and check in the development of your random 
*     testers, including improvements in coverage and effort to check 
*     the correctness of your specification, as randomhistory.c. Be 
*     detailed and thorough!
***************************************************************************
This is a txt file

1. randomtestadventurer.c
This random tester correctly executes 2000 random tests, all of which 
provide information towards what the bug that was written into the code is.
Randomized items include: current player, deck count, location of teasure cards
in current player's deck, which type of treasure cards are randomized into the deck, 
discard pile, and hand count.  This randomization can be seen in lines 44-63
of randomtestadventurer.c.  For each random test, I utilize the ideas implemented
in my unit test for the adventurer card to check whether or not any potential 
element related to the gamestate has changed in a way it should or shouldn't have.
These tests include: player1's hand count, player2's hand count, player1's deck
count, player2's deck count, player1's discard pile, player2's discard pile, the
number of players in the game, the number of outposts played, whose turn it is,
what phase it is, number of actions, number of coins, number of buys, and drawn 
treasure.

I also untilize a sigal handler to handle instances of a potntential bug that 
causes cardEffect to cause a segmentation fault.  If the signal handler is utilized
tests are still printed with their randomized items, but the call to cardEffect() is
not taken and instead the two test states are compared without it (causing all 
changes related to adventurer card fail in test).  A special print statement, letting
the reader know that that paticular test did not execute cardEffect() is also included
in the tests to better determine where there are specific issues with bugs.

As for code coverage, this is a bit tricky with the particular bug that I wrote for adventurer.
My bug occurs at:
 743:    if (cardDrawn == copper && cardDrawn == silver && cardDrawn == gold){
This line will never be true and that causes the entire function to execute poorly.  Since
treasure is not incremented, many other conditions can never be entered unless I tamper with the 
dominion code.  This would undermine the purpose of finding and identifying the bug.  Currently,
my tests point to this error as well as run all of the code that is possible to run without 
tampering with dominion.c (potentially changing the drawntreasure).  This can be seen below.

dominion.c gcov of c_adventurer:
     1:  733:int c_adventurer(int drawntreasure, struct gameState *state, int currentPlayer, int cardDrawn, int temphand[], int z, int handPos){
        -:  734:  //draw until two treasure card draws
    21834:  735:  while(drawntreasure<2){
        -:  736:    //if deck is empty
    21833:  737:    if (state->deckCount[currentPlayer] <1){//we need to shuffle discard and add to deck
    21828:  738:      shuffle(currentPlayer, state);
        -:  739:    }
    21833:  740:    drawCard(currentPlayer, state);
    21832:  741:    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
        -:  742:    //if card is treassure
    21832:  743:    if (cardDrawn == copper && cardDrawn == silver && cardDrawn == gold){
    #####:  744:      drawntreasure++;
        -:  745:    }
        -:  746:    //if card is not treassure
        -:  747:    else{
    21832:  748:      temphand[z]=cardDrawn;
    21832:  749:      state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
    21832:  750:      z++;
        -:  751:    }
        -:  752:  }
        -:  753:  //discard all drawn cards
    #####:  754:  while(z-1>=0){
    #####:  755:    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    #####:  756:    z=z-1;
        -:  757:  }
    #####:  758:  return 0;        
        -:  759:}

To get full results utilize "make randomtestadventurer.out"


2. randomtestcard.c  (village card)
For my choice card, I selected the village card.  
This random tester correctly executes 2000 random tests, all of which 
provide information towards what the bug that was written into the code is.
Randomized items include: current player, deck count, discard pile, 
and hand count.  This randomization can be seen in lines 41-47 of 
randomtestcard.c.  For each random test, I utilize the ideas implemented
in my unit test for the village card to check whether or not any potential 
element related to the gamestate has changed in a way it should or shouldn't have.
These tests include: player1's hand count, player2's hand count, player1's deck
count, player2's deck count, player1's discard pile, player2's discard pile, the
number of players in the game, the number of outposts played, whose turn it is,
what phase it is, number of actions, number of coins, number of buys, and drawn 
treasure.

I also untilize a sigal handler to handle instances of a potntential bug that 
causes cardEffect to cause a segmentation fault.  If the signal handler is utilized
tests are still printed with their randomized items, but the call to cardEffect() is
not taken and instead the two test states are compared without it (causing all 
changes related to adventurer card fail in test).  A special print statement, letting
the reader know that that paticular test did not execute cardEffect() is also included
in the tests to better determine where there are specific issues with bugs.  

For code coverage, I have achieved 100% of code coverage on this card.  This can
be seen with the example below or appended to the end of the randomtestcard.out file.

dominion.c gcov of c_village:
14:  674:int c_village(int currentPlayer, struct gameState *state, int handPos, int nextPlayer){
        -:  675:  //+1 Card
       14:  676:  drawCard(currentPlayer, state);
        -:  677:  //+2 Actions
       14:  678:  state->numActions = state->numActions + 2;
        -:  679:  //discard played card from hand
       14:  680:  discardCard(handPos, nextPlayer, state, 0);
        -:  681:
       14:  682:  return 0;

To get full results utilize "make randomtestcard.out"