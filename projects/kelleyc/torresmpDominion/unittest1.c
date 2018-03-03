/******************************************************************************
** Cody Kelley
** CS362 - Winter 2018
**
** unittest1.c
**
** Include the following lines in your makefile:
**
** unittest1: unittest1.c dominion.o rngs.o
**      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
**
** This unit test evaluates:
** int isGameOver(struct gameState* state) which returns 0 if game is not
** over and 1 if game is over.  Game ending conditions are any 3 cards in
** the supply pile are empty OR the province pile is empty.
**
** It accepts a valid gameState as a parameter.  It sets up a gameState and
** initializes all supply piles to have 1 card.  It then loops through all
** cards setting 3 at a time to 0 and checks that isGameOver() returns a value
** of 1 as expected.  Finally, it sets province only to 0, and checks that
** isGameOver() returns 1 as expected.
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"

//set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int assertTrue(const int a, const int b) {

	if (a == b) {

		printf("PASSED!\n");
		return 1;
	}

	printf("FAILED!\n");
	return 0;
}

int main() {

	int i, j;
	int failed = 0;		//how many tests failed
	struct gameState G;
	//struct gameState pre;

	//memcpy(&pre, &G, sizeof(struct gameState));
	//assert(memcmp(&pre, &G, sizeof(struct gameState)) == 0);

	printf("\n*--------------- TESTING UNITTEST1 - isGameOver() ---------------*\n\n");

#if (NOISY_TEST == 1)
	printf("--Looping through cards setting 3 piles to 0 at a time, expecting return 1\n");
#endif

	i = 0;		//variable to keep track of which cards already tested

	while (i < 27) {

		for (j = 0; j < 27; ++j) {	//ensure all cards have at least 1 (not empty)

			G.supplyCount[j] = 1;
		}

		for (j = 0; j < 3; ++j) {	//set 3 cards at a time to empty

#if (NOISY_TEST == 1)
			printf("--Testing card %d..\n", i);
#endif

			G.supplyCount[i] = 0;
			i++;
		}

		if (assertTrue(isGameOver(&G), 1) == 0) {	//check that game is over

			failed++;
		}
	}

#if (NOISY_TEST == 1)
	printf("--Setting province pile to 0, expecting return 1\n");
#endif

	for (j = 0; j < 27; ++j) {	//ensure all cards have at least 1 card (not empty)

		G.supplyCount[j] = 1;
	}

	G.supplyCount[province] = 0;	//set province only to be empty

	if (assertTrue(isGameOver(&G), 1) == 0) {	//check that game is over

		failed++;
	}

	if (failed > 0) {		//report success or failures

		printf("\n*--------------- %d TESTS FAILED! ---------------*\n\n", failed);
	}
	else {
	
		printf("\n*--------------- ALL TESTS PASSED! ---------------*\n\n");
	}

        return 0;
}
