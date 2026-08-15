/**
 * Sudoku by Evelyn
 *
 * Less Spicy version for CS1 @ Menlo School
 * Based on the CS50 Problem Set
 * Written by Zach Blick
 * With help from Douglas Kiang
 * on Monday, Aug. 14 2023
 */

#include "sudoku.h"
#include <ctype.h>
#include <ncurses.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Macro for processing control characters
#define CTRL(x) ((x) & ~0140)

// Size of each int (in bytes) in *.bin files
#define INTSIZE 4

// Wrapper for our game's globals
struct
{
    // The current level
    char *level;

    // The game's board
    int board[9][9];

    // The board's number
    int number;

    // The board's top-left coordinates
    int top, left;

    // The cursor's current location between (0,0) and (8,8)
    int y, x;

    // A copy of the original board to check to see if a number
    // came with the board originally.
    int board_copy[9][9];

    // A boolean indicating whether or not the user has won. This is
    // used to lock the screen and change the numbers to green.
    bool game_over;

    bool edit;

    // Previously edited values, for the undo function.
    int last_y, last_x, last_value;
} g;

// Prototypes
void draw_grid(void);
void draw_borders(void);
void draw_logo(void);
void draw_numbers(void);
void hide_banner(void);
bool load_board(void);
void handle_signal(int signum);
void log_move(int ch);
void redraw_all(void);
bool restart_game(void);
void show_banner(char *b);
void show_cursor(void);
void shutdown(void);
bool startup(void);
void copy_board(void);
bool can_edit(int row, int col);
bool has_row_error(int row, int col, int entry);
bool has_col_error(int row, int col, int entry);
bool has_box_error(int row, int col, int entry);
bool has_won(void);

