bugs introduced:

Adventurer - 
* Changed the deck state check to shuffle if 1 or less cards

Smithy - 
* Changed < to <= in order to draw 4 cards instead of 3

Village - 
* Shouldn't add two action points, instead it is basically a useless statement

Embargo -
* The return in the case statement does not deal with if Embargo returns -1, so it will return 0 every time. 

Outpost - 
* No bugs intdroduced, however it was refractored