/*================================================================
* Filename:test.c
* Author: KCN_yu
* Createtime:Fri 08 May 2020 11:57:56 AM CST
================================================================*/

#include <stdio.h>
#include <stdlib.h>

#define N    15

int chessboard[N + 1][N + 1] = { 0 };

int whoseTurn = 0;

void initGame(void);
void printChessboard(void);
void playChess(void);
int judge(int, int);

int main(void)
{
    initGame();

    while (1)
    {
            whoseTurn++;

            playChess();
        }

    return 0;
}

void initGame(void)
{
    char c;

    printf("Please input \'y\' to enter the game:");
    c = getchar();
    if ('y' != c && 'Y' != c)
        exit(0);

    system("clear");
    printChessboard();
}

void printChessboard(void)
{
    int i, j;

    for (i = 0; i <= N; i++)
    {
            for (j = 0; j <= N; j++)
            {
                        if (0 == i)
                            printf("%3d", j);
                        else if (j == 0)
                            printf("%3d", i);
                        else if (1 == chessboard[i][j])
                            printf("  O");
                        else if (2 == chessboard[i][j])
                            printf("  X");
                        else
                            printf("  *");
                    }
            printf("\n");
        }
}

void playChess(void)
{
    int i, j, winner;

    if (1 == whoseTurn % 2)
    {
            printf("Turn to player 1, please input the position:");
            scanf("%d %d", &i, &j);

            while(chessboard[i][j] != 0)
            {
                        printf("This position  has been occupied, please input the position again:");
                        scanf("%d %d", &i, &j);
                    }

            chessboard[i][j] = 1;
        }
    else
    {
            printf("Turn to player 2, please input the position:");
            scanf("%d %d", &i, &j);

            while(chessboard[i][j] != 0)
            {
                        printf("This position  has been occupied, please input the position again:");
                        scanf("%d %d", &i, &j);
                    }

            chessboard[i][j] = 2;
        }

    system("clear");
    printChessboard();

    if (judge(i, j))
    {
            if (1 == whoseTurn % 2)
            {
                        printf("Winner is player 1!\n");
                        exit(0);
                    }
            else
            {
                        printf("Winner is player 2!\n");
                        exit(0);
                    }
        }
}

int judge(int x, int y)
{
    int i, j;
    int t = 2 - whoseTurn % 2;
    const int step[4][2]={{-1,0},{0,-1},{1,1},{1,0}};
    for(int i=0;i<4;++i)
    {
            const int d[2]={-1,1};
            int count=1;
            for(int j=0;j<2;++j)
                for(int k=1;k<=4;++k){
                                int row=x+k*d[j]*step[i][0];
                                int col=y+k*d[j]*step[i][1];
                                if( row>=1 && row<=N &&
                                                            col>=1 && col<=N &&
                                                                                chessboard[x][y]==chessboard[row][col])
                                    count+=1;
                                else
                                    break;
                            }
            if(count>=5)
                return 1;
        }
    return 0;
}
