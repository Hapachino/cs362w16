/*
smithy:
When I created the function for smithy called smithyEffect(), I input a condition that the card would only be drawn
if the position  in of the index in the loop  was less than the handpos index that comes into the function as
an argument.  This should be an easy thing to see looking at the code but tricky to notice if just looking
at the game.

Adventurer:
This is now adventurerEffect and the bug it has is that it will no longer search for gold coins.

village:
This is now named villageEffect and the number of actions is 2 * the handcount - 1 which should prove pretty 
dramatic during gameplay.

council_room:
This is now councilRoomEffect and the bug is fairly subtle...  simply 5 cards are drawn instead of 4.

outpost:
This is now named outpostEffect and  it has no bugs.
*/