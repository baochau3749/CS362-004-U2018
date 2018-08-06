
/* -----------------------------------------------------------------------
 * Description: Random test for Remodel card.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

#define TEST_CARD "Remodel"

int testRemodelCard(int choice1, int choice2, struct gameState *state, int handPos);

int main(int argc, char* argv[]) {    
    int numTest = 50000;
    int i, k, player, passed = 0, failed = 0;
    int seed = 10, printCount = 0;
    struct gameState game;
    int handPos, choice1, choice2;

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

        player = game.whoseTurn;
        game.discardCount[player] = floor(Random() * (MAX_DECK - 1));
        game.handCount[player] = floor(Random() * (MAX_HAND - 2)) + 2;

        for (k = 0; k < game.handCount[player]; k++) {
            game.hand[player][k] = floor(Random() * (treasure_map + 1));                
        }   

        choice1 = floor(Random() * game.handCount[player]);
        choice2 = floor(Random() * (treasure_map + 1));
        game.supplyCount[choice2] = floor(Random() * 100) + 1;

        handPos = floor(Random() * game.handCount[player]);    
        if (handPos == choice1) {
            handPos = (handPos != 0) ? 0 : 1;
        }

        // Carry out the test.
        if (testRemodelCard(choice1, choice2, &game, handPos) == 0) {
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

// call the function under test and check result.
int testRemodelCard(int choice1, int choice2, struct gameState *postGame, int handPos) {
    struct gameState preGame;
    int choice3 = 0, bonus = 0;
    int outValue, inValue, player;
    
    // Copy initial game state.
    memcpy(&preGame, postGame, sizeof(struct gameState));
    player = preGame.whoseTurn;


    // call function under test.
    int result = cardEffect(remodel, choice1, choice2, choice3, postGame, handPos, &bonus);

    outValue = getCost(preGame.hand[player][choice1]);  // value of card to be discard.
    inValue = getCost(choice2);                         // value of card to be gain.
    
    if ((outValue + 2) > inValue) {   // inValue is too high. Invalid case. No changes to game state.
        if ((memcmp(&preGame, postGame, sizeof(struct gameState)) != 0) || (result != -1)) {
            return -1;
        }        
    }
    else {        
        // create expected result.
        preGame.discard[player][preGame.discardCount[player]] = choice2;
        preGame.discardCount[player]++;
        preGame.supplyCount[choice2]--;

        preGame.playedCards[preGame.playedCardCount] = preGame.hand[player][handPos];
        preGame.playedCardCount++;

        memcpy(preGame.hand[player], postGame->hand[player], preGame.handCount[player] * sizeof(int));
        preGame.handCount[player] -= 2;                    

        // compare game state and return result.
        if (memcmp(&preGame, postGame, sizeof(struct gameState)) != 0) {
            return -1;
        }  
    }

    return 0;
}


