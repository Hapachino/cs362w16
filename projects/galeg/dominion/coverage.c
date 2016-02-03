/*
Assignment #3 - Gerald Gale

COVERAGE:

BASIC STATS:
File 'dominion.c'
Lines executed:23.96% of 576
Branches executed:18.23% of 417
Taken at least once:16.07% of 417
Calls executed:12.77% of 94

INDIVIDUAL UNIT TEST STATS:
discardCard()			-	function discardCard called 6490 returned 100% blocks executed 88%
shuffle()				-	function shuffle called 418 returned 100% blocks executed 93%
isGameOver()			-	function isGameOver called 5 returned 100% blocks executed 100%
buyCard()				-	function BuyCardTEST called 202 returned 100% blocks executed 68%
callSmithyCard()		-	function callSmithyCard called 500 returned 100% blocks executed 100%
callAdventurerCard()	-	function callAdventurerCard called 500 returned 100% blocks executed 73%
callVillageCard()		-	function callVillageCard called 500 returned 100% blocks executed 100%
callEmbargoCard()		-	function callEmbargoCard called 5400 returned 100% blocks executed 80%

REVIEW:
In looking back over the results, I am personally surprised how much I learned just from the results of gcov. In addition, 
it is getting easier to see why testing, specifically all of different theoretical methods of testing are so important. 
The data, gives you quantifiable data that you are able to make decisions on compared to using humans for testing. 
I was thinking that in many cases, especially GUI applications, that it would be easier for humans to just do a lot of the testing. 
At least, any major bugs. 

After this though, that is no longer the case. By calling individual functions, and testing their coverage compared to the rest of 
the program, it gives you a good understanding of the proportional amount of use certain areas of the program use. 
This allows you to get a feel for how and where things work and could go wrong. More importantly, it also give you a gauge for 
measuring what the costs of repairs or sales figures going down as a result of problems can be. “OK, we know that this is being called a lot, 
and it’s important to using the application. This breaking could lose us millions of dollars in sales alone. This HAS to work.”

In the results above, the line calls were happening quite a bit, while the branches were pretty low. I wonder how much this would change if humans were playing the game?
I was expecting more branch coverage. I think part of this could be the bugs that were put in for Assignment 2. 
If conditions aren’t being met that lead to other areas of the program, branch coverage could be misleading. 
As for the individual unit tests, isGameOver(), callSmithyCard(), and callVillageCard() all had 100% branch coverage, 
while all the others did not. This shows me that there are likely other areas of application that I need to learn more about. 
If my tests are not hitting all of the possible branches areas the application can go for individual functions, this means 
there are other areas of the ENTIRE application that might not be getting called which need to be. This could help explain the lower
branch coverage in dominion.c. As a reault I would need to work on making better unit tests. 












*/
