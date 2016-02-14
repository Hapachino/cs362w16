/*************************************************************
Jack Holkeboer
Oregon State University cs362
holkeboj@onid.oregonstate.edu
Assignment 4

Discussion of random tests

******************************************
**********  ADVENTURER CARD **************
******************************************
Function 'adventurer_card'
Lines executed:85.71% of 21
Branches executed:100.00% of 14
Taken at least once:85.71% of 14


*** STRATEGY FOR CONSTRUCTING TEST CASES
******************************************
My goal in creating random test game states was to cover
every possible permutation of the game.  The variables that can 
change between games are the player count, the deck, 
the hand, and the discard pile.

One major shortcoming of my previous tests is that they only tested 
for the case of two players.  They also did not randoming the state of the
decks, hands, or discard piles.  Introducing randomness here allowed me to
test a wider variety of casea and improve my line coverage by 33.33%.
Randomization of players is done with the following code:

        playerCount = 2 + (rand() % (MAX_PLAYERS - 1));
        player = rand() % playerCount;

For the deck, hand, and discard pile, it is first necessary to set the "counts"
for each of these piles by choosing a random number between 0 and the 
maximum possible size for that pile.  These values are provided as constants
in dominion.h as MAX_HAND and MAX_DECK.

Then I loop from 0 to these randomly chosen sizes, at each stem adding
a random card by picking a random number between 0 and 26.
This is done with the following code:


        for (i = 0; i < playerCount; i++) {
            testGame.deckCount[i] = rand() % MAX_DECK; // random deck count
            testGame.discardCount[i] = rand() % MAX_DECK; // random discard count
            testGame.handCount[i] = rand () % MAX_HAND + 1; // random hand count
            
            // give each player a random hand
            for (j = 0; j < testGame.handCount[i]; j++) {
                testGame.hand[i][j] = rand() % 27;   
            }
            // give each player a random deck
            for (j = 0; j < testGame.deckCount[i], j++) {
                testGame.deck[i][j] = rand() % 27;
            }
            // give each player a random discard pile
            for (j = 0; j < testGame.discardCount[i], j++) {
                testGame.discard[i][j] = rand() % 27;
            }
        }

Finally, we must satisfy some special conditions for the adventuere card.
First, the player whose turn it is must have an adventurer card to play, so we 
guarantee they will have one by placing one in a random spot in their hand.
This is done with the following code:

        testGame.hand[player][rand() % testGame.handCount[player]] = adventurer;

We must also make sure there are at least two treasure cards in the deck, or else
the player will continue drawing and never satisfy the condition of the card, which is
that the player draws until he/she receives two treasure cards.
This is done with the following code:

        for (treasure = 0; treasure < 2; treasure++) {
            randomTreasure = rand() % 3;
            randomDeckPos = rand() % MAX_DECK;
            if (randomTreasure == 0) {
                // add a gold to the deck
                testGame.deck[player][randomDeckPos] = gold;
            } else if (randomTreasure == 1) {
                // add a copper to the deck
                testGame.deck[player][randomDeckPos] = silver;
            } else {
                testGame.deck[player][randomDeckPos] = copper;
            }
        }



*** IMPROVEMENTS IN COVERAGE
******************************************
All of my coverage metrics improved from by previous test
of this card.  

Line coverage increased by 33.33%, from 52.38% to 85.71%.

Branch coverage reached 100%.  It increased 28.57% from 71.43%
in the previous assignment.

85.71% of statements were taken at least once, which is up
50% from 35.71 previously.

*** BUG DETECTION
******************************************
When the test was run previously, there were 18 passes and 5 failures (27.8% pass rate).
In the randomized for, there were 7998 passed and 3002 failed (37.5% pass rate).
The higher percentage of failures in the random tests suggests that they are 
catching some bugs that were not caught by the simpler test cases.  However, since
the sample size from the previous test was so small, we must be cautious in interpreting
this difference.  There is also some slight variation in the number of tests passed,
indicating that randomness has an effect. 
The three tests that consistently are failing are:

    Did played card count increment?
    Did player _ receive two cards ?
    Did player _ receive two treasure cards?


******************************************
**********  GREAT HALL CARD **************
******************************************
(since this card is in a case switch statement, we use 
    the raw gcov output instead of gcov -f -b)
*** GCOV OUTPUT
        -:  948:    case great_hall:
        -:  949:      //+1 Card
     1000:  950:      drawCard(currentPlayer, state);
        -:  951:
        -:  952:      //+1 Actions
     1000:  953:      state->numActions++;
        -:  954:
        -:  955:      //discard card from hand
     1000:  956:      discardCard(handPos, currentPlayer, state, 0);
     1000:  957:      return 0;

*** STRATEGY TO CONSTRUCT TEST CASES
******************************************
The strategy for this was mostly same as the strategy described above
for the adventuere card, but with the following differences:
    - No manipulation to guarantee presence of treasure cards
    - Instead of guaranteeing the player has an adventuere card,
        we guarantee that the player has a great hall card

*** IMPROVEMENTS IN COVERAGE
******************************************
This card was already fully covered (branch, statement, boundary) when
I tested it in the previous assignment, so there was no improvement to be made.
However, it is interesting 

*** BUG DETECTION
******************************************
When this test was run previously, it had 24 passed tests and 2 failures.
In the randomized form, it has 12000 passes and 1000 failures.  This value did
not change on repeated execution of the randomized tester.
Since these pass/fail ratios are equal, it suggests that no new
bugs were discovered by the introduction of randomness in this card.
The failures indicated the same bug in the discardCard function as
they did previously.



**************************************************************/