- Created a seperate function for adventurer, smithy, remodel, baron,  and council_room.  These functions are all playX where X is the name of the card with the first letter capital (ex. playSmithy),  found at the bottom of domionion.c

- Modified the loop in smithy from for (i = 0; i < 3; i++) to for (i = 0; i <= 3; i++) to draw 1 less card

- Inside adventurer changed if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) to if (cardDrawn == copper || cardDrawn == silvar || cardDrawn == gold) creating a typo on silver so drawing silvers will not count towards treasure drawn.

- In remodel gainCard(choice2, state, 0, currentPlayer); which gives the card they were picking to remodel to, I changed the choice to choice1 so they just get remodel again. gainCard(choice1, state, 0, currentPlayer);

-Inside the playCouncil_room function removed the line, state->numBuys++; , so the card no longer gives the player an extra buy.

- Inside baron before the first main while loop int card_not_discarded = 1; was changed to int card_not_discarded = 0; making it so the while loop is never acctually entererd.