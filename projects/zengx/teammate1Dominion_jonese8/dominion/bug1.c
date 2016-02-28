CS362 - Assignment 3 - Emmalee Jones
02/02/2016

1. unittest1.c - updateCoins
No bugs found

2. unittest2.c - scoreFor
There appears to be a bug where the wrong number of deck count is being used for 
scoreFor.  The bug only shows if the number of cards between discardCount and
deckCount is different. 

3. unittest3.c - getWinner
No bugs found
The test has a failure but it is the same bug from scoreFor because getWinner
calls scoreFor.

4. unittest4.c - isGameOver

No bugs found

5. cardtest1.c - smithy
The smithy card appears to change the next players number of cards, which is a bug I introduced 
in assignment 2.

6. cardtest2.c - adventurer
The adventurer card appears to not read copper treasure cards a bug I introduced in assignment 2. 
In addition there appears to be no boundary on negative cards which the bug in assignment
2 has caused also.

7. cardtest3.c - council_room 
The council_room card appears to count the number of buys incorrectly.  A bug I introducted  
introduced in assignment 2.

8. cardtest4.c - great_hall
No bugs found