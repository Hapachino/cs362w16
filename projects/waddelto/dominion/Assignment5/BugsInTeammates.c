Noverse Bug Reporting Template
==============================

Title:   Minion failed to record coins correctly 

Class:  Serious bug 
e.g. "Feature Request", "System Error", "Serious Bug"

Date:   2/21/2016        
Reported By:   Todd Waddell
Email: waddelto@oregonstate.edu


Product:   Dominion/Minion      Version:
Platform:   C                    Version:
Browser:                        Version:
URL:        

Is it reproducible: Yes 

Description
===========
On 5000 tests, Minion faield to record coins correctly 5000 times.


Steps to Produce/Reproduce
--------------------------
Run Minion with path 1 selected.  Track bonus coins that should be
granted.


Expected Results
----------------
Minon path 1 should give the current player two bonus coins.


Actual Results
--------------
Bonus coins are not credited to current player's status for the current 
turn.


Workarounds
-----------
None


Attachments
-----------



Other Information
-----------------
This is a problem with how minion records coins.  Card records them
directly to state->coins++.  To be properly recorded, they should be added
to bonus coins. 

Noverse Bug Reporting Template
==============================

Title: Dominion/Minion fails to discard played card

Class:  Serious Bug
e.g. "Feature Request", "System Error", "Serious Bug"

Date:           2/21/2016
Reported By:   Todd Waddell
Email:      waddelto@oregonstate.edu


Product:  Dominon/Minion        Version:
Platform:                       Version:
Browser:                        Version:
URL:        

Is it reproducible: Yes 

Description
===========
On 5000 tests, Minion failed to discard played card 5000 times.


Steps to Produce/Reproduce
--------------------------
When playing minion card with choice 1, Minion does not
properly discard the played card.



Expected Results
----------------
Minion card should be in the discard pile
and discardCount should be incremented



Actual Results
--------------
Card is put into played card pile and 
play card count in incremented.  Essentially, 
card is trashed.



Workarounds
-----------
None



Attachments
-----------



Other Information
-----------------


Noverse Bug Reporting Template
==============================

Title:    Minion Path 2 Current player didn't discard hand

Class:  Serious Bug
e.g. "Feature Request", "System Error", "Serious Bug"

Date:   2/21/16        
Reported By:   Todd Waddell
Email:      waddelto@oregonstate.edu


Product:     Dominon/Minion     Version:
Platform:                       Version:
Browser:                        Version:
URL:        

Is it reproducible: Yes 

Description
===========
On 5000 tests of Minion-Path 2, minion failed to properly discard the
current player's hand every time.


Steps to Produce/Reproduce
--------------------------
Run Minion card with path 2


Expected Results
----------------
Minon should discard current hand and draw four new cards



Actual Results
--------------
Minon discard routine trashes hand


Workarounds
-----------
none


Attachments
-----------



Other Information
-----------------


Noverse Bug Reporting Template
==============================

Title:    Dominion/Minion Path 2 Always discards other players hands

Class: Serious Bug
e.g. "Feature Request", "System Error", "Serious Bug"

Date:   2/21/2016
Reported By:   Todd Waddell
Email:      waddelto@oregonstate.edu


Product:    Dominion.c          Version:
Platform:                       Version:
Browser:                        Version:
URL:        

Is it reproducible: Yes 

Description
===========
In 50000 randomized tests of minion path 2, Minon discarded player hands
everytime.  


Steps to Produce/Reproduce
--------------------------
Run minion with path 2 track other player hands


Expected Results
----------------
Other players should only discard when they have five or 
more cards.



Actual Results
--------------
Tests included randomized handsizes set to include sizes gt and lt 
5.  Minion discarded every time. 


Workarounds
-----------
None.



Attachments
-----------



Other Information
-----------------


Noverse Bug Reporting Template
==============================

Title:  Dominion/Adventurer Shuffle Error  

Class:  Serious Bug
e.g. "Feature Request", "System Error", "Serious Bug"

Date: 2/21/16
Reported By: Todd Waddell  
Email:       waddelto@oregonstate.edu


Product:  Dominion/Adventurer   Version:
Platform:                       Version:
Browser:                        Version:
URL:        

Is it reproducible: Occasionally

