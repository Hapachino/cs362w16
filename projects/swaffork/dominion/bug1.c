discardCard(): not exactly a bug, but I was surprised to learn that discard actually moves cards into the played card deck, not the discard pile. A little misleading.
playSmithy(): handCount and playedCardCount are not as expected. This is because of the bug I introduced, outlined in refactor.c, where each time a card is drawn, the card at handPos is discarded, which effectively only lets the player keep 1 of his or her drawn cards
playAdventurer(): because the drawn card variable is assigned inside the if-statement, the player is never guaranteed to actually draw treasure cards, and the hand count will be incorrect as well.
playMine(): the bug found here is that choice1 should be trashed, not discarded; this seems to be a bug in the original mine implementation. Furthermore, because of the bug I introduced, choice1 is the card in player’s hand (not choice2, as it should be).
gainCard(): deckCount is off by 10
