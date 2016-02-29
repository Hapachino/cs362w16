Bugs introduced to refactored action cards:
1)playSmithy: the card is trashed rather than set to the discarded pile when discardCard() is called.

2)playAdventurer: The last card in the tempHand does not get discarded back into the discard pile.

3)playFeast: in the hand resetting portion, the for loop stops a card short of the actual hand count.

4)playCouncil_Room: draws 5 cards instead of 4 because of the for loop.