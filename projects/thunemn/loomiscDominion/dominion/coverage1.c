/*
Filename:	coverage1.c
Author:		Chris Loomis
Created:	1/31/2016
Last Mod:	1/31/2016

My tests were good in the sense that few lines within the functions called were missed.  There are a few exceptions, such as my
updateCoins() test not testing Gold coins ever.

drawCard() has missed coverage which is directly related to bugs it stirred up reported in bug1.c.  I used a freshly initialized
game, set it's deckCount to 0 to trigger a shuffle when drawCard() was called, and this resulted in logic errors as the 
discardCount was 0 as nothing had been discarded yet.  The code relies on itself, so when my tests (not just drawCard()) introduced
absurd game instances things began to misbehave understandibly.

Of the 4 cards, only Adventurer contained some missed lines of code.  It never required a shuffle, as it has only been run from
a freshly initialized game, so it is impossible for it to ever require a shuffle (even if the first 3 cards drawn are the estates
the next 2 must then be copper).  Due to this, the only lines of code not run have to do when the player goes through a lot of 
cards and would have to discard them.  This never occurred.

In the future it will be better if I take the time to generate random instances of the game, that make logical sense (such as no
deckCount 0 and discardCount 0), to test.  I will also need to develop helper functions independent of the code that calculate
what the correct responses are.  As an example, for updateCoins() I will need a separate function to calc what the answer should
be so I can make sure the dominion code calcs it correctly.  With this I will be able to run many distinct instances of all 
the tests, producing more data, which will either find more errors, or at the least show more convincingly that the code is working
as intended.
*/