
/* -----------------------------------------------------------------------
 * Description: Unit test for: int discardCard(int handPos, 
 *              int currentPlayer, struct gameState *state, int trashFlag).
 *
 * Makefile's compile command:
 * unittest3: unittest3.c dominion.o rngs.o test_helpers.o
        gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
	    ./unittest3
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


void testDiscardCard() {    
    char result[2000];
    int seed = 10;
    int handPos = 0, trashFlag = 0;
    int currentPlayer, numPlayers = 2;
    int kingdomCards[10] = { adventurer, council_room, feast, gardens, mine, 
                              remodel, smithy, village, steward, treasure_map };
    struct gameState testGame, game;

    initializeGame(numPlayers, kingdomCards, seed, &game);      // initialize a new game
    currentPlayer = game.whoseTurn;                             // get current player
    game.hand[currentPlayer][0] = gold;                         // preset values for tests.
    game.hand[currentPlayer][1] = silver;
    game.hand[currentPlayer][2] = gold;
    game.handCount[currentPlayer] = 3;

    printf("TESTING FUNCTION: discardCard(......)\n");    
    printf("=====================================\n\n");   
    printf("discardCard(......) is called:\n");  

    // ********** Test #1 **************************************************
    // *** When trashFlag = 0, the chosen card goes into the played card
    // *** area.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing
    handPos = 0;                                             // preset values for test
    trashFlag = 0;

    // call function under test
    discardCard(handPos, currentPlayer, &testGame, trashFlag);

    if (((game.playedCardCount + 1) == testGame.playedCardCount) && 
        (testGame.playedCards[testGame.playedCardCount - 1] == gold))
        strcpy(result, "   PASS - when trashFlag = 0, the chosen card is sent to played cards area.\n");           
    else 
        strcpy(result, " * FAIL - when trashFlag = 0, the chosen card is not sent to played cards area.\n");   


    // ********** Test #2 **************************************************
    // *** When trashFlag = 1, the chosen card is trashed.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing
    handPos = 0;                                             // preset values for test
    trashFlag = 1;

    // call function under test
    discardCard(handPos, currentPlayer, &testGame, trashFlag);

    if (game.playedCardCount == testGame.playedCardCount)
        strcat(result, "   PASS - when trashFlag = 1, the chosen card is trashed.\n");           
    else 
        strcat(result, " * FAIL - when trashFlag = 1, the chosen card is not trashed.\n");     


    // ********** Test #3 **************************************************
    // *** The player's current hand should lose a card.
    // *********************************************************************
    if ((game.handCount[currentPlayer] - 1) == testGame.handCount[currentPlayer])
        strcat(result, "   PASS - when player's hand loses a card.\n");           
    else 
        strcat(result, " * FAIL - when player's hand does not lose a card.\n");   


    // ********** Test #4 **************************************************
    // *** If there is only one card available, player's hand should 
    // *** becomes empty.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing
    testGame.handCount[currentPlayer] = 1;                   // preset values for test
    handPos = 0;
    trashFlag = 0;

    // call function under test
    discardCard(handPos, currentPlayer, &testGame, trashFlag);

    if (testGame.handCount[currentPlayer] == 0)
        strcat(result, "   PASS - when there was only one card in hand, player's hand becomes empty.\n");           
    else 
        strcat(result, " * FAIL - when there was only one card in hand, player's hand is not empty.\n");  


    // ********** Test #5 **************************************************
    // *** Function should correctly discard the first card in hand.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing
    testGame.handCount[currentPlayer] = 2;                   // preset values for test
    handPos = 0;
    trashFlag = 0;

    // call function under test
    discardCard(handPos, currentPlayer, &testGame, trashFlag);

    if ((testGame.handCount[currentPlayer] == 1) && (testGame.hand[currentPlayer][0] == silver))
        strcat(result, "   PASS - when correctly discard the first card in hand.\n");           
    else 
        strcat(result, " * FAIL - when unable to correctly discard the first card in hand.\n");    


    // ********** Test #6 **************************************************
    // *** Function should correctly discard the last card in hand
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing
    testGame.handCount[currentPlayer] = 2;                   // preset values for test
    handPos = 1;
    trashFlag = 0;

    // call function under test
    discardCard(handPos, currentPlayer, &testGame, trashFlag);

    if ((testGame.handCount[currentPlayer] == 1) && (testGame.hand[currentPlayer][0] == gold))
        strcat(result, "   PASS - when correctly discard the last card in hand.\n");           
    else 
        strcat(result, " * FAIL - when unable to correctly discard the last card in hand.\n");     

    // ********** Test #7 **************************************************
    // *** Function should correctly discard the a middle card in hand
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing
    testGame.handCount[currentPlayer] = 3;                   // preset values for test
    handPos = 1;
    trashFlag = 0;

    // call function under test
    discardCard(handPos, currentPlayer, &testGame, trashFlag);

    if ((testGame.handCount[currentPlayer] == 2) && 
        (testGame.hand[currentPlayer][0] == gold) && (testGame.hand[currentPlayer][1] == gold))
        strcat(result, "   PASS - when correctly discard a middle card in hand.\n");           
    else 
        strcat(result, " * FAIL - when unable to correctly discard a middle card in hand.\n"); 
    

    // ********** Test #8 **************************************************
    // *** Player's deck pile should not be affected.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing    
    handPos = 0;                                            // preset values for test
    trashFlag = 0;
    testGame.deck[currentPlayer][0] = estate;
    testGame.deckCount[currentPlayer] = 1;
    testGame.discard[currentPlayer][0] = estate;   
    testGame.discardCount[currentPlayer] = 1;

    // call function under test
    discardCard(handPos, currentPlayer, &testGame, trashFlag);

    if ((testGame.deckCount[currentPlayer] == 1) && (testGame.deck[currentPlayer][0] == estate))
        strcat(result, "   PASS - when player's deck pile is not affected.\n");           
    else 
        strcat(result, " * FAIL - when player's deck pile is affected.\n");           

    // ********** Test #9 **************************************************
    // *** Player's discard pile should not be affected.
    // *********************************************************************
    if ((testGame.discardCount[currentPlayer] == 1) && (testGame.discard[currentPlayer][0] == estate))
        strcat(result, "   PASS - when player's discard pile is not affected.\n");           
    else 
        strcat(result, " * FAIL - when player's discard pile is affected.\n");     


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
    testDiscardCard();
    return 0;
}