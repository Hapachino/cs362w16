Bug #1 -
In testing adventurer card a bug was found.
A top card drawn from hand was not checked if it is copper.
Also if the top drawn card is a treasure card (copper, silver, or gold), then the variable drawntreasure was incremented by two.
These caused discrepancies in the number of cards on the deck and hand as well as that of discarded cards as shown below.


Testing adventurer card...

Iteration #1 ......
expected    deck cnt: 95
tested      deck cnt: 91
expected discard cnt: 3
tested   discard cnt: 8
expected    hand cnt: 409
tested      hand cnt: 408
Iteration #2 ......
expected    deck cnt: 122
tested      deck cnt: 129
expected discard cnt: 10
tested   discard cnt: 4
expected    hand cnt: 297
tested      hand cnt: 296
Iteration #3 ......
expected    deck cnt: 3
tested      deck cnt: 16
expected discard cnt: 16
tested   discard cnt: 4
expected    hand cnt: 89
tested      hand cnt: 88
Iteration #4 ......
expected discard cnt: 286
tested   discard cnt: 287
expected    hand cnt: 244
tested      hand cnt: 243
Iteration #5 ......
expected    deck cnt: 71
tested      deck cnt: 63
expected discard cnt: 418
tested   discard cnt: 427
expected    hand cnt: 443
tested      hand cnt: 442
Iteration #6 ......
expected    deck cnt: 66
tested      deck cnt: 71
expected discard cnt: 320
tested   discard cnt: 316
expected    hand cnt: 214
tested      hand cnt: 213
Iteration #7 ......
expected    deck cnt: 444
tested      deck cnt: 474
expected discard cnt: 296
tested   discard cnt: 267
expected    hand cnt: 26
tested      hand cnt: 25
Iteration #8 ......
expected discard cnt: 356
tested   discard cnt: 357
expected    hand cnt: 488
tested      hand cnt: 487
Iteration #9 ......
expected    deck cnt: 42
tested      deck cnt: 57
expected discard cnt: 491
tested   discard cnt: 477
expected    hand cnt: 350
tested      hand cnt: 349
Iteration #10 ......
expected    deck cnt: 218
tested      deck cnt: 219
expected    hand cnt: 263
tested      hand cnt: 262

Testing adventurer card done...


For fixing the bugs checking if the drawn card is copper was added.
And if the drawn card is a treasure card, increment the drawntreasure variable by one.


while (drawntreasure < 2) {
	if (state->deckCount[currentPlayer] <1) { //if the deck is empty we need to shuffle discard and add to deck
		shuffle(currentPlayer, state);
	}
	drawCard(currentPlayer, state);
	cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]; //top card of hand is most recently drawn card.

	/* BUG INTRODUCED */
	//if (cardDrawn == silver || cardDrawn == gold) // BUG INTRODUCED
	if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
		//drawntreasure = drawntreasure + 2; // BUG INTRODUCED
		drawntreasure++;
	else {
		temphand[z] = cardDrawn;
		state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one)
		z++;
	}
}
while (z-1 >= 0) {
	state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z-1]; // discard all cards in play that have been drawn
	z--;
}


/***********************************************************************************/


Bug #2 -
In testing smithy card card counts on the deck and hand for the next player have changed, which should not happen.
This is only supposed to affect the current player not the next player.


Testing smithy card...

Iteration #1 ......
expected    deck cnt for next player: 188
tested      deck cnt for next player: 187
expected    hand cnt for next player: 348
tested      hand cnt for next player: 349
Iteration #2 ......
expected    deck cnt for next player: 272
tested      deck cnt for next player: 271
expected    hand cnt for next player: 139
tested      hand cnt for next player: 140
Iteration #3 ......
expected    deck cnt for next player: 188
tested      deck cnt for next player: 187
expected    hand cnt for next player: 333
tested      hand cnt for next player: 334
Iteration #4 ......
expected    deck cnt for next player: 336
tested      deck cnt for next player: 335
expected    hand cnt for next player: 250
tested      hand cnt for next player: 251
Iteration #5 ......
expected    deck cnt for next player: 110
tested      deck cnt for next player: 109
expected    hand cnt for next player: 165
tested      hand cnt for next player: 166
Iteration #6 ......
expected    deck cnt for next player: 444
tested      deck cnt for next player: 443
expected    hand cnt for next player: 383
tested      hand cnt for next player: 384
Iteration #7 ......
expected    deck cnt for next player: 442
tested      deck cnt for next player: 441
expected    hand cnt for next player: 342
tested      hand cnt for next player: 343
Iteration #8 ......
expected    deck cnt for next player: 284
tested      deck cnt for next player: 283
expected    hand cnt for next player: 304
tested      hand cnt for next player: 305
Iteration #9 ......
expected    deck cnt for next player: 368
tested      deck cnt for next player: 367
expected    hand cnt for next player: 157
tested      hand cnt for next player: 158
Iteration #10 ......
expected    deck cnt for next player: 256
tested      deck cnt for next player: 255
expected    hand cnt for next player: 96
tested      hand cnt for next player: 97

