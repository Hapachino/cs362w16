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

**** DISCUSSION
I wouldn't expect that testing four functions and four cards
would get us anywhere close to 100% coverage.  Still,
32% will be a baseline going forward.  

I noticed that even after
running only Unit Test 1, my line coverate was at 18%.
This is probably due to the invoking of initializeGame()
and other helper functions.  

I should note that there are a lot of case statements for cards 
that are not used the way the game is currently set up to be played.
This will drive down the overall coverage percentage.

The following functions were not covered at all by this test suite.
These will require closer attention in a future test suite:
    newGame()
    kingdomCards()
    playCard()
    buyCard()
    handCard()
    supplyCount()
    fullDeckCount()
    scoreFor()
    getWinners()
    gainCard()


*******************
Unit Test 1: isGameOver()
*******************
Function 'isGameOver'
Lines executed:100.00% of 12
Branches executed:100.00% of 8
Taken at least once:100.00% of 8

**** DISCUSSION
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

**** DISCUSSION
This function is covered 100% by testing every possible permutation
of player and bonus value on six test hands designed
to activate every branch.


*******************
Unit Test 3: discardCard()
*******************
Function 'discardCard'
Lines executed:86.67% of 15
Branches executed:100.00% of 6
Taken at least once:83.33% of 6

**** DISCUSSION
The branch that was missed here was when there's only one 
card in the hand:
        -: 1286:    {
        -: 1287:      //reduce number of cards in hand
    #####: 1288:      state->handCount[currentPlayer]--;
    #####: 1289:    }
This should be covered by an additional test case.

*******************
Unit Test 4: getCost()
*******************
Function 'getCost'
Lines executed:96.67% of 30
Branches executed:100.00% of 28
Taken at least once:96.43% of 28

**** DISCUSSION
It was easy to achieve full coverage for this function
simply by testing every possible case switch value.
The one line that wasn't executed was "return -1",
which happens if you pass an invalid coin.


*******************
Card Test 1: Smithy
*******************
Function 'smithy_card'
Lines executed:100.00% of 7
Branches executed:100.00% of 4
Taken at least once:100.00% of 4

**** DISCUSSION
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

**** DISCUSSION
Several conditions weren't reached in my test of Adventurer.  
The empty deck causing shuffle was not covered.
The (drawntreasure == 1) gate was also not reached, meaning the bug
I introduced was not caught.  I think this may be due to the non-random way
the game is seeded.  It looks like my tests were only drawing 
treasure cards and then exiting, without putting the tempHand
in the discard pile.


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
        
**** DISCUSSION
Since council_room and great_hall are contained within a switch statement,
I instead show the raw gcov output.
For council room I have 100% branch and statement coverage.
We can see by the numers on the left that each statement was executed at least 4 times.

*******************
Card Test 4: Great Hall
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
        
**** DISCUSSION
For Great Hall I have 100% statement coverage.
There are no branches so branch coverage is not relevant here.

*/


/* FULL OUTPUT OF `gcov dominion.c -f -b`
Function 'compare'
Lines executed:83.33% of 6
Branches executed:100.00% of 4
Taken at least once:75.00% of 4
No calls

Function 'newGame'
Lines executed:0.00% of 2
No branches
No calls

Function 'kingdomCards'
Lines executed:0.00% of 12
No branches
No calls

Function 'initializeGame'
Lines executed:85.90% of 78
Branches executed:95.65% of 46
Taken at least once:78.26% of 46
No calls

Function 'shuffle'
Lines executed:100.00% of 18
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
No calls

Function 'playCard'
Lines executed:0.00% of 14
Branches executed:0.00% of 10
Taken at least once:0.00% of 10
No calls

Function 'buyCard'
Lines executed:0.00% of 13
Branches executed:0.00% of 6
Taken at least once:0.00% of 6
No calls

Function 'numHandCards'
Lines executed:0.00% of 1
No branches
No calls

Function 'handCard'
Lines executed:0.00% of 2
No branches
No calls

Function 'supplyCount'
Lines executed:0.00% of 1
No branches
No calls

Function 'fullDeckCount'
Lines executed:0.00% of 11
Branches executed:0.00% of 12
Taken at least once:0.00% of 12
No calls

Function 'whoseTurn'
Lines executed:100.00% of 1
No branches
No calls

Function 'endTurn'
Lines executed:0.00% of 22
Branches executed:0.00% of 6
Taken at least once:0.00% of 6
No calls

Function 'isGameOver'
Lines executed:100.00% of 12
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
No calls

Function 'scoreFor'
Lines executed:0.00% of 26
Branches executed:0.00% of 42
Taken at least once:0.00% of 42
No calls

Function 'getWinners'
Lines executed:0.00% of 33
Branches executed:0.00% of 22
Taken at least once:0.00% of 22
No calls

Function 'drawCard'
Lines executed:70.83% of 24
Branches executed:100.00% of 6
Taken at least once:66.67% of 6
No calls

Function 'getCost'
Lines executed:96.67% of 30
Branches executed:100.00% of 28
Taken at least once:96.43% of 28
No calls

Function 'smithy_card'
Lines executed:100.00% of 7
Branches executed:100.00% of 4
Taken at least once:100.00% of 4
No calls

Function 'adventurer_card'
Lines executed:61.90% of 21
Branches executed:71.43% of 14
Taken at least once:42.86% of 14
No calls

Function 'outpost_card'
Lines executed:0.00% of 4
No branches
No calls

Function 'remodel_card'
Lines executed:0.00% of 12
Branches executed:0.00% of 6
Taken at least once:0.00% of 6
No calls

Function 'village_card'
Lines executed:0.00% of 6
Branches executed:0.00% of 2
Taken at least once:0.00% of 2
No calls

Function 'cardEffect'
Lines executed:10.55% of 256
Branches executed:16.20% of 179
Taken at least once:6.70% of 179
No calls

Function 'discardCard'
Lines executed:86.67% of 15
Branches executed:100.00% of 6
Taken at least once:83.33% of 6
No calls

Function 'gainCard'
Lines executed:0.00% of 15
Branches executed:0.00% of 6
Taken at least once:0.00% of 6
No calls

Function 'updateCoins'
Lines executed:100.00% of 14
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
No calls

File 'dominion.c'
Lines executed:33.99% of 656
Branches executed:36.64% of 423
Taken at least once:28.61% of 423
No calls
dominion.c:creating 'dominion.c.gcov'
*/


/* FULL CONTENT OF dominion.c.gcov
        -:    0:Source:dominion.c
        -:    0:Graph:dominion.gcno
        -:    0:Data:dominion.gcda
        -:    0:Runs:8
        -:    0:Programs:1
        -:    1:#include "dominion.h"
        -:    2:#include "dominion_helpers.h"
        -:    3:#include "rngs.h"
        -:    4:#include <stdio.h>
        -:    5:#include <math.h>
        -:    6:#include <stdlib.h>
        -:    7:
        -:    8:int compare(const void* a, const void* b) {
     2184:    9:  if (*(int*)a > *(int*)b)
    #####:   10:    return 1;
     2184:   11:  if (*(int*)a < *(int*)b)
      780:   12:    return -1;
     1404:   13:  return 0;
     2184:   14:}
        -:   15:
        -:   16:struct gameState* newGame() {
    #####:   17:  struct gameState* g = malloc(sizeof(struct gameState));
    #####:   18:  return g;
        -:   19:}
        -:   20:
        -:   21:int* kingdomCards(int k1, int k2, int k3, int k4, int k5, int k6, int k7,
        -:   22:		  int k8, int k9, int k10) {
    #####:   23:  int* k = malloc(10 * sizeof(int));
    #####:   24:  k[0] = k1;
    #####:   25:  k[1] = k2;
    #####:   26:  k[2] = k3;
    #####:   27:  k[3] = k4;
    #####:   28:  k[4] = k5;
    #####:   29:  k[5] = k6;
    #####:   30:  k[6] = k7;
    #####:   31:  k[7] = k8;
    #####:   32:  k[8] = k9;
    #####:   33:  k[9] = k10;
    #####:   34:  return k;
        -:   35:}
        -:   36:
        -:   37:int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed,
        -:   38:		   struct gameState *state) {
        -:   39:
        -:   40:  int i;
        -:   41:  int j;
        -:   42:  int it;
        -:   43:  //set up random number generator
       78:   44:  SelectStream(1);
       78:   45:  PutSeed((long)randomSeed);
        -:   46:
        -:   47:  //check number of players
      156:   48:  if (numPlayers > MAX_PLAYERS || numPlayers < 2)
        -:   49:    {
    #####:   50:      return -1;
        -:   51:    }
        -:   52:
        -:   53:  //set number of players
       78:   54:  state->numPlayers = numPlayers;
        -:   55:
        -:   56:  //check selected kingdom cards are different
     1716:   57:  for (i = 0; i < 10; i++)
        -:   58:    {
    17160:   59:      for (j = 0; j < 10; j++)
        -:   60:        {
    14820:   61:	  if (j != i && kingdomCards[j] == kingdomCards[i])
        -:   62:	    {
    #####:   63:	      return -1;
        -:   64:	    }
     7800:   65:        }
      780:   66:    }
        -:   67:
        -:   68:
        -:   69:  //initialize supply
        -:   70:  ///////////////////////////////
        -:   71:
        -:   72:  //set number of Curse cards
       78:   73:  if (numPlayers == 2)
        -:   74:    {
       78:   75:      state->supplyCount[curse] = 10;
       78:   76:    }
    #####:   77:  else if (numPlayers == 3)
        -:   78:    {
    #####:   79:      state->supplyCount[curse] = 20;
    #####:   80:    }
        -:   81:  else
        -:   82:    {
    #####:   83:      state->supplyCount[curse] = 30;
        -:   84:    }
        -:   85:
        -:   86:  //set number of Victory cards
       78:   87:  if (numPlayers == 2)
        -:   88:    {
       78:   89:      state->supplyCount[estate] = 8;
       78:   90:      state->supplyCount[duchy] = 8;
       78:   91:      state->supplyCount[province] = 8;
       78:   92:    }
        -:   93:  else
        -:   94:    {
    #####:   95:      state->supplyCount[estate] = 12;
    #####:   96:      state->supplyCount[duchy] = 12;
    #####:   97:      state->supplyCount[province] = 12;
        -:   98:    }
        -:   99:
        -:  100:  //set number of Treasure cards
       78:  101:  state->supplyCount[copper] = 60 - (7 * numPlayers);
       78:  102:  state->supplyCount[silver] = 40;
       78:  103:  state->supplyCount[gold] = 30;
        -:  104:
        -:  105:  //set number of Kingdom cards
     3276:  106:  for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
        -:  107:    {
    25740:  108:      for (j = 0; j < 10; j++)           		//loop chosen cards
        -:  109:	{
    12090:  110:	  if (kingdomCards[j] == i)
        -:  111:	    {
        -:  112:	      //check if card is a 'Victory' Kingdom card
     1560:  113:	      if (kingdomCards[j] == great_hall || kingdomCards[j] == gardens)
        -:  114:		{
       78:  115:		  if (numPlayers == 2){
       78:  116:		    state->supplyCount[i] = 8;
       78:  117:		  }
    #####:  118:		  else{ state->supplyCount[i] = 12; }
       78:  119:		}
        -:  120:	      else
        -:  121:		{
      702:  122:		  state->supplyCount[i] = 10;
        -:  123:		}
      780:  124:	      break;
        -:  125:	    }
        -:  126:	  else    //card is not in the set choosen for the game
        -:  127:	    {
    11310:  128:	      state->supplyCount[i] = -1;
        -:  129:	    }
    11310:  130:	}
        -:  131:
     1560:  132:    }
        -:  133:
        -:  134:  ////////////////////////
        -:  135:  //supply intilization complete
        -:  136:
        -:  137:  //set player decks
      468:  138:  for (i = 0; i < numPlayers; i++)
        -:  139:    {
      156:  140:      state->deckCount[i] = 0;
     1248:  141:      for (j = 0; j < 3; j++)
        -:  142:	{
      468:  143:	  state->deck[i][j] = estate;
      468:  144:	  state->deckCount[i]++;
      468:  145:	}
     2496:  146:      for (j = 3; j < 10; j++)
        -:  147:	{
     1092:  148:	  state->deck[i][j] = copper;
     1092:  149:	  state->deckCount[i]++;
     1092:  150:	}
      156:  151:    }
        -:  152:
        -:  153:  //shuffle player decks
      468:  154:  for (i = 0; i < numPlayers; i++)
        -:  155:    {
      156:  156:      if ( shuffle(i, state) < 0 )
        -:  157:	{
    #####:  158:	  return -1;
        -:  159:	}
      156:  160:    }
        -:  161:
        -:  162:  //draw player hands
      468:  163:  for (i = 0; i < numPlayers; i++)
        -:  164:    {
        -:  165:      //initialize hand size to zero
      156:  166:      state->handCount[i] = 0;
      156:  167:      state->discardCount[i] = 0;
        -:  168:      //draw 5 cards
        -:  169:      // for (j = 0; j < 5; j++)
        -:  170:      //	{
        -:  171:      //	  drawCard(i, state);
        -:  172:      //	}
      156:  173:    }
        -:  174:
        -:  175:  //set embargo tokens to 0 for all supply piles
     4368:  176:  for (i = 0; i <= treasure_map; i++)
        -:  177:    {
     2106:  178:      state->embargoTokens[i] = 0;
     2106:  179:    }
        -:  180:
        -:  181:  //initialize first player's turn
       78:  182:  state->outpostPlayed = 0;
       78:  183:  state->phase = 0;
       78:  184:  state->numActions = 1;
       78:  185:  state->numBuys = 1;
       78:  186:  state->playedCardCount = 0;
       78:  187:  state->whoseTurn = 0;
       78:  188:  state->handCount[state->whoseTurn] = 0;
        -:  189:  //int it; move to top
        -:  190:
        -:  191:  //Moved draw cards to here, only drawing at the start of a turn
      936:  192:  for (it = 0; it < 5; it++){
      390:  193:    drawCard(state->whoseTurn, state);
      390:  194:  }
        -:  195:
       78:  196:  updateCoins(state->whoseTurn, state, 0);
        -:  197:
       78:  198:  return 0;
       78:  199:}
        -:  200:
        -:  201:int shuffle(int player, struct gameState *state) {
        -:  202:
        -:  203:
        -:  204:  int newDeck[MAX_DECK];
      158:  205:  int newDeckPos = 0;
        -:  206:  int card;
        -:  207:  int i;
        -:  208:
      158:  209:  if (state->deckCount[player] < 1)
        2:  210:    return -1;
      156:  211:  qsort ((void*)(state->deck[player]), state->deckCount[player], sizeof(int), compare);
        -:  212:   SORT CARDS IN DECK TO ENSURE DETERMINISM! 
        -:  213:
     3432:  214:  while (state->deckCount[player] > 0) {
     1560:  215:    card = floor(Random() * state->deckCount[player]);
     1560:  216:    newDeck[newDeckPos] = state->deck[player][card];
     1560:  217:    newDeckPos++;
     9672:  218:    for (i = card; i < state->deckCount[player]-1; i++) {
     3276:  219:      state->deck[player][i] = state->deck[player][i+1];
     3276:  220:    }
     1560:  221:    state->deckCount[player]--;
        -:  222:  }
     3432:  223:  for (i = 0; i < newDeckPos; i++) {
     1560:  224:    state->deck[player][i] = newDeck[i];
     1560:  225:    state->deckCount[player]++;
     1560:  226:  }
        -:  227:
      156:  228:  return 0;
      158:  229:}
        -:  230:
        -:  231:int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
        -:  232:{
        -:  233:  int card;
    #####:  234:  int coin_bonus = 0; 		//tracks coins gain from actions
        -:  235:
        -:  236:  //check if it is the right phase
    #####:  237:  if (state->phase != 0)
        -:  238:    {
    #####:  239:      return -1;
        -:  240:    }
        -:  241:
        -:  242:  //check if player has enough actions
    #####:  243:  if ( state->numActions < 1 )
        -:  244:    {
    #####:  245:      return -1;
        -:  246:    }
        -:  247:
        -:  248:  //get card played
    #####:  249:  card = handCard(handPos, state);
        -:  250:
        -:  251:  //check if selected card is an action
    #####:  252:  if ( card < adventurer || card > treasure_map )
        -:  253:    {
    #####:  254:      return -1;
        -:  255:    }
        -:  256:
        -:  257:  //play card
    #####:  258:  if ( cardEffect(card, choice1, choice2, choice3, state, handPos, &coin_bonus) < 0 )
        -:  259:    {
    #####:  260:      return -1;
        -:  261:    }
        -:  262:
        -:  263:  //reduce number of actions
    #####:  264:  state->numActions--;
        -:  265:
        -:  266:  //update coins (Treasure cards may be added with card draws)
    #####:  267:  updateCoins(state->whoseTurn, state, coin_bonus);
        -:  268:
    #####:  269:  return 0;
    #####:  270:}
        -:  271:
        -:  272:int buyCard(int supplyPos, struct gameState *state) {
        -:  273:  int who;
        -:  274:  if (DEBUG){
        -:  275:    printf("Entering buyCard...\n");
        -:  276:  }
        -:  277:
        -:  278:  // I don't know what to do about the phase thing.
        -:  279:
    #####:  280:  who = state->whoseTurn;
        -:  281:
    #####:  282:  if (state->numBuys < 1){
        -:  283:    if (DEBUG)
        -:  284:      printf("You do not have any buys left\n");
    #####:  285:    return -1;
    #####:  286:  } else if (supplyCount(supplyPos, state) <1){
        -:  287:    if (DEBUG)
        -:  288:      printf("There are not any of that type of card left\n");
    #####:  289:    return -1;
    #####:  290:  } else if (state->coins < getCost(supplyPos)){
        -:  291:    if (DEBUG)
        -:  292:      printf("You do not have enough money to buy that. You have %d coins.\n", state->coins);
    #####:  293:    return -1;
        -:  294:  } else {
    #####:  295:    state->phase=1;
        -:  296:    //state->supplyCount[supplyPos]--;
    #####:  297:    gainCard(supplyPos, state, 0, who); //card goes in discard, this might be wrong.. (2 means goes into hand, 0 goes into discard)
        -:  298:
    #####:  299:    state->coins = (state->coins) - (getCost(supplyPos));
    #####:  300:    state->numBuys--;
        -:  301:    if (DEBUG)
        -:  302:      printf("You bought card number %d for %d coins. You now have %d buys and %d coins.\n", supplyPos, getCost(supplyPos), state->numBuys, state->coins);
        -:  303:  }
        -:  304:
        -:  305:  //state->discard[who][state->discardCount[who]] = supplyPos;
        -:  306:  //state->discardCount[who]++;
        -:  307:
    #####:  308:  return 0;
    #####:  309:}
        -:  310:
        -:  311:int numHandCards(struct gameState *state) {
    #####:  312:  return state->handCount[ whoseTurn(state) ];
        -:  313:}
        -:  314:
        -:  315:int handCard(int handPos, struct gameState *state) {
    #####:  316:  int currentPlayer = whoseTurn(state);
    #####:  317:  return state->hand[currentPlayer][handPos];
        -:  318:}
        -:  319:
        -:  320:int supplyCount(int card, struct gameState *state) {
    #####:  321:  return state->supplyCount[card];
        -:  322:}
        -:  323:
        -:  324:int fullDeckCount(int player, int card, struct gameState *state) {
        -:  325:  int i;
    #####:  326:  int count = 0;
        -:  327:
    #####:  328:  for (i = 0; i < state->deckCount[player]; i++)
        -:  329:    {
    #####:  330:      if (state->deck[player][i] == card) count++;
    #####:  331:    }
        -:  332:
    #####:  333:  for (i = 0; i < state->handCount[player]; i++)
        -:  334:    {
    #####:  335:      if (state->hand[player][i] == card) count++;
    #####:  336:    }
        -:  337:
    #####:  338:  for (i = 0; i < state->discardCount[player]; i++)
        -:  339:    {
    #####:  340:      if (state->discard[player][i] == card) count++;
    #####:  341:    }
        -:  342:
    #####:  343:  return count;
        -:  344:}
        -:  345:
        -:  346:int whoseTurn(struct gameState *state) {
       17:  347:  return state->whoseTurn;
        -:  348:}
        -:  349:
        -:  350:int endTurn(struct gameState *state) {
        -:  351:  int k;
        -:  352:  int i;
    #####:  353:  int currentPlayer = whoseTurn(state);
        -:  354:
        -:  355:  //Discard hand
    #####:  356:  for (i = 0; i < state->handCount[currentPlayer]; i++){
    #####:  357:    state->discard[currentPlayer][state->discardCount[currentPlayer]++] = state->hand[currentPlayer][i];//Discard
    #####:  358:    state->hand[currentPlayer][i] = -1;//Set card to -1
    #####:  359:  }
    #####:  360:  state->handCount[currentPlayer] = 0;//Reset hand count
        -:  361:
        -:  362:  //Code for determining the player
    #####:  363:  if (currentPlayer < (state->numPlayers - 1)){
    #####:  364:    state->whoseTurn = currentPlayer + 1;//Still safe to increment
    #####:  365:  }
        -:  366:  else{
    #####:  367:    state->whoseTurn = 0;//Max player has been reached, loop back around to player 1
        -:  368:  }
        -:  369:
    #####:  370:  state->outpostPlayed = 0;
    #####:  371:  state->phase = 0;
    #####:  372:  state->numActions = 1;
    #####:  373:  state->coins = 0;
    #####:  374:  state->numBuys = 1;
    #####:  375:  state->playedCardCount = 0;
    #####:  376:  state->handCount[state->whoseTurn] = 0;
        -:  377:
        -:  378:  //int k; move to top
        -:  379:  //Next player draws hand
    #####:  380:  for (k = 0; k < 5; k++){
    #####:  381:    drawCard(state->whoseTurn, state);//Draw a card
    #####:  382:  }
        -:  383:
        -:  384:  //Update money
    #####:  385:  updateCoins(state->whoseTurn, state , 0);
        -:  386:
    #####:  387:  return 0;
        -:  388:}
        -:  389:
        -:  390:int isGameOver(struct gameState *state) {
        -:  391:  int i;
        -:  392:  int j;
        -:  393:
        -:  394:  //if stack of Province cards is empty, the game ends
        7:  395:  if (state->supplyCount[province] == 0)
        -:  396:    {
        3:  397:      return 1;
        -:  398:    }
        -:  399:
        -:  400:  //if three supply pile are at 0, the game ends
        4:  401:  j = 0;
      208:  402:  for (i = 0; i < 25; i++)
        -:  403:    {
      100:  404:      if (state->supplyCount[i] == 0)
        -:  405:	{
        5:  406:	  j++;
        5:  407:	}
      100:  408:    }
        4:  409:  if ( j >= 3)
        -:  410:    {
        1:  411:      return 1;
        -:  412:    }
        -:  413:
        3:  414:  return 0;
        7:  415:}
        -:  416:
        -:  417:int scoreFor (int player, struct gameState *state) {
        -:  418:
        -:  419:  int i;
    #####:  420:  int score = 0;
        -:  421:  //score from hand
    #####:  422:  for (i = 0; i < state->handCount[player]; i++)
        -:  423:    {
    #####:  424:      if (state->hand[player][i] == curse) { score = score - 1; };
    #####:  425:      if (state->hand[player][i] == estate) { score = score + 1; };
    #####:  426:      if (state->hand[player][i] == duchy) { score = score + 3; };
    #####:  427:      if (state->hand[player][i] == province) { score = score + 6; };
    #####:  428:      if (state->hand[player][i] == great_hall) { score = score + 1; };
    #####:  429:      if (state->hand[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    #####:  430:    }
        -:  431:
        -:  432:  //score from discard
    #####:  433:  for (i = 0; i < state->discardCount[player]; i++)
        -:  434:    {
    #####:  435:      if (state->discard[player][i] == curse) { score = score - 1; };
    #####:  436:      if (state->discard[player][i] == estate) { score = score + 1; };
    #####:  437:      if (state->discard[player][i] == duchy) { score = score + 3; };
    #####:  438:      if (state->discard[player][i] == province) { score = score + 6; };
    #####:  439:      if (state->discard[player][i] == great_hall) { score = score + 1; };
    #####:  440:      if (state->discard[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    #####:  441:    }
        -:  442:
        -:  443:  //score from deck
    #####:  444:  for (i = 0; i < state->discardCount[player]; i++)
        -:  445:    {
    #####:  446:      if (state->deck[player][i] == curse) { score = score - 1; };
    #####:  447:      if (state->deck[player][i] == estate) { score = score + 1; };
    #####:  448:      if (state->deck[player][i] == duchy) { score = score + 3; };
    #####:  449:      if (state->deck[player][i] == province) { score = score + 6; };
    #####:  450:      if (state->deck[player][i] == great_hall) { score = score + 1; };
    #####:  451:      if (state->deck[player][i] == gardens) { score = score + ( fullDeckCount(player, 0, state) / 10 ); };
    #####:  452:    }
        -:  453:
    #####:  454:  return score;
        -:  455:}
        -:  456:
        -:  457:int getWinners(int players[MAX_PLAYERS], struct gameState *state) {
        -:  458:  int i;
        -:  459:  int j;
        -:  460:  int highScore;
        -:  461:  int currentPlayer;
        -:  462:
        -:  463:  //get score for each player
    #####:  464:  for (i = 0; i < MAX_PLAYERS; i++)
        -:  465:    {
        -:  466:      //set unused player scores to -9999
    #####:  467:      if (i >= state->numPlayers)
        -:  468:	{
    #####:  469:	  players[i] = -9999;
    #####:  470:	}
        -:  471:      else
        -:  472:	{
    #####:  473:	  players[i] = scoreFor (i, state);
        -:  474:	}
    #####:  475:    }
        -:  476:
        -:  477:  //find highest score
    #####:  478:  j = 0;
    #####:  479:  for (i = 0; i < MAX_PLAYERS; i++)
        -:  480:    {
    #####:  481:      if (players[i] > players[j])
        -:  482:	{
    #####:  483:	  j = i;
    #####:  484:	}
    #####:  485:    }
    #####:  486:  highScore = players[j];
        -:  487:
        -:  488:  //add 1 to players who had less turns
    #####:  489:  currentPlayer = whoseTurn(state);
    #####:  490:  for (i = 0; i < MAX_PLAYERS; i++)
        -:  491:    {
    #####:  492:      if ( players[i] == highScore && i > currentPlayer )
        -:  493:	{
    #####:  494:	  players[i]++;
    #####:  495:	}
    #####:  496:    }
        -:  497:
        -:  498:  //find new highest score
    #####:  499:  j = 0;
    #####:  500:  for (i = 0; i < MAX_PLAYERS; i++)
        -:  501:    {
    #####:  502:      if ( players[i] > players[j] )
        -:  503:	{
    #####:  504:	  j = i;
    #####:  505:	}
    #####:  506:    }
    #####:  507:  highScore = players[j];
        -:  508:
        -:  509:  //set winners in array to 1 and rest to 0
    #####:  510:  for (i = 0; i < MAX_PLAYERS; i++)
        -:  511:    {
    #####:  512:      if ( players[i] == highScore )
        -:  513:	{
    #####:  514:	  players[i] = 1;
    #####:  515:	}
        -:  516:      else
        -:  517:	{
    #####:  518:	  players[i] = 0;
        -:  519:	}
    #####:  520:    }
        -:  521:
    #####:  522:  return 0;
        -:  523:}
        -:  524:
        -:  525:int drawCard(int player, struct gameState *state)
        -:  526:{	int count;
        -:  527:  int deckCounter;
      429:  528:  if (state->deckCount[player] <= 0){//Deck is empty
        -:  529:
        -:  530:    //Step 1 Shuffle the discard pile back into a deck
        -:  531:    int i;
        -:  532:    //Move discard to deck
        2:  533:    for (i = 0; i < state->discardCount[player];i++){
    #####:  534:      state->deck[player][i] = state->discard[player][i];
    #####:  535:      state->discard[player][i] = -1;
    #####:  536:    }
        -:  537:
        1:  538:    state->deckCount[player] = state->discardCount[player];
        1:  539:    state->discardCount[player] = 0;//Reset discard
        -:  540:
        -:  541:    //Shufffle the deck
        1:  542:    shuffle(player, state);//Shuffle the deck up and make it so that we can draw
        -:  543:
        -:  544:    if (DEBUG){//Debug statements
        -:  545:      printf("Deck count now: %d\n", state->deckCount[player]);
        -:  546:    }
        -:  547:
        1:  548:    state->discardCount[player] = 0;
        -:  549:
        -:  550:    //Step 2 Draw Card
        1:  551:    count = state->handCount[player];//Get current player's hand count
        -:  552:
        -:  553:    if (DEBUG){//Debug statements
        -:  554:      printf("Current hand count: %d\n", count);
        -:  555:    }
        -:  556:
        1:  557:    deckCounter = state->deckCount[player];//Create a holder for the deck count
        -:  558:
        1:  559:    if (deckCounter == 0)
        1:  560:      return -1;
        -:  561:
    #####:  562:    state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to hand
    #####:  563:    state->deckCount[player]--;
    #####:  564:    state->handCount[player]++;//Increment hand count
    #####:  565:  }
        -:  566:
        -:  567:  else{
      428:  568:    int count = state->handCount[player];//Get current hand count for player
        -:  569:    int deckCounter;
        -:  570:    if (DEBUG){//Debug statements
        -:  571:      printf("Current hand count: %d\n", count);
        -:  572:    }
        -:  573:
      428:  574:    deckCounter = state->deckCount[player];//Create holder for the deck count
      428:  575:    state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to the hand
      428:  576:    state->deckCount[player]--;
      428:  577:    state->handCount[player]++;//Increment hand count
        -:  578:  }
        -:  579:
      428:  580:  return 0;
      429:  581:}
        -:  582:
        -:  583:int getCost(int cardNumber)
        -:  584:{
       28:  585:  switch( cardNumber )
        -:  586:    {
        -:  587:    case curse:
        1:  588:      return 0;
        -:  589:    case estate:
        1:  590:      return 2;
        -:  591:    case duchy:
        1:  592:      return 5;
        -:  593:    case province:
        1:  594:      return 8;
        -:  595:    case copper:
        1:  596:      return 0;
        -:  597:    case silver:
        1:  598:      return 3;
        -:  599:    case gold:
        1:  600:      return 6;
        -:  601:    case adventurer:
        1:  602:      return 6;
        -:  603:    case council_room:
        1:  604:      return 5;
        -:  605:    case feast:
        1:  606:      return 4;
        -:  607:    case gardens:
        1:  608:      return 4;
        -:  609:    case mine:
        1:  610:      return 5;
        -:  611:    case remodel:
        1:  612:      return 4;
        -:  613:    case smithy:
        1:  614:      return 4;
        -:  615:    case village:
        1:  616:      return 3;
        -:  617:    case baron:
        1:  618:      return 4;
        -:  619:    case great_hall:
        1:  620:      return 3;
        -:  621:    case minion:
        1:  622:      return 5;
        -:  623:    case steward:
        1:  624:      return 3;
        -:  625:    case tribute:
        2:  626:      return 5;
        -:  627:    case ambassador:
        1:  628:      return 3;
        -:  629:    case cutpurse:
        1:  630:      return 4;
        -:  631:    case embargo:
        1:  632:      return 2;
        -:  633:    case outpost:
        1:  634:      return 5;
        -:  635:    case salvager:
        1:  636:      return 4;
        -:  637:    case sea_hag:
        1:  638:      return 4;
        -:  639:    case treasure_map:
        1:  640:      return 4;
        -:  641:    }
        -:  642:
    #####:  643:  return -1;
       28:  644:}
        -:  645://*********************************
        -:  646:// Cards from refactor.c with bugs
        -:  647://*********************************
        -:  648:// Refactored smithy card
        -:  649:int smithy_card(int handPos, int currentPlayer, struct gameState *state) {
        -:  650:    int i;
        -:  651:    // +3 Cards
       80:  652:    for (i = 0; i < 3; i++) {
       30:  653:        if (handPos != 2) { // bug - this condition shouldn't be here
       24:  654:            drawCard(currentPlayer, state);
       24:  655:        }
       30:  656:    }
        -:  657:
        -:  658:    //discard card from hand
       10:  659:    discardCard(handPos, currentPlayer, state, 0);
       10:  660:    return 0;
        -:  661:}
        -:  662:
        -:  663:
        -:  664:// Refactored adventure card
        -:  665:int adventurer_card(int handPos, int z, int temphand[], int drawntreasure, int currentPlayer, int cardDrawn, struct gameState *state) {
        6:  666:    while (drawntreasure < 2) {
        3:  667:        if (state->deckCount[currentPlayer] < 1) {
        1:  668:            shuffle(currentPlayer, state);
        1:  669:        }
        3:  670:        drawCard(currentPlayer, state);
        3:  671:        if (drawntreasure == 1) {
        -:  672:            // BUG: draw two extra cards if drawntreasure == 1.  Could potentiall result in drawing
        -:  673:            // more than two treasure cards.
    #####:  674:            drawCard(currentPlayer, state);
    #####:  675:            drawCard(currentPlayer, state);
    #####:  676:        }
        3:  677:        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];
        3:  678:        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) {
        3:  679:            drawntreasure++;
        3:  680:        } else {
    #####:  681:            temphand[z] = cardDrawn;
    #####:  682:            state->handCount[currentPlayer]--;
    #####:  683:            z++;
        -:  684:        }
        6:  685:        while (z-1>=0) {
    #####:  686:            state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z-1];
    #####:  687:            z = z -1;
        -:  688:        }
        3:  689:        return 0;
        -:  690:    }
        3:  691:}
        -:  692:
        -:  693:// Refactored outpost card
        -:  694:int outpost_card(int handPos, int currentPlayer, struct gameState *state) {
        -:  695:    // set outpost flag
    #####:  696:    state->outpostPlayed++;
        -:  697:
    #####:  698:    state->handCount[currentPlayer]++;
        -:  699:
        -:  700:    // discard card
    #####:  701:    discardCard(handPos, currentPlayer, state, 0);
    #####:  702:    return 0;
        -:  703:}
        -:  704:
        -:  705:// Refactored remodel card
        -:  706:int remodel_card(int handPos, int currentPlayer, int choice1, int choice2, struct gameState *state) {
        -:  707:    int i, j;
        -:  708:    // store card we will trash
    #####:  709:    j = state->hand[currentPlayer][choice1];
        -:  710:
    #####:  711:    if ( (getCost(state->hand[currentPlayer][choice2]) + 2) > getCost(choice1) ) {
    #####:  712:        return -1;
        -:  713:    }
        -:  714:
    #####:  715:    gainCard(choice2, state, 0, currentPlayer);
        -:  716:
        -:  717:    // discard card from hand
    #####:  718:    discardCard(handPos, currentPlayer, state, 0);
        -:  719:
        -:  720:    //discard trashed card
    #####:  721:    for (i = 0; i < state->handCount[currentPlayer]; i++) {
    #####:  722:        if (state->hand[currentPlayer][i] == j) {
    #####:  723:            discardCard(i, currentPlayer, state, 0);
    #####:  724:            break;
        -:  725:        }
    #####:  726:    }
        -:  727:
    #####:  728:    return 0;
    #####:  729:}
        -:  730:
        -:  731:// Refactored village card
        -:  732:int village_card(int handPos, int currentPlayer, struct gameState *state) {
        -:  733:    // +1 card
    #####:  734:    drawCard(currentPlayer,state);
        -:  735:
        -:  736:    // +2 actions
    #####:  737:    state->numActions = state->numActions + 2;
        -:  738:
        -:  739:    // discard played card from hand
    #####:  740:    if (state->numActions > 3) {
    #####:  741:        discardCard(handPos, currentPlayer, state, 0);
    #####:  742:    }
    #####:  743:    return 0;
        -:  744:}
        -:  745:
        -:  746:int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
        -:  747:{
        -:  748:  int i;
        -:  749:  int j;
        -:  750:  int k;
        -:  751:  int x;
        -:  752:  int index;
       17:  753:  int currentPlayer = whoseTurn(state);
       17:  754:  int nextPlayer = currentPlayer + 1;
        -:  755:
       17:  756:  int tributeRevealedCards[2] = {-1, -1};
        -:  757:  int temphand[MAX_HAND];// moved above the if statement
       17:  758:  int drawntreasure=0;
        -:  759:  int cardDrawn;
       17:  760:  int z = 0;// this is the counter for the temp hand
       17:  761:  if (nextPlayer > (state->numPlayers - 1)){
        8:  762:    nextPlayer = 0;
        8:  763:  }
        -:  764:
        -:  765:
        -:  766:  //uses switch to select card and perform actions
       17:  767:  switch( card )
        -:  768:    {
        -:  769:    case adventurer:
        3:  770:        return adventurer_card(handPos, z, temphand, drawntreasure, currentPlayer, cardDrawn, state);
        -:  771:
        -:  772:    case council_room:
        -:  773:      //+4 Cards
       20:  774:      for (i = 0; i < 4; i++)
        -:  775:	{
        8:  776:	  drawCard(currentPlayer, state);
        8:  777:	}
        -:  778:
        -:  779:      //+1 Buy
        2:  780:      state->numBuys++;
        -:  781:
        -:  782:      //Each other player draws a card
       12:  783:      for (i = 0; i < state->numPlayers; i++)
        -:  784:	{
        4:  785:	  if ( i != currentPlayer )
        -:  786:	    {
        2:  787:	      drawCard(i, state);
        2:  788:	    }
        4:  789:	}
        -:  790:
        -:  791:      //put played card in played card pile
        2:  792:      discardCard(handPos, currentPlayer, state, 0);
        -:  793:
        2:  794:      return 0;
        -:  795:
        -:  796:    case feast:
        -:  797:      //gain card with cost up to 5
        -:  798:      //Backup hand
    #####:  799:      for (i = 0; i <= state->handCount[currentPlayer]; i++){
    #####:  800:	temphand[i] = state->hand[currentPlayer][i];//Backup card
    #####:  801:	state->hand[currentPlayer][i] = -1;//Set to nothing
    #####:  802:      }
        -:  803:      //Backup hand
        -:  804:
        -:  805:      //Update Coins for Buy
    #####:  806:      updateCoins(currentPlayer, state, 5);
    #####:  807:      x = 1;//Condition to loop on
    #####:  808:      while( x == 1) {//Buy one card
    #####:  809:	if (supplyCount(choice1, state) <= 0){
        -:  810:	  if (DEBUG)
        -:  811:	    printf("None of that card left, sorry!\n");
        -:  812:
        -:  813:	  if (DEBUG){
        -:  814:	    printf("Cards Left: %d\n", supplyCount(choice1, state));
        -:  815:	  }
    #####:  816:	}
    #####:  817:	else if (state->coins < getCost(choice1)){
    #####:  818:	  printf("That card is too expensive!\n");
        -:  819:
        -:  820:	  if (DEBUG){
        -:  821:	    printf("Coins: %d < %d\n", state->coins, getCost(choice1));
        -:  822:	  }
    #####:  823:	}
        -:  824:	else{
        -:  825:
        -:  826:	  if (DEBUG){
        -:  827:	    printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
        -:  828:	  }
        -:  829:
    #####:  830:	  gainCard(choice1, state, 0, currentPlayer);//Gain the card
    #####:  831:	  x = 0;//No more buying cards
        -:  832:
        -:  833:	  if (DEBUG){
        -:  834:	    printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
        -:  835:	  }
        -:  836:
        -:  837:	}
        -:  838:      }
        -:  839:
        -:  840:      //Reset Hand
    #####:  841:      for (i = 0; i <= state->handCount[currentPlayer]; i++){
    #####:  842:	state->hand[currentPlayer][i] = temphand[i];
    #####:  843:	temphand[i] = -1;
    #####:  844:      }
        -:  845:      //Reset Hand
        -:  846:
    #####:  847:      return 0;
        -:  848:
        -:  849:    case gardens:
    #####:  850:      return -1;
        -:  851:
        -:  852:    case mine:
    #####:  853:      j = state->hand[currentPlayer][choice1];  //store card we will trash
        -:  854:
    #####:  855:      if (state->hand[currentPlayer][choice1] < copper || state->hand[currentPlayer][choice1] > gold)
        -:  856:	{
    #####:  857:	  return -1;
        -:  858:	}
        -:  859:
    #####:  860:      if (choice2 > treasure_map || choice2 < curse)
        -:  861:	{
    #####:  862:	  return -1;
        -:  863:	}
        -:  864:
    #####:  865:      if ( (getCost(state->hand[currentPlayer][choice1]) + 3) > getCost(choice2) )
        -:  866:	{
    #####:  867:	  return -1;
        -:  868:	}
        -:  869:
    #####:  870:      gainCard(choice2, state, 2, currentPlayer);
        -:  871:
        -:  872:      //discard card from hand
    #####:  873:      discardCard(handPos, currentPlayer, state, 0);
        -:  874:
        -:  875:      //discard trashed card
    #####:  876:      for (i = 0; i < state->handCount[currentPlayer]; i++)
        -:  877:	{
    #####:  878:	  if (state->hand[currentPlayer][i] == j)
        -:  879:	    {
    #####:  880:	      discardCard(i, currentPlayer, state, 0);
    #####:  881:	      break;
        -:  882:	    }
    #####:  883:	}
        -:  884:
    #####:  885:      return 0;
        -:  886:
        -:  887:    case remodel:
    #####:  888:        return remodel_card(handPos, currentPlayer, choice1, choice2, state);
        -:  889:
        -:  890:    case smithy:
       10:  891:        return smithy_card(handPos, currentPlayer, state);
        -:  892:
        -:  893:
        -:  894:    case village:
    #####:  895:        return village_card(handPos, currentPlayer, state);
        -:  896:
        -:  897:    case baron:
    #####:  898:      state->numBuys++;//Increase buys by 1!
    #####:  899:      if (choice1 > 0){//Boolean true or going to discard an estate
    #####:  900:	int p = 0;//Iterator for hand!
    #####:  901:	int card_not_discarded = 1;//Flag for discard set!
    #####:  902:	while(card_not_discarded){
    #####:  903:	  if (state->hand[currentPlayer][p] == estate){//Found an estate card!
    #####:  904:	    state->coins += 4;//Add 4 coins to the amount of coins
    #####:  905:	    state->discard[currentPlayer][state->discardCount[currentPlayer]] = state->hand[currentPlayer][p];
    #####:  906:	    state->discardCount[currentPlayer]++;
    #####:  907:	    for (;p < state->handCount[currentPlayer]; p++){
    #####:  908:	      state->hand[currentPlayer][p] = state->hand[currentPlayer][p+1];
    #####:  909:	    }
    #####:  910:	    state->hand[currentPlayer][state->handCount[currentPlayer]] = -1;
    #####:  911:	    state->handCount[currentPlayer]--;
    #####:  912:	    card_not_discarded = 0;//Exit the loop
    #####:  913:	  }
    #####:  914:	  else if (p > state->handCount[currentPlayer]){
        -:  915:	    if(DEBUG) {
        -:  916:	      printf("No estate cards in your hand, invalid choice\n");
        -:  917:	      printf("Must gain an estate if there are any\n");
        -:  918:	    }
    #####:  919:	    if (supplyCount(estate, state) > 0){
    #####:  920:	      gainCard(estate, state, 0, currentPlayer);
    #####:  921:	      state->supplyCount[estate]--;//Decrement estates
    #####:  922:	      if (supplyCount(estate, state) == 0){
    #####:  923:		isGameOver(state);
    #####:  924:	      }
    #####:  925:	    }
    #####:  926:	    card_not_discarded = 0;//Exit the loop
    #####:  927:	  }
        -:  928:
        -:  929:	  else{
    #####:  930:	    p++;//Next card
        -:  931:	  }
        -:  932:	}
    #####:  933:      }
        -:  934:
        -:  935:      else{
    #####:  936:	if (supplyCount(estate, state) > 0){
    #####:  937:	  gainCard(estate, state, 0, currentPlayer);//Gain an estate
    #####:  938:	  state->supplyCount[estate]--;//Decrement Estates
    #####:  939:	  if (supplyCount(estate, state) == 0){
    #####:  940:	    isGameOver(state);
    #####:  941:	  }
    #####:  942:	}
        -:  943:      }
        -:  944:
        -:  945:
    #####:  946:      return 0;
        -:  947:
        -:  948:    case great_hall:
        -:  949:      //+1 Card
        2:  950:      drawCard(currentPlayer, state);
        -:  951:
        -:  952:      //+1 Actions
        2:  953:      state->numActions++;
        -:  954:
        -:  955:      //discard card from hand
        2:  956:      discardCard(handPos, currentPlayer, state, 0);
        2:  957:      return 0;
        -:  958:
        -:  959:    case minion:
        -:  960:      //+1 action
    #####:  961:      state->numActions++;
        -:  962:
        -:  963:      //discard card from hand
    #####:  964:      discardCard(handPos, currentPlayer, state, 0);
        -:  965:
    #####:  966:      if (choice1)		//+2 coins
        -:  967:	{
    #####:  968:	  state->coins = state->coins + 2;
    #####:  969:	}
        -:  970:
    #####:  971:      else if (choice2)		//discard hand, redraw 4, other players with 5+ cards discard hand and draw 4
        -:  972:	{
        -:  973:	  //discard hand
    #####:  974:	  while(numHandCards(state) > 0)
        -:  975:	    {
    #####:  976:	      discardCard(handPos, currentPlayer, state, 0);
        -:  977:	    }
        -:  978:
        -:  979:	  //draw 4
    #####:  980:	  for (i = 0; i < 4; i++)
        -:  981:	    {
    #####:  982:	      drawCard(currentPlayer, state);
    #####:  983:	    }
        -:  984:
        -:  985:	  //other players discard hand and redraw if hand size > 4
    #####:  986:	  for (i = 0; i < state->numPlayers; i++)
        -:  987:	    {
    #####:  988:	      if (i != currentPlayer)
        -:  989:		{
    #####:  990:		  if ( state->handCount[i] > 4 )
        -:  991:		    {
        -:  992:		      //discard hand
    #####:  993:		      while( state->handCount[i] > 0 )
        -:  994:			{
    #####:  995:			  discardCard(handPos, i, state, 0);
        -:  996:			}
        -:  997:
        -:  998:		      //draw 4
    #####:  999:		      for (j = 0; j < 4; j++)
        -: 1000:			{
    #####: 1001:			  drawCard(i, state);
    #####: 1002:			}
    #####: 1003:		    }
    #####: 1004:		}
    #####: 1005:	    }
        -: 1006:
    #####: 1007:	}
    #####: 1008:      return 0;
        -: 1009:
        -: 1010:    case steward:
    #####: 1011:      if (choice1 == 1)
        -: 1012:	{
        -: 1013:	  //+2 cards
    #####: 1014:	  drawCard(currentPlayer, state);
    #####: 1015:	  drawCard(currentPlayer, state);
    #####: 1016:	}
    #####: 1017:      else if (choice1 == 2)
        -: 1018:	{
        -: 1019:	  //+2 coins
    #####: 1020:	  state->coins = state->coins + 2;
    #####: 1021:	}
        -: 1022:      else
        -: 1023:	{
        -: 1024:	  //trash 2 cards in hand
    #####: 1025:	  discardCard(choice2, currentPlayer, state, 1);
    #####: 1026:	  discardCard(choice3, currentPlayer, state, 1);
        -: 1027:	}
        -: 1028:
        -: 1029:      //discard card from hand
    #####: 1030:      discardCard(handPos, currentPlayer, state, 0);
    #####: 1031:      return 0;
        -: 1032:
        -: 1033:    case tribute:
    #####: 1034:      if ((state->discardCount[nextPlayer] + state->deckCount[nextPlayer]) <= 1){
    #####: 1035:	if (state->deckCount[nextPlayer] > 0){
    #####: 1036:	  tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
    #####: 1037:	  state->deckCount[nextPlayer]--;
    #####: 1038:	}
    #####: 1039:	else if (state->discardCount[nextPlayer] > 0){
    #####: 1040:	  tributeRevealedCards[0] = state->discard[nextPlayer][state->discardCount[nextPlayer]-1];
    #####: 1041:	  state->discardCount[nextPlayer]--;
    #####: 1042:	}
        -: 1043:	else{
        -: 1044:	  //No Card to Reveal
        -: 1045:	  if (DEBUG){
        -: 1046:	    printf("No cards to reveal\n");
        -: 1047:	  }
        -: 1048:	}
    #####: 1049:      }
        -: 1050:
        -: 1051:      else{
    #####: 1052:	if (state->deckCount[nextPlayer] == 0){
    #####: 1053:	  for (i = 0; i < state->discardCount[nextPlayer]; i++){
    #####: 1054:	    state->deck[nextPlayer][i] = state->discard[nextPlayer][i];//Move to deck
    #####: 1055:	    state->deckCount[nextPlayer]++;
    #####: 1056:	    state->discard[nextPlayer][i] = -1;
    #####: 1057:	    state->discardCount[nextPlayer]--;
    #####: 1058:	  }
        -: 1059:
    #####: 1060:	  shuffle(nextPlayer,state);//Shuffle the deck
    #####: 1061:	}
    #####: 1062:	tributeRevealedCards[0] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
    #####: 1063:	state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
    #####: 1064:	state->deckCount[nextPlayer]--;
    #####: 1065:	tributeRevealedCards[1] = state->deck[nextPlayer][state->deckCount[nextPlayer]-1];
    #####: 1066:	state->deck[nextPlayer][state->deckCount[nextPlayer]--] = -1;
    #####: 1067:	state->deckCount[nextPlayer]--;
        -: 1068:      }
        -: 1069:
    #####: 1070:      if (tributeRevealedCards[0] == tributeRevealedCards[1]){//If we have a duplicate card, just drop one
    #####: 1071:	state->playedCards[state->playedCardCount] = tributeRevealedCards[1];
    #####: 1072:	state->playedCardCount++;
    #####: 1073:	tributeRevealedCards[1] = -1;
    #####: 1074:      }
        -: 1075:
    #####: 1076:      for (i = 0; i <= 2; i ++){
    #####: 1077:	if (tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold){//Treasure cards
    #####: 1078:	  state->coins += 2;
    #####: 1079:	}
        -: 1080:
    #####: 1081:	else if (tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall){//Victory Card Found
    #####: 1082:	  drawCard(currentPlayer, state);
    #####: 1083:	  drawCard(currentPlayer, state);
    #####: 1084:	}
        -: 1085:	else{//Action Card
    #####: 1086:	  state->numActions = state->numActions + 2;
        -: 1087:	}
    #####: 1088:      }
        -: 1089:
    #####: 1090:      return 0;
        -: 1091:
        -: 1092:    case ambassador:
    #####: 1093:      j = 0;		//used to check if player has enough cards to discard
        -: 1094:
    #####: 1095:      if (choice2 > 2 || choice2 < 0)
        -: 1096:	{
    #####: 1097:	  return -1;
        -: 1098:	}
        -: 1099:
    #####: 1100:      if (choice1 == handPos)
        -: 1101:	{
    #####: 1102:	  return -1;
        -: 1103:	}
        -: 1104:
    #####: 1105:      for (i = 0; i < state->handCount[currentPlayer]; i++)
        -: 1106:	{
    #####: 1107:	  if (i != handPos && i == state->hand[currentPlayer][choice1] && i != choice1)
        -: 1108:	    {
    #####: 1109:	      j++;
    #####: 1110:	    }
    #####: 1111:	}
    #####: 1112:      if (j < choice2)
        -: 1113:	{
    #####: 1114:	  return -1;
        -: 1115:	}
        -: 1116:
        -: 1117:      if (DEBUG)
        -: 1118:	printf("Player %d reveals card number: %d\n", currentPlayer, state->hand[currentPlayer][choice1]);
        -: 1119:
        -: 1120:      //increase supply count for choosen card by amount being discarded
    #####: 1121:      state->supplyCount[state->hand[currentPlayer][choice1]] += choice2;
        -: 1122:
        -: 1123:      //each other player gains a copy of revealed card
    #####: 1124:      for (i = 0; i < state->numPlayers; i++)
        -: 1125:	{
    #####: 1126:	  if (i != currentPlayer)
        -: 1127:	    {
    #####: 1128:	      gainCard(state->hand[currentPlayer][choice1], state, 0, i);
    #####: 1129:	    }
    #####: 1130:	}
        -: 1131:
        -: 1132:      //discard played card from hand
    #####: 1133:      discardCard(handPos, currentPlayer, state, 0);
        -: 1134:
        -: 1135:      //trash copies of cards returned to supply
    #####: 1136:      for (j = 0; j < choice2; j++)
        -: 1137:	{
    #####: 1138:	  for (i = 0; i < state->handCount[currentPlayer]; i++)
        -: 1139:	    {
    #####: 1140:	      if (state->hand[currentPlayer][i] == state->hand[currentPlayer][choice1])
        -: 1141:		{
    #####: 1142:		  discardCard(i, currentPlayer, state, 1);
    #####: 1143:		  break;
        -: 1144:		}
    #####: 1145:	    }
    #####: 1146:	}
        -: 1147:
    #####: 1148:      return 0;
        -: 1149:
        -: 1150:    case cutpurse:
        -: 1151:
    #####: 1152:      updateCoins(currentPlayer, state, 2);
    #####: 1153:      for (i = 0; i < state->numPlayers; i++)
        -: 1154:	{
    #####: 1155:	  if (i != currentPlayer)
        -: 1156:	    {
    #####: 1157:	      for (j = 0; j < state->handCount[i]; j++)
        -: 1158:		{
    #####: 1159:		  if (state->hand[i][j] == copper)
        -: 1160:		    {
    #####: 1161:		      discardCard(j, i, state, 0);
    #####: 1162:		      break;
        -: 1163:		    }
    #####: 1164:		  if (j == state->handCount[i])
        -: 1165:		    {
    #####: 1166:		      for (k = 0; k < state->handCount[i]; k++)
        -: 1167:			{
        -: 1168:			  if (DEBUG)
        -: 1169:			    printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
    #####: 1170:			}
    #####: 1171:		      break;
        -: 1172:		    }
    #####: 1173:		}
        -: 1174:
    #####: 1175:	    }
        -: 1176:
    #####: 1177:	}
        -: 1178:
        -: 1179:      //discard played card from hand
    #####: 1180:      discardCard(handPos, currentPlayer, state, 0);
        -: 1181:
    #####: 1182:      return 0;
        -: 1183:
        -: 1184:
        -: 1185:    case embargo:
        -: 1186:      //+2 Coins
    #####: 1187:      state->coins = state->coins + 2;
        -: 1188:
        -: 1189:      //see if selected pile is in play
    #####: 1190:      if ( state->supplyCount[choice1] == -1 )
        -: 1191:	{
    #####: 1192:	  return -1;
        -: 1193:	}
        -: 1194:
        -: 1195:      //add embargo token to selected supply pile
    #####: 1196:      state->embargoTokens[choice1]++;
        -: 1197:
        -: 1198:      //trash card
    #####: 1199:      discardCard(handPos, currentPlayer, state, 1);

    #####: 1200:      return 0;
        -: 1201:
        -: 1202:    case outpost:
    #####: 1203:        return outpost_card(handPos, currentPlayer, state);
        -: 1204:
        -: 1205:    case salvager:
        -: 1206:      //+1 buy
    #####: 1207:      state->numBuys++;
        -: 1208:
    #####: 1209:      if (choice1)
        -: 1210:	{
        -: 1211:	  //gain coins equal to trashed card
    #####: 1212:	  state->coins = state->coins + getCost( handCard(choice1, state) );
        -: 1213:	  //trash card
    #####: 1214:	  discardCard(choice1, currentPlayer, state, 1);

    #####: 1215:	}
        -: 1216:
        -: 1217:      //discard card
    #####: 1218:      discardCard(handPos, currentPlayer, state, 0);
    #####: 1219:      return 0;
        -: 1220:
        -: 1221:    case sea_hag:
    #####: 1222:      for (i = 0; i < state->numPlayers; i++){
    #####: 1223:	if (i != currentPlayer){
    #####: 1224:	  state->discard[i][state->discardCount[i]] = state->deck[i][state->deckCount[i]--];			    state->deckCount[i]--;
    #####: 1225:	  state->discardCount[i]++;
    #####: 1226:	  state->deck[i][state->deckCount[i]--] = curse;//Top card now a curse
    #####: 1227:	}
    #####: 1228:      }
    #####: 1229:      return 0;
        -: 1230:
        -: 1231:    case treasure_map:
        -: 1232:      //search hand for another treasure_map
    #####: 1233:      index = -1;
    #####: 1234:      for (i = 0; i < state->handCount[currentPlayer]; i++)
        -: 1235:	{
    #####: 1236:	  if (state->hand[currentPlayer][i] == treasure_map && i != handPos)
        -: 1237:	    {
    #####: 1238:	      index = i;
    #####: 1239:	      break;
        -: 1240:	    }
    #####: 1241:	}
    #####: 1242:      if (index > -1)
        -: 1243:	{
        -: 1244:	  //trash both treasure cards
    #####: 1245:	  discardCard(handPos, currentPlayer, state, 1);
    #####: 1246:	  discardCard(index, currentPlayer, state, 1);
        -: 1247:
        -: 1248:	  //gain 4 Gold cards
    #####: 1249:	  for (i = 0; i < 4; i++)
        -: 1250:	    {
    #####: 1251:	      gainCard(gold, state, 1, currentPlayer);
    #####: 1252:	    }
        -: 1253:
        -: 1254:	  //return success
    #####: 1255:	  return 1;
        -: 1256:	}
        -: 1257:
        -: 1258:      //no second treasure_map found in hand
    #####: 1259:      return -1;
        -: 1260:    }
        -: 1261:
    #####: 1262:  return -1;
       17: 1263:}
        -: 1264:
        -: 1265:int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
        -: 1266:{
        -: 1267:
        -: 1268:  //if card is not trashed, added to Played pile
       34: 1269:  if (trashFlag < 1)
        -: 1270:    {
        -: 1271:      //add card to played pile
       24: 1272:      state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos];
       24: 1273:      state->playedCardCount++;
       24: 1274:    }
        -: 1275:
        -: 1276:  //set played card to -1
       34: 1277:  state->hand[currentPlayer][handPos] = -1;
        -: 1278:
        -: 1279:  //remove card from player's hand
       34: 1280:  if ( handPos == (state->handCount[currentPlayer] - 1) ) 	//last card in hand array is played
        -: 1281:    {
        -: 1282:      //reduce number of cards in hand
        3: 1283:      state->handCount[currentPlayer]--;
        3: 1284:    }
       31: 1285:  else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
        -: 1286:    {
        -: 1287:      //reduce number of cards in hand
    #####: 1288:      state->handCount[currentPlayer]--;
    #####: 1289:    }
        -: 1290:  else
        -: 1291:    {
        -: 1292:      //replace discarded card with last card in hand
       31: 1293:      state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
        -: 1294:      //set last card to -1
       31: 1295:      state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
        -: 1296:      //reduce number of cards in hand
       31: 1297:      state->handCount[currentPlayer]--;
        -: 1298:    }
        -: 1299:
       34: 1300:  return 0;
        -: 1301:}
        -: 1302:
        -: 1303:int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
        -: 1304:{
        -: 1305:  //Note: supplyPos is enum of choosen card
        -: 1306:
        -: 1307:  //check if supply pile is empty (0) or card is not used in game (-1)
    #####: 1308:  if ( supplyCount(supplyPos, state) < 1 )
        -: 1309:    {
    #####: 1310:      return -1;
        -: 1311:    }
        -: 1312:
        -: 1313:  //added card for [whoseTurn] current player:
        -: 1314:  // toFlag = 0 : add to discard
        -: 1315:  // toFlag = 1 : add to deck
        -: 1316:  // toFlag = 2 : add to hand
        -: 1317:
    #####: 1318:  if (toFlag == 1)
        -: 1319:    {
    #####: 1320:      state->deck[ player ][ state->deckCount[player] ] = supplyPos;
    #####: 1321:      state->deckCount[player]++;
    #####: 1322:    }
    #####: 1323:  else if (toFlag == 2)
        -: 1324:    {
    #####: 1325:      state->hand[ player ][ state->handCount[player] ] = supplyPos;
    #####: 1326:      state->handCount[player]++;
    #####: 1327:    }
        -: 1328:  else
        -: 1329:    {
    #####: 1330:      state->discard[player][ state->discardCount[player] ] = supplyPos;
    #####: 1331:      state->discardCount[player]++;
        -: 1332:    }
        -: 1333:
        -: 1334:  //decrease number in supply pile
    #####: 1335:  state->supplyCount[supplyPos]--;
        -: 1336:
    #####: 1337:  return 0;
    #####: 1338:}
        -: 1339:
        -: 1340:int updateCoins(int player, struct gameState *state, int bonus)
        -: 1341:{
        -: 1342:  int i;
        -: 1343:
        -: 1344:  //reset coin count
      210: 1345:  state->coins = 0;
        -: 1346:
        -: 1347:  //add coins for each Treasure card in player's hand
     2520: 1348:  for (i = 0; i < state->handCount[player]; i++)
        -: 1349:    {
     1050: 1350:      if (state->hand[player][i] == copper)
        -: 1351:	{
      454: 1352:	  state->coins += 1;
      454: 1353:	}
      596: 1354:      else if (state->hand[player][i] == silver)
        -: 1355:	{
      220: 1356:	  state->coins += 2;
      220: 1357:	}
      376: 1358:      else if (state->hand[player][i] == gold)
        -: 1359:	{
      220: 1360:	  state->coins += 3;
      220: 1361:	}
     1050: 1362:    }
        -: 1363:
        -: 1364:  //add bonus
      210: 1365:  state->coins += bonus;
        -: 1366:
      210: 1367:  return 0;
        -: 1368:}
        -: 1369:
        -: 1370:
        -: 1371://end of dominion.c
        -: 1372:

*/