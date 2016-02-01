#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
	int n = rand() % (126 - 32 + 1);
	n += 32;
	return n;
}

char *inputString(char *str) 
{
	int i = 0;
	for (; i<5; ++i)
		str[i] = (rand() % ('z' - 'a' + 1)) + 'a'; // contains only alphabet letters in lower case

	if (!str[i]) str[i] = 0;

	return str;
}


/*
char *inputString()
{
    // TODO: rewrite this function
    return "";
}
*/


void testme()
{
  char *str = (char*)malloc(6); // allocate memory to store a string of 5 characters
  
  // write random strings to a file, "randomstring.c"
  FILE *fp;
  fp = fopen("randomstring.c", "w");
  
  
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    //s = inputString();
	s = inputString(str);
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
	fprintf(fp, "Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

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
      printf("error:\n");
      free(str); // free memory
	  fclose(fp);
      exit(200);
    }
  }
  free(str); // free memory
  fclose(fp);
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