Testing smithy card done...


In order to fix the bug, remove drawCard() for the next player.


//+3 Cards
for (i = 0; i < 3; i++)
	drawCard(currentPlayer, state);

/* BUG INTRODUCED */
//drawCard(currentPlayer+1, state); // BUG INTRODUCED

//discard card from hand
discardCard(handPos, currentPlayer, state, 0);


/***********************************************************************************/


Bug #3 -
In testing village card a discrepancy was found in the number of actions for the game.
This only happens when the hand position is on top of the hand.
It appears that the number of actions was incremented by one more than it should be.

Testing village card...

Iteration #1 ......
Iteration #2 ......
Iteration #3 ......
Iteration #4 ......
expected number of actions: 8
tested   number of actions: 9
Iteration #5 ......
expected number of actions: 10
tested   number of actions: 11
Iteration #6 ......
expected number of actions: 12
tested   number of actions: 13
Iteration #7 ......
Iteration #8 ......
Iteration #9 ......
Iteration #10 ......

Testing village card done...

In order to fix the bug, remove checking the hand position and simply increment the number of actions by two.


//+1 Card
drawCard(currentPlayer, state);

/* BUG INTRODUCED */
//if (handPos == (state->handCount[currentPlayer] - 1)) //+3 Actions // BUG INTRODUCED
	//state->numActions = state->numActions + 3; // BUG INTRODUCED
//else //+2 Actions // BUG INTRODUCED
	state->numActions = state->numActions + 2;
			
//discard played card from hand
discardCard(handPos, currentPlayer, state, 0);


/***********************************************************************************/


Bug #4 -
In testing great hall card a discrepancy was found in the number of actions for the game.
It appears that one extra action was added.


Testing great_hall card...

Iteration #1 ......
expected number of actions: 1
tested   number of actions: 2
Iteration #2 ......
expected number of actions: 2
tested   number of actions: 3
Iteration #3 ......
expected number of actions: 3
tested   number of actions: 4
Iteration #4 ......
expected number of actions: 4
tested   number of actions: 5
Iteration #5 ......
expected number of actions: 5
tested   number of actions: 6
Iteration #6 ......
expected number of actions: 6
tested   number of actions: 7
Iteration #7 ......
expected number of actions: 7
tested   number of actions: 8
Iteration #8 ......
expected number of actions: 8
tested   number of actions: 9
Iteration #9 ......
expected number of actions: 9
tested   number of actions: 10
Iteration #10 ......
expected number of actions: 10
tested   number of actions: 11

Testing great_hall card done...


In order to fix the bug, increment the number of actions by one instead of two.


//+1 Card
drawCard(currentPlayer, state);

/* BUG INTRODUCED */
//state->numActions = state->numActions + 2; // BUG INTRODUCED
state->numActions++;

//discard card from hand
discardCard(handPos, currentPlayer, state, 0);


/***********************************************************************************/
/***********************************************************************************/


Running GDB results

bash-4.1$ ls
BugsInTeammate0.out  dominion_helpers.h  Makefile   rngs.c  testcard
dominion.c         interface.c   playdom.c  rngs.h  testcard.c
dominion.h         interface.h   player.c   rt.c
bash-4.1$ gcc -g testcard.c dominion.c rngs.c -lm
bash-4.1$ ls
a.out              dominion.h            interface.h  player.c  rt.c
BugsInTeammate0.out  dominion_helpers.h  Makefile     rngs.c    testcard
dominion.c         interface.c   playdom.c    rngs.h    testcard.c
bash-4.1$ gdb a.out
GNU gdb (GDB) Red Hat Enterprise Linux (7.2-83.el6)
Copyright (C) 2010 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from /nfs/stak/students/c/choiy/courses/cs362/hw5/member0/a.out...done.
(gdb) r adventurer
Starting program: /nfs/stak/students/c/choiy/courses/cs362/hw5/member0/a.out adventurer
warning: the debug information found in "/usr/lib/debug//lib64/ld-2.12.so.debug" does not match "/lib64/ld-linux-x86-64.so.2" (CRC mismatch).

