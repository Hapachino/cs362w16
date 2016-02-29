/**
 * BUGS in David Vogel's Dominion

 ==============================

Title: Incorrect HandCount in playAdventurer

Class: serious bug


Date:  2/28/16
Reported By:  Robert Jackson
Email:   jackrobe@oregonstate.edu


Product: Dominion.c
Function: PlayAdventurer()


Is it reproducible: Yes

Description
===========
An Incorrect Handcount is established when this function is called


Steps to Produce/Reproduce
--------------------------
Call PlayAdventurer with with a typical state. The player should have at least two treasure cards in their deck


Expected Results
----------------
Hand count should be incremented by two cards


Actual Results
--------------
Hand count is only incremented by one


Fault Location
-----------
Line 500, should increment on each loop.


Attachments
-----------
vogeldTest.out


==============================

Title: Incorrect HandCount in playSmithy

Class: serious bug


Date:  2/28/16
Reported By:  Robert Jackson
Email:   jackrobe@oregonstate.edu


Product: Dominion.c
Function: PlaySmithy()


Is it reproducible: Yes

Description
===========
An Incorrect Handcount is established when this function is called


Steps to Produce/Reproduce
--------------------------
Call PlaySmithy with with a typical state.


Expected Results
----------------
Hand count should be incremented by two cards


Actual Results
--------------
Hand count is increased by 3


Fault Location
-----------
Line 519, loop draws a total of 4 cards,


Reference
-----------
vogeldTest.out


/**
 * BUGS in Ian Bender Dominion

 ==============================

Title: Incorrect HandCount in playSmithy

Class: serious bug


Date:  2/28/16
Reported By:  Robert Jackson
Email:   jackrobe@oregonstate.edu


Product: Dominion.c
Function: PlaySmithy()


Is it reproducible: Yes

Description
===========
An Incorrect Handcount is established when this function is called.


Steps to Produce/Reproduce
--------------------------
Call PlaySmithy with with a typical state.


Expected Results
----------------
Hand count should be incremented by two cards


Actual Results
--------------
Hand count appears to be decremented by one


Fault Location
-----------
Line 682 for loop does not execute


Reference
-----------
benderiTest.out


 ==============================

Title: Incorrect HandCount in playAdventurer

Class: serious bug


Date:  2/28/16
Reported By:  Robert Jackson
Email:   jackrobe@oregonstate.edu


Product: Dominion.c
Function: PlayAdventurer()


Is it reproducible: Yes

Description
===========
An Incorrect Handcount is established when this function is called.


Steps to Produce/Reproduce
--------------------------
Call PlayAdventurer with with a typical state. The player should have at least two treasure cards in their deck


Expected Results
----------------
Hand count should be incremented by two cards
Discard should increase


Actual Results
--------------
Hand count is unchanged
Discard is unchanged

Fault Location
-----------
Line 660 Drawcard() only executes inside an if statement, limiting it to cases where the deck is empty


Reference
-----------
benderiTest.out

 * /