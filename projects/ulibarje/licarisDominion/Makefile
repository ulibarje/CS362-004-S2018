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

cardtest1: cardtest1.c dominion.c rngs.c testFunctions.c
	gcc -o cardtest1 cardtest1.c dominion.c rngs.c $(CFLAGS)

cardtest2: cardtest2.c dominion.c rngs.c testFunctions.c
	gcc -o cardtest2 cardtest2.c dominion.c rngs.c $(CFLAGS)

cardtest3: cardtest3.c dominion.c rngs.c testFunctions.c
	gcc -o cardtest3 cardtest3.c dominion.c rngs.c $(CFLAGS)

cardtest4: cardtest4.c dominion.c rngs.c testFunctions.c
	gcc -o cardtest4 cardtest4.c dominion.c rngs.c $(CFLAGS)


################################################################################################

randomtestcard1.out: randomtestcard1
	echo "Result for running randomtestcard1 tests:" > testSuiteResults.out
	echo "" >> testSuiteResults.out
	./randomtestcard1 >> testSuiteResults.out
	echo "" >> testSuiteResults.out
	gcov dominion.gdca >> testSuiteResults.out
	echo -e '\n' >> testSuiteResults.out

randomtestcard2.out: randomtestcard2
	echo "Result for running randomtestcard2 tests:" >> testSuiteResults.out
	echo "" >> testSuiteResults.out
	./randomtestcard2 >> testSuiteResults.out
	echo "" >> testSuiteResults.out
	gcov dominion.gdca >> testSuiteResults.out
	echo -e '\n' >> testSuiteResults.out

randomtestadventurer.out: randomtestadventurer
	echo "Result for running randomtestadventurer tests:" >> testSuiteResults.out
	echo "" >> testSuiteResults.out
	./randomtestadventurer >> testSuiteResults.out
	echo "" >> testSuiteResults.out
	gcov dominion.gdca >> testSuiteResults.out
	echo -e '\n' >> testSuiteResults.out

cardtest1.out: cardtest1
	echo "Result for running cardtest1 tests:" >> testSuiteResults.out
	echo "" >> testSuiteResults.out
	./cardtest1 >> testSuiteResults.out
	echo "" >> testSuiteResults.out
	gcov dominion.gdca >> testSuiteResults.out
	echo -e '\n' >> testSuiteResults.out

cardtest2.out: cardtest2
	echo "Result for running cardtest2 tests:" >> testSuiteResults.out
	echo "" >> testSuiteResults.out
	./cardtest2 >> testSuiteResults.out
	echo "" >> testSuiteResults.out
	gcov dominion.gdca >> testSuiteResults.out
	echo -e '\n' >> testSuiteResults.out

cardtest3.out: cardtest3
	echo "Result for running cardtest3 tests:" >> testSuiteResults.out
	echo "" >> testSuiteResults.out
	./cardtest3 >> testSuiteResults.out
	echo "" >> testSuiteResults.out
	gcov dominion.gdca >> testSuiteResults.out
	echo -e '\n' >> testSuiteResults.out

cardtest4.out: cardtest4
	echo "Result for running cardtest4 tests:" >> testSuiteResults.out
	echo "" >> testSuiteResults.out
	./cardtest4 >> testSuiteResults.out
	echo "" >> testSuiteResults.out
	gcov dominion.gdca >> testSuiteResults.out
	echo -e '\n' >> testSuiteResults.out

################################################################################################

alltests:
	$(MAKE) randomtestcard1.out
	$(MAKE) randomtestcard2.out
	$(MAKE) randomtestadventurer.out
	$(MAKE) cardtest1.out
	$(MAKE) cardtest2.out
	$(MAKE) cardtest3.out
	$(MAKE) cardtest4.out
	$(MAKE) clean

################################################################################################


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so
	rm -f testDrawCard testDrawCard.exe
	rm -f unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	rm -f randomtestcard1 randomtestcard2 randomtestadventurer randomtestsmithy