warning: the debug information found in "/usr/lib/debug/lib64/ld-2.12.so.debug" does not match "/lib64/ld-linux-x86-64.so.2" (CRC mismatch).

warning: the debug information found in "/usr/lib/debug//lib64/libc-2.12.so.debug" does not match "/lib64/libc.so.6" (CRC mismatch).

warning: the debug information found in "/usr/lib/debug/lib64/libc-2.12.so.debug" does not match "/lib64/libc.so.6" (CRC mismatch).

Testing adventurer card...

Iteration #1 ......
expected    deck cnt: 85
tested      deck cnt: 115
expected discard cnt: 34
tested   discard cnt: 5
expected    hand cnt: 408
tested      hand cnt: 407
Iteration #2 ......
expected    deck cnt: 236
tested      deck cnt: 253
expected discard cnt: 17
tested   discard cnt: 1
expected    hand cnt: 211
tested      hand cnt: 210
Iteration #3 ......
expected    deck cnt: 420
tested      deck cnt: 413
expected discard cnt: 5
tested   discard cnt: 13
expected    hand cnt: 145
tested      hand cnt: 144
Iteration #4 ......
expected    deck cnt: 99
tested      deck cnt: 107
expected discard cnt: 420
tested   discard cnt: 413
expected    hand cnt: 228
tested      hand cnt: 227
Iteration #5 ......
expected    deck cnt: 213
tested      deck cnt: 217
expected discard cnt: 182
tested   discard cnt: 179
expected    hand cnt: 287
tested      hand cnt: 286
Iteration #6 ......
expected    deck cnt: 140
tested      deck cnt: 144
expected discard cnt: 232
tested   discard cnt: 229
expected    hand cnt: 479
tested      hand cnt: 478
Iteration #7 ......
expected    deck cnt: 140
tested      deck cnt: 158
expected discard cnt: 168
tested   discard cnt: 151
expected    hand cnt: 80
tested      hand cnt: 79
Iteration #8 ......
expected    deck cnt: 23
tested      deck cnt: 26
expected discard cnt: 346
tested   discard cnt: 344
expected    hand cnt: 23
tested      hand cnt: 22
Iteration #9 ......
expected discard cnt: 279
tested   discard cnt: 280
expected    hand cnt: 187
tested      hand cnt: 186
Iteration #10 ......
expected    deck cnt: 209
tested      deck cnt: 223
expected discard cnt: 232
tested   discard cnt: 219
expected    hand cnt: 131
tested      hand cnt: 130

Testing adventurer card done...
/***************************************************************/

Program exited normally.
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.166.el6_7.7.x86_64
(gdb) r smithy
Starting program: /nfs/stak/students/c/choiy/courses/cs362/hw5/member0/a.out smithy
warning: the debug information found in "/usr/lib/debug//lib64/ld-2.12.so.debug" does not match "/lib64/ld-linux-x86-64.so.2" (CRC mismatch).

warning: the debug information found in "/usr/lib/debug/lib64/ld-2.12.so.debug" does not match "/lib64/ld-linux-x86-64.so.2" (CRC mismatch).

warning: the debug information found in "/usr/lib/debug//lib64/libc-2.12.so.debug" does not match "/lib64/libc.so.6" (CRC mismatch).

warning: the debug information found in "/usr/lib/debug/lib64/libc-2.12.so.debug" does not match "/lib64/libc.so.6" (CRC mismatch).

Testing smithy card...

