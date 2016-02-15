RANDOM FUNCTION TEST ATTEMPS CAN BE CHANGED
IN THESE LOCATIONS(SET INITIALLY AT 1,000,000)

randomtestadventurer.c
LINE 75 
while(countNum < 500000){ //Stops testing after a certain number of attemtps


randomtestcard.c
LINE 75 
while(countNum < 500000){ //Stops testing after a certain number of attemtps






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
File 'dominion.c'
Lines executed:21.60% of 588
Branches executed:24.58% of 419
Taken at least once:17.42% of 419
Calls executed:10.89% of 101
dominion.c:creating 'dominion.c.gcov'












/******************************************
Random Tester Baron Card
*******************************************/

-Had current players selected randomly

-Amout of players randomly between 2-4

-Started off testing number of buys randomly

      //SETUP NUMBER OF BUYS COUNT------------------------------------------------
                numBuysRandom = floor(Random()*20);//set intial buys
                G.numBuys = numBuysRandom; //Used in assert 
                
-Number of buys working correctly

-Moved onto situation where player decides to get a estate card.
   1)Added randomly generated coin count and assert to make sure it didn't change.
      Assert added to test.
   
      //SETUP COINS------------------------------------------------
          coinRandom = floor(Random()*27);
          G.coins = coinRandom;
          
   2)Added randomly generated supply count for estate card. Assert added to test.
   
      //SETUP SUPPLY COUNT------------------------------------------------
          supplyRandomEstate = floor(Random()*100);
          G.supplyCount[estate] = supplyRandomEstate;
          
   -Ran test. Test failed on first try of "picking a estate card over discard & money".
   
      TEST START---------------------------------
      CARD: 1
      CHOICE: 0
      TEST NUM: 1 Deck: 80 Hand: 90 Discard: 58 Player 1
      GET ESTATE CARD---
      Coins = 0 ,expected 0
      Number of buys = 2,expected 2
      Estate Supply Count = 38 ,expected 39
      randomtestcard: randomtestcard.c:249: main: Assertion `G.supplyCount[estate] == supplyRandomEstate-1' failed.
      
      -Hand supply is updated correctly but the supply count for the estate card is never decreased.
      
   3)Added assert to check DISCARD supply count because it should be increased by one.
      
      -It doesn't always fail. It took 914 test before something went wrong. Test situations below.
      
      
      ***************   FAILED   *****************************
      TEST START---------------------------------
      CARD: 1
      CHOICE: 0
      TEST NUM: 914 Deck: 74 Hand: 15 Discard: 20 Player 4
      GET ESTATE CARD---
      Coins = 6 ,expected 6
      Number of buys = 12,expected 12
      Estate Supply Count = 0 ,expected -1
      TEST FAIL
      Hand Supply Count = 15 ,expected 15
      Discard Supply Count = 20 ,expected 21
      randomtestcard: randomtestcard.c:257: main: Assertion `G.discardCount[G.whoseTurn] == discardRandom+1' failed.
      
      
      ***************   WORKS   *****************************
      TEST START---------------------------------
      CARD: 1
      CHOICE: 0
      TEST NUM: 911 Deck: 41 Hand: 74 Discard: 80 Player 2
      GET ESTATE CARD---
      Coins = 15 ,expected 15
      Number of buys = 8,expected 8
      Estate Supply Count = 58 ,expected 59
      TEST FAIL
      Hand Supply Count = 74 ,expected 74
      Discard Supply Count = 81 ,expected 81
      
      
      ***************   WORKS   *****************************
      TEST START---------------------------------
      CARD: 1
      CHOICE: 0
      TEST NUM: 841 Deck: 55 Hand: 86 Discard: 68 Player 2
      GET ESTATE CARD---
      Coins = 9 ,expected 9
      Number of buys = 4,expected 4
      Estate Supply Count = 7 ,expected 8
      TEST FAIL
      Hand Supply Count = 86 ,expected 86
      Discard Supply Count = 69 ,expected 69
      

      
      
      
-Moved onto situation where player decides to get a estate card.

   1)Added asserts for coin, number of buys, estate supply count, hand supply count,&
      discard supply count. Found no bugs.

      
      
      
      

      
      
