BUGS FOUND

### _adventurer() ###
- Discarded cards are not removed from hand (introduced bug)
- Adventurer card is not discarded

### _smithy() ###
- Discard pile size does not increase when smithy card is discarded

### _village() ###
- Village card disappears from hand but does not appear in discard pile, discard size does not increase

### case council_room ###
- Discard pile size does not increase when council_room card is discarded

### buyCard() ###
(passes all tests)

### discardCard() ###
- discardCount does not increment
- Card is not added to discard pile
- When discarding from an empty hand, hand count decreases to -1 and an "empty" card is added to the played cards pile.

### isGameOver() ###
(passes all tests)

### scoreFor() ###
- Score calculation is incorrect - fails all tests. Verified that the test's calculation should yield the correct result.