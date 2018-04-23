/* Name: unittest2
 * Author: Jesse Ulibarri
 * CS362 - Assignment 3
 * Test For: "endTurn"
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

#define TESTFUNC "endTurn"


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

	// if(!(testG->outpostPlayed == origG->outpostPlayed)) {
	// 	stateSuccess = 1;
	// 	printf("testG->outpostPlayed: %d, origG->outpostPlayed: %d\n", testG->outpostPlayed, origG->outpostPlayed);
	// }

	// if(!(testG->whoseTurn == origG->whoseTurn)) {
	// 	stateSuccess = 1;
	// 	printf("testG->whoseTurn: %d, origG->whoseTurn: %d\n", testG->whoseTurn, origG->whoseTurn);
	// }

	// if(!(testG->phase == origG->phase)) {
	// 	stateSuccess = 1;
	// 	printf("testG->phase: %d, origG->phase: %d\n", testG->phase, origG->phase);
	// }

	// if(!(testG->numActions == origG->numActions)) {
	// 	stateSuccess = 1;
	// 	printf("testG->numActions: %d, origG->numActions: %d\n", testG->numActions, origG->numActions);
	// }

	// if(!(testG->coins == origG->coins)) {
	// 	stateSuccess = 1;
	// 	printf("testG->coins: %d, origG->coins: %d\n", testG->coins, origG->coins);
	// }

	// if(!(testG->numBuys == origG->numBuys)) {
	// 	stateSuccess = 1;
	// 	printf("testG->numBuys: %d, origG->numBuys: %d\n", testG->numBuys, origG->numBuys);
	// }

	// if(!(testG->playedCardCount == origG->playedCardCount)) {
	// 	stateSuccess = 1;
	// 	printf("testG->playedCardCount: %d, origG->playedCardCount: %d\n", testG->playedCardCount, origG->playedCardCount);
	// }

	if(stateSuccess == 0) {
		// for(i = 0; i < testG->numPlayers; i++) {
		// 	if(!(testG->handCount[i] == origG->handCount[i]))
		// 		stateSuccess = 2;
		// }

		for(i = 0; i < testG->numPlayers; i++) {
			if(!(testG->deckCount[i] == origG->deckCount[i]))
				stateSuccess = 2;
		}

		// for(i = 0; i < testG->numPlayers; i++) {
		// 	if(!(testG->discardCount[i] == origG->discardCount[i]))
		// 		stateSuccess = 2;
		// }

		if(stateSuccess == 0) {
			// for(i = 0; i < testG->numPlayers; i++) {
			// 	for(j = 0; j < testG->handCount[i]; j++) {
			// 		if(!(testG->hand[i][j] == origG->hand[i][j]))
			// 			stateSuccess = 3;
			// 	}
			// }

			for(i = 0; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->deckCount[i]; j++) {
					if(!(testG->deck[i][j] == origG->deck[i][j]))
						stateSuccess = 3;
				}
			}

			// for(i = 0; i < testG->numPlayers; i++) {
			// 	for(j = 0; j < testG->discardCount[i]; j++) {
			// 		if(!(testG->discard[i][j] == origG->discard[i][j]))
			// 			stateSuccess = 3;
			// 	}
			// }
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

/*************************************************************************
* Name: testFunc
*
* Description: This function compares the test game state object with 
*	a reference game state object. This function only compares the parameters
*	that were changed by the "function-under-test".
*
*************************************************************************/
int testFunc(struct gameState* testG, struct gameState* game) {

	int successFlag = 0;

	// Compare values that have changed between regular game and test game
	printf("whoseTurn test 		---> ");
	if(assertTrue(testG->whoseTurn, game->whoseTurn) && successFlag == 0)
		successFlag = 1;
	printf("outpostPlayed test 	---> ");
	if(assertTrue(testG->outpostPlayed, game->outpostPlayed) && successFlag == 0)
		successFlag = 1;
	printf("phase test 		---> ");
	if(assertTrue(testG->phase, game->phase) && successFlag == 0)
		successFlag = 1;
	printf("numActions test 	---> ");
	if(assertTrue(testG->numActions, game->numActions) && successFlag == 0)
		successFlag = 1;
	printf("coins test 		---> ");
	if(assertTrue(testG->coins, game->coins) && successFlag == 0)
		successFlag = 1;
	printf("numBuys test 		---> ");
	if(assertTrue(testG->numBuys, game->numBuys) && successFlag == 0)
		successFlag = 1;
	printf("playedCardCount test 	---> ");
	if(assertTrue(testG->playedCardCount, game->playedCardCount) && successFlag == 0)
		successFlag = 1;
	printf("handCount test 		---> ");
	if(assertTrue(testG->handCount[testG->whoseTurn], game->handCount[game->whoseTurn]) && successFlag == 0)
		successFlag = 1;

	return successFlag;
}

/****************************************************************************************/
/************************************* MAIN *********************************************/
/****************************************************************************************/

int main() {

	int i, j, numPlayers;

	int allSuccess = 0;
	int seed = 123;
	struct gameState regGame, testGame;
	int useCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	printf(YEL ">>>>>>>>>>>>>>>>>> " CYN "BEGINNING TEST FOR FUNCTION \"%s\"" RESET YEL " <<<<<<<<<<<<<<<<<\n" RESET, TESTFUNC);

	// Iterate through the number of possible players in a single game
	for(numPlayers = 2; numPlayers <= MAX_PLAYERS; numPlayers++) {
		printf(YEL ">>>>>>>>>>>>>>>>>>>> " CYN "Testing with a %d player game" RESET YEL " <<<<<<<<<<<<<<<<<<<<<<<<\n"RESET, numPlayers);

		// For each set of "number of players", test the endTurn function for each player.
		for(j = 0; j < numPlayers; j++) {
			initializeGame(numPlayers, useCards, seed, &testGame);
			memcpy(&regGame, &testGame, sizeof(struct gameState));

			// Manually change whose turn it is
			testGame.whoseTurn = j;
			endTurn(&testGame);

			// Manually set the parameters in the reference game to the values
			// we know should be there.
			if(j == numPlayers - 1)
				regGame.whoseTurn = 0;
			else
				regGame.whoseTurn = j + 1;

			regGame.outpostPlayed = 0;
		  	regGame.phase = 0;
		  	regGame.numActions = 1;
		  	regGame.coins = 0;
		  	regGame.numBuys = 1;
		  	regGame.playedCardCount = 0;
		  	regGame.handCount[regGame.whoseTurn] = 0;

		  	for(i = 0; i < 5; i++) {
				drawCard(regGame.whoseTurn, &regGame);
			}
			updateCoins(regGame.whoseTurn, &regGame, 0);

			// Compare the test gamestate object with the reference
			allSuccess = testFunc(&testGame, &regGame);
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
	}

	// All tests have completed, print out if all were successful, or if there was any failures.
	if(allSuccess == 0)
		printf(YEL ">>>>>>>>>>>>>>>> " GRN "SUCCESS -- ALL TESTS PASSED" RESET YEL " <<<<<<<<<<<<<<<<<<\n" RESET);
	else
		printf(YEL ">>>>>>>>>>>>>>>> " RED "FAIL -- AT LEAST ONE CASE FAILED" RESET YEL " <<<<<<<<<<<<<<<<<<<<\n" RESET);


	return 0;
}