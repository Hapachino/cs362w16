CFLAGS = -Wall -fpic -coverage -lm

testme: testme.o testme.c
	gcc -o testme testme.c  $(CFLAGS)

#runtests: testme
#    ./testme &> testmeresult.out
#	./cardtest1 &> unittestresult.out
#	./cardtest2 &> unittestresult.out
#	./cardtest3 &> unittestresult.out
#    gcov testme.c >> testmeresult.out
#    cat testme.c.gcov >> testmeresult.out


clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so
