Aggregated Coverage.
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
----------------------------------------

File 'dominion.c'
Lines executed:41.84% of 588
Branches executed:46.54% of 419
Taken at least once:40.10% of 419
Calls executed:30.69% of 101
dominion.c:creating 'dominion.c.gcov'











Testing fullDeckCount()
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
----------------------------------------
*Basic requirements of fullDeckCount()
   1)Count how many of one card are in all of
      the decks.

-Statement Coverage     
   Good statement coverage,each line was executed.
-Branch Coverage
   Each branch was taken atleast once.
   
   

/*******************************************
dominion.c.gcov
/*******************************************
function fullDeckCount called 14484 returned 100% blocks executed 100%
    14484:  324:int fullDeckCount(int player, int card, struct gameState *state) {
        -:  325:  int i;
    14484:  326:  int count = 0;
        -:  327:
    51324:  328:  for (i = 0; i < state->deckCount[player]; i++)
branch  0 taken 72%
branch  1 taken 28% (fallthrough)
        -:  329:    {
    36840:  330:      if (state->deck[player][i] == card) count++;
branch  0 taken 79% (fallthrough)
branch  1 taken 21%
        -:  331:    }
        -:  332:
    51954:  333:  for (i = 0; i < state->handCount[player]; i++)
branch  0 taken 72%
branch  1 taken 28% (fallthrough)
        -:  334:    {
    37470:  335:      if (state->hand[player][i] == card) count++;
branch  0 taken 78% (fallthrough)
branch  1 taken 22%
        -:  336:    }
        -:  337:
    52584:  338:  for (i = 0; i < state->discardCount[player]; i++)
branch  0 taken 72%
branch  1 taken 28% (fallthrough)
        -:  339:    {
    38100:  340:      if (state->discard[player][i] == card) count++;
branch  0 taken 77% (fallthrough)
branch  1 taken 23%
        -:  341:    }
        -:  342:
    14484:  343:  return count;
        -:  344:}
************************************************/















Testing scoreFor()
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
----------------------------------------
*Basic requirements of fullDeckCount()
   1)Return score for player by counting cards with values
     across all card piles.
   2)Only cards in deck pile return correct score.
   3)Only cards in hand return correct score.
   4)Only cards in discard pile return correct score.

-Statement Coverage     
   Good statement coverage,each line was executed.
-Branch Coverage
   Each branch was taken atleast once.

/*******************************************
dominion.c.gcov
/*******************************************
function scoreFor called 2592 returned 100% blocks executed 100%
     2592:  417:int scoreFor (int player, struct gameState *state) {
        -:  418:
        -:  419:  int i;
     2592:  420:  int score = 0;
        -:  421:  //score from hand
     9072:  422:  for (i = 0; i < state->handCount[player]; i++)
branch  0 taken 71%
branch  1 taken 29% (fallthrough)
        -:  423:    {
     6480:  424:      if (state->hand[player][i] == curse) { score = score - 1; };
branch  0 taken 17% (fallthrough)
branch  1 taken 83%
     6480:  425:      if (state->hand[player][i] == estate) { score = score + 1; };
branch  0 taken 17% (fallthrough)
branch  1 taken 83%
     6480:  426:      if (state->hand[player][i] == duchy) { score = score + 3; };
branch  0 taken 17% (fallthrough)
branch  1 taken 83%
     6480:  427:      if (state->hand[player][i] == province) { score = score + 6; };
branch  0 taken 17% (fallthrough)
branch  1 taken 83%
     6480:  428:      if (state->hand[player][i] == great_hall) { score = score + 1; };
branch  0 taken 17% (fallthrough)
branch  1 taken 83%
     6480:  429:      if (state->hand[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
branch  0 taken 17% (fallthrough)
branch  1 taken 83%
call    2 returned 100%
        -:  430:    }
        -:  431:
        -:  432:  //score from discard
     9072:  433:  for (i = 0; i < state->discardCount[player]; i++)
branch  0 taken 71%
branch  1 taken 29% (fallthrough)
        -:  434:    {
     6480:  435:      if (state->discard[player][i] == curse) { score = score - 1; };
branch  0 taken 17% (fallthrough)
branch  1 taken 83%
     6480:  436:      if (state->discard[player][i] == estate) { score = score + 1; };
branch  0 taken 17% (fallthrough)
branch  1 taken 83%
     6480:  437:      if (state->discard[player][i] == duchy) { score = score + 3; };
branch  0 taken 17% (fallthrough)
branch  1 taken 83%
     6480:  438:      if (state->discard[player][i] == province) { score = score + 6; };
branch  0 taken 17% (fallthrough)
branch  1 taken 83%
     6480:  439:      if (state->discard[player][i] == great_hall) { score = score + 1; };
branch  0 taken 17% (fallthrough)
branch  1 taken 83%
     6480:  440:      if (state->discard[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
branch  0 taken 17% (fallthrough)
branch  1 taken 83%
call    2 returned 100%
        -:  441:    }
        -:  442:
        -:  443:  //score from deck
     9072:  444:  for (i = 0; i < state->discardCount[player]; i++)
branch  0 taken 71%
branch  1 taken 29% (fallthrough)
        -:  445:    {
     6480:  446:      if (state->deck[player][i] == curse) { score = score - 1; };
branch  0 taken 10% (fallthrough)
branch  1 taken 90%
     6480:  447:      if (state->deck[player][i] == estate) { score = score + 1; };
branch  0 taken 22% (fallthrough)
branch  1 taken 78%
     6480:  448:      if (state->deck[player][i] == duchy) { score = score + 3; };
branch  0 taken 10% (fallthrough)
branch  1 taken 90%
     6480:  449:      if (state->deck[player][i] == province) { score = score + 6; };
branch  0 taken 10% (fallthrough)
branch  1 taken 90%
     6480:  450:      if (state->deck[player][i] == great_hall) { score = score + 1; };
branch  0 taken 10% (fallthrough)
branch  1 taken 90%
     6480:  451:      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
branch  0 taken 10% (fallthrough)
branch  1 taken 90%
call    2 returned 100%
        -:  452:    }
        -:  453:
     2592:  454:  return score;
        -:  455:}
************************************************/















