/*
For the random testers I tried to think of ways to iterate and change the variables every time. I started with the adventurer card,
And my plan was to utilize the game seed for initializing the game as my random element, since it feeds the RNG that determins
how the deck is shuffled. So I designed a loop that basically uses the iterator from 1, 2, 3... n to feed the game and make the
composition of the deck random. This would result in a random testing of the adventurer since we wouldn't know how many cards it has to draw.

Looking at the results: 
I got a total of 19.48% lines executed by testing this one function.
I executed 24.22% of branches

On the related functions  drawcard I only executed 36% of the function. Likewise with initialize game I called it 100% of the runs, but
only hit 83% coverage. In hindsight I don't think using the game seed was enough to make this a truly random test. I should have designed 
my test to create random scenarios of cards in hand, discard, and deck. This would have allowed the game to run different scenarios like 
no cards in hand, shuffling the deck back up, etc.

The bug in adveturer that is preventing the game from discarding non treasure cards. Because of this it is impossible to get 100% coverage on the card itself.
I didn't improve my coverage of adventurer any more. My original test had me hard coding options to get coverage of every branch/path. This test
does execute 10k times on the test, but unless we start considering coverage of related functions I don't know what else can be done to test adventurer.

The main thing is that I need to consider more random elements, I think.


################
For the second test I decided to create a random test for the Steward card. On this test I achieved these results:
20.7% lines executed
Branches executed: 23.74%
For the steward card specifically I got 100% branch coverage.

I designed this test by actually initializing a game and using the iterator as a seed again, but then I ended up filling the hand
and deck with a random numer and random variety of cards so that it was different every time. I then randomsly selected the 3 choice
values neceessary to execute the steward card. Once again I think my main oversight is that I did not consider random generation for
every variable necessary to test. I've found that is the greatest challenge with creating random tests compared to hard coding the values.

I did not encounter any bugs in the Steward code. One challenge I encountered was that I did not consider
the behavior of the discard function correctly. I used a default handpos of 0 for the played card, but when you discard a card at that position
it takes a card from the top of the hand stack. This was a challenge to debug in itself.


################
Overall, my new test suite coverage percenteage is 31.30% coverage.
Branch coverage is 35.73%
Call execution is now 25.26%

This is in comparision to 29.74% with just assignment 3.
Branch coverage went up by 1% from 34.77%. 
And calls executed in assignment 3 were 20%

The improvement is incremental here, but I think I could make the tests far more robust now that I have a taste for building random tests.