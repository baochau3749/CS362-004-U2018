
/* -----------------------------------------------------------------------
 * Description: Unit test for the council_room card.
 *
 * Makefile's compile command:
 * cardtest3: cardtest3.c dominion.o rngs.o test_helpers.o
        gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
	    ./cardtest3
 * -----------------------------------------------------------------------
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define TEST_CARD "Council Room"

void testCouncilRoomCardEffect() {
    char result[2000];
    int seed = 10;
    int currentPlayer, numPlayers = 2;
     int cardToPlay = council_room;
    int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
    int kingdomCards[10] = { adventurer, council_room, feast, gardens, mine, 
                             remodel, smithy, village, steward, treasure_map };
    struct gameState testGame, game;

    initializeGame(numPlayers, kingdomCards, seed, &game);      // Initialize a new game
    currentPlayer = game.whoseTurn;                             // get current player
    game.hand[currentPlayer][handpos] = cardToPlay;             // preset values for test run.

    printf("TESTING CARD: %s\n", TEST_CARD);    
    printf("==========================\n\n");      
    printf("Player plays the %s card:\n", TEST_CARD);    

    // ********** Test #1 **************************************************
    // *** When player's pile is empty, player should not receive any new 
    // *** card since there are none to drawn from.
    // *********************************************************************    
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing
    testGame.discardCount[currentPlayer] = 0;               // clear discard count
    testGame.deckCount[currentPlayer] = 0;                  // clear deck count

    // copy game state for testing
    cardEffect(smithy, choice1, choice2, choice3, &testGame, handpos, &bonus);

    if ((game.handCount[currentPlayer] - 1) == testGame.handCount[currentPlayer])
        strcpy(result, "   PASS - when player's pile is empty and player does not receive any new cards.\n");              
    else if ((game.handCount[currentPlayer] - 1) < testGame.handCount[currentPlayer])
        strcpy(result, " * FAIL - when player's pile is empty, but player receives new card(s).\n"); 

    
    // ********** Test #2 **************************************************
    // *** When the player's pile has only one card, player should receive 
    // *** one new card since that's all to drawn from.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing
    testGame.discardCount[currentPlayer] = 0;               // clear discard count
    testGame.deckCount[currentPlayer] = 1;                  // preset deck count to 1
    
    // call function under test
    cardEffect(cardToPlay, choice1, choice2, choice3, &testGame, handpos, &bonus);
    
    // Player played a card and gain a card, so net count on hand should be the same.
    if (game.handCount[currentPlayer] == testGame.handCount[currentPlayer])
        strcat(result, "   PASS - when player's pile has only 1 card and player receives 1 card.\n");           
    else 
        strcat(result, " * FAIL - when player's pile has only 1 card, but player does not receive 1 card.\n"); 


    // ********** Test #3 **************************************************
    // *** Player draws no more than 4 cards.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing

    // call function under test    
    cardEffect(cardToPlay, choice1, choice2, choice3, &testGame, handpos, &bonus);

    if ((game.handCount[currentPlayer] + 3) == testGame.handCount[currentPlayer])
        strcat(result, "   PASS - when player's pile has more than 4 cards and player receives 4 cards.\n");        
    else 
        strcat(result, " * FAIL - when player's pile has more than 4 cards, but player does not receive 4 cards.\n");


    // ********** Test #4 **************************************************
    // *** Player should receives one additional buy.
    // *********************************************************************
    if ((game.numBuys + 1) == testGame.numBuys)
        strcat(result, "   PASS - when player receives 1 additional buy.\n");        
    else 
        strcat(result, " * FAIL - when player does not receive 1 additional buy.\n");  


    // ********** Test #5 **************************************************
    // *** Other players should draw one card.
    // *********************************************************************
    if ((game.handCount[currentPlayer + 1] + 1) == testGame.handCount[currentPlayer + 1])
        strcat(result, "   PASS - when other players draw one card.\n");        
    else 
        strcat(result, " * FAIL - when other players do not draw one card.\n");   


    // ********** Test #6 **************************************************
    // *** When (council room) played card should ends up in the played pile.
    // *********************************************************************
    if (((game.playedCardCount + 1) == testGame.playedCardCount) &&
        (testGame.playedCards[testGame.playedCardCount - 1]) == cardToPlay)
        strcat(result, "   PASS - when the council room card is sent to played card area.\n");        
    else 
        strcat(result, " * FAIL - when the council room card is not sent to played card area.\n"); 


    // ********** Test #7 **************************************************
    // *** Playing a Council Room card should not affect victory card 
    // *** and kingdom card piles.
    // *********************************************************************  
    if (compareKingdomCards(&game, &testGame) == 0)
        strcat(result, "   PASS - when there is no change in victory card and kingdom card piles.\n");        
    else 
        strcat(result, " * FAIL - when there is change in victory card and kingdom card piles.\n");  


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
    testCouncilRoomCardEffect();
    return 0;
}

