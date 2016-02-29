{\rtf1\ansi\ansicpg1252\cocoartf1404\cocoasubrtf340
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
\margl1440\margr1440\vieww33400\viewh18140\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 Myles Chatman\
CS 362 - Software Engineering II\
Assignment 5\
2/28/2016\
\
In order to get the tests working successfully, I needed to refactor my tests to run successfully\
with teammate\'92s 1 and teammate\'92s 2 code. The code below are my initial tests and a comparison\
to the changes that I needed to implement including the bugs discovered:\
\

\b Teammate 1:\

\b0 \

\b Adventurer Card
\b0 \
\
Initial Test:\
\pard\tx866\pardeftab866\pardirnatural\partightenfactor0
\cf0 \CocoaLigature0 	preCount = countTreasure(p, G1);	\
	postCount = countTreasure(p, G1);\
	assert(postCount - preCount) == 2);\
\
	preCount would equal to a random number based on how many treasures are contained\
	in the current player\'92s deck. After calling the function adventureEffect, we run through the\
	necessary actions of the adventurer count where afterwards, postCount receives those\
	post actions. Asserting the different between postCount and preCount should always result\
	int two.\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 \CocoaLigature1 \
\
Refactored Test:\
\
	Add variables and initialize in the testAdventurerCard function:\
\pard\tx866\pardeftab866\pardirnatural\partightenfactor0
\cf0 \CocoaLigature0     	\
	preDeckCount = G1->handCount[p];\CocoaLigature1 \
	\CocoaLigature0 postDeckCount = G1->handCount[p];\
	assert(postDeckCount - preDeckCount == 2);\
\
	This is very similar to the previous implementation of preCount and postCount.\
\
	The refactored function adventureEffect had a minor reconstruction of the code to simplify the\
	execution of the code. It removes the unnecessary while loop that discards card and discards\
	card through each iteration when a treasure card is not drawn.\
\
Initial Code:\
\
	temphand[z]=cardDrawn;\
	state->handCount[currentPlayer]\'97;\
	z++;\
\
	while(z-1>=0)\
		state->discard[currentPlayer][state->discardCount[currentPlayer]++=temphand[z-1];\
		z=z-1;\
\
Refactored Code:\
\
	state->discard[currentPlayer][state->discardCount[currentPlayer]++] = cardDrawn;\
	state->handCount[currentPlayer]\'97;\
\
	I believed there was the possibility of a bug existing in this refactored code but the tests were still\
	successful.\
\
Bug1:\
\
	When I first wrote a test for this card, I didn\'92t consider about the deckCount changing in value.\
	Of course it will change as the player continues to draw cards and discards them. But the\
	fact that the player draws three treasure cards instead of two it is much more essential to just\
	check the deckCount before and after and confirm that the player only received two cards. This\
	will confirm that he truly drew two treasure cards because all other cards would have been discarded.\
\
Bug2:\
\
	The current player receives three treasures card which gives that player an advantage of amount of\
	currency they posses. This can really create a disadvantage especially if the card they drew was a gold\
	card.\
\
\pard\tx866\pardeftab866\pardirnatural\partightenfactor0

\b \cf0 Smithy\
\
\pard\tx866\pardeftab866\pardirnatural\partightenfactor0

\b0 \cf0 Initial Test:\
	G1->handCount[p] = (G1->handCount[p] + actionCard) - 1;\
	assert(G2.handCount[p] == G1->handCount[p];\
\
	This test makes sure that the post actions after playing the smithy grant the user with\
	three cards. \
\
Refactored Test:\
	G1->playedCardCount - 1;\
	assert(memcmp(&G2, G1, sizeof(struct gameState)) == 0\
\
Bug3:\
	The only bug I found in this card was after the current player finished their turn, the playedCardCount didn\'92t increment by one.\
	The value remained at 0 and this was due to the card being regarded as a trashed card rather than a played card.\
\
\pard\tx866\pardeftab866\pardirnatural\partightenfactor0

\b \cf0 Teammate 2:\
\
Adventurer\
\
\pard\tx866\pardeftab866\pardirnatural\partightenfactor0

\b0 \cf0 Initial Test:\
	preCount = countTreasure(p, G1);	\
	postCount = countTreasure(p, G1);\
	assert(postCount - preCount) == 2);\
Refactored Test:\
	preDeckCount = G1->handCount[p];\CocoaLigature1 \
	\CocoaLigature0 postDeckCount = G1->handCount[p];\
	assert(postDeckCount - preDeckCount == 2);\
\
	The results are identical when I ran tests again teammates 1 code. But the issue was due to an initialization of drawn treasure\
	equal to 1.\
\
Bug1:\
	Treasure count, deckCount was incorrect for the current player because the while loop only executed once. Player missed\
	out on opportunity to receive more currency.
\b \
\
Smithy\
\

\b0 Initial Test:\
	G1->handCount[p] = (G1->handCount[p] + actionCard) - 1;\
	assert(G2.handCount[p] == G1->handCount[p];\
\
	This test makes sure that the post actions of playing the smithy grants the user with\
	three cards.\
\
Refactored Test:\
	G1->playedCardCount - 1;\
	assert(memcmp(&G2, G1, sizeof(struct gameState)) == 0\
\
Bug2:\
\pard\tx866\pardeftab866\pardirnatural\partightenfactor0

\b \cf0 	
\b0 There was a bug where the current player didn\'92t receive the correct number of actions after they\
	finished their turn. 
\b \
\
Village\
\
\pard\tx866\pardeftab866\pardirnatural\partightenfactor0

\b0 \cf0 Initial Test:\
	drawCard(p, &G2);\
	G2.numActions += 2;\
	discardCard(handPos, p, &G2, 0);\
	assert(memcmp(&G2, G1, sizeof(struct gameState)) == 0);\
\
Refactored Test:\
	N/A\
\
Bug3:\
	Current player received one extra actions after playing this card but should have been limited to two. This caused an inconsistency\
	in the game since the player would have an extra decision to play another card.}