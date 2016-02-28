/*
 * 
 * cardEffectAdventurer()
 *     cardEffect() case for adventurer calls this new function created
 *     by refactoring the case statement code into this function.
 *     Parameters for current player and the game state data structure
 *     are passed in. Declared needed variables cardDrawn, drawntreasure,
 *     z, and temphand. Bug introduced in while loop to discard cards
 *     in play that were drawn (conditional was >= bug is >).
 * 
 * cardEffectCouncilRoom()
 *     cardEffect() case for council_room calls this new function
 *     created by refactoring the case statement code into this function.
 *     Parameters for current player and the game state data structure
 *     and hand position are passed in. Declared variable i for the
 *     function. Bug introduced in for loop to draw card for the 
 *     current player (i was initialized to 0 bug is initialized to 1).
 * 
 * cardEffectMine()
 *     cardEffect() case for mine calls this new function created by 
 *     refactoring the case statement code into this function.
 *     Parameters for current player and the game state data structure,
 *     hand position, choice1 and choice2 are passed in. Declared variables
 *     i and j for the function. Bug introduced in card cost check of the
 *     chosen card (was > bug is >=).
 * 
 * cardEffectRemodel()
 *     cardEffect() case for remodel calls this new function created by 
 *     refactoring the case statement code into this function.
 *     Parameters for current player and the game state data structure,
 *     hand position, choice1 and choice2 are passed in. Declared variables
 *     i and j for the function. Bug introduced in card cost check of the
 *     chosen card (was +2 bug is +3).
 * 
 * cardEffectSmithy()
 *     cardEffect() case for smithy calls this new function created by 
 *     refactoring the case statement code into this function.
 *     Parameters for current player and the game state data structure,
 *     and hand position are passed in. Declared variable i for the 
 *     refactored function. Bug introduced in for loop to draw cards
 *     (was i=0 bug is i=1).
 * 
 * 
 */
