CS362 - Assignment 4 - Emmalee Jones
Date: 02/14/2016

randomtestadventurer.c (adventurer Card)

Initial: I started with the original adventurer card test and added a for loop to run 10000 times.  The test included 
my pre and post tests checking for valid handcount, deckcount, and discardcount on current and next player. I also checked
for pre and post tests for estate, duchy, province, and adventurer counts.

Improvements: I added a random seed to change the results for each test and a random selection of handCount, deckCount, 
and discardCount to be used to also randomly select the treasure cards used. The helped make the tests random between 
each iteration of the test.

Results: It appears that all the code was accessed.  There were problems with the bugs I introduced in assignment 2. 
Depending the on cards selected I had failures with "deckcount does not change" between pre and post and failure on
"discardcount does not change" between pre and post but only occasionally failure on "handcount does not change". 
The bug introduced in assignment 2 also appears to have introduced a boundary error with negative count numbers
occasionally for handcount.

Selected portion of gcov for coverage:

File 'dominion.c'
Lines executed:23.18% of 578
Branches executed:24.70% of 417
Taken at least once:17.27% of 417
Calls executed:12.37% of 97

        -: 1156:/********************************/
        -: 1157:/* Adventurer Function          */ 
        -: 1158:/********************************/
function runAdventurer called 10000 returned 100% blocks executed 100%
    10000: 1159:int runAdventurer(struct gameState *state, int drawntreasure, int currentPlayer, int cardDrawn, int temphand[], int z)
        -: 1160:{
   342599: 1161:  while(drawntreasure<2){
branch  0 taken 97%
branch  1 taken 3% (fallthrough)
   322599: 1162:  if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
branch  0 taken 48% (fallthrough)
branch  1 taken 52%
   156013: 1163:    shuffle(currentPlayer, state);
call    0 returned 100%
        -: 1164:  }
   322599: 1165:  drawCard(currentPlayer, state);
call    0 returned 100%
   322599: 1166:  cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
   342599: 1167:  if (cardDrawn == silver || cardDrawn == gold) //refactor to remove cardDrawn == copper
branch  0 taken 97% (fallthrough)
branch  1 taken 3%
branch  2 taken 3% (fallthrough)
branch  3 taken 97%
    20000: 1168:    drawntreasure++;  
        -: 1169:  else{
   302599: 1170:    temphand[z]=cardDrawn;
   302599: 1171:    state->handCount[currentPlayer]--;  
   302599: 1172:    z++;
        -: 1173:  }
        -: 1174:  }
   322599: 1175:      while(z-1>=0){
branch  0 taken 97%
branch  1 taken 3% (fallthrough)
   302599: 1176:  state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
   302599: 1177:  z=z-1;
        -: 1178:      }


randomtestcard.c (great_hall Card)

Initial: I started with the original great_hall card test and added a for loop to run 10000 times.  The test included 
my pre and post tests checking for valid handcount, and deckcount on current and next player. I also checked
for pre and post tests for estate, duchy, province, and adventurer counts. I also checked for correct action
count on pre and post.

Improvements: I added a random seed to change the results for each test and a random selection of handCount, deckCount, 
and discardCount to be used to also randomly select the treasure cards used. The helped make the tests random between 
each iteration of the test.

Results: It appears that all the code was accessed.  There no bugs encountered in the test.

Selected portion of gcov for coverage:

File 'dominion.c'
Lines executed:23.53% of 578
Branches executed:23.74% of 417
Taken at least once:15.83% of 417
Calls executed:12.37% of 97
dominion.c:creating 'dominion.c.gcov'

        -: 1233:/********************************/
        -: 1234:/* GreatHall Function           */ 
        -: 1235:/********************************/
function runGreatHall called 10000 returned 100% blocks executed 100%
    10000: 1236:int runGreatHall(struct gameState *state, int currentPlayer, int handPos) 
        -: 1237:{
        -: 1238:      //+1 Card
    10000: 1239:      drawCard(currentPlayer, state);
call    0 returned 100%
        -: 1240:      
        -: 1241:      //+1 Actions
    10000: 1242:      state->numActions++;
        -: 1243:      
        -: 1244:      //discard card from hand
    10000: 1245:      discardCard(handPos, currentPlayer, state, 0);
call    0 returned 100%
    10000: 1246:      return 0;

