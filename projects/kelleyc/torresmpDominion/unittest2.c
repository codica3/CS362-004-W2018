/******************************************************************************
** Cody Kelley
** CS362 - Winter 2018
**
** unittest2.c
**
** Include the following lines in your makefile:
**
** unittest2: unittest2.c dominion.o rngs.o
**      gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
**
** This unit test evaluates:
** int supplyCount(int card, struct gameState* state) which returns the
** supply of a card.
**
** It accepts a card and a valid gameState as parameters.  It sets up a
** gameState and then it sets the maximum amount + 1 in the supply pile
** for each card (based on rules of the game) and decreases the amount
** until there are -1 cards in the pile, each time checking for supplyCount()
** to return the correct value.  Max values were determined by documentation
** provided in week 2 module.  Test checks for two out-of-bounds values as
** well: -1 and max + 1.
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
	struct gameState G;

	printf("\n*--------------- TESTING UNITTEST2 - supplyCount() ---------------*\n\n");

	//set supply counts to max + 1
	G.supplyCount[curse] = 30 + 1;
	G.supplyCount[estate] = 12 + 1;
	G.supplyCount[duchy] = 12 + 1;
	G.supplyCount[province] = 12 + 1;
	G.supplyCount[copper] = 46 + 1;		//60-(7*numPlayers); min numPlayers = 2
	G.supplyCount[silver] = 40;
	G.supplyCount[gold] = 30;
	G.supplyCount[adventurer] = 10 + 1;
	G.supplyCount[council_room] = 10 + 1;
	G.supplyCount[feast] = 10 + 1;
	G.supplyCount[gardens] = 12 + 1;	//victory kingdom card
	G.supplyCount[mine] = 10 + 1;
	G.supplyCount[remodel] = 10 + 1;
	G.supplyCount[smithy] = 10 + 1;
	G.supplyCount[village] = 10 + 1;
	G.supplyCount[baron] = 10 + 1;
	G.supplyCount[great_hall] = 12 + 1;	//victory kingdom card
	G.supplyCount[minion] = 10 + 1;
	G.supplyCount[steward] = 10 + 1;
	G.supplyCount[tribute] = 10 + 1;
	G.supplyCount[ambassador] = 10 + 1;
	G.supplyCount[cutpurse] = 10 + 1;
	G.supplyCount[embargo] = 10 + 1;
	G.supplyCount[outpost] = 10 + 1;
	G.supplyCount[salvager] = 10 + 1;
	G.supplyCount[sea_hag] = 10 + 1;
	G.supplyCount[treasure_map] = 10 + 1;

#if (NOISY_TEST == 1)
	printf("--Testing each supply pile..\n");
#endif

	for (i = 0; i < 27; ++i) {	//loop through each card

#if (NOISY_TEST == 1)
	printf("--Checking card %d..\n", i);
#endif

		while (G.supplyCount[i] >= -1) {	//decrement pile

			if (assertTrue(supplyCount(i, &G), G.supplyCount[i]) == 0) {

				failed++;
			}

			G.supplyCount[i]--;
		}
	}

	//assert(memcmp(&pre, &G, sizeof(struct gameState)) == 0);	//check game state hasn't changed

	if (failed > 0) {

		printf("\n*--------------- %d TESTS FAILED! ---------------*\n\n", failed);
	}
	else {

		printf("\n*--------------- ALL TESTS PASSED! ---------------*\n\n");
	}

	return 0;
}
