
/* -----------------------------------------------------------------------
 * Description: Unit test for the Smithy card.
 *
 * Makefile's compile command:
 * cardtest1: cardtest1.c dominion.o rngs.o test_helpers.o
        gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
	    ./cardtest1
 * -----------------------------------------------------------------------
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include "test_helpers.h"
#include "rngs.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define TEST_CARD "Smithy"

void testSmithyCardEffect() {
    char result[2000];
    int seed = 10;
    int currentPlayer, numPlayers = 2;
     int cardToPlay = smithy;
    int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
    int kingdomCards[10] = { adventurer, council_room, feast, gardens, mine, 
                             remodel, smithy, village, steward, treasure_map };
    struct gameState testGame, game;

    initializeGame(numPlayers, kingdomCards, seed, &game);      // Initialize a new game
    currentPlayer = game.whoseTurn;                             // get current player
    game.hand[currentPlayer][handpos] = cardToPlay;             // preset values for tests.

    printf("TESTING CARD: %s\n", TEST_CARD);    
    printf("====================\n\n");    
    printf("Player plays the %s card:\n", TEST_CARD);    
    
    // ********** Test #1 **************************************************
    // *** When playing smithy card and the player's pile is empty, player 
    // *** should not receive any new card since there are none to drawn from.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing
    testGame.discardCount[currentPlayer] = 0;               // clear discard count
    testGame.deckCount[currentPlayer] = 0;                  // clear deck count
    
    // call function under test
    cardEffect(cardToPlay, choice1, choice2, choice3, &testGame, handpos, &bonus);

    if ((game.handCount[currentPlayer] - 1) == testGame.handCount[currentPlayer])
        strcpy(result, "   PASS - when player's pile is empty and player does not receive any new cards.\n");              
    else if ((game.handCount[currentPlayer] - 1) < testGame.handCount[currentPlayer])
        strcpy(result, " * FAIL - when player's pile is empty, but player receives new card(s).\n");         


    // ********** Test #2 **************************************************
    // *** When playing smithy card and the player's pile has only one card, 
    // *** player should receive one new card since that's all to drawn from.
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
    // *** When playing smithy card and the player's pile has a total of 3 cards, 
    // *** player should receive 3 cards, which is the basic functionality of smithy card.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing
    testGame.discardCount[currentPlayer] = 0;               // clear discard count
    testGame.deckCount[currentPlayer] = 3;                  // preset deck count to 3

    // call function under test
    cardEffect(cardToPlay, choice1, choice2, choice3, &testGame, handpos, &bonus);

    if ((game.handCount[currentPlayer] + 2) == testGame.handCount[currentPlayer])
        strcat(result, "   PASS - when player's pile has 3 cards and player receives 3 cards.\n");        
    else 
        strcat(result, " * FAIL - when player's pile has 3 cards, but player does not receive 3 cards.\n");  
    

    // ********** Test #4 **************************************************
    // *** When playing smithy card and the player's pile has more than 3 cards, 
    // *** player should receive only 3 cards (basic functionality of smithy card).
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));     // copy game state for testing

    // call function under test    
    cardEffect(cardToPlay, choice1, choice2, choice3, &testGame, handpos, &bonus);

    if ((game.handCount[currentPlayer] + 2) == testGame.handCount[currentPlayer])
        strcat(result, "   PASS - when player's pile has more than 3 cards and player receives 3 cards.\n");        
    else 
        strcat(result, " * FAIL - when player's pile has more than 3 cards, but player does not receive 3 cards.\n");
  

    // ********** Test #6 **************************************************
    // *** When playing smithy card, the smithy card will end up in the playedCards pile. 
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));        // copy game state for testing

    // call function under test
    cardEffect(cardToPlay, choice1, choice2, choice3, &testGame, handpos, &bonus);

    if ((game.playedCardCount + 1) == testGame.playedCardCount)
        strcat(result, "   PASS - when the Smithy card is sent to played cards area.\n");        
    else 
        strcat(result, " * FAIL - when the Smithy card is not sent to played cards area.\n");   


    // ********** Test #7 **************************************************
    // *** Playing a Smithy card should not affect other players' state.
    // *********************************************************************    
    if (compareOtherPlayers(&game, &testGame, currentPlayer) == 0)
        strcat(result, "   PASS - when there is no state change occurred for other players.\n");        
    else 
        strcat(result, " * FAIL - when there is state change occurred for other players.\n");  
 

    // ********** Test #8 **************************************************
    // *** Playing a Smithy card should not affect victory card and kingdom
    // *** card piles.
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
    testSmithyCardEffect();
    return 0;
}

