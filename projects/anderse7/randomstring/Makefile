CFLAGS = -Wall -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

testme: testme.c
	gcc -o testme testme.c $(CFLAGS)

testme2: testme2.c rngs.o
	gcc -o testme2 testme2.c -g  rngs.o $(CFLAGS)

all: testme rngs.o testme2

clean:
	rm -f *.o testme2