/********************************************************************
Assignment 5 - Part 2
Author: Eric Anderson
Date: 2/27/16
Description: Fix all the bugs that are found in your code. First 
fix the bugs that your teammate found then fix the bugs that you 
introduced. Use GDB to debug your code and fix it. Provide a 
documentation file to discuss which bugs you fix and mention your 
code changes. Provide a documentation file BugFixes.c. In case your 
teamates already fixed the bugs and you cannot find out any bugs, 
find out the version they just submitted for assignment 2 and use 
that version. It will give you better practice with git repository 
and repository history.    
********************************************************************/

Bug 1.1: Function results in a mismatch from expected card counts in both deck and hand. 
    Smithy should leave 47 cards in deck after play, results in 46. Hand should have 52 cards
    but has 53. This can be traced to the for loop in the playSmithy() function, where the
    drawCard() function is called four times and not three because the condition is 
    "<= 3" rather than "<3."
This was the code before the fix:

playSmithy
-------------------------------------------------------------------------------------------------------------------
int playSmithy(struct gameState *state, int currentPlayer, int handPos)
{
	//+3 Cards
	int i;
    for (i = 0; i <= 3; i++)
	{
	  drawCard(currentPlayer, state);
	}
			
      //discard card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
}

This bug was fixed by changing the for loop to be less than, not <=.
Now the code is as follows:

int playSmithy(struct gameState *state, int currentPlayer, int handPos)
{
	//+3 Cards
	int i;
    for (i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);
	}
			
      //discard card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
}

I also corrected the bug I introduced of ++i to i++, the result of incrementing one 
ahead of the function caused card counts to be incorrect in my tests.  I was always
one card off.

With gdb, i discovered an error in my test.  I tested for incrementing 3 cards but i 
failed to account for the discard.  I fixed this by subtracting the discard.

playAdventurer
-------------------------------------------------------------------------------------------------------------------
Another bug within my own code was caught by the compiler, and generated an error, I 
had removed the decrementer from the state->handCount[currentPlayer]--; statement. I 
had to fix this to compile and link.

There is also a bug where if you set z greater than MAX_HAND (500) the code doesn't defend against this and can crash as a result.  


  Current Code
  while(z-1>=0){
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }

 Fixed Code
  
  while(z-1>=0 && z <= MAX_HAND){  //does not allow more than MAX_HAND
    state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
    z=z-1;
  }

I have added a check on z to make sure it checks for the upper bounds for z.

Note: CardTest4 has a bug itself. It fails to account for situations in which the combined
deck and discard piles do not have more than one treasure between them. In running batches of 
200 tests, this does happen. But it should be disregarded. Otherwise, no bugs were detected.
No action taken on my part.

playCouncilRoom
-------------------------------------------------------------------------------------------------------------------
In the playCouncilRoom function, there seems to be some stray code.  My cuurent version has 

    if(currentPlayer == 2){
        drawCard(currentPlayer, state);
    }

this causes player two to gain an extra card.  The action for playCouncilRoom is +4 cards for currentPlayer, +1 Buy,
and +1 card for all other players.  Each of these cases is handled so I have commented out this code.

Another issue I discovered with gdb is with the statement 
    if(i > currentPLayer) {
      drawCard(i, state);
    }

this mis handles the case where this could be player 1 or 2 and will miss the + 1 card for player 0 or 1 depending on whos turn it is.
I changed this to 
    if(i != currentPLayer) {
      drawCard(i, state);
    }
This lead to some really nasty wrong card counts.  The problem is that you don't catch it until it shows someplace else in the game.
I had a very hard time reproducing the reported bug for Salvager.  This may be a root cause to that issue.


Steward
-------------------------------------------------------------------------------------------------------------------
In steward, the action is to trash 2 cards in hand.  The code will discard the two cards but not trash them.

    discardCard(choice2, currentPlayer, state, 1);
    discardCard(choice3, currentPlayer, state, 1);

