---------------------------------------------------------------------------
David Vogel
CS362 Assignment 3
Due Feb 3, 2016
Filename: coverage1.c

I've appended the output from gcov for my 4 card tests below. I have removed
all functions that were not covered at all.

Here is the summary:
    Lines executed:23.05% of 590
    Branches executed:26.14% of 417
    Taken at least once:17.27% of 417
    Calls executed:16.67% of 90

Since my tests only checked a small number of conditions and features,
there is no reason to think that there would be anywhere near full coverage.

Of interest, the following functions were all called and received 100% 
block coverage:
    "function compare called 120 returned 100% blocks executed 83%"
    "function initializeGame called 4 returned 100% blocks executed 88%"    
    "function shuffle called 8 returned 100% blocks executed 93%"
    "function whoseTurn called 4 returned 100% blocks executed 100%"
    "function drawCard called 28 returned 100% blocks executed 36%"
    "function cardEffect called 4 returned 100% blocks executed 11%"
    "function discardCard called 3 returned 100% blocks executed 75%"
    "function updateCoins called 5 returned 100% blocks executed 80%"
This indicates that none of the errors that were checked for in the
functions were ever triggered and the functions exited successfully 
each time they were called.

It is good to have these statistics so you know where top focus your
efforts when testing.

---------------------------------------------------------------------------
File 'dominion.c'
Lines executed:23.05% of 590
Branches executed:26.14% of 417
Taken at least once:17.27% of 417
Calls executed:16.67% of 90
dominion.c:creating 'dominion.c.gcov'

        -:    0:Source:dominion.c
        -:    0:Graph:dominion.gcno
        -:    0:Data:dominion.gcda
        -:    0:Runs:4
        -:    0:Programs:4
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include <stdio.h>
        -:    5:#include <math.h>
        -:    6:#include <stdlib.h>
        -:    7:
function compare called 120 returned 100% blocks executed 83%
      120:    8:int compare(const void *a, const void *b) {
      120:    9:  if (*(int *) a > *(int *) b)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:   10:    return 1;
      120:   11:  if (*(int *) a < *(int *) b)
branch  0 taken 27% (fallthrough)
branch  1 taken 73%
       32:   12:    return -1;
       88:   13:  return 0;
        -:   14:}
