{\rtf1\ansi\ansicpg1252\cocoartf1404\cocoasubrtf340
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
\margl1440\margr1440\vieww16240\viewh18140\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 Myles Chatman\
CS 362 - Software Engineering II\
Assignment 5\
2/28/2016\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 \
\pard\tx560\tx1120\tx1680\tx2240\tx2800\tx3360\tx3920\tx4480\tx5040\tx5600\tx6160\tx6720\pardirnatural\partightenfactor0

\b \cf0 \CocoaLigature0 Teammate1 (waddelto):\

\b0 There were two bugs in the adventurer card based on the player drawing excessive treasure cards and having\
excessive cards in there deck. When tests ran successfully, they needed to be refactored to cover all aspects\
on the behavior of the cards.
\b \
\

\b0 \ul Adventurer\ulnone \
\
Execution Results:\
	Testing Card: Adventurer\
	cardtest2: cardtest2.c:38: testAdventurerCard: Assertion `postDeckCount - preDeckCount == 2` failed.\
	Abort (core dumped)\
\
GDB Results:\
	Testing Card: Adventurer\
	cardtest2: cardtest2.c:38: testAdventurerCard: Assertion `postDeckCount - preDeckCount == 2` failed.\
\
	Program received signal SIGABRT, Aborted.\
	0x00000035ffc32625 in raise () from /lib64/libc.so.6\
\
Debugging Steps:\
	Set a breakpoint at line 38: (gdb) b 38\
	Display the code: (gdb) list\
	Display value of postDeckCount: (gdb) print postDeckCount\
							   $1 = 462\
	Display value of preDeckCount: (gdb) print preDeckCount\
							    $2 = 459\
\
Bug Fix:\
	The issue lies within the variable postDeckCount having a different of three compared to\
	preDeckCount. Taking a look at the function adventureEffect, there is a problem with the while loop.\
\
	while (drawntreasure <= 2)\
\
	The adventurer card allows the current player to draw cards until they receive two treasure cards.\
	drawnTreasure increments by one when the player draws a copper, silver, or gold card. This means\
	that drawnTreasure will equal to three. The player draws cards and discards cards that are not treasures.\
	At the end of the turn, they received a total of three treasure cards. The fix is to change the while loop to:\
\
	while (drawntreasure < 2)\
\
	I also ran a test with randomtestadventurer code and I ran into issues with the program getting stuck while\
	executing the test. So I had to reduce the size number of tests. Results were exactly the same as the previous\
	test.\
\
\pard\tx560\tx1120\tx1680\tx2240\tx2800\tx3360\tx3920\tx4480\tx5040\tx5600\tx6160\tx6720\pardirnatural\partightenfactor0
\cf0 \ul \ulc0 Smithy\ulnone \
	Execution Results:\
		Testing Card: Smithy\
		Player\'92s Beginning Hand Count = 5\
		Final Hand Count = 6, Expected Hand Count = 7\
		cardtest1: cardtest1.c:40: testSmithyCard: Assertion `memcmp(&G2, G1, sizeof(struct gameState)) == 0` failed.\
		Abort (core dumped)\
	GDB Results:\
		Testing Card: Smithy\
		Player\'92s Beginning Hand Count = 5\
		Final Hand Count = 6, Expected Hand Count = 7\
		cardtest1: cardtest1.c:40: testSmithyCard: Assertion `memcmp(&G2, G1, sizeof(struct gameState)) == 0` failed.\
		Program received signal SIGABRT, Aborted\
	Debugging Steps:\
		Set a breakpoint at line 40: (gdb) b 40\
		Display the code: (gdb) list\
		Display the struct G2: (gdb) print G2\
						  $1 = \'85\'85. playedCardCount = 0\
		Display the struct G1: (gdb) print G1.playedCardCount\
						  $2 = 1\
	Bug Fix:\
		This test was tough to debug because I basically only tested this card based on the deckCount\
		because the player draws three cards but adds two to the deck. I had to think a bit creative to catch\
		a bug for this case. I basically reinforced a bug that I implemented into this test to get an assertion failure\
		using:\
\
		assert(memcmp(&G2, G1, sizeof(struct gameState)) == 0\
\
		When printing the gameState G2, a ton of variables and their values were printed to the screen. In a case where we\
		could be dealing with a much larger structure or even a larger program, locating a bug like this could be even tougher\
		but thankfully it was simple to catch an issue with the struct because of the last output that showed playedCardCount.\
		All played cards should return a value of one for playedCardCount. I refactored the test to increment the playedCardCount\
		to equal one for gameState G1.\
\
		\

\b Teammate2(solisj):\
\

\b0 \ul Adventurer
\b \ulnone \

\b0 	Execution Results:\
		Testing Card: Adventurer\
		cardtest2: cardtest2.c:37: testAdventurerCard: Assertion `postDeckCount - preDeckCount == 2` failed.\
		Abort (core dumped)\
	GDB Results:\
		Test Card: Adventurer\
		cardtest2: cardtest2.c:37: testAdventurerCard: Assertion `postDeckCount - preDeckCount == 2` failed.\
		Program received signal SIGABRT, Aborted.\
		0x0000003ec7432625 in raise () from /lib64/libc.so.6\
	Debugging Results:\
		Set a breakpoint at line 37: (gdb) b 37\
		Display the code: (gdb) list\
		Display variables in assertion: (gdb) print postCount\
							       $1 = 56\
							       (gdb) print preCount\
							       $2 = 55\
		Bug Fix:\
			We can see that there is an issue with the amount of cards being drawn from the current player. Taking a\
			look at the function playAdventurer, the variable drawntreasure is initialized to one, so when he program \
			reaches the while loop, it will only execute once and update the drawntreasure to a value of one. The value\
			should begin at one because the while loop should execute only twice.\

\b \

\b0 \ul Smithy\
	\ulnone Execution Results:\
		Testing Card: Smithy\
		Player\'92s Beginning Hand Count = 5\
		Final Hand Count = 6, Expected Hand Count = 7\
		cardtest1: cardtest1.c:40: testSmithyCard: Assertion `memcmp(&G2, G1, sizeof(struct gameState)) == 0` failed.\
		Abort (core dumped)\
	GDB Results:\
		Testing Card: Smithy\
		Player\'92s Beginning Hand Count = 5\
		Final Hand Count = 6, Expected Hand Count = 7\
		cardtest1: cardtest1.c:40: testSmithyCard: Assertion `memcmp(&G2, G1, sizeof(struct gameState)) == 0` failed.\
		Program received signal SIGABRT, Aborted\
	Debugging Steps:\
		Set a breakpoint at line 40: (gdb) b 40\
		Display the code: (gdb) list\
		Display the struct G2: (gdb) print G2\
						  $1 \'85.. hand = \{\{4,4,1,4,4,4, -1, 0\}\
		*Its important to pay attention to variables that would be affected by playing the smithy card.\
		* Variables hand, deck, and handCount should update so values should be identical between states.\
		Display the struct G1: (gdb) print G1.hand\
						   $2 = \{\{4, 4, 1, 4, 4, 0\}\}\
		* Although values are not identical, this looks to be okay because the card in hand that reads -1 is a discarded card.\
						  (gdb) print G1.deck\
		* G1 deck and G2 deck returned identical values.\
						  (gdb) print G1.handCount\
						    $3 = \{7, 0, 0, 0\}\
\
		G2  returned a hand count with \{6, 0, 0, 0\}. This means that gameState G2 didn\'92t draw three cards because of the\
		different in the first index between both gameStates.\
	Bug Fix:\
		The initialization in the for loop is incorrect. It was set to a value of one:\
\
		for (i = 1; i < 3; i++)\
\
		was changed to:\
\
		for (i = 0; i < 3; i++)\
		I had to go through each member variable in the struct and compare the values to see any anomalies.\
		But the test I had implement was enough to figure out there was a bug. Using gdb, I was able to trace\
		the bug.\
\
\ul Village\
	\ulnone Execution Results:\
		Testing Card: Village\
		cardtest4: cardtest4.c:40: testVillage: Assertion `memcmp(&G2, G1, sizeof(struct gameState)) == 0` failed.\
		Abort (core dumped)\
\
	GDB Results:\
		Testing Card: Village\
		assert(memcmp(&G2, G1, sizeof(struct gameState)) == 0);\
\
	Debugging Steps:\
		Set a breakpoint at line 40: (gdb) b 40\
		Display the code: (gdb) list\
		* Because the card is based on number of actions, we can compare those values in the gamestates G1 and G2\
		Display the struct G1\'92s number of actions: (gdb) print G1.numActions\
										 $1 = 1938863405\
		Display the struct G2\'92s number of actions: (gdb) print G2->numActions\
										 $2 = 1938863404\
\
		Bug Fix:\
			The variable numActions is a random arbitrary value but we can see that the value of G2 had only updated\
			by two but G1 updated by a value of three. G1 should have only received two cards. In the function, playVillage\
			the statement:\
\
			state->numActions = state->numActions + 3\
\
			was changed to:\
\
			state->numActions = state->numActions + 2
\b \
\
chatmanm:\

\b0 It was not necessary to execute the files I created bugs for. I went back and made the changes to the code that\
contained bugs reported by both of my teammates. The bugs they reported were very accurate to what I had\
implemented and a couple were discovered that I did not implement.\

\b \

\b0 \ul Adventurer\ulnone \
\
Bug Fix:\
	The current player drew too many treasure cards resulting in receiving twice an many cards instead of two.\
	In the function playAdventurer, the statement:\
\
	drawntreasure+=2;\
\
	was changed to:\
\
	drawntreasure++;\
\
\ul Smithy\ulnone \
\
Bug Fix:\
	If the current player played this card, the player only drew two cards instead of three. In the function playSmithy,\
	the for loop:\
\
	for (i = 1; i < 3; i++)\
\
	was changed to:\
\
	for (i = 0; i < 3; i++)\
\
\ul Salvager\ulnone \
\
Bug Fix:\
	The issue was this card was not considered as a trash card when the current player made the decision to trash. The\
	card ended up as a played card. In the function playSalavager, the function call:\
\
	discardCard(choice1, currentPlayer, state, 0)\
\
	was changed to:\
\
	discardCard(choice1, currentPlayer, state, 1)\
\
\ul GreatHall\ulnone \
Bug Fix:\
	The current player received too many actions when playing this card. In the function playGreatHall, the statement:\
\
	state->numActions += 2\
\
	was changed to:\
\
	state->numActions++\
\
\
\ul Minion\ulnone \
Bug Fix:\
	The action of this card doesn\'92t affect the opponents but it does affect the current player that played the card.\
	In the function playMinion, the condition statement:\
\
	if (i == currentPlayer)\
\
	was changed to:\
\
	if (i != currentPlayer)\
\
}