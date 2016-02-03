#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//return a random printable character
char inputChar()
{
	char ascMax = 126;
	char ascMin = 32;
	//srand() is called in main, no need to seed here
	char randomC = rand() % (ascMax - ascMin + 1) + ascMin;
	return randomC;
}

//return a random length string consisting of random arrangement of characters found in testme
char *inputString()
{
	//generate random n for size of array 1 - 5 characters in length, with 1 space for \0
	int n = rand() % 5 + 1;
	//allocate memory for variable length string
	char *testString = malloc(n*sizeof(char));
	int i = 0;
	//range of possible letters from testme string
	char charPool[] = "rest";
	for (i;i<n;i++)
		testString[i] = charPool[rand() % 4];
	//last character in c character array/string is \0
	testString[n] = '\0';
    
	return testString;
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
