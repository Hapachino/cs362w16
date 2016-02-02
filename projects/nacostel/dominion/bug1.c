Bugs Found:

Adventurer card implementation bug:  I tested six different aspects of the Adventurer implementation in cardtest1.c: the card was discarded correctly, 2 cards were drawn into 
current player's hand, the right number of cards were taken from the current player's deck, the other player's deck remains unchanged, the other player's hand remains 
unchanged, and that the last three cards added to the current player's hand are treasure cards.  I was able to confirm that the correct card was discarded and the hand of the 
other player remained unchanged. However, the other tests failed.  Three cards were drawn instead of two. So, this resulted in an incorrect hand count and deck count.(I introduced 
these bugs in Assignment 2. See refactor.c)  Additionally, the other player's deck changed. I'm not sure exactly what caused this bug.

Smithy card implementation bug:  I tested five different aspects of the Smithy implementation in cardtest2.c: the card was discarded correctly, three cards were drawn from the current
player's deck to the current player's hand, and that the other player's deck and hand remain unchanged. One test failed.  The hand count of the current player was incorrect.  
(I inroduced this bug in Assignment2. See refactor.c). All other tests passed.

Coucil Room card implementation bug:  I tested five different aspects of the Council Room implementation in cardtest3.c: four cards were added to the current player's hand, 1 card was added 
to the other player's hand, the right card was discarded, and the right number of cards was removed from each player's deck.  The right number of cards were added to the other player's hand
and the cards came from the other player's deck as expected and the right card was discarded. However, the other test failed.  The wrong number of cards were added to the current player's hand
and the wrong number of cards were removed from the current player's deck. (I introduced this bug in Assignment2. See refactor.c) 

Mine card implementation bug: I tested several different aspects of the Mine card implmentation in cardtest4.c.  Two of the things I tested are whether the card gained is a treasure card and 
whether the card discarded is a treasure card. I was able to confirm that the card gained is a treasure card. However, the other test failed. The card discarded was not a treasure card. I'm 
not sure what is causing this issue.

I found no other bugs after the execution of my unit tests.