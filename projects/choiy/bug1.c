While testing Adventurer card, I found that top card of hand is always copper.

cardDrawn = G.hand[currentPlayer][G.handCount[currentPlayer] - 1]; //top card of hand is most recently drawn card.

Running test result shows cardDrawn value is 4, which represents copper card.

I think Random() function generates the same result per program's running.