int main(int argc, char *argv[])
{
    // Ensure that number of arguments is as expected
    if (argc != 2 && argc != 3)
    {
        fprintf(stderr, "Usage: sudoku n00b|l33t [#]\n");
        return 1;
    }

    // Ensure that level is valid
    if (strcmp(argv[1], "debug") == 0)
    {
        g.level = "debug";
    }
    else if (strcmp(argv[1], "n00b") == 0)
    {
        g.level = "n00b";
    }
    else if (strcmp(argv[1], "l33t") == 0)
    {
        g.level = "l33t";
    }
    else
    {
        fprintf(stderr, "Usage: sudoku n00b|l33t [#]\n");
        return 2;
    }

    // n00b and l33t levels have 1024 boards; debug level has 9
    int max = (strcmp(g.level, "debug") == 0) ? 9 : 1024;

    // Ensure that #, if provided, is in [1, max]
    if (argc == 3)
    {
        // Ensure n is integral
        char c;
        if (sscanf(argv[2], " %d %c", &g.number, &c) != 1)
        {
            fprintf(stderr, "Usage: sudoku n00b|l33t [#]\n");
            return 3;
        }

        // Ensure n is in [1, max]
        if (g.number < 1 || g.number > max)
        {
            fprintf(stderr, "That board # does not exist!\n");
            return 4;
        }

        // Seed PRNG with # so that we get same sequence of boards
        srand(g.number);
    }
    else
    {
        // Seed PRNG with current time so that we get any sequence of boards
        srand(time(NULL));

        // Choose a random n in [1, max]
        g.number = rand() % max + 1;
    }

    // Start up ncurses
    if (!startup())
    {
        fprintf(stderr, "Error starting up ncurses!\n");
        return 5;
    }

    // Register handler for SIGWINCH (SIGnal WINdow CHanged)
    signal(SIGWINCH, (void (*)(int)) handle_signal);

    // Start the first game
    if (!restart_game())
    {
        shutdown();
        fprintf(stderr, "Could not load board from disk!\n");
        return 6;
    }
    redraw_all();

    // Let the user play
    int ch;
    do
    {
        // Refresh the screen
        refresh();

        // Get user's input
        ch = getch();

        // Capitalize input to sim

        // Process user's input
        switch (ch)
        {
            // Start a new game
            case 'N':
                hide_banner();
                g.number = rand() % max + 1;
                if (!restart_game())
                {
                    shutdown();
                    fprintf(stderr, "Could not load board from disk!\n");
                    return 6;
                }
                break;

            // Restart current game
            case 'R':
                hide_banner();
                if (!restart_game())
                {
                    shutdown();
                    fprintf(stderr, "Could not load board from disk!\n");
                    return 6;
                }
                break;

            // Let user manually redraw screen with ctrl-L
            case CTRL('l'):
                redraw_all();
                break;

            /**
             * PART 1 — Implement Cursor Movement
             */
            // mr blick is so cool he gave us the code!!!!
            case KEY_LEFT:
                g.x = (g.x + 8) % 9;
                break;

            case KEY_RIGHT:
                g.x = (g.x + 1) % 9;
                break;

            case KEY_UP:
                g.y = (g.y + 8) % 9;
                break;

            case KEY_DOWN:
                g.y = (g.y + 1) % 9;
                break;

            /**
             * PART 1 — Implement Board Modification
             *
             * You will later edit this in parts 2 and
             * 3 to add additional features.
             *
             */

            // Enable the user to replace any blank with a number by
            // moving their cursor over that blank and then hitting a number from 1 to 9.
            case '1' ... '9':
                if (can_edit(g.y, g.x))
                {
                    // For undo, remember where you are, what was here before
                    g.last_y = g.y;
                    g.last_x = g.x;
                    g.last_value = g.board[g.last_y][g.last_x];

                    // Convert the key character to an integer and place it
                    int num = ch - '0';
                    g.board[g.y][g.x] = num;
                    draw_numbers();

                    // Check all three Sudoku constraints and warn the user if any are violated
                    if (has_row_error(g.y, g.x, num))
                    {
                        show_banner("Bad Row");
                    }
                    else if (has_col_error(g.y, g.x, num))
                    {
                        show_banner("Bad Column");
                    }
                    else if (has_box_error(g.y, g.x, num))
                    {
                        show_banner("Bad Box");
                    }

                    // Check if this move completed the board correctly
                    has_won();
                    if (g.game_over == true)
                    {
                        // Redraw the winning colors and show the congratulations message
                        draw_numbers();
                        show_banner("GOOD JOB YOU WON YOU ARE AMAZING!!!!!!!!!");
                    }
                }
                break;

            // Enable the user to change a number that they already inputted back to a blank by
            // hitting any of 0, a period, KEY_BACKSPACE, or KEY_DC or to some other number from 1
            // to 9 by hitting that number
            case '0':
            case KEY_BACKSPACE:
            case KEY_DC:
            case '.':
                if (can_edit(g.y, g.x))
                {
                    // 0 represents a blank cell
                    g.board[g.y][g.x] = 0;
                    draw_numbers();
                }
                break;

            /**
             * PART 3 — UNDO
             */
            case 'u':
            case 'U':
            case CTRL('z'):
                // You cant undo after winning
                if (g.game_over != true)
                {
                    g.board[g.last_y][g.last_x] = g.last_value;
                    g.y = g.last_y;
                    g.x = g.last_x;
                    draw_numbers();
                }
                break;
        }
        // No matter what, make sure the cursor is moved back to its
        // proper location.
        show_cursor();

        // Log input (and board's state) if any was received this iteration
        if (ch != ERR)
        {
            log_move(ch);
        }
    }
    while (ch != 'Q');

    // Shut down ncurses
    shutdown();

    // Tidy up the screen (using ANSI escape sequences)
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);

    // That's all folks
    printf("\nkthxbai!\n\n");
    return 0;
}

// Returns true if the given location is a location
// that the user can edit — i.e., was originally blank.
bool can_edit(int row, int col)
{
    if (g.board_copy[row][col] == 0)
    {
        // g.edit = true;
        return true;
    }
    return false;
}

