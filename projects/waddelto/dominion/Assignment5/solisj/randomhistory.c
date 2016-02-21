/********************************************************************************************************************************************************
*** Filename: randomhistory.c
*** Author: Juan C. Solis
*** Class: CS362-400
*** Due date: 2/14/2015
*** Assignment 4
*** Description: Write up and check in the development of your random testers, including improvements in coverage and effort to check the correctness
***              of your specification, as randomhistory.c.
***
*******************************************************************************************************************************************************

======================
playAdventurer()
=======================

     Previous coverage of dominion.c code using assignment 3's cardtest2.c
          File 'dominion.c'
          Lines executed:18.37% of 577
          Branches executed:18.71% of 417
          Taken at least once:15.11% of 417
          Calls executed:8.42% of 95


     randomrandomtestadventurer.c
          File 'dominion.c'
          Lines executed:22.88% of 577
          Branches executed:20.14% of 417
          Taken at least once:18.71% of 417
          Calls executed:10.53% of 95


     Implications:
         The random tester for playAdventurer() has improved coverage over the fixed cardtest2.c from the last assignment. Last assignment, I neglected to test for cases where a shuffle of the discard pile into the deck was needed.
         However, in the new random tester, there can now be random cases where the deck pile is empty causing a function call to shuffle(). 

     Development:
          After developing the random tester for playAdventurer(), I found that because of the intentional bug added in a previous assignment, all of the tests were failing. While this was excellent due to finding the bug, I had to fix the intentional bug
          to be able to further analyze my random tester. 

          I modified the cardtest2.c, which was more of a fixed case card test for playAdventurer(), to randomly generate various test cases. For example, the amount of cards in the deck, hand, and  discard piles was randomized and filled with
          random cards. This created cases where even though the player's deck and discard pile were not empty, they might have less than 2 treasure cards. Another situation could be that the deck and discard piles are indeed empty. 
          It was due to situations like these, that I added a print statement for any failed tests to display the card count for deck, hand, and discard piles. I also would print how many treasure cards were in each if any. This allowed me to discover that 
          the failed tests were due to the previously mentioned situations. 

          Please note: I have re-applied the intended bug, which will cause all tests to fail. 



===================================
Case great_hall from cardEffect()
===================================
     Coverage:
          Due to not having previously tested the great_hall card function, I was unable to compare coverage results specific to the great_hall function.
          After reviewing the coverage results, the random tester achieved 100% coverage for the great_hall case in cardEffect(). This means that the random tester was able to generate various test cases needed to achieve the 100% coverage.


     Development:
          I used the same initial setup from randomrandomtestadventurer.c to be able to generate various random game test cases. The great_hall card is pretty straightforward in that it increase the number of actions by 1 and adds a card to the player’s hand.
          Similarly to the playAdventurer() test, if there are cases where the deck and discard pile are empty , the test will fail. This is due to the great_hall card being discarded while no other card has been added as intended.  The random tester did not 
          find any bugs. However, this could possibly mean that if there are bugs, I did not test for them. One test case that I did not think of before would be to check that the great hall card was also added to the playedCards pile.  

*/