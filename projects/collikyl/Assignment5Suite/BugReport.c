Statement About Refactoring:

Some refactoring occured. I prevented some tests from displaying pass/fail states and instead displayed cards in hand/deck/discard pile to better illustrate the error. While the pass/fail states were helpful in determining a bug and descriptive, 
they were also redundant as I stated them in my bug report and multiple tests would display even for tests that passed. The display of relevant piles in their preState and postState forms were more helpful as they allowed for immeadiate 
identification of an error. I provided my teammates with the option of sending them my test code with the ability to print tests states but it wasn't requested. Additionally, refactoring occured for endTurnTest where I simply modified 
my adventureCard test to call endTurn after the adventure card had been played. This was unique to the bug report I submitted to Shaine.  Finally, I had to debug Shaine's dominion.c as my tests were not working because I called playCard.
After some testing I discovered that his adventurer case for cardEffect lacked a break statement and was the reason I was getting very odd test results. I used Shaines cardTest for the adventurer card as a base case to help me debug. Note:
I could have simply called Shaine's adventurer function as well but I went through this method instead and found this bug. I did not report it because although it was difficult to discover (I initially thought the error was in my testing) it was trivial
to fix. 

Bug Report From Shaine Afzal

***************************************
Bugs in Kyle's code, username collikyl*
***************************************

According to the tests I created I was able to identify 2 bugs. The first
bug I found was in the play_village function. The village card is supposed to 
draw a card, however the number of cards in the player's hand did not increase. 
When I ran the test it indicated that the expected number of cards in the hand
was 6 but the actual number of cards in the hand was 5.

Response:
This is not a bug. The Village card draws one card and discards one card The handCount of the player playing the village card is therefore handCount+1-1=handCount which indicates that there should be no increase or decrease to handCount. However,
in an edge case where handCount = 1 and the village card is the only card in the hand this would produce an error because it would try to discard a card at handPos = -1. This is representive of a bug that discards the wrong card, not a bug that incorectly
alters handCount. To fix this I reverted my change in the village function I wrote.

On line 708 pre-bug fix it reads 		discardCard(handPos-1, currentPlayer, state, 0); //attempts to discard wrong card.
On line 708 post-bug fix it reads 		discardCard(handPos, currentPlayer, state, 0); 

The 2nd bug that I found was in the fullDeckCount function. This function should show
the total amount of cards, but does not do so accurately. When I ran the test the 
expected number of cards in the deck was 23 but the actual output was 0.

Response: 
This is not a bug. I believe that there was a misinterpretation of the functionality of fullDeckCount. fullDeckCount should return the number of cards in all piles of a specific card, not the total cardCount in all piles.
As such, if fullDeckCount were to be called for a card that doesn't exist in a deck, the count would appropriately return 0.

It is important to note that fullDeckCount does not iterate through the playedCard pile. However, because fullDeckCount is used to calculate total score at the end of the game and nothing else it should not need to iterate through the playedPile as all
cards should be in the deck,discard,or hand. 

Bug Report From Jack Holkeboer

	Bug 1: 
********************************************************************************
*** Adventurer does not always give player two treasure cards ***
********************************************************************************
Look in unittestresults.out for the following line:
---- Did player 1 receive two treasure cards?
Pre: 3	Post: 7
Failed.
You'll notice that when the test was run for player 1, the treasure count 
goes up by 4 instead of 2.  However, this test passes when it is run for player 0:
---- Did player 0 receive two treasure cards?
Pre: 3	Post: 5
Passed.
Here is the code of the test:
        printf("---- Did player %d receive two treasure cards?\n", player);
        printf("Pre: %d\tPost: %d\n",preTreasureCount,postTreasureCount);
        if (preTreasureCount + 2 == postTreasureCount) {
            printf("Passed.\n");
            testsPassed++;
        } else {
            printf("Failed.\n");
        }
        testsRun++;
To fix this, you'd need to figure out why there would be a scenario when adventurer 
awards more than 2 treasure cards.
How to reproduce: Run my tests (make unittestresults.out), or play adventeurer for player 1 on a clean game.


Response: This is not a bug. Adventurer does produce a bug but it's not this. The test code used to test my function is incorrect. I had to examine Jack's test code as I could not reproduce this error. Please note the following test code from Jack.

