/******************************************************************************
** Cody Kelley
** CS362 - Winter 2018
**
** unittest4.c
**
** Include the following lines in your makefile:
**
** unittest4: unittest4.c dominion.o rngs.o
**      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
**
** This unit test evaluates:
** int fullDeckCount(int player, int card, struct gameState* state) which
** returns the number of a specified card in a specified player's deck,
** hand, and discard pile.
**
** It accepts a player, card, and valid gameState as parameters.  It sets up
** a gameState and systematically evaluates increasing amounts of cards in
** hand, discard, and deck piles to see if fullDeckCount() returns the right
** number of a specific card.  All cards are tested for max players.
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

	int p, c;
	int i, j, k;
	int failed = 0;		//how many tests failed
        int numPlayers = 4;
	struct gameState G;

        printf("\n*--------------- TESTING UNITTEST4 - fullDeckCount() ---------------*\n\n");

	int maxDeckCount = 5;
	int maxHandCount = 5;
	int maxDiscardCount = 5;

	for (p = 0; p < numPlayers; ++p) {	//loop for each player

		G.deckCount[p] = 0;
		G.handCount[p] = 0;
		G.discardCount[p] = 0;

#if (NOISY_TEST == 1)
		printf("--Checking player %d..\n", p + 1);
#endif

		for (c = 0; c < 27; ++c) {	//loop for each card

#if (NOISY_TEST == 1)
			printf("--Checking card %d..\n", c);
#endif
			k = 0;		//set loop variable

			while (k <= maxHandCount) {	//loop for hand size 0-5

#if (NOISY_TEST == 1)
				printf("--Testing hand pile size %d\n", k);
#endif

				j = 0;		//set loop variable

				G.hand[p][k] = c;
				G.handCount[p]++;
				k++;

				while (j <= maxDiscardCount) {	//loop for discard size 0-5

#if (NOISY_TEST == 1)
					printf("--Testing discard pile size %d\n", j);
#endif

					i = 0;		//set loop variable

					G.discard[p][j] = c;
					G.discardCount[p]++;
					j++;

					while (i <= maxDeckCount) {	//loop for deck size 0-5

#if (NOISY_TEST == 1)
						printf("--Testing deck count pile size %d\n", i);
#endif

						G.deck[p][i] = c;
						G.deckCount[p]++;
						i++;
						if (assertTrue(fullDeckCount(p, c, &G), i + j + k) == 0) {

							failed++;
						}
					}

					G.deckCount[p] = 0;	//reset deck count
				}

				G.discardCount[p] = 0;	//reset discard count
			}
		}
	}

	if (failed > 0) {

		printf("\n*--------------- %d TESTS FAILED! ---------------*\n\n", failed);
	}
	else {

		printf("\n*--------------- ALL TESTS PASSED! ---------------*\n\n");
	}

	return 0;
}
