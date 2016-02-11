/**
 * randomhistory.c
 * Student: Jeannine Amm
 * Email:  ammj@oregonstate.edu
 * Class: CS362w2016
 *
 * randomtestcard.c
 * Card:  Baron
 * Previously this card was tested under cardtest3.c
 * Random inputs generated:
 * 	handCount: the handCount was generated randomly to test different hand sizes
 * 	hand: the hand was generated randomly to test different configurations of cards
 * 		in the hand.  Randomly choosing the cards also allowed for testing with different
 * 		numbers of estate cards in the hand.
 *
 * 	discardCount: the discardCount was generated randomly to test different discard
 * 		sizes.
 * 	discard: the discard pile was generated with random cards to test different
 * 		configurations of cards in the discard pile.
 *
 * 	deckCount: was generated randomly to test different deck sizes
 * 	deck: the deck pile was filled with randomly generated cards.  As the deck is not used
 * 		in this function randomizing the deck only ensured different sized decks did not effect
 * 		play.
 *
 * 	The deckCount, handCount and discardCount were constrained so the sum was not
 * 	greater than MAX_DECK.  As we were testing the function of the card not the
 * 	external functions I felt overloading the probable number of cards that could
 * 	end up being discarded was not needed at this level.  With that said, without
 * 	assertion statements and proper checks prior the function of this card, if given a
 * 	discard pile that was already at max capacity, would throw a SEGMENTATION FAULT
 * 	eventually.
 *
 * 	supplyCount[estate]: the estate supplyCount was randomly generated to test with
 * 		different levels estate cards available to draw from.
 *
 * 	supply of estates in the hand were calculated from the randomly generated cards in
 * 		the hand.
 *
 * Improvement in coverage:
 * 	Random testing did improve the branch coverage for this card.  It found boundary tests
 * 	that were not in the original test that triggered if the game was over or not.  The
 * 	running of the isGameOver function also improved overall branch coverage as new branches
 * 	were tested.
 *
 * 	Statement coverage was improved as the check to verify if the game was over prior was
 * 	not run.  The running of this function also added to the overall statement coverage for
 * 	the game.
 *
 * 	By looking at the coverage on the initial run of the random test there were many branches
 * 	with one direction heavily weighted.
 * 	fallthrough definition[1]:
 * 	"Translating conditional statements is interesting. In C, for example, when the
 * 	condition is true, you execute the body. This is the fall-through case. That is, you execute
 * 	the next statement. When the condition is false, you don't execute the body, you jump over it.
 * 	This is the jump case."
 *
 * 	Line 841: had a 50% jump rate and a 50% fallthrough rate.  (this was perfect)
 * 	Line 844: had an 85% jump rate and a 15% fallthrough rate
 * 	Line 845: had an 83% jump rate and a 17% fallthrough rate
 * 	Line 850: had a 99% jump rate and a 1% fallthrough rate.   (this was not well tested)
 * 	Line 857: had a 99% jump rate and a 1% fallthrough rate.   (this was not well tested)
 * 	Line 862: had a 97% fallthrough rate and only a 3% jump rate. (this was not well tested)
 * 	Line 865: had a 96% jump rate and a 4% fallthrough rate.  (this was not well tested)
 * 	Line 879: had a 97% fallthrough rate and only a 3% jump rate.  (this was not well tested)
 * 	Line 882: had a 97% jump rate and a 3% fallthrough rate. (this was not well tested)
 *
 * 	These results showed too many inputs in particular domains were being tested and not
 * 	enough of others.  Initially the random generator was written to have a large pool of
 * 	random numbers for the hand and estate piles.
 *
 * 	By reducing the pool of random numbers for the hand closer to the boundary of empty hand
 * 	all the branches prior to line 850 moved closer to 50%.  All branches between lines 850
 * 	and 856 moved considerably closer to 50% but the other lines remained the same.
 *
 * 	By reducing the pool of random numbers for quantity of estates in the supply closer to the
 * 	boundary of an empty estate pile Lines 857 to 882 all moved considerably closer to 50%
 * 	providing more even coverage for the function.
 *
 * 	The final result:
 * 	Line 841: had a 50% jump rate and a 50% fallthrough rate.  (this was perfect before)
 * 	Line 844: had an 79% jump rate and a 21% fallthrough rate
 * 	Line 845: had an 80% jump rate and a 20% fallthrough rate
 * 	Line 850: had a 67% jump rate and a 33% fallthrough rate.
 * 	Line 857: had a 92% jump rate and a 8% fallthrough rate.
 * 	Line 862: had a 83% fallthrough rate and a 17% jump rate.
 * 	Line 865: had a 80% jump rate and a 20% fallthrough rate.
 * 	Line 879: had a 83% fallthrough rate and a 17% jump rate.
 * 	Line 882: had a 80% jump rate and a 20% fallthrough rate.
 *
 *  It was observed that shrinking the pool of random numbers to between 0 and 3 for both the
 *  hand and estate supply produced the best coverage but as the function contained bugs a
 *  bug free function would react differently as the hand would normally have at least one card
 *  being the baron card during play.
 *
 *
 * Improvement in effort:
 * 	As baron was a card already tested prior creating the random testing was much
 * 	simpler.  A few refactoring improvements were also made to reduce redundant code not
 * 	refactored prior.  Getting full branch coverage only involved increasing the number of
 * 	tests as opposed to writing a new section of code to accommodate for a branch not taken.
 *
 * randomtestadventurer.c
 * Card:  Adventurer
 * Previously this card was tested under cardtest2.c
 *
 * Random inputs generated:
 * 	handCount: the handCount was generated randomly to test different hand sizes
 * 	hand: the hand was generated randomly to test different configurations of cards
 * 		in the hand.  Randomly choosing the cards also allowed for testing with different
 * 		numbers of estate cards in the hand.
 *
 * 	discardCount: the discardCount was generated randomly to test different discard
 * 		sizes.
 * 	discard: the discard pile was generated with random cards to test different
 * 		configurations of cards in the discard pile.
 *
 * 	deckCount: was generated randomly to test different deck sizes
 * 	deck: the deck pile was filled with randomly generated cards.
 *
 * 	The deckCount, handCount and discardCount were constrained so the sum was not
 * 	greater than MAX_DECK in this random test as well.  As we were testing the function of
 * 	the card not the external functions I felt overloading the probable number of cards
 * 	that could end up being discarded was not needed at this level. With that said, without
 * 	assertion statements and proper checks prior the function of this card, if given a
 * 	discard pile that was already at max capacity, would throw a SEGMENTATION FAULT
 * 	eventually.
 *
 * 	supplyCount[estate]: the estate supplyCount was randomly generated to test with
 * 		different levels estate cards available to draw from.
 *
 * 	supply of estates in the hand were calculated from the randomly generated cards in
 * 		the hand.
 *
 * Improvement in coverage:
 * 	Random testing did improve the branch coverage for this card.  It found boundary tests
 * 	that were not in the original test that triggered if the game was over or not.  The
 * 	running of the isGameOver function also improved overall branch coverage as new branches
 * 	were tested.
 *
 * 	Statement coverage was improved as the check to verify if the game was over prior was
 * 	not run.  The running of this function also added to the overall statement coverage for
 * 	the game.
 *
 * 	By looking at the coverage on the initial run of the random test there were many branches
 * 	with one direction heavily weighted.
 * 	Line 1248: had a 89% jump rate and a 11% fallthrough rate.
 * 	Line 1249: had a 97% jump rate and a 3% fallthrough rate
 * 	Line 1255: had an 81% fallthrough and 19% jump rate for copper,
 * 									a 96% fallthrough and 4% jump rate for silver
 * 									and a 96% jump rate for gold with a 4% fallthrough
 * 	Line 1269: had a 85% jump rate and a 15% fallthrough rate.
 *
 * 	Improving line 1248 proved difficult to adjust as the loop is always entered and run twice.
 * 	never checks if there are no cards.  By improving the chances that coins were found to even
 * 	out Line 1255 did improve the metric.
 * 	97% of the time there were coins in the deck and no shuffle was required.  By restricting
 * 	the number of cards in the deck chosen from this percentage was increased.  This increased
 * 	with the smaller the deckcount range.  Adding a bias of multiplying by a random number between
 * 	0 and 1 further increased this percentage.
 *
 * 	81% of the time the coin was a copper and only 19% of the time the coin was another treasure
 * 	Increasing the probability by using a subset deck with more instances of random silver and
 * 	gold to choose improved how even the branch coverage was on line 1255.
 *
 * 	With that said not all changes that even coverage make the test suite better.  During
 * 	experimentation to discover the true meaning of fall through both deck and discard piles
 * 	were set to 0 cards for all tests.  Test coverage in that state was considerably more even
 * 	on many of the branches but the even branch coverage came at the cost of removing some
 * 	valuable domain coverage.
 *
 * 	The final result:
 * 	Line 1248: had a 73% jump rate and a 27% fallthrough rate.
 * 	Line 1249: had an 88% jump rate and a 12% fallthrough rate
 * 	Line 1255: had a 50% fallthrough and 50% jump rate for copper,
 * 									a 72% fallthrough and 28% jump rate for silver
 * 									and a 75% jump rate for gold with a 25% fallthrough
 * 	Line 1269: had a 31% jump rate and a 69% fallthrough rate.
 *
 * Improvement in effort:
 * 	As adventurer was a card already tested prior creating the random testing was much
 * 	simpler.  A few refactoring improvements were also made to reduce redundant code not
 * 	refactored prior.  There was little improvement to the coverage that resulted from the
 * 	effort.
 *
 *
 * Overall:
 *  Initial Coverage prior to adding random testing:
 *  Lines executed:56.28% of 565
 *  Branches executed:65.47% of 417
 *  Taken at least once:57.79% of 417
 *  Calls executed:30.69% of 101
 *
 *  Coverage after random testing:
 *  Lines executed:58.05% of 565
 *  Branches executed:67.39% of 417
 *  Taken at least once:59.71% of 417
 *  Calls executed:32.67% of 101
 *
 *	By adding random testing overall coverage was increased by roughly 2% in all areas.
 *
 * 	Overall it is less intensive to tweak the inputs to gain even coverage with the random tester
 * 	than it is to write more tests to cover a missing domain.
 *
 *	[1] https://www.cs.umd.edu/class/sum2003/cmsc311/Notes/Mips/cond.html
 */
