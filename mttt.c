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
#include <math.h>

#define TRUE 1
#define FALSE 0

#define X 1
#define O 2
#define DRAW 3

/* The following defines board size currently; subject to change */
#define SIZE 3

/* Function declarations */

void clearboard();
int det_winner();           // Returns FALSE, X, O, or DRAW values
void endgame(int);
void getinput();
int checkinput(int, int);   // Returns TRUE if input is valid
void printboard();

/* Global variable declarations */

int board[SIZE][SIZE];     // The gameplay board
int i, ii;                 // Used in for loops as counters
int getoutnow = FALSE;     // Bool, TRUE signifies the end of a game
int i_row, i_col;          // Input stuff
int currentplayer = 0;     // X for X, O for O (1 and 2 respectively)
int x, y;                  // For loops w/ board[][]

/* Begin function definitions */

void clearboard()
{
    // Clear array board[][]; fill it with zeros

    for (i = 0; i < SIZE; i++)
        for (ii = 0; ii < SIZE; ii++)
            board[i][ii] = 0;
}

int det_winner()
{
    // X/O horizontal
    for (x = 0; x < SIZE; x++)
    {
        i = ii = 0;

        for (y = 0; y < SIZE; y++)
        {
            if (board[x][y] == X) i++;
            if (board[x][y] == O) ii++;
        }

        if (i == SIZE) return X;
        if (ii == SIZE) return O;
    }

    // X/O vertical
    for (y = 0; y < SIZE; y++)
    {
        i = ii = 0;

        for (x = 0; x < SIZE; x++)
        {
            if (board[x][y] == X) i++;
            if (board[x][y] == O) ii++;
        }

        if (i == SIZE) return X;
        if (ii == SIZE) return O;
    }

    // Check X/O diagonals

    for (x = 0, y = 0, i = 0, ii = 0; x < SIZE; x++, y++)
    {
        if (board[x][y] == X) i++;
        if (board[x][y] == O) ii++;
    }

    if (i == SIZE) return X;
    if (ii == SIZE) return O;

    for (x = 0, y = SIZE - 1, i = 0, ii = 0; x < SIZE; x++, y--)
    {
        if (board[x][y] == X) i++;
        if (board[x][y] == O) ii++;
    }

    if (i == SIZE) return X;
    if (ii == SIZE) return O;

    // Check for tie

    for (x = 0, i = 0; x < SIZE; x++)
        for (y = 0; y < SIZE; y++)
            if (board[x][y] > 0)
                i++;

    if (i == SIZE * SIZE)
        return DRAW; 

    return FALSE;
}

void endgame(int winner)
{
    getoutnow = TRUE; // Used to tell other function calls not to run

    if (winner == X)
        puts("X has won!");

    if (winner == O)
        puts("O has won!");

    if (winner == DRAW)
        puts("Cat has won!");
}

void printboard()
{
    printf("\n");
    
    for (x = 0; x < SIZE; x++)
    {
        for (y = 0; y < SIZE; y++)
        {
            switch (board[x][y])
            {
                case FALSE : printf("|%d,%d", x + 1, y + 1);
                    break;
                case X : printf("| X ");
                    break;
                case O : printf("| O ");
            }
        }
        
        printf("\n|");

        for (i = 0; i < SIZE; i++)
        {
            printf("---");
            if (i != SIZE - 1)
                printf("+");
            if (i == SIZE - 1)
                printf("\n");
        }
    }

    printf("\n");
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
        
        i_row = i_col = 0;

        printf("Please input row,col [1-%d],[1-%d]: ", SIZE, SIZE);
        scanf("%d,%d", &i_row, &i_col);

        if (checkinput(i_row, i_col) == TRUE)
            break;

        puts("Invalid input, please try again.");
    }
}

int checkinput(int row, int col)
{
    if (((1 <= row) && (row <= SIZE)) &&       // These two lines ensure
        ((1 <= col) && (col <= SIZE)))         // the input is within range
    {
        if (board[row-1][col-1] == 0)
        {
            board[row-1][col-1] = currentplayer;
            return TRUE;
        }
        else
            return FALSE;
    }
    else
        return FALSE;
}

int main()
{
    currentplayer = X;

    while (TRUE)
    {
        // New Game!
    
        clearboard();

        while (getoutnow == FALSE)
        {
            printboard();

            if (det_winner() > FALSE)
                endgame(det_winner());
            
            if (getoutnow == FALSE)
                getinput();

            switch (currentplayer)
            {
                case X : currentplayer = O;
                    break;
                case O : currentplayer = X;
            }
        }

        getoutnow = FALSE;      // Reset to allow another game

        // Would you like to play again?
        
        break;
    }

    puts("Thank you for playing!");

    return 0;
}
