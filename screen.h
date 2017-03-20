// includes the function prototypes for screen manipulation
enum COLOR{BLACK=30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};
#define UNICODE
#define BAR "\u2590"	//unicode for a bar

// function prototypes
void setFGcolor(int fq);
void resetColors(void);
void gotoXY(int row, int col);
void displayBar(double rms, int col);
void clearScreen(void);
