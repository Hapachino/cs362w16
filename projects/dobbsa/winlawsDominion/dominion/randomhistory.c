******************************************************************************

***  CS 362 - Assignment 4 - Random Testing For Dominion - Spencer Winlaw  ***

***************  randomhistory.c - write-up for Assignment 4   ***************

******************************************************************************

Development
------------------------------------------------------------------------------
Assignment 4 asked students to develop random testers for two dominion cards. 
In addition to the required Adventurer card, I chose to test the Smithy card.
My approach to randomly testing both cards was virtually identical. I initialized
a random gamestate, called the cardEffect() function for the appropriate card,
then compared the results of the call to exected results based on the rules 
of the dominion game. 
The main difficulty I faced was in developing an appropriate way of generating 
random gameStates. Ultimately I ended up deciding to create my own function in 
order to generate the random gamestates for dominion - getRandomGameState(). 
The code for this function can be found in the getRandomGameState.c file in my 
dominion directory. It creates a new gamestate pointer and initializes relavant
attributes (numPlayers, whoseTurn, hand, handCount, deck, deckCount, discard, 
discardCount, playedCards, and playedCardCount) with random values in order to 
test the two cards.

Coverage Results
------------------------------------------------------------------------------
	
	Adventurer Card
	--------------------------------------------------------------------------
	function playAdventurer called 10000 returned 100% blocks executed 100%
	    10000: 1327:int playAdventurer(struct gameState *state)
	        -: 1328:{ 
	    10000: 1329:  int currentPlayer = whoseTurn(state);
	call    0 returned 100%
	        -: 1330:  int temphand[MAX_HAND];// moved above the if statement
	    10000: 1331:  int drawntreasure=0;
	        -: 1332:  int cardDrawn;
	    10000: 1333:  int z = 0;
	        -: 1334:  
	   338694: 1335:  while(drawntreasure<2)
	branch  0 taken 97%
	branch  1 taken 3% (fallthrough)
	        -: 1336:  {
	   318694: 1337:    if (state->deckCount[currentPlayer] <1)//if the deck is empty we need to shuffle discard and add to deck
	branch  0 taken 28% (fallthrough)
	branch  1 taken 72%
	        -: 1338:    {
	    89485: 1339:    shuffle(currentPlayer, state);
	call    0 returned 100%
	        -: 1340:    }
	   318694: 1341:    drawCard(currentPlayer, state);
	call    0 returned 100%
	   318694: 1342:    cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
	        -: 1343:    //if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) *ORIGINAL CODE*
	   338694: 1344:    if (cardDrawn == copper || cardDrawn == gold) //*BUG INTRODUCED* - Omit check for silver
	branch  0 taken 97% (fallthrough)
	branch  1 taken 3%
	branch  2 taken 3% (fallthrough)
	branch  3 taken 97%
	    20000: 1345:      drawntreasure++;
	        -: 1346:    else
	        -: 1347:    {
	   298694: 1348:      temphand[z]=cardDrawn;
	   298694: 1349:      state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
	   298694: 1350:      z++;
	        -: 1351:    }
	        -: 1352:  }
	        -: 1353:  
	   258837: 1354:  while(z-1>=0)
	branch  0 taken 96%
	branch  1 taken 4% (fallthrough)
	        -: 1355:  {
	   238837: 1356:    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
	   238837: 1357:    z=z-1;
	        -: 1358:  }
	    10000: 1359:  return 0;
	        -: 1360:}

	Smithy Card
	--------------------------------------------------------------------------
	function playSmithy called 10000 returned 100% blocks executed 100%
	    10000: 1363:int playSmithy(struct gameState *state, int handPos)
	        -: 1364:{
	        -: 1365:  int i;
	    10000: 1366:  int currentPlayer = whoseTurn(state);
	call    0 returned 100%
	        -: 1367:  
	        -: 1368:  //+3 Cards
	        -: 1369:  //for (i = 0; i < 3; i++) *ORIGINAL CODE*
	    50000: 1370:  for (i = 0; i <= 3; i++) //*BUG INTRODUCED* - wrong logical operator -> Off-By-One error 
	branch  0 taken 80%
	branch  1 taken 20% (fallthrough)
	        -: 1371:  {
	    40000: 1372:    drawCard(currentPlayer, state);
	call    0 returned 100%
	        -: 1373:  }
	        -: 1374:      
	        -: 1375:  //discard card from hand
	    10000: 1376:  discardCard(handPos, currentPlayer, state, 0);
	call    0 returned 100%
	    10000: 1377:  return 0;
	        -: 1378:}

My coverage results for Assignment 4 were improved from Assignment 3. While I was
able to acheive 100% statement coverage with my initiial unit tests for these funcitons
in Assignment 3, I wasn't reaching full branch coverage. With random testing I am now
reaching full branch coverage in Assignment 4, though I see that with some tweaking 
I could manipulate some branches to be covered more frequently. It seams with testing
there is always more that can be done.


Bugs
------------------------------------------------------------------------------
When analyzing some of the results of the testing I was able to find the 
following bugs. 

	Adventurer Card
	--------------------------------------------------------------------------
	Doesn't discard adventurer card after it is played. Therefore the card 
	remains in the players hand and is not recorded in the player's playedCards.
	This is a significant issue as it would allow the player to continually play
	the card an infinite number of times. This in itself is a problem for 
	gameplay, but in addition, the card functionality has no checks to ensure 
	there are two more treasure cards remaining in a player's deck to be drawn, 
	and could enter into an infinite loop searching for more when there are none
	to be found, breaking the game.

	Smithy Card
	--------------------------------------------------------------------------
	Draws 4 cards to player's hand when it should only draw 3. This was an 
	off-by-one error introduced by the use of an incorrect logical operator 
	(<= instead of <).
	**Bug from Assignment 2

With these present and occuring in every test it makes it more difficult to 
sort out other bugs that may be present within the code. I suspect that resolving
these issues and running more random testing may lead to clearer results and 
the discovery of more bugs.
	
	



