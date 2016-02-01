Testing fullDeckCount()
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
----------------------------------------
*Basic requirements of fullDeckCount()
   1)Count how many of one card are in all of
      the decks.


All lines ran in fullDeckCount(), so I have 100% coverage.

   -Statement Coverage
      Tests coverade all nodes.
   -Branch Coverage

   -Path Coverage
      All possible paths covered.
   -Data Flow(def-use) Coverage
   
   -Model-based Testing Coverage
   
   
-Lines executed:16.92% of 585

/*******************************************
dominion.c.gcov
/*******************************************
    11664:  324:int fullDeckCount(int player, int card, struct gameState *state) {
        -:  325:  int i;
    11664:  326:  int count = 0;
        -:  327:
    40824:  328:  for (i = 0; i < state->deckCount[player]; i++)
        -:  329:    {
    29160:  330:      if (state->deck[player][i] == card) count++;
        -:  331:    }
        -:  332:
    40824:  333:  for (i = 0; i < state->handCount[player]; i++)
        -:  334:    {
    29160:  335:      if (state->hand[player][i] == card) count++;
        -:  336:    }
        -:  337:
    40824:  338:  for (i = 0; i < state->discardCount[player]; i++)
        -:  339:    {
    29160:  340:      if (state->discard[player][i] == card) count++;
        -:  341:    }
        -:  342:
    11664:  343:  return count;
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

Lines executed:21.03% of 585

All lines ran in fullDeckCount(), so I have 100% coverage.

/*******************************************
dominion.c.gcov
/*******************************************
2592:  417:int scoreFor (int player, struct gameState *state) {
        -:  418:
        -:  419:  int i;
     2592:  420:  int score = 0;
        -:  421:  //score from hand
     9072:  422:  for (i = 0; i < state->handCount[player]; i++)
        -:  423:    {
     6480:  424:      if (state->hand[player][i] == curse) { score = score - 1; };
     6480:  425:      if (state->hand[player][i] == estate) { score = score + 1; };
     6480:  426:      if (state->hand[player][i] == duchy) { score = score + 3; };
     6480:  427:      if (state->hand[player][i] == province) { score = score + 6; };
     6480:  428:      if (state->hand[player][i] == great_hall) { score = score + 1; };
     6480:  429:      if (state->hand[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
        -:  430:    }
        -:  431:
        -:  432:  //score from discard
     9072:  433:  for (i = 0; i < state->discardCount[player]; i++)
        -:  434:    {
     6480:  435:      if (state->discard[player][i] == curse) { score = score - 1; };
     6480:  436:      if (state->discard[player][i] == estate) { score = score + 1; };
     6480:  437:      if (state->discard[player][i] == duchy) { score = score + 3; };
     6480:  438:      if (state->discard[player][i] == province) { score = score + 6; };
     6480:  439:      if (state->discard[player][i] == great_hall) { score = score + 1; };
     6480:  440:      if (state->discard[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
        -:  441:    }
        -:  442:
        -:  443:  //score from deck
     9072:  444:  for (i = 0; i < state->discardCount[player]; i++)
        -:  445:    {
     6480:  446:      if (state->deck[player][i] == curse) { score = score - 1; };
     6480:  447:      if (state->deck[player][i] == estate) { score = score + 1; };
     6480:  448:      if (state->deck[player][i] == duchy) { score = score + 3; };
     6480:  449:      if (state->deck[player][i] == province) { score = score + 6; };
     6480:  450:      if (state->deck[player][i] == great_hall) { score = score + 1; };
     6480:  451:      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
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
