Shaun Stapleton
CS 362
Assignment 4
randomhistory.c

Write up and check in the development of your random testers, including improvements in coverage and 
effort to check the correctness of your specification, as randomhistory.c. Be detailed and thorough!

randomtestadventurer:
For the adventurer random tester, I fortunately had a great starting place due to my unit test from last week.
I was able to use the main structure of the unit test file, but with some additional work to capture the random
testing of inputs for it. I have checks in place to evaluate much of the game state before and after the call
to adventurer with cardEffect. For example, I check both player one and two's decks, hands, the game treasure
cards, the victory cards and I output an error if it comes up. Because I knew I would be doing 
more volume testing with the random testing, I added a for loop with a testCount variable where I add up successful
and failing iterations of each run through. This provides me with a decent oracle to evaluate what is passing
and the amount that it is. I initially just looped through once to make sure I cleaned up my code and that it
was doing what I hoped. The input that I decided to randomize are the deck cards that will be drawn in to the
players hand whenever the adventurer card is played. I thought that this would allow me to evaluate the card
basically from any point in the game because they could randomly hold any different sequence of cards throughout. 
One thing I did do was make sure I randomly placed two treasure cards at least in the deck each time. This 
would allow it to test and truly let the adventurer function work. Furthermore, I knew that I had created a 
bug that make the adventurer card discard any silver cards in the hand. Once I knew that the function would 
fail gracefully, then I was able to catch errors based on a test of whether treasure cards were discarded. 
I also test the expected discard or hand counts that the player should have after playing the adventurer card.

I was able to see the failure of the card fairly quickly due to the thirty three percent change that each time
a treasure card was pulled it was going to be silver. My program operated as expected and notified me that there
was an error. I then started ramping up the test cases and I currently have it set at 1000 iterations. To my
surprise the card still succeeds at about a 40 percent rate. I expect this is due to the other three deck cards
being randomly generated and that the odds of a treasure card drawn from those are three in twenty seven. From
my coverage review, I saw that I did additionally add more coverage in each area as I suppose was expected.
My lines executed went up from 18.76% to 21.86%. My branches executed went up from 22.89% to 24.34%. My branches
taken at least once went up from 13.98% to 16.14%. And my calls executed went up from 11.00% to 13.00%.

randomtestcard:
For my second card, I decided to use the remodel card as the test case. Similar to the adventurer card, I 
had implemented this card as a test unit a week ago and therefore had the structure in place. I decided to
do a hybrid of the structure between what I had for the unit test and how I approached the adventurer card
for random testing this time. I once again am testing the state of the game before and after in several
areas where I check whether different cards or supply counts were changed. With this card, one large difference
in how I test is that I go through every card in the player's hand each iteration of my "test loop". Therefore, I run
1000 tests once more, but this time I will have 4000 individual test cases that I document throughout. My inputs that
I decided to randomize for remodel were both the choice2 card in cardEffect (card purchased) and the players cards 
in hand for each iteration. I felt like this would provide me with a lot of different input and create the opportunity 
for error catching. As was my situation with the last time I tested remodel, I was aware that there is a flipped > operator 
in the remodel code. This evaluates the choice1 and choice2 backwards. This causes a failure almost every time in the remodel
code as it ends execution right away before remodel does anything. With that in mind I flipped the operator to < while
I tested to make sure I was getting all of my parts correct. With that operator in the correct direction my 4000 test
cases passed. Otherwise they all of course fail.
	
Looking at my coverage results, they were additionally encouraging with this random test card. My lines executed went up 
from 22.89% to 27.02%. However my branches executed stayed the same from 32.05% to 32.05%, which I found interesting since
I was more rigorous with my testing this time. My branches taken at least once did go up from 16.39% to 22.17%
due to this larger amount of tests. And my calls also stayed the same from 14.00% to 14.00%. I checked out the coverage
numbers for when the error is in the remodel code and I found that they were 22.03%, 28.19%, 19.52%, and 10.00% respectively.
This makes sense since the code is jumping out each time before further code is run.