---------------------------------------------------------------------------
function initializeGame called 4 returned 100% blocks executed 88%
        4:   37:int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state) {
        -:   38:  int i, j, it;
        -:   39:  //set up random number generator
        4:   40:  SelectStream(1);
call    0 returned 100%
        4:   41:  PutSeed((long) randomSeed);
call    0 returned 100%
        -:   42:  //check number of players
        4:   43:  if (numPlayers > MAX_PLAYERS || numPlayers < 2)
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
branch  2 taken 0% (fallthrough)
branch  3 taken 100%
    #####:   44:    return -1;
        -:   45:  //set number of players
        4:   46:  state->numPlayers = numPlayers;
        -:   47:  //check selected kingdom cards are different
       44:   48:  for (i = 0; i < 10; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
      440:   49:    for (j = 0; j < 10; j++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
      400:   50:      if (j != i && kingdomCards[j] == kingdomCards[i])
branch  0 taken 90% (fallthrough)
branch  1 taken 10%
branch  2 taken 0% (fallthrough)
branch  3 taken 100%
    #####:   51:        return -1;
        -:   52:    }
        -:   53:  }
        -:   54:  //initialize supply  
        -:   55:  //set number of Curse cards
        4:   56:  if (numPlayers == 2)
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        4:   57:    state->supplyCount[curse] = 10;
    #####:   58:  else if (numPlayers == 3)
branch  0 never executed
branch  1 never executed
    #####:   59:    state->supplyCount[curse] = 20;
        -:   60:  else
    #####:   61:    state->supplyCount[curse] = 30;
        -:   62:  //set number of Victory cards
        4:   63:  if (numPlayers == 2) {
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        4:   64:    state->supplyCount[estate] = 8;
        4:   65:    state->supplyCount[duchy] = 8;
        4:   66:    state->supplyCount[province] = 8;
        -:   67:  }
        -:   68:  else {
    #####:   69:    state->supplyCount[estate] = 12;
    #####:   70:    state->supplyCount[duchy] = 12;
    #####:   71:    state->supplyCount[province] = 12;
        -:   72:  }
        -:   73:  //set number of Treasure cards
        4:   74:  state->supplyCount[copper] = 60 - (7 * numPlayers);
        4:   75:  state->supplyCount[silver] = 40;
        4:   76:  state->supplyCount[gold] = 30;
        -:   77:  //set number of Kingdom cards
       84:   78:  for (i = adventurer; i <= treasure_map; i++) { //loop all cards  
branch  0 taken 95%
branch  1 taken 5% (fallthrough)
      660:   79:    for (j = 0; j < 10; j++) { //loop chosen cards    
branch  0 taken 94%
branch  1 taken 6% (fallthrough)
      620:   80:      if (kingdomCards[j] == i) { //check if card is a 'Victory' Kingdom card        
branch  0 taken 6% (fallthrough)
branch  1 taken 94%
       42:   81:        if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens) {
branch  0 taken 95% (fallthrough)
branch  1 taken 5%
branch  2 taken 0% (fallthrough)
branch  3 taken 100%
        2:   82:          if (numPlayers == 2)
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        2:   83:            state->supplyCount[i] = 8;
        -:   84:          else
    #####:   85:            state->supplyCount[i] = 12;
        -:   86:        }
        -:   87:        else
       38:   88:          state->supplyCount[i] = 10;
       40:   89:        break;
        -:   90:      }
        -:   91:      else    //card is not in the set choosen for the game
      580:   92:        state->supplyCount[i] = -1;
        -:   93:    }
        -:   94:  }
        -:   95:  //supply intilization complete
        -:   96:  //set player decks
       12:   97:  for (i = 0; i < numPlayers; i++) {
branch  0 taken 67%
branch  1 taken 33% (fallthrough)
        8:   98:    state->deckCount[i] = 0;
       32:   99:    for (j = 0; j < 3; j++) {
branch  0 taken 75%
branch  1 taken 25% (fallthrough)
       24:  100:      state->deck[i][j] = estate;
       24:  101:      state->deckCount[i]++;
        -:  102:    }
       64:  103:    for (j = 3; j < 10; j++) {
branch  0 taken 88%
branch  1 taken 13% (fallthrough)
       56:  104:      state->deck[i][j] = copper;
       56:  105:      state->deckCount[i]++;
        -:  106:    }
        -:  107:  }
        -:  108:  //shuffle player decks
       12:  109:  for (i = 0; i < numPlayers; i++) {
branch  0 taken 67%
branch  1 taken 33% (fallthrough)
        8:  110:    if (shuffle(i, state) < 0)
call    0 returned 100%
branch  1 taken 0% (fallthrough)
branch  2 taken 100%
    #####:  111:      return -1;
        -:  112:  }
       12:  113:  for (i = 0; i < numPlayers; i++) {
branch  0 taken 67%
branch  1 taken 33% (fallthrough)
        8:  114:    state->handCount[i] = 0;
        8:  115:    state->discardCount[i] = 0;
        -:  116:  }
        -:  117:  //set embargo tokens to 0 for all supply piles
      112:  118:  for (i = 0; i <= treasure_map; i++)
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
      108:  119:    state->embargoTokens[i] = 0;
        -:  120:  //initialize first player's turn
        4:  121:  state->outpostPlayed = 0;
        4:  122:  state->phase = 0;
        4:  123:  state->numActions = 1;
        4:  124:  state->numBuys = 1;
        4:  125:  state->playedCardCount = 0;
        4:  126:  state->whoseTurn = 0;
        4:  127:  state->handCount[state->whoseTurn] = 0;
        -:  128:  //Moved draw cards to here, only drawing at the start of a turn
       24:  129:  for (it = 0; it < 5; it++)
branch  0 taken 83%
branch  1 taken 17% (fallthrough)
       20:  130:    drawCard(state->whoseTurn, state);
call    0 returned 100%
        4:  131:  updateCoins(state->whoseTurn, state, 0);
call    0 returned 100%
        4:  132:  return 0;
        -:  133:}
        -:  134:
---------------------------------------------------------------------------        
function shuffle called 8 returned 100% blocks executed 93%
        8:  135:int shuffle(int player, struct gameState *state) {
        8:  136:  int newDeck[MAX_DECK], newDeckPos = 0, card, i;
        8:  137:  if (state->deckCount[player] < 1)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  138:    return -1;
        8:  139:  qsort((void *) (state->deck[player]), state->deckCount[player], sizeof(int), compare);
call    0 returned 100%
        -:  140:  /* SORT CARDS IN DECK TO ENSURE DETERMINISM! */
       96:  141:  while (state->deckCount[player] > 0) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       80:  142:    card = floor(Random() * state->deckCount[player]);
call    0 returned 100%
       80:  143:    newDeck[newDeckPos] = state->deck[player][card];
       80:  144:    newDeckPos++;
      271:  145:    for (i = card; i < state->deckCount[player] - 1; i++)
branch  0 taken 70%
branch  1 taken 30% (fallthrough)
      191:  146:      state->deck[player][i] = state->deck[player][i + 1];
       80:  147:    state->deckCount[player]--;
        -:  148:  }
       88:  149:  for (i = 0; i < newDeckPos; i++) {
branch  0 taken 91%
branch  1 taken 9% (fallthrough)
       80:  150:    state->deck[player][i] = newDeck[i];
       80:  151:    state->deckCount[player]++;
        -:  152:  }
        8:  153:  return 0;
        -:  154:}
        -:  155:
---------------------------------------------------------------------------
function whoseTurn called 4 returned 100% blocks executed 100%
        4:  244:int whoseTurn(struct gameState *state) {
        4:  245:  return state->whoseTurn;
        -:  246:}
        -:  247:
