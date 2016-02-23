smithy card
  Action card.
  Costs 4 gold, determined by the getCost() helper method.
  Player draws 3 cards then discards the card, switch statement in cardEffect().
  Gives player no additional buys.
  Gives player no additional actions.
  Assigned index is 13 (enum).



adventurer card
  Action card.
  Costs 6 gold, determined by the getCost() helper method.
  Player reveals cards in deck until two treasure cards (copper, silver, or gold) are revealed then the two
  revealed cards are put in the players hands. The other revealed cards are placed into the discard pile.
  Switch statement in cardEffect() method determines result. Cards are drawn
  from deck while 'drawntreasure' is less than 2, once two cards are drawn, shuffle() is called.
  If deck has less than 1 card in it, then discard is shuffled back into deck.


discardCard()
  Method
  Accepts 4 arguments:
    int handPos - Card position in hand array to discard.
    int currentPlayer - Players who's hand it is.
    struct gameState *state - Current game state.
    int trashFlag - Flag to determine if the card should be discarded to trashed.
      If trashFlag = 0, then card is just added to played card pile 'discard pile'.

    Once the card is played it is set to '-1' indicating a 'played' status then the
    player's total hand count is decremented 1.
    If the last card in hand array is played the hand array is decremented.
    If the card played with in the middle of the hand then the discarded card's position
    is filled by the last card in the hand before the hand array is decremented one.


updateCoins()
  Method
  Accepts 3 arguments:
    int player - Player who's coins are to updated
    struct gameState *state - Current game state
    int bonus - Amount of coins added by Action cards during the players turn. (e.g., 'Feast' adds
    5 coins to the players available 'pot' when played.)

    Loops through each card in a players hand and add's coins to the players available
    coins to purchase an item.
    If coin is copper, add 1.
    If coin is silver, add 2.
    If coin is gold, add 3.
    After each coin is added to total a bonus amount is added to the coin total.
