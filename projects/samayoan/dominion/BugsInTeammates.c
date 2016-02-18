/*
 Nelson Samayoa
 Bugs found in teammates' code
 
 Teammate 1: meynm
 
 Bug 1
    Title: scoreFor method is not calculating the player's score correctly.
    Product: Domion game
    Classification: Severe
    Platform: Ubuntu Linux 15.04 running Domion in Code::Blocks IDE
    Can it be reproduced?: Yes
    Description: Under certain conditions, the score return by scoreFor is 2 less than expected. Note that 
        sometimes the score is correct, and just three of the 6 total test runs fail.
    Steps to reproduce: Go into the teammate1dominion folder and run command "make unittest4.out".
        Look at results and note that some test runs failed.
    Expected results: All scores should be accurated calculated.
    Actual results: The score is often not correctly calculated.
    Workaround: No workarounds exist that could be used by the player.
    
 
Bug 2
    Title: After a player plays the Salvager card, the coin count is often incorrect.
    Product: Domion game
    Classification: Severe
    Platform: Ubuntu Linux 15.04 running Domion in Code::Blocks IDE
    Can it be reproduced?: Yes
    Description: After a player plays the Salvager card, the coin count is often incorrect by varying amounts.
    Steps to reproduce: Go into the teammate1dominion folder and run command "make cardtest3.out". 
                        Note that this test takes a few seconds to run.
    Expected results: All coin counts should be accurated calculated because the Salvager card should correctly
                     give the user the value of their trashed card.
    Actual results: The value of the trashed card seems to not be correctly calculated.
    Workaround: No workarounds exist that could be used by the player.
    

Teammate 2: burrellp
Bug 1
    Title: Sometimes when player 1 plays the Cutpurse card, player 2 does not get the correct amount of coins removed.
    Product: Domion game
    Classification: Moderate
    Platform: Ubuntu Linux 15.04 running Domion in Code::Blocks IDE
    Can it be reproduced?: Yes
    Description: When a player plays the Cutpurse card, the other players must discard a copper card if they have one.
                The effect is that the other players should 
    Steps to reproduce: Go into the teammate2dominion folder and run command "make {cccc}.out". 
    Expected results: 
    Actual results: 
    Workaround: No workarounds exist that could be used by the player.
        
 */

