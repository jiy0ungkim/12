#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_DIE     6

int rolldie(void)
{
    return rand()%MAX_DIE + 1;
}

int main(int argc, char *argv[])
{
    int cnt; // for testing
    int pos; // for testing (player position)
    
    srand((unsigned)time(NULL));
    
    //opening
    printf("==================================================\n");
    printf("                 SHARK GAME START                 \n");
    printf("==================================================\n");
    printf("\n");
    
    //step 1. Initialization (player name setting + variables)
    board_initBoard();
    
    //step 2. Turn play (do-while)
    cnt = 0;
    pos = 0;
    
    do{
        int die_result;
        int coinResult;
        
        //2-1. Print status
        board_printBoardStatus();
        
        //2-2. Roll die
        die_result = rolldie();
        
        //2-3. Move (print result)
        pos += die_result;
        
        printf("Position: %i (Die: %i)\n", pos, die_result);
        
        coinResult += board_getBoardCoin(pos);
        
        printf("Coin: %i\n", coinResult);
        //2-4. Change turn & Move shark
        
        cnt++;
        printf("\n");
    } while(cnt<5);
    //step 3. Game end (print winner)
    
    
    
    
    
    // ending
    printf("\n\n\n\n\n\n\n");
    printf("==================================================\n");
    printf("                  SHARK GAME END                  \n");
    printf("==================================================\n");
    
    system("PAUSE");	
    return 0;
}
