Xiaohan Zeng
CS362
assignment5

/***********************************
Teammate1: jones8(Emmalee Jonese)
*************************************/
________________________________________
1: test adventurer
Unhandled exception at 0X01125A4D happened; it shows "z":the card in hand number is 14165 when ask for break,which means player does not get enough tresure card after getting so many card in reuse card stack.This is because when I intialize the game in cardtest2, the only treasure card I provided is copper(4).


reproduce:

1: Initialize a game; copy the hand card status
2: set G.deck[thisPlayer] has 2 copper and other cards are not silver or gold
3: run cardEffect with adventurer

Expected Result: adventurer card moved from hand and 2 copper add to hand.

Result: segment fault

____________________________________________
2: test steward 
Get error message shows under test steward card trash 2 cards: played card number not correct. The played the played card number +3 after run. One of the three card should be the steward. Other two could be cards need to trash.

reproduce:
1: initialize a game
2: set player play with steward card and run cardEffect with steward;
3: set choice 1 == 3; set 5 card, random choose trash 2 of them;
4: check card on hand, played card and card on deck are correct;

Expected Result: G.playedCardCount = 0 testG.playedCardCount =1 (which is the steward card played)

Result: testG.playedCardCount = 3

/***********************************
Teammate2: richatan(Tanna Richardson)
*************************************/
__________________________________________________
1: test adventurer
error message shows: card discard not correct. Also hand count acutally get is 2 more than expected. Since I found that this function has a bug (forget to discard the played card), so the handcount expected is 6(based on the deck card I set), there are 2 more cards in hand now.

reproduce:
1: initialize a game
2: set deck card which 2 treasure cards: one at the begin place and 3 non-treasure flowing then one more treasure
3: cardEffect to play adventurer
4:compare handcard deckcard discardcard.

Expected: handcard is with 2 more treasure and discard the played card so should be 6

Result: handcard is 9

_____________________________________________________________
2: test smithy
error message shows that handCard number not correct, also the deck count is not correct.
HandCard is one more than expected when deckcount is one less than expected,it could be one more card is drawed from deck

reproduce:
1: initialize a new game
2: record the handcard count and deckcard count
3: run cardEffect with smithy
4: compare the result with expected 

Expected: handcount should be 7 and deckcount should be 2

Result: handcount is 8 and deckcount is 1