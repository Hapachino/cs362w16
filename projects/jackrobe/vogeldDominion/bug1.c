/* ---------------------------------------------------------------------------
 *  David Vogel
 *  CS362 Assignment 3
 *  Due Feb 3, 2016
 *  Filename: bug1.c
 *    Description of bugs found in Assignment 3
 *  
 *  The only bug that was uncovered in my testing was with the adventurer card.
 *  The adventurer card should finish with only 6 cards in the deck:
 *    original hand = 5
 *    + 2 treasure cards
 *    - 1 adventurer card
 *    = 6 cards in hand
 *  The tests I ran gave 7 cards in total. I have not yet been able to determine why.
 *  The tests I ran for the smithy, great_hall, and village cards all succeeded 
 *  in producing correct results and game states.
 * --------------------------------------------------------------------------- */