# Smithy
int useSmithy(int currentPlayer, struct gameState *state, int handPos)
Bug: calls discardHand() with trashFlag set.

# Adventurer
int useAdventurer(int currentPlayer, struct gameState *state)
Bug: fails to decrement temphand count when removing cards from temp hand inside while loop
  
# Village
int useVillage(int currentPlayer, struct gameState *state, int handPos)
Bug: calls discardHand() with trashFlag set.

# Great Hall
int useGreat_Hall(int currentPlayer, struct gameState *state, int handPos)
Bug: draws an extra card from deck

# Outpost
int useOutpost(int currentPlayer, struct gameState *state, int handPos)
Bug: fails to discard card.