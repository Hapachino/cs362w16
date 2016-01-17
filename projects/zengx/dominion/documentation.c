// CS 362 Xiaohan Zeng assignment2


Smithy cards:
The case smithy is in dominion.c cardEffect() function.  This card will let player get 3 card. In function, when player playcard:
playCard() function will check if the player has enough actions; 
get the card value of the player’s choice by handCard() function;
check if it is an action card;
then if the card value is smithy the cardEffect() function will go to case smithy;
in case smithy: first will be a loop to draw 3 new card for the player;
then this smithy card will be discard by discardCard() function;

adventure cards:
when the card value is adventure the cardEffect() function will go to case adventure;
while the drawtreasure (the number of treasure card) is smaller than 2:
if there is no cards on deck: shuffle card;
draw a card and put it as top card;
if the card is a treasure card: add treasure card number;
if the card is not : put it into a temp arr and remove the top card;
after getting 2 treasure cards, discard the cards in temp.


int discardCard()
input:
gamesate is for tracking the game status for now. The implementation of all status are in dominion.h file;
The handpost is for the card to process in this function;
CurrentPlayer: who is playing
trashFlag: check if this card need to be trash
function:
if the card is not trashed, put it in to played pile;
set the players handcard pos of this card to -1(show this card is palyed)
if this car position is at the last one or it is the last card in hand, we just simply reduce the cards in hand number to discard it;
else we need to switch this card which needs to be discarded with the last one then reduce the cards in hand number.

updateCoins():
input:
player: who played
state: tracking needed status
bonus: coins get from action card
function:
reset this round coins count to 0;
loop through the player’s card, calculate the coins;
add bonus coins from action card to total coins.