int main() {
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};    
    int testsRun = 0, testsPassed = 0, i, preTreasureCount = 0, postTreasureCount = 0, otherPlayer, player;
    struct gameState testGame;
    struct gameState cleanGame;


    printf("---------- Testing Card: %s --------------\n", TESTCARD);
    for (player = 0; player < 2; player++) {
        initializeGame(2, k, 500, &cleanGame);
        cleanGame.whoseTurn = player;
        memcpy(&testGame, &cleanGame, sizeof(struct gameState));
        for (i = 0; i < testGame.handCount[player]; i++) {
            if (testGame.hand[player][i] == copper || testGame.hand[player][i] == silver
                || testGame.hand[player][i] == gold) {
                preTreasureCount++;   
            }
        }
        cardEffect(adventurer,0,0,0,&testGame,0,0);
        otherPlayer = (player == 1) ? 0 : 1;
        for (i = 0; i < testGame.handCount[player]; i++) {
            if (testGame.hand[player][i] == copper || testGame.hand[player][i] == silver
                || testGame.hand[player][i] == gold) {
                postTreasureCount++;   
            }
        }        

        printf("---- Did player %d receive two cards ?\n", player);
        if (testGame.handCount[player] == cleanGame.handCount[player] + 1) {
            printf("Passed.\n");
            testsPassed++;
        } else {
            printf("Failed.\n");
        }
        testsRun++;
        
        printf("---- Did player %d receive two treasure cards?\n", player);
        printf("Pre: %d\tPost: %d\n",preTreasureCount,postTreasureCount);
        if (preTreasureCount + 2 == postTreasureCount) {
            printf("Passed.\n");
            testsPassed++;
        } else {
            printf("Failed.\n");
        }
        testsRun++;
        
        printf("---- Did player %d discard a card?\n", player);
        if (testGame.discardCount[player] == cleanGame.discardCount[player] + 1) {
            printf("Test Passed.\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        
        // check for game state changes
        printf("---- Was player %d's discard pile unaffected?\n", otherPlayer);
        if (testGame.discardCount[otherPlayer] == cleanGame.discardCount[otherPlayer]) {
            printf("Test Passed.\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        printf("---- Did whoseTurn change?\n");
        if (testGame.whoseTurn == cleanGame.whoseTurn) {
            printf("No, it didn't change.  Test Passed.\n");
            testsPassed++;
        } else {
            printf("Yes, it changed. Test Failed.\n");
        }
        testsRun++;
        printf("---- Did player count change?\n");
        if (testGame.numPlayers == cleanGame.numPlayers) {
            printf("No. Test Passed\n");
            testsPassed++;
        } else {
            printf("Yes. Test Failed.\n");
        }
        testsRun++;
        printf("---- Did outpostPlayed change?\n");
        if (testGame.outpostPlayed == cleanGame.outpostPlayed) {
            printf("No. Test Passed\n");
            testsPassed++;
        } else {
            printf("Yes. Test Failed.\n");
        }
        testsRun++;
        printf("---- Did outpostTurn change?\n");
        if (testGame.outpostTurn == cleanGame.outpostTurn) {
            printf("Test Passed\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        printf("---- Did phase change?\n");
        if (testGame.phase == cleanGame.phase) {
            printf("Test Passed\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        printf("---- Did the other player's deck change?\n");
        if (testGame.deckCount[otherPlayer] == cleanGame.deckCount[otherPlayer]) {
            printf("Test Passed\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
        printf("---- Did played card count increment?\n");
        if (testGame.playedCardCount == cleanGame.playedCardCount + 1) {
            printf("Test Passed\n");
            testsPassed++;
        } else {
            printf("Test Failed.\n");
        }
        testsRun++;
    }
    
    printf("\n---- %d Passed ---- %d Failed ------\n", testsPassed, (testsRun - testsPassed));    
    printf("---------- Testing %s Card Complete ------\n", TESTCARD);
    return 0;
}

The test continues for other categories but at no point does preTreasureCount or postTreasureCount reset.  This means that the values do not reflect appropiate states for treasureCount. As such, preTreasureCount will remain 3 (it counts 3 
for the first iteration (player 0), and adds 0 for the second iteration (player 1)) when it should count 3 for the first iteration, and reset to 0 for the second iteration. PostTreasreCount will count 5 (3 in hand from pre + 2 from adv.) for the first iteration (player 0)
and then add 2 (call to adv) for the second iteration (player 1) for a total of 7 when it should count 5 for the first iteration, reset to 0 and then count 2 for the second iteration. 


Summary: None of the bugs reported by my teammates were actual bugs, rather they were bugs in the testing code or a mintrepretation of the problem. To compensate for this, I've went through and fixed all the card bugs I introduced (a total of 4 fixes) by
reverting my changes. This was fairly easy as I knew what bugs I introduced.

Bug Fixd List:

Smithy Card - No bug was actually introduced during the first refactor for assignment 2. I changed the function to discard first, thinking that discard would put the smithy card into the discard pile thus allowing it to be shuffled back into the deck in the event
drawCount > deckCount but discardCard simply places the smithy card into the played pile. As such, this would not violate a game rule and no fix was needed.

Village Card - Reverted change introduced in assignment 2 that discards wrong card (card to the left of the village card). Now propery discards village card.

Adventurer Card - Reverted change introduced in assignment 2. Now appropiately discards all of tempHand instead of leaving one card remaining in tempHand. This allows the discardTest to pass for every iteration as opposed to only iterations where
the first two cards drawn were treasures.

Salvager Card - Reverted change so that salvager appropriately trashes a card

Additional Fixes:

Adv. Card - Now actually discards itself (moves itself to played pile)


To Be Fixed:
Adv. Card - major error when there are too few (<2) treasure cards in deck although I don't believe it's possible to actually get rid of all treasure cards as cards that trash treasure cards add a treasure card of higher value to the deck.