Testing gainCard()
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
----------------------------------------
*Basic requirements of gainCard()
   1)Fail if card is not in supplyCount()
   2)Add card to players deck - check if deck has been updated.
   3)Add card to players hand - check if hand has been updated.
   4)Add card to players discard - check if discard has been updated.
   5)Was supplyCount decressed in size.


-Statement Coverage     
   Good statement coverage,each line was executed.
-Branch Coverage
   Each branch was taken atleast once.   
   
/*******************************************
dominion.c.gcov
/*******************************************
function gainCard called 5 returned 100% blocks executed 100%
        5: 1337:int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
        -: 1338:{
        -: 1339:  //Note: supplyPos is enum of choosen card
        -: 1340:	
        -: 1341:  //check if supply pile is empty (0) or card is not used in game (-1)
        5: 1342:  if ( supplyCount(supplyPos, state) < 1 )
call    0 returned 100%
branch  1 taken 20% (fallthrough)
branch  2 taken 80%
        -: 1343:    {
        1: 1344:      return -1;
        -: 1345:    }
        -: 1346:	
        -: 1347:  //added card for [whoseTurn] current player:
        -: 1348:  // toFlag = 0 : add to discard
        -: 1349:  // toFlag = 1 : add to deck
        -: 1350:  // toFlag = 2 : add to hand
        -: 1351:
        4: 1352:  if (toFlag == 1)
branch  0 taken 25% (fallthrough)
branch  1 taken 75%
        -: 1353:    {
        1: 1354:      state->deck[ player ][ state->deckCount[player] ] = supplyPos;
        1: 1355:      state->deckCount[player]++;
        -: 1356:    }
        3: 1357:  else if (toFlag == 2)
branch  0 taken 67% (fallthrough)
branch  1 taken 33%
        -: 1358:    {
        2: 1359:      state->hand[ player ][ state->handCount[player] ] = supplyPos;
        2: 1360:      state->handCount[player]++;
        -: 1361:    }
        -: 1362:  else
        -: 1363:    {
        1: 1364:      state->discard[player][ state->discardCount[player] ] = supplyPos;
        1: 1365:      state->discardCount[player]++;
        -: 1366:    }
        -: 1367:	
        -: 1368:  //decrease number in supply pile
        4: 1369:  state->supplyCount[supplyPos]--;
        -: 1370:	 
        4: 1371:  return 0;
        -: 1372:}
   ************************************************/
 










 
   
Testing isGameOver()
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
----------------------------------------   
 *Basic requirements of isGameOver()
   1)Does game end when provience cards are empty?
   2)Game shouldn't end with a provience card.
   3)Does game end when only 2 or less supply piles are empty?
   4)Does game end when a certain type of card 
      is included when the 3 piles are gone?

      
-Statement Coverage     
   Good statement coverage,each line was executed.
-Branch Coverage
   Each branch was taken atleast once.   

   
