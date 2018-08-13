
/* -----------------------------------------------------------------------
 * Description: Random test for Adventurer Card.
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

#define TEST_CARD "Adventurer"

int testAdventurerCard(struct gameState *postGame, int handPos);

int main(int argc, char* argv[]) {
    int numTest = 50000;
    int i, k, player, passed = 0, failed = 0, handPos;
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
        player = game.whoseTurn;
        game.handCount[player] = floor(Random() * (MAX_HAND - 2));
        game.deckCount[player] = floor(Random() * (MAX_DECK / 2));
        game.discardCount[player] = floor(Random() * (MAX_DECK / 2));
        game.playedCardCount = floor(Random() * (MAX_HAND - 1));

        for (k = 0; k < game.deckCount[player]; k++) {
            game.deck[player][k] = floor(Random() * 100);
        }
        for (k = 0; k < game.discardCount[player]; k++) {
            game.discard[player][k] = floor(Random() * 100);
        }

        handPos = floor(Random() * game.handCount[game.whoseTurn]);

        // Carry out the test.
        if (testAdventurerCard(&game, handPos) == 0) {
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
int testAdventurerCard(struct gameState *postGame, int handPos) {
    struct gameState preGame;
    int i, card, count, cardDrawn, player;
    int choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int treasureFromDeck = 0, treasureDrawn = 0;

    memcpy(&preGame, postGame, sizeof(struct gameState));
    player = preGame.whoseTurn;

    // call function under test    
    cardEffect(adventurer, choice1, choice2, choice3, postGame, handPos, &bonus);

    // find out how many treasure card drawn from deck.
    for (i = 0; i < preGame.deckCount[player]; i++) {
        card =  preGame.deck[player][i];
        if (card == copper || card == silver || card == gold) {
            treasureFromDeck++;
            treasureDrawn++;
            if (treasureDrawn == 2) break;
        }
    }

    // If we have not drawn 2 treasure card, find out how many 
    // treasure cards can drawn from the discard pile.
    if (treasureDrawn < 2) {        
        for (i = 0; i < preGame.discardCount[player]; i++) {
            card =  preGame.discard[player][i];
            if (card == copper || card == silver || card == gold) {
                treasureDrawn++;
                if (treasureDrawn == 2) break;
            }
        }
    }

    // playedCards pile is affected.
    preGame.playedCards[preGame.playedCardCount] = preGame.hand[player][handPos];
    preGame.playedCardCount++;

    count = preGame.deckCount[player] + preGame.discardCount[player];
    memcpy(preGame.discard[player], postGame->discard[player], count * sizeof(int));
    memcpy(&(preGame.hand[player][preGame.handCount[player]]), 
            &(postGame->hand[player][preGame.handCount[player]]), 2 * sizeof(int));

    if (treasureDrawn == 0) {               // No treasure cards drawn                
        memcpy(preGame.deck[player], postGame->deck[player], count * sizeof(int));
        preGame.discardCount[player] += preGame.deckCount[player];
        preGame.deckCount[player] = 0;        
        return memcmp(&preGame, postGame, sizeof(struct gameState));
    }

    else if (treasureFromDeck == 2) {       // treasure cards drawn from deck only   
        cardDrawn = preGame.deckCount[player] - postGame->deckCount[player];        
        preGame.handCount[player] += 2;
        preGame.discardCount[player] += (cardDrawn - 2);
        preGame.deckCount[player] -= cardDrawn; 
        return memcmp(&preGame, postGame, sizeof(struct gameState));
    }
    
    // treasure cards drawn from both deck and discard pile.      
    memcpy(preGame.deck[player], postGame->deck[player], count * sizeof(int));        
    preGame.handCount[player] += treasureDrawn ;
    preGame.discardCount[player] += (preGame.deckCount[player] - postGame->deckCount[player] - treasureDrawn);
    preGame.deckCount[player] = postGame->deckCount[player];
    return memcmp(&preGame, postGame, sizeof(struct gameState));
}