// Create a copy of the board.
void copy_board(void)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            g.board_copy[i][j] = g.board[i][j];
        }
    }
    return;
}

// Draw's the game's board
void draw_grid(void)
{
    // Get window's dimensions
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    // Determine where top-left corner of board belongs
    g.top = maxy / 2 - 7;
    g.left = maxx / 2 - 30;

    // Enable color
    attron(COLOR_PAIR(PAIR_GRID));

    // Print grid
    for (int i = 0; i < 3; ++i)
    {
        mvaddstr(g.top + 0 + 4 * i, g.left, "+-------+-------+-------+");
        mvaddstr(g.top + 1 + 4 * i, g.left, "|       |       |       |");
        mvaddstr(g.top + 2 + 4 * i, g.left, "|       |       |       |");
        mvaddstr(g.top + 3 + 4 * i, g.left, "|       |       |       |");
    }
    mvaddstr(g.top + 4 * 3, g.left, "+-------+-------+-------+");

    // Remind user of level and #
    char reminder[maxx + 1];
    sprintf(reminder, "   playing %s #%d", g.level, g.number);
    mvaddstr(g.top + 14, g.left + 25 - strlen(reminder), reminder);

    // Disable color
    attroff(COLOR_PAIR(PAIR_GRID));
}

// Draws game's borders.
void draw_borders(void)
{
    // Get window's dimensions
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    // Enable color
    attron(A_PROTECT);
    attron(COLOR_PAIR(PAIR_BORDER));

    // Draw borders
    for (int i = 0; i < maxx; i++)
    {
        mvaddch(0, i, ' ');
        mvaddch(maxy - 1, i, ' ');
    }

    // Draw header
    char header[maxx + 1];
    sprintf(header, "%s by %s", TITLE, AUTHOR);
    mvaddstr(0, (maxx - strlen(header)) / 2, header);

    // Draw footer
    mvaddstr(maxy - 1, 1, "[N]ew Game   [R]estart Game");
    mvaddstr(maxy - 1, maxx - 13, "[Q]uit Game");

    // Disable color
    attroff(COLOR_PAIR(PAIR_BORDER));
}

// Draws game's logo (Must be called after draw_grid has been called at least once)
void draw_logo(void)
{
    // Determine top-left coordinates of logo
    int top = g.top + 2;
    int left = g.left + 30;

    // Enable color
    attron(COLOR_PAIR(PAIR_LOGO));

    // Draw logo
    mvaddstr(top + 0, left, "               _       _          ");
    mvaddstr(top + 1, left, "              | |     | |         ");
    mvaddstr(top + 2, left, " ___ _   _  __| | ___ | | ___   _ ");
    mvaddstr(top + 3, left, "/ __| | | |/ _` |/ _ \\| |/ / | | |");
    mvaddstr(top + 4, left, "\\__ \\ |_| | (_| | (_) |   <| |_| |");
    mvaddstr(top + 5, left, "|___/\\__,_|\\__,_|\\___/|_|\\_\\\\__,_|");

    // Sign logo
    char signature[3 + strlen(AUTHOR) + 1];
    sprintf(signature, "by %s", AUTHOR);
    mvaddstr(top + 7, left + 35 - strlen(signature) - 1, signature);

    // Disable color
    attroff(COLOR_PAIR(PAIR_LOGO));
}

// Draw's game's numbers (Must be called after draw_grid has been called at least once)