Description
===========
In 25000 tests, adventurer had the wrong card count after shuffle 53 times.



Steps to Produce/Reproduce
--------------------------
Adventurer with handsize set to force a shuffle.



Expected Results
----------------
Cards in the discard pile before the shuffle should be 
in the deck after the shuffle.  The discardCount[currentPlayer]
should be 0 and the deckCount[currentPlayer] should be equal to the 
prior discardCount.


Actual Results
--------------
Card counts are incorrect after shuffle.


Workarounds
-----------
Make deckCount[currentPlayer] and composition large enough
so that a shuffle isn't necessary.


Attachments
-----------



Other Information
-----------------


Noverse Bug Reporting Template
==============================

Title:    Dominion/Adventurer Drew the wrong amount of treasure

Class:  Serious Bug
e.g. "Feature Request", "System Error", "Serious Bug"

Date:  2/2116         
Reported By: Todd Waddell  
Email:       waddelto@oregonstate.edu


Product:  Dominion/Adventurer   Version:
Platform:                       Version:
Browser:                        Version:
URL:        

Is it reproducible: Yes 

Description
===========
In 25000 randomized tests, Adventurer drew the wrong amount of treasure
each time 


Steps to Produce/Reproduce
--------------------------
Run adventurer, track the amount of treasure drawn.


Expected Results
----------------
Adventurer should add two treasure cards from your deck into your hand.


Actual Results
--------------
Adventurer drew more or less than two treasure cards.


Workarounds
-----------
None


Attachments
-----------



Other Information
-----------------


Noverse Bug Reporting Template
==============================

Title:    Dominion/Adventurer  draws wrong cards into hand

Class:   Serious Bug
e.g. "Feature Request", "System Error", "Serious Bug"

Date:           2/21/16
Reported By:   Todd Waddell
Email:      waddelto@oregonstate.edu


Product:   Dominon/Adventurer   Version:
Platform:                       Version:
Browser:                        Version:
URL:        

Is it reproducible: Yes 

Description
===========
On 25000 randomized tests, Adventurer function put incorrect cards in hand.
Bug reported > 32000 times.  Likely due to multiple incorrect cards in hand
per test iteration.

Steps to Produce/Reproduce
--------------------------
Run adventurer.  Track cards drawn into hand.


Expected Results
----------------
Adventurer should draw cards from deck.  It should draw until it has put
two treasure cards into hand.  Non-treasure cards drawn are discarded. 



Actual Results
--------------



Workarounds
-----------



Attachments
-----------



Other Information
-----------------


Noverse Bug Reporting Template
==============================

Title:  Dominion/Minion Record Coins Bug  

Class:  Serious Bug
e.g. "Feature Request", "System Error", "Serious Bug"

Date:           2/21/2016
Reported By:   Todd Waddell
Email:      waddelto@oregonstate.edu


Product:  Dominion/Minion       Version:
Platform:                       Version:
Browser:                        Version:
URL:        

Is it reproducible: Yes 

Description
===========
In 5000 tests of minion path 1, Minion failed to record bonus coins
each time.


Steps to Produce/Reproduce
--------------------------
Run Minion with path 1 track bonus coins


Expected Results
----------------
Current player should have two bonus coins to play in current round.



Actual Results
--------------
Coins are not properly credited and essentially disappear. 
Coins should be credited to bonus coins variable.  Instead they are
credited to gamestate->coins.  That value is zero'ed out when 
update coins is called.



Workarounds
-----------
None.


Attachments
-----------



Other Information
-----------------


Noverse Bug Reporting Template
==============================

Title:    Dominion/Minion Failed to discard current hand

Class:  Serious Bug
e.g. "Feature Request", "System Error", "Serious Bug"

Date:    2/21/16       
Reported By:   Todd Waddell
Email:      waddelto@oregonstate.edu


Product:    Dominion/Minion     Version:
Platform:                       Version:
Browser:                        Version:
URL:        

Is it reproducible: Yes 

Description
===========
in 5000 tests of minion path 2, minion failed to properly discard current
player's hand



Steps to Produce/Reproduce
--------------------------
Run minion with path 2, check discardCount and discardPile for current hand


Expected Results
----------------
DiscardCount[currentPlayer] should increase by handCount[currentPlayer].
DiscardPile[currentPlayer] array should contain cards from hand.