/*******************************************
dominion.c.gcov
/*******************************************
function isGameOver called 15604 returned 100% blocks executed 100%
    15604:  390:int isGameOver(struct gameState *state) {
        -:  391:  int i;
        -:  392:  int j;
        -:  393:	
        -:  394:  //if stack of Province cards is empty, the game ends
    15604:  395:  if (state->supplyCount[province] == 0)
branch  0 taken 1% (fallthrough)
branch  1 taken 99%
        -:  396:    {
        1:  397:      return 1;
        -:  398:    }
        -:  399:
        -:  400:  //if three supply pile are at 0, the game ends
    15603:  401:  j = 0;
   405678:  402:  for (i = 0; i < 25; i++)
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
        -:  403:    {
   390075:  404:      if (state->supplyCount[i] == 0)
branch  0 taken 11% (fallthrough)
branch  1 taken 89%
        -:  405:	{
    43203:  406:	  j++;
        -:  407:	}
        -:  408:    }
    15603:  409:  if ( j >= 3)
branch  0 taken 78% (fallthrough)
branch  1 taken 22%
        -:  410:    {
    12144:  411:      return 1;
        -:  412:    }
        -:  413:
     3459:  414:  return 0;
        -:  415:}
/*******************************************/

















Testing adventurer card
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
----------------------------------------
*Basic requirements of adventurer card
   1)Player should recieve 2 treasure cards in their hand.
   2)Adventurer card should work with all treasure coins.
   3)If deck is empty adventurer should single that cards
      should be shuffled from discard deck and be used.
   4)Other players shouldn't have any changes to their cards.

-Statement Coverage     
   Good statement coverage,each line was executed.
-Branch Coverage
   Each branch was taken atleast once.   
  
/*******************************************
dominion.c.gcov
/*******************************************   
function adventurerCardFunc called 7 returned 100% blocks executed 100%
        7:  647:int adventurerCardFunc(struct gameState *state)
        -:  648:{
        7:  649:         int z = 0;// this is the counter for the temp hand
        7:  650:         int drawntreasure=0;
        7:  651:         int currentPlayer = whoseTurn(state);
call    0 returned 100%
        -:  652:         int cardDrawn;
        -:  653:         int temphand[MAX_HAND];// moved above the if statement
        -:  654:         
       38:  655:         while(drawntreasure<2){
branch  0 taken 77%
branch  1 taken 23% (fallthrough)
       24:  656:            if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
branch  0 taken 4% (fallthrough)
branch  1 taken 96%
        1:  657:               shuffle(currentPlayer, state);
call    0 returned 100%
        -:  658:            }
       24:  659:            drawCard(currentPlayer, state);
call    0 returned 100%
       24:  660:            cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-2];//top card of hand is most recently drawn card.
       38:  661:            if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
branch  0 taken 58% (fallthrough)
branch  1 taken 42%
branch  2 taken 86% (fallthrough)
branch  3 taken 14%
branch  4 taken 17% (fallthrough)
branch  5 taken 83%
       14:  662:               drawntreasure++;
        -:  663:            else{
       10:  664:                temphand[z]=cardDrawn;
       10:  665:                state->handCount[currentPlayer]; //this should just remove the top card (the most recently drawn one).
       10:  666:                z++;
        -:  667:            }
        -:  668:         }
       24:  669:         while(z-1>=0){
branch  0 taken 59%
branch  1 taken 41% (fallthrough)
       10:  670:            state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
       10:  671:            z=z-1;
        -:  672:         }
        7:  673:         return 0;
        -:  674:}
 /*******************************************/
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
Testing smithy card
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
----------------------------------------
*Basic requirements of smithy card
   1)Increase current players hand by 3 cards
   2)Other players shouldn't have any changes to their cards.
   3)Smithy card removed from current players hand after being used.
   4)Supply count of all cards not effected.

-Statement Coverage     
   Good statement coverage,each line was executed.
-Branch Coverage
   Each branch was taken atleast once.   

   
/*******************************************
dominion.c.gcov
/*******************************************    
function smithyCardFunc called 6 returned 100% blocks executed 100%
        6:  676:int smithyCardFunc(struct gameState *state, int handPos)
        -:  677:{
        -:  678: int i;
        6:  679: int currentPlayer = whoseTurn(state);
call    0 returned 100%
       24:  680: for (i = 0; i < 3; i++)
branch  0 taken 75%
branch  1 taken 25% (fallthrough)
        -:  681:	{
       18:  682:	  drawCard(currentPlayer, state);
call    0 returned 100%
        -:  683:	}
        6:  684:		drawCard(currentPlayer, state);
call    0 returned 100%
        -:  685:      //discard card from hand
        6:  686:      discardCard(handPos, currentPlayer, state, 0);
call    0 returned 100%
        6:  687:      return 0;
        -:  688:		
        -:  689:}
 /*******************************************/
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
Testing village card
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
----------------------------------------
*Basic requirements of smithy card
   1)Increase current players hand by 1 card
   2)Actions increased by 2
   3)Increase current players hand +1 card and +2 actions with different player sizes.
   4)Play village card when players deck is empty.

