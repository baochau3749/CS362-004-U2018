/* -----------------------------------------------------------------------
 * Description: Unit test for 
 *      int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
 *      function.
 *
 * Makefile's compile command:
 * unittest2: unittest2.c dominion.o rngs.o test_helpers.o
        gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
	    ./unittest2
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void testGainCard() {    
    char result[2000];
    int returnValue;
    int seed = 10;
    int chosenCard = gardens;
    int currentPlayer, numPlayers = 2;
    int kingdomCards[10] = { adventurer, council_room, feast, gardens, mine, 
                              remodel, smithy, village, steward, treasure_map };
    struct gameState testGame, game;

    initializeGame(numPlayers, kingdomCards, seed, &game);      // initialize a new game
    currentPlayer = game.whoseTurn;                             // get current player
    
    printf("TESTING FUNCTION: gainCard(......)\n");    
    printf("==================================\n\n");   
    printf("gainCard(......) is called:\n");  
      

    // ********** Test #1 **************************************************
    // *** when supply pile for the chosen card is empty, function should
    // *** return -1.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState)); // copy game state for testing
    testGame.supplyCount[chosenCard] = 0;              // clear supply pile for the chosen card

    // call function under test
    returnValue = gainCard(chosenCard, &testGame, 0, currentPlayer);

    if (returnValue == -1)
        strcpy(result, "   PASS - when supply pile is empty, gainCard function returns -1.\n");           
    else 
        strcpy(result, " * FAIL - when supply pile is empty, gainCard function does not returns -1.\n");            


    // ********** Test #2 **************************************************
    // *** when supply pile for the chosen card is empty, player does not  
    // *** gain/lose any new card.
    // *********************************************************************
    if (game.discardCount[currentPlayer] == testGame.discardCount[currentPlayer])
        strcat(result, "   PASS - when supply pile is empty, player has same number of cards.\n");           
    else 
        strcat(result, " * FAIL - when supply pile is empty, player does not has same number of cards.\n");           



    // ********** Test #3 **************************************************
    // *** when gain to discard, discard pile receives the choosen card.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing

    // call function under test
    returnValue = gainCard(chosenCard, &testGame, 0, currentPlayer);

    if (testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] == chosenCard)
        strcat(result, "   PASS - when gaining to discard and discard pile receives chosen card.\n");           
    else 
        strcat(result, " * FAIL - when gaining to discard, but discard pile does not receives chosen card.\n"); 


    // ********** Test #4 **************************************************
    // *** when gaining to deck, deck pile receives the choosen card.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing

    // call function under test
    returnValue = gainCard(chosenCard, &testGame, 1, currentPlayer);

    if (testGame.deck[currentPlayer][testGame.deckCount[currentPlayer] - 1] == chosenCard)
        strcat(result, "   PASS - when gaining to deck and deck pile receives chosen card.\n");           
    else 
        strcat(result, " * FAIL - when gaining to deck, but deck pile does not receives chosen card.\n"); 


    // ********** Test #5 **************************************************
    // *** when gaining to hand, player's hand receives the choosen card.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing

    // call function under test
    returnValue = gainCard(chosenCard, &testGame, 2, currentPlayer);

    if (testGame.hand[currentPlayer][testGame.handCount[currentPlayer] - 1] == chosenCard)
        strcat(result, "   PASS - when gaining to hand and hand pile receives chosen card.\n");           
    else 
        strcat(result, " * FAIL - when gaining to hand, but hand pile does not receives chosen card.\n"); 


    // ********** Test #6 **************************************************
    // *** when gaining a card, does not affect other players' state.
    // *********************************************************************
    if (compareOtherPlayers(&game, &testGame, currentPlayer) == 0)
        strcat(result, "   PASS - when there is no state change occurred for other players.\n");        
    else 
        strcat(result, " * FAIL - when there is state change occurred for other players.\n");  


    // ********** Test #7 **************************************************
    // *** when gaining a card, the supply pile of the choosen card loses 
    // *** a card.
    // *********************************************************************
    if ((game.supplyCount[chosenCard] - 1) == testGame.supplyCount[chosenCard])
        strcat(result, "   PASS - when supply pile of the chosen card loses one card.\n");        
    else 
        strcat(result, " * FAIL - when supply pile of the chosen card does not lose one card.\n"); 


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
    testGainCard();
    return 0;
}
