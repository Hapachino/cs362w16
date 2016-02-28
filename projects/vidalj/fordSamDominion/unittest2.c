/* Test the kingdomCards() function
   NOTE: kingdomCards() takes ten integers (cards), allocates an array of
   length 10, assigns each of the integer arguments as array members, and
   returns a pointer to the dynamically allocated array.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dominion.h"
#include "fordsamTest.h"

#define KINGDOM_ARRAY_LENGTH 10

void testKingdomCards() {
  int passCount = 0;
  int testCount = 0;
  int* resultArray = NULL;
  int k[KINGDOM_ARRAY_LENGTH] = {
    council_room,
    gardens,
    village,
    remodel,
    embargo,
    minion,
    cutpurse,
    feast,
    smithy,
    adventurer
  };

  printf("----- Testing kingdomCards() -----\n");

  printf("----- Test: Provide only non-cards (-1) as arguments\n");
  resultArray = kingdomCards(-1, -1, -1, -1, -1, -1, -1, -1, -1, -1);

  /* Should not return a null pointer */
  testCount += 1;
  passCount += fakeAssert(
    "Should ensure provided cards are valid before assigning to output array",
    (resultArray != NULL && resultArray[0] != -1)
  );

  /* Free and reset the resultArray before proceeding, if necessary */
  if (resultArray != NULL) {
    free(resultArray);
    resultArray = NULL;
  }

  /* Pass the values from the established array of kingdom cards, k, into the
     kingdomCards() function */
  printf("\n----- Test: Ten valid cards are passed as arguments\n");
  resultArray = kingdomCards(
    k[0], k[1], k[2], k[3], k[4], k[5], k[6], k[7], k[8], k[9]
  );

  /* Should not return a null pointer */
  testCount += 1;
  passCount += fakeAssert(
    "Should not return a null pointer",
    (resultArray != NULL)
  );

  /* Output array cards should match the cards given as arguments
     NOTE: It's unclear at this point whether there's any intention to the
       order of the kingdom cards array. If the cards don't need to maintain
       their order then we can simply test for the presence of the argument
       cards in the output array (not a direct match between the source array
       and output array). */
  testCount += 1;
  passCount += fakeAssert(
    "Output array cards should match the cards given as arguments",
    (memcmp(resultArray, k, KINGDOM_ARRAY_LENGTH * sizeof(int)) == 0)
  );

  /* Free and reset the resultArray before proceeding, if necessary */
  if (resultArray != NULL) {
    free(resultArray);
    resultArray = NULL;
  }

  /* Print the final number of passing tests and the total number of tests */
  printTestResults(passCount, testCount);
}

int main() {
  testKingdomCards();
  return 0;
}
