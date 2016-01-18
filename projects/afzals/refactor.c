The cards that I selected to refactor are Adventurer, Smithy, Village, Great Hall, and Outpost. 
I was unsure if we were supposed to change the code so the function calls were not part of the 
switch statement, but after rereading the assignment a few times I did not think it was necessary, 
I apologize if this was incorrect. In Adventurer I deleted the section for handling situations where 
there are no cards left in the deck and the discard pile is shuffled in. This bug will only arise in 
certain situations where adventurer is chosen and the deck is empty, so it is not something that should 
affect every game. On the Smithy card I changed the for loop to read (i=0; i≤3; i++) making it less 
than or equal to will draw 4 cards each time instead of 3. I changed the Village card from 
state→numActions = state→numActions + 2 to just read state→numActions + 2, this will make it so this 
card ends up doing nothing. For Great Hall I pass 1 to the discardCards function as the trash flag instead of 0. 
I tried it out and the program still runs, these bugs have an effect but they are subtle in that they
do not crash the program. 