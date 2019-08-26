/**
 * Author:  Sebastian Turner 
 * Date: 08/26/19
 * 
 * Implements a sudoku board as a 9x9 grouping of 'Cell' types. Each cell type
 * consists of the current value within that cell (0 if not initalized) and
 * whether or not that value is original (was given as a clue).
 * 
 * To initialze a board that represents a given sudoku construction/puzzle. 
 * A string of length 81 (excluding terminator) that row by row represents the
 * given puzzle is to be used as the argument for initSetBoard.
 * 
 * This module also implements functions for checking the legality of a given 
 * sudoku position (set of values for the board). This legality is as defined 
 * in README.md.
 * 
 * Access to this 2d array of cells is done in the way a matrix is 
 * traditionally examined mathamatically. That is all declarations are in
 * [row][col] format.
 * 
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define BOARDSIZE 9 //sudoku boards are sqaure so only one value is needed 

typedef struct cell{
    int value; //The current value in the cell
    bool clue; //Whether or not the given value was an original one
}Cell;

//function prototypes 
Cell **initBoard();    //initialzes an empty board
Cell **initSetBoard(char *clues); //intializes a board from a given clue set
Cell *getCell(int row, int col, Cell **board);

bool checkBoard(Cell **board); //Checks a given board for legality
bool isLegal(Cell *cell);
bool checkRow(Cell **board, int);
bool checkCol(Cell **board);
bool checkSquare(Cell **board);

void printBoard();
void deleteBoard();

/**
 * Creates a 9*9 sudoku board out Cell structs. As there is no independent 
 * sudoku board struct this function will return a pointer to the first value 
 * of the board. 
 * 
 * This function will return NULL if any of the memory requested could not be 
 * allocated
 */ 
Cell** initBoard()
{
    Cell** board;
    for(int i = 0; i < BOARDSIZE; i++){
        board[i] = calloc(BOARDSIZE, sizeof(Cell));
        if(board[i] == NULL){
            return NULL;
        }
        for(int j = 0; j < BOARDSIZE; j++){
            Cell *cell = malloc(sizeof(Cell));
            if(cell == NULL){
                return NULL;
            }
            cell->clue = false;
            cell->value = 0;
            board[i][j] = cell;
        }
    }
}

/**
 * Initialzes a set sudoku board. This is read in as a string of integers of 
 * length 81. This function returns a pointer to the first Cell in the board.
 * 
 * Will return NULL if any of the memory required for the board could not be
 * allocated or if the `clues` argument is not of the proper length (81) or if
 * it contains any non-numerical
 */ 
Cell** initSetBoard(char *clues)
{
    int len = sizeof(clues) - 1; //remove the null terminator from size calcs
    if(len != 81){
        fprintf(stderr, "invalid clues string");
        return NULL;
    }

    //checking that all given values are numerical
    for(int i = 0; i < len; i++){
        int clue = atoi(clues[i]);

    }
}


/**
 * Returns the address of a cell given a specific row and column and the board
 * that that cell resides in. This function will return NULL in the following 
 * circumstances.
 * 
 * 1. Row or Col is < 0 or >= than BOARDSIZE
 * 2. Board is NULL 
 */
Cell *getCell(int row, int col, Cell** board)
{
    if(row < 0 || row >= BOARDSIZE ||
       col < 0 || col >= BOARDSIZE || 
       board == NULL){
           return NULL;
    }

    Cell *cell = board[row][col];
    return cell;
}

/**
 * Checks the given sudoku board for legality of position. If the position is 
 * not legal then this function will return false. This function will also 
 * return false in the case that the given board is NULL or if any of cells 
 * within it are NULL
 */
bool checkBoard(Cell **board) //TO-DO finish ALL legality functions
{
    if(board == NULL){
        fprintf(stderr, "The given board is not initialized");
        return false;
    }

} 


/**
 * Deletes a given board from memory cell by cell. If the given board is NULL
 * this function will simply return and not throw an error.
 */ 
void deleteBoard(Cell **board)
{
    if(board == NULL){
        fprintf(stderr, "The given board is not initialized");
        return;
    }
    
    for(int i = 0; i < BOARDSIZE; i++){
        for(int j = 0; j < BOARDSIZE; j++){
            Cell *cell = board[i][j];
            if(cell != NULL){
                free(cell);
            }
        }
    }
}