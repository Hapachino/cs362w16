/****************
Philip Jones
CS362 - Winter 2016
GreatHall(cardtest4)
Smithy(cardtest3)
Adventurer(cardtest2)
Village(cardtest1)

DiscardCard(unittest4)
Shuffle(unittest3)
GameOver(unittest2)
BuyCard(unittest1)

teammate1_cierra:
Smithy card:
Bug: The after state of the handcount was higher than it should be
Description: It appears that instead of drawing 3 cards, the Smithy card is drawing 4 or more. 
How to Reproduce: Run cardTest3(). 

Village card:
Bug: The player's actions don't match the +2 that they should after using the card
Description: No actions are added when using the Village card.
How to Reproduce: Run cardTest1().

Adventurer -
Changed the deck state check to shuffle if 1 or less cards


teammate2_richard:

Adventurer card:
Bug: Too many cards remain in play at the end of the Adventurer card. 
Description: Not all of the drawn cards end up being discarded; one remains.
How to Reproduce: Run cardTest2().

Smithy card:
Bug: The after state of the handcount was lower than it should be
Description: It appears that instead of drawing 3 cards, the Smithy card is drawing 2.
How to Reproduce: Run cardTest3().
