As for the unittests, I didn't use any function where I implemented previous bugs so no testing was required in those files.
But as for card Smithy, Adventurer, and Great Hall each have a bug implemented from the previous week that results in
an assertion error.

Smithy returns 2 cards instead of 3 which alters the game states pre and post during a copy initialization of the game.

Adventurer does not shuffle the deck if it is empty but the true error here lies with the deckCount.

Great Hall plays identical to Village. It generates 2 actions instead of 1.
