#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
    //We don't want to itterate through every char, so we only use the options within our parameters.
    char array[9] = {'[', '(', '{', ' ', 'a', 'x', '}', ')', ']'};
    int pos;

    //give the random position of one of the chars in array
    pos = rand() % 9;

    //returns the char at random pos in array
    return array[pos];

}

char *inputString()
{
    // TODO: rewrite this function
    char letters[4] = {'r', 'e', 's', 't'};
    //mallocing for the array to be returned
    char *array = malloc(6 * sizeof(char));
    //vars used for positions
    int i;
    int pos;

    //populates the array to be returned
    for (i = 0; i < 5; i++){
        //chooses a random pos from the letters array
        pos = rand() % 4;
        //adds a random letter to the array to be returned
        array[i] = letters[pos];
    }

    return array;
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
        if (c == ' ' && state == 3) state = 4;
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
        //we don't want a major memory leak from mallocing so many times.
        free(s);
    }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}