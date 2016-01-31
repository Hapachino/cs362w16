Discovered Bugs

unittest1.c
Tested: initializeGame();
This test didn't uncover any bugs in the initializeGame method.
The test tested that games initilize correctly for valid player amounts (2-4)
as well as made sure it rejected invalid player (0, 1 and 5) totals.

These tests also checked to make sure the correct number of victory cards and treasures were initiized
based on the number of game players. It also made sure the correct number of cards were
placed in each players deck, hand, and discard pile.


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
This test didn't uncover any errors in the updateCoins method.
This function did prove multiple business cases for the updateCoins function.
It uncovered:
- Coin total isn't correctly calculated when a player's hand has a combination of treausure
and bonus coins.
