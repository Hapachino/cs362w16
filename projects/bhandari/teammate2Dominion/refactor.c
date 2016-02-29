- Created a seperate function for adventurer, smithy, remodel, baron,  and council_room.  These functions are all playX where X is the name of the card with the first letter capital (ex. playSmithy),  found at the bottom of domionion.c

- Modified the loop in smithy from for (i = 0; i < 3; i++) to for (i = 0; i <= 3; i++) to draw 1 more card

- Inside adventurer changed if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold) to if (cardDrawn == copper || cardDrawn == gold) making so silver does not count towards the draw.

- In remodel moved discardCard(handPos, currentPlayer, state, 0) to before it checking if the choices are a valid remodel so you would lose the card without a valid choice gaining no effect.

- Inside the playCouncil_room function removed the line, state->numBuys++; , so the card no longer gives the player an extra buy.

- Inside baron before the first main while loop int card_not_discarded = 1; was changed to int card_not_discarded = 0; making it so   the while loop is never acctually entererd.