Not sure if this is a bug or the interpretation of trash is discard.

Feast Card.
-------------------------------------------------------------------------------------------------------------------
I noticed, while in gdb, that the Feast card seems to be doing the wrong thing.  I didn't write a test for this card 
but I see errors. I assume this will get fixed in another assignment.


Card Test 4: Salvager
-------------------------------------------------------------------------------------------------------------------
    Bug 1.1: I detected this bug when I tested my own code with this function and it reppears here. 
    The problem is that if the card is fed a player choice of "0" the program interprets this 
    choice as "no choice" rather than the card indexed at "0." With a random 50 card hand, this 
    happens with about .02 probability. Significant. 
    **To recreate:** 
    Give the playCard function a player choice of 0, note what card is at the 0 position in the player 
    hand, and then counts instances of that card in the player hand before and after the card is played. 
    They should be different, when card removed, but they will be the same.

    I think this is an invalid bug based on the Salvager function.  The function looks for choice1
    to be equal to 1 or greater to increment the coins and then trashes the card.  it then discards the card the play is playing (in this case  Salvager)
    passing it a value of 0 will cause the coins not to be incremented and the card thrown away.
    I have instrumented the test code to show what is actually happening. With a value of choice1 of 0, we are discarding
    one instance of the salvager card.  The test is looking for the discardedCard = to choice 1 but this
    is never getting executed.

    To fix the test, test to see if choice == 0 if it is, then test for the discard and make sure the coins are not changed (this seems counter to what the card is supposed to do)
    and then if choice1 > 0 then test the coins and the discard as is done here.

    Finally, the test does expose a difficiency in Salvager.  The expectation is that salvager will discard itself and credit coins
    what if it is trashing itself?  It get discarded but no coins are credited.  It should credit 4 coins = to its own cost.  I'm not changing
    the code in dominion.c as choice1 = 0 is not valid.

isGameOver function
-------------------------------------------------------------------------------------------------------------------
While walking through the code with gdb to solve the Salvager bug, I ran across a bug in the isGameOver function.
When 3 supply piles are empty. The function only checks supply piles for cards 0-25. This means that when seahag or treasure_map
are empty the function will not return 1 to indicate the end of the game.

prior to fixing the code read:
  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)

After the bug fix: 
  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 27; i++)

I also had a bug I discovered with one of my tests where some of my tests had a negative supply count 
indicating either a bad game state of intialization issues.
To fix this, changed the == test to <= to account for a negative supply count.

the code before the fix looks like this:

j = 0;
  for (i = 0; i < 27; i++)
    {
      if (state->supplyCount[i] == 0)

The code after the fix looks like this:
 j = 0;
  for (i = 0; i < 27; i++)
    {
      if (state->supplyCount[i] <= 0)

General debugging
-------------------------------------------------------------------------------------------------------------------
To quiet a compiler warning, I had to change the line;
int cardDrawn;

in cardEffect to

int cardDrawn = 0;

I have a general error in my tests.  I failed to account for the discard on a player's turn, I had
expected that the pre and post hand counts would be the same but when calling the function, it discards and thus
the hand count would be decremented vs. a player who had not played.  I fixed this in all my tests.

Agan's Rules
-------------------------------------------------------------------------------------------------------------------
Agans' principles that apply particularly well here:

#2 - Make it Fail: Finding out what caused the problem helped me better understand what I was trying to accomplish in 
my code. While debugging I was able to not only look dominion.c but also testdominion.c so I was able to to fix up 
some little things along the way that I didn't notice before as well.

#3 - Quit Thinking and Look: Using gdb to manually step through my code actually took up a lot of time. If I had 
just looked at my code or had somebody else look at my code (which happened through my team mates) the problem 
may have been identified more quickly.

#8 - GET A FRESH VIEW: I should have asked someone else to look at my code. Looking at my own code usually 
takes a while to spot problems because since I'm the one who wrote it, in my mind is going to seem correct the 
first few times I look over it. 