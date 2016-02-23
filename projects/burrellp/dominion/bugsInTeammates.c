/*
                                bugsInTeammates.c
 
 
 TEAMMATE 1 (teammate1Dominion/):
 
Bug #1
 Title: Player's deck count always decreases by exactly two after Adventurer card
    is played
 Classification: Severe
 Platform: Linux
 Description:
    Playing the Adventurer card should result in a player's deckCount decreasing by 
    the number of cards that were drawn in the course of drawing two treasure cards
    from the player's deck. My test shows that the player's deckCount instead is 
    always decreased by exactly two, regardless of the conditions before a call to 
    play Adventurer. 
 
    This error was present in all initial game conditions that were created prior
    to the Adventurer card being played.
 Steps to reproduce:
    Inside teammate1Dominion folder, run the following commands:
        $ gcc dominion.c rngs.c cardtest2.c -o prog
        $ ./prog
 
Bug #2
 Title: Player's coin total is always increased by exactly two after Adventurer card
    is played
 Classification: Severe
 Platform: Linux
 Description:
    Playing the Adventurer card should result in a player's coin total increasing by
    2-6 coins depending on which two treasure cards are drawn and added to the hand. 
    My test shows that the player's coin total is always increased by exactly two 
    when the Adventurer card is played, regardless of the conditions before a call
    to play Adventurer.
    
    This error was present in all initial game conditions that were created prior
    to the Adventurer card being played.
 Steps to reproduce:
    Inside teammate1Dominion folder, run the following commands:
        $ gcc dominion.c rngs.c cardtest2.c -o prog
        $ ./prog

**************************************************************************************** 
 
TEAMMATE 2 (teammate2Dominion/):
 
Bug #1
 Title: Player's hand count increases by incorrect number when Smithy card is played
 Classification: Severe
 Platform: Linux
 Description:
    Playing the Smithy card results in a player drawing three additional cards, and 
    then discarding the played card, resulting in an expected net increase of 2 cards
    in the player's hand. My test indicates that a player's hand count either increases
    by 3 or decreases by 1 after playing the Smithy card.
 
    The most common result is a change for +3 cards. The change of -1 occurs for player
    2 in a two player game and player 2 in a four player game. Player 4 in a four player
    game was the only condition that did not result in this error.
 Steps to reproduce:
    Inside teammate2dominion folder, run following commands:
        $ gcc dominion.c rngs.c cardFunctions.c cardtest1-2.c -o prog
        $ ./prog
 
Bug #2
 Title: playedCardCount does not increase by 1 after Smithy card is played
 Classification: Severe
 Platform: Linux
 Description:
    After playing Smithy, the card is moved from the player's hand and into the played
    card pile as part of the discardCard() function in the call to Smithy. This should 
    result in the playedCardCount being incremented by 1 after Smithy is played. My 
    test results show that playedCardCount is not incremented after Smithy is played; 
    it's value remains the same before and after Smithy is played. 
 
    This error was present in all initial game conditions that were created prior to 
    playing the Smithy card.
 Steps to reproduce:
    Inside teammate2dominion folder, run following commands:
        $ gcc dominion.c rngs.c cardFunctions.c cardtest1-2.c -o prog
        $ ./prog
 
Bug #3
 Title: Player's hand count, deck count, and coin total don't change after Adventurer 
    card is played
 Classification: Severe
 Platform: Linux
 Description:
    Playing the Adventure card should result in a player's handCount increasing by two
    from drawing two additional treasure cards, the player's coin total increasing by
    2-6 depending on what treasure cards were drawn, and the player's deck count 
    decreasing by the number of  cards drawn over the course of drawing the two treasure 
    cards. My tests show that none of these values are changed when the Adventurer card 
    is played.
 
    This error was present in all initial game conditions that were created prior to 
    playing the Adventurer card.
 Steps to reproduce:
    Inside teammate2dominion folder, run following commands:
        $ gcc dominion.c rngs.c cardFunctions.c cardtest2.c -o prog
        $ ./prog
*/