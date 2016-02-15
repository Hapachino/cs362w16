Jennifer Frase
CS 362 A4

#DEVELOPEMENT

For this assignment I chose to do the adventurer and smithy cards. When deciding
looking back at the card tests that I had done in the previous assignment I 
found that while the smithy card did not need a lot of change the adventurer
card ended up having to change fairly significantly. The adventurer card tests
took three different scenarios for each set of tests, however in regards to the
random testing this was not possible. As a result, I ended up having to get rid
of 2 of the sets of tests and modifying the last. 

While writing up the random tester I found that I could actually add to the whose turn
is it player's tests by checking that the last card in the discard pile was an 
adventurer card. In addition I could also check that the hand, deck, and discard piles
all added together have the same number of cards as before. In other words if there
are 300 cards total for a player then the player should still have 300 cards
distributed to the hand, deck, and discard piles.

Besides this I left the checks that all other players cards were not messed with in
the tester because these were still valid. Similarily the smithy card tests before
were also all still valid since I was simply making sure that three cards are added
to the hand for the whose turn is it player's deck, and that no other player's cards
were messed with.

In the process of running the tests I did not find any new bugs just that the smithy
doesn't discard the smithy card and so is trashed. However, for the adventurer card
I did actually discover that when all possible 500 cards are in a person's hand,
the function will crash. I was not entirely sure why this was so I went back and
looked at the adventurer case. 

#PROCESS for finding the bug(s) that I couldn't cover in my test without seg fault

I think I may have figured out why this happens 
after checking through the code, because when the deck is empty the adventurer card's
call to drawCard will try to shuffle the discard pile into the deck. But since all
possible cards are in the hand, the discard is also empty. This means that the deck
count will be empty when the drawCard function check so it will return -1. However no
checks for the return value a run so it doesn't fault there. But if the last card
in the hand is not a treasure card then it will get discarded. My test doesn't allow
for treasure cards to be in the hand however, so eventually all the cards in the hand
will be discarded and the function will try to access an index of -1, from the line:

cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];

In this line when all the cards in the hand are discarded the handCount becomes 0, so 
state->handCount[currentPlayer]-1, becomes -1, which is an invalid index, causing
the seg fault. After considering this I could come up with no way for running a test
that will allow for all cards to be in the hand but not seg fault. As a result, I
was forced to reduce the max hand to 1 less. This seems to have worked, but I also
consider this to be a bug.

When there is only 1 treasure and no cards in the deck or discard piles, once again
the drawCard will fail but this adventurer card doesn't check for this so what 
happens is it still checks if the last card in the hand is a treasure card, which of
course it is since it is the card just drawn. This means that that 1 treasure card
will be counted as the second treasure card. While this is not accurate, it does
allow for the game to continue, so in a way it works despite being a bug. Once
again though I am not entirely sure how I would make a check for this since it
really needs to be a check in the adventurer case itself.

#CODE COVERAGE

For both the smithy and adventurer random tests the code coverage was acceptable
since it covered as much as the cards could since some tests were always failed or
never failed. In both cases there were bugs so my end test passed statement also
never executed. In regards to dominion.c the tests were only testing 2 switch cases
so the fact that it only covered 23% of the code is not very suprising.

File 'randomtestadventurer.c'
Lines executed:83.51% of 97

File 'randomtestcard.c'
Lines executed:85.71% of 91 

File 'dominion.c'
Lines executed:23.89% of 565
Branches executed:24.70% of 417
Taken at least once:16.79% of 417
Calls executed:12.22% of 90