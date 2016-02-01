#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// define level of FUZZ
//     where 0 = expected outputs only by inputChar(), reset only from inputString()
//           1 = expected outputs only by inputChar() and inputString() excluding \0
//           2 = expected outputs only by inputChar() and inputString() including \0 
//           3 = all ASCII keyboard chars by inputChar() and expected only by inputString() including \0 
//           4 = all ASCII keyboard chars by inputChar() and all a-z by inputString() excluding \0 
//           5 = all ASCII keyboard chars by inputChar() and all A-z by inputString() excluding \0 
//           6 = all ASCII keyboard chars by inputChar() and inputString() excluding \0 
#define FUZZ 6
#define TRACE 1  // trace where 0 = last state only, 1 = all traces
char s[] = "abcde";

char inputChar()
{
    // TODO: rewrite this function
    int i;

    if ( FUZZ < 3 ) {
        i = rand() % 9;
        switch ( i ) {
        case 0:
            return '[';
        case 1:
            return '(';
        case 2:
            return '{';
        case 3:
            return ' ';
        case 4:
            return 'a';
        case 5:
            return 'x';
        case 6:
            return '}';
        case 7:
            return ')';
        case 8:
            return ']';
        }
    } else if ( FUZZ < 7 ) {
        return ( rand() % (126 - 32 + 1 ) + 32); // 32 ASCII code for space, 126 ASCII code for ~
    } else {
        printf("error in inputChar - FUZZ too large\n");
        exit(1);
    }

}

char *inputString()
{
    // TODO: rewrite this function
    int i = 0;
    int j = 0;

    //char s[] = "abcde"; made global - here get - function returns address of local variable

    if ( FUZZ < 1 ) {
        return "reset\0";
    } else if ( FUZZ < 2 ) {
        while ( i < 5 ) {
            j = rand() % 4;
            switch ( j ) {
            case 0:
                s[i] = 'r';
                break;
            case 1:
                s[i] = 'e';
                break;
            case 2:
                s[i] = 's';
                break;
            case 3:
                s[i] = 't';
                break;
            }
            i++;
        }
    } else if ( FUZZ < 4 ) {
        while ( i < 5 ) {
            j = rand() % 5;
            switch ( j ) {
            case 0:
                s[i] = 'r';
                break;
            case 1:
                s[i] = 'e';
                break;
            case 2:
                s[i] = 's';
                break;
            case 3:
                s[i] = 't';
                break;
            case 4:
                s[i] = '\0';
                break;
            }
            i++;
        }
    } else if ( FUZZ < 5 ) {
        while ( i < 5 ) {
            s[i] = rand() % (122 - 97 + 1 ) + 97; // 97 ASCII code for a, 122 ASCII code for z
            i++;
        }
    } else if ( FUZZ < 6 ) {
        while ( i < 5 ) {
            s[i] = rand() % (122 - 65 + 1 ) + 65; // 65 ASCII code for A, 122 ASCII code for z
            i++;
        }
    } else if ( FUZZ < 7 ) {
        while ( i < 5 ) {
            s[i] = rand() % (126 - 32 + 1 ) + 32; // 32 ASCII code for space, 126 ASCII code for ~
            i++;
        }
    } else {
        printf("error in inputString - FUZZ too large\n");
        exit(1);
    }

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
        if ( TRACE > 0 ) {
            printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
        }

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
            if ( TRACE < 1 ) {
                printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
            }
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

