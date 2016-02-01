/*
James Linnenburger
coverage1.c
CS362 - Assignment #3
Oregon State University - Winter 2016 Term


Summary Coverage of entire dominion.c file
---------------------------------------------------------------------------
File 'dominion.c'
Lines executed:34.00% of 597
Branches executed:33.73% of 415
Taken at least once:31.33% of 415
Calls executed:16.84% of 95
dominion.c:creating 'dominion.c.gcov'

Analysis:
  While you will be able to see that my unit and card tests that I tested 
  for this assignment have very good coverage, I have still only hit about 
  1/3 of the code in dominion and even less of the potential calls.  Moving 
  forward with this test suite, I will need to add in new tests for
  the areas that got no coverage so far.
  
Things to Improve in future:
  Most of my testing involved using a high number of randomly generated
  tests.  While I did refine the random selections so that there would be
  tests of 'fringe' cases, I think it would still be valuable to put 
  together specific gamestates to pointedly test some of the outlier 
  fringe cases instead of hoping by luck that they get hit with the random
  testing.
--------------------------------------------------------------------------


unittest1: isGameOver()
--------------------------------------------------------------------------
Function 'isGameOver'
Lines executed:100.00% of 10
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
No calls

  106:  422:int isGameOver(struct gameState *state)
	-:  423:{
	-:  424:    int i;
	-:  425:    int j;
	-:  426:
	-:  427:    //if stack of Province cards is empty, the game ends
  106:  428:    if (state->supplyCount[province] == 0)
  106:  428-block  0
	-:  429:    {
   10:  430:        return 1;
   10:  430-block  0
	-:  431:    }
	-:  432:
	-:  433:    //if three supply pile are at 0, the game ends
   96:  434:    j = 0;
 2496:  435:    for (i = 0; i < 25; i++)
   96:  435-block  0
 2400:  435-block  1
 2496:  435-block  2
	-:  436:    {
 2400:  437:        if (state->supplyCount[i] == 0)
 2400:  437-block  0
	-:  438:        {
  203:  439:            j++;
  203:  439-block  0
	-:  440:        }
	-:  441:    }
   96:  442:    if ( j >= 3)
   96:  442-block  0
	-:  443:    {
   30:  444:        return 1;
   30:  444-block  0
	-:  445:    }
	-:  446:
  106:  447:    return 0;
   66:  447-block  0
  106:  447-block  1
	-:  448:}

	
Analysis:
My coverage does a good job hitting everything inside isGameOver()
multiple times.  This was done by random testing with a high enough
test count to make sure everything got hit multiple times.  Using
the high random test count, I was able to find a bug that I would 
have normally missed (described in bug1.c).  Overall I feel confident
with this test and feel it is thorough in its testing of isGameOver().
--------------------------------------------------------------------------
 
 
unittest2: getCost()
--------------------------------------------------------------------------
Function 'getCost'
Lines executed:96.67% of 30
Branches executed:100.00% of 28
Taken at least once:96.43% of 28
No calls

Analysis:
(I'm skipping the actual line count graph for this one as it is long and
uneventful.)  After looking at the gcov results, I realize that I never
attempted to pass in an 'out of bounds' card into getCost().  This is
the line of code that I'm missing from here.  This is an easy fix, but
possibly not that critical as there should be check in place before 
getCost() gets called to make sure it is being passed a valid card.  
Either way, I should add in the last check to get the 100% coverage.
--------------------------------------------------------------------------

unittest3:  updateCoins()
--------------------------------------------------------------------------
Function 'updateCoins'
Lines executed:100.00% of 11
Branches executed:100.00% of 8
Taken at least once:100.00% of 8
No calls

 3520: 1477:int updateCoins(int player, struct gameState *state, int bonus)
	-: 1478:{
	-: 1479:    int i;
	-: 1480:
	-: 1481:    //reset coin count
 3520: 1482:    state->coins = 0;
	-: 1483:
	-: 1484:    //add coins for each Treasure card in player's hand
20240: 1485:    for (i = 0; i < state->handCount[player]; i++)
 3520: 1485-block  0
16720: 1485-block  1
20240: 1485-block  2
	-: 1486:    {
16720: 1487:        if (state->hand[player][i] == copper)
16720: 1487-block  0
	-: 1488:        {
 7260: 1489:            state->coins += 1;
 7260: 1489-block  0
	-: 1490:        }
 9460: 1491:        else if (state->hand[player][i] == silver)
 9460: 1491-block  0
	-: 1492:        {
 1980: 1493:            state->coins += 2;
 1980: 1493-block  0
	-: 1494:        }
 7480: 1495:        else if (state->hand[player][i] == gold)
 7480: 1495-block  0
	-: 1496:        {
 1980: 1497:            state->coins += 3;
 1980: 1497-block  0
	-: 1498:        }
	-: 1499:    }
	-: 1500:
	-: 1501:    //add bonus
 3520: 1502:    state->coins += bonus;
	-: 1503:
 3520: 1504:    return 0;
 3520: 1504-block  0
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

  100: 1271:int playCardSmithy(struct gameState *state, int currentPlayer, int handPos)
	-: 1272:{
	-: 1273:    //+3 Cards
	-: 1274:    int i;
  400: 1275:    for (i = 0; i < 3; i++)
  100: 1275-block  0
  400: 1275-block  1
	-: 1276:    {
  300: 1277:        drawCard(currentPlayer, state);
  300: 1277-block  0
  300: 1278:        handPos++;    //adjust position of smithy card to allow for card just drawn.
	-: 1279:    }
	-: 1280:
	-: 1281:    //discard card from hand
  100: 1282:    discardCard(handPos, currentPlayer, state, 1);
  100: 1282-block  0
  100: 1283:    return 0;
	-: 1284:}
	-: 1285:
 1000: 1286:int playCardVillage(struct gameState *state, int currentPlayer)
	-: 1287:{
	-: 1288:    //+1 Card
 1000: 1289:    drawCard(currentPlayer, state);
 1000: 1289-block  0
	-: 1290:
	-: 1291:    //+2 Actions
 1000: 1292:    state->numActions = 2;
 1000: 1293:    return 0;
	-: 1294:}

Analysis:
Coverage was very good for the test of the smithy card, hitting 100%
in lines, branches and blocks.  Testing was done with randomly loading 
a hand/deck/discard and passing that to the smithy card.  Through the
use of a high # of random choices, I feel confident that all fringe cases
got hit and tested.  Several bugs were discovered through testing. I
temporarily fixed the function to make sure my test suite was valid
for a good implementation.
--------------------------------------------------------------------------

cardtest2: adventurer
--------------------------------------------------------------------------
Function 'playCardAdventurer'
Lines executed:100.00% of 18
Branches executed:100.00% of 12
Taken at least once:100.00% of 12
Calls executed:100.00% of 3

  100: 1306:int playCardAdventurer(struct gameState *state, int currentPlayer, int handPos)
	-: 1307:{
	-: 1308:    //decare variables
	-: 1309:    int temphand[MAX_HAND];     //establish a temporary hand for non-treasure cards
  100: 1310:    int tempCount = 0;          //How many cards are currently in the temporary hand
  100: 1311:    int drawntreasure = 0;          //how many treasure cards have been drawn
	-: 1312:    int cardDrawn;              //the card that was just drawn
	-: 1313:
  100: 1314:    discardCard(handPos, currentPlayer, state, 0);  //Discard the adventurer card
  100: 1314-block  0
	-: 1315:
39042: 1316:    while(drawntreasure<=2)                         //As long as 2 treasures have not been drawn
39042: 1316-block  0
	-: 1317:    {
	-: 1318:
38942: 1319:        if (state->deckCount[currentPlayer] <1)     //if the deck is empty we need to shuffle
38942: 1319-block  0
	-: 1320:        {
38482: 1321:            shuffle(currentPlayer, state);            //discard and add to deck
38482: 1321-block  0
	-: 1322:        }
	-: 1323:
38942: 1324:        drawCard(currentPlayer, state);
38942: 1324-block  0
38942: 1325:        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]; //correct version.
	-: 1326:
38942: 1327:        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
38832: 1327-block  0
38745: 1327-block  1
  300: 1327-block  2
  300: 1328:            drawntreasure++;
	-: 1329:        else
	-: 1330:        {
38642: 1331:            temphand[tempCount]=cardDrawn;
38642: 1332:            state->handCount[currentPlayer]--;  //this should just remove the top card (the most recently drawn one).
38642: 1333:            tempCount++;
38642: 1333-block  0
	-: 1334:        }
	-: 1335:    }
	-: 1336:
 1161: 1337:    while(tempCount-1>=0)
  100: 1337-block  0
 1161: 1337-block  1
	-: 1338:    {
 1061: 1339:        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[tempCount-1]; // discard all cards in play that have been drawn
 1061: 1340:        tempCount -= 1;
 1061: 1340-block  0
	-: 1341:    }
  100: 1342:    return 0;
  100: 1342-block  0
	-: 1343:}

Analysis:
This was one of the most difficult tests to write.  Partially because the
function itself was so buggy that it was hard to tell specifically where
the discrepancies were (Almost needed a test for my test).  Eventually
I got it sorted out, but there are still some things that could use 
improvement.  This is a great example of 100% coverage does not mean
100% tested.  There are a few things that I don't feel my test did 
well enough especially when it comes to identifying if the gamestate 
matches exactly what it is supposed to after the card is played.  This
is where I would focus my time with this tester.
--------------------------------------------------------------------------

cardtest3: village
--------------------------------------------------------------------------
Function 'playCardVillage'
Lines executed:100.00% of 4
No branches
Calls executed:100.00% of 1

 1000: 1286:int playCardVillage(struct gameState *state, int currentPlayer)
	-: 1287:{
	-: 1288:    //+1 Card
 1000: 1289:    drawCard(currentPlayer, state);
 1000: 1289-block  0
	-: 1290:
	-: 1291:    //+2 Actions
 1000: 1292:    state->numActions = 2;
 1000: 1293:    return 0;
	-: 1294:}

Analysis:
Although this method is short, I spent quit a bit of time trying to get
as thorough of a test on it as I could.  It hits all of the lines, and
calls, but there are no branches in this function.  The test did find 
several issues when checking the player's hand and played card pile
before and after playing the card.  Here again, I focused on random 
testing so it would be a good idea to also implement some specific fringe
tests to make sure of functionality for all cases. 	In writing the test 
for this, I realized that this function really needs to be refactored to
include a parameter for the position of the village card being played.
--------------------------------------------------------------------------

cardtest4: great_hall
--------------------------------------------------------------------------
Function 'playCardGreatHall'
Lines executed:100.00% of 4
No branches
Calls executed:100.00% of 2

     1000: 1296:int playCardGreatHall(struct gameState *state, int currentPlayer, int handPos)
	-: 1297:{
	-: 1298:    //+1 Card
 1000: 1299:    drawCard(currentPlayer, state);
 1000: 1299-block  0
	-: 1300:
	-: 1301:    //discard card from hand
 1000: 1302:    discardCard(handPos, currentPlayer, state, 1);
 1000: 1303:    return 0;
	-: 1304:}
	
Analysis:
The test did a good job of getting 100% coverage (although not difficult to
do in this case.)  Again, the key to a good test here is what is happening
'behind the scenes'.  Without checking the value of the gamestate, testing
this function would be basically worthless.
--------------------------------------------------------------------------
