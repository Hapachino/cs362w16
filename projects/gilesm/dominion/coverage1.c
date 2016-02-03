CS 362 - Software Engineering II
Assignment 3
Coverage Summary
My final line coverage percentace for dominion.c after running four unit tests and
four card tests was 31.34%. Considering the number of functions available for
testing compared to the 8 that I selected, this seems to be an appropriate number. 
There were several areas of the file not under consideration, so I will give a brief
summary of coverage for each of the functions tested.

For the first function, buyCard, statement coverage is 100%. There are a few areas of
conditional branching which require running the function in multiple ways. This
comes into play in the case of potential failure conditions presented by the function.
The possible failures are if the user is attempting to buy a card without any
remaining buys, if the card supply for that card is empty, or if the player cannot
afford the card. I ran the functioni through testing each of these conditions,
which allowed for full branch coverage, and therefore each line of code executed.
This could be considered path coverage, although there are fairly limited conditions
and no nested conditions to make that task overly challenging. There are some debug
options in this function, but they are ignored for the purposes of testing the final product.

For gainCard, a similar result is achieved by running the function in several ways.
There is an execution of every individual line at least once, which covers statement, 
branch and path coverage. In terms of boundary testing, the primary attribute
to be tested is the toFlag, which is tested with all options that are available
to the user.

For numHandCards, the results are the same. This is a fairly simple function, which
allows for easy execution of each line. Truly revealing testing comes from the
unit tests selected around the game state it effects.

For the updateCoins function, I executed every line, statement, branch, and path.
The path coverage is trivial as there is only one conditional statement. Within
a for loop, there is a conditional statement that checks three possible values for
each of the player's cards. One of my test conditions includes one of each of
the treasure cards in the same hand, which works toward statement coverage as well
as boundary coverage for this particular conditional. I also looked at boundaries
by running a few options for the bonus attribute. Keeping the bonus attribute at
0 allowed for testing other areas, and once they were validated, I was able to
modify the bonus attribute to test that the function processed it accurately.

I tested my function called smithyEffect with complete statement coverage. There is
only one possibility of skipping a line in this function, which is if the for loop
were somehow modified to not iterate at least once. In terms of bounadries, I could
do better with testing more hand positions for the card's placement which could
prove varying results depending on how the called functions are configured.

With adventurerEffect, in analyzing coverage, I see a branch that is not tested.
This branch comes into play if the player's deck is empty, requiring a shuffle
and placement of the discard pile back into the deck. I can easily add a test case
that calls the function with an empty deck to achieve better coverage in this area.
There are lines in a while loop that did not execute, but there seems to be an error
with this part of the code as it doesn't appear possible to access it. This could
be an area that could be analyzed for additional testing.

Village effect is executed with 100% path coverage as there are no conditionals
or branches to take. Boundary testing could be produced better as there is a
handpos attribute. To add to this testing, a handpos that at least includes a
card from the top of the deck, the middle of the deck, and the last card could
help expand on possible results from testing this function in terms of boundary.

The last card test function I did was remodelEffect. Lacking many conditional
statements and branches, this one again lends itself to easily running 100%
path coverage. However, I think in looking at the past few card functions,
I will spend more time thinking of boundary testing on functions with a similar
flat architecture. The lack of branches gives the appearance of simplified testing,
but I see now based on limited line number executions that other possibilities
could be checked with more extreme attribute selections, especially when
these functions call other methods that I haven't tested.
