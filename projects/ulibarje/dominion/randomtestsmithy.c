/* Name: randomtestcard1
 * Author: Jesse Ulibarri
 * CS362 - Assignment 4
 * Test For: "smithy" card
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "testFunctions.h"

#define PRINT 	0
#define PRINT1 	0

#define TESTCARD "smithy"

int compareGameStates(struct gameState* testG, struct gameState* refG, int playerUT);

/****************************************************************************************/
/************************************* MAIN *********************************************/
/****************************************************************************************/
int main() {

	int i, test, randPlayer, randHandPos;

	// test counter variables that track how many times each test fails
	int handCountTC = 0;
	int deckCountTC = 0;
	int cardsCheckTC = 0;
	int playedCardCountTC = 0;
	int playedCardsPileTC = 0;
	int gamestateCompareTC = 0;

	int iterations = 100000;

	int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int numDraws = 3, numDiscards = 1;

	struct gameState refGame, testGame;
	int useCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int cardsInGame[17] = {curse, estate, duchy, province, copper, silver, gold, adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	SelectStream(2);

	/****************************************************************************************/
	/************************************* BEGINNING TEST ***********************************/
	/****************************************************************************************/

	for(test = 0; test < iterations; test++) {

		PutSeed(test + 1);

		// Clear out both gamestate structures
		memset(&refGame, '\0', sizeof(struct gameState));
		memset(&testGame, '\0', sizeof(struct gameState));

		// Generate a random reference gamestate
		randomGamestate(&refGame, cardsInGame, useCards);

		// Grab a random player to test with
		randPlayer = (int)floor(Random() * refGame.numPlayers);
		randHandPos = (int)floor(Random() * refGame.handCount[randPlayer]);

		refGame.whoseTurn = randPlayer;
		refGame.hand[randPlayer][randHandPos] = smithy;

		// Copy the reference gamestate to the test gamestate
		memcpy(&testGame, &refGame, sizeof(struct gameState));
		// if(compareGameStates(&testGame, &refGame, randPlayer))
		// 	printf("failed!!!");

		cardEffect(smithy, choice1, choice2, choice3, &testGame, randHandPos, &bonus);

		/****************************************************************************************/
		if(PRINT1)
			printf("Testing handCount									--->	");
		if(assertTrue(testGame.handCount[randPlayer], refGame.handCount[randPlayer] + numDraws - numDiscards)) {
			handCountTC += 1;
		}

		/****************************************************************************************/
		if(PRINT1)
			printf("Testing deckCount									--->	");
		if(assertTrue(testGame.deckCount[randPlayer], refGame.deckCount[randPlayer] - numDraws)) {
			deckCountTC += 1;
		}

		/****************************************************************************************/
		if(PRINT1)
			printf("Check that 3 new cards came from deck	--->	");
		if((testGame.hand[randPlayer][testGame.handCount[randPlayer] - 2] == refGame.deck[randPlayer][refGame.deckCount[randPlayer] - 1])  &&
			(testGame.hand[randPlayer][testGame.handCount[randPlayer] - 1] == refGame.deck[randPlayer][refGame.deckCount[randPlayer] - 2]) &&
			(testGame.hand[randPlayer][randHandPos] == refGame.deck[randPlayer][refGame.deckCount[randPlayer] - 3])) {
			if(PRINT1)
				printf("PASSED\n");
		}
		else {
			cardsCheckTC += 1;
			if(PRINT1)
				printf("FAILED\n");
		}

		/****************************************************************************************/
		if(PRINT1)
			printf("Testing playedCardCount				--->	");
		if(assertTrue(testGame.playedCardCount, refGame.playedCardCount + 1)) {
			playedCardCountTC += 1;
		}

		/****************************************************************************************/
		if(PRINT1)
			printf("Check that %s is in playedCards pile	--->	", TESTCARD);
		if(testGame.playedCardCount > 0) {
			i = 0;
			if(i < testGame.playedCardCount) {
				if(testGame.playedCards[i] == adventurer) {
					if(PRINT1)
						printf("PASSED\n");
				}
				else
					i++;
			}
			else {
				if(PRINT1)
					printf("FAILED\n");
				playedCardsPileTC += 1;
			}
		}
		else {
			if(PRINT1)
				printf("FAILED: No cards in playedCard pile\n");
			playedCardsPileTC += 1;
		}

		/****************************************************************************************/
		// Compare the two game states and make sure that they are the same
		if(PRINT1)
			printf("Gamestate comparison of non-involved parameters	--->	");
	    if(compareGameStates(&testGame, &refGame, randPlayer))
	    	gamestateCompareTC += 1;
	    else {
	    	if(PRINT1)
	    		printf("PASSED\n");
	    }
	}//main test "for" loop

	/****************************************************************************************/
	
	// All tests have completed, print out if all were successful, or if there was any failures.
	printf("***************************************************************************\n");
	printf("************************ \"%s\" UNIT TEST RESULTS ***********************\n", TESTCARD);
	printf("\"handCount\" variable test 			---> %d/%d tests PASSED\n", (iterations - handCountTC), iterations);
	printf("\"deckCount\" variable test 			---> %d/%d tests PASSED\n", (iterations - deckCountTC), iterations);
	printf("New cards came from deck test 		---> %d/%d tests PASSED\n", (iterations - cardsCheckTC), iterations);
	printf("\"playedCardCount\" variable test 	---> %d/%d tests PASSED\n", (iterations - playedCardCountTC), iterations);
	printf("\"playedCards pile\" test 			---> %d/%d tests PASSED\n", (iterations - playedCardsPileTC), iterations);
	printf("Unused variables comparison test 	---> %d/%d tests PASSED\n", (iterations - gamestateCompareTC), iterations);

	printf("***************************************************************************\n");
	printf("\n");


	// printGS(&testGame, "testGame");
	// printGS(&refGame, "refGame");

	return 0;
}

/****************************************************************************************/
/************************************* FUNCTIONS ****************************************/
/****************************************************************************************/


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
int compareGameStates(struct gameState* testG, struct gameState* refG, int playerUT) {

	int i, j;
	int stateSuccess = 0;

	// Tier 1
	if(!(testG->numPlayers == refG->numPlayers)) {
		stateSuccess = 1;
		if(PRINT)
			printf("FAILED: testG->numPlayers: %d, refG->numPlayers: %d\n", testG->numPlayers, refG->numPlayers);
		
	}

	for(i = 0; i < treasure_map + 1; i++) {
		if(!(testG->supplyCount[i] == refG->supplyCount[i])) {
		stateSuccess = 1;
		if(PRINT)
			printf("FAILED: testG->supplyCount[%d]: %d, refG->supplyCount[%d]: %d\n", i, testG->supplyCount[i], i, refG->supplyCount[i]);
		}
	}

	for(i = 0; i < treasure_map + 1; i++) {
		if(!(testG->embargoTokens[i] == refG->embargoTokens[i])) {
		stateSuccess = 1;
		if(PRINT)
			printf("FAILED: testG->embargoTokens[%d]: %d, refG->embargoTokens[%d]: %d\n", i, testG->embargoTokens[i], i, refG->embargoTokens[i]);
		}
	}

	if(!(testG->outpostPlayed == refG->outpostPlayed)) {
		stateSuccess = 1;
		if(PRINT)
			printf("FAILED: testG->outpostPlayed: %d, refG->outpostPlayed: %d\n", testG->outpostPlayed, refG->outpostPlayed);
	}

	if(!(testG->whoseTurn == refG->whoseTurn)) {
		stateSuccess = 1;
		if(PRINT)
			printf("FAILED: testG->whoseTurn: %d, refG->whoseTurn: %d\n", testG->whoseTurn, refG->whoseTurn);
	}

	if(!(testG->phase == refG->phase)) {
		stateSuccess = 1;
		if(PRINT)
			printf("FAILED: testG->phase: %d, refG->phase: %d\n", testG->phase, refG->phase);
	}

	if(!(testG->numActions == refG->numActions)) {
		stateSuccess = 1;
		if(PRINT)
			printf("FAILED: testG->numActions: %d, refG->numActions: %d\n", testG->numActions, refG->numActions);
	}

	if(!(testG->coins == refG->coins)) {
		stateSuccess = 1;
		if(PRINT)
			printf("FAILED: testG->coins: %d, refG->coins: %d\n", testG->coins, refG->coins);
	}

	if(!(testG->numBuys == refG->numBuys)) {
		stateSuccess = 1;
		if(PRINT)
			printf("FAILED: testG->numBuys: %d, refG->numBuys: %d\n", testG->numBuys, refG->numBuys);
	}

	// if(!(testG->playedCardCount == refG->playedCardCount)) {
	// 	stateSuccess = 1;
	// 	if(PRINT)
	// 		printf("FAILED: testG->playedCardCount: %d, refG->playedCardCount: %d\n", testG->playedCardCount, refG->playedCardCount);
	// }

	// Tier 2
	if(stateSuccess == 0) {
		for(i = 1; i < testG->numPlayers; i++) {
			if(i != playerUT) {
				if(!(testG->handCount[i] == refG->handCount[i])) {
					stateSuccess = 1;
					if(PRINT) {
						printf("Player under test = %d\n", playerUT);
						printf("FAILED: testG->handCount[player = %d]: %d, refG->handCount[player = %d]: %d\n", i, testG->handCount[i], i, refG->handCount[i]);
					}
				}
			}
		}

		for(i = 1; i < testG->numPlayers; i++) {
			if(i != playerUT) {
				if(!(testG->deckCount[i] == refG->deckCount[i])) {
					stateSuccess = 1;
					if(PRINT) {
						printf("Player under test = %d\n", playerUT);
						printf("FAILED: testG->deckCount[player = %d]: %d, refG->deckCount[player = %d]: %d\n", i, testG->deckCount[i], i, refG->deckCount[i]);
					}
				}
			}
		}

		// for(i = 0; i < testG->playedCardCount; i++) {
		// 	if(!(testG->playedCards[i] == refG->playedCards[i])) {
		// 		stateSuccess = 1;
		// 		if(PRINT)
		// 			printf("FAILED: testG->playedCards[%d]: %d, refG->playedCards[%d]: %d\n", i, testG->playedCards[i], i, refG->playedCards[i]);
		// 	}
		// }

		for(i = 0; i < testG->numPlayers; i++) {
			if(i != playerUT) {
				if(!(testG->discardCount[i] == refG->discardCount[i])) {
					stateSuccess = 1;
					if(PRINT) {
						printf("Player under test = %d\n", playerUT);
						printf("FAILED: testG->discardCount[player = %d]: %d, refG->discardCount[player = %d]: %d\n", i, testG->discardCount[i], i, refG->discardCount[i]);
					}
				}
			}
		}

		// Tier 3
		if(stateSuccess == 0) {
			for(i = 0; i < testG->numPlayers; i++) {
				if(i != playerUT) {
					for(j = 0; j < testG->handCount[i]; j++) {
						if(!(testG->hand[i][j] == refG->hand[i][j])) {
							stateSuccess = 1;
							if(PRINT) {
								printf("Player under test = %d\n", playerUT);
								printf("FAILED: testG->hand[player = %d][%d]: %d, refG->hand[player = %d][%d]: %d\n", i, j, testG->hand[i][j], i, j, refG->hand[i][j]);
							}
						}
					}
				}
			}

			for(i = 0; i < testG->numPlayers; i++) {
				if(i != playerUT) {
					for(j = 0; j < testG->deckCount[i]; j++) {
						if(!(testG->deck[i][j] == refG->deck[i][j])) {
							stateSuccess = 1;
							if(PRINT) {
								printf("Player under test = %d\n", playerUT);
								printf("FAILED: testG->deck[player = %d][%d]: %d, refG->deck[player = %d][%d]: %d\n", i, j, testG->deck[i][j], i, j, refG->deck[i][j]);
							}
						}
					}
				}
			}

			for(i = 0; i < testG->numPlayers; i++) {
				if(i != playerUT) {
					for(j = 0; j < testG->discardCount[i]; j++) {
						if(!(testG->discard[i][j] == refG->discard[i][j])) {
							stateSuccess = 1;
							if(PRINT) {
								printf("Player under test = %d\n", playerUT);
								printf("FAILED: testG->discard[player = %d][%d]: %d, refG->discard[player = %d][%d]: %d\n", i, j, testG->discard[i][j], i, j, refG->discard[i][j]);
							}
						}
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