-Statement Coverage     
   Good statement coverage,each line was executed.
-Branch Coverage
   Each branch was taken atleast once. 
   
/*******************************************
dominion.c.gcov
/******************************************* 
function villageCardFunc called 8 returned 100% blocks executed 100%
        8:  691:int villageCardFunc(struct gameState *state, int handPos)
        -:  692:{
        8:  693:   int currentPlayer = whoseTurn(state);
call    0 returned 100%
        -:  694: 
        -:  695:   //+1 Card
        8:  696:   drawCard(currentPlayer, state);
call    0 returned 100%
        -:  697:      
        -:  698:   //+2 Actions
        8:  699:   state->numActions = state->numActions + state->numPlayers;
        -:  700:      
        -:  701:   //discard played card from hand
        8:  702:   discardCard(handPos, currentPlayer, state, 0);
call    0 returned 100%
        8:  703:   return 0;
        -:  704:		
        -:  705:}
 /*******************************************/
 





 
 
 
 
 
 
 


 
 
Testing cutpurse card
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
----------------------------------------
*Basic requirements of cutpurse card
   1)Current player +2 treasure 
   2)Each other player discards a Copper card
   3)If other players don't have a copper, hands should remain the same.
   4)Card supply is unaffected when played.
   
   
-Statement Coverage    
      I was never able to figure out a situation when j
      would be equal to a players hand count. Something would
      have to be seriously wrong with the function.
      
         if (j == state->handCount[i])
      
      Therefore the line below could never run.
   
         #####:  731:		      for (k = 0; k < state->handCount[i]; k++)
         
      Other then those lines and the DEBUG code, coverage was complete.
      
   Good statement coverage,each line was executed.
-Branch Coverage
   Same problem as the statement coverage. On the the IF:"if (j == state->handCount[i])"
   I couldn't get it to be true so only one of it's branches was ran. All other
   branches in the function did run.

  
/*******************************************
dominion.c.gcov
/******************************************* 
function cutpurseCardFunc called 30 returned 100% blocks executed 76%
       30:  708:int cutpurseCardFunc(struct gameState *state, int handPos)
        -:  709:{
        -:  710:   int i;
        -:  711:   int j;
        -:  712:   int k;
       30:  713:   int currentPlayer = whoseTurn(state);
call    0 returned 100%
        -:  714:   
        -:  715:   
        -:  716:   
       30:  717:   updateCoins(currentPlayer, state, 2);
call    0 returned 100%
      126:  718:      for (i = 0; i < state->numPlayers; i++)
branch  0 taken 76%
branch  1 taken 24% (fallthrough)
        -:  719:	{
       96:  720:	  if (i != currentPlayer || i != 3)
branch  0 taken 31% (fallthrough)
branch  1 taken 69%
branch  2 taken 90% (fallthrough)
branch  3 taken 10%
        -:  721:	    {
      268:  722:	      for (j = 0; j < state->handCount[i]; j++)
branch  0 taken 82%
branch  1 taken 18% (fallthrough)
        -:  723:		{
      219:  724:		  if (state->hand[i][j] == copper)
branch  0 taken 20% (fallthrough)
branch  1 taken 80%
        -:  725:		    {
       44:  726:		      discardCard(j, i, state, 0);
call    0 returned 100%
       44:  727:		      break;
        -:  728:		    }
      175:  729:		  if (j == state->handCount[i])
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:  730:		    {
    #####:  731:		      for (k = 0; k < state->handCount[i]; k++)
branch  0 never executed
branch  1 never executed
        -:  732:			{
    #####:  733:			  if (DEBUG)
        -:  734:			    printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
        -:  735:			}	
    #####:  736:		      break;
        -:  737:		    }		
        -:  738:		}
        -:  739:					
        -:  740:	    }
        -:  741:				
        -:  742:	}				
        -:  743:
        -:  744:      //discard played card from hand
       30:  745:      discardCard(handPos, currentPlayer, state, 0);			
call    0 returned 100%
        -:  746:
       30:  747:      return 0;
        -:  748:		
        -:  749:}			
/*******************************************/





