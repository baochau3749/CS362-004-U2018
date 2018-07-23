
#include "test_helpers.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


int compareKingdomCards(struct gameState *expectedGame, struct gameState *testGame) {
    int i;    
    for (i = 0; i <= treasure_map; i++) {
        if (expectedGame->supplyCount[i] > testGame->supplyCount[i]) return 1;
        if (expectedGame->supplyCount[i] < testGame->supplyCount[i]) return -1;
    }
    return 0;
}

int compareOtherPlayers(struct gameState *expectedGame, struct gameState *testGame, int curPlayer) {
    int p, k;    
    for (p = 0; p < MAX_PLAYERS; p++) {
        if (p != curPlayer) {
            // Compare cards on hand.
            if (expectedGame->handCount[p] > testGame->handCount[p]) return 1;
            if (expectedGame->handCount[p] < testGame->handCount[p]) return -1;
            
            for (k = 0; k < expectedGame->handCount[p]; k++) {
                if (expectedGame->hand[p][k] > testGame->hand[p][k]) return 1;
                if (expectedGame->hand[p][k] < testGame->hand[p][k]) return -1;
            }

            // Compare cards in deck.
            if (expectedGame->deckCount[p] > testGame->deckCount[p]) return 1;
            if (expectedGame->deckCount[p] < testGame->deckCount[p]) return -1;
            
            for (k = 0; k < expectedGame->deckCount[p]; k++) {
                if (expectedGame->deck[p][k] > testGame->deck[p][k]) return 1;
                if (expectedGame->deck[p][k] < testGame->deck[p][k]) return -1;
            }
           
            // Compare cards in discard stacks;
            if (expectedGame->discardCount[p] > testGame->discardCount[p]) return 1;
            if (expectedGame->discardCount[p] < testGame->discardCount[p]) return -1;
            
            for (k = 0; k < expectedGame->discardCount[p]; k++) {
                if (expectedGame->discard[p][k] > testGame->discard[p][k]) return 1;
                if (expectedGame->discard[p][k] < testGame->discard[p][k]) return -1;
            }
        }
    }
    return 0;
}

