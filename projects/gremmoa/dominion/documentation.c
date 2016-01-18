playSmithy
Requires a player number (int), game state (gameState) and hand position (int).
Player draws 3 cards in exchange for discarding 1 card currently in hand.

playAdventurer
Requires a player number (int) and game state (gameState).
Reveal cards from deck until 2 treasure cards are found.  2 treasure cards are
placed in hand and other revealed cards are discarded.

discardCard
Requires a hand position (int), player number (int), game state (gameState) and
trash flag (int).
The discardCard method first checks if the trash flag is set, if not, the card
is added to the played pile.  The method then removes the card from the player's
hand according to the number of cards currently in hand.

updateCoins
Requires a player number (int), game state (gameState) and bonus (int).
The updateCoins methods counts how many treasure cards are currently in hand,
and adds to the game's state's coins variable based on the denominations of the
treasure cards present plus bonus.