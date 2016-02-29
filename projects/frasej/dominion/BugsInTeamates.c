Jennifer Frase 
CS 362 Assignment 5

/**Hardesc bugs**/
getCost():
passed

updateCoins():
passed

scoreFor():
discard and deck score are not coming out right, all deck scores are 0 and discard
scores are never right. For example when there were 486 great halls in the deck,
which should give 486 points, will instead give 0 for the deck and if all the great
halls are in the discard then the score will instead be 971 instead of 486.

isGameOver():
does not notice when card stacks for sea hag and/or treasure map are empty

smithy:
The card discarded from the hand is not the smithy card. (random)

seg faults when the deck and discard counts are 0. (unit test) (had to use GDB to
figure this out.)

adventurer:
The card has trashed 1 card.

gardens:
passed

sea hag:
sea hag does not discard the itself from the hand at all let alone into the 
playedCards array.

(no refactoring was required)



/**Choiy bugs**/
getCost():
passed

updateCoins():
passed


scoreFor():
discard and deck score are not coming out right, all deck scores are 0 and discard
scores are never right. For example when there were 486 great halls in the deck,
which should give 486 points, will instead give 0 for the deck and if all the great
halls are in the discard then the score will instead be 971 instead of 486.

isGameOver():
does not notice when card stacks for sea hag and/or treasure map are emptycar

smithy:
A card is added to the next players hand from their deck; ie if player 1 uses the 
smithy player 2's hand gains a card from player 2's deck. (both random and unit)

adventurer:
Adventurer does not discard the adventurer card from the hand at all let alone into
the playedCards array. (randomtestadventurer)

segfaults if there are only copper treasure cards (unittest) (had to use GDB to
figure this out)

gardens:
passed

sea hag:
sea hag does not discard the itself from the hand at all let alone into the 
playedCards array.

(no refactoring was required)


