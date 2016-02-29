Unit Test 1 - getUpdatedCoins:
	Statement: 	100% 
	Branch: 	100%
	Boundary:	For my boundaries, I wanted to make sure I checked as many options as I could.
			 	This included all copper, silver, and gold, and then a mix of them, and finally a mix 
				of all coins and cards, to ensure it wasn't counting other cards. This is all done 
				through a semi random testing to create the state, because I feel it is important
				to have tested this program with many different states.

Unit Test 2 - isGameOver: 
	Statement: 	100% statement
	Branch: 	100%
	Boundary:	To test my boundaries, I used the semi-random testing in order to populate my game state
				and accounted for if province was either 0 or not 0, and then would randomly decrement 
				items within supplyCount until three of them were 0. Every time I would assert that the 
				value wasn't gameOver, and then once it exited, I asserted that it was gameover. Each time 
				it passed.

Unit Test 3:
	Statement: 	100%
	Branch: 	100%
	Boundary: 	For boundary testing, I chose to make sure I included that if the deck was 1 or 0
				that the deck was still creating the correct results. I checked randomness by making 
				sure that the values weren't more than 1/4 of the deck count in the same order. Any 
				more than that would be pretty unlikely, although with over 2000 tests ran, none of them
				returned with more than 1/4 repeatd 
				 

Unit Test 4 - :
	Statement: 	100%
	Branch: 	unsure - still buggy
	Boundary:	The goal of this is to create a random hand, then test to see if cards from the correct
				places are getting pulled. 

Card Test 1 - Smithy:
	Boundary:  

Card Test 2 - Adventurer:
	Statement:
	Branch:
	Boundary:

Card Test 3 - Village:
	Statement:
	Branch:
	Boundary:

Card Test 4 - Embargo:
	Statement:
	Branch:
	Boundary: 
	
How to imporove test sweet - 
	The biggest things I can do are get my card tests going, and start adding more functions to my suite.
	Currently, I'm only covering about 30% of my code, in order to increase this, I could test more functions
	that are critical, such as draw, play, and discard. By covering those, I would increase the coverage a lot.
	Also having a test suite that ensured all of the cards were covered, would also increase the coverage. 
		
	
Lessons learned:
	Practice what I preach -
		I'm also a TA for the intro classes, I constantly remind people to start things early.
		However, starting things early is not my forte. As always, start things earlier.
	
	Going from python to c, is like jumping off a building and trying to walk again. It's slow and painful.
	
	Trying to push your assignment when a lot of other people are too, is not fun. It's a lot like wax on wax off,
	with a lot more banging your hands on the keyboard. 
			
	Terribly formatted code is my nightmare. This code drives me nuts. The mix of tabs and spaces is not okay.