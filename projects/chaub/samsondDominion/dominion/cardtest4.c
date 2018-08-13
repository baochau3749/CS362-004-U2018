
/* -----------------------------------------------------------------------
 * Description: Unit test for the Remodel card.
 *
 * Makefile's compile command:
 * cardtest4: cardtest4.c dominion.o rngs.o test_helpers.o
        gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
	    ./cardtest4
 * -----------------------------------------------------------------------
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define TEST_CARD "Remodel"

void testRemodelCardEffect() {
    char result[2000];
    int seed = 10, returnValue;
    int currentPlayer, numPlayers = 2;
    int cardToPlay = remodel, cardToGain = council_room;
    int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
    int kingdomCards[10] = { adventurer, council_room, feast, gardens, mine, 
                             remodel, smithy, village, steward, treasure_map };
    struct gameState testGame, game;

    initializeGame(numPlayers, kingdomCards, seed, &game);      // Initialize a new game
    currentPlayer = game.whoseTurn;                             // get current player
    game.hand[currentPlayer][0] = cardToPlay;                   // preset values for test run.
    game.hand[currentPlayer][1] = estate;
    game.hand[currentPlayer][2] = copper;
    game.handCount[currentPlayer] = 3;
    game.playedCardCount = 0;
    testGame.playedCards[0] = -1;
    choice1 = estate;
    choice2 = cardToGain;

    printf("TESTING CARD: %s\n", TEST_CARD);    
    printf("=====================\n\n");    
    printf("Player plays the %s card:\n", TEST_CARD);    
        
    // ********** Test #1 **************************************************
    // *** when gain card's value is greater than trash card by more than
    // *** 2, the function should return -1
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing
    
    // call function under test
    returnValue = cardEffect(cardToPlay, choice1, choice2, choice3, &testGame, handpos, &bonus);

    if (returnValue == -1)
        strcpy(result, "   PASS - when value of gain card is too high, function returns -1.\n");  
    else
        strcpy(result, " * FAIL - when value of gain card is too high, but function does not return -1.\n");  

    // ********** Test #2 **************************************************
    // *** the played (Remodel) card should go into the played card area 
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing
    
    // call function under test
    cardEffect(cardToPlay, choice1, choice2, choice3, &testGame, handpos, &bonus);
    if (testGame.playedCards[0] == cardToPlay)
        strcat(result, "   PASS - when the Remodel card is sent to played cards area.\n");        
    else 
        strcat(result, " * FAIL - when the Remodel card is not sent to played cards area.\n");  


    // ********** Test #3 **************************************************
    // *** The card choosen to be trash should no longer in player's hand.    
    // *********************************************************************
    if ((testGame.handCount[currentPlayer] == 1) && (testGame.hand[currentPlayer][0] != choice1))
        strcat(result, "   PASS - when the trash card is removed from player's possession.\n");        
    else 
        strcat(result, " * FAIL - when the trash card is not removed from player's possession.\n");


    // ********** Test #4 **************************************************
    // *** The number of card in the discard pile should increase by 1.
    // *********************************************************************  
    // *** The gain card should go into the discard pile.
    // *********************************************************************   
    if ((game.discardCount[currentPlayer] + 1) == testGame.discardCount[currentPlayer])
        strcat(result, "   PASS - when count of discard pile is increased by 1.\n");        
    else 
        strcat(result, " * FAIL - when count of discard pile is not increased by 1.\n");   


    // ********** Test #5 **************************************************
    // *** The gain card should go into the discard pile.
    // *********************************************************************   
    if (testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] == choice2)
        strcat(result, "   PASS - when the gain card is added to the discard pile.\n");        
    else 
        strcat(result, " * FAIL - when the gain card is not added to the discard pile.\n");      


    // ********** Test #6 **************************************************
    // *** Player's deck should remain unchanged.
    // *********************************************************************
    if (game.deckCount[currentPlayer] == testGame.deckCount[currentPlayer])
        strcat(result, "   PASS - when count of deck pile remains unchanged.\n");        
    else 
        strcat(result, " * FAIL - when count of deck pile is changed.\n");   


    // ********** Test #7 **************************************************
    // *** The count of the gain card's supply pile should decrease by 1.
    // *********************************************************************
    if ((game.supplyCount[choice2] - 1) == testGame.supplyCount[choice2])
        strcat(result, "   PASS - when supply pile of the gain card loses one card.\n");        
    else 
        strcat(result, " * FAIL - when supply pile of the gain card does not lose one card.\n"); 


    // ********** Test #8 **************************************************
    // *** Playing a Remodel card should not affect other players' state.
    // *********************************************************************    
    if (compareOtherPlayers(&game, &testGame, currentPlayer) == 0)
        strcat(result, "   PASS - when there is no state change occurred for other players.\n");        
    else 
        strcat(result, " * FAIL - when there is state change occurred for other players.\n");  


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
    testRemodelCardEffect();
    return 0;
}

