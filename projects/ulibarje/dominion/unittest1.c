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

#define TESTFUNC "updateCoins"

int assertTrue(int test, int expect) {
	if(test == expect) {
		printf(GRN "TEST PASSED " RESET);
		printf("Test: %d, Expected: %d\n", test, expect);
		return 0;
	}
	else {
		printf(RED "TEST FAILED " RESET);
		printf("Test: %d, Expected: %d\n", test, expect);
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
int compareGameStates(struct gameState* testG, struct gameState* origG) {

	int i, j;
	int stateSuccess = 0;

	if(!(testG->numPlayers == origG->numPlayers)) {
		stateSuccess = 1;
		printf("testG->numPlayers: %d, origG->numPlayers: %d\n", testG->numPlayers, origG->numPlayers);
	}

	for(i = 0; i < treasure_map + 1; i++) {
		if(!(testG->supplyCount[i] == origG->supplyCount[i])) {
			stateSuccess = 1;
			printf("testG->supplyCount[%d]: %d, origG->supplyCount[%d]: %d\n", i, testG->supplyCount[i], i, origG->supplyCount[i]);
		}
	}

	for(i = 0; i < treasure_map + 1; i++) {
		if(!(testG->embargoTokens[i] == origG->embargoTokens[i])) {
			stateSuccess = 1;
			printf("testG->embargoTokens[%d]: %d, origG->embargoTokens[%d]: %d\n", i, testG->embargoTokens[i], i, origG->embargoTokens[i]);
		}
	}

	if(!(testG->outpostPlayed == origG->outpostPlayed)) {
		stateSuccess = 1;
		printf("testG->outpostPlayed: %d, origG->outpostPlayed: %d\n", testG->outpostPlayed, origG->outpostPlayed);
	}

	if(!(testG->whoseTurn == origG->whoseTurn)) {
		stateSuccess = 1;
		printf("testG->whoseTurn: %d, origG->whoseTurn: %d\n", testG->whoseTurn, origG->whoseTurn);
	}

	if(!(testG->phase == origG->phase)) {
		stateSuccess = 1;
		printf("testG->phase: %d, origG->phase: %d\n", testG->phase, origG->phase);
	}

	if(!(testG->numActions == origG->numActions)) {
		stateSuccess = 1;
		printf("testG->numActions: %d, origG->numActions: %d\n", testG->numActions, origG->numActions);
	}

	// if(!(testG->coins == origG->coins)) {
	// 	stateSuccess = 1;
	// 	printf("testG->coins: %d, origG->coins: %d\n", testG->coins, origG->coins);
	// }

	if(!(testG->numBuys == origG->numBuys)) {
		stateSuccess = 1;
		printf("testG->numBuys: %d, origG->numBuys: %d\n", testG->numBuys, origG->numBuys);
	}

	if(!(testG->playedCardCount == origG->playedCardCount)) {
		stateSuccess = 1;
		printf("testG->playedCardCount: %d, origG->playedCardCount: %d\n", testG->playedCardCount, origG->playedCardCount);
	}

	if(stateSuccess == 0) {
		for(i = 0; i < testG->numPlayers; i++) {
			if(!(testG->handCount[i] == origG->handCount[i]))
				stateSuccess = 2;
		}

		for(i = 0; i < testG->numPlayers; i++) {
			if(!(testG->deckCount[i] == origG->deckCount[i]))
				stateSuccess = 2;
		}

		for(i = 0; i < testG->numPlayers; i++) {
			if(!(testG->discardCount[i] == origG->discardCount[i]))
				stateSuccess = 2;
		}

		if(stateSuccess == 0) {
			for(i = 0; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->handCount[i]; j++) {
					if(!(testG->hand[i][j] == origG->hand[i][j]))
						stateSuccess = 3;
				}
			}

			for(i = 0; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->deckCount[i]; j++) {
					if(!(testG->deck[i][j] == origG->deck[i][j]))
						stateSuccess = 3;
				}
			}

			for(i = 0; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->discardCount[i]; j++) {
					if(!(testG->discard[i][j] == origG->discard[i][j]))
						stateSuccess = 3;
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

	int bonusCoins, result, i, allSuccess = 0;

	int seed = 123;
	int numPlayers = 2;
	int currentPlayer = 0;
	struct gameState regGame, testGame;
	int useCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	initializeGame(numPlayers, useCards, seed, &testGame);
	memcpy(&regGame, &testGame, sizeof(struct gameState));

	printf(YEL ">>>>>>>>>>>>>>>>>> " CYN "BEGINNING TEST FOR FUNCTION \"%s\"" RESET YEL " <<<<<<<<<<<<<<<<<\n" RESET, TESTFUNC);
	printf(YEL ">>>>>>>>>>>>>>>>>>>>>>> " CYN "Testing with 5 cards in hand" RESET YEL " <<<<<<<<<<<<<<<<<<<<<<<<<\n" RESET);

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

	for(i = 0; i < 10; i++) {
		bonusCoins = i;
		updateCoins(currentPlayer, &testGame, bonusCoins);

		printf("Hand: C C C C C + bonus of %d ---> ", bonusCoins);
		if(assertTrue(testGame.coins, 5 + bonusCoins) && allSuccess == 0)
			allSuccess = 1;

		switch(compareGameStates(&testGame, &regGame)) {
			case 0:
				printf("	Gamestate Comparison ---> " GRN "PASSED\n\n" RESET);
				break;
			case 1:
				printf("	Gamestate Comparison ---> " RED "FAILED: TIER 1\n\n" RESET);
				break;
			case 2:
				printf("	Gamestate Comparison ---> " RED "FAILED: TIER 2\n\n" RESET);
				break;
			case 3:
				printf("	Gamestate Comparison --->  " RED "FAILED: TIER 3\n\n" RESET);
				break;
		}//switch
	}//for


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

	for(i = 0; i < 10; i++) {
		bonusCoins = i;
		result = updateCoins(currentPlayer, &testGame, bonusCoins);

		printf("Hand: S S S S S + bonus of %d ---> ", bonusCoins);
		if(assertTrue(testGame.coins, 10 + bonusCoins) && allSuccess == 0)
			allSuccess = 1;

		switch(compareGameStates(&testGame, &regGame)) {
			case 0:
				printf("	Gamestate Comparison ---> " GRN "PASSED\n\n" RESET);
				break;
			case 1:
				printf("	Gamestate Comparison ---> " RED "FAILED: TIER 1\n\n" RESET);
				break;
			case 2:
				printf("	Gamestate Comparison ---> " RED "FAILED: TIER 2\n\n" RESET);
				break;
			case 3:
				printf("	Gamestate Comparison --->  " RED "FAILED: TIER 3\n\n" RESET);
				break;
		}//switch
	}


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

	for(i = 0; i < 10; i++) {
		bonusCoins = i;
		result = updateCoins(currentPlayer, &testGame, bonusCoins);

		printf("Hand: G G G G G + bonus of %d ---> ", bonusCoins);
		if(assertTrue(testGame.coins, 15 + bonusCoins) && allSuccess == 0)
			allSuccess = 1;

		switch(compareGameStates(&testGame, &regGame)) {
			case 0:
				printf("	Gamestate Comparison ---> " GRN "PASSED\n\n" RESET);
				break;
			case 1:
				printf("	Gamestate Comparison ---> " RED "FAILED: TIER 1\n\n" RESET);
				break;
			case 2:
				printf("	Gamestate Comparison ---> " RED "FAILED: TIER 2\n\n" RESET);
				break;
			case 3:
				printf("	Gamestate Comparison --->  " RED "FAILED: TIER 3\n\n" RESET);
				break;
		}//switch
	}


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

	for(i = 0; i < 10; i++) {
		bonusCoins = i;
		result = updateCoins(currentPlayer, &testGame, bonusCoins);

		printf("Hand: C S G E E + bonus of %d ---> ", bonusCoins);
		if(assertTrue(testGame.coins, 6 + bonusCoins) && allSuccess == 0)
			allSuccess = 1;

		switch(compareGameStates(&testGame, &regGame)) {
			case 0:
				printf("	Gamestate Comparison ---> " GRN "PASSED\n\n" RESET);
				break;
			case 1:
				printf("	Gamestate Comparison ---> " RED "FAILED: TIER 1\n\n" RESET);
				break;
			case 2:
				printf("	Gamestate Comparison ---> " RED "FAILED: TIER 2\n\n" RESET);
				break;
			case 3:
				printf("	Gamestate Comparison --->  " RED "FAILED: TIER 3\n\n" RESET);
				break;
		}//switch
	}


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

	for(i = 0; i < 10; i++) {
		bonusCoins = i;
		result = updateCoins(currentPlayer, &testGame, bonusCoins);

		printf("Hand: Cur D P E K + bonus of %d ---> ", bonusCoins);
		if(assertTrue(testGame.coins, 0 + bonusCoins) && allSuccess == 0)
			allSuccess = 1;

		switch(compareGameStates(&testGame, &regGame)) {
			case 0:
				printf("	Gamestate Comparison ---> " GRN "PASSED\n\n" RESET);
				break;
			case 1:
				printf("	Gamestate Comparison ---> " RED "FAILED: TIER 1\n\n" RESET);
				break;
			case 2:
				printf("	Gamestate Comparison ---> " RED "FAILED: TIER 2\n\n" RESET);
				break;
			case 3:
				printf("	Gamestate Comparison --->  " RED "FAILED: TIER 3\n\n" RESET);
				break;
		}//switch
	}

	if(allSuccess == 0)
		printf(">>>>>>>>>>>>>>>> " GRN "SUCCESS -- ALL TESTS PASSED" RESET " <<<<<<<<<<<<<<<<<<\n");
	else
		printf(">>>>>>>>>>>>>>>> " RED "FAIL -- AT LEAST ONE CASE FAILED" RESET " <<<<<<<<<<<<<<<<<<<<\n");

	return 0;
}