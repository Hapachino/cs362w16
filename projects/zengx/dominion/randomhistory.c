
CS362 assignment 4
Xiaohan zeng

TO run test using makefile use following rules
randomtestadventurer.out
randomtestcard.out


Test strategy for adventurer card

1. I started by firstly looking at the effects of adventurer card. It has following main steps
   a. Drawing card until you have two treasure cards
   b. Discard other non treasure cards 
For step a drawing card is related to deck setup and discard setup(when there is no enough card in deck). In deck setup deck count and count&position of treasure card will cause different situations
For step b we need to check hand cards and discard cards after discarding treasure cards
In summary we can randomly generate deck setup by randomly choosing deck count, treasure card count and treasure card positions

2. In next step I took a look at the code implementation and found that the implementation of checking deck empty seems buggy
	if (state->deckCount[currentPlayer] <1) {//if the deck is empty we need to shuffle discard and add to deck// shuffle function bug: didn't use discard card just shuffle deck
			shuffle(currentPlayer, state);
		}
All it does is calling shuffle which just shuffle the deck, which is already empty. I was excited because this should be caught by my random test

So I ran the same test 1000 times in main and checked the log. Interestingly it didn't run into this bug even when deck is empty. I took a look at code again and found there is logic in drawCard to
move discard cards to deck, very tricky!
Other than this the above logic correctly detected all the bugs and function coverage shows it covers all the conditions 

Test strategy for smithy card
smithy card is a little simpler than adventurer. It just allows player to draw addtional three cards. It will change the status of deck, discard(if there are less than 3 cards in deck) and player's hand
card. So the test strategy is straightforward, I just randomly initialized deck and hands to have 0-7 cards. Also I initialized discard with a fix setup(more than 3 cards)

Same as above I ran the test 1000 times in main and it correctly captured all the bugs and code coverage shows 100% condition coverage for playSimity function