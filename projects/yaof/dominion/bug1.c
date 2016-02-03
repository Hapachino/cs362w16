/*
 * scoreFor
 * ------------
 * scoreFor appears to work as intended for all victory cards except for Gardens and estate. When we expect
 * 1500 as the score for having all estate cards in the deck, hand, and discard, the game identifies it as score
 * 0. We also have a score of 0 for Gardens, which is likely because gardens only counts for the int card value
 * of 0, which is highly unlikely! This would mean only curse cards count toward the Gardens card bonus total.
 *
 * isGameOver
 * ------------
 * No bugs found from unit test.
 * 
 * drawCard
 * ------------
 * No bugs found from unit test.
 * 
 * updateCoins
 * ------------
 * No bugs found from unit test.
 * 
 * playAdventurer
 * ------------
 * playAdventurer does not discard the adventurer card from the hand after playing it. The player has 3 cards
 * on hand after playing Adventurer (had an empty hand besides Adventurer), instead of the expected 2.
 *
 * playSmithy
 * ------------
 * playSmithy does not discard the Smithy card from the hand after playing it. The player had 4 cards on hand
 * after playing Smithy, instead of just 3. 
 * 
 * playVillage
 * ------------
 * playVillage does not discard the Village card from the hand after playing it. The only card in 
 * the player's hand after playing Village is the Village card itself, so it did not draw a card successfully
 * either.
 * 
 * playFeast
 * ------------
 * Originally I could not even run playFeast on cards that were too expensive because the game would be
 * sent into an infinite loop printing 'The card is too expensive!'. I had to modify the function to return
 * -1 just so all the other tests could execute. This would send the game into an infinite loop if it was
 * in regular play.
 *
 * Also, it appears that playFeast modifies the state of other players' decks erroneously. The playedCards amount
 * is also wrong. From playing Feast, we should increment playedCards by 1.
 * 
 * playFeast modifies the supplyAmount of the card that we want to buy erroneously as well. When the unit test
 * captures the supplyAmount before we playFeast, it's the right amount expected from initializeGame. 
 * \After we play Feast, the supplyAmount is 0.
 */