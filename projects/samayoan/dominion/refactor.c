 /*
Nelson Samayoa
CS 362
Documentation of refactored code
Onid: samayoan

CHANGES & INTRODUCED BUGS
	1) Smithy
		I moved the smithy code into a function called smithyEffect. In the switch statement
		I have a call to smithyEffect passing in the handPos, currentPlayer, and state variables.
		I introduced a logic bug in the for loop which increments the index before checking it (++i).
		It was incrementing after checking (i++). This bug will cause the function to draw only 2
		cards for the player, rather than the expected 3 cards.

	2) Adventurer 
		I moved the adventurer code into a function called adventurerEffect. In the switch statement
		I have a call to the new function passing in the drawntreasure, currentPlayer, 
		and state variables. I changed where the comments were because I felt they were written 
		in a way that made the code ugly.
		The bug I introduced was in the line that was originally 
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]
		I added "=copper" to the end and the result was this:
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1]=copper
		This bug will make it so a user always gets two copper treasure cards when playing the 
		adventurer card. Not only will it prevent the user from getting gold and silver cards,
 		but it will discard that possibly non-existant copper card, thus introduce other unknown bugs.
	
	3) Cutpurse
		I moved the cutpurse code into a function called cutpurseEffect. In the switch statement
		I have a call to the new function passing in the currentPlayer and state variables. The bug I 
		introduced is in line "if (state->hand[i][j] == copper)". I changed it to 
		"if (state->hand[i][j] == gold)" which will discard the very useful gold treasure card.

	4) Embargo
		I moved the embargo code into a function called embargoEffect. In the switch statement
		I have a call to the new function passing in the choice1, handPos, currentPlayer, and 
		state variables. The bug I introduced is in line "discardCard(handPos, currentPlayer, state, 1);"
		I changed it to "discardCard(handPos, currentPlayer, state, 0);"
		The bug is very sutle and simply causes the embargo card to be added to the Played pile rather 
		than the trash.

	5) Salvager
		I moved the salvager code into a function called salvagerEffect. In the switch statement
		I have a call to the new function passing in the choice1, handPos, currentPlayer, and 
		state variables. Since the code in the functions for the four cards above all have bugs,
		I did not introduce any bugs into the salvagerEffect function.

*/
