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

After this, I turned up the number of tests to 1,000,000.  This test takes 5-10 seconds.  I do not think it makes sense to
make the number of tests higher.  I am confident that it tests all possibilities and that there are not any bugs for that card.

