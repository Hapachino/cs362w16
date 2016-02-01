#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    //Returns an ASCII value between 32 - 125 (' ' through '}').
    return ((rand() % 94) + 32);
}

void inputString(char *s)
{
    int x, size, fate = rand() % 100;
    
    //Produce size between 0 - 10, favoring size 5.
    if (fate < 25) { size = 5; }
    else { size = fate % 11; }

    //In 1/7 cases of size 5 string, letters only chosen from r, e, s, t & 4 addtl random letters.
    if (size == 5 && (rand() % 7 == 0)) {
	char set[8] = {'r', 'e', 's', 't', 
	               ((rand() % 94) + 32), ((rand() % 94) + 32), ((rand() % 94) + 32), ((rand() % 94) + 32)};
        for (x = 0; x < 5; x++) { s[x] = set[rand() % 8]; }
	s[5] = '\0';  //Ensure string is null terminated
    }
    else { //In rest of cases build a string of length 'size' with full range of possible characters.
        for (x = 0; x < size; x++) { s[x] = ((rand() % 94) + 32); }
        s[size] = '\0';  //Ensure string is null terminated
    }
}

void testme()
{
  int tcCount = 0;
  char *s = malloc(11 * sizeof(char)); //Added memory allocation.
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    inputString(s);  //Changed to void function, and passed pointer to string for update.
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
      printf("error\n\n");  //Added newlines to cleanup final prompt.
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
