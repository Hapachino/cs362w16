/******************************************
Random Tester Adventurer Card
*******************************************/

-Had current players selected randomly

-Amout of players randomly between 2-4

-Deck was initially fill with a random amount of cards
but caused segementation faults. I had change it to
MAX_DECK to procced with checking. I call this a bug.

-Hand and discard piles have random card amounts & cards
within those decks.

-I initally started out with testing supply count & found no
problems.

-I then tried to check deck but then the problem of
seg fault that I mention above started happening.

-Line 657 wasn't being called
656: if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
 657:               shuffle(currentPlayer, state);

-So I setup situation where deckCount could equal 0 but it caused
segmentation faults. Shuffle not working when 
state->deckCount[currentPlayer] == zero. Had to stop
making deck count zero so I could proceed with testing.

-Setup tester for handcount, always wrong. Player
never gets back two cards, always more.

-Added oracle to count how many cards should be added to
the discard pile after adventurer is finished. Found out that
discard being correct isn't consistent. Mostly incorrect, rarely
right.Example below:



      TEST START---------------------------------
      TEST NUM: 99998 Deck: 500 Hand: 49 Discard: 36 Player: 3 DiscardCount: 25
      ADVENTURER CARD---
      Hand Supply Count = 77 ,expected 51
      TEST FAIL
      Discard Supply Count = 62,expected 62
      Coins = 16 ,expected 16
      Number of buys = 10,expected 10

      TEST START---------------------------------
      TEST NUM: 99999 Deck: 500 Hand: 67 Discard: 85 Player: 2 DiscardCount: 10
      ADVENTURER CARD---
      Hand Supply Count = 80 ,expected 69
      TEST FAIL
      Discard Supply Count = 96,expected 96
      Coins = 0 ,expected 0
      Number of buys = 16,expected 16
      

-BUGS-----------------------------
1)If deck count is below 500, segmentation fault occurs.
2)Amount of cards added to hand is incorrect.
3)Empty deck causes sementation fault
4)Discard pile not updated correctly all the time.



-Coverage-------------------
   Coverage was good. I couldn't get 100% because deckCount < 1 would cause
   a program to hault so I had to stop doing that.
//////////////////////////////
//dominion.c.gcov
/*///////////////////////////////////////////////////////////////////////////////////////////////
function adventurerCardFunc called 100000 returned 100% blocks executed 93%
   100000:  647:int adventurerCardFunc(struct gameState *state)
        -:  648:{
   100000:  649:         int z = 0;// this is the counter for the temp hand
   100000:  650:         int drawntreasure=0;
   100000:  651:         int currentPlayer = whoseTurn(state);
call    0 returned 100%
        -:  652:         int cardDrawn;
        -:  653:         int temphand[MAX_HAND];// moved above the if statement
        -:  654:         
  1995670:  655:         while(drawntreasure<2){
branch  0 taken 95%
branch  1 taken 5% (fallthrough)
  1795670:  656:            if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  657:               shuffle(currentPlayer, state);
call    0 never executed
        -:  658:            }
  1795670:  659:            drawCard(currentPlayer, state);
call    0 returned 100%
  1795670:  660:            cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-2];//top card of hand is most recently drawn card.
  1995670:  661:            if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 96% (fallthrough)
branch  3 taken 4%
branch  4 taken 4% (fallthrough)
branch  5 taken 96%
   200000:  662:               drawntreasure++;
        -:  663:            else{
  1595670:  664:                temphand[z]=cardDrawn;
  1595670:  665:                state->handCount[currentPlayer]; //this should just remove the top card (the most recently drawn one).
  1595670:  666:                z++;
        -:  667:            }
        -:  668:         }
  1795670:  669:         while(z-1>=0){
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
  1595670:  670:            state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
  1595670:  671:            z=z-1;
        -:  672:         }
   100000:  673:         return 0;
*////////////////////////////////////////////////////////////////////////