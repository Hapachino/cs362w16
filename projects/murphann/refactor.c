/*
Smithy: moved to method playSmithy. takes input of handPos and the state which
  is used to get the current player. In the method drawsCard 3 times, then
  discards the Smithy card. BUG: also gives player an action

Adventure: moved to method playAdventure, takes input of game state
  to get current player. also initializes cardDrawn, an empty tempHand and
  the counter for the temp hand. First checks to make sure there are cards
  available to be drawn. If not, shuffles discard pile and adds it to deck.
  While number of drawn treasure cards is less than 2, run draw card function
  on player. If treasure card is drawn, update count of treasure cards and add
  card to hand. If not a treasure card sends it to tempHand. When 2 treasure
  cards have been drawn, stop drawing cards and sends tempHand to discard pile.
  BUG: Also adds village cards to deck.

Great hall: moved to method playGreat_Hall, takes handPos and struct for game
  state. adds action to players turn, draws a card and then discards the Great
  Hall card. BUG: next player also draws a card.

Sea Hag: moved to method playSea_Hag, gets current user from sate. Iterates
  through each player and discards the top card in their deck and replaces
  it with a curse. BUG: shuffles next players deck

Village: Moved to method playVillage, takes state and handPos. gets current
  user from state. draws a card and increases number of actions by 2 before
  discarding current card.
*/
