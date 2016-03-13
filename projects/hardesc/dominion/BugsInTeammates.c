Teammate 1: Jennifer Frase (frasej):

BUGS FOUND:

BUG 1: 4 extra cards drawn from player's deck.
BUG 2: Each other player receives an additional card from their own deck 
BUG 3: Buys are incremented

It seems as though maybe the council_room card is being played instead of the adventurer. There is no indication that any
adventurer code is being ran. After examining several iterations, there are cases where no additional treasure cards are
gained, although 4 cards are always drawn. This indicates that the cards are being randomly drawn and no attempt to find
treausre cards is being made as would be the case when running the adventurer code. 


Sample of one test iteration output:


-------------------------Random Testing adventurer-------------------

adventurer card at k[7] position.
number of players = 3
player playing adventurer = 0
randomizing kingdom cards...

kingdom cards:
	k[0] = 25
	k[1] = 8
	k[2] = 23
	k[3] = 18
	k[4] = 26
	k[5] = 22
	k[6] = 17
	k[7] = 7
	k[8] = 13
	k[9] = 14
initializing game...
numactions = 3
coins = 1
numbuys = 0
whoseTurn = 0
phase = 0

numCardsPlayed = 0

player 0 playing adventurer from handpos 6

player 0:  handCount = 9	deckCount = 15	discardCount = 27
player 1:  handCount = 3	deckCount = 30	discardCount = 454
player 2:  handCount = 5	deckCount = 10	discardCount = 306

copying game state G to testG
calling cardEffect(adventurer, 0, 0, &testG, handPos = 6, &bonus = 0)

TEST 1: DRAW 2 TREASURE CARDS - player has 2 new treasure cards - 1 discard
	handCount = 14, expected = 10	FAIL
	treasureCount = 9, expected = 7	FAIL

TEST 2: CARDS TAKEN FROM DECK/DISCARD - deck + discard has 2 fewer cards 
	discardCount + deckCount = 36; expected = 40	FAIL

TEST 3: PLAYED CARDS PILE - advevnturer card is played 
	playedCardsCount = 1, expected = 1	PASS

TEST 4: NO STATE CHANGE - state remains unchanged in unaffected variables
	Supply Counts:	PASS

	Other Player States:
		Player[1]: 
		testG.hand[1][3] = 0; expected = 7	FAIL

		testG.handCount[1] = 4; expected = 3	FAIL
		testG.deckCount[1] = 29; expected = 30	FAIL
		testG.discardCount[1] = 454; expected = 454	PASS

		Player[2]: 
		testG.hand[2][5] = 1; expected = 24	FAIL

		testG.handCount[2] = 6; expected = 5	FAIL
		testG.deckCount[2] = 9; expected = 10	FAIL
		testG.discardCount[2] = 306; expected = 306	PASS


	numActions = 3; expected = 3	PASS
	numBuys = 1; expected = 0	FAIL
	coins = 1; expected = 1		PASS


----------------------adventurer test complete------------------------


Teammate 2: Yunsik Choi (choiy):

BUGS FOUND:

BUG 1: Player has one extra card in hand
BUG 2: No additional card in played cards pile 

These two faults would actually seem to be the product of one bug, that the adventurer card is not discarded to the played cards pile
after it is played. This is why there is one additional card in the player's hand and a card missing from the played cards pile. Refactoring
of the adventurer test was completed to show that the card at the position the adventurer was played at always remains an adventurer in every 
iteration of the test.

Sample of one test iteration output:


-------------------------Random Testing adventurer-------------------

adventurer card at k[4] position.
number of players = 2
player playing adventurer = 0
randomizing kingdom cards...

kingdom cards:
	k[0] = 25
	k[1] = 26
	k[2] = 19
	k[3] = 10
	k[4] = 7
	k[5] = 24
	k[6] = 15
	k[7] = 17
	k[8] = 14
	k[9] = 18
initializing game...
numactions = 3
coins = 4
numbuys = 0
whoseTurn = 0
phase = 0

numCardsPlayed = 0

player 0 playing adventurer from handpos 0

player 0:  handCount = 1	deckCount = 471	discardCount = 31
player 1:  handCount = 5	deckCount = 8	discardCount = 12

copying game state G to testG
calling cardEffect(adventurer, 0, 0, &testG, handPos = 0, &bonus = 0)

TEST 1: DRAW 2 TREASURE CARDS - player has 2 new treasure cards - 1 discard
	handCount = 3, expected = 2	FAIL
	treasureCount = 2, expected = 2	PASS

TEST 2: CARDS TAKEN FROM DECK/DISCARD - deck + discard has 2 fewer cards 
	discardCount + deckCount = 500; expected = 500	PASS
	Card at adventurer position is still adventurer after played: 	TRUE

TEST 3: PLAYED CARDS PILE - advevnturer card is played 
	playedCardsCount = 0, expected = 1	FAIL

TEST 4: NO STATE CHANGE - state remains unchanged in unaffected variables
	Supply Counts:	PASS

	Other Player States:
		Player[1]: 
		testG.handCount[1] = 5; expected = 5	PASS
		testG.deckCount[1] = 8; expected = 8	PASS
		testG.discardCount[1] = 12; expected = 12	PASS


	numActions = 3; expected = 3	PASS
	numBuys = 0; expected = 0	PASS
	coins = 4; expected = 4		PASS


----------------------adventurer test complete------------------------