-At this point for statement and branch everything had been covered. Some of the branches
where only at 1%(shown below around line 991) so I decided to try a situation where player
decides to discard an estate card but doesn't have one in hand.

               169398:  991:	  else if (p > state->handCount[currentPlayer]){
         branch  0 taken 1% (fallthrough)
         branch  1 taken 99%
              2110:  992:	    if(DEBUG) {
                 -:  993:	      printf("No estate cards in your hand, invalid choice\n");
                 -:  994:	      printf("Must gain an estate if there are any\n");
                 -:  995:	    }
              2110:  996:	    if (supplyCount(estate, state) > 0){
         call    0 returned 100%
         branch  1 taken 99% (fallthrough)
         branch  2 taken 1%
              2087:  997:	      gainCard(estate, state, 0, currentPlayer);
              
              
          -Didn't increase the one 1% like I thought it would though.
              
              
                 169398:  991:	  else if (p > state->handCount[currentPlayer]){
         branch  0 taken 1% (fallthrough)
         branch  1 taken 99%
              2110:  992:	    if(DEBUG) {
                 -:  993:	      printf("No estate cards in your hand, invalid choice\n");
                 -:  994:	      printf("Must gain an estate if there are any\n");
                 -:  995:	    }
              2110:  996:	    if (supplyCount(estate, state) > 0){
         call    0 returned 100%
         branch  1 taken 99% (fallthrough)
         branch  2 taken 1%
              2087:  997:	      gainCard(estate, state, 0, currentPlayer);
              
              
              
      1)I had fails on coins sometimes. Player shouldn't recieve any coins if they
         didn't have an estate card to discard. 
         
         Estate supple count pile sometimes was incorrect. It shouldn't change in value.
         Nothing is being take from it.
         
         Hand supply count always incorrect. Should increase by one because if you can't
         discard an estate, then you would have to get one. 
            
            
            TEST START---------------------------------
            CARD: 0
            CHOICE: 1
            TEST NUM: 29999 Deck: 12 Hand: 24 Discard: 68 Player 2
            ESTATE CARD NOT FOUND---
            Coins = 11 ,expected 11
            Number of buys = 17,expected 17
            Estate Supply Count = 68 ,expected 70
            TEST FAIL
            Deck Supply Count = 12 ,expected 12
            Hand Supply Count = 24 ,expected 25
            TEST FAIL
            Discard Supply Count = 69 ,expected 69


            TEST START---------------------------------
            CARD: 0
            CHOICE: 1
            TEST NUM: 29854 Deck: 2 Hand: 86 Discard: 41 Player 1
            ESTATE CARD NOT FOUND---
            Coins = 19 ,expected 15
            TEST FAIL
            Number of buys = 6,expected 6
            Estate Supply Count = 23 ,expected 23
            Deck Supply Count = 2 ,expected 2
            Hand Supply Count = 85 ,expected 87
            TEST FAIL
            Discard Supply Count = 42 ,expected 42

            
            
            
            
-Coverage-------------------
   Statement and branch coverage 100%.
//////////////////////////////
//dominion.c.gcov
/*///////////////////////////////////////////////////////////////////////////////////////////////
        -:  974:    case baron:
    30000:  975:      state->numBuys++;//Increase buys by 1!
    30000:  976:      if (choice1 > 0){//Boolean true or going to discard an estate
branch  0 taken 50% (fallthrough)
branch  1 taken 50%
    15097:  977:	int p = 0;//Iterator for hand!
    15097:  978:	int card_not_discarded = 1;//Flag for discard set!
   212579:  979:	while(card_not_discarded){
branch  0 taken 92%
branch  1 taken 8%
   182385:  980:	  if (state->hand[currentPlayer][p] == estate){//Found an estate card!
branch  0 taken 7% (fallthrough)
branch  1 taken 93%
    12987:  981:	    state->coins += 4;//Add 4 coins to the amount of coins
    12987:  982:	    state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
    12987:  983:	    state->discardCount[currentPlayer]++;
   595819:  984:	    for (;p < state->handCount[currentPlayer]; p++){
branch  0 taken 98%
branch  1 taken 2% (fallthrough)
   582832:  985:	      state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
        -:  986:	    }
    12987:  987:	    state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
    12987:  988:	    state->handCount[currentPlayer]--;
    12987:  989:	    card_not_discarded = 0;//Exit the loop
        -:  990:	  }
   169398:  991:	  else if (p > state->handCount[currentPlayer]){
branch  0 taken 1% (fallthrough)
branch  1 taken 99%
     2110:  992:	    if(DEBUG) {
        -:  993:	      printf("No estate cards in your hand, invalid choice\n");
        -:  994:	      printf("Must gain an estate if there are any\n");
        -:  995:	    }
     2110:  996:	    if (supplyCount(estate, state) > 0){
call    0 returned 100%
branch  1 taken 99% (fallthrough)
branch  2 taken 1%
     2087:  997:	      gainCard(estate, state, 0, currentPlayer);
call    0 returned 100%
     2087:  998:	      state->supplyCount[estate]--;//Decrement estates
     2087:  999:	      if (supplyCount(estate, state) == 0){
call    0 returned 100%
branch  1 taken 1% (fallthrough)
branch  2 taken 99%
       16: 1000:		isGameOver(state);
call    0 returned 100%
        -: 1001:	      }
        -: 1002:	    }
     2110: 1003:	    card_not_discarded = 0;//Exit the loop
        -: 1004:	  }
        -: 1005:			    
        -: 1006:	  else{
   167288: 1007:	    p++;//Next card
        -: 1008:	  }
        -: 1009:	}
        -: 1010:      }
        -: 1011:			    
        -: 1012:      else{
    14903: 1013:	if (supplyCount(estate, state) > 0){
call    0 returned 100%
branch  1 taken 99% (fallthrough)
branch  2 taken 1%
    14770: 1014:	  gainCard(estate, state, 0, currentPlayer);//Gain an estate
call    0 returned 100%
    14770: 1015:	  state->supplyCount[estate]--;//Decrement Estates
    14770: 1016:	  if (supplyCount(estate, state) == 0){
call    0 returned 100%
branch  1 taken 1% (fallthrough)
branch  2 taken 99%
      152: 1017:	    isGameOver(state);
call    0 returned 100%
        -: 1018:	  }
        -: 1019:	}
        -: 1020:      }
        -: 1021:	    
        -: 1022:      
    30000: 1023:      return 0;
*////////////////////////////////////////////////////////////////////////
File 'dominion.c'
Lines executed:26.36% of 588
Branches executed:29.36% of 419
Taken at least once:21.24% of 419
Calls executed:16.83% of 101
dominion.c:creating 'dominion.c.gcov'

