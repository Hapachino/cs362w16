Bug 1 - scoreFor() function
The first bug I found was in my unit test 3 which was testing the scoreFor function. I implemented
a random tester for this unit test by having it create a random game state and distribute random cards.
I then added the points as they should be added before calling the function and then passed the data
into the function and saw that how I added the points was different from the way the function did. To
do a bit more digging into this bug I commented out the return value for the gardens card and the function
worked as intended, so I would assume that the bug is located in either the gardens card or the fulldeckcount 
function.

Bug 2
My second bug came from testing the smithy card. Fortunately, it was able to catch my own bug I implemented
where it only gave two cards while it expected 3. The error prints out the counts of the cards as well as stating
that the error is in the handcount.

Bug 3 
My third bug came from testing the adventurer card. The hand count and deck count weren't being calculated
properly. This is because of my own bug I implemented where I incremented the value of drawntreasure on each
conditional statement rather than just when the player draws a treasure card.

Bug 4
My fourth bug came from testing the village card. This bug was not implemented by me and it seems to not properly
discard the card. If I was to continue troubleshooting I think I would have to test the discardCard function.


