For randomtestadventurer, I first tried randomizing the entire gamestate and running that, just to see what would happen.
This instantly segfaulted. Once I thought about it, I decided there were 2 possible reasons for the segfault:

1. A variable that needed to be positive got initialized with a negative value
2. Somewhere among deckCount and deck, handCount and hand, or discardCount and discard, the numbers didn't line up.

I decided that #2 was the most likely problem given the adventurer card's code, so I added code to randomize the counts
to positive values, and then to give the deck/hand/discard piles the same number of cards as their counts.
Once satisfied here, I ran the code again, but it still segfaulted. So, I checked the code and saw that I was only making
the values good for one player. I upgraded it to fix both players. At this point it was running for a bit and then segfaulting,
instead of crashing immediately, so I added some trace statements and saw that adventurer_card was drawing all the cards from
the deck and then crashing.

I realized here that it must not be drawing any treasure cards, and indeed I realized I forgot to put them in. I added
treasure cards to the k array and compiled again. This time some of the tests completed, but some failed. This was because
in some of the runs, since the deck was put together randomly, sometimes not enough treasure cards would be in the deck.

With this test I might have actually found a bug in the Dominion rules themselves -- undefined behavior!

There are cards which let you get rid of a card altogether, and you might be able to destroy all your treasure cards this way,
causing Adventurer to never draw 3 cards. However, since the game intends for you to have at least 3 treasures at all times,
I modified my test code to add 2 coppers to one side of the deck and 1 to the other, to guarantee that there's at least 3
treasures in the deck. I also set a minimum deck size to avoid any problems there. With this fix, the tests completed
without segfaulting!

In terms of coverage, I was getting 93% adventurer branch coverage at this point. I saw that the shuffle section wasn't getting
called, as a direct result of having plenty of treasure in the deck already of course. I moved the guaranteed treasure to the
discard pile instead of the deck so that it would run out of cards in the deck, shuffle in the discard, and then get the
guaranteed cards, however, running this segfaulted.

I checked what went wrong and found another bug, in the original shuffle code: It never adds the discard pile in! So it gets
called when the deckCount is < 1, then immediately checks to see if the deckCount is <1 and if yes, it returns -1. This means
that it returns -1 every time and actually does nothing at all. Realizing this, I saw that fixing the shuffle function to work
so that I could get 100% coverage in adventurer was beyond the scope of this assignment. Finding these 2 bugs was very helpful though.

Looking over the asserts, both the assert that the discardCount isn't changed fails, which I expected, but also the assert that makes
sure the last two cards in the player's hand are treasures fails as well. I'm not sure why this is, but I added some printfs
(commented out in the final code) in case analysis of the behavior is needed later.


For randomtestcard, I tested the village card. I thought it would be very easy since I had done most of the randomization work in
the adventurer test, but when I ran the same state on village, it segfaulted. I traced the segfault into the discardCard function,
and figured out that the negatively-initiated integer problem I hypothesized in the adventurer test was happening with the playedCard
array. Once I made sure this was positive, the test ran without crashing and with 100% branch coverage of the village card!

In terms of bugs, the random test confirmed the same bugs I already found with the manual testing: player 2 gets 2 actions instead of
1 like it should be.