
Jack Holkeboer
Oregon State University
holkeboj@onid.oregonstate.edu
CS362
Assignment 5



****************************
BUGS FOUND BY TEAMMATES
****************************


************************************************
Bugs found by Teammate #1 Kyle Collins (ONID collikyl)
***********************************************

******************************
Bug #1: Adventurer does not correctly move itself to the played pile.
************************************************************


******************************
Bug #2: When Adventurer is played, there is only one card being drawn 
    and added to the players hand while in other cases no cards are 
    drawn at all despite treasure being in the fullDeck.
*********************************************************************



************************************************
Bugs found by Teammate #2 Shaine Afzal (ONID afzals)
***********************************************


Bug #1: The fullDeckCount may not be correct, the expected amount was 25 but the result was 0.
**********
Upon closer inspection this is actually not a bug but rather a problem with my teammates test code.
Take a look at the file projects/azfals/unittest1.c:

    // from projects/azfals/unittest1.c
	initializeGame(numPlayers, k, seed, &G);

	printf("Testing fullDeckCount\n");
	
	x = rand() % 10;
	y = rand() % 20;
	z = rand() % 10;
	
	G.handCount[0] = x;
	G.deckCount[0] = y;
	G.discardCount[0] = z;
	
	rtotal = x + y + z;
	ftotal = fullDeckCount(0, smithy, &G);
	
	if(rtotal != ftotal)
	{
		printf("Test failed. Result: %d, Expected: %d\n", rtotal, ftotal);
	}
	else
	{
		printf("Test passed\n");
	}

This test is initializing a game, and then assigning random values for the handCount, deckCount, and discardCount
for player 0.  Then he calls the fullDeckCount function for player zero and the smithy card.

The problem is that fullDeckCounts return value is not based on the counts of each pile, but rather 
how many occurences of the card in question are in the piles.  If we take a look at the code of 
fullDeckCount, we can see that the return count is only incremented if the card parameter is found in 
that pile.  So the return value in this case will be the total number of smithy cards in that pile.  The 
problem with this test is that it checks the total number of cards of any type, rather than the total number
of smithy cards.  His test is returning 0 because there are no smithy cards in the hand, deck, or discard piles. 


Bug #2: In the Smithy card, when the handPos passed to the function
is 2 there were only 4 cards in the players hand after running the function. However when there 
are other numbers passed in for handPos there are 7 cards in the players hand after running the function.
**********
This is a bug that I introduced.  If you take a look at my refactor.c file, youll see that I 
purposefully made the Smithy card behave incorrectly if the handPos passed is 2.  This 
is the code that causes the bug:
        
    for (i = 0; i < 3; i++) {
        if (handPos != 2) {}
            drawCard(currentPlayer, state);
        }
    }

I fixed the bug by removing the "if (handPos != 2)" condition, so drawCard() will be called
for any handPos.

****************************
BUGS THAT I INTRODUCED
****************************