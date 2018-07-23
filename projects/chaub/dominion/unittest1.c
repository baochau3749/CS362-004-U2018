
/* -----------------------------------------------------------------------
 * Description: Unit test for 
 *              drawCard(int player, struct gameState *state) function.
 *
 * Makefile's compile command:
 * unittest1: unittest1.c dominion.o rngs.o test_helpers.o
        gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
	    ./unittest1
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


void testDrawCard() {    
    char result[2000];
    int seed = 10;
    int testCard = silver;
    int currentPlayer, numPlayers = 2;
    int kingdomCards[10] = { adventurer, council_room, feast, gardens, mine, 
                              remodel, smithy, village, steward, treasure_map };
    struct gameState testGame, game;

    initializeGame(numPlayers, kingdomCards, seed, &game);      // initialize a new game
    currentPlayer = game.whoseTurn;                             // get current player
    
    printf("TESTING FUNCTION: drawCard(......)\n");    
    printf("==================================\n\n");   
    printf("drawCard(......) is called:\n");  

    // ********** Test #1 **************************************************
    // *** When a card is drawn, deck stack loses a card.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));         // copy game state for testing 

    // preset top card on deck to a known card.
    testGame.deck[currentPlayer][testGame.deckCount[currentPlayer] - 1] = testCard;

    drawCard(currentPlayer, &testGame);                         // call function under test
    
    if ((game.deckCount[currentPlayer] - 1) == testGame.deckCount[currentPlayer])
        strcpy(result, "   PASS - when player's deck loses a card.\n");           
    else 
        strcpy(result, " * FAIL - when player's deck does not lose a card.\n");          
      

    // ********** Test #2 **************************************************
    // *** When a card is drawn, player's hand gains a card.
    // *********************************************************************
    if ((game.handCount[currentPlayer] + 1) == testGame.handCount[currentPlayer])
        strcat(result, "   PASS - when player's hand gains a card.\n");           
    else 
        strcat(result, " * FAIL - when player's deck does not gain a card.\n");   


    // ********** Test #3 **************************************************
    // *** When the card on top of the deck is moved to the player's hand.
    // *********************************************************************
    if ((testGame.hand[currentPlayer][testGame.handCount[currentPlayer] - 1] == testCard))
        strcat(result, "   PASS - when player's hand receives card on top of his deck.\n");           
    else 
        strcat(result, " * FAIL - when player's hand does not receive card on top of his deck.\n");  


    // ********** Test #4 **************************************************
    // *** When deck is empty, discarded cards are shuffle into deck for 
    // *** drawing.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState)); // copy game state for testing   
    testGame.deckCount[currentPlayer] = 0;              // clear number of cards in deck
    testGame.discard[currentPlayer][0] = testCard;      // preset 3 cards in discard pile
    testGame.discard[currentPlayer][1] = testCard;
    testGame.discard[currentPlayer][2] = testCard;
    testGame.discardCount[currentPlayer] = 3;

    drawCard(currentPlayer, &testGame);                 // call function under test

    if (testGame.deckCount[currentPlayer] == 2)
        strcat(result, "   PASS - when deck is empty and discard cards are shuffled into deck.\n");           
    else 
        strcat(result, " * FAIL - when deck is empty and discard cards are shuffled into deck.\n");


    // ********** Test #5 **************************************************
    // *** When discarded cards are used, discardCount resets to zero.
    // *********************************************************************
    if (testGame.discardCount[currentPlayer] == 0)
        strcat(result, "   PASS - when discard cards are used, discardCount resets to zero.\n");           
    else 
        strcat(result, " * FAIL - when discard cards are used, discardCount resets to zero.\n"); 


    // ********** Test #6 **************************************************
    // *** When there are no cards to drawn, current hand gets no new cards.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing
    testGame.discardCount[currentPlayer] = 0;               // clear number of diccard cards
    testGame.deckCount[currentPlayer] = 0;                  // clear number of cards in deck

    int returnValue = drawCard(currentPlayer, &testGame);   // call function under test

    if (game.handCount[currentPlayer] == testGame.handCount[currentPlayer])
        strcat(result, "   PASS - when there are no cards to draw, current hand has same number of cards.\n");           
    else 
        strcat(result, " * FAIL - when there are no cards to draw, current hand does not has same number of cards.\n");           

    // ********** Test #7 **************************************************
    // *** When there are no cards to drawn, cardDraw function returns -1.
    // *********************************************************************
    if (returnValue == -1)
        strcat(result, "   PASS - when there are no cards to draw, cardDraw function returns -1.\n");           
    else 
        strcat(result, " * FAIL - when there are no cards to draw, cardDraw function does not returns -1.\n");           


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
    testDrawCard();
    return 0;
}
