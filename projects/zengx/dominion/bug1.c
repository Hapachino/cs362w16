/* Xiaohan Zeng bug report for assignmen3
1: cardtest4.c for Steward

BUG1:happens when choice3 is the last one

	When random trash 2 card from hand, if the first trash card is before second trash card
	choice 3 is the last one
	The second card will not trash correctly 

	This bug is caused by the void playSteward function
	in else
	{
			//trash 2 cards in hand
			discardCard(choice2, currentPlayer, state, 1);
			discardCard(choice3, currentPlayer, state, 1);
	}
	If choice2 =3 choice3=4
	after trash 3 the largest position hand card has is 3, 4 is -1 and it will be switch with position 3.
	The hand array will be  x x x -1 x

	We need to check if choice 3 is the last one
	
BUG2: When not check input choice2 and choice3 if valid.
		Happens when handcount < 2 ; choice2 >= handcount ; choice3 >= handcount 

Another bug is if we only have 1 card in hand but we need to trash 2 card
when handcount =1 trash not work correctly
choice2 == choice3 (if user enter the same number)
trash not work correctly
choice2 <0 choice3<0 or choice2 >= handcount choice2 >= handcount

All these cause by discardCard not check input

BUG3: choice1 == 1 and choice1 ==2 action switched, this is the bug I introduced in last week

2: cardtest3.c for village

BUG 1: action not add correctly. This is the bug I introduced in last week
BUG 2: if keeping play village n times, there is a possibility of no card on deck, but there is no check for card on deck before drawcard.


3: cardtest2.c for adventure
BUG 1: didn't discard the played card by the end of this function
BUG 2: In playAdventurer 
	while (z - 1 >= 0) {
		state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z - 1];
		state->discardCount[currentPlayer]++;
		z = z - 1;
	}
	discardCount[currentPlayer] ++ run twice here
BUG 3: z - 1 > = 0  missing =  is the bug introduced in last week
BUG 4:playedCard and discardCard pile is not cleared used in this whole program:
Not sure if discardCard means reuseable card or PlayedCard means reuseable card in this program.

int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
{
	
  //if card is not trashed, added to Played pile  // which means playedCard shoule be resued 
  if (trashFlag < 1)
    {
      //add card to played pile
      state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos]; 
      state->playedCardCount++;
    }
	
In other functions, discard card means put it back into this playedCards array
However in drawcard() when deck card is 0, they used discardCard for shuffler.
 
4: cardtest1.c for smithy
BUG1: find the bug from last week. only draw 2 card instead of 3

5:unittest1.c for discardCard:

BUG1: didn't check if handPos is valid or not(when handPos > handcount) 
BUG2: As I mentioned in 3.BUG4, if discard array and count tracking the discard(no use anymore) in this game, it should increase when trash flag is on.
But it is not change here.

6:unittest2.c for gainCard:

7:unittest3.c for updateCoin
No Bugs Found

8:unittest4.c for isgameover
NO Bugs Found





























*/