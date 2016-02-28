/*File: BugsInTeammates.c
	Author: Chris Trana
	CS 362

****Teammate 1

---cardtest1 - Smithy
refactored code to pass in arguments in correct order.

bugs:

 smithy was not removed from hand
 handcount was not correct
 
---cardtest2 - adventurer
refactored code as adventurer did not return a value indicating how many cards where drawn before getting 
correct treasure amount.  Tests were changed from checking to see if deck count and discard count are correct size to just checking to see if they changed from the control state.

bugs;
 
 handcount was not correct
 
---cardtest3 - Village
refactored code to pass in arguments in correct order.

bugs:

 discardcount was not correct
 
---cardtest4 - council_room
refactored code to run test for council_room which is still in cardEffect.

bugs:

 discardcount failed
 

---unittest1 - getCost
no refactoring required

bugs:

 no bugs found

 
---unittest2 - isGameOver
no refactoring required

bugs:

 no bugs found 
 
 
---unittest3 - shuffle
no refactoring required

bugs:

 no bugs found 
 
 
---unittest4 - drawCard
no refactoring required

bugs:

 when deckcount gets to 0 drawcard failed to return 0, handcount failed, and deckcount failed.
 
 

---randomtest - adventurer
refactored code as adventurer did not return a value indicating how many cards where drawn before getting 
correct treasure amount.  Tests were changed from checking to see if deck count and discard count are correct size to just checking to see if they changed from the control state.

bugs:

 current players handcount fails (becomes negative) and treasure count is not correct.
 
 
 ---randomtest - great_hall
No refactoring required

bugs:

 no bugs found
 
 
*****Teammate2

---cardtest1 - Smithy
refactored code to call correct function name and to pass incorrect parameters.  Also added
thisPlayer=whoseTurn(&G);//added to identify player turn 

bugs:

 deckcount failed
 handcount was not correct
 
---cardtest2 - adventurer
refactored code as adventurer did not return a value indicating how many cards where drawn before getting 
correct treasure amount.  Tests were changed from checking to see if deck count and discard count are correct size to just checking to see if they changed from the control state.  Also refactored code to call correct function name and to pass incorrect parameters.  Also added
thisPlayer=whoseTurn(&G);//added to identify player turn 

bugs;
 
 handcount was not correct
 
---cardtest3 - Village
refactored code to call correct function name and to pass incorrect parameters.  Also added
thisPlayer=whoseTurn(&G);//added to identify player turn 

bugs:

 discardcount was not correct
 
---cardtest4 - council_room
refactored code to run test for council_room which is still in cardEffect.

bugs:

 discardcount failed
 
 
---unittest1 - getCost
no refactoring required

bugs:

 no bugs found

 
---unittest2 - isGameOver
no refactoring required

bugs:

 no bugs found 
 
 
---unittest3 - shuffle
no refactoring required

bugs:

 no bugs found 
 
 
---unittest4 - drawCard
no refactoring required

bugs:

 when deckcount gets to 0 drawcard failed to return 0, handcount failed, and deckcount failed.
 
 

---randomtest - adventurer
refactored code as adventurer did not return a value indicating how many cards where drawn before getting 
correct treasure amount.  Tests were changed from checking to see if deck count and discard count are correct size to just checking to see if they changed from the control state.  Also refactored code to call correct function name and to pass incorrect parameters. 

bugs:

 current players handcount fails, deck count fails, discardcount fails, treasure count is not correct.
 Also hit a segfault which could have been due to bad gamestate.
 
 
 ---randomtest - great_hall
No refactoring required

bugs:

 no bugs found


*/