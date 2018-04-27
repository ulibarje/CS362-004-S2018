/* Name: unittest1
 * Author: Jesse Ulibarri
 * CS362 - Assignment 3
 * Test For: "baron" card
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

#define TESTCARD "baron"


/*************************************************************************
* Name: assertTrue
*
* Description: 
*
*************************************************************************/
int assertTrue(int test, int expect) {
	if(test == expect) {
			printf("TEST PASSED ");
			printf("Test: %d, Expected: %d\n", test, expect);
		return 0;
	}
	else {
			printf("TEST FAILED ");
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

	// if(!(testG->numBuys == refG->numBuys)) {
	// 	stateSuccess = 1;
	// 	printf("FAILED: testG->numBuys: %d, refG->numBuys: %d\n", testG->numBuys, refG->numBuys);
	// }

	// if(!(testG->playedCardCount == refG->playedCardCount)) {
	// 	stateSuccess = 1;
	// 	printf("FAILED: testG->playedCardCount: %d, refG->playedCardCount: %d\n", testG->playedCardCount, refG->playedCardCount);
	// }

	// Tier 2
	if(stateSuccess == 0) {
		for(i = 1; i < testG->numPlayers; i++) {
			if(!(testG->handCount[i] == refG->handCount[i])) {
				stateSuccess = 1;
				printf("FAILED: testG->handCount[player = %d]: %d, refG->handCount[player = %d]: %d\n", i, testG->handCount[i], i, refG->handCount[i]);
			}
		}

		for(i = 1; i < testG->numPlayers; i++) {
			if(!(testG->deckCount[i] == refG->deckCount[i])) {
				stateSuccess = 1;
				printf("FAILED: testG->deckCount[player = %d]: %d, refG->deckCount[player = %d]: %d\n", i, testG->deckCount[i], i, refG->deckCount[i]);
			}
		}

		// for(i = 0; i < testG->playedCardCount; i++) {
		// 	if(!(testG->playedCards[i] == refG->playedCards[i])) {
		// 		stateSuccess = 1;
		// 		printf("FAILED: testG->playedCards[%d]: %d, refG->playedCards[%d]: %d\n", i, testG->playedCards[i], i, refG->playedCards[i]);
		// 	}
		// }

		for(i = 1; i < testG->numPlayers; i++) {
			if(!(testG->discardCount[i] == refG->discardCount[i])) {
				stateSuccess = 1;
				printf("FAILED: testG->discardCount[player = %d]: %d, refG->discardCount[player = %d]: %d\n", i, testG->discardCount[i], i, refG->discardCount[i]);
			}
		}

		// Tier 3
		if(stateSuccess == 0) {
			for(i = 1; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->handCount[i]; j++) {
					if(!(testG->hand[i][j] == refG->hand[i][j])) {
						stateSuccess = 1;
						printf("FAILED: testG->hand[player = %d][%d]: %d, refG->hand[player = %d][%d]: %d\n", i, j, testG->hand[i][j], i, j, refG->hand[i][j]);
					}
				}
			}

			for(i = 1; i < testG->numPlayers; i++) {
				for(j = 0; j < testG->deckCount[i]; j++) {
					if(!(testG->deck[i][j] == refG->deck[i][j])) {
						stateSuccess = 1;
						printf("FAILED: testG->deck[player = %d][%d]: %d, refG->deck[player = %d][%d]: %d\n", i, j, testG->deck[i][j], i, j, refG->deck[i][j]);
					}
				}
			}

			for(i = 1; i < testG->numPlayers; i++) {
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


void printHand(struct gameState* G) {
	int i;
	for(i = 0; i < G->handCount[G->whoseTurn]; i++) {
		printf("Card %d: %d\n", i, G->hand[G->whoseTurn][i]);
	}
}


/****************************************************************************************/
/************************************* MAIN *********************************************/
/****************************************************************************************/
int main() {

	int i, allPassed;

	int seed = 123;
	int numPlayers = 2;
	int player = 0;
	int handPos = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int moreCoins = 4, moreBuys = 1;

	struct gameState refGame, testGame;
	int useCards[10] = {baron, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	initializeGame(numPlayers, useCards, seed, &refGame);
	refGame.hand[player][handPos] = baron;

	printf("\n====================== Beginning \"%s\" test ======================\n", TESTCARD);

/****************************************************************************************/
/****************************************************************************************/
	memcpy(&testGame, &refGame, sizeof(struct gameState));

	int choice1 = 1;
	printf("-------> Testing \"choice1\", discard estate for +4 coins\n");
	cardEffect(baron, choice1, choice2, choice3, &testGame, handPos, &bonus);

	printf("Testing number of estates in resource pile ---> ");
	if(assertTrue(testGame.supplyCount[estate], refGame.supplyCount[estate] - 0)) {
		allPassed = 1;
	}
	printf("Testing handCount ---> ");
	if(assertTrue(testGame.handCount[player], refGame.handCount[player] - 2)) {
		allPassed = 1;
	}
	printf("Testing coin count ---> ");
	if(assertTrue(testGame.coins, refGame.coins + moreCoins)) {
		allPassed = 1;
	}
	printf("Testing number of buys ---> ");
	if(assertTrue(testGame.numBuys, refGame.numBuys + moreBuys)) {
		allPassed = 1;
	}
	printf("Testing number of cards in discard pile ---> ");
	if(assertTrue(testGame.discardCount[player], refGame.discardCount[player] + 1)) {
		allPassed = 1;
	}
	printf("Testing playedCardCount ---> ");
	if(assertTrue(testGame.playedCardCount, refGame.playedCardCount + 1)) {
		allPassed = 1;
	}
	printf("Check that %s is in playedCards pile ---> ", TESTCARD);
	if(testGame.playedCardCount > 0) {
		i = 0;
		if(i < testGame.playedCardCount) {
			if(testGame.playedCards[i] == adventurer) {
				printf("PASSED: Found \"%s\" in playedCards pile\n", TESTCARD);
			}
			else
				i++;
		}
		else {
			printf("FAILED: Did not find \"%s\" in playedCards pile\n", TESTCARD);
			allPassed = 1;
		}
	}
	else
		printf("FAILED: No cards in playedCard pile\n");

	// Compare the two game states and make sure that they are the same
	printf("Gamestate comparison of non-involved parameters ---> ");
    if(compareGameStates(&testGame, &refGame))
    	allPassed = 1;
    else
    	printf("PASSED\n");


/****************************************************************************************/
/****************************************************************************************/
	memcpy(&testGame, &refGame, sizeof(struct gameState));

	// Remove all estates from the hand
	for(i = 0; i < testGame.handCount[player]; i++) {
		if(testGame.hand[player][i] == estate) {
			testGame.hand[player][i] = copper;
		}
	}

	choice1 = 1;
	printf("\n-------> Testing \"choice1\", (discard estate for +4 coins) with no estates in hand\n");
	cardEffect(baron, choice1, choice2, choice3, &testGame, handPos, &bonus);

	printf("Testing number of estates in resource pile ---> ");
	if(assertTrue(testGame.supplyCount[estate], refGame.supplyCount[estate] - 1)) {
		allPassed = 1;
	}
	printf("Testing handCount ---> ");
	if(assertTrue(testGame.handCount[player], refGame.handCount[player] - 1)) {
		allPassed = 1; // 
	}
	printf("Testing coin count ---> ");
	if(assertTrue(testGame.coins, refGame.coins + 0)) {
		allPassed = 1;
	}
	printf("Testing number of buys ---> ");
	if(assertTrue(testGame.numBuys, refGame.numBuys + moreBuys)) {
		allPassed = 1;
	}
	printf("Testing number of cards in discard pile ---> ");
	if(assertTrue(testGame.discardCount[player], refGame.discardCount[player] + 1)) {
		allPassed = 1;
	}
	printf("Testing playedCardCount ---> ");
	if(assertTrue(testGame.playedCardCount, refGame.playedCardCount + 1)) {
		allPassed = 1;
	}
	printf("Check that %s is in playedCards pile ---> ", TESTCARD);
	if(testGame.playedCardCount > 0) {
		i = 0;
		if(i < testGame.playedCardCount) {
			if(testGame.playedCards[i] == adventurer) {
				printf("PASSED: Found \"%s\" in playedCards pile\n", TESTCARD);
			}
			else
				i++;
		}
		else {
			printf("FAILED: Did not find \"%s\" in playedCards pile\n", TESTCARD);
			allPassed = 1;
		}
	}
	else
		printf("FAILED: No cards in playedCard pile\n");

	// Compare the two game states and make sure that they are the same
	printf("Gamestate comparison of non-involved parameters ---> ");
    if(compareGameStates(&testGame, &refGame))
    	allPassed = 1;
    else
    	printf("PASSED\n");


/****************************************************************************************/
/****************************************************************************************/
	memcpy(&testGame, &refGame, sizeof(struct gameState));

	choice1 = 0;
	printf("\n-------> Testing \"choice1\", gain estate\n");
	cardEffect(baron, choice1, choice2, choice3, &testGame, handPos, &bonus);

	printf("Testing number of estates in resource pile ---> ");
	if(assertTrue(testGame.supplyCount[estate], refGame.supplyCount[estate] - 1)) {
		allPassed = 1;
	}
	printf("Testing handCount ---> ");
	if(assertTrue(testGame.handCount[player], refGame.handCount[player] - 1)) {
		allPassed = 1;
	}
	printf("Testing coin count ---> ");
	if(assertTrue(testGame.coins, refGame.coins + 0)) {
		allPassed = 1;
	}
	printf("Testing number of buys ---> ");
	if(assertTrue(testGame.numBuys, refGame.numBuys + moreBuys)) {
		allPassed = 1;
	}
	printf("Testing number of cards in discard pile ---> ");
	if(assertTrue(testGame.discardCount[player], refGame.discardCount[player] + 0)) {
		allPassed = 1;
	}
	printf("Testing playedCardCount ---> ");
	if(assertTrue(testGame.playedCardCount, refGame.playedCardCount + 1)) {
		allPassed = 1;
	}
	printf("Check that %s is in playedCards pile ---> ", TESTCARD);
	if(testGame.playedCardCount > 0) {
		i = 0;
		if(i < testGame.playedCardCount) {
			if(testGame.playedCards[i] == adventurer) {
				printf("PASSED: Found \"%s\" in playedCards pile\n", TESTCARD);
			}
			else
				i++;
		}
		else {
			printf("FAILED: Did not find \"%s\" in playedCards pile\n", TESTCARD);
			allPassed = 1;
		}
	}
	else
		printf("FAILED: No cards in playedCard pile\n");

	// Compare the two game states and make sure that they are the same
	printf("Gamestate comparison of non-involved parameters ---> ");
    if(compareGameStates(&testGame, &refGame))
    	allPassed = 1;
    else
    	printf("PASSED\n");

    printf("\n");
    if(allPassed == 0) { 
    	printf("-------> \"%s\" test - PASSED\n\n", TESTCARD);
    }
    else {
    	printf("-------> \"%s\" test - FAILED\n\n", TESTCARD);
    }

	return 0;
}