---------------------------------------------------------------------------
function drawCard called 28 returned 100% blocks executed 36%
       28:  385:int drawCard(int player, struct gameState *state) {
        -:  386:  int count, deckCounter, i;
       28:  387:  if (state->deckCount[player] <= 0) {//Deck is empty
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
        -:  388:    //Step 1 Shuffle the discard pile back into a deck
        -:  389:    //Move discard to deck
    #####:  390:    for (i = 0; i < state->discardCount[player]; i++) {
branch  0 never executed
branch  1 never executed
    #####:  391:      state->deck[player][i] = state->discard[player][i];
    #####:  392:      state->discard[player][i] = -1;
        -:  393:    }
    #####:  394:    state->deckCount[player] = state->discardCount[player];
    #####:  395:    state->discardCount[player] = 0;//Reset discard
        -:  396:    //Shufffle the deck
    #####:  397:    shuffle(player, state);//Shuffle the deck up and make it so that we can draw
call    0 never executed
    #####:  398:    if (DEBUG) //Debug statements
        -:  399:      printf("Deck count now: %d\n", state->deckCount[player]);
    #####:  400:    state->discardCount[player] = 0;
        -:  401:    //Step 2 Draw Card
    #####:  402:    count = state->handCount[player];//Get current player's hand count
    #####:  403:    if (DEBUG) //Debug statements
        -:  404:      printf("Current hand count: %d\n", count);
    #####:  405:    deckCounter = state->deckCount[player];//Create a holder for the deck count
    #####:  406:    if (deckCounter == 0)
branch  0 never executed
branch  1 never executed
    #####:  407:      return -1;
    #####:  408:    state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to hand
    #####:  409:    state->deckCount[player]--;
    #####:  410:    state->handCount[player]++;//Increment hand count
        -:  411:  }
        -:  412:  else {
       28:  413:    int count = state->handCount[player];//Get current hand count for player
        -:  414:    int deckCounter;
       28:  415:    if (DEBUG) //Debug statements
        -:  416:      printf("Current hand count: %d\n", count);
       28:  417:    deckCounter = state->deckCount[player];//Create holder for the deck count
       28:  418:    state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to the hand
       28:  419:    state->deckCount[player]--;
       28:  420:    state->handCount[player]++;//Increment hand count
        -:  421:  }
       28:  422:  return 0;
        -:  423:}
        -:  424:
---------------------------------------------------------------------------
function cardEffect called 4 returned 100% blocks executed 11%
        4:  485:int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus) {
        -:  486:  int i, j, k, x, index;
        4:  487:  int currentPlayer = whoseTurn(state);
call    0 returned 100%
        4:  488:  int nextPlayer = currentPlayer + 1;
        4:  489:  int tributeRevealedCards[2] = {-1, -1};
        -:  490:  int temphand[MAX_HAND];// moved above the if statement
        4:  491:  int drawntreasure = 0;
        -:  492:  int cardDrawn;
        4:  493:  int z = 0;// this is the counter for the temp hand
        4:  494:  if (nextPlayer > (state->numPlayers - 1))
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  495:    nextPlayer = 0;
        -:  496:  //uses switch to select card and perform actions
        4:  497:  switch (card) {
branch  0 taken 25%
branch  1 taken 0%
branch  2 taken 0%
branch  3 taken 0%
branch  4 taken 0%
branch  5 taken 0%
branch  6 taken 25%
branch  7 taken 25%
branch  8 taken 0%
branch  9 taken 25%
branch 10 taken 0%
branch 11 taken 0%
branch 12 taken 0%
branch 13 taken 0%
branch 14 taken 0%
branch 15 taken 0%
branch 16 taken 0%
branch 17 taken 0%
branch 18 taken 0%
branch 19 taken 0%
branch 20 taken 0%
        -:  498:    case adventurer:
        5:  499:      while (drawntreasure < 2) {
branch  0 taken 75%
branch  1 taken 25% (fallthrough)
        3:  500:        if (state->deckCount[currentPlayer] < 1) //if the deck is empty we need to shuffle discard and add to deck
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  501:          shuffle(currentPlayer, state);
call    0 never executed
        3:  502:        drawCard(currentPlayer, state);
call    0 returned 100%
        -:  503:        //top card of hand is most recently drawn card.
        3:  504:        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];
        5:  505:        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
branch  0 taken 33% (fallthrough)
branch  1 taken 67%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 0% (fallthrough)
branch  5 taken 100%
        2:  506:          drawntreasure++;
        -:  507:        else {
        1:  508:          temphand[z] = cardDrawn;
        1:  509:          state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
        1:  510:          z++;
        -:  511:        }
        -:  512:      }
        3:  513:      while (z - 1 >= 0) {
branch  0 taken 50%
branch  1 taken 50% (fallthrough)
        -:  514:        // discard all cards in play that have been drawn
        1:  515:        state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z - 1];
        1:  516:        z = z - 1;
        -:  517:      }
        1:  518:      return 0;
        -:  519:
        -:  520:    case council_room:      
    #####:  521:      for (i = 0; i < 4; i++) //+4 Cards
