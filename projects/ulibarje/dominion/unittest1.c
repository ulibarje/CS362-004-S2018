/* Name: unittest1
 * Author: Jesse Ulibarri
 * CS362 - Assignment 3
 * Test For: "updateCoins"
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

#define PRINT 0

#define TESTFUNC "updateCoins"


/*************************************************************************
* Name: assertTrue
*
* Description: 
*
*************************************************************************/
int assertTrue(int test, int expect) {
	if(test == expect) {
		if(PRINT ){
			printf("TEST PASSED ");
			printf("Test: %d, Expected: %d\n", test, expect);
		}
		return 0;
	}
	else {
		if(PRINT){
			printf("TEST FAILED ");
			printf("Test: %d, Expected: %d\n", test, expect);
		}
		return 1;
	}
}

/*************************************************************************
* Name: compareGameStates
*
* Description: This function compares the test game state object with 
*	a reference game state object. This function only tests the
*	parameters that are not explicitly tested in the test case. This
*	function serves as a check for the parameters that shouldn't have
*	changed after running the "function-under-test", but this check makes
*	sure of that. The commented out regions are those that are explicitly
*	checked in the test case, and thus, do not need to be tested again.
*
*************************************************************************/
int compareGameStates(struct gameState* testG, struct gameState* refG) {

	int i, j;
	int stateSuccess = 0;

	// Tier 1
	if(!(testG->numPlayers == refG->numPlayers)) {
		stateSuccess = 1;
		printf("FAILED: testG->numPlayers: %d, refG->numPlayers: %d\n", testG->numPlayers, refG->numPlayers);
		
	}

	for(i = 2; i < treasure_map + 1; i++) {
		if(!(testG->supplyCount[i] == refG->supplyCount[i])) {
		stateSuccess = 1;
			printf("FAILED: testG->supplyCount[%d]: %d, refG->supplyCount[%d]: %d\n", i, testG->supplyCount[i], i, refG->supplyCount[i]);
		}
	}

	for(i = 0; i < treasure_map + 1; i++) {
		if(!(testG->embargoTokens[i] == refG->embargoTokens[i])) {
		stateSuccess = 1;
			printf("FAILED: testG->embargoTokens[%d]: %d, refG->embargoTokens[%d]: %d\n", i, testG->embargoTokens[i], i, refG->embargoTokens[i]);
		}
	}

	if(!(testG->outpostPlayed == refG->outpostPlayed)) {
		stateSuccess = 1;
		printf("FAILED: testG->outpostPlayed: %d, refG->outpostPlayed: %d\n", testG->outpostPlayed, refG->outpostPlayed);
	}

	if(!(testG->whoseTurn == refG->whoseTurn)) {
		stateSuccess = 1;
		printf("FAILED: testG->whoseTurn: %d, refG->whoseTurn: %d\n", testG->whoseTurn, refG->whoseTurn);
	}

	if(!(testG->phase == refG->phase)) {
		stateSuccess = 1;
		printf("FAILED: testG->phase: %d, refG->phase: %d\n", testG->phase, refG->phase);
	}

	if(!(testG->numActions == refG->numActions)) {
		stateSuccess = 1;
		printf("FAILED: testG->numActions: %d, refG->numActions: %d\n", testG->numActions, refG->numActions);
	}

	// if(!(testG->coins == refG->coins)) {
	// 	stateSuccess = 1;
	// 	printf("FAILED: testG->coins: %d, refG->coins: %d\n", testG->coins, refG->coins);
	// }

	if(!(testG->numBuys == refG->numBuys)) {
		stateSuccess = 1;
		printf("FAILED: testG->numBuys: %d, refG->numBuys: %d\n", testG->numBuys, refG->numBuys);
	}

	if(!(testG->playedCardCount == refG->playedCardCount)) {
		stateSuccess = 1;
		printf("FAILED: testG->playedCardCount: %d, refG->playedCardCount: %d\n", testG->playedCardCount, refG->playedCardCount);
	}

	// Tier 2
	if(stateSuccess == 0) {
		for(i = 0; i < testG->numPlayers; i++) {
			if(!(testG->handCount[i] == refG->handCount[i])) {
				stateSuccess = 1;
				printf("FAILED: testG->handCount[player = %d]: %d, refG->handCount[player = %d]: %d\n", i, testG->handCount[i], i, refG->handCount[i]);
			}
		}

		for(i = 0; i < testG->numPlayers; i++) {
			if(!(testG->deckCount[i] == refG->deckCount[i])) {
				stateSuccess = 1;
				printf("FAILED: testG->deckCount[player = %d]: %d, refG->deckCount[player = %d]: %d\n", i, testG->deckCount[i], i, refG->deckCount[i]);
			}
		}

		for(i = 0; i < testG->playedCardCount; i++) {
			if(!(testG->playedCards[i] == refG->playedCards[i])) {
				stateSuccess = 1;
				printf("FAILED: testG->playedCards[%d]: %d, refG->playedCards[%d]: %d\n", i, testG->playedCards[i], i, refG->playedCards[i]);
			}
		}

		for(i = 0; i < testG->numPlayers; i++) {
			if(!(testG->discardCount[i] == refG->discardCount[i])) {
				stateSuccess = 1;
				printf("FAILED: testG->discardCount[player = %d]: %d, refG->discardCount[player = %d]: %d\n", i, testG->discardCount[i], i, refG->discardCount[i]);
			}
		}

		// Tier 3
		if(stateSuccess == 0) {
			for(i = 0; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->handCount[i]; j++) {
					if(!(testG->hand[i][j] == refG->hand[i][j])) {
						stateSuccess = 1;
						printf("FAILED: testG->hand[player = %d][%d]: %d, refG->hand[player = %d][%d]: %d\n", i, j, testG->hand[i][j], i, j, refG->hand[i][j]);
					}
				}
			}

			for(i = 0; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->deckCount[i]; j++) {
					if(!(testG->deck[i][j] == refG->deck[i][j])) {
						stateSuccess = 1;
						printf("FAILED: testG->deck[player = %d][%d]: %d, refG->deck[player = %d][%d]: %d\n", i, j, testG->deck[i][j], i, j, refG->deck[i][j]);
					}
				}
			}

			for(i = 0; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->discardCount[i]; j++) {
					if(!(testG->discard[i][j] == refG->discard[i][j])) {
						stateSuccess = 1;
						printf("FAILED: testG->discard[player = %d][%d]: %d, refG->discard[player = %d][%d]: %d\n", i, j, testG->discard[i][j], i, j, refG->discard[i][j]);
					}
				}
			}
		}
		else {
			return stateSuccess;
		}
	}
	else {
		return stateSuccess;
	}

	return stateSuccess;
}


