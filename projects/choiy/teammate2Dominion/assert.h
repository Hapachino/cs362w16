#include <stdio.h>
#include <stdlib.h>

void assert(int TorF) {

   if (TorF) {
      printf("\tPASS\n");
      //return "\tPASS\n";
   }
      
   else {
      printf("\tFAIL\n");
      //return "\tFAIL\n";
   }
}

char *assert2(int TorF) {

   if (TorF) {
      //printf("\tPASS\n");
      return "PASS";
   }
      
   else {
      //printf("\tFAIL\n");
      return "FAIL";
   }
}
