/* 
* CS 362 Winter 16
* Name: YUNSIK CHOI
*/

A gameState was set or prepared by random values.
I tried to assign random values as much as possible to numbers of cards such as ones on the deck, hand and discarded for a game.
Another gameState was created by copying the memory of the original gameState.
One runs out of the existing function, cardEffect().
The other gameState runs following steps specified in the cardEffect() function.
After running both gameStates, I compared results.


I have run into an issue in initiating a gameState.
As lecture video shows, I was trying to assign random values to each byte of a struct gameState.

/*
struct gameState G;
int i;
for (i=0; i<sizeof(struct gameState); ++i)
	((char*)&G)[i] = floor(Random()*256);
*/

However, including this caused program to crash.  Therefore, I had to comment it out.
I understand it is a very good way of making a gameState instance more randomized.
But somehow it doesn't work.


I also ran the games 500 times and 1000 times.
But the results such as lines, branches and function calls executed remain the same.
Running 500 times took about the same as running 1000 times.  It was instant to run.
