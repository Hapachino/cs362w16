For this assignment I debuged Steven Heng's Dominion code using my random tests for village
and adventurer. My other partner, Jashua Homann doesn't seem to be in the class anymore (no work in
dominion folder) so I could not run tests on his work.


Bug Report for Steven Heng Village Card
========================================

Title: Incorrect Number of Actions Given in Village   

Class: Feature Error
e.g. "Feature Request", "System Error", "Serious Bug"

Date: 02/27/2016          
Reported By: Brandon Gipson
Email: gipsonb@oregonstate.edu     


Product: Dominion               Version: Test Code for CS 362
Platform: Linux                 
      

Is it reproducible: Yes

Description
===========
The village card does not give the required two actions to the player. It only gives one


Steps to Produce/Reproduce
--------------------------
Always happens. Bug in initial design


Expected Results
----------------
Two actions given to player


Actual Results
--------------
One action given to player


Workarounds
-----------
None


Attachments
-----------
None


Other Information
-----------------
I had to go back a revision or two to find this bug. Bug is now fixed in latest version of dominion.c

-------------------------------------------------------------------------------------------------------


Bug Report for Steven Heng Adventurer Card
===========================================

Title: Player Doesn't Dicard Extra Cards   

Class: Feature Error
e.g. "Feature Request", "System Error", "Serious Bug"

Date: 02/27/2016          
Reported By: Brandon Gipson
Email: gipsonb@oregonstate.edu     


Product: Dominion               Version: Test Code for CS 362
Platform: Linux                 
      

Is it reproducible: Yes

Description
===========
The Adventurer card fails to decrement the current  player's hand count. Code to do so is
commented out.


Steps to Produce/Reproduce
--------------------------
Always happens.


Expected Results
----------------
Player discards excess cards.


Actual Results
--------------
Player retains excess cards


Workarounds
-----------
None


Attachments
-----------
None


Other Information
-----------------

