/********************************************************************************
** Cody Kelley
** CS362 - Winter 2018
**
** randomtestcard1.c
**
** Include the following lines in your makefile:
** 
** randomtestcard1: randomtestcard1.c dominion.o rngs.o
**      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
**
** This tests card: smithy
**
** Card effects: +3 cards
** Test for +3 cards, cards come from own pile, own piles updated with
** correct values (hand/deck/played), no state change for the
** other players, no state change for supply piles.
**
** Inputs: int i (loop counter), int current player (cp), struct valid gameState
** *s, and int handPos (hp).
********************************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//change NOISY_TEST, NOISY_ASSERTS, and NOISY_ERRORS to 0 to remove printfs
#define NOISY_TEST 0
#define NOISY_ASSERTS 0
#define NOISY_ERRORS 1

int assertTrue(const int a, const int b) {

        if (a == b) {

#if (NOISY_ASSERTS == 1)
                printf("PASSED!\n");
#endif

                return 1;
        }

#if (NOISY_ASSERTS == 1)
        printf("FAILED!\n");
#endif

        return 0;
}

int checkSmithy(int p, struct gameState *G) {

	int newCards = 3;
	int i = 0;
        int played = 1;
        int shuffled = 0;
        int currentPlayer = 0;
        int handPos = 0;
        int failed = 0;

        struct gameState preG;

	//copy gameState
	memcpy(&preG, G, sizeof(struct gameState));

	smithyEffect(i, currentPlayer, G, handPos);

	//check hand count
        if (assertTrue(G->handCount[currentPlayer], preG.handCount[currentPlayer] + newCards - played) == 0) {

                failed++;

#if (NOISY_ERRORS == 1)
	        printf("--Hand count = %d, expected = %d\n", G->handCount[currentPlayer], preG.handCount[currentPlayer] + newCards - played);
#endif

        }

	//check deck count
        if (assertTrue(G->deckCount[currentPlayer], preG.deckCount[currentPlayer] - newCards + shuffled) == 0) {

                failed++;

#if (NOISY_ERRORS == 1)
        	printf("--Deck count = %d, expected = %d\n", G->deckCount[currentPlayer], preG.deckCount[currentPlayer] - newCards + shuffled);
#endif

        }

	//check played card count
        if (assertTrue(G->playedCardCount, preG.playedCardCount + played) == 0) {

                failed++;

#if (NOISY_ERRORS == 1)
        	printf("--Played card count = %d, expected %d\n", G->playedCardCount, preG.playedCardCount + played);
#endif

        }

#if (NOISY_TEST == 1)
        printf("--Checking other players' states, no change should occur\n");
#endif

	for (i = 1; i < p; ++i) {

#if (NOISY_TEST == 1)
                printf("--Checking player %d\n", i + 1);
#endif

                if (assertTrue(preG.handCount[i], G->handCount[i]) == 0) {

                        failed++;

#if (NOISY_ERRORS == 1)
                        printf("--Hand count = %d, expected %d\n", G->handCount[i], preG.handCount[i]);
#endif

                }

                if (assertTrue(preG.deckCount[i], G->deckCount[i]) == 0) {

                        failed++;

#if (NOISY_ERRORS == 1)
                        printf("--Deck count = %d, expected %d\n", G->deckCount[i], preG.deckCount[i]);
#endif

                }

                if (assertTrue(preG.discardCount[i], G->discardCount[i]) == 0) {

                        failed++;

#if (NOISY_ERRORS == 1)
                        printf("--Discard count = %d, expected %d\n", G->discardCount[i], preG.discardCount[i]);
#endif
                }
        }

#if (NOISY_TEST == 1)
        printf("--Checking supply piles, no piles should change\n");
#endif

        for (i = 0; i < 27; ++i) {


                if (assertTrue(preG.supplyCount[i], G->supplyCount[i]) == 0) {

                        failed++;

#if (NOISY_ERRORS == 1)
			printf("--Card %d in supply file failed\n", i);
#endif
                }
        }

        if (failed > 0) {

                printf("\n*--------------- %d TESTS FAILED! ---------------*\n\n", failed);
        }
        else {

                printf("\n*--------------- ALL TESTS PASSED! ---------------*\n\n");
        }

	return failed;
}

int main() {

	int n, i, p;
	int numFailed = 0;
	int totalFailed = 0;

	struct gameState G;

	printf("\n*--------------- TESTING RANDOMTESTCARD1 - SMITHY ---------------*\n\n");

	SelectStream(2);
	PutSeed(3);

	for (n = 0; n < 1000; ++n) {   //run test n times

		printf("--Test #%d:\n", n + 1);

		p = floor((Random() * 2) + 2);   //generate random number of players

#if (NOISY_TEST == 1)
		printf("--Randomizing gameState..\n");
#endif

		for (i = 0; i < sizeof(struct gameState); ++i) {   //fill G with random bytes

			((char*)&G)[i] = floor(Random() * 256);
		}

#if (NOISY_TEST == 1)
		printf("--Randomizing each player's deck, hand, and discard counts..\n");
#endif

		for (i = 0; i < p; ++i) {  //set reasonable deck, hand, and discard count for each player

			G.deckCount[i] = floor(Random() * MAX_DECK);
			G.handCount[i] = floor(Random() * MAX_HAND);
			G.discardCount[i] = floor(Random() * MAX_DECK);
		}

		G.playedCardCount = 0;   //set playedCardCount to 0

#if (NOISY_TEST == 1)
		printf("--Randomizing supply counts..\n");
#endif

		for (i = 0; i < 27; ++i) {  //set reasonable supply counts

			G.supplyCount[i] = floor(Random() * MAX_DECK);
		}

#if (NOISY_TEST == 1)
		printf("--Calling smithy test..\n");
#endif

		//call test oracle
		numFailed = checkSmithy(p, &G);

		totalFailed += numFailed;
	}	

	if (totalFailed > 0) {

		printf("\n\n--Total number of failed tests: %d\n", totalFailed);
	}

	printf("*--------------- TESTING COMPLETED! ---------------*\n\n");

	return 0;
}
