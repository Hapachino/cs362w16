//
// Created by Robert on 1/26/2016.
// the Smithy Test

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"
#include "interface.h"
#include <time.h>

//http://stackoverflow.com/questions/3437404/min-and-max-in-c
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MAX_D 500;
float genPro(){

    int prob;
    float ran;
    int i;
    double test = RAND_MAX;

    srand(time(NULL)+i);
    prob = rand();
    ran = prob/test;

    return prob;
};


int main(int argc, char** argv) {
    int i, maxDeck, maxDisc;
    for (i = 0; i < 1000; i++){
    int n= Random() ;
    double m = Random();
float l = (Random() * 3) + 4;
//printf("flt: %f \n",l );
//    printf(" dbl: %d \n",l );
//    printf("int: %i \n\n",l );
//
//    printf("flt: %f \n",m );
//    printf(" dbl: %d \n",m );
//    printf("int: %i \n\n",m );
//
//    printf("flt: %f \n",n );
//    printf(" dbl: %d \n",n );
//    printf("int: %i \n",n );

        maxDeck = MAX_D;
        maxDisc = MAX_D;
        //20% of the time the deck or discard or Hand is 0
       /* if(l < 0.2){
            maxDeck = 0;
            printf("  set maxDeck  ");
        }

        //can't both be 0
        if((l < 0.4) && (maxDeck !=0 )){
            maxDisc = 0;
            printf("  set maxDisc  ");
        }

        printf("maxDisc %i , maxDeck %i \n", maxDisc, maxDeck);*/

        printf("%i \n", (int)floor(l) );

        if ((int)floor(l) < 5){
            printf("bullshit \n");
        }
}
return 0;
}