branch  0 never executed
branch  1 never executed
    #####:  522:        drawCard(currentPlayer, state);      
call    0 never executed
    #####:  523:      state->numBuys++; //+1 Buy
        -:  524:      //Each other player draws a card
    #####:  525:      for (i = 0; i < state->numPlayers; i++) {
branch  0 never executed
branch  1 never executed
    #####:  526:        if (i != currentPlayer)
branch  0 never executed
branch  1 never executed
    #####:  527:          drawCard(i, state);
call    0 never executed
        -:  528:      }
        -:  529:      //put played card in played card pile
    #####:  530:      discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
    #####:  531:      return 0;
        -:  532:
        -:  533:    case feast: //gain card with cost up to 5      
        -:  534:      //Backup hand
    #####:  535:      for (i = 0; i <= state->handCount[currentPlayer]; i++) {
branch  0 never executed
branch  1 never executed
    #####:  536:        temphand[i] = state->hand[currentPlayer][i];//Backup card
    #####:  537:        state->hand[currentPlayer][i] = -1;//Set to nothing
        -:  538:      }
        -:  539:      //Update Coins for Buy
    #####:  540:      updateCoins(currentPlayer, state, 5);
call    0 never executed
    #####:  541:      x = 1;//Condition to loop on
    #####:  542:      while (x == 1) {//Buy one card
branch  0 never executed
branch  1 never executed
    #####:  543:        if (supplyCount(choice1, state) <= 0) {
call    0 never executed
branch  1 never executed
branch  2 never executed
    #####:  544:          if (DEBUG)
        -:  545:            printf("None of that card left, sorry!\n");
    #####:  546:          if (DEBUG)
        -:  547:            printf("Cards Left: %d\n", supplyCount(choice1, state));
        -:  548:        }
    #####:  549:        else if (state->coins < getCost(choice1)) {
call    0 never executed
branch  1 never executed
branch  2 never executed
    #####:  550:          printf("That card is too expensive!\n");
call    0 never executed
    #####:  551:          if (DEBUG)
        -:  552:            printf("Coins: %d < %d\n", state->coins, getCost(choice1));
        -:  553:        }
        -:  554:        else {
    #####:  555:          if (DEBUG)
        -:  556:            printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] +
        -:  557:                                       state->discardCount[currentPlayer]);
    #####:  558:          gainCard(choice1, state, 0, currentPlayer);//Gain the card
call    0 never executed
    #####:  559:          x = 0;//No more buying cards
    #####:  560:          if (DEBUG)
        -:  561:            printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] +
        -:  562:                                       state->discardCount[currentPlayer]);
        -:  563:        }
        -:  564:      }
        -:  565:      //Reset Hand
    #####:  566:      for (i = 0; i <= state->handCount[currentPlayer]; i++) {
branch  0 never executed
branch  1 never executed
    #####:  567:        state->hand[currentPlayer][i] = temphand[i];
    #####:  568:        temphand[i] = -1;
        -:  569:      }
    #####:  570:      return 0;
        -:  571:
        -:  572:    case gardens:
    #####:  573:      return -1;
        -:  574:
        -:  575:    case mine:
    #####:  576:      j = state->hand[currentPlayer][choice1];  //store card we will trash
    #####:  577:      if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:  578:        return -1;
    #####:  579:      if (choice2 > treasure_map || choice2 < curse)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:  580:        return -1;
    #####:  581:      if ((getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2))
call    0 never executed
call    1 never executed
branch  2 never executed
branch  3 never executed
    #####:  582:        return -1;      
    #####:  583:      gainCard(choice2, state, 2, currentPlayer);      
call    0 never executed
    #####:  584:      discardCard(handPos, currentPlayer, state, 0); //discard card from hand
call    0 never executed
        -:  585:      //discard trashed card
    #####:  586:      for (i = 0; i < state->handCount[currentPlayer]; i++) {
branch  0 never executed
branch  1 never executed
    #####:  587:        if (state->hand[currentPlayer][i] == j) {
branch  0 never executed
branch  1 never executed
    #####:  588:          discardCard(i, currentPlayer, state, 0);
call    0 never executed
    #####:  589:          break;
        -:  590:        }
        -:  591:      }
    #####:  592:      return 0;
        -:  593:
        -:  594:    case remodel:
    #####:  595:      j = state->hand[currentPlayer][choice1];  //store card we will trash
    #####:  596:      if ((getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2))
call    0 never executed
call    1 never executed
branch  2 never executed
branch  3 never executed
    #####:  597:        return -1;
    #####:  598:      gainCard(choice2, state, 0, currentPlayer);      
call    0 never executed
    #####:  599:      discardCard(handPos, currentPlayer, state, 0); //discard card from hand
