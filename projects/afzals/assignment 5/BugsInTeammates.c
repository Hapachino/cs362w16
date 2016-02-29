***************************************
Bugs in Kyle's code, username collikyl*
***************************************

According to the tests I created I was able to identify 2 bugs. The first
bug I found was in the play_village function. The village card is supposed to 
draw a card, however the number of cards in the player's hand did not increase. 
When I ran the test it indicated that the expected number of cards in the hand
was 6 but the actual number of cards in the hand was 5. Upon reviewing this after
sending it to my teammate I realized this is incorrect. The card should be discarded
after it is played so this is not actually a bug.

The 2nd bug that I found was in the fullDeckCount function. This function should show
the total amount of cards, but does not do so accurately. When I ran the test the 
expected number of cards in the deck was 23 but the actual output was 0.


****************************************
Bugs in Jack's code, user name holkeboj*
****************************************

The first bug that I found in this code was with the fullDeckCount function. This 
leads me to believe that there is something wrong with this function in the original
dominion code we were given. The expected amount of cards was 25 but the result was 0.


The 2nd bug that I found in the code was with the Smithy card. I believe that the drawCard
function has issues to begin with, but on this function when the handPos passed to the function
is 2 there were only 4 cards in the players hand after running the function. However when there 
are other numbers passed in for handPos there are 7 cards in the players hand after running the function.