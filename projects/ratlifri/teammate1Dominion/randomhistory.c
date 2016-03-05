/*
Philip Jones
CS362 - Winter 2016
Instructions: Write up and check in the development of your random testers,
including improvements in coverage and effort to check the correctness of 
your specification, as randomhistory.c. Be detailed and thorough!

~~~~~~~

I wrote random tests for the Feast card and the Adventurer card. I had
already written a somewhat adequate tester for the Adventurer card for the
previous assignment, so I was luckily able to move forward without having
to write it from scratch-- just using modifications to get more of a "random"
test. Similarly, I was able to find a base of how exactly to produce a
random test and apply it to both the Adventurer and Feast cards. 

The development of the adventurer card gave me the most trouble, interestingly,
even though I had a base. This was because of a segfault I accidentally 
introduced into it via a non-exiting for loop. Because so much of the game's
data is used in the adventurer card, I had to ensure a number of random values
were generated-- determining the deck, discard, hands, and other counts were
within the expected range yet still random. Additionally for the Adventurer,
the deck had to have a random number of coin cards (gold, silver, and bronze)
as they are essential to the card functionality. An issuecould occur when 
there are no coin cards available-- the function could run into an infinite 
loop, constantly looking for what isn't there. 

For the Feast card, I did similar work with the randomness of the game state--
ensuring all possible random values were accounted for, while staying within
the realm of expected results. One issue I ran into was the possibility of
a card being too expensive for the card-pick phase of Feast-- if that is the
case, the loop would have to reject that offer and try for a different card.

The coverage for both is as follows:

File 'randomtestadventurer.c'
Lines executed:96.74% of 92
Branches executed:100.00% of 40
Taken at least once:92.50% of 40
Calls executed:96.30% of 27
randomtestadventurer.c:creating 'randomtestadventurer.c.gcov'

File 'randomtestcard.c'
Lines executed:89.53% of 86
Branches executed:100.00% of 42
Taken at least once:78.57% of 42
Calls executed:96.43% of 28
randomtestcard.c:creating 'randomtestcard.c.gcov'

Only three lines weren't executed in the randomAdventurer test, which accounts
for the nearly-100% execution rate. The lines that didn't execute were
'failsafe' lines-- making sure that if an unexpected output was encountered,
there would be a statement to catch it. The same occurred in the randomFeast
test, except for there were more possible chances for unexpected outcomes--
hence the slightly lower percentage of total lines executed. There still is 
work to be done on it, though, looking at the percentage of taken at least
once-- 78% is probably too low for a satisfying confirmation that the coverage
is good.

*/