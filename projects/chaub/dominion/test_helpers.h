
#include "dominion.h"
#include "dominion_helpers.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int compareKingdomCards(struct gameState *expectedGame, struct gameState *testGame);
int compareOtherPlayers(struct gameState *expectedGame, struct gameState *testGame, int curPlayer);