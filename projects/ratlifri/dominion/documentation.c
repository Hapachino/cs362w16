/*
 * 
 * Smithy :: cost=4, +3 cards
 *     Smithy is an action card that costs 4 to buy, and when played, 
 *     allows the player draw 3 more cards.
 * 
 * Adventurer :: cost=6, reveal 2 treasure cards
 *     Adventurer is an action card that costs 6 to buy, and when played, 
 *     reveals cards from the deck, one at a time, until two treasure cards 
 *     are revealed. The two treasure cards are drawn into play while the 
 *     other cards revealed are discarded.
 * 
 * discardCard() :: remove card from player hand
 *     Main operation of the function is to remove a card from player hand.
 *     Function first checks if the card is to be trashed and if not then the 
 *     card is marked as played by the current player and added to the played 
 *     pile. Number of cards in hand is reduced by one. Last card in hand
 *     sentinel value is updated to -1 when other cards remain in hand.
 * 
 * updateCoins() :: resolves coin count during turn
 *     Coin count is first set to 0 then coins in play for the turn 
 *     are resolved by counting all treasure cards in hand (copper +1, 
 *     silver +2, and gold +3) and adding bonus from action cards.
 * 
 */
