
/* -----------------------------------------------------------------------
 * Description: Random test for Council Room card.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

#define TEST_CARD "Council Room"

int testCouncilRoomCard(struct gameState *state, int handPos);

int main(int argc, char* argv[]) {
    int numTest = 50000;
    int i, k, handPos, passed = 0, failed = 0;
    int seed = 10, printCount = 0;
    struct gameState game;

    PutSeed(seed);
    printf("\n\nRandom test for %s card:\n", TEST_CARD);

    for (i = 0; i < numTest; i++) {
        // Setup random game state.
        for (k = 0; k < sizeof(struct gameState); k++) {
            ((char*)&game)[k] = floor(Random() * 256);
        }
        game.numPlayers = floor(Random() * (MAX_PLAYERS - 1)) + 2;

        game.whoseTurn =  floor(Random() * game.numPlayers);        
        game.playedCardCount = floor(Random() * (MAX_DECK - 1));

        for (k = 0; k < game.numPlayers; k++)
        {
            game.handCount[k] = floor(Random() * (MAX_HAND - 4)) + 1;
            game.deckCount[k] = floor(Random() * MAX_DECK);
            game.discardCount[k] = floor(Random() * MAX_DECK);
        }

        handPos = floor(Random() * game.handCount[game.whoseTurn]);
        
        // Carry out the test.
        if (testCouncilRoomCard(&game, handPos) == 0) {
            passed++;
        }
        else {
            failed++;
            if (printCount <= 100) {                
                printCount++;      
                if (printCount > 100) {
                    printf("\tFor this assignment's purpose, only ");
                    printf("100 failing messages are display.\n");
                }
                else
                    printf("\ttest #%d = %s Card failed.\n", i, TEST_CARD);
            }
        }
    }

    printf("Number of test: %d\n", numTest);
    printf("Number of test passed: %d\n", passed);
    printf("Number of test failed: %d\n\n", failed);
    return 0;
}

// create affect to game state when cards are drawn.
void drawCardEffect(struct gameState *preGame, struct gameState *postGame, int player, int numCard) {    
    int i;
    for (i = 0; i < numCard; i++) {
        if ((preGame->deckCount[player] <= 0) && (preGame->discardCount[player] > 0)) {
            memcpy(preGame->deck[player], postGame->deck[player], preGame->discardCount[player] * sizeof(int));
            memcpy(preGame->discard[player], postGame->discard[player], preGame->discardCount[player] * sizeof(int));
            preGame->deckCount[player] = preGame->discardCount[player];
            preGame->discardCount[player] = 0;        
        }
        
        if (preGame->deckCount[player] > 0) {
            preGame->deckCount[player]--;
            preGame->hand[player][preGame->handCount[player]] = preGame->deck[player][preGame->deckCount[player]];
            preGame->handCount[player]++;
        }
    }  
}

// call the function under test and check result.
int testCouncilRoomCard(struct gameState *postGame, int handPos) {        
    struct gameState preGame;
    int i, player;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    
    // Copy initial game state.
    memcpy(&preGame, postGame, sizeof(struct gameState));
    player = preGame.whoseTurn;

    // call function under test    
    cardEffect(council_room, choice1, choice2, choice3, postGame, handPos, &bonus);

    // numBuys should increase by 1.
    preGame.numBuys++;

    // Some cards are drawn.
    for (i = 0; i < preGame.numPlayers; i++) {        
        if (i == player) 
            drawCardEffect(&preGame, postGame, i, 4);            
        else 
            drawCardEffect(&preGame, postGame, i, 1);                    
    }

    // playedCards pile is affected.
    preGame.playedCards[preGame.playedCardCount] = preGame.hand[player][handPos];
    preGame.playedCardCount++;

    // player's hand is affected.
    memcpy(preGame.hand[player], postGame->hand[player], preGame.handCount[player] * sizeof(int));
    preGame.handCount[player]--;    

    // compare game state and return result.
    return memcmp(&preGame, postGame, sizeof(struct gameState));
}
