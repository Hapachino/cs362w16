/*
 * Changes Made to cardEffect
 *
 * Refactored the switch cases for cardEffect so smithy, adventurer,
 * council room, feast, and village effects are in their own functions.
 *
 * Smithy Changes
 * ---------------
 * Refactored so that all of the original function methods and logic
 * are in playSmithy. We pass the game state and handPos to playSmithy
 * so it can change the game state as it used to in the cardEffect
 * function.
 *
 * Adventurer Changes
 * ---------------
 * Refactored so that all of the original function methods and logic
 * are in the function playAdventurer. We pass the game state to playAdventurer
 * so it can change the game state as it used to in the cardEffect
 * function.
 *
 * Council Room Changes
 * ---------------
 * Refactored so that all of the original function methods and logic
 * are in the function playCouncil_Room. We pass the game state and 
 * handPos to playCouncil_Room so it can change the game state as it 
 * used to in the cardEffect function.
 *
 * Feast Changes
 * ---------------
 * Refactored so that all of the original function methods and logic
 * are in the function playFeast. We pass the game state and 
 * choice1 to playFeast so it can change the game state as it 
 * used to in the cardEffect function.
 *
 * Village Changes
 * ---------------
 * Refactored so that all of the original function methods and logic
 * are in the function playVillage. We pass the game state and 
 * handPos to playVillage so it can change the game state as it 
 * used to in the cardEffect function.
 *
 * Introduced Bugs
 * ---------------
 * playAdventurer
 * * no shuffle before we begin drawing, we could end up drawing from
 * an empty deck!
 * playSmithy
 * * one-off error, for loop to draw 3 cards is i <= 3, should be i < 3
 * playFeast
 * * does not set x = 0 when we finish buying one card
 * playCouncil_Room
 * * all players will draw a card, even when the current player that played
 * it should be excluded
 */