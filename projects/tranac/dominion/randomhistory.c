/* 	File: randomhistory.c
	Author: Chris Trana
	CS 362
	
randomtestadventurer.c

For this test I started with the test cases I had written for the previous assignment and added a for loop to 
run multiple itterations and then I started to add piedes to introduce some randomness.  Intially I tried to use the loop shown in lecture to add random info into the game state and then set some critcal informaiton to 
reasonable states but I kept getting seg faults and I couldn't correct the issue so I changed my setup some.  This reduced the randomness of the tests but allowed me to get results.   I did use a random seed to try to inject some more randomness. 

I also tried to refine my tests along the way but with the seg fault issues and time constraints I feel my tests are still not as strong as they could be.  I did break the test cases to account for having no treasure, 1 treasure, or 2 treasure in the deck which would impact how the card worked.

At first my code coverage was inadequate so I increased the number of itterations on my for loop to 100000. This gave me what I felt was good coverage.  

The bugs introduced did cause failed tests with some boundary errors.  




randomtescard.c  great_hall

For this test i didn't use tests I had previosly written instead focusing on a card that I still have in card effects in my dominion.c folder.  I constructed the tests much like my random tests for the adventurer card.  For whatever reasons I didn't have the seg fault issues and I was able to use the code that was introduced in the lectures to randomly create a game state.  When setting critical pieces I also used random selections and I also added a random seed in this test.
My first few tests were ran with 1000 itterations and code coverage wasn't great.  Increasing the itterations on the for loop to 10,000 got better results.

I did have some test fails on handcount and deckcount and got some random negative numbers which could indicate some boundary errors.
*/