/*
  Smithy:
    Bug: affects more than it should
      Fix: removed code that gives player another action

  Adventurer:
    Bug: does not discard correctly
      Fix: added discardCard method to the method so that Adventurer card is discarded

    Bug: Adventurer counts village as treusure
      Fix: Removed logic which increses tresure count when villager is drawn

  GreatHall:
    Bug: Next player does not have expected hand count
      Fix: Removed function which draws a card for next player as well

  SeaHag:
    Bug: next player's deck gets shuffled
      Fix: Removed shuffle method for next player
*/
