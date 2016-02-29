Teammate #1: Jennifer Frase

Bug #1 -
In testing adventurer card a bug was found.
When especially there is no card on a player's deck, there is a big discrepancy between expected and test results.
As shown below in testing result, first three iterations have set the player's deck empty.
Some discrepancies were also found in the number of cards on the deck when the deck was not empty.
It seems that a bug related to card count on the deck exists.


Testing adventurer card...

Iteration #1 ......
expected    deck cnt: 360
tested      deck cnt: 357
expected discard cnt: 1
tested   discard cnt: 4
Iteration #2 ......
expected    deck cnt: 289
tested      deck cnt: 301
expected discard cnt: 19
tested   discard cnt: 7
Iteration #3 ......
expected    deck cnt: 414
tested      deck cnt: 451
expected discard cnt: 46
tested   discard cnt: 9
Iteration #4 ......
Iteration #5 ......
Iteration #6 ......
Iteration #7 ......
Iteration #8 ......
Iteration #9 ......
Iteration #10 ......

Testing adventurer card done...


/***********************************************************************************/


Bug #2 -
In testing smithy card a discrepancy was found in the card counts on the hand.
One card on the hand is short against the expected number of cards on the hand.
It appears that one extra card was discarded unnecessarily.


Testing smithy card...

Iteration #1 ......
expected    hand cnt: 404
tested      hand cnt: 403
Iteration #2 ......
expected    hand cnt: 132
tested      hand cnt: 131
Iteration #3 ......
expected    hand cnt: 315
tested      hand cnt: 314
Iteration #4 ......
expected    hand cnt: 395
tested      hand cnt: 394
Iteration #5 ......
expected    hand cnt: 27
tested      hand cnt: 26
Iteration #6 ......
expected    hand cnt: 351
tested      hand cnt: 350
Iteration #7 ......
expected    hand cnt: 249
tested      hand cnt: 248
Iteration #8 ......
expected    hand cnt: 439
tested      hand cnt: 438
Iteration #9 ......
expected    hand cnt: 63
tested      hand cnt: 62
Iteration #10 ......
expected    hand cnt: 237
tested      hand cnt: 236

Testing smithy card done...


/***********************************************************************************/
/***********************************************************************************/


Teammate #2: Charles Hardes

Bug #1 -
In testing adventurer card a discrepancy was found in the card counts on the deck and discarded cards.
First four iterations have set the player's deck empty.
When especially the deck was not empty, the number of discarded cards is one less than that of the expected results.
It appears that one extra card needs to be discarded.


Testing adventurer card...

Iteration #1 ......
expected    deck cnt: 427
tested      deck cnt: 440
expected discard cnt: 13
tested   discard cnt: 0
Iteration #2 ......
expected    deck cnt: 226
tested      deck cnt: 233
expected discard cnt: 13
tested   discard cnt: 5
Iteration #3 ......
expected    deck cnt: 36
tested      deck cnt: 30
expected discard cnt: 9
tested   discard cnt: 14
Iteration #4 ......
expected discard cnt: 194
tested   discard cnt: 193
Iteration #5 ......
expected discard cnt: 418
tested   discard cnt: 417
Iteration #6 ......
expected discard cnt: 456
tested   discard cnt: 455
Iteration #7 ......
expected discard cnt: 284
tested   discard cnt: 283
Iteration #8 ......
expected discard cnt: 340
tested   discard cnt: 339
Iteration #9 ......
expected discard cnt: 204
tested   discard cnt: 203
Iteration #10 ......
expected discard cnt: 405
tested   discard cnt: 404

Testing adventurer card done...


/***********************************************************************************/


Bug #2 -
In testing smithy card a discrepancy was found in the card which was represented in integers at a given hand position.
It seems that a card at a different or wrong hand position was discarded.
Bug can be related to the hand position variable.


Testing smithy card...

Iteration #1 ......
expected card at hand pos 61: 24
tested   card at hand pos 61: 14
Iteration #2 ......
expected card at hand pos 49: 0
tested   card at hand pos 49: 5
Iteration #3 ......
expected card at hand pos 129: 16
tested   card at hand pos 129: 11
Iteration #4 ......
expected card at hand pos 116: 21
tested   card at hand pos 116: 4
Iteration #5 ......
expected card at hand pos 59: 8
tested   card at hand pos 59: 22
Iteration #6 ......
expected card at hand pos 113: 14
tested   card at hand pos 113: 18
Iteration #7 ......
expected card at hand pos 24: 0
tested   card at hand pos 24: 9
Iteration #8 ......
expected card at hand pos 72: 19
tested   card at hand pos 72: 3
Iteration #9 ......
expected card at hand pos 114: 23
tested   card at hand pos 114: 22
Iteration #10 ......
expected card at hand pos 211: 20
tested   card at hand pos 211: 5

Testing smithy card done...