call    0 never executed
        -:  600:      //discard trashed card
    #####:  601:      for (i = 0; i < state->handCount[currentPlayer]; i++) {
branch  0 never executed
branch  1 never executed
    #####:  602:        if (state->hand[currentPlayer][i] == j) {
branch  0 never executed
branch  1 never executed
    #####:  603:          discardCard(i, currentPlayer, state, 0);
call    0 never executed
    #####:  604:          break;
        -:  605:        }
        -:  606:      }
    #####:  607:      return 0;
        -:  608:
        -:  609:    case smithy: //+3 Cards      
        4:  610:      for (i = 0; i < 3; i++)
branch  0 taken 75%
branch  1 taken 25% (fallthrough)
        3:  611:        drawCard(currentPlayer, state);      
call    0 returned 100%
        1:  612:      discardCard(handPos, currentPlayer, state, 0); //discard card from hand
call    0 returned 100%
        1:  613:      return 0;
        -:  614:
        -:  615:    case village: //+1 Card      
        1:  616:      drawCard(currentPlayer, state);      
call    0 returned 100%
        1:  617:      state->numActions = state->numActions + 2; //+2 Actions      
        1:  618:      discardCard(handPos, currentPlayer, state, 0); //discard played card from hand
call    0 returned 100%
        1:  619:      return 0;
        -:  620:
        -:  621:    case baron:
    #####:  622:      state->numBuys++;//Increase buys by 1
    #####:  623:      if (choice1 > 0) {//Boolean true or going to discard an estate
branch  0 never executed
branch  1 never executed
    #####:  624:        int p = 0;//Iterator for hand
    #####:  625:        int card_not_discarded = 1;//Flag for discard set
    #####:  626:        while (card_not_discarded) {
branch  0 never executed
branch  1 never executed
    #####:  627:          if (state->hand[currentPlayer][p] == estate) {//Found an estate card
branch  0 never executed
branch  1 never executed
    #####:  628:            state->coins += 4;//Add 4 coins to the amount of coins
    #####:  629:            state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
    #####:  630:            state->discardCount[currentPlayer]++;
    #####:  631:            for (; p < state->handCount[currentPlayer]; p++)
branch  0 never executed
branch  1 never executed
    #####:  632:              state->hand[currentPlayer][p] = state->hand[currentPlayer][p + 1];
    #####:  633:            state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
    #####:  634:            state->handCount[currentPlayer]--;
    #####:  635:            card_not_discarded = 0;//Exit the loop
        -:  636:          }
    #####:  637:          else if (p > state->handCount[currentPlayer]) {
branch  0 never executed
branch  1 never executed
    #####:  638:            if (DEBUG) {
        -:  639:              printf("No estate cards in your hand, invalid choice\n");
        -:  640:              printf("Must gain an estate if there are any\n");
        -:  641:            }
    #####:  642:            if (supplyCount(estate, state) > 0) {
call    0 never executed
branch  1 never executed
branch  2 never executed
    #####:  643:              gainCard(estate, state, 0, currentPlayer);
call    0 never executed
    #####:  644:              state->supplyCount[estate]--;//Decrement estates
    #####:  645:              if (supplyCount(estate, state) == 0)
call    0 never executed
branch  1 never executed
branch  2 never executed
    #####:  646:                isGameOver(state);
call    0 never executed
        -:  647:            }
    #####:  648:            card_not_discarded = 0;//Exit the loop
        -:  649:          }
        -:  650:          else
    #####:  651:            p++;//Next card
        -:  652:        }
        -:  653:      }
        -:  654:      else {
    #####:  655:        if (supplyCount(estate, state) > 0) {
call    0 never executed
branch  1 never executed
branch  2 never executed
    #####:  656:          gainCard(estate, state, 0, currentPlayer);//Gain an estate
call    0 never executed
    #####:  657:          state->supplyCount[estate]--;//Decrement Estates
    #####:  658:          if (supplyCount(estate, state) == 0)
call    0 never executed
branch  1 never executed
branch  2 never executed
    #####:  659:            isGameOver(state);
call    0 never executed
        -:  660:        }
        -:  661:      }
    #####:  662:      return 0;
        -:  663:
        -:  664:    case great_hall: //+1 Card      
        1:  665:      drawCard(currentPlayer, state);      
call    0 returned 100%
        1:  666:      state->numActions++; //+1 Actions      
        1:  667:      discardCard(handPos, currentPlayer, state, 0); //discard card from hand
call    0 returned 100%
        1:  668:      return 0;
        -:  669:
        -:  670:    case minion: //+1 action      
    #####:  671:      state->numActions++;      
    #####:  672:      discardCard(handPos, currentPlayer, state, 0); //discard card from hand
call    0 never executed
    #####:  673:      if (choice1) //+2 coins
branch  0 never executed
branch  1 never executed
    #####:  674:        state->coins = state->coins + 2;
    #####:  675:      else if (choice2) { //discard hand, redraw 4, other players with 5+ cards discard hand and draw 4        
