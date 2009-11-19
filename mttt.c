/* MTTT2: A legitimate version of Tic-Tac-Toe, unlike the original MTTT.
 * (c) 2009 Andrew Gray
 *
 * Licensed under the GPLv3, as if that matters for a project this miniscule.
 * All that really means is you can share, distribute, modify, and
 * redistribute this "software" freely, as long as this notice is maintained.
 * Or something like that. Just do whatever you want. I don't care. Seriously.
 */

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define X 1
#define O 2

#define A board[0][0]
#define B board[0][1]
#define C board[0][2]
#define D board[1][0]
#define E board[1][1]
#define F board[1][2]
#define G board[2][0]
#define H board[2][1]
#define I board[2][2]

/* Now that's what I call making code compact. Unfortunately, this is a
 * horrible hack, and is blatant abuse of #define. I do believe a rewrite is
 * in order, my good friend.
 */

#define PRINT case FALSE : printf(" "); break;
#define SPOT case X : printf("X"); break;
#define OWNER case O : printf("O");
 
/* Function declarations */

void clearboard();
void checkvictory();
void endgame(int);
void getinput();
int checkinput(int, int);   // Returns TRUE if input is valid
void printboard();

/* Global variable declarations */

int board[3][3];
int i, ii;                 // Used in 'for' loops
int getoutnow = FALSE;     // Bool, TRUE signifies the end of a game
int i_row, i_col;          // input stuff
int currentplayer = 0;     // X for X, O for O (1 and 2 respectively)

/* Begin function definitions */

void clearboard()
{
    // Clear array board[][]; fill it with zeros

    for (i = 0; i < 3; i++)
        {
            for (ii = 0; ii < 3; ii++)
                {
                    board[i][ii] = 0;
                }
        }
}

void checkvictory()
{
    // Check for X's victory

    if ((A * B * C == 1) ||
        (D * E * F == 1) ||
        (G * H * I == 1) ||
        (A * D * G == 1) ||
        (B * E * H == 1) ||
        (C * F * I == 1) ||
        (A * E * I == 1) ||
        (C * E * G == 1))
            endgame(X);

    // Check for O's victory

    if ((A * B * C == 8) ||
        (D * E * F == 8) ||
        (G * H * I == 8) ||
        (A * D * G == 8) ||
        (B * E * H == 8) ||
        (C * F * I == 8) ||
        (A * E * I == 8) ||
        (C * E * G == 8))
            endgame(O);

    // Check for tie; only if winner has not yet been found

   if (((A != 0) &&
        (B != 0) &&
        (C != 0) &&
        (D != 0) &&
        (E != 0) &&
        (F != 0) &&
        (G != 0) &&
        (H != 0) &&
        (I != 0)) &&
       (getoutnow == FALSE))    // Makes sure that a winner has not been found yet
            endgame(FALSE);

}

void endgame(int winner)
{
    getoutnow = TRUE; // Used to tell other function calls not to run

    if (winner == X)
    {
        puts("X has won!");
    }

    if (winner == O)
    {
        puts("O has won!");
    }

    if (winner == FALSE)
    {
        puts("Cat has won!");
    }
}

void printboard()
{
    printf("\n1| ");
    switch (A) { PRINT SPOT OWNER }
    printf(" | ");
    switch (B) { PRINT SPOT OWNER }
    printf(" | ");
    switch (C) { PRINT SPOT OWNER }
    printf("\n |---+---+---\n2| ");
    switch (D) { PRINT SPOT OWNER }
    printf(" | ");
    switch (E) { PRINT SPOT OWNER }
    printf(" | ");
    switch (F) { PRINT SPOT OWNER }
    printf("\n |---+---+---\n3| ");
    switch (G) { PRINT SPOT OWNER }
    printf(" | ");
    switch (H) { PRINT SPOT OWNER }
    printf(" | ");
    switch (I) { PRINT SPOT OWNER }
    printf("\n +-----------\n   1   2   3\n\n");
}

void getinput()
{
    while (TRUE)
    {
        switch (currentplayer)
        {
            case X : puts("It's X's turn!");
                break;
            case O : puts("It's O's turn!");
        }
/*
        printf("Please input row [1-3]: ");
        scanf("%d", &i_row);
        printf("Please input col [1-3]: ");
        scanf("%d", &i_col);
*/

        printf("Please input row,col [1-3],[1-3]: ");
        scanf("%d,%d", &i_row, &i_col);

        if (checkinput(i_row, i_col) == TRUE)
            break;

        puts("Invalid input, please try again.");
    }
}

int checkinput(int row, int col)
{
    if (((1 <= row) && (row <= 3)) &&       // These two lines ensure
        ((1 <= col) && (col <= 3)))         // the input is within range
    {
    
        if (board[row-1][col-1] == 0)
        {
            board[row-1][col-1] = currentplayer;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}

int main()
{

    currentplayer = X;

    while (TRUE)
    {
        // New Game!
        // Clear the board
    
        clearboard();

        while (getoutnow == FALSE)
        {

            printboard();
            checkvictory();
            
            if (getoutnow == FALSE)
                getinput();

            // Switch player

            switch (currentplayer)
            {
                case X : currentplayer = O;
                    break;
                case O : currentplayer = X;
            }
        }

        getoutnow = FALSE;      // Reset to allow another game

        // Would you like to play again?
        // 1. Yes -- do nothing
        // 2. No -- exit();

        break;
    }

    puts("Thank you for playing!");

    return 0;
}
