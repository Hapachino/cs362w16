/*  Paul Zotz
    CS 362 Winter 2016
    Assignment 4
*/

/*

For both of these tests, I tested the functions in relative isolation. Game states were randomized based on the example in testDrawCard.c.
Necessary things such as hands, decks, discard piles, etc. were initialized as needed. Pile sizes were based on the maximum possible values.
To make running times more manageable, it might be best to attempt to keep decks, hands, etc. relatively small while still allowing for
the possibility of very large values - something I experimented with in randomtestcard.

Adventurer:
For the purposes of this test, I ensured that there were at least two treasure cards to be played in every deck and counted any treasure
randomly added to the hand (in order to check against the expected number of treasure after 2 were added). Discard piles are initialized to zero.

The biggest issue I noticed is that the random tester very rarely produces a situation where an empty deck needs to be shuffled - something the unit
test specifically addressed. This could be rectified by brute force (increasing the number of tests) or by making modifying the pile creation
to ensure a greater chance of the discard needing to be shuffled. It would also probably be a good idea to randomize the discard pile before
each test and try to create more situations (through manipulation or brute force) where a player has to discard their entire deck before they begin
finding treasures in their newly shuffled deck.

Village:
No major observations here. This card is fairly simple and the random tester simply produces the same coverage results as the unit tests for
many more times. It seems that more brute force would have no benefit here. Instead, better testing would need to expand the test oracle to
test for more situations - behavior after a a turn is ended, if the played cards pile isn't always 0, etc.

DETAILED COVERAGE RESULTS:

ADVENTURER: (randomtestadventurer.c)

Assignment 3:
function adventurerCard called 6 returned 100% blocks executed 100%
        6: 1271:int adventurerCard(struct gameState *state, int currentPlayer)
        -: 1272:{
        -: 1273:    int cardDrawn;
        6: 1274:    int drawntreasure = 0;
        6: 1275:    int z = 0;
        -: 1276:    int temphand[MAX_HAND];
        -: 1277:
       32: 1278:    while(drawntreasure<=2){
branch  0 taken 77%
branch  1 taken 23% (fallthrough)
       20: 1279:        if (state->deckCount[currentPlayer] < 1){//if the deck is empty we need to shuffle discard and add to deck
branch  0 taken 25% (fallthrough)
branch  1 taken 75%
        5: 1280:          shuffle(currentPlayer, state);
call    0 returned 100%
        -: 1281:        }
       20: 1282:        drawCard(currentPlayer, state);
call    0 returned 100%
       20: 1283:        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
       38: 1284:        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
branch  0 taken 85% (fallthrough)
branch  1 taken 15%
branch  2 taken 100% (fallthrough)
branch  3 taken 0%
branch  4 taken 88% (fallthrough)
branch  5 taken 12%
       18: 1285:          drawntreasure++;
        -: 1286:        else{
        2: 1287:          temphand[z]=cardDrawn;
        2: 1288:          state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
        2: 1289:          z++;
        -: 1290:        }
        -: 1291:    }
        -: 1292:
       14: 1293:    while(z-1>=0){
branch  0 taken 25%
branch  1 taken 75% (fallthrough)
        2: 1294:        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
        2: 1295:        z=z-1;
        -: 1296:    }
        -: 1297:
        6: 1298:    return 0;


Assignment 4:

function adventurerCard called 2000 returned 100% blocks executed 100%
     2000: 1271:int adventurerCard(struct gameState *state, int currentPlayer)
        -: 1272:{
        -: 1273:    int cardDrawn;
     2000: 1274:    int drawntreasure = 0;
     2000: 1275:    int z = 0;
        -: 1276:    int temphand[MAX_HAND];
        -: 1277:
    56498: 1278:    while(drawntreasure<=2){
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
    52498: 1279:        if (state->deckCount[currentPlayer] < 1){//if the deck is empty we need to shuffle discard and add to deck
branch  0 taken 2% (fallthrough)
branch  1 taken 98%
      805: 1280:          shuffle(currentPlayer, state);
call    0 returned 100%
        -: 1281:        }
    52498: 1282:        drawCard(currentPlayer, state);
call    0 returned 100%
    52498: 1283:        cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
    58498: 1284:        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)^M
branch  0 taken 96% (fallthrough)
branch  1 taken 4%
branch  2 taken 96% (fallthrough)
branch  3 taken 4%
branch  4 taken 4% (fallthrough)
branch  5 taken 96%
     6000: 1285:          drawntreasure++;
        -: 1286:        else{
    46498: 1287:          temphand[z]=cardDrawn;
    46498: 1288:          state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
    46498: 1289:          z++;
        -: 1290:        }
        -: 1291:    }
        -: 1292:
    50498: 1293:    while(z-1>=0){
branch  0 taken 96%
branch  1 taken 4% (fallthrough)
    46498: 1294:        state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    46498: 1295:        z=z-1;
        -: 1296:    }
        -: 1297:
     2000: 1298:    return 0;

VILLAGE: (randomtestvillage.c)

Assignment 3:

function villageCard called 5 returned 100% blocks executed 100%
        5: 1301:int villageCard(struct gameState *state, int currentPlayer, int handPos)
        -: 1302:{
        -: 1303:    //+1 Card
        5: 1304:    drawCard(currentPlayer, state);
call    0 returned 100%
        -: 1305:
        -: 1306:    //+2 Actions
        5: 1307:    state->numActions = state->numActions++;
        -: 1308:
        -: 1309:    //discard played card from hand
        5: 1310:    discardCard(handPos, currentPlayer, state, 0);
call    0 returned 100%
        5: 1311:    return 0;


Assignment 4:

function villageCard called 1000 returned 100% blocks executed 100%
     1000: 1301:int villageCard(struct gameState *state, int currentPlayer, int handPos)
        -: 1302:{
        -: 1303:    //+1 Card
     1000: 1304:    drawCard(currentPlayer, state);
call    0 returned 100%
        -: 1305:
        -: 1306:    //+2 Actions
     1000: 1307:    state->numActions = state->numActions++;
        -: 1308:
        -: 1309:    //discard played card from hand
     1000: 1310:    discardCard(handPos, currentPlayer, state, 0);
call    0 returned 100%
