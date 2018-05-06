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

char* CARDS[27] = {"curse",
				   "estate",
				   "duchy",
				   "province",

				   "copper",
				   "silver",
				   "gold",

				   "adventurer",
				   
				   "council_room",
				   "feast",
				   "gardens",
				   "mine", 

				   "remodel",
				   "smithy",
				   "village",

				   "baron", 

				   "great_hall",
				   "minion",
				   "steward",
				   "tribute",

				   "ambassador",
				   "cutpurse",
				   "embargo",
				   "outpost",
				   "salvager",
				   "sea_hag",
				   "treasure_map"
				  };


/*************************************************************************
* Name: assertTrue
*
* Description: 
*
*************************************************************************/
int assertTrue(int test, int expect) {
	if(test == expect) {
		printf("PASSED\n");
		// printf("Test: %d, Expected: %d\n", test, expect);
		return 0;
	}
	else {
		printf("FAILED ");
		printf("Test: %d, Expected: %d\n", test, expect);
		return 1;
	}
}


/****************************************************************************************/
/************************************* MAIN *********************************************/
/****************************************************************************************/
int main() {

	int i, cardNum, result;

	int player = 0;
	int allSuccess = 0;
	int seed = 123;
	struct gameState testGame;
	int useCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	printf("***************************************************************************\n");
	printf("************************ BEGINNING \"%s\" TEST ************************\n", TESTFUNC);
	printf("***************************************************************************\n\n");


	initializeGame(MAX_PLAYERS, useCards, seed++, &testGame);


	testGame.handCount[player] = 27;
	for(i = 0; i <= treasure_map; i++) { testGame.hand[player][i] = i; }

	for (cardNum = 0; cardNum < testGame.handCount[player]; cardNum++) {

		result = handCard(cardNum, &testGame);

		if(strlen(CARDS[result]) <= 5)
			printf("Expecting: %s,			Received: %s			--->	", CARDS[testGame.hand[player][cardNum]], CARDS[result]);
		else if(strlen(CARDS[result]) <= 7)
			printf("Expecting: %s,			Received: %s		--->	", CARDS[testGame.hand[player][cardNum]], CARDS[result]);
		else if(strlen(CARDS[result]) <= 8)
			printf("Expecting: %s,		Received: %s		--->	", CARDS[testGame.hand[player][cardNum]], CARDS[result]);
		else if(strlen(CARDS[result]) <= 11)
			printf("Expecting: %s,		Received: %s	--->	", CARDS[testGame.hand[player][cardNum]], CARDS[result]);
		else
			printf("Expecting: %s,	Received: %s	--->	", CARDS[testGame.hand[player][cardNum]], CARDS[result]);

		if(assertTrue(result, testGame.hand[player][cardNum])) {
			allSuccess = 1;
		}
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