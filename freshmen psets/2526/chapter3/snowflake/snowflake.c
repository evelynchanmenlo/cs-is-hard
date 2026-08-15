//Snowflake by Evelyn Chan
#include <stdio.h>
#define DIM 9

void init(void);
void draw(void);
//declares 2D char array
char board[DIM][DIM];

int main(void)
{
    init();
    draw();
}

// function to fill the array
void init(void)
{
    //Fills each array with stars
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            // this checks if this is in the middle row or column
            // if ((i > 3 && i < 6) || (j > 3 && j < 6))
            if (i == 4 || j == 4)
            {
                board[i][j] = '*';
            }
            else
            {
                board[i][j] = ' ';
            }

            if (i == j)
            {
                board [i][j] = '*';
            }

            if (i + j == 9)
            {
                board[i][j] = '*';
            }
        }
    }
}

//function to print the board
void draw(void)
{
    //This prints the board
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

