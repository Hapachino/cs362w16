Mark Giles
CS 362 - Software Engineering II
Assignment 5
BugsInTeammates.c
Special Note: The bug template used here is a slightly modified version of the
	Noverse template provided at:
		http://noverse.com/blog/2012/06/how-to-write-a-good-bug-report/
	There are several components of this template not relevant to this bug
	report such as browser version, but otherwise the content is the same.

Setting Up Test Code - Jerry Kim
======================
Jerry used naming and function parameters slightly different from my original
implementations when the tests were created. In order to allow for my tests to
run in this environment, I modified the test function names, added the
initialization of a custom struct infosStruct, and used that structure to set
initial parameters for performing the tests. With my tests set up to allow for
flexibility in function parameters, these changes were minimal and allowd for
ease of testing. I also copied my Makefile into the directory, and the only
modification was to remove the testing for my refactored remodel function as it
was not used in Jerry's project initially. Otherwise, my tests were able to
adapt to this new environment quickly and easily.

BUG REPORT #1 - Jerry Kim -  effectVillage(struct gameState *, struct infosStruct *)

Title: Invalid player hand count after the function is used

Class: System Error

Date: 2/27/2016
Reported By: Mark Giles
Email: gilesm@oregonstate.edu

Product: Dominion Game
Platform: Linux			Version: CentOS version 6.7

Is it reproducible: Yes

Description
===========
When calling the effectVillage function, the expected result is that the player
will draw one card and then discard the village card in the player's hand.
Because the player's hand will gain one card and remove one card, the overall
result should be a net gain/loss of 0 to the player's hand count. Multiple 
tests reveal that each time the function is called, the player's hand count is
incremented by 1.

Steps to Produce/Reproduce
--------------------------
	1 - initialize a game state
	2 - intiailze an infosStruct
	3 - set the infosStruct current player to 0
	4 - set the infosStruct handpos to any position
	5 - call the function using the established parameters
	6 - observe the player's hand count before and after the function call

Expected Results
----------------
The overall expected results at the end of the function call is that the number
of cards in the player's hand will be equal before and after the function,
given that there is a +1 and -1 operation.

Actual Results
--------------
The player's hand count after the function call is less  than the player's hand
count before the function call. Multiple randomized tests reveal this to be the
case in a number of conditions in hand position and beginning hand count. The
different between initial hand count and final hand count is almost completely
1 or 2, indicating that one or two additional hand count decrements are taking
place in these cases where there should only be one.

Other Information
-----------------
Given that the function under test only calls the the discardCard function to 
handle hand count decrements, it is possible that there is either an error in 
the function call or in the discardCard method itself. Given that there is a
variance between the number of invalid decrements, the conditional logic used
in the discardCard() method is most likely the cause and could missing
opportunities to evalute the appropriate time to decrement the player's hand
count.

Test Setup - Eric Olsen
=======================



Title:

Class:
e.g. "Feature Request", "System Error", "Serious Bug"

Date:
Reported By:
Email:


Product:							Version:
Platform:							Version:
Browser:							Version:
URL:

Is it reproducible: Yes / Occassionally / One Time / No

Description
===========



Steps to Produce/Reproduce
--------------------------



Expected Results
----------------



Actual Results
--------------



Workarounds
-----------



Attachments
-----------



Other Information
-----------------


