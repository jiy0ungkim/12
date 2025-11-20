#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_DIE     6
#define MAXLENGTH   30 

#define N_PLAYER            3
#define PLAYERSTATUS_LIVE   0
#define PLAYERSTATUS_DIE    1
#define PLAYERSTATUS_END    2

char player_name[N_PLAYER][MAXLENGTH];
int player_position[N_PLAYER];
int player_coin[N_PLAYER];
int player_status[N_PLAYER];
char player_statusString[3][MAXLENGTH] = {"LIVE", "DIE", "END"};


void initPlayer(void)
{
     int i;
     for (i=0; i<N_PLAYER; i++)
     {
         printf("Player %i's name: ", i);
         scanf("%s", player_name[i]); 
         player_position[i] = 0;
         player_coin[i] = 0;
         player_status[i] = PLAYERSTATUS_LIVE;
         fflush(stdin);
     }
}

void printPlayerPosition(int player)
{
     int i;
     for (i=0; i<N_BOARD; i++)
     {
         printf("|");
         if (i == player_position[player])
            printf("%c", player_name[player][0]);
         else
         {
             if (board_getBoardStatus(i) == BOARDSTATUS_OK)
                printf(" "); 
             else
                printf("X");
         
         }
     }
     printf("|\n");
}

void printPlayerStatus(void)
{
     int i;
     for (i=0; i<N_PLAYER; i++)
     {
         printf("%s : pos %i, coin %i, status %s\n", 
                    player_name[i], 
                    player_position[i],
                    player_coin[i], 
                    player_statusString[player_status[i]]);
         printPlayerPosition(i);
     }
}

int rolldie(void)
{
    return rand()%MAX_DIE + 1;
}

int main(int argc, char *argv[])
{
    int cnt; // for testing
    int turn; 
    int dum;
    srand((unsigned)time(NULL));
    
    //opening
    printf("==================================================\n");
    printf("                 SHARK GAME START                 \n");
    printf("==================================================\n");
    
    //step 1. Initialization (player name setting + variables)
    board_initBoard();
    initPlayer();//Player init
    
    //step 2. Turn play (do-while)
    cnt = 0;
    turn = 0;
    do{
        int die_result;
        
        if (player_status[turn] != PLAYERSTATUS_LIVE)
        {  
           turn = (turn + 1) % N_PLAYER;   
           continue;
        }  
        
        //2-1. Print status
        board_printBoardStatus();
        printPlayerStatus();// print player_status
        
        //2-2. Roll die (player turn)
        printf("%s turn!! ", player_name[turn]);
        printf("Press any key to roll a die!\n");
        scanf("%d", &dum);
        fflush(stdin);
        die_result = rolldie();
        
        //2-3. Move (print result) (player turn)
        player_position[turn] += die_result; 
        if (player_position[turn] >= (N_BOARD - 1))
        {
            player_position[turn] = N_BOARD-1;
            player_status[turn] = PLAYERSTATUS_END;
        }
        
        printf("Die result : %i, %s moved to %i\n", 
                    die_result, player_name[turn], player_position[turn]);
        
        player_coin[turn] += board_getBoardCoin(player_position[turn]);
        printf("Lucky! %s got %i coins", player_name[turn], player_coin[turn]);

        //2-4. Change turn & Move shark
        
        cnt++;
        turn = (turn + 1)%N_PLAYER;
        printf("\n\n");
    } while(cnt<N_PLAYER*5); //game end condition
    //step 3. Game end (print winner)
    
    
    
    // ending
    printf("\n\n\n\n\n\n\n");
    printf("==================================================\n");
    printf("                  SHARK GAME END                  \n");
    printf("==================================================\n");
    
    system("PAUSE");	
    return 0;
}
