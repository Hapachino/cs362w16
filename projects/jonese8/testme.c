#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
   		//Select random ASCII character
		int i = rand() % 128;
        return (char)i;
    return (char)i;
}

char *inputString()
{
        char *createString = (char *)malloc(6);
        //Select random 26 numbers and add 97 to get ASCII 
        createString[0] = (char)(rand() % 26 + 97);
        createString[1] = (char)(rand() % 26 + 97);
        createString[2] = (char)(rand() % 26 + 97);
        createString[3] = (char)(rand() % 26 + 97);
        createString[4] = (char)(rand() % 26 + 97);
        //End of String
		createString[5] = 0;

    return createString;
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