void draw_numbers(void)
{
    // Iterate over board's numbers
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            // Determine char
            char c = (g.board[i][j] == 0) ? '.' : g.board[i][j] + '0';

            if (g.game_over == true)
            {
                // After winning, draw everything in the winning color (green)
                attron(COLOR_PAIR(PAIR_WON));
                mvaddch(g.top + i + 1 + i / 3, g.left + 2 + 2 * (j + j / 3), c);
                attroff(COLOR_PAIR(PAIR_WON));
            }
            else if (can_edit(i, j) == true)
            {
                // Cells the user can edit are drawn in the user color
                attron(COLOR_PAIR(PAIR_USER));
                // Draw the number
                mvaddch(g.top + i + 1 + i / 3, g.left + 2 + 2 * (j + j / 3), c);
                attroff(COLOR_PAIR(PAIR_USER));
            }
            // original puzzle digits are drawn in the original color
            else
            {
                // Enable color
                attron(COLOR_PAIR(PAIR_ORIGINAL));

                // Draw the number
                mvaddch(g.top + i + 1 + i / 3, g.left + 2 + 2 * (j + j / 3), c);

                // Disable color
                attroff(COLOR_PAIR(PAIR_ORIGINAL));
            }

            // Refresh the screen
            refresh();
        }
    }
}

// Designed to handles signals (e.g., SIGWINCH)

void handle_signal(int signum)
{
    // Handle a change in the window (i.e., a resizing)
    if (signum == SIGWINCH)
    {
        redraw_all();
    }

    // Re-register myself so this signal gets handled in future too
    signal(signum, (void (*)(int)) handle_signal);
}

// Returns true if placing "entry" at (row,col) would duplicate a value that already exists
// elsewhere in the same row
bool has_row_error(int row, int col, int entry)
{
    for (int i = 0; i < 9; i++)
    {
        // Don't compare the cell with itself
        if (i != col)
        {
            if (g.board[row][i] == entry)
            {
                return true;
            }
        }
    }
    return false;
}

// Returns true if placing `entry` at (row, col) would duplicate a value
// that already exists elsewhere in the same column
bool has_col_error(int row, int col, int entry)
{
    for (int i = 0; i < 9; i++)
    {
        // Dont compare the cell with itself
        if (i != row)
        {
            if (g.board[i][col] == entry)
            {
                return true;
            }
        }
    }
    return false;
}

// Returns true if placing `entry` at (row, col) would duplicate a value
// that already exists elsewhere in the same 3x3 box
bool has_box_error(int row, int col, int entry)
{
    // Find the top-left corner of the 3x3 box containing (row, col)
    int box_row = (row / 3) * 3;
    int box_col = (col / 3) * 3;

    for (int i = box_row; i < box_row + 3; i++)
    {
        for (int j = box_col; j < box_col + 3; j++)
        {
            // Skip the cell itself
            // only need to check the other 8 cells in the box
            if (i != row && j != col)
            {
                if (g.board[i][j] == entry)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// checks whether the board is completely and correctly filled in
// sets g.game_over = true and returns true if the user has won
bool has_won(void)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            int num = g.board[i][j];

            // a blank cell means the board isn't complete yet
            if (g.board[i][j] != 0)
            {
                // if any digit violates a sudoku rule, the board isn't solved
                if (has_row_error(i, j, num))
                {
                    return false;
                }
                else if (has_col_error(i, j, num))
                {
                    return false;
                }
                else if (has_box_error(i, j, num))
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
    }

    // Every cell is fillled and no rules are broken
    // meaning the user has won
    g.game_over = true;
    return true;
}

// Hides banner
void hide_banner(void)
{
    // Get window's dimensions
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    // Overwrite banner with spaces
    for (int i = 0; i < maxx; i++)
    {
        mvaddch(g.top + 16, i, ' ');
    }
}

// Loads current board from disk, returning true iff successful
bool load_board(void)
{
    // Open file with boards of specified level
    char filename[strlen(g.level) + 5];
    sprintf(filename, "%s.bin", g.level);
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        return false;
    }

    // Determine file's size
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);

    // Ensure file is of expected size
    if (size % (81 * INTSIZE) != 0)
    {
        fclose(fp);
        return false;
    }

    // Compute offset of specified board
    int offset = ((g.number - 1) * 81 * INTSIZE);

    // Seek to specified board
    fseek(fp, offset, SEEK_SET);

    // Read board into memory
    if (fread(g.board, 81 * INTSIZE, 1, fp) != 1)
    {
        fclose(fp);
        return false;
    }

    // w00t
    fclose(fp);
    return true;
}

// Logs input and board's state to log.txt to facilitate automated tests
void log_move(int ch)
{
    // Open log
    FILE *fp = fopen("log.txt", "a");
    if (fp == NULL)
    {
        return;
    }

    // Log input
    fprintf(fp, "%d\n", ch);

    // Log board
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fprintf(fp, "%d", g.board[i][j]);
        }
        fprintf(fp, "\n");
    }

    // That's it
    fclose(fp);
}

