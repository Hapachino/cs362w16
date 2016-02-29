/*

teammate1Dominion = Philip Jones
--------------------------------

Smithy Card:

	Bug:  Smithy draws four cards instead of three.

	Description:  Smithy draws one card too many from deck into hand. After play,
	              there is one too many cards in hand, one too few in deck.

	How to Reproduce:
		1. make clean
		2. make cardTest1
		3. cardTest1
	 or
		1. make all   (make all run clean)
		2. cardTest1  (can also review unittestresults.out after make all)


Adventurer Card:

	Bug:  Adventurer remains in hand after play.

	Description:  Adventurer or any card should move from hand to played after
	              being played, but adventurer remains in the hand after play.

	Bug:  Adventurer draws one treasure card instead of two.

	Description:  Adventurer draws one treasure card too few from deck into hand.

	How to Reproduce: 
		1. make clean
		2. make cardTest2
		3. cardTest2
	 or
		1. make all   (make all run clean)
		2. cardTest2  (can also review unittestresults.out after make all)


Mine Card:  *** NOTE - i discovered a testing bug late so this was NOT reported to Philip ***

	Bug:  Mine remains in hand after play.

	Description:  Mine or any card should move from hand to played after
	              being played, but mine remains in the hand after play.

	Bug:  Mine does not convert copper to silver.

	Description:  Mine failed to convert a copper treasure to silver.

	How to Reproduce: 
		1. make clean
		2. make cardTest4
		3. cardTest4
	 or
		1. make all   (make all run clean)
		2. cardTest4  (can also review unittestresults.out after make all)


teammate2Dominion = Cierra Shaw
-------------------------------

Smithy Card:

	Bug:  Smithy draws four cards instead of three.

	Description:  Smithy draws one card too many from deck into hand. After play,
	              there is one too many cards in hand, one too few in deck.

	How to Reproduce:
		1. make clean
		2. make cardTest1
		3. cardTest1
	 or
		1. make all   (make all run clean)
		2. cardTest1  (can also review unittestresults.out after make all)


Adventurer Card:

	Bug:  Adventurer remains in hand after play.

	Description:  Adventurer or any card should move from hand to played after
	              being played, but adventurer remains in the hand after play.

	How to Reproduce: 
		1. make clean
		2. make cardTest2
		3. cardTest2
	 or
		1. make all   (make all run clean)
		2. cardTest2  (can also review unittestresults.out after make all)


Mine Card:  *** NOTE - i discovered a testing bug late so this was NOT reported to Cierra ***

	Bug:  Mine remains in hand after play.

	Description:  Mine or any card should move from hand to played after
	              being played, but mine remains in the hand after play.

	Bug:  Mine does not convert copper to silver.

	Description:  Mine failed to convert a copper treasure to silver.

	How to Reproduce: 
		1. make clean
		2. make cardTest4
		3. cardTest4
	 or
		1. make all   (make all run clean)
		2. cardTest4  (can also review unittestresults.out after make all)


Regarding a quick summary about refactoring and how maintainable my tests are.
There were no changes required for unit tests.
There were minimal changes required for card tests and random tests.
The minimal changes included refactoring for function calls and related variables.


flip1 % diff -ws teammate1Dominion/unittest1.c dominion/unittest1.c
Files teammate1Dominion/unittest1.c and dominion/unittest1.c are identical


flip1 % diff -ws teammate1Dominion/unittest2.c dominion/unittest2.c
Files teammate1Dominion/unittest2.c and dominion/unittest2.c are identical


flip1 % diff -ws teammate1Dominion/unittest3.c dominion/unittest3.c
Files teammate1Dominion/unittest3.c and dominion/unittest3.c are identical


flip1 % diff -ws teammate1Dominion/unittest4.c dominion/unittest4.c
Files teammate1Dominion/unittest4.c and dominion/unittest4.c are identical


flip1 % diff -ws teammate2Dominion/unittest1.c dominion/unittest1.c
Files teammate2Dominion/unittest1.c and dominion/unittest1.c are identical


flip1 % diff -ws teammate2Dominion/unittest2.c dominion/unittest2.c
Files teammate2Dominion/unittest2.c and dominion/unittest2.c are identical


flip1 % diff -ws teammate2Dominion/unittest3.c dominion/unittest3.c
Files teammate2Dominion/unittest3.c and dominion/unittest3.c are identical


flip1 % diff -ws teammate2Dominion/unittest4.c dominion/unittest4.c
Files teammate2Dominion/unittest4.c and dominion/unittest4.c are identical


flip1 % diff -ws teammate1Dominion/cardtest1.c dominion/cardtest1.c
220,221c220
< //    cardEffectSmithy(0, &testG, 3);
<     playSmithy(&testG, 3);
---
>     cardEffectSmithy(0, &testG, 3);


flip1 % diff -ws teammate1Dominion/cardtest2.c dominion/cardtest2.c
221,222c221
< //    cardEffectAdventurer(0, &testG);
<     playAdventurer(&testG);
---
>     cardEffectAdventurer(0, &testG);


flip1 % diff -ws teammate1Dominion/cardtest3.c dominion/cardtest3.c
147d146
<     int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
222,223c221
< //    cardEffectCouncilRoom(0, &testG, 4);
<     cardEffect(council_room, choice1, choice2, choice3, &testG, 4, &bonus);
---
>     cardEffectCouncilRoom(0, &testG, 4);


flip1 % diff -ws teammate1Dominion/cardtest4.c dominion/cardtest4.c
147d146
<     int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
222,225c221
< //    cardEffectMine(0, &testG, 4, copper, silver);
<       choice1 = copper;
<       choice2 = silver;
<     cardEffect(mine, choice1, choice2, choice3, &testG, 4, &bonus);
---
>     cardEffectMine(0, &testG, 4, copper, silver);


flip1 % diff -ws teammate2Dominion/cardtest1.c dominion/cardtest1.c
220,221c220
< //    cardEffectSmithy(0, &testG, 3);
<     mySmithy(&testG, 0, 3);
---
>     cardEffectSmithy(0, &testG, 3);


flip1 % diff -ws teammate2Dominion/cardtest2.c dominion/cardtest2.c
221,222c221
< //    cardEffectAdventurer(0, &testG);
<     myAdventurer(&testG, 0);
---
>     cardEffectAdventurer(0, &testG);


flip1 % diff -ws teammate2Dominion/cardtest3.c dominion/cardtest3.c
147d146
<     int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
222,223c221
< //    cardEffectCouncilRoom(0, &testG, 4);
<     cardEffect(council_room, choice1, choice2, choice3, &testG, 4, &bonus);
---
>     cardEffectCouncilRoom(0, &testG, 4);


flip1 % diff -ws teammate2Dominion/cardtest4.c dominion/cardtest4.c
147d146
<     int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
222,225c221
< //    cardEffectMine(0, &testG, 4, copper, silver);
<       choice1 = copper;
<       choice2 = silver;
<     cardEffect(mine, choice1, choice2, choice3, &testG, 4, &bonus);
---
>     cardEffectMine(0, &testG, 4, copper, silver);


flip1 % diff -ws teammate1Dominion/randomtestadventurer.c dominion/randomtestadventurer.c
16,17c16
< //    r = cardEffectAdventurer(p, post);
<       r = playAdventurer(post);
---
>       r = cardEffectAdventurer(p, post);


flip1 % diff -ws teammate2Dominion/randomtestadventurer.c dominion/randomtestadventurer.c
16,17c16
< //    r = cardEffectAdventurer(p, post);
<       r = myAdventurer(post, p);
---
>       r = cardEffectAdventurer(p, post);


flip1 % diff -ws teammate1Dominion/randomtestcard.c dominion/randomtestcard.c
16,17c16
< //    r = cardEffectSmithy(p, post, pos);
<       r = playSmithy(post, pos);
---
>       r = cardEffectSmithy(p, post, pos);


flip1 % diff -ws teammate2Dominion/randomtestcard.c dominion/randomtestcard.c
16,17c16
< //    r = cardEffectSmithy(p, post, pos);
<       r = mySmithy(post, p, pos);
---
>       r = cardEffectSmithy(p, post, pos);


*/
