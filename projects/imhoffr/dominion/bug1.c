/*********************

Found a bug in how playadventure (and the original adventurer function) calls shuffle.
 It calls shuffle if the deck is empty, but shuffle (when the deck is empty) returns
 -1 without changing the deck.  

*********************/