Iteration #1 ......
expected    deck cnt for next player: 458
tested      deck cnt for next player: 457
expected    hand cnt for next player: 205
tested      hand cnt for next player: 206
Iteration #2 ......
expected    deck cnt for next player: 473
tested      deck cnt for next player: 472
expected    hand cnt for next player: 289
tested      hand cnt for next player: 290
Iteration #3 ......
expected    deck cnt for next player: 5
tested      deck cnt for next player: 4
expected    hand cnt for next player: 22
tested      hand cnt for next player: 23
Iteration #4 ......
expected    deck cnt for next player: 338
tested      deck cnt for next player: 337
expected    hand cnt for next player: 489
tested      hand cnt for next player: 490
Iteration #5 ......
expected    deck cnt for next player: 355
tested      deck cnt for next player: 354
expected    hand cnt for next player: 126
tested      hand cnt for next player: 127
Iteration #6 ......
expected    deck cnt for next player: 243
tested      deck cnt for next player: 242
expected    hand cnt for next player: 65
tested      hand cnt for next player: 66
Iteration #7 ......
expected    deck cnt for next player: 192
tested      deck cnt for next player: 191
expected    hand cnt for next player: 174
tested      hand cnt for next player: 175
Iteration #8 ......
expected    deck cnt for next player: 363
tested      deck cnt for next player: 362
expected    hand cnt for next player: 499
tested      hand cnt for next player: 500
Iteration #9 ......
expected    deck cnt for next player: 438
tested      deck cnt for next player: 437
expected    hand cnt for next player: 377
tested      hand cnt for next player: 378
Iteration #10 ......
expected    deck cnt for next player: 247
tested      deck cnt for next player: 246
expected    hand cnt for next player: 444
tested      hand cnt for next player: 445

Testing smithy card done...
/***************************************************************/

Program exited normally.
(gdb) r village
Starting program: /nfs/stak/students/c/choiy/courses/cs362/hw5/member0/a.out village
warning: the debug information found in "/usr/lib/debug//lib64/ld-2.12.so.debug" does not match "/lib64/ld-linux-x86-64.so.2" (CRC mismatch).

warning: the debug information found in "/usr/lib/debug/lib64/ld-2.12.so.debug" does not match "/lib64/ld-linux-x86-64.so.2" (CRC mismatch).

warning: the debug information found in "/usr/lib/debug//lib64/libc-2.12.so.debug" does not match "/lib64/libc.so.6" (CRC mismatch).

warning: the debug information found in "/usr/lib/debug/lib64/libc-2.12.so.debug" does not match "/lib64/libc.so.6" (CRC mismatch).

Testing village card...

Iteration #1 ......
Iteration #2 ......
Iteration #3 ......
Iteration #4 ......
expected number of actions: 8
tested   number of actions: 9
Iteration #5 ......
expected number of actions: 10
tested   number of actions: 11
Iteration #6 ......
expected number of actions: 12
tested   number of actions: 13
Iteration #7 ......
Iteration #8 ......
Iteration #9 ......
Iteration #10 ......

Testing village card done...
/***************************************************************/

Program exited normally.
(gdb) r great_hall
Starting program: /nfs/stak/students/c/choiy/courses/cs362/hw5/member0/a.out great_hall
warning: the debug information found in "/usr/lib/debug//lib64/ld-2.12.so.debug" does not match "/lib64/ld-linux-x86-64.so.2" (CRC mismatch).

warning: the debug information found in "/usr/lib/debug/lib64/ld-2.12.so.debug" does not match "/lib64/ld-linux-x86-64.so.2" (CRC mismatch).

warning: the debug information found in "/usr/lib/debug//lib64/libc-2.12.so.debug" does not match "/lib64/libc.so.6" (CRC mismatch).

warning: the debug information found in "/usr/lib/debug/lib64/libc-2.12.so.debug" does not match "/lib64/libc.so.6" (CRC mismatch).

Testing great_hall card...

Iteration #1 ......
expected number of actions: 1
tested   number of actions: 2
Iteration #2 ......
expected number of actions: 2
tested   number of actions: 3
Iteration #3 ......
expected number of actions: 3
tested   number of actions: 4
Iteration #4 ......
expected number of actions: 4
tested   number of actions: 5
Iteration #5 ......
expected number of actions: 5
tested   number of actions: 6
Iteration #6 ......
expected number of actions: 6
tested   number of actions: 7
Iteration #7 ......
expected number of actions: 7
tested   number of actions: 8
Iteration #8 ......
expected number of actions: 8
tested   number of actions: 9
Iteration #9 ......
expected number of actions: 9
tested   number of actions: 10
Iteration #10 ......
expected number of actions: 10
tested   number of actions: 11

Testing great_hall card done...
/***************************************************************/

Program exited normally.
(gdb)
