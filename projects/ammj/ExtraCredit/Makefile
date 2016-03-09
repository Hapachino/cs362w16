CFLAGS = -Wall -fpic -coverage -lm
	
rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
	
interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

unittest.o: unittest.h unittest.c
	gcc -c unittest.c -g  $(CFLAGS)
	
player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

tarantula.o: tarantula.h tarantula.c
	gcc -c tarantula.c -g $(CFLAGS)
	
cleanTest:
	rm -f playdom player dominion.o testgetwinners testGetWinnersOnly dominion*.g* tarant*.out.txt tarant*.html
	
testgetwinners: cleanTest dominion.o testgetwinners.c unittest.o rngs.o
	gcc -o testgetwinners testgetwinners.c -g dominion.o rngs.o unittest.o $(CFLAGS)
	
testGetWinnersOnly: cleanTest dominion.o testGetWinnersOnly.c unittest.o rngs.o
	gcc -o testGetWinnersOnly testGetWinnersOnly.c -g dominion.o rngs.o unittest.o $(CFLAGS)
	
tarantulaMain: tarantulaMain.c tarantula.h tarantula.c
	gcc -o tarantulaMain -g tarantulaMain.c tarantula.h tarantula.c -g $(CFLAGS)
	
all: playdom player tarantulaMain

clean: 
	rm -f *.o *.out *.g* dominion player playdom tarantulaMain testgetwinners testGetWinnersOnly *.tarantula.txt *.tarantula.html