branch  0 never executed
branch  1 never executed
    #####:  676:        while (numHandCards(state) > 0) //discard hand
call    0 never executed
branch  1 never executed
branch  2 never executed
    #####:  677:          discardCard(handPos, currentPlayer, state, 0);
call    0 never executed
    #####:  678:        for (i = 0; i < 4; i++) //draw 4
branch  0 never executed
branch  1 never executed
    #####:  679:          drawCard(currentPlayer, state);
call    0 never executed
        -:  680:        //other players discard hand and redraw if hand size > 4
    #####:  681:        for (i = 0; i < state->numPlayers; i++) {
branch  0 never executed
branch  1 never executed
    #####:  682:          if (i != currentPlayer) {
branch  0 never executed
branch  1 never executed
    #####:  683:            if (state->handCount[i] > 4) {              
branch  0 never executed
branch  1 never executed
    #####:  684:              while (state->handCount[i] > 0) //discard hand
branch  0 never executed
branch  1 never executed
    #####:  685:                discardCard(handPos, i, state, 0);              
call    0 never executed
    #####:  686:              for (j = 0; j < 4; j++) //draw 4
branch  0 never executed
branch  1 never executed
    #####:  687:                drawCard(i, state);
call    0 never executed
        -:  688:            }
        -:  689:          }
        -:  690:        }
        -:  691:      }
    #####:  692:      return 0;
        -:  693:
        -:  694:    case steward:
    #####:  695:      if (choice1 == 1) { //+2 cards        
branch  0 never executed
branch  1 never executed
    #####:  696:        drawCard(currentPlayer, state);
call    0 never executed
    #####:  697:        drawCard(currentPlayer, state);
call    0 never executed
        -:  698:      }
    #####:  699:      else if (choice1 == 2) //+2 coins        
branch  0 never executed
branch  1 never executed
    #####:  700:        state->coins = state->coins + 2;
        -:  701:      else { //trash 2 cards in hand
    #####:  702:        discardCard(choice2, currentPlayer, state, 1);
call    0 never executed
    #####:  703:        discardCard(choice3, currentPlayer, state, 1);
call    0 never executed
        -:  704:      }      
    #####:  705:      discardCard(handPos, currentPlayer, state, 0); //discard card from hand
call    0 never executed
    #####:  706:      return 0;
        -:  707:
        -:  708:    case tribute:
    #####:  709:      if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1) {
branch  0 never executed
branch  1 never executed
    #####:  710:        if (state->deckCount[nextPlayer] > 0) {
branch  0 never executed
branch  1 never executed
    #####:  711:          tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer] - 1];
    #####:  712:          state->deckCount[nextPlayer]--;
        -:  713:        }
    #####:  714:        else if (state->discardCount[nextPlayer] > 0) {
branch  0 never executed
branch  1 never executed
    #####:  715:          tributeRevealedCards[0] = state->discard[nextPlayer][state->discardCount[nextPlayer] - 1];
    #####:  716:          state->discardCount[nextPlayer]--;
        -:  717:        }
        -:  718:        else //No Card to Reveal          
    #####:  719:          if (DEBUG)
        -:  720:            printf("No cards to reveal\n");
        -:  721:      }
        -:  722:      else {
    #####:  723:        if (state->deckCount[nextPlayer] == 0) {
branch  0 never executed
branch  1 never executed
    #####:  724:          for (i = 0; i < state->discardCount[nextPlayer]; i++) {
branch  0 never executed
branch  1 never executed
    #####:  725:            state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
    #####:  726:            state->deckCount[nextPlayer]++;
    #####:  727:            state->discard[nextPlayer][i] = -1;
    #####:  728:            state->discardCount[nextPlayer]--;
        -:  729:          }
    #####:  730:          shuffle(nextPlayer, state);//Shuffle the deck
call    0 never executed
        -:  731:        }
    #####:  732:        tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer] - 1];
    #####:  733:        state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
    #####:  734:        state->deckCount[nextPlayer]--;
    #####:  735:        tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer] - 1];
    #####:  736:        state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
    #####:  737:        state->deckCount[nextPlayer]--;
        -:  738:      }
    #####:  739:      if (tributeRevealedCards[0] == tributeRevealedCards[1]) {//If we have a duplicate card, just drop one
branch  0 never executed
branch  1 never executed
    #####:  740:        state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
    #####:  741:        state->playedCardCount++;
    #####:  742:        tributeRevealedCards[1] = -1;
        -:  743:      }
    #####:  744:      for (i = 0; i <= 2; i++) {
branch  0 never executed
branch  1 never executed
    #####:  745:        if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver 
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
branch  4 never executed
branch  5 never executed
    #####:  746:          || tributeRevealedCards[i] == gold) {//Treasure cards
    #####:  747:          state->coins += 2;
        -:  748:        }
    #####:  749:        else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
