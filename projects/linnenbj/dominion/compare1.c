/*
James Linnenburger
coverage1.c
CS362 - Assignment #3
Oregon State University - Winter 2016 Term


Summary Coverage of entire dominion.c file
---------------------------------------------------------------------------
File 'dominion.c'
Lines executed:37.19% of 597
Branches executed:39.28% of 415
Taken at least once:33.25% of 415
Calls executed:22.11% of 95
dominion.c:creating 'dominion.c.gcov'

Analysis:
  While you will be able to see that my unit and card tests that I tested 
  for this assignment have very good coverage, I have still only hit about 
  1/3 of the code in dominion and even less of the potential calls.  Moving 
  forward with this test suite, I will need to add in new tests for
  the areas that got no coverage so far.
  
Things to Improve in future:
  <<finish this>>
--------------------------------------------------------------------------


unittest1: isGameOver()
--------------------------------------------------------------------------
Function 'isGameOver'
Lines executed:100.00% of 10
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
No calls

function isGameOver called 18280 returned 100% blocks executed 100%
    18280:  422:int isGameOver(struct gameState *state)
        -:  423:{
        -:  424:    int i;
        -:  425:    int j;
        -:  426:
        -:  427:    //if stack of Province cards is empty, the game ends
    18280:  428:    if (state->supplyCount[province] == 0)
branch  0 taken 2003 (fallthrough)
branch  1 taken 16277
        -:  429:    {
     2003:  430:        return 1;
        -:  431:    }
        -:  432:
        -:  433:    //if three supply pile are at 0, the game ends
    16277:  434:    j = 0;
   423202:  435:    for (i = 0; i < 25; i++)
branch  0 taken 406925
branch  1 taken 16277 (fallthrough)
        -:  436:    {
   406925:  437:        if (state->supplyCount[i] == 0)
branch  0 taken 44424 (fallthrough)
branch  1 taken 362501
        -:  438:        {
    44424:  439:            j++;
        -:  440:        }
        -:  441:    }
    16277:  442:    if ( j >= 3)
branch  0 taken 12144 (fallthrough)
branch  1 taken 4133
        -:  443:    {
    12144:  444:        return 1;
        -:  445:    }
        -:  446:
     4133:  447:    return 0;
        -:  448:}



	
Analysis:
My coverage does a good job hitting everything inside isGameOver()
multiple times. This was done by a brute force unit test that tested
all possible combinations of empty card stacks using 0, 1, 2, and 3
different cards being emptied out.  This method allowed me to find a bug 
that I would have normally missed (described in bug1.c).  Overall I feel 
confident with this test and feel it is thorough in its testing of 
isGameOver().
--------------------------------------------------------------------------
 
 
unittest2: getCost()
--------------------------------------------------------------------------
Function 'getCost'
Lines executed:100.00% of 30
Branches executed:100.00% of 28
Taken at least once:100.00% of 28
No calls

Analysis:
(I'm skipping the actual line count graph for this one as it is long and
uneventful.)  After looking at the gcov results, I realize that I never
attempted to pass in an 'out of bounds' card into getCost().  This is
the line of code that I'm missing from here.  This is an easy fix, but
possibly not that critical as there should be check in place before 
getCost() gets called to make sure it is being passed a valid card.  
Either way, I should add in the last check to get the 100% coverage.

**UPDATE**
I fixed the unit test for this method and it now hits all possible 
branches and lines.
--------------------------------------------------------------------------

unittest3:  updateCoins()
--------------------------------------------------------------------------
Function 'updateCoins'
Lines executed:100.00% of 11
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
No calls

function updateCoins called 3535 returned 100% blocks executed 100%
     3535: 1477:int updateCoins(int player, struct gameState *state, int bonus)
        -: 1478:{
        -: 1479:    int i;
        -: 1480:
        -: 1481:    //reset coin count
     3535: 1482:    state->coins = 0;
        -: 1483:
        -: 1484:    //add coins for each Treasure card in player's hand
    20330: 1485:    for (i = 0; i < state->handCount[player]; i++)
branch  0 taken 16795
branch  1 taken 3535 (fallthrough)
        -: 1486:    {
    16795: 1487:        if (state->hand[player][i] == copper)
branch  0 taken 7313 (fallthrough)
branch  1 taken 9482
        -: 1488:        {
     7313: 1489:            state->coins += 1;
        -: 1490:        }
     9482: 1491:        else if (state->hand[player][i] == silver)
branch  0 taken 1980 (fallthrough)
branch  1 taken 7502
        -: 1492:        {
     1980: 1493:            state->coins += 2;
        -: 1494:        }
     7502: 1495:        else if (state->hand[player][i] == gold)
branch  0 taken 1980 (fallthrough)
branch  1 taken 5522
        -: 1496:        {
     1980: 1497:            state->coins += 3;
        -: 1498:        }
        -: 1499:    }
        -: 1500:
        -: 1501:    //add bonus
     3535: 1502:    state->coins += bonus;
        -: 1503:
     3535: 1504:    return 0;
        -: 1505:}


Analysis:
This test does a good job of hitting all branches and blocks of updateCoins()
many times.  I feel confident that this test has thoroughly 'vetted' the
updateCoins() method as there is 100% coverage with each line being run at
least 1900 times.
--------------------------------------------------------------------------

unittest4:  fullDeckCount()
--------------------------------------------------------------------------
Function 'fullDeckCount'
Lines executed:100.00% of 9
Branches executed:100.00% of 12
Taken at least once:100.00% of 12
No calls

 1000:  349:int fullDeckCount(int player, int card, struct gameState *state)
	-:  350:{
	-:  351:    int i;
 1000:  352:    int count = 0;
	-:  353:
10273:  354:    for (i = 0; i < state->deckCount[player]; i++)
 1000:  354-block  0
 9273:  354-block  1
10273:  354-block  2
	-:  355:    {
 9273:  356:        if (state->deck[player][i] == card) count++;
 9273:  356-block  0
 1632:  356-block  1
	-:  357:    }
	-:  358:
 5968:  359:    for (i = 0; i < state->handCount[player]; i++)
 1000:  359-block  0
 4968:  359-block  1
 5968:  359-block  2
	-:  360:    {
 4968:  361:        if (state->hand[player][i] == card) count++;
 4968:  361-block  0
  930:  361-block  1
	-:  362:    }
	-:  363:
 6759:  364:    for (i = 0; i < state->discardCount[player]; i++)
 1000:  364-block  0
 5759:  364-block  1
 6759:  364-block  2
	-:  365:    {
 5759:  366:        if (state->discard[player][i] == card) count++;
 5759:  366-block  0
 1021:  366-block  1
	-:  367:    }
	-:  368:
 1000:  369:    return count;
 1000:  369-block  0
	-:  370:}

Anaylsis:
Complete coverage on all lines, braches & blocks in fullDeckCount().
This was another reasonably straight forward function to test for, and with
the high number of tests, I again feel confident that this function has
been fully 'vetted'.
--------------------------------------------------------------------------

cardtest1: smithy
--------------------------------------------------------------------------
Function 'playCardSmithy'
Lines executed:100.00% of 6
Branches executed:100.00% of 2
Taken at least once:100.00% of 2
Calls executed:100.00% of 2

function playCardSmithy called 4 returned 100% blocks executed 100%
        4: 1271:int playCardSmithy(struct gameState *state, int currentPlayer, int handPos)
        -: 1272:{
        -: 1273:    //+3 Cards
        -: 1274:    int i;
       16: 1275:    for (i = 0; i < 3; i++)
branch  0 taken 12
branch  1 taken 4 (fallthrough)
        -: 1276:    {
       12: 1277:        drawCard(currentPlayer, state);
call    0 returned 12
       12: 1278:        handPos++;    //adjust position of smithy card to allow for card just drawn.
        -: 1279:    }
        -: 1280:
        -: 1281:    //discard card from hand
        4: 1282:    discardCard(handPos, currentPlayer, state, 1);
call    0 returned 4
        4: 1283:    return 0;
        -: 1284:}
        -: 1285:



Analysis:
Coverage was very good for the test of the smithy card, hitting 100%
in lines, calls and branches.  Testing was done by loading a specific player's
 hand/deck/discard and passing that to the smithy card.  Several bugs were 
 discovered through testing. I temporarily fixed the function to make sure 
 my test suite was valid for a good implementation. I believe I did a decent
 job in picking enough 'interesting' test cases to get a thorough test of
 this card.
--------------------------------------------------------------------------

cardtest2: adventurer
--------------------------------------------------------------------------
Function 'playCardAdventurer'
Lines executed:100.00% of 18
Branches executed:100.00% of 12
Taken at least once:100.00% of 12
Calls executed:100.00% of 3

function playCardAdventurer called 5 returned 100% blocks executed 100%
        5: 1306:int playCardAdventurer(struct gameState *state, int currentPlayer, int handPos)
        -: 1307:{
        -: 1308:    //decare variables
        -: 1309:    int temphand[MAX_HAND];     //establish a temporary hand for non-treasure cards
        5: 1310:    int tempCount = 0;          //How many cards are currently in the temporary hand
        5: 1311:    int drawntreasure = 0;          //how many treasure cards have been drawn
        -: 1312:    int cardDrawn;              //the card that was just drawn
        -: 1313:
        5: 1314:    discardCard(handPos, currentPlayer, state, 0);  //Discard the adventurer card
call    0 returned 5
        -: 1315:
       38: 1316:    while(drawntreasure<=2)                         //As long as 2 treasures have not been drawn
branch  0 taken 28
branch  1 taken 5 (fallthrough)
        -: 1317:    {
        -: 1318:
       28: 1319:        if (state->deckCount[currentPlayer] <1)     //if the deck is empty we need to shuffle
branch  0 taken 6 (fallthrough)
branch  1 taken 22
        -: 1320:        {
        6: 1321:            shuffle(currentPlayer, state);            //discard and add to deck
call    0 returned 6
        -: 1322:        }
        -: 1323:
       28: 1324:        drawCard(currentPlayer, state);
call    0 returned 28
       28: 1325:        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]; //correct version.
        -: 1326:
       43: 1327:        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
branch  0 taken 16 (fallthrough)
branch  1 taken 12
branch  2 taken 14 (fallthrough)
branch  3 taken 2
branch  4 taken 1 (fallthrough)
branch  5 taken 13
       15: 1328:            drawntreasure++;
        -: 1329:        else
        -: 1330:        {
       13: 1331:            temphand[tempCount]=cardDrawn;
       13: 1332:            state->handCount[currentPlayer]--;  //this should just remove the top card (the most recently drawn one).
       13: 1333:            tempCount++;
        -: 1334:        }
        -: 1335:    }
        -: 1336:
       23: 1337:    while(tempCount-1>=0)
branch  0 taken 13
branch  1 taken 5 (fallthrough)
        -: 1338:    {
       13: 1339:        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[tempCount-1]; // discard all cards in play that have been drawn
       13: 1340:        tempCount -= 1;
        -: 1341:    }
        5: 1342:    return 0;
        -: 1343:}


Analysis:
This was one of the most difficult tests to write.  Partially because the
function itself was so buggy that it was hard to tell specifically where
the discrepancies were (Almost needed a test for my test).  Eventually
I got it sorted out, but there are still some things that could use 
improvement.  I am happy with they way my unittest reports output and
I feel that it does a good job of checking not only code/branch coverage 
but it digs deeper and tests to make sure the entire gamestate is what
it should be after playing the card.  I developed the robust reporting
and it really streamlined the process of unit testing the cards.
--------------------------------------------------------------------------

cardtest3: village
--------------------------------------------------------------------------
Function 'playCardVillage'
Lines executed:100.00% of 4
No branches
Calls executed:100.00% of 1

function playCardVillage called 3 returned 100% blocks executed 100%
        3: 1286:int playCardVillage(struct gameState *state, int currentPlayer)
        -: 1287:{
        -: 1288:    //+1 Card
        3: 1289:    drawCard(currentPlayer, state);
call    0 returned 3
        -: 1290:
        -: 1291:    //+2 Actions
        3: 1292:    state->numActions = 2;
        3: 1293:    return 0;
        -: 1294:}

Analysis:
Although this method is short, I spent quit a bit of time trying to get
as thorough of a test on it as I could.  It hits all of the lines, and
calls, but there are no branches in this function.  The test did find 
several issues when checking the player's hand and played card pile
before and after playing the card. In writing the test 
for this, I realized that this function really needs to be refactored to
include a parameter for the position of the village card being played.
--------------------------------------------------------------------------

cardtest4: great_hall
--------------------------------------------------------------------------
Function 'playCardGreatHall'
Lines executed:100.00% of 4
No branches
Calls executed:100.00% of 2

function playCardGreatHall called 3 returned 100% blocks executed 100%
        3: 1296:int playCardGreatHall(struct gameState *state, int currentPlayer, int handPos)
        -: 1297:{
        -: 1298:    //+1 Card
        3: 1299:    drawCard(currentPlayer, state);
call    0 returned 3
        -: 1300:
        -: 1301:    //discard card from hand
        3: 1302:    discardCard(handPos, currentPlayer, state, 1);
call    0 returned 3
        3: 1303:    return 0;
        -: 1304:}
	
Analysis:
The test did a good job of getting 100% coverage (although not difficult to
do in this case.)  Again, the key to a good test here is what is happening
'behind the scenes'.  Without checking the value of the gamestate, testing
this function would be basically worthless.  I was able to determine the
bugs in the implementation of this card through the checking of the gamestate
with an expected gamestate.
--------------------------------------------------------------------------
