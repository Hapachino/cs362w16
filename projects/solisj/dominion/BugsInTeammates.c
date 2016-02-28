/********************************************************************************************************************************************************
*** Filename: BugsInTeammates.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Due date: 2/23/2016
*** Assignment 5
*** Description: Report any bugs you found in your teammates/ code
***
*******************************************************************************************************************************************************

================================
Teammate #1: Waddelto
================================


     Noverse Bug Reporting Template
     ==============================

     Title: Smithy card was not found in played cards pile

     Class: Serious Bug
     e.g. "Feature Request", "System Error", "Serious Bug"

     Date: 2/22/2016
     Reported By: Juan Solis
     Email: solisj@oregonstate.edu

     Product:   dominion.c/smithyEffect()            Version:
     Platform:    C                                  Version:
     Browser:                                        Version:
     URL:

     Is it reproducible: Yes

     Description
     ===========
     After playing the smithy card, the card should be added to the playedCards array.

     Steps to Produce/Reproduce
     --------------------------
     1) Run smithyEffect()
     2) Check the gameState.playedCards[] for the smithy card

     Expected Results
     ----------------
     The smithy card to be found in the playedCards array

     Actual Results
     --------------
     Checking that the smithy card was added to the played cards pile...
     Failed! Smithy card was not found in played cards pile!

     Workarounds
     -----------
     none

     Other Information
     -----------------
     The call to discardCard() in the smithyEffect() function has the trashflag set to '1'. It should be set to '0'.


          Noverse Bug Reporting Template
     ==============================

     Title: Smithy card is not incrementing the playedCardsCount by 1

     Class: Serious Bug
     e.g. "Feature Request", "System Error", "Serious Bug"

     Date: 2/22/2016          
     Reported By: Juan Solis  
     Email: solisj@oregonstate.edu      

     Product:   dominion.c/smithyEffect()            Version:
     Platform:    C                                  Version:
     Browser:                                        Version:
     URL:        

     Is it reproducible: Yes

     Description
     ===========
     After playing the smithy card, the playedCardsCount is not incrementing by 1

     Steps to Produce/Reproduce
     --------------------------
     1) Run smithyEffect()
     2) Check the gameState.playedCardsCount

     Expected Results
     ----------------
     The playedCardsCount to be increased by 1

     Actual Results
     --------------
     Testing that player[1] playedCardCount has increased by 1..
     playedCardCount = 0, Expected = 1

     Workarounds
     -----------
     none

     Other Information
     -----------------
     The call to discardCard() in the smithyEffect() function has the trashflag set to '1'. It should be set to '0'.

     Noverse Bug Reporting Template
     ==============================

     Title: isGameOver() is not checking the seahag and treasuremap card supply piles.

     Class: Serious Bug
     e.g. "Feature Request", "System Error", "Serious Bug"

     Date: 2/22/2016
     Reported By: Juan Solis
     Email: solisj@oregonstate.edu

     Product:   dominion.c/isGameOver()              Version:
     Platform:    C                                  Version:
     Browser:                                        Version:
     URL:

     Is it reproducible: Yes

     Description
     ===========
     The isGameOver() function only checks supply piles for cards 0-24. Cards 25 and 26 are seahag and treasuremap.

     Steps to Produce/Reproduce
     --------------------------
     Run isGameOver() with the following combination of 3 depleted supply piles:

     gameState.supplyCount[<anycard other than seahag and treasure_map>] = 0;
     gameState.supplyCount[<anycard other than seahag and treasure_map>] = 0;
     gameState.supplyCount[<seahag or treasure_map>] = 0;

     Expected Results
     ----------------
     isGameover() to return 1

     Actual Results (Small excerpt fomr unit test)
     ---------------------------------------------------------------------------------------------------------------------------
     Testing three depleted supply piles- Cards depleted: remodel, council_room, and sea_hag
     isGameover = 0, Expected = 1
     ---------------------------------------------------------------------------------------------------------------------------
     Testing three depleted supply piles- Cards depleted: remodel, council_room, and treasure_map
     isGameover = 0, Expected = 1
     ---------------------------------------------------------------------------------------------------------------------------
     Testing three depleted supply piles- Cards depleted: remodel, feast, and sea_hag
     isGameover = 0, Expected = 1
     ---------------------------------------------------------------------------------------------------------------------------
     Testing three depleted supply piles- Cards depleted: remodel, feast, and treasure_map
     isGameover = 0, Expected = 1
     ---------------------------------------------------------------------------------------------------------------------------
     Testing three depleted supply piles- Cards depleted: remodel, gardens, and sea_hag
     isGameover = 0, Expected = 1
     ---------------------------------------------------------------------------------------------------------------------------
     Testing three depleted supply piles- Cards depleted: remodel, gardens, and treasure_map
     isGameover = 0, Expected = 1
     ---------------------------------------------------------------------------------------------------------------------------

     Workarounds
     -----------
     none

     Attachments
     -----------

     Other Information
     -----------------


================================
Teammate #2: Chatmanm
================================

         Noverse Bug Reporting Template
     ==============================

     Title: Smithy card is not adding the correct amount of cards to the player's hand.  

     Class: Serious Bug
     e.g. "Feature Request", "System Error", "Serious Bug"

     Date: 2/22/2016          
     Reported By: Juan Solis  
     Email: solisj@oregonstate.edu      

     Product:   dominion.c/playSmithy()            Version:
     Platform:    C                                  Version:
     Browser:                                        Version:
     URL:        

     Is it reproducible: Yes

     Description
     ===========
     After playing the smithy card, the handCount should increase by 2(+3 new cards, -1 smithy card = net +2 cards).

     Steps to Produce/Reproduce
     --------------------------
     1) Run smithyEffect()
     2) Check the gameState.handCount[player] for the smithy card

     Expected Results
     ----------------
     previousGameState..handCount[player] + 2

     Actual Results
     --------------
     Testing that player[0] handCount has increased by 2...
     handCount = 2, Expected = 3


     Workarounds
     -----------
     none

     Attachments
     -----------

     Other Information
     -----------------
     The for loop in playSmithy() is starting the variable 'i' at '1'. It should be set to "i = 0".


     Noverse Bug Reporting Template
     ==============================

     Title:   Great Hall card effect is not correctly increasing number of actions by exactly 1.

     Class: Serious Bug
     e.g. "Feature Request", "System Error", "Serious Bug"

     Date: 2/22/2016
     Reported By: Juan Solis
     Email: solisj@oregonstate.edu


     Product:   dominion.c/playGreatHall()            Version:
     Platform:    C                                  Version:
     Browser:                                        Version:
     URL:

     Is it reproducible: Yes

     Description
     ===========
     The great hall card should add exactly 1 action to the game state but is instead adding 2.


     Steps to Produce/Reproduce
     --------------------------
     1) Run playGreatHall(struct gameState *state, int currentPlayer, int handPos)
     2) Check number of gameState actions


     Expected Results
     ----------------
     PreviousGameState..numActions + 1


     Actual Results
     --------------
     Iteration #92: Testing that number of actions has increased by 1 has failed.
     prevState.numActions = 1, postState.numActions = 3, expected = 2


     Workarounds
     -----------
     none


     Attachments
     -----------



     Other Information
     -----------------
     In the playGreatHall() function:
     "state->numActions += 2;" should be "state->numActions += 1;"

     Noverse Bug Reporting Template
     ==============================

     Title: isGameOver() is not checking the seahag and treasuremap card supply piles.

     Class: Serious Bug
     e.g. "Feature Request", "System Error", "Serious Bug"

     Date: 2/22/2016
     Reported By: Juan Solis
     Email: solisj@oregonstate.edu


     Product:   dominion.c/isGameOver()              Version:
     Platform:    C                                  Version:
     Browser:                                        Version:
     URL:

     Is it reproducible: Yes

     Description
     ===========
     The isGameOver() function only checks supply piles for cards 0-24. Cards 25 and 26 are seahag and treasuremap.


     Steps to Produce/Reproduce
     --------------------------
     Run isGameOver() with the following combination of 3 depleted supply piles:

     gameState.supplyCount[<anycard other than seahag and treasure_map>] = 0;
     gameState.supplyCount[<anycard other than seahag and treasure_map>] = 0;
     gameState.supplyCount[<seahag or treasure_map>] = 0;



     Expected Results
     ----------------
     isGameover() to return 1


     Actual Results (Small excerpt fomr unit test)
     ---------------------------------------------------------------------------------------------------------------------------
     Testing three depleted supply piles- Cards depleted: remodel, council_room, and sea_hag
     isGameover = 0, Expected = 1
     ---------------------------------------------------------------------------------------------------------------------------
     Testing three depleted supply piles- Cards depleted: remodel, council_room, and treasure_map
     isGameover = 0, Expected = 1
     ---------------------------------------------------------------------------------------------------------------------------
     Testing three depleted supply piles- Cards depleted: remodel, feast, and sea_hag
     isGameover = 0, Expected = 1
     ---------------------------------------------------------------------------------------------------------------------------
     Testing three depleted supply piles- Cards depleted: remodel, feast, and treasure_map
     isGameover = 0, Expected = 1
     ---------------------------------------------------------------------------------------------------------------------------
     Testing three depleted supply piles- Cards depleted: remodel, gardens, and sea_hag
     isGameover = 0, Expected = 1
     ---------------------------------------------------------------------------------------------------------------------------
     Testing three depleted supply piles- Cards depleted: remodel, gardens, and treasure_map
     isGameover = 0, Expected = 1
     ---------------------------------------------------------------------------------------------------------------------------

     Workarounds
     -----------
     none


     Attachments
     -----------


     Other Information
     -----------------

