Bugs fixed:

Smithy 
Bug: Playing Smithy cause each other player to draw an extra card much like Council Room
Fix: Deleted second for loop that was a copy of the one beginning at line 1280

Adventurer 
Bug: Ignores copper cards. Will only count gold or silver cards for the treasures.
Fix: changed the second silver variable in line 1307 to copper

Village 
Bug: Causes the other players to discard one card as well as the current player.
Fix: Removed for loop used to cause all other players to discard a card.

Council Room 
Bug: Each other player gets two cards instead of the normal one
Fix: Deleted extra drawCard call that caused players to recieve an extra card