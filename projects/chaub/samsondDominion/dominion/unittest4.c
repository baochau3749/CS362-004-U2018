
/* -----------------------------------------------------------------------
 * Description: Unit test for 
 *              updateCoins(int player, struct gameState *state, int bonus) function.
 *
 * Makefile's compile command:
 * unittest4: unittest4.c dominion.o rngs.o test_helpers.o
        gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
	    ./unittest4
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


void testUpdateCoins() {    
    char result[2000];
    int seed = 10;
    int bonus;
    int currentPlayer, numPlayers = 2;
    int kingdomCards[10] = { adventurer, council_room, feast, gardens, mine, 
                              remodel, smithy, village, steward, treasure_map };
    struct gameState testGame, game;

    initializeGame(numPlayers, kingdomCards, seed, &game);      // initialize a new game
    currentPlayer = game.whoseTurn;                             // get current player
    game.hand[currentPlayer][0] = estate;                       // preset values for tests.
    game.hand[currentPlayer][1] = estate;
    game.hand[currentPlayer][2] = estate;
    game.hand[currentPlayer][3] = estate;
    game.hand[currentPlayer][4] = estate;
    game.handCount[currentPlayer] = 5;
    bonus = 0;
    
    printf("TESTING FUNCTION: updateCoins(......)\n");    
    printf("=====================================\n\n");   
    printf("updateCoins(......) is called:\n");  


    // ********** Test #1 **************************************************
    // *** Function should be able to update copper treasure cards.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));         // copy game state for testing 
    testGame.hand[currentPlayer][0] = copper;                   // preset values for test.
    testGame.hand[currentPlayer][2] = copper;
    testGame.hand[currentPlayer][4] = copper;
    bonus = 0;

    updateCoins(currentPlayer, &testGame, bonus);               // call function under test

    if (testGame.coins == 3)
        strcpy(result, "   PASS - when copper treasure cards are updated correctly.\n");           
    else 
        strcpy(result, " * FAIL - when copper treasure cards are not updated correctly.\n");
    

    // ********** Test #2 **************************************************
    // *** Function should be able to update silver treasure cards.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));         // copy game state for testing 
    testGame.hand[currentPlayer][0] = silver;                   // preset values for test.
    testGame.hand[currentPlayer][2] = silver;
    testGame.hand[currentPlayer][4] = silver;
    bonus = 0;

    updateCoins(currentPlayer, &testGame, bonus);               // call function under test

    if (testGame.coins == 6)
        strcat(result, "   PASS - when silver treasure cards are updated correctly.\n");           
    else 
        strcat(result, " * FAIL - when silver treasure cards are not updated correctly.\n");


    // ********** Test #3 **************************************************
    // *** Function should be able to update gold treasure cards.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));         // copy game state for testing 
    testGame.hand[currentPlayer][0] = gold;                     // preset values for test.
    testGame.hand[currentPlayer][2] = gold;
    testGame.hand[currentPlayer][4] = gold;
    bonus = 0;

    updateCoins(currentPlayer, &testGame, bonus);               // call function under test

    if (testGame.coins == 9)
        strcat(result, "   PASS - when gold treasure cards are updated correctly.\n");           
    else 
        strcat(result, " * FAIL - when gold treasure cards are not updated correctly.\n");

    // ********** Test #4 **************************************************
    // *** Function should be able to update hand with different types of
    // *** treasure cards.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));         // copy game state for testing 
    testGame.hand[currentPlayer][0] = copper;                     // preset values for test.
    testGame.hand[currentPlayer][2] = silver;
    testGame.hand[currentPlayer][4] = gold;
    bonus = 0;

    updateCoins(currentPlayer, &testGame, bonus);               // call function under test

    if (testGame.coins == 6)
        strcat(result, "   PASS - when hand with different types of treasure cards is updated correctly.\n");           
    else 
        strcat(result, " * FAIL - when hand with different types of treasure cards is not updated correctly.\n");


    // ********** Test #5 **************************************************
    // *** Function should be able to update bonus value.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));         // copy game state for testing 
    bonus = 5;                                                  // preset values for test.
    
    updateCoins(currentPlayer, &testGame, bonus);               // call function under test

    if (testGame.coins == 5)
        strcat(result, "   PASS - when hand with only bonus value is updated correctly.\n");           
    else 
        strcat(result, " * FAIL - when hand with only bonus value is not updated correctly.\n"); 


    // ********** Test #6 **************************************************
    // *** Function should be able to update hand with no coin value.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));         // copy game state for testing 
    bonus = 0;                                                  // preset values for test.
    
    updateCoins(currentPlayer, &testGame, bonus);               // call function under test

    if (testGame.coins == 0)
        strcat(result, "   PASS - when hand with no coin value is updated correctly.\n");           
    else 
        strcat(result, " * FAIL - when hand with no coin value is not updated correctly.\n"); 


    // Get test's overall result.
    if (strstr(result, "FAIL")) 
        strcat(result, "   TEST FAILED\n\n"); 
    else
        strcat(result, "   TEST SUCCESSFULLY COMPLETED\n\n"); 

    // print test result.
    printf("%s", result);

    return ;
}

int main() {
    testUpdateCoins();
    return 0;
}