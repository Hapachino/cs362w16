Basically the code that were in the switch statements were encapsulated into functions. The arguments for the functions are all the same. It is passed the gamestate pointer and a pointer to a new struct called infosStruct that will store the values of all the variables, except that of gameState, within the cardEffect function. Since each function uses different code to create the kingdom card's effect, this makes it so that whatever values are needed for that particular effect are called from the infosStruct. 

The bug that was introduced was inside discardCard(...). The curly brackets surrounding the statements of the last else statement were removed, resulting in that only the first statement is executed. Since this function is common to all of the new functions, all the new functions are affected. 

---------------------------------------------------------------------------
One bug was found in smithycard. The handCount does not increment correctly. It increments by only 2, should be 3;

One bug in village card - players hand does not increment by one card