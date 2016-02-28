/********************************************************************
Assignment 5 - Part 2
Author: Lynn Herrick
Date: 2/26/16
Description: Fix all the bugs that are found in your code. First 
fix the bugs that your teammate found then fix the bugs that you 
introduced. Use GDB to debug your code and fix it. Provide a 
documentation file to discuss which bugs you fix and mention your 
code changes. Provide a documentation file BugFixes.c. In case your 
teamates already fixed the bugs and you cannot find out any bugs, 
find out the version they just submitted for assignment 2 and use 
that version. It will give you better practice with git repository 
and repository history.    
********************************************************************

Below is bug documentation and fixed code in dominion.c.  I have the
the title of where the bug is listed for each section.  Within each
section I have both teammate's reports of a bug along with the code
containing the bug.  Then I have my conlusion after running gdb and/or
other testing methods along with the corrected code.  For further
information, please also note teammate1Dominion and teammate2Dominion
folders for groupmates imhoffr and mcleodki.

***Village
*imhoffr's report: The handcount is always one more than expected.

   //discard played card from hand
  discardCard(handPos, nextPlayer, state, 0);

-----------------------------Fixed Code Below-----------------------------------------

  //discard played card from hand
  discardCard(handPos, currentPlayer, state, 0);

Conclusion: the handcount was always one more than expected because the current
player was not discarding a card as the rules expect they should.  I have made
the adjustments for the proper discard.



***Adventurer
*mckleodki's report (bug 2): User does not receive two treasure cards when playing 
the adventurer card, even though there are two treasure cards available.

    //if card is treassure
    if (cardDrawn == copper && cardDrawn == silver && cardDrawn == gold){
      drawntreasure++;
    }

 -----------------------------Fixed Code Below-----------------------------------------
    
    //if card is treassure
    if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
      drawntreasure++;
    }

Conclusion: The currentPlayer was not getting the correct amount of treasure due
to improper conditions that were impossible to be met by drawing two treasure cards, 
without the random chance that a third treasure card was already in their hand.


*imhoffr's report: 
This catches a bug where z is not checked against MAX_HAND, which is 
500 (here when it crashes z is up to 7436!)  

  while(z-1>=0){
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }

 -----------------------------Fixed Code Below-----------------------------------------
  
  while(z-1>=0 && z <= MAX_HAND){  //does not allow more than MAX_HAND
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }

Conclusion: I have added a check on z to make sure that no improper deck amount can
get through and cause an error.



***Smithy
*mckleodki's report: Smithy card does not discard card correctly.

  //discard card from hand
  discardCard(handPos,currentPlayer,state,1); 

 -----------------------------Fixed Code Below-----------------------------------------
  //discard card from hand
  discardCard(handPos,currentPlayer,state,0); 

Conclusion: the card was not going into the played pile due to an improper flag being
set within the discard card parameters.  This kept the card in the player's hand after
running the function for that card.



***Cutpurse
Bug: Player was revealing hand when they weren't required to.

		//if has copper, discard it
        if(state->hand[i][j] == copper){
          discardCard(j, i, state, 0);
        }
-----------------------------Fixed Code Below-----------------------------------------

 		//if has copper, discard it
        if(state->hand[i][j] == copper){
          discardCard(j, i, state, 0);
          break;
        }

Conclusion: code was not exiting the for loop if it found a copper.  Added a break to
exit the loop and therefore not show hand.



***Council Room
Bug: Other player's hand is off by -1.  Current player's hand is off by +1.

  //Each other player draws a card
  for (i = 0; i < state->numPlayers; i++){
    if ( i == currentPlayer ){	
      drawCard(i, state);
    }
  }   

-----------------------------Fixed Code Below-----------------------------------------

  //Each other player draws a card
  for (i = 0; i < state->numPlayers; i++){
    if ( i != currentPlayer ){	
      drawCard(i, state);
    }
  } 

Conclusion: Current player was drawing a card instead of other player(s).  Changed the
condition to "if not" current player.



***Other:
While I am not sure if we are allowed to touch playdom.c,
I noticed this bug within the file and would like to make 
note of what the bug is and how to fix it if I can edit
this file in the future.  Below are lines 85-88 of playdom.c:

    else {
      if (adventurerPos != -1) {
        printf("1: adventurer played from position %d\n", adventurerPos);
        playCard(adventurerPos, -1, -1, -1, &G);

On the last line (88 in playdom.c), the adventurer card is not 
getting passed as the first parameter to playCard.  Instead, the int
position of adventurer is getting passed.  This will cause playdom.c
to segfault.  Here is what the correct code should look like:

    else {
      if (adventurerPos != -1) {
        printf("1: adventurer played from position %d\n", adventurerPos);
        playCard(adventurer, -1, -1, -1, &G);
