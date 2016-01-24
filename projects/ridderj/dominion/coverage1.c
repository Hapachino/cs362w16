Testing fullDeckCount()
-Lines executed:16.92% of 585
-All lines ran in fullDeckCount()
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