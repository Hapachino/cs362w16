Adventurer:
The hardest part about testing this card was getting my bugs worked out in how I was testing. This was a challenge because at first I was trying to make sure that I had an adventurer in my hand, which was causing issues with how the test ran. 
In order to test this, I created a random game state, and then assigned a random hand, deck, and discard to each player, which was also a random number, and then randomly chose a player. 
In this case, I was limiting my hand count to 1/10 of the normal size, in order to favor some of the lower numbers, since they would be edge cases. On top of that, the chance of a player having up to the max hand of 500 cards is nearly impossible. Next, I wanted to first focus on testing if the deck and discard pile were the correct numbers. In order to make sure I was correctly getting the number of cards that the player was drawing, I used a loop to print out where the cards should stop, and then what the loop within dominion.c was working with. After I managed to get these to be the same, I was confident that I was at least using the correct number when calculating my cards in each pile. 

Due to time restrictions at the moment, I would like to further implement more edge cases comparisons, such as if the deck/discard/hand are at 0 or 1, what is the gamestate in comparison to what it should be, and then other ones such as if the game shuffles, are the cards still going to the correct spot. 

Overall I achieved 100% statement and branch coverage within my function, so even though there are still more failsafe tests I would like to run, because it wasn’t able to catch the bug I implemented (honestly, I’m not sure if it’s possible to find it with random testing), I’m still happy that it’s able to account for 100% of blocks. 

Smithy:
The biggest thing I need to test here, is that the user hand has 2 more cards than it originally did, and that the discard pile is up 1, and the deck is three less. There is no point in doing tests that will never deal with anything being changed within the program. In this case, I think a less is more approach is the way to go. 

One thing to note, is if I was doing unit tests, I would be much more concerned with making sure that if my deck and my edge conditions were met, however this is random testing, it’s meant to ensure that given random inputs, the card continues to work. 

The biggest thing to note, is that I didn’t run thousands of tests, mostly due to the fact that the bug I introduced will always make the program output. (it draws 4 cards, which throws off deck, hand, and discard count.

So my test suite did catchy my bug :D

My coverage was 100% block and branch with the random testing, however my overall coverage went from 22% to 20% when I added the smithy card. This doesn’t make sense to me. 

I did start earlier on this assignment, however this week was crazy, so it got started and then neglected. I'm slowly tending to my little programs more often, however next assignment my goal is to get it done in the first few days. 