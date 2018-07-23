/* -----------------------------------------------------------------------
 * Description: Unit test for the Adventurer card.
 *
 * Makefile's compile command:
 * cardtest2: cardtest2.c dominion.o rngs.o
        gcc -o cardtest2 cardtest1.c test_helpers.c -g dominion.o rngs.o $(CFLAGS)
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

#define TEST_CARD "Adventurer"

void testAdventurerCardEffect() {    
    char result[2000];
    int seed = 10;
    int currentPlayer, numPlayers = 2;
    int cardToPlay = adventurer;
    int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;
    int kingdomCards[10] = { adventurer, council_room, feast, gardens, mine, 
                             remodel, smithy, village, steward, treasure_map };
    struct gameState testGame, game;

    initializeGame(numPlayers, kingdomCards, seed, &game);          // Initialize a new game
    currentPlayer = testGame.whoseTurn;                             // get current player
    game.hand[currentPlayer][0] = cardToPlay;                       // preset values for tests.
    game.hand[currentPlayer][1] = estate;
    game.hand[currentPlayer][2] = estate;
    game.handCount[currentPlayer] = 3;

    game.deck[currentPlayer][0] = copper;                           // preset values for tests.
    game.deck[currentPlayer][1] = silver;
    game.deck[currentPlayer][2] = gold;
    game.deck[currentPlayer][3] = smithy;
    game.deck[currentPlayer][4] = village;
    game.deckCount[currentPlayer] = 5;

    printf("TESTING CARD: %s\n", TEST_CARD);    
    printf("========================\n\n");    
    printf("Player plays the %s card:\n", TEST_CARD);  


    // ********** Test #1 **************************************************
    // *** When playing Adventurer card, the Adventurer card will end up in 
    // *** the playedCards pile, 
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));         // copy game state for testing

    // call function under test
    cardEffect(cardToPlay, choice1, choice2, choice3, &testGame, handpos, &bonus);

    if (((game.playedCardCount + 1) == testGame.playedCardCount) &&
        (testGame.playedCards[testGame.playedCardCount - 1]) == cardToPlay)
        strcpy(result, "   PASS - when the Adventurer card is sent to played card area.\n");        
    else 
        strcpy(result, " * FAIL - when the Adventurer card is not sent to played card area.\n");   


    // ********** Test #2 ***************************************************
    // *** When 2 treasure cards revealed, no more cards are revealed.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));       // copy game state for testing

    // call function under test
    cardEffect(cardToPlay, choice1, choice2, choice3, &testGame, handpos, &bonus);

    if ((testGame.deckCount[currentPlayer] == 1) && (testGame.deck[currentPlayer][0] == copper))
        strcat(result, "   PASS - when 2 treasure cards revealed, no more cards are revealed.\n");       
    else 
        strcat(result, " * FAIL - when 2 treasure cards revealed, more cards are revealed.\n"); 


    // ********** Test #3 **************************************************
    // *** The revealed treasure cards should be added to player's hand.
    // *********************************************************************
    if ((testGame.hand[currentPlayer][testGame.handCount[currentPlayer] - 1] == silver) && 
        (testGame.hand[currentPlayer][testGame.handCount[currentPlayer] - 2] == gold))
        strcat(result, "   PASS - when revealed treasure cards are added to player's hand.\n");       
    else 
        strcat(result, " * FAIL - when revealed treasure cards are not added to player's hand.\n");


    // ********** Test #4 **************************************************
    // *** The non-treasure cards are revealed and they end up discarded.
    // ********************************************************************* 
    if ((testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 1] == smithy) && 
        (testGame.discard[currentPlayer][testGame.discardCount[currentPlayer] - 2] == village))
        strcat(result, "   PASS - when revealed, non-treasure cards are added to discard pile.\n");       
    else 
        strcat(result, " * FAIL - when revealed, non-treasure cards are not added to discard pile.\n");


    // ********** Test #5 **************************************************
    // *** When deck is empty, discard cards should be shuffle into deck 
    // *** and continue.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));         // copy game state for testing
    game.discard[currentPlayer][0] = copper;                    // preset values for tests.
    game.discard[currentPlayer][1] = copper;    
    testGame.discardCount[currentPlayer] = 2;
    testGame.deckCount[currentPlayer] = 0;

    // call function under test
    cardEffect(cardToPlay, choice1, choice2, choice3, &testGame, handpos, &bonus);

    if ((testGame.hand[currentPlayer][testGame.handCount[currentPlayer] - 1] == copper) && 
        (testGame.hand[currentPlayer][testGame.handCount[currentPlayer] - 2] == copper))
        strcat(result, "   PASS - when deck is empty, discard cards are shuffled into deck.\n");       
    else 
        strcat(result, " * FAIL - when deck is empty, discard cards are not shuffled into deck.\n"); 

    // ********** Test #6**************************************************
    // *** When there are no treasure cards in player's pile, player's
    // *** should not receive any new cards.
    // *********************************************************************
    memcpy(&testGame, &game, sizeof(struct gameState));         // copy game state for testing
    testGame.discardCount[currentPlayer] = 0;                   // preset values for tests.
    testGame.deckCount[currentPlayer] = 0;

    // call function under test
    cardEffect(cardToPlay, choice1, choice2, choice3, &testGame, handpos, &bonus);

    if (testGame.handCount[currentPlayer] == 2)
        strcat(result, "   PASS - when no treasure cards in piles, player's hand receives no new cards.\n");       
    else 
        strcat(result, " * FAIL - when no treasure cards in piles, player's hand has unexpected changes.\n");    

    // ********** Test #7 **************************************************
    // *** Playing a Adventurer card should not affect other players' state.
    // *********************************************************************    
    memcpy(&testGame, &game, sizeof(struct gameState));         // copy game state for testing

    // call function under test
    cardEffect(cardToPlay, choice1, choice2, choice3, &testGame, handpos, &bonus);
 
     if (compareOtherPlayers(&game, &testGame, currentPlayer) == 0)
        strcat(result, "   PASS - when there is no state change occurred for other players.\n");        
    else 
        strcat(result, " * FAIL - when there is state change occurred for other players.\n");  
 

    // ********** Test #8 **************************************************
    // *** Playing a Adventurer card should not affect victory card and 
    // *** kingdom card piles.
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
    testAdventurerCardEffect();
    return 0;
}