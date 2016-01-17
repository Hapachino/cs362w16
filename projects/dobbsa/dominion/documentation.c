Smithy - implemented in cardEffect()
Effect: Draw 3 cards.
- loops through three calls to drawCard()
- is discarded

Adventurer - implemented in cardEffect()
Effect: draw cards until 2 treasure cards have been drawn, then discard the rest.
- loops until number of treasure cards drawn is equal to 2.
- if the deck is empty, replenish by shuffling discard.
- call drawCard()
- check if drawn card is a treasure card, and increment the drawntreasure variable if so
- if card is not a treasure card, add it to temphand and increment z (counter for temphand)
- after treasuredrawn is equal to 2:
- loop through discarding each temphand card until they have all been discarded.



discardCard()
Takes 4 parameters:
    int handPos
    int currentPlayer
    gameState *state
    trashFlag

- trashFlag tracks if card is to be trashed or discarded.
- if card is not trashed, add to Played pile and increment playedCardCount (contained in state struct)
- set position of played card to -1
- remove card from hand:
    - if last card in hand was played, decrement hand count by 1
    - if there is only one card in hand, decrement hand count by 1
    - else, replace discarded card with last card in ahnd and decrement hand count to 1


updateCoins()
Takes 3 parameters:
    int player
    gameState *state
    int bonus
- reset coin count
- loop through players hand
    - for each copper, add 1 coin
    - for each silver, add 2 coins
    - for each gold, add 3 coins
- add bonus parameter to coins count