branch  4 never executed
branch  5 never executed
branch  6 never executed
branch  7 never executed
branch  8 never executed
branch  9 never executed
    #####:  750:                 || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens
    #####:  751:                 || tributeRevealedCards[i] == great_hall) {//Victory Card Found
    #####:  752:          drawCard(currentPlayer, state);
call    0 never executed
    #####:  753:          drawCard(currentPlayer, state);
call    0 never executed
        -:  754:        }
        -:  755:        else //Action Card
    #####:  756:          state->numActions = state->numActions + 2;
        -:  757:      }
    #####:  758:      return 0;
        -:  759:
        -:  760:    case ambassador:
    #####:  761:      j = 0;    //used to check if player has enough cards to discard
    #####:  762:      if (choice2 > 2 || choice2 < 0)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:  763:        return -1;
    #####:  764:      if (choice1 == handPos)
branch  0 never executed
branch  1 never executed
    #####:  765:        return -1;
    #####:  766:      for (i = 0; i < state->handCount[currentPlayer]; i++) {
branch  0 never executed
branch  1 never executed
    #####:  767:        if (i != handPos && i == state->hand[currentPlayer][choice1] && i != choice1)
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
branch  4 never executed
branch  5 never executed
    #####:  768:          j++;
        -:  769:      }
    #####:  770:      if (j < choice2)
branch  0 never executed
branch  1 never executed
    #####:  771:        return -1;
    #####:  772:      if (DEBUG)
        -:  773:        printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][choice1]);
        -:  774:      //increase supply count for choosen card by amount being discarded
    #####:  775:      state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;
        -:  776:      //each other player gains a copy of revealed card
    #####:  777:      for (i = 0; i < state->numPlayers; i++) {
branch  0 never executed
branch  1 never executed
    #####:  778:        if (i != currentPlayer)
branch  0 never executed
branch  1 never executed
    #####:  779:          gainCard(state->hand[currentPlayer][choice1], state, 0, i);
call    0 never executed
        -:  780:      }      
    #####:  781:      discardCard(handPos, currentPlayer, state, 0); //discard played card from hand
call    0 never executed
        -:  782:      //trash copies of cards returned to supply
    #####:  783:      for (j = 0; j < choice2; j++) {
branch  0 never executed
branch  1 never executed
    #####:  784:        for (i = 0; i < state->handCount[currentPlayer]; i++) {
branch  0 never executed
branch  1 never executed
    #####:  785:          if (state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1]) {
branch  0 never executed
branch  1 never executed
    #####:  786:            discardCard(i, currentPlayer, state, 1);
call    0 never executed
    #####:  787:            break;
        -:  788:          }
        -:  789:        }
        -:  790:      }
    #####:  791:      return 0;
        -:  792:
        -:  793:    case cutpurse:
    #####:  794:      updateCoins(currentPlayer, state, 2);
call    0 never executed
    #####:  795:      for (i = 0; i < state->numPlayers; i++) {
branch  0 never executed
branch  1 never executed
    #####:  796:        if (i != currentPlayer) {
branch  0 never executed
branch  1 never executed
    #####:  797:          for (j = 0; j < state->handCount[i]; j++) {
branch  0 never executed
branch  1 never executed
    #####:  798:            if (state->hand[i][j] == copper) {
branch  0 never executed
branch  1 never executed
    #####:  799:              discardCard(j, i, state, 0);
call    0 never executed
    #####:  800:              break;
        -:  801:            }
    #####:  802:            if (j == state->handCount[i]) {
branch  0 never executed
branch  1 never executed
    #####:  803:              for (k = 0; k < state->handCount[i]; k++) {
branch  0 never executed
branch  1 never executed
    #####:  804:                if (DEBUG)
        -:  805:                  printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
        -:  806:              }
    #####:  807:              break;
        -:  808:            }
        -:  809:          }
        -:  810:        }
        -:  811:      }      
    #####:  812:      discardCard(handPos, currentPlayer, state, 0); //discard played card from hand
call    0 never executed
    #####:  813:      return 0;
        -:  814:
        -:  815:    case embargo:      
    #####:  816:      state->coins = state->coins + 2; //+2 Coins
        -:  817:      //see if selected pile is in play
    #####:  818:      if (state->supplyCount[choice1] == -1)
branch  0 never executed
branch  1 never executed
    #####:  819:        return -1;
        -:  820:      //add embargo token to selected supply pile
    #####:  821:      state->embargoTokens[choice1]++;
        -:  822:      //trash card
    #####:  823:      discardCard(handPos, currentPlayer, state, 1);
call    0 never executed
    #####:  824:      return 0;
        -:  825:
        -:  826:    case outpost:      
    #####:  827:      state->outpostPlayed++; //set outpost flag      
    #####:  828:      discardCard(handPos, currentPlayer, state, 0); //discard card
call    0 never executed
    #####:  829:      return 0;
        -:  830:
        -:  831:    case salvager: //+1 buy      
    #####:  832:      state->numBuys++;
    #####:  833:      if (choice1) { //gain coins equal to trashed card        
