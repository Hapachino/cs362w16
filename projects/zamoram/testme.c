#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    char c;
	//list of possible chars
	//char chars[9] = "[({ ax})]";
	
	//random number in random range = random * (Max - Min + 1) + min
	//char in ascii range
	int max = 126;
	int min = 32;
	c = (rand() * (max -min + 1)) + min;
	
    //return chars[c];
	return c;
}

char *inputString()
{
    char *s = malloc(5);
	//list of possible chars
	char chars[5] = "rset";
	int i;
	char c;
	
	for(i = 0; i< 5; i++)
	{
		c = rand() % 5;
		s[i] = chars[c];
	}
	
	s[5] = '\0';
	
    return s;
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
