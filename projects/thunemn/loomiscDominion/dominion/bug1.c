/*
Filename:	bug1.c
Author:		Chris Loomis
Created:	1/31/2016
Last Mod:	1/31/2016

Firstly, I must say it was fun looking over the data and carefully deducing if the bug was with the dominion code, or due
to faulty logic in my tests.  I managed to find cases of both.

unittest1.c for shuffle() passed, though it is a weak test which I will expound upon in coverage1.c

unittest2.c for updateCoins() passed, though it is a weak test which I will expound upon in coverage1.c

unittest3.c for isGameOver() found a small bug on a boundary case.  For the game to be over it needs precisely 0 province cards to end.
I tested it with -1 and it will not end.  This is an absurd case, as I do not believe there is a way for that value to ever be less
than 0.  At the same time however, it is easy to change "== 0" to " < 1" which will have the same functionality, and also cover this
unusual circumstance.

unittest4.c for drawCard() passed it's tests when it did not have to shuffle.  However when I set the deckCount to 0 and called drawCard()
this made it call shuffle which caused my tests to fail.  I understand why the deckCount is different.  It is a pointer to the array that
is the player's deck.  The deck array always holds all the cards that player has, and the pointer incrementing makes it act as though
that player is drawing.  So after a shuffle, the deckCount should be 0.  I do not understand why the handCount is not incrementing.  On
a freshly initialized game, the player has 5 cards in hand.  Setting the deckCount to 0 will cause it to reshuffle and in a way add cards
illegally to the deck.  I assume this may cause some issues later as those duplicate cards are discarded, but that is out of bounds for
this test.  So after the shuffle, the player then draws a card incrementing his hand count.  The test is reporting this is not happening.
I believe this is due to the way drawCard() acts after a shuffle.  It uses the discardCount, which under normal circumstances would be the
equal to all cards the player has.  Since we are calling this on a fresh game where we have tricked the program to think it's deckCount 
is 0, it resets the deckCount to the discardCount, which is also 0.  This causes the rest of the logic to misbehave.

cardtest1.c for card Smithy failed.  It failed due to the bug I introduced last week.  The bug causes 4 cards to be drawn.  

cardtest2.c for card Adventurer failed.  Adventurer should draw 2 cards (2 new treasure), but also discard 1 card (Adventurer) leaving
the player with 1 more card in hand than when he started.  I noticed this a couple weeks ago while trying to understand how this dominion
code worked.  It is probably my biggest criticism that there is a lack of consistency between the way different card effects resolve, and
most of it has to due with discarding the played card.

cardtest3.c for Village failed.  The discard issue expressed previously in cardtest2.c is present here also.  My test also caught the bug
I introduced last week, which is the card only grants one more action rather than 2.

cardtest4.c for Council Room failed.  Like Village, it is due to the card not being discarded and the bug I introduced last week. This
bug has the active player draw a 5th card in the loop where only the inactive players should draw their card.  Code could be refactored
to have the active player draw 3, then loop all players draw once.  This would mean the active player would have drawn the 4 cards for
Council Room.  This differs as to it's current implementation which has the active player draw 4, then has all over players draw one.
*/