Actual Results
--------------
At least one bug is discard function.  Instead of putting cards into
discard pile, discard puts into played card pile, which essentially trashes
them. 


Workarounds
-----------
none


Attachments
-----------



Other Information
-----------------


Noverse Bug Reporting Template
==============================

Title:    Dominion/Minion  Didn't properly discard other players' hands

Class:  Serious Bug
e.g. "Feature Request", "System Error", "Serious Bug"

Date:           2/21/16
Reported By:   Todd Waddell
Email:      waddelto@oregonstate.edu


Product:    Dominion/Minion     Version:
Platform:                       Version:
Browser:                        Version:
URL:        

Is it reproducible: Yes / Occasionally / One Time / No

Description
===========
Minion, path 2, fails to properly discard other players' hands when
handcount >= 5.



Steps to Produce/Reproduce
--------------------------
Run Minion with path 2, check discardCount and discardPile.


Expected Results
----------------
If other players have handCount >= 5, those cards should be discarded and
discardCount[otherPlayers] should be incremented.



Actual Results
--------------
Probably related to bug in discard Function wherein cards are improperly
put in the playedCard pile instead of the discard pile. 


Workarounds
-----------
none



Attachments
-----------



Other Information
-----------------


Noverse Bug Reporting Template
==============================

Title:  Dominion/Adventurer Shuffle Error  

Class:  Serious Bug
e.g. "Feature Request", "System Error", "Serious Bug"

Date: 2/21/16
Reported By: Todd Waddell  
Email:       waddelto@oregonstate.edu


Product:  Dominion/Adventurer   Version:
Platform:                       Version:
Browser:                        Version:
URL:        

Is it reproducible: Occasionally

Description
===========
In 25000 tests, adventurer had the wrong card count after shuffle 53 times.



Steps to Produce/Reproduce
--------------------------
Adventurer with handsize set to force a shuffle.



Expected Results
----------------
Cards in the discard pile before the shuffle should be 
in the deck after the shuffle.  The discardCount[currentPlayer]
should be 0 and the deckCount[currentPlayer] should be equal to the 
prior discardCount.


Actual Results
--------------
Card counts are incorrect after shuffle.


Workarounds
-----------
Make deckCount[currentPlayer] and composition large enough
so that a shuffle isn't necessary.


Attachments
-----------



Other Information
-----------------


Noverse Bug Reporting Template
==============================

Title:    Dominion/Adventurer Drew the wrong amount of treasure

Class:  Serious Bug
e.g. "Feature Request", "System Error", "Serious Bug"

Date:  2/2116         
Reported By: Todd Waddell  
Email:       waddelto@oregonstate.edu


Product:  Dominion/Adventurer   Version:
Platform:                       Version:
Browser:                        Version:
URL:        

Is it reproducible: Yes 

Description
===========
In 25000 randomized tests, Adventurer drew the wrong amount of treasure
each time 


Steps to Produce/Reproduce
--------------------------
Run adventurer, track the amount of treasure drawn.


Expected Results
----------------
Adventurer should add two treasure cards from your deck into your hand.


Actual Results
--------------
Adventurer drew more or less than two treasure cards.


Workarounds
-----------
None


Attachments
-----------



Other Information
-----------------


Noverse Bug Reporting Template
==============================

Title:    Dominion/Adventurer  draws wrong cards into hand

Class:   Serious Bug
e.g. "Feature Request", "System Error", "Serious Bug"

Date:           2/21/16
Reported By:   Todd Waddell
Email:      waddelto@oregonstate.edu


Product:   Dominon/Adventurer   Version:
Platform:                       Version:
Browser:                        Version:
URL:        

Is it reproducible: Yes 

Description
===========
On 25000 randomized tests, Adventurer function put incorrect cards in hand.
Bug reported > 32000 times.  Likely due to multiple incorrect cards in hand
per test iteration.

Steps to Produce/Reproduce
--------------------------
Run adventurer.  Track cards drawn into hand.


Expected Results
----------------
Adventurer should draw cards from deck.  It should draw until it has put
two treasure cards into hand.  Non-treasure cards drawn are discarded. 



Actual Results
--------------



Workarounds
-----------



Attachments
-----------



Other Information
-----------------


