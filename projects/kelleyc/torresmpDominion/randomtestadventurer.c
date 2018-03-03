/*****************************************************************************************
** Cody Kelley
** CS362 - Winter 2018
**
** randomtestadventurer.c
**
** Include the following lines in your makefile:
**
** randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
**      gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
**
** This tests card: adventurer
**
** Card effects: Dig through deck until 2 treasure cards are revealed.
** All other revealed cards are set aside and discarded at the end.
** If deck is empty, shuffle discard pile (does not include already
** revealed cards) and continuing drawing.  If discard and deck pile
** become empty, turn ends.
** Test for 2 treasure cards to be drawn, must be drawn from own pile, check for
** correct ending state of own piles, no changes should occur in state of other
** players, and supply piles should not change.
**
** Inputs: int drawn treasure (dt), struct valid gameState *s,
** int current player (cp), int *th, int z (loop variable).
**
** Note: Function had to be modified to work with teammate's code.  Parameters
** and set-up were slightly different so were modified accordingly.  The
** player turn had to be initialized in the set-up.
**
** New inputs: struct valid gameState *state and int* tempHand.
******************************************************************************************/

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

int checkAdventurer(int p, struct gameState *G) {

	int i = 0;
	//int z = 0;
	int drawnTreasure = 0;
	int currentPlayer = 0;
	int tempHand[MAX_HAND];
	//int cardDrawn = -1;
	int failed = 0;

	struct gameState preG;

	//copy game state
	memcpy(&preG, G, sizeof(struct gameState));

	//clear tempHand
	for (i = 0; i < MAX_HAND; ++i) {

		tempHand[i] = -1;
	}

        //adventurerEffect(drawnTreasure, G, currentPlayer, tempHand, cardDrawn, z);
	adventurerCard(G, tempHand);

	for (i = 0; i < G->handCount[currentPlayer]; ++i) {

		if (G->hand[currentPlayer][i] == copper || G->hand[currentPlayer][i] == silver || G->hand[currentPlayer][i] == gold) {

			drawnTreasure++;
		}
	}

	//check number of drawn treasures
	if (assertTrue(drawnTreasure, 2) == 0) {

		failed++;

#if (NOISY_ERRORS == 1)
		printf("--Drawn treasure = %d, expected 2\n", drawnTreasure);
#endif
	}

	//check cards played
	if (assertTrue(G->playedCardCount, 1) == 0) {

		failed++;

#if (NOISY_ERRORS == 1)
		printf("--Played card count = %d, expected 1\n", G->playedCardCount);
#endif
	}

	//check hand count
	if (assertTrue(G->handCount[currentPlayer], preG.handCount[currentPlayer] + 2) == 0) {

		failed++;

#if (NOISY_ERRORS == 1)
		printf("--Hand count = %d, expected %d\n", G->handCount[currentPlayer], preG.handCount[currentPlayer] + 2);
#endif
	}

#if (NOISY_TEST == 1)
        printf("--Checking other players' states, no change should occur\n");
#endif

	//check other players, no state should change
	for (i = 1; i < p; ++i) {      //player 0 is current, check others

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
			printf("--Card %d in supply pile failed..\n", i);
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

	int n, i, j, p;
	int numFailed = 0;
	int totalFailed = 0;

        struct gameState G;

        printf("\n*--------------- TESTING RANDOMTESTADVENTURER - ADVENTURER ---------------*\n\n");

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

			for (j = 0; j < G.deckCount[i]; ++j) {   //set random deck pile

				G.deck[i][j] = floor(Random() * 26);
			}

			for (j = 0; j < G.handCount[i]; ++j) {   //set hand to all estate

				G.hand[i][j] = estate;
			}

			for (j = 0; j < G.discardCount[i]; ++j) {   //set random discard pile

				G.discard[i][j] = floor(Random() * 26);
			}
                }

                G.playedCardCount = 0;   //set playedCardCount to 0
		G.whoseTurn = 0;   //set turn to player 0

#if (NOISY_TEST == 1)
                printf("--Randomizing supply counts..\n");
#endif

                for (i = 0; i < 27; ++i) {  //set reasonable supply counts

			G.supplyCount[i] = floor(Random() * MAX_DECK);
                }

#if (NOISY_TEST == 1)
                printf("--Calling adventurer test..\n");
#endif

		//call test oracle
		numFailed = checkAdventurer(p, &G);

		totalFailed += numFailed;
	}

	if (totalFailed > 0) {

		printf("\n\n--Total number of failed tests: %d\n", totalFailed);
	}

        printf("\n*--------------- TESTING COMPLETED! ---------------*\n\n"); 

	return 0;
}
