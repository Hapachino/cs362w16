#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{

    return rand() % (126 -  32) + 32; //return 1 character used on a keyboard

    //faster implementation
    /*const char* letters = "[({ ax})]"; //characters that set the state
    int index = rand() % 9;
    return letters[index];*/
}

char *inputString()
{
    const char *letters = "rest"; //possible letters to choose from
    static char str[] = "reset"; //storage for the returned string
    int i, index; //index values

    for(i = 0; i < 5; i++){
        index = rand() % 4;
        str[i] = letters[index];
    }

    /*about 1 in 12 million (1/(26^5)) chance of getting reset
    for(i = 0; i < 5; i++){
        str[i] = rand() % (123 -  97) + 97; //selects a random lowercase letter
    }*/

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
