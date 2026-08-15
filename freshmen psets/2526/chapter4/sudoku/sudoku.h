// Compile-time options for the game of Sudoku.

// Game's author
#define AUTHOR "Evelyn Chan"

// Game's title
#define TITLE "Sudoku"

// Banner's colors
#define FG_BANNER COLOR_CYAN
#define BG_BANNER COLOR_BLACK

// Grid's colors
#define FG_GRID COLOR_CYAN
#define BG_GRID COLOR_BLACK

// Border's colors
#define FG_BORDER COLOR_WHITE
#define BG_BORDER COLOR_CYAN

// Logo's colors
#define FG_LOGO COLOR_MAGENTA
#define BG_LOGO COLOR_BLACK

// Digits's colors
#define FG_DIGITS COLOR_CYAN
#define BG_DIGITS COLOR_BLACK

// User Digits's colors
#define FG_USER COLOR_CYAN
#define BG_USER COLOR_BLACK

// Winning Digits's colors
#define FG_WON COLOR_GREEN
#define BG_WON COLOR_BLACK

//original colors
#define FG_ORIGINAL COLOR_YELLOW
#define BG_ORIGINAL COLOR_BLACK


// Nicknames for pairs of colors
enum { PAIR_BANNER = 1, PAIR_GRID, PAIR_BORDER, PAIR_LOGO, PAIR_DIGITS, PAIR_USER, PAIR_WON, PAIR_ORIGINAL };
