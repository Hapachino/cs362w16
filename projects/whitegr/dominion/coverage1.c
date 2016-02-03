//Coverage tests for Greg White
Below is a summary of my coverage reports. Overall I had a real hard time and struggled a lot wasting time
on very trivial things. Anyway the unit tests do not do a great job of testing all of the problems that could
arise. If i had more time I would add more tests to better check the status of the various arrays as they relate to function being tested. Also I would
implement more complex checks that utilize loops to check many combinations. I did however add some random testing of cards in the card tests with 
multiple players and the function tests do an OK job of testing the business rules and logic of the functions. 
On some occasions I get deep into the arrays of the game to determine if everything is functioning OK.

Looking below at the numbers I am surprised they are so high. (They may be slightly different from the make file as I was making changes to the test at the 
last minute.) The tests do confirm that the program works in general and that a lot of different pathways
were taken when the tests are run as a group. To get a higher count I kind of feel that I would need to test more functions or cards in general. The program is 
based around functions so I think there is a lot of logic to be tested in unchecked functions as shown in the Calls executed statistic. Also the taken at least once
and Branches executed statistics indicates I hit a lot of branches but missed all of the pathways.  

I did find one thing that looked like a bug in the calculate score function for the garden card. One problem with unit testing though is that of course there could 
be bugs in your unit tests so you definitely can't relly on thing 100%.

As for gcov. I should have more throughly used the gcov command DURING the testing process and not at the end. Using it while authoring
the unit test would have definitely helped me out making sure I at least attempting to test all of the logic.

From the gcov file:
I also got a 100% coverage on smithy - function smithyCard called 20 returned 100% blocks executed 100%

I missed some things on the discard which was used by most of the functions I tested-    
80: 1246:int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
       80: 1246-block  0
        -: 1247:{
        -: 1248:	
        -: 1249:  //if card is not trashed, added to Played pile 
       80: 1250:  if (trashFlag < 1)
       80: 1250-block  0
branch  0 taken 50% (fallthrough)
branch  1 taken 50%

I missed some here because I didn't test this function: 
function updateCoins called 6 returned 100% blocks executed 82%

I didn't test this one at all but I used it a lot which show the dangers of this stuff:
function shuffle called 20 returned 100% blocks executed 100%



Summary:
Lines executed:41.46% of 562
Branches executed:48.19% of 415
Taken at least once:38.31% of 415
Calls executed:31.31% of 99
Creating 'dominion.c.gcov' 

Functions:
1. scoreFor()
	Lines executed:5.87% of 562
	Branches executed:13.01% of 415
	Taken at least once:13.01% of 415
	Calls executed:3.03% of 99

2. BuyCard()
	Lines executed:20.11% of 562
	Branches executed:25.06% of 415
	Taken at least once:14.70% of 415
	Calls executed:12.12% of 99

3. gainCard()
	Lines executed:18.15% of 562
	Branches executed:17.35% of 415
	Taken at least once:13.98% of 415
	Calls executed:8.08% of 99

4. isGameOver()
	Lines executed:17.08% of 562
	Branches executed:17.35% of 415
	Taken at least once:13.98% of 415

Cards:

1. Smithy:
	File 'dominion.c'
	Lines executed:10.85% of 562
	Branches executed:6.27% of 415
	Taken at least once:5.06% of 415
	Calls executed:6.06% of 99

2. Adventurer
	Lines executed:11.03% of 562
	Branches executed:7.23% of 415
	Taken at least once:6.75% of 415
	Calls executed:6.06% of 99

3. Council Room
	Lines executed:5.34% of 562
	Branches executed:2.89% of 415
	Taken at least once:1.93% of 415
	Calls executed:4.04% of 99


4. Steward Card
	Lines executed:9.96% of 562
	Branches executed:5.78% of 415
	Taken at least once:4.34% of 415
	Calls executed:8.08% of 99


