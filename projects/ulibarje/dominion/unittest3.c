/* Name: unittest2
 * Author: Jesse Ulibarri
 * CS362 - Assignment 3
 * Test For: "handCard"
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

#define TESTFUNC "handCard"


/*************************************************************************
* Name: assertTrue
*
* Description: 
*
*************************************************************************/
int assertTrue(int test, int expect) {
	if(test == expect) {
		if(PRINT) {
			printf(GRN "TEST PASSED " RESET);
			printf("Test: %d, Expected: %d\n", test, expect);
		}
		return 0;
	}
	else {
		if(PRINT) {
			printf(RED "TEST FAILED " RESET);
			printf("Test: %d, Expected: %d\n", test, expect);
		}
		return 1;
	}
}

/****************************************************************************************/
/************************************* MAIN *********************************************/
/****************************************************************************************/
int main() {

	int i, player, test, cardNum, result;

	int maxHandCount = 5;
	int allSuccess = 0;
	int seed = 123;
	struct gameState testGame;
	int useCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	printf("Beginning \"%s\" test\n", TESTFUNC);

	int numTests = 10;
	for(test = 0; test < numTests; test++) {
		// printf("\n>>>>>>>>>>>>>>>>> Starting new test <<<<<<<<<<<<<<<<<<<<<<<<<\n");
		memset(&testGame, '\0', sizeof(struct gameState));
		initializeGame(MAX_PLAYERS, useCards, seed++, &testGame);

		for (player = 0; player < MAX_PLAYERS; player++) {

			testGame.whoseTurn = player;
			testGame.handCount[player] = 0;
			for(i = 0; i < maxHandCount; i++) { drawCard(player, &testGame); }

        	for (cardNum = 0; cardNum < maxHandCount; cardNum++) {

        		result = handCard(cardNum, &testGame);

        		if(assertTrue(player, whoseTurn(&testGame)))
        			printf("Wrong player was returned!! Should have been: %d, Player that was returned: %d\n", player, whoseTurn(&testGame));

        		if(assertTrue(result, testGame.hand[player][cardNum])) {
        			allSuccess = 1;
        			printf("TEST FAILED: at player = %d, card position = %d\n", player, cardNum);
        		}
           }
       }
	}

	// All tests have completed, print out if all were successful, or if there was any failures.
	if(allSuccess == 0)
		printf("SUCCESS -- All Tests Passed\n");
	else
		printf("FAIL -- At Least One Case Failed\n");


	return 0;
}