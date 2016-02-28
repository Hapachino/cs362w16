
Title: Assignment 5 - Bugs found in teammate's program (Note: We are a 2 person team since our 3rd person dropped the course)

Date: 2/23/26          
Reported By:  Jennifer Mendoza
  


Bug 1 Description- isGameOver()
===========
Bug found when setting random piles of 3 to 0. Some pass and some fail, meaning that there is a bug
with one or more of the cards. My test indicates that the bug is when treasure map and/or sea hag is
set to 0. These 2 cards are the source of the bug.


Steps to Produce/Reproduce
--------------------------
Use the following to reproduce error
	G.supplyCount[province]=2;
	G.supplyCount[adventurer]=2;
	G.supplyCount[treasure_map]=0;
	result= isGameOver(&G);
	printf("Game over");
	if (result==1)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}
and/or
	G.supplyCount[province]=2;
	G.supplyCount[adventurer]=2;
	G.supplyCount[sea_hag]=0;
	result= isGameOver(&G);
	printf("Game over");
	if (result==1)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}

	
Expected Results
----------------
When 3 piles are set to 0, isGameOver() should return 1.


Actual Results
--------------
isGameOver returns 0



Bug 2 Description- village card function
===========
Tests fail when checking handCount(decreased instead of increased), deckCount(should have stayed the same), and 
playedCardCount(incorrect increase) for current player.


Steps to Produce/Reproduce
--------------------------
Use the following to reproduce error
	villageCard(1,&G,0);
	printf("Actions = %d, expected = 3", G.numActions);
	if (G.numActions==3)
	{
		printf("....PASS\n");
	}
	else{
		printf("....FAIL\n");
	}

	
Expected Results
----------------
numActions for current player should increase by 2.


Actual Results
--------------
numActions for current player stayed the same.




Bug 3 Description- smithy card function
===========
Tests fail when checking handCount(decreased instead of increased), deckCount(should have stayed the same), and 
playedCardCount(incorrect increase) for current player.

Steps to Produce/Reproduce
--------------------------
Use the following to reproduce error
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	p=1;
	smithyCard(p,post, 0);
	printf("Testing if player 1 handCount increased");
	if (pre.handCount[1]<post->handCount[1])
	{
		printf("....PASSED\n");
		printf("pre: %d, post:%d\n", pre.handCount[1],post->handCount[1]);
	}
	else{
		printf("....FAILED\n");
		printf("pre: %d, post:%d\n", pre.handCount[1],post->handCount[1]);
	}
	printf("Testing if player 1 deckCount remains unchanged");
	if (pre.deckCount[1]==post->deckCount[1])
	{
		printf("....PASSED\n");
		printf("pre: %d, post:%d\n", pre.deckCount[1],post->deckCount[1]);
	}
	else{
		printf("....FAILED\n");
		printf("pre: %d, post:%d\n", pre.deckCount[1],post->deckCount[1]);
	}	
	printf("Testing playedCardCount for player 1.",p);
	if (post->playedCardCount==1)
	{
		printf("....PASSED\n");
		printf("Number of Cards Played = %d, expected = %d\n", post->playedCardCount, 1);
	}
	else{
		printf("....FAILED\n");
		printf("Number of Cards Played = %d, expected = %d\n", post->playedCardCount, 1);	
	}	
	
Expected Results
----------------
deckCount and handcount should have remained the same
playedCardCount should have increased by 1


Actual Results
--------------
handCount decreased instead of increased
deckCount changed
playedCardCount increased by a large amount




Bug 4 Description- adventurer card function
===========
Tests fail when checking current player's handCount (negative), discardCount(increased), and deckCount(decreased).
For my fixed tests, test hits a segmentation fault when calling adventurer card more than once.


Steps to Produce/Reproduce
--------------------------
Use the following to reproduce error
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	p=1;
	adventurerCard(p,post);
	printf("Testing if player 1 handCount increased");
	if (pre.handCount[1]<post->handCount[1])
	{
		printf("....PASSED\n");
		printf("pre: %d, post:%d\n", pre.handCount[1],post->handCount[1]);
	}
	else{
		printf("....FAILED\n");
		printf("pre: %d, post:%d\n", pre.handCount[1],post->handCount[1]);
	}
	printf("Testing if player 1 discardCount remains unchanged");
	if (pre.discardCount[1]==post->discardCount[1])
	{
		printf("....PASSED\n");
		printf("pre: %d, post:%d\n", pre.discardCount[1],post->discardCount[1]);
	}
	else{
		printf("....FAILED\n");
		printf("pre: %d, post:%d\n", pre.discardCount[1],post->discardCount[1]);
	}
	printf("Testing if player 1 deckCount remains unchanged");
	if (pre.deckCount[1]==post->deckCount[1])
	{
		printf("....PASSED\n");
		printf("pre: %d, post:%d\n", pre.deckCount[1],post->deckCount[1]);
	}
	else{
		printf("....FAILED\n");
		printf("pre: %d, post:%d\n", pre.deckCount[1],post->deckCount[1]);
	}
		
	Tests fail when checking current player's handCount (negative), 
	discardCount(increased), and deckCount(decreased).
For my fixed tests, test hits a segmentation fault when calling 
adventurer card more than once.

Expected Results
----------------
handCount should be a positive number
discardCount should have stayed the same
deckCount should have stayed the same


Actual Results
--------------
handCount was negative
discardCount increased
deckCount decreased



Bug 5 Description- feast card function
===========
Test on feastCard seemed like it hit an infinite loop. The test executed but once it called feastCard, the test did 
not stop.

Steps to Produce/Reproduce
--------------------------
Use the following to reproduce error
	int* k=kingdomCards(1,2,3,4,5,6,7,8,9,10);
	G.numPlayers=rand() % 3+1;
	initializeGame(G.numPlayers,k,1000,&G);
	p = rand() % 2+1;
	G.numPlayers=rand() % 3+1;
    G.deckCount[p] = rand() % MAX_DECK;
    G.discardCount[p] = rand() % MAX_DECK;
    G.handCount[p] = rand() % MAX_HAND;
	G.supplyCount[feast]=rand()%10;
	feastCard(p,G,0); <- infinite loop here
	
Expected Results
----------------
Test will execute and display handCount, deckCount, playedCardCount, discardCount, and supplyCount.


Actual Results
--------------
Test ran and does not end after several minutes. I aborted the test.

