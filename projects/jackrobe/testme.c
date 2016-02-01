#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

char inputChar()
{

    // generate a random number
    int k = rand()%50000; // for the low probability
    int b = rand()%9;  // for the character array

    //1 in 50k chance it sends the level 9 condition
    if( k == 42){
        return  ']';
    }

    char c[8] = {'[','(','{',' ','a', 'x','}',')'};

    return c[b];


}

char *inputString()
{
    int i;
    int p, z;
    p = rand()%2;
    z = rand()%11; // allow strings up to 10 characters long
    char set[5] = {'r','e','s','e','t'} ;
    char *randomString = malloc(sizeof(char) * 5);

    //50% chance that we generate from a limited data set
    if(p == 1){

        for(i=0; i < z; i++){
            int j = rand()%z;
            randomString[i] = set[j];
        }
        return randomString;
    }

    //make a bunch of x letter words from all ascii values
    for(i=0; i < z; i++) {

        int k = rand()%96 +32; // set of possible ascii values
        randomString[i] = (char)k;
    }
    return randomString;
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
        if (s[0] == 'r'
            && s[1] == 'e'
            && s[2] == 's'
            && s[3] == 'e'
            && s[4] == 't'
            && s[5] == '\0'
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
