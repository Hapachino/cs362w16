/* Author:      Ian Bender
 * Course:      CS362
 * Due Date:    2/3/2016
 * Description: Assignment 3 bug report.
 */

Bugs found:
cardtest1.c - Smithy card
- Player did not gain 3 cards as expected.
- Known bug caused by faults created in assignment 2.
- < in for loop replaced with > so loop is never entered

cardtest2.c - Adventurer card
- Additional cards were not added to player hand.
- Known bug caused by faults created in assignment 2.
- Closing } in wrong position, causing drawCard function to be called only if
    the deck is empty

My other unit and card tests did not come back with obvious errors. Admittedly,
the testing does not go as in-depth as it could and there are certainly bugs
elsewhere that could be caught with deeper testing.

Intentions for further testing:
- Verify cards drawn are coming from correct players' hands and discard/trash
    piles are updated appropriately.