/****************************************************************************************/
/************************************* MAIN *********************************************/
/****************************************************************************************/

int main() {

	int bonusCoins, i;

	int allSuccess = 0, testSuccess = 0;
	int seed = 123;
	int numPlayers = 2;
	int maxBonus = 5;
	int currentPlayer = 0;
	struct gameState regGame, testGame;
	int useCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	initializeGame(numPlayers, useCards, seed, &testGame);
	memcpy(&regGame, &testGame, sizeof(struct gameState));

	printf("***************************************************************************\n");
	printf("********************** BEGINNING \"%s\" TEST ***********************\n", TESTFUNC);
	printf("***************************************************************************\n\n");

	/****************************************************************************************/
	/****************************************************************************************/
	printf("Testing with set hand and iterating through bonus from 0 to 10...\n\n");
	// Set the hand ---> All copper
	testGame.hand[currentPlayer][0] = copper;
	testGame.hand[currentPlayer][1] = copper;
	testGame.hand[currentPlayer][2] = copper;
	testGame.hand[currentPlayer][3] = copper;
	testGame.hand[currentPlayer][4] = copper;

	regGame.hand[currentPlayer][0] = copper;
	regGame.hand[currentPlayer][1] = copper;
	regGame.hand[currentPlayer][2] = copper;
	regGame.hand[currentPlayer][3] = copper;
	regGame.hand[currentPlayer][4] = copper;


	for(i = 0; i < maxBonus; i++) {
		bonusCoins = i;
		updateCoins(currentPlayer, &testGame, bonusCoins);

		if(PRINT)
			printf("Hand: C C C C C + bonus of %d ---> 			", bonusCoins);
		if(assertTrue(testGame.coins, 5 + bonusCoins) && allSuccess == 0) {
			allSuccess = 1;
			testSuccess = 1;
		}

		// Make sure that the rest of the gamestate has not changed
		if(compareGameStates(&testGame, &regGame)) {
    		allSuccess = 1;
    		testSuccess = 1;
		}

	}//for


    if(testSuccess == 0) { 
    	printf("All copper in hand			--->	PASSED\n");
    }
    else {
    	printf("All copper in hand			--->	FAILED\n");
    }


	/****************************************************************************************/
	/****************************************************************************************/
	// Set the hand ---> All silver
	testGame.hand[currentPlayer][0] = silver;
	testGame.hand[currentPlayer][1] = silver;
	testGame.hand[currentPlayer][2] = silver;
	testGame.hand[currentPlayer][3] = silver;
	testGame.hand[currentPlayer][4] = silver;

	regGame.hand[currentPlayer][0] = silver;
	regGame.hand[currentPlayer][1] = silver;
	regGame.hand[currentPlayer][2] = silver;
	regGame.hand[currentPlayer][3] = silver;
	regGame.hand[currentPlayer][4] = silver;

	testSuccess = 0;

	for(i = 0; i < maxBonus; i++) {
		bonusCoins = i;
		updateCoins(currentPlayer, &testGame, bonusCoins);

		if(PRINT)
			printf("Hand: S S S S S + bonus of %d ---> ", bonusCoins);
		if(assertTrue(testGame.coins, 10 + bonusCoins) && allSuccess == 0) {
			allSuccess = 1;
			testSuccess = 1;
		}

		// Make sure that the rest of the gamestate has not changed
		if(compareGameStates(&testGame, &regGame)) {
    		allSuccess = 1;
    		testSuccess = 1;
		}

	}//for


    if(testSuccess == 0) { 
    	printf("All silver in hand			--->	PASSED\n");
    }
    else {
    	printf("All silver in hand			--->	FAILED\n");
    }


	/****************************************************************************************/
	/****************************************************************************************/
	// Set the hand ---> All gold
	testGame.hand[currentPlayer][0] = gold;
	testGame.hand[currentPlayer][1] = gold;
	testGame.hand[currentPlayer][2] = gold;
	testGame.hand[currentPlayer][3] = gold;
	testGame.hand[currentPlayer][4] = gold;

	regGame.hand[currentPlayer][0] = gold;
	regGame.hand[currentPlayer][1] = gold;
	regGame.hand[currentPlayer][2] = gold;
	regGame.hand[currentPlayer][3] = gold;
	regGame.hand[currentPlayer][4] = gold;

	testSuccess = 0;

	for(i = 0; i < maxBonus; i++) {
		bonusCoins = i;
		updateCoins(currentPlayer, &testGame, bonusCoins);

		if(PRINT)
			printf("Hand: G G G G G + bonus of %d ---> ", bonusCoins);
		if(assertTrue(testGame.coins, 15 + bonusCoins) && allSuccess == 0) {
			allSuccess = 1;
			testSuccess = 1;
		}

		// Make sure that the rest of the gamestate has not changed
		if(compareGameStates(&testGame, &regGame)) {
    		allSuccess = 1;
    		testSuccess = 1;
		}

	}//for


    if(testSuccess == 0) { 
    	printf("All gold in hand			--->	PASSED\n");
    }
    else {
    	printf("All gold in hand			--->	FAILED\n");
    }


	/****************************************************************************************/
	/****************************************************************************************/
	// Set the hand ---> One of each
	testGame.hand[currentPlayer][0] = copper;
	testGame.hand[currentPlayer][1] = silver;
	testGame.hand[currentPlayer][2] = gold;
	testGame.hand[currentPlayer][3] = estate;
	testGame.hand[currentPlayer][4] = estate;

	regGame.hand[currentPlayer][0] = copper;
	regGame.hand[currentPlayer][1] = silver;
	regGame.hand[currentPlayer][2] = gold;
	regGame.hand[currentPlayer][3] = estate;
	regGame.hand[currentPlayer][4] = estate;

	testSuccess = 0;

	for(i = 0; i < maxBonus; i++) {
		bonusCoins = i;
		updateCoins(currentPlayer, &testGame, bonusCoins);

		if(PRINT)
			printf("Hand: C S G E E + bonus of %d ---> ", bonusCoins);
		if(assertTrue(testGame.coins, 6 + bonusCoins) && allSuccess == 0) {
			allSuccess = 1;
			testSuccess = 1;
		}

		// Make sure that the rest of the gamestate has not changed
		if(compareGameStates(&testGame, &regGame)) {
    		allSuccess = 1;
    		testSuccess = 1;
		}

	}//for


    if(testSuccess == 0) { 
    	printf("One of each coin in hand 	--->	PASSED\n");
    }
    else {
    	printf("One of each coin in hand	--->	FAILED\n");
    }


	/****************************************************************************************/
	/****************************************************************************************/
	// Set the hand ---> No coins
	testGame.hand[currentPlayer][0] = curse;
	testGame.hand[currentPlayer][1] = duchy;
	testGame.hand[currentPlayer][2] = province;
	testGame.hand[currentPlayer][3] = estate;
	testGame.hand[currentPlayer][4] = minion;

	regGame.hand[currentPlayer][0] = curse;
	regGame.hand[currentPlayer][1] = duchy;
	regGame.hand[currentPlayer][2] = province;
	regGame.hand[currentPlayer][3] = estate;
	regGame.hand[currentPlayer][4] = minion;

	testSuccess = 0;

	for(i = 0; i < maxBonus; i++) {
		bonusCoins = i;
		updateCoins(currentPlayer, &testGame, bonusCoins);

		if(PRINT)
			printf("Hand: Cur D P E K + bonus of %d ---> ", bonusCoins);
		if(assertTrue(testGame.coins, 0 + bonusCoins) && allSuccess == 0) {
			allSuccess = 1;
			testSuccess = 1;
		}

		// Make sure that the rest of the gamestate has not changed
		if(compareGameStates(&testGame, &regGame)) {
    		allSuccess = 1;
    		testSuccess = 1;
		}

	}//for


    if(testSuccess == 0) { 
    	printf("No coins in hand			--->	PASSED\n");
    }
    else {
    	printf("No coins in hand			--->	FAILED\n");
    }

    printf("\n");

	printf("**************************************************\n");
	// All tests have completed, print out if all were successful, or if there was any failures.
	if(allSuccess == 0)
		printf("\"%s\" unit test		---> 	PASSED\n", TESTFUNC);
	else
		printf("\"%s\" unit test		---> 	FAILED\n", TESTFUNC);
	printf("**************************************************\n");
	printf("\n");

	return 0;
}