// (Re)draws everything on the screen
void redraw_all(void)
{
    // Reset ncurses
    endwin();
    refresh();

    // Clear screen
    clear();

    // Re-draw everything
    draw_borders();
    draw_grid();
    draw_logo();
    draw_numbers();

    // Show cursor
    show_cursor();
}

// (Re)starts current game, returning true iff ("if and only if") succesful
bool restart_game(void)
{
    // Reload current game
    if (!load_board())
    {
        return false;
    }

    g.edit = false;
    g.game_over = false;

    // copies the original board
    copy_board();
    draw_grid();
    draw_numbers();

    // reset the undo buffer
    // nothing to undo at the start of the game
    g.last_y = 0;
    g.last_x = 0;
    g.last_value = 0;

    // Get window's dimensions
    int maxy, maxx;
    getmaxyx(stdscr, maxy, maxx);

    // Move cursor to board's center
    g.y = g.x = 4;
    show_cursor();

    // Remove log, if any
    remove("log.txt");

    // w00t
    return true;
}

// Shows cursor at (g.y, g.x)
void show_cursor(void)
{
    // Restore cursor's location
    move(g.top + g.y + 1 + g.y / 3, g.left + 2 + 2 * (g.x + g.x / 3));
}

// Shows a banner (Must be called after show_grid has been called at least once)
void show_banner(char *b)
{
    // Enable color
    attron(COLOR_PAIR(PAIR_BANNER));

    // Determine where top-left corner of board belongs
    mvaddstr(g.top + 16, g.left + 64 - strlen(b), b);

    // Disable color
    attroff(COLOR_PAIR(PAIR_BANNER));
}

// Shuts down ncurses
void shutdown(void)
{
    endwin();
}

// Starts up ncurses and returns true iff successful
bool startup(void)
{
    // Initialize ncurses
    if (initscr() == NULL)
    {
        return false;
    }

    // Enable color
    if (start_color() == ERR || attron(A_PROTECT) == ERR)
    {
        endwin();
        return false;
    }

    // Initialize pairs of colors
    if (init_pair(PAIR_BANNER, FG_BANNER, BG_BANNER) == ERR ||
        init_pair(PAIR_GRID, FG_GRID, BG_GRID) == ERR ||
        init_pair(PAIR_BORDER, FG_BORDER, BG_BORDER) == ERR ||
        init_pair(PAIR_LOGO, FG_LOGO, BG_LOGO) == ERR ||
        init_pair(PAIR_DIGITS, FG_DIGITS, BG_DIGITS) == ERR ||
        init_pair(PAIR_USER, FG_USER, BG_USER) == ERR || init_pair(PAIR_WON, FG_WON, BG_WON) == ERR)
    {
        endwin();
        return false;
    }

    // Don't echo keyboard input
    if (noecho() == ERR)
    {
        endwin();
        return false;
    }

    // Disable line buffering and certain signals
    if (raw() == ERR)
    {
        endwin();
        return false;
    }

    // Enable arrow keys
    if (keypad(stdscr, true) == ERR)
    {
        endwin();
        return false;
    }

    // Wait 1000 ms at a time for input
    timeout(1000);

    // w00t
    return true;
}
