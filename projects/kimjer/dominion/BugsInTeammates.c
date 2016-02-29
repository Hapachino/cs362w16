MARK GILES

-------------------------------------------------------------
Noverse Bug Reporting Template
==============================

Title:  "Smithy Effect"
Class: "Serious Bug"

Date: 2-28-2016
Reported By:  Jerry Kim
Email:  kimjer@oregonstate.edu   
Platform: Version: Ubuntu 14.04

Is it reproducible: Yes

Description
===========
Bug in smithyEffect was found to be in the part to modify the current player's deck count after three cards 
more cards have been pulled from it. It draws actually 4 cards instead of 3, affecting both the deckCount 
and handCount. Bug seems to be isolated in the loop exit condition that is in charge of drawing the cards, 
which makes it cycle 4 times instead of 3. The final card count of the hand seems to end up as the correct
 value because there is a discardCard executed after the loop, which decrements the hand count. 


Steps to Produce/Reproduce
--------------------------
Just run it. 


Expected Results
----------------
Deck count before: 495; deck count after: 492


Actual Results
--------------
Deck count before: 495; deck count after: 491

==============================================================================
Title:  "Village Effect"
Class: "Serious Bug"

Date: 2-28-2016
Reported By:  Jerry Kim
Email:  kimjer@oregonstate.edu   
Platform: Version: Ubuntu 14.04

Is it reproducible: Yes

Description
===========
Only one bug was found in village test, which has to do with dealing out the correct number of actions. 
It happens currently to deal only one action whereas correctly it should deal out two actions. Probably 
easily fixed with a loop, which has the slight, added benefit of making the code more maintainable. 


Steps to Produce/Reproduce
--------------------------
Just run it. 


Expected Results
----------------
Action count before: 1
Action count after: 3


Actual Results
--------------
Action count before: 1
Action count after: 1




ERIC OLSON
-------------------------------------------------------------
Noverse Bug Reporting Template
==============================

Title:  "Village Effect"
Class: "Serious Bug"

Date: 2-28-2016
Reported By:  Jerry Kim
Email:  kimjer@oregonstate.edu   
Platform: Version: Ubuntu 14.04

Is it reproducible: Yes

Description
===========
Action count doesn't update at all. 


Steps to Produce/Reproduce
--------------------------
Just run it. 


Expected Results
----------------
Action count before: 1
Action count after: 3


Actual Results
--------------
Action count before: 1
Action count after: 1

==========================================================

Title:  "Smithy Effect"
Class: "Serious Bug"

Date: 2-28-2016
Reported By:  Jerry Kim
Email:  kimjer@oregonstate.edu   
Platform: Version: Ubuntu 14.04

Is it reproducible: Yes

Description
===========
Hand count doesn't update correctly after drawing 3 cards from the deck. 


Steps to Produce/Reproduce
--------------------------
Everytime. Just run it. 


Expected Results
----------------
Hand count before: 5
Hand count after: 8


Actual Results
--------------
Hand count before: 5
Hand count after: 7

