CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

################################################################################################
# For individual use
################################################################################################

randomtestcard1: randomtestcard1.c dominion.c rngs.c testFunctions.c
	gcc -o randomtestcard1 randomtestcard1.c dominion.c rngs.c testFunctions.c $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.c rngs.c testFunctions.c
	gcc -o randomtestcard2 randomtestcard2.c dominion.c rngs.c testFunctions.c $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.c rngs.c testFunctions.c
	gcc -o randomtestadventurer randomtestadventurer.c dominion.c rngs.c testFunctions.c $(CFLAGS)

randomtestsmithy: randomtestsmithy.c dominion.c rngs.c testFunctions.c
	gcc -o randomtestsmithy randomtestsmithy.c dominion.c rngs.c testFunctions.c $(CFLAGS)


################################################################################################

randomtestcard1.out: randomtestcard1
	echo "Result for running randomtestcard1 tests:" > randomtestcard1.out
	echo "" >> randomtestcard1.out
	./randomtestcard1 >> randomtestcard1.out
	echo "" >> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out

randomtestcard2.out: randomtestcard2
	echo "Result for running randomtestcard2 tests:" > randomtestcard2.out
	echo "" >> randomtestcard2.out
	./randomtestcard2 >> randomtestcard2.out
	echo "" >> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out

randomtestadventurer.out: randomtestadventurer
	echo "Result for running randomtestadventurer tests:" > randomtestadventurer.out
	echo "" >> randomtestadventurer.out
	./randomtestadventurer >> randomtestadventurer.out
	echo "" >> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out

################################################################################################

alltests:
	$(MAKE) randomtestcard1.out
	$(MAKE) randomtestcard2.out
	$(MAKE) randomtestadventurer.out

################################################################################################


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out
	rm -f testDrawCard testDrawCard.exe
	rm -f unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	rm -f randomtestcard1 randomtestcard2 randomtestadventurer randomtestsmithy
