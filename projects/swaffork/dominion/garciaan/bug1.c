BUGS FOUND:

--ADVENTURER--
When the adventurer card does not get stuck in an infinite loop due to the
bug that I introduced, it fails 1 test. It cannot correctly handle when there
are no treasure cards in the deck or discard. It ended up repeating an arbitrary
amount of times which discarded all the cards in my hand and I ended up with
a hand count of -36.

--discardCard--
This is not a bug as much as an unexpected path of execution. I expected 
this function to actually move the card to the discard pile, but it did 
not do this. For the first test that required this that I used, it failed 
the discard test because there was nothing in the discard pile. I realized
that the actual discard action happens in endTurn, where it moves cards from
playedCards to the discard pile. discardCard only sets the card as played and
removes it from the hand.



