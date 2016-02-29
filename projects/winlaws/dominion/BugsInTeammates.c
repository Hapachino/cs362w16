*********************************************************************************
***  CS 362 - Assignment 5 - Testing and Debugging Dominion - Spencer Winlaw  ***
***   BugsInTeammates.c - write-up of Bugs found in teammates dominion code   ***
*********************************************************************************

---------------------------------------------------------------------------------
-                             Bugs for dobbsaDominion                           -
---------------------------------------------------------------------------------
 ________________________________________________________________________________
|	
|	Title: Too many cards received when Adventurer Card played
|
|	Class: Serious Bug
|
|	Date: 2/28/2016          
|	Reported By: Spencer Winlaw  
|	Email: winlaws@oregonstate.edu     
|
|	Product: dominion.c 
|	Platform: Linux version 2.6.32-573.8.1.e16.x86_64 
|			  (mockbuild@c6b8.bsys.dev.centos.org)
|			  (gcc version 4.4.7 20120313 (Red Hat 4.4.7-16) (GCC))     
|
|	Is it reproducible: Yes - Every time the Adventurer Card is played
|
|	Description
|	===========
|	When Adventurer Card is played, the current player receives all cards drawn, 
|	not just the treasure cards as expected
|
|	Steps to Produce/Reproduce
|	--------------------------
|	Play the Adventurer Card
|
|	Expected Results
|	----------------
|	The current player receives 2 treasure cards and all other cards are discarded.
|
|	Actual Results
|	--------------
|	The current player receives all cards drawn until 2 treasure cards are drawn. 
|
|________________________________________________________________________________

 ________________________________________________________________________________
|	
|	Title: Too many cards received/numActions changed when Smithy Card is played   
|
|	Class: Serious Bug
|
|	Date: 2/28/2016          
|	Reported By: Spencer Winlaw  
|	Email: winlaws@oregonstate.edu     
|
|	Product: dominion.c 
|	Platform: Linux version 2.6.32-573.8.1.e16.x86_64 
|			  (mockbuild@c6b8.bsys.dev.centos.org)
|			  (gcc version 4.4.7 20120313 (Red Hat 4.4.7-16) (GCC))     
|
|	Is it reproducible: Yes - Every time the Smithy Card is played 
|
|	Description
|	===========
|	When Smithy Card is played, the current player receives too many cards and
|	numActions does not remain the same
|
|	Steps to Produce/Reproduce
|	--------------------------
|	Play Smithy Card
|
|	Expected Results
|	----------------
|	Current player receives 3 cards and numActions remains the same
|
|	Actual Results
|	--------------
|	Current Player receives 4 cards and numActions is incremented by 2
|
|________________________________________________________________________________



---------------------------------------------------------------------------------
-                              Bugs for gremmoaDominion                         -
---------------------------------------------------------------------------------
 ________________________________________________________________________________
|	
|	Title: Too many cards received when Smithy Card is played   
|
|	Class: Serious Bug
|
|	Date: 2/28/2016          
|	Reported By: Spencer Winlaw  
|	Email: winlaws@oregonstate.edu     
|
|	Product: dominion.c 
|	Platform: Linux version 2.6.32-573.8.1.e16.x86_64 
|			  (mockbuild@c6b8.bsys.dev.centos.org)
|			  (gcc version 4.4.7 20120313 (Red Hat 4.4.7-16) (GCC))     
|
|	Is it reproducible: Yes - Every time the Smithy Card is played   
|
|	Description
|	===========
|	When Smithy is played, the current player receives too many cards 
|
|	Steps to Produce/Reproduce
|	--------------------------
|	Play Smithy Card
|
|	Expected Results
|	----------------
|	Current Player receives 3 cards
|
|	Actual Results
|	--------------
|	Current Player receives 4 cards
|
|________________________________________________________________________________

 ________________________________________________________________________________
|	
|	Title: Silver and Gold Cards not received when Adventurer Card is played  
|
|	Class: Serious Bug
|
|	Date: 2/28/2016          
|	Reported By: Spencer Winlaw  
|	Email: winlaws@oregonstate.edu     
|
|	Product: dominion.c 
|	Platform: Linux version 2.6.32-573.8.1.e16.x86_64 
|			  (mockbuild@c6b8.bsys.dev.centos.org)
|			  (gcc version 4.4.7 20120313 (Red Hat 4.4.7-16) (GCC))     
|
|	Is it reproducible: Yes - When Adventurer Card is played and silver or gold 
|							  cards are in position in deck to be drawn
|
|	Description
|	===========
|	When Card is played and silver or gold cards are in position in deck to be drawn,
|	silver or gold cards are not added to the current players hand.
|
|	Steps to Produce/Reproduce
|	--------------------------
|	 - Stack deck so that  silver or gold cards are in position in deck to be drawn
|	 - Play Adventurer Card
|
|	Expected Results
|	----------------
|	Silver and Gold cards are added to current players hand
|
|	Actual Results
|	--------------
|	Silver and Gold Cards are not added to current players hand
|
|________________________________________________________________________________