/*************************************************************************
** Cody Kelley
** CS362 - Winter 2018
**
** cardtest2.c
**
** Include the following lines in your makefile:
**
** cardtest2: cardtest2.c dominion.o rngs.o
**      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
**
** This test card: adventurer
**
** Card effects: Dig through deck until 2 treasure cards are revealed.
** All other revealed cards are set aside and discarded at the end.
** If deck is empty, shuffle discard pile (does not include already
** revealed cards) and continuing drawing.  If discard and deck pile
** become empty, turn ends.
** Test for 2 treasure cards to be drawn, must be drawn from own pile,
** check for correct ending state of own piles (hand, deck, played),
** no changes should occur in state of other players.
*************************************************************************/

#include <stdio.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//change NOISY_TEST to 0 to remove printfs
#define NOISY_TEST 1

int assertTrue(const int a, const int b) {

        if (a == b) {

#if (NOISY_TEST == 1)
                printf("PASSED!\n");
#endif

                return 1;
        }

#if (NOISY_TEST == 1)
        printf("FAILED!\n");
#endif

        return 0;
}

int main() {

	int failed = 0;
	int seed = 1000;
	int numPlayers = 4;
	int currentPlayer = 0;
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	struct gameState G, testG;
	//int cardDrawn = 0;
	int drawnTreasure = 0;
	//int tempHand[MAX_HAND];
	int i = 0;

	printf("\n*--------------- TESTING CARDTEST2 - ADVENTURER ---------------*\n\n");

	initializeGame(numPlayers, k, seed, &G);	//initialize new game
	memcpy(&testG, &G, sizeof(struct gameState));	//copy state into test game

	//manually setting up hand, discard, and deck piles
	testG.deckCount[currentPlayer] = 10;
	testG.discardCount[currentPlayer] = 0;
	testG.handCount[currentPlayer] = 5;

	testG.deck[currentPlayer][0] = copper;
	testG.deck[currentPlayer][1] = gold;
	testG.deck[currentPlayer][2] = silver;
	testG.deck[currentPlayer][3] = silver;
	testG.deck[currentPlayer][4] = mine;
	testG.deck[currentPlayer][5] = silver;
	testG.deck[currentPlayer][6] = province;
	testG.deck[currentPlayer][7] = copper;
	testG.deck[currentPlayer][8] = estate;
	testG.deck[currentPlayer][9] = smithy;

	for (i = 0; i < testG.handCount[currentPlayer]; ++i) {	//set hand to all estate

		testG.hand[currentPlayer][i] = estate;
	}

	//adventurerEffect(drawnTreasure, &testG, currentPlayer, &tempHand, cardDrawn, i);
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);

	for (i = 0; i < testG.handCount[currentPlayer]; ++i) {

		if (testG.hand[currentPlayer][i] == copper || testG.hand[currentPlayer][i] == silver || testG.hand[currentPlayer][i] == gold) {

			drawnTreasure++;
		}
	}


#if (NOISY_TEST == 1)
	printf("--Drawn treasure = %d, expected 2\n", drawnTreasure);
#endif

	if (assertTrue(drawnTreasure, 2) == 0) {

		failed++;
	}

#if (NOISY_TEST == 1)
	printf("--Deck count = %d, expected 5\n", testG.deckCount[currentPlayer]);
#endif

	if (assertTrue(testG.deckCount[currentPlayer], 5) == 0) {

		failed++;
	}


#if (NOISY_TEST == 1)
	printf("--Played card count = %d, expected 1\n", testG.playedCardCount);
#endif

	if (assertTrue(testG.playedCardCount, 1) == 0) {

		failed++;
	}

#if (NOISY_TEST == 1)
	printf("--Hand count = %d, expected 7\n", testG.handCount[currentPlayer]);
#endif

	if (assertTrue(testG.handCount[currentPlayer], 7) == 0) {

		failed++;
	}

#if (NOISY_TEST == 1)
        printf("--Checking other players' states, no change should occur\n");
#endif

        for (i = 1; i < numPlayers; ++i) {      //player 0 is current, check others

#if (NOISY_TEST == 1)
                printf("--Checking player %d\n", i + 1);
#endif

                if (assertTrue(testG.handCount[i], G.handCount[i]) == 0) {

                        failed++;
                }

                if (assertTrue(testG.deckCount[i], G.deckCount[i]) == 0) {

                        failed++;
                }

                if (assertTrue(testG.discardCount[i], G.discardCount[i]) == 0) {

                        failed++;
                }
        }

#if (NOISY_TEST == 1)
        printf("--Check supply piles, no piles should change\n");
#endif

        for (i = 0; i < 27; ++i) {

#if (NOISY_TEST == 1)
                printf("--Checking card %d..\n", i);
#endif

                if (assertTrue(testG.supplyCount[i], G.supplyCount[i]) == 0) {

                        failed++;
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

