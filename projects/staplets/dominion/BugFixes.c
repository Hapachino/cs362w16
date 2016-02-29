Shaun Stapleton
CS 362
Assignment 5
BugFixes.c

Fix all the bugs that are found in your code.. First fix the bugs that your teammate found then 
fix the bugs that you introduced. Use GDB to debug your code and fix it. Provide a documentation file 
to discuss which bugs you fix and mention your code changes. Provide a documentation file BugFixes.c. 
In case your teamates already fixed the bugs and you cannot  find out any bugs, Find out the version 
they just submitted for assignment 2 and use that version. It will give you better practice with git 
repository and repository history.


From Robin Lin's report:
scoreFor Function:
Robin reported that there was a bug in the total's for the scoreFor function. I did some debugging and eventually
found that the dominion.c file was counting the score for the discardCount cards twice and never counting over the
deckCount cards in each players hand. I fixed this bug in dominion.c.

smithy Card:
Robin found my bug that I set up about adding an extra card when the Smithy is played. I fixed it and I have
the details under bugs I fixed.

Great_Hall and Village Card:
Robin reported that there was an extra action being added with each of these cards however when I looked
into it it appears that the cards themselves do not decrement the actions so when she would call cardEffect the
number would be off. However in the dominion.c code, there is a function PlayCard which calls cardEffect
and will handle the decrement. I'm sure this works without error in the game since we aren't calling cardEffect
as a stand alone function then. I did not make any adjustments to the code for these.


From Faye Yao's report:
Village Card:
Faye noted that there was an error with the the number of buys being added for the her tests. However in her tests,
she is using a pointer to assign the expected number and it updates it's buys along with G.numBuys so when she
thinks it's two off, it's actually just adding two on top of the two it got from G.numBuys when the card was played.
Additionally looking at dominion.c the function is explicitly only adding two.

Faye also reported a bug about the played cards not changing after the card is played. This was due to my trash flag
bug that I put into the code. I fixed this and it's noted under bugs I fixed below.

Adventurer Card:
Faye reported that the adventurer card is not discarded from the hand successfully. Per my own testing and the code,
I know that this is an incorrect test. Faye does a lot of randomization with her game state's and I believe this bug
and others are incorrectly picked up from it.

Faye reported the buys and cards played is once again incorrect. I believe this is the same error from code that
is mentioned in the Village card. Looking at the dominion code and my own tests I have run on the game state confirms
my beliefs that there isn't a bug.

Feast Card:
Faye found the bug I placed in the Feast card and how it can create an infinite loop. I fixed this and it's noted under 
bugs I fixed below. 

Smithy Card:
Faye found my bug that I set up about adding an extra card when the Smithy is played. I fixed it and I have
the details under bugs I fixed.

ScoreFor Function:
Faye reported that the estate card never returns the proper score. From my own testing, I believe this to be incorrect.
I think Faye may have found the same bug as Robin but due to her randomized testing the oracle she created did
not provide her with the appropriate failure error. 

Faye reported that the gardens card in scoreFor is incorrect and I reviewed the fullDeckCount function and made
a change so that it will return the number of cards in the deck and not the number of one specific card like I
had originally thought.


Bug's I fixed that I introduced or found myself:

Remodel Card:
I fixed the bug that is causing the cardEffect call to fail by making the total cost of choice1 + 2 be the highest
value that choice2's card cost can be.

Adventurer Card:
I re-added the check on if the silver card is drawn during the card drawing process. This
will correctly place the silver card in the temp hand and update the drawntreasure again.

Smithy Card:
I fixed the size variable and set its value of 4 back to 3. The smithy card will once again pull 3 cards.

Council_Room Card:
I fixed the for loop so that it increments 4 times again and draws 4 cards. I also changed the trash
flag in the discardCard function call back to 0 so that the card will be placed in the discard pile and
not trashed.

Feast Card:
I reset the value of the supply count for choice1 card back to be <= 0 instead of 1. This will
accurately tell the user when a particular supply card is no longer available.

Village Card:
I changed the trash flag in the discardCard function call back to 0 so that the card will be placed 
in the discard pile and not trashed.