Refactored the following functions from the switch statement into their own functions:
playSmithy(), playAdventurer(), playFeast(), and playMine(). I also changed the headers
in the dominion.h file to match the new function headers of the functions above. There
were bugs introduced purposely as well. These bugs will not issue any compiler warnings 
or errors. Feast and Mine cards now grant additional advantages while Smithy is now less
powerful and Adventurer is useless.

playSmithy() bug
- only adds 2 cards instead of 3

playAdventurer() bug
- drawn treasure is set to 2 so the loop never executes 

playFeast() bug
- allows 15 coins to buy instead of 5

playMine() bug
- Allows player to buy a card that is +10 coins of the trashed card


