CFLAGS = -Wall -fpic -coverage -lm -std=c99

default: testme;

testme: testme.o
	gcc -o testme -g  testme.c $(CFLAGS)
	./testme 
	echo ""
	gcov -b testme.c 
	

clean:
	rm -f *.o *.gcov *.gcda *.gcno