branch  0 never executed
branch  1 never executed
    #####:  834:        state->coins = state->coins + getCost(handCard(choice1, state));        
call    0 never executed
call    1 never executed
    #####:  835:        discardCard(choice1, currentPlayer, state, 1); //trash card
call    0 never executed
        -:  836:      }      
    #####:  837:      discardCard(handPos, currentPlayer, state, 0); //discard card
call    0 never executed
    #####:  838:      return 0;
        -:  839:
        -:  840:    case sea_hag:
    #####:  841:      for (i = 0; i < state->numPlayers; i++) {
branch  0 never executed
branch  1 never executed
    #####:  842:        if (i != currentPlayer) {
branch  0 never executed
branch  1 never executed
    #####:  843:          state->discard[i][state->discardCount[i]] = state->deck[i][state->deckCount[i]--];
    #####:  844:          state->deckCount[i]--;
    #####:  845:          state->discardCount[i]++;
    #####:  846:          state->deck[i][state->deckCount[i]--] = curse;//Top card now a curse
        -:  847:        }
        -:  848:      }
    #####:  849:      return 0;
        -:  850:
        -:  851:    case treasure_map:      
    #####:  852:      index = -1; //search hand for another treasure_map
    #####:  853:      for (i = 0; i < state->handCount[currentPlayer]; i++) {
branch  0 never executed
branch  1 never executed
    #####:  854:        if (state->hand[currentPlayer][i] == treasure_map && i != handPos) {
branch  0 never executed
branch  1 never executed
branch  2 never executed
branch  3 never executed
    #####:  855:          index = i;
    #####:  856:          break;
        -:  857:        }
        -:  858:      }
    #####:  859:      if (index > -1) {
branch  0 never executed
branch  1 never executed
        -:  860:        //trash both treasure cards
    #####:  861:        discardCard(handPos, currentPlayer, state, 1);
call    0 never executed
    #####:  862:        discardCard(index, currentPlayer, state, 1);        
call    0 never executed
    #####:  863:        for (i = 0; i < 4; i++) //gain 4 Gold cards
branch  0 never executed
branch  1 never executed
    #####:  864:          gainCard(gold, state, 1, currentPlayer);        
call    0 never executed
    #####:  865:        return 1; //return success
        -:  866:      }
        -:  867:      //no second treasure_map found in hand
    #####:  868:      return -1;
        -:  869:  }
    #####:  870:  return -1;
        -:  871:}
        -:  872:
---------------------------------------------------------------------------        
function discardCard called 3 returned 100% blocks executed 75%
        3:  873:int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag) {
        -:  874:  //if card is not trashed, added to Played pile 
        3:  875:  if (trashFlag < 1) { //add card to played pile    
branch  0 taken 100% (fallthrough)
branch  1 taken 0%
        3:  876:    state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos];
        3:  877:    state->playedCardCount++;
        -:  878:  }  
        3:  879:  state->hand[currentPlayer][handPos] = -1; //set played card to -1
        -:  880:  //remove card from player's hand
        3:  881:  if (handPos == (state->handCount[currentPlayer] - 1))  //last card in hand array is played
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  882:    state->handCount[currentPlayer]--; //reduce number of cards in hand
        3:  883:  else if (state->handCount[currentPlayer] == 1) //only one card in hand
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  884:    state->handCount[currentPlayer]--; //reduce number of cards in hand
        -:  885:  else { //replace discarded card with last card in hand    
        3:  886:    state->hand[currentPlayer][handPos] = state->hand[currentPlayer][(state->handCount[currentPlayer] - 1)];
        -:  887:    //set last card to -1
        3:  888:    state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
        -:  889:    //reduce number of cards in hand
        3:  890:    state->handCount[currentPlayer]--;
        -:  891:  }
        3:  892:  return 0;
        -:  893:}
        -:  894:
---------------------------------------------------------------------------
function updateCoins called 5 returned 100% blocks executed 80%
        5:  920:int updateCoins(int player, struct gameState *state, int bonus) {
        -:  921:  int i;  
        5:  922:  state->coins = 0; //reset coin count
        -:  923:  //add coins for each Treasure card in player's hand
       32:  924:  for (i = 0; i < state->handCount[player]; i++) {
branch  0 taken 84%
branch  1 taken 16% (fallthrough)
       27:  925:    if (state->hand[player][i] == copper)
branch  0 taken 81% (fallthrough)
branch  1 taken 19%
       22:  926:      state->coins += 1;
        5:  927:    else if (state->hand[player][i] == silver)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  928:      state->coins += 2;
        5:  929:    else if (state->hand[player][i] == gold)
branch  0 taken 0% (fallthrough)
branch  1 taken 100%
    #####:  930:      state->coins += 3;
        -:  931:  }  
        5:  932:  state->coins += bonus; //add bonus
        5:  933:  return 0;
        -:  934:}
        -:  935://end of dominion.c