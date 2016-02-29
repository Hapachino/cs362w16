#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// Used to control which ASCII characters to search for, and how many
#define MIN 97
#define MAX 122
#define COUNT 5

char inputChar()
{
    // TODO: rewrite this function
    // Randomly generate a random int that includes all applicable characters
    int randInt = rand() % 128;
    randInt = randInt;
    
    // Avoids error with outputing to stdout, which didn't let me retrive error code (200)
    if (randInt == 5) {
        return ' ';
    }
    
    // Set the random int to a character and return
    char y = randInt;
    return y;
}

char *inputString()
{
    // TODO: rewrite this function
    // Create goal string, char array to hold string, and populate with closing character
    char goal[] = {'r','e','s','e','t','\0'};
    char target[COUNT + 1];
    target[COUNT + 1] = '\0';
    
    int i;
    for (i = 0; i < COUNT; i++) {
        
        /* There are ~11 million combinations if I don't check for the goal word, 
        so I added this while loop to ensure a solution is reached. 
        Otherwise, with a shorter string, you could comment out while loop 
        (leave inner items), and brute force your way to an answer. Feel free to try*/
        while (target[i] != goal[i]) {
            int y = rand() % (MAX + 1 - MIN);
            y = y + MIN;
            char temp = y;
            target[i] = temp;
        } 
        // Note, the while loop causes state 9 to not be printed, because always returns correct string 
    }
    return target;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
