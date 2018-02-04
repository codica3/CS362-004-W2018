/******************************************************************************
** Cody Kelley
** CS362 - Winter 2018
**
** unittest3.c
**
** Include the following lines in your makefile:
**
** unittest3: unittest3.c dominion.o rngs.o
**      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
**
** This unit test evaluates:
** int getCost(int card) which returns the cost of the card.  If there is
** no matching card, it returns -1.
**
** It takes a card as a parameter.  It uses the official game rules costs to
** set up an array that corresponds in index number to that card (enum
** value).  It then loops through all cards and confirms that getCost() is
** returning the correct cost of the card.  Finally, it checks that the
** return value for a non-existent card is -1.
******************************************************************************/

#include <stdio.h>
#include <string.h>
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

	int i;
	int failed = 0;		//how many tests failed

	//array to hold costs of each enum card
	int cost[27] = { 0, 2, 5, 8, 0, 3, 6, 6, 5, 4, 4, 5, 4, 4,
			3, 4, 3, 5, 3, 5, 3, 4, 2, 5, 4, 4, 4 };

	printf("\n*--------------- TESTING UNITTEST3 - getCost() ---------------*\n\n");

	for (i = 0; i < 27; ++i) {	//check each card's cost

#if (NOISY_TEST == 1)
		printf("--Getting cost for card %d, expecting cost to be %d\n", i, cost[i]);
#endif
		if (assertTrue(getCost(i), cost[i]) == 0) {

			failed++;
		}
	}

#if (NOISY_TEST == 1)
	printf("--Checking for non-existent card 27..\n");
#endif

	if (assertTrue(getCost(27), -1) == 0) {	//check that a no match returns -1

		failed++;
	}

	if (failed > 0) {

		printf("\n*--------------- %d TESTS FAILED! ---------------*\n\n", failed);
	}
	else {

		printf("\n*--------------- ALL TESTS PASSED! ---------------*\n\n");
	}

	return 0;
}
