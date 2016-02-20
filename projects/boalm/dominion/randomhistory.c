First error in the code I found from adventurer random test.  It fails when the number of treasure cards
is 0.  I hit this the first time I set the number of repetitions to 100.  It had passed on every other time
I had run the test.  I knew the probability of getting 0 treasure cards was enough to run into eventually, but it 
did not happen until I started jacking up the number of repetitions.

To allow for longer tests with more repetitions I fixed the bug.  It was caused by faulty logic that would
not exit the adventurer section, unless two treasures were drawn.  I fixed this by exiting the loop of 
drawing cards if drawCard returns -1.  It will do so, if there are no more cards to draw from the deck or 
the discard.  It will shuffle the discard into the deck if necessary.

To test I fixed the bug, I made the loop run 100 times with reporting on every time and did a spot check
to make sure it looked like everything was ok.  I had not gotten any failures previously with one card drawn
and I wanted to make sure it was passing.  There were several examples of 1 card passing successfully in this report.

After this, I turned up the number of tests to 1,000,000.  This test takes ~10 seconds.  I do not think it makes sense to
make the number of tests higher.  I am confident that it tests all possibilities and that there are not any bugs for that card.

sea_hag:
It looks like sea_hag did not have the discardCard method called at the end to put
it into the playedCard pile.

The -- that sea_hag is using, will actually decrement the actual value of the variable it is used on.  
When looking for one less than the value of the count of a pile of cards, - 1 should be used.  This will
not change the value of the variable.

sea_had was decrementing the size of the deck by 1 and not increasing it back when adding curse.  I fixed this.

sea_hag was adding a card to discard, when the deck was empty.  Fixed this.

Now it works and runs 1,000,000 times successfully. 



Above are some notes I made while running the tests and debugging the implementation of the cards.

Coverage results from Assn3:

File 'dominion.c'
Lines executed:37.22% of 634
Branches executed:50.62% of 405
Taken at least once:32.35% of 405


adventurer random tester:

File 'dominion.c'
Lines executed:40.51% of 632
Branches executed:51.60% of 405
Taken at least once:35.06% of 405


sea_hag random tester: 

File 'dominion.c'
Lines executed:21.51% of 637
Branches executed:24.82% of 407
Taken at least once:15.72% of 407

