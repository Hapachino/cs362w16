#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<unistd.h>

/*
* References:
*   http://stackoverflow.com/questions/2509679/how-to-generate-a-random-number-from-within-a-range
*   http://stackoverflow.com/questions/14416759/return-char-string-from-a-function
*/

/* To run:
 * $ gcc -lm -o t testme.c
 * $ ./t
 */
#define MAX_CHARS 8
#define MAX_STRING 4
char inputChar()
{
    char options[] = "[({ ax})]";
    int r = (rand() % (MAX_CHARS+1-0));
    return options[ r ];
}

char *inputString()
{
    char options[] = "reset";
    char char0= options[ (rand() % (MAX_STRING+1)) ];
    char char1= options[ (rand() % (MAX_STRING+1)) ];
    char char2= options[ (rand() % (MAX_STRING+1)) ];
    char char3= options[ (rand() % (MAX_STRING+1)) ];
    char char4= options[ (rand() % (MAX_STRING+1)) ];
    char char5= options[ (rand() % (MAX_STRING+1)) ];

    char *str = (char *) malloc(sizeof(char) * 5);
    str[0] = char1;
    str[1] = char2;
    str[2] = char3;
    str[3] = char4;
    str[4] = char5;
    str[5] = '\0';

    return str;
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
