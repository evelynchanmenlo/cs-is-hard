// Implements Game of Fifteen (generalized to d x d)

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Constants
#define DIM_MIN 3
#define DIM_MAX 9
#define COLOR "\033[32m"

// Board
int board[DIM_MAX][DIM_MAX];

// Dimensions
int d;

int steps = 0;

// Saved locations of the blank tile
int blank_row;
int blank_col;

// Prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void swap(int *a, int *b);
void print_grid_row(int d);
void print_tile(int tile);

int main(int argc, string argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // Ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n", DIM_MIN, DIM_MIN, DIM_MAX,
               DIM_MAX);
        return 2;
    }

    // Open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // Greet user with instructions
    greet();

    // Initialize the board
    init();

    // Accept moves until game is won
    while (true)
    {
        // Clear the screen
        clear();

        // Draw the current state of the board
        draw();

        // Log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // Check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // Prompt for move
        int tile = get_int("Tile to move: ");

        // Quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // Log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // Move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // Sleep thread for animation's sake
        usleep(50000);
    }

    // Close log
    fclose(file);

    // Print number of steps
    printf("Number of steps: %i\n", steps);

    // Success
    return 0;
}

// Clears screen using ANSI escape sequences
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

// Greets player
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(200000);
}

// Initializes the game's board with tiles numbered 1 through d*d - 1
void init(void)
{
    // Starts the board at the right number to ensure that there is a blank space at the end
    steps++;
    int num = (d * d) - 1;
    // Iterates for every number in the board
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {   steps++;
            board[i][j] = num;
            // If the board size is even, the number 2 and 1 must be switched
            steps++;
            if (d % 2 == 0)
            {
                steps++;
                if (num == 2)
                {
                    steps++;
                    board[i][j] = 1;
                }
                steps++;
                if (num == 1)
                {
                    steps++;
                    board[i][j] = 2;
                }
            }
            // Make sure the starting nubmers in the board go in decreasing order
            steps++;
            num--;
        }
    }
}

// Prints the board in its current state
void draw(void)
{
    // Iterates for every number in the board
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // Make sure that the blankspace prints as a underscore
            steps++;
            if (board[i][j] == 0)
            {
                steps++;
                printf("   _");
            }
            else
            {
                steps+=2;
                printf("%4i", board[i][j]);
            }
        }
        steps++;
        printf("\n");
    }
}

// Moves the tile to the blank space per user prompting
bool move(int tile)
{
    steps += 2;
    int tile_row;
    int tile_col;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // Gets the current tile and blank space location
            steps++;
            if (board[i][j] == tile)
            {
                steps += 2;
                tile_row = i;
                tile_col = j;
            }
            steps++;
            if (board[i][j] == 0)
            {
                steps += 2;
                blank_row = i;
                blank_col = j;
            }
        }
    }

    // Finds the overall difference between tile and the blank column
    steps++;
    int dif = abs(tile_row - blank_row) + abs(tile_col - blank_col);
    // The tile must be within one space next to the blank space in order for it to move
    steps++;
    if (dif == 1)
    {
        steps += 2;
        board[tile_row][tile_col] = 0;
        board[blank_row][blank_col] = tile;
        return true;
    }
    return false;
}

// Returns true if game is won (i.e., board is in winning configuration), else false
bool won(void)
{
    // Makes sure that the current board goes in increasing order
    steps++;
    int start_num = 1;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            // Makes sure to skip the last number of the board, as the value is 0.
            steps++;
            if (start_num == (d * d))
            {
                continue;
            }
            steps++;
            // If it doesn't match, it returns false and makes the user continue the game
            if (board[i][j] != start_num)
            {
                return false;
            }
            else
            {
                steps+=2;
                start_num++;
            }
        }
    }
    return true;
}
