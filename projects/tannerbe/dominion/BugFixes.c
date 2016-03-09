-Fixed all bugs that I initially introduced in the first assignment and documented in refactor.c

embargoEffect:
-Moved check for whether kingdom card pile exists to the very start of the embargoEffect function. This ensures that the
player does not still get 2 coins in the event that an invalid pile is chosen. A player could exploit this bug by repeatedly
playing the embargo card, as actionpoints allowed, and gaining two coins, but choosing an invalid pile so that the card is 
not discarded from their hand.

adventurerEffect:
-Added discardCard statement at the end of adventurerEffect so that card is discarded.
-Commented out check for if the deck is empty in adventurerEffect because it is unnecessary since shuffling the discard pile
back into the deck is handled by the drawCard function.

endTurn:
-Added code to put all cards in the playedCards array into the discard array as specified should be done by official rules. 