Discovered Bugs

unittest1.c
Tested: initializeGame();
This test didn't uncover any bugs in the initializeGame method.
It proved:
- The games initilize correctly for valid player amounts (2-4)
- Games with invalid player totals (0, 1 and 5) were rejected
- The correct number of victory cards and treasures were initiized based on the number of game players
- It also made sure the correct number of cards were placed in each players deck, hand, and discard pile.

unittest2.c
Tested: buyCard();
This test also didn't uncover any errors in the buyCard method.
This function did prove multiple business cases for the buyCard function.
It proved:
- A player can't buy a kingdom card with no buys available
- A player can't buy a kingdom card with no supply available
- A player can't buy a treasure card with no buys available
- A player can't buy a treasure card with no supply available
- A player can't buy a victory card with no buys available
- A player can't buy a victory card with no supply available
- Each purchase requires the correct amount of coins
- A player purchasing an item subtracts 1 buy from their available buys
- A buy happens during phase 1
- Buying a card puts the newly purchased card in the discard pile

unittest3.c
Tested: updateCoins();
This test uncovered one error.
It uncovered:
- Coin total isn't correctly calculated when a player's hand has a combination of treausure
and bonus coins.

unittest4.c
Tested: drawCard();
This test didn't uncover any errors in the drawCard method.
It proved multiple business rules for the drawCard method.
It proved:
- A players hand total increases by 1 after drawing card
- A players deck total decreases by 1 after drawing card
- A players discard pile stays the same after drawing card
- A players hand total increases by 1 after drawing card with no cards in deck
- A players discard pile correctly shuffles back into their deck when no card in deck and they draw a card
- None of the other players hand, deck, or discard pile sizes change.

cardtest1.c
Tested: playSmithy();
This test uncovered multiple bugs with the playSmithy() method.
- The player who played smithy hand size increased by 3 instead of 2
- The player who played smithy deck size decreases by 4 instead of 3
- The player who played smithy action count didn't decrease
- The smithy card doesnt correctly got into the played pile, instead it goes directly to discard

cardtest2.c
Tested: playAdventurer();
This test uncovered multiple bugs with the playAdventurer() method.
- The players action count doesn't correctly decrease
- It doesn't correctly remove the adventurer card from the players hand
- It doesn't correctly place the adventurer card in played card pile after playing it
- It doesn't correctly place two treasure cards in the players hand after playing it
- It doesn't correctly check that the selected card to play is an adventurere card
- It doesn't correctly suffle the discarded cards back into the players deck if their deck is empty
- It doesn't add one treasure to the players hand if their is only one treasure in their deck


cardtest3.c
Tested: playRemodel();
This test uncovered multiple bugs with the playRemodel() method.
- Playing remodel and selecting a valid card to trash doesn't decrease handsize by 2
- Playing remodel doesn't correctly decrease the players actions
- Playing remodel doesn't correctly remove it from the players hand
- Playing remodel doesn't place the card in the players played pile
- Playing remodel doesn't correctly place the 'purchased' card into the players discard pile
- Playing remodel doesn't correctly place the 'trashed' card in the trashed pile
- Attempting to buy a more expensive card than the trashed card still removes one card the players hand
- Attempting to buy a more expensive card than the trashed card increases the players discard pile
- Error checking for cases of to expensive of card doesn't work


cardtest4.c
Tested: playVillage();
This test uncovered multiple bugs with the playVillage() method.
- Playing village doesn't keep the players hand size the same, it decreased by 1
- Playing village increased actions by 4 instead of 2
- Playing village keeps buy amount the